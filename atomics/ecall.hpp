#ifndef ECALL_HPP
#define ECALL_HPP

#include <cadmium/modeling/devs/atomic.hpp>
#include <algorithm>
#include <limits>
#include <ostream>
#include <string>

#include "../data_structures/messages.hpp"

/**
 * ECall (Cadmium v2 Atomic Model)
 *
 * Purpose:
 *  - Receives call requests from inside/outside the elevator.
 *  - Immediately outputs the selected requested floor on call_gen.
 *
 * Behavior (adapted from CD++ Ecall + Part II DEVS Graph):
 *  - PASSIVE (sigma = inf): waiting for a call.
 *  - On any input: store requested floor and go ACTIVE (sigma = 0).
 *  - Output stored floor via call_gen, then return PASSIVE.
 *  - Tie rule: if inside_call and outside_call arrive at the same time,
 *    inside_call takes priority.
 *
 */

enum class ECallPhase { PASSIVE, ACTIVE };

struct ECallState {
    ECallPhase phase;
    bool has_pending;
    fe::Floor pending_floor;
    double sigma;

    ECallState()
        : phase(ECallPhase::PASSIVE),
          has_pending(false),
          pending_floor(0),
          sigma(std::numeric_limits<double>::infinity()) {}
};

inline std::ostream& operator<<(std::ostream& os, const ECallState& s) {
    os << "{phase:" << (s.phase == ECallPhase::PASSIVE ? "PASSIVE" : "ACTIVE")
       << ",has_pending:" << (s.has_pending ? "true" : "false")
       << ",pending_floor:" << s.pending_floor
       << ",sigma:" << s.sigma << "}";
    return os;
}

class ECall : public cadmium::Atomic<ECallState> {
public:
    // Ports
    cadmium::Port<fe::Floor> inside_call;
    cadmium::Port<fe::Floor> outside_call;
    cadmium::Port<fe::Floor> call_gen;

    explicit ECall(const std::string& id)
        : cadmium::Atomic<ECallState>(id, ECallState()) {

        inside_call  = addInPort<fe::Floor>("inside_call");
        outside_call = addInPort<fe::Floor>("outside_call");
        call_gen     = addOutPort<fe::Floor>("call_gen");
    }

    void externalTransition(ECallState& s, double e) const override {
        // Cadmium manual pattern: subtract elapsed time from sigma
        if (s.sigma != std::numeric_limits<double>::infinity()) {
            s.sigma = std::max(0.0, s.sigma - e);
        }

        // Tie rule: inside_call wins if both ports have messages at same time.
        if (!inside_call->empty()) {
            s.pending_floor = inside_call->getBag().back();  // last message
            s.has_pending = true;
            s.phase = ECallPhase::ACTIVE;
            s.sigma = 0.0;
        } else if (!outside_call->empty()) {
            s.pending_floor = outside_call->getBag().back(); // last message
            s.has_pending = true;
            s.phase = ECallPhase::ACTIVE;
            s.sigma = 0.0;
        }
        // else: no relevant input => do nothing
    }

    void output(const ECallState& s) const override {
        if (s.phase == ECallPhase::ACTIVE && s.has_pending) {
            call_gen->addMessage(s.pending_floor);
        }
    }

    void internalTransition(ECallState& s) const override {
        // After output, return to PASSIVE
        s.phase = ECallPhase::PASSIVE;
        s.has_pending = false;
        s.sigma = std::numeric_limits<double>::infinity();
    }

    void confluentTransition(ECallState& s, double /*e*/) const override {
        // Standard DEVS confluent pattern (Cadmium style): internal then external(e=0)
        internalTransition(s);
        externalTransition(s, 0.0);
    }

    [[nodiscard]] double timeAdvance(const ECallState& s) const override {
        return s.sigma;
    }
};

#endif