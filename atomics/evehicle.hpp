#ifndef EVEHICLE_HPP
#define EVEHICLE_HPP

#include <cadmium/modeling/devs/atomic.hpp>
#include <algorithm>
#include <limits>
#include <ostream>
#include <string>

#include "../data_structures/messages.hpp"

/**
 * EVehicle 
 */

enum class EVehiclePhase { IDLE, MOVING };

struct EVehicleState {
    EVehiclePhase phase;
    fe::TravelTime travel_time;   // t
    double sigma;                 // time advance

    EVehicleState()
        : phase(EVehiclePhase::IDLE),
          travel_time(0),
          sigma(std::numeric_limits<double>::infinity()) {}
};

inline std::ostream& operator<<(std::ostream& os, const EVehicleState& s) {
    os << "{phase:" << (s.phase == EVehiclePhase::IDLE ? "IDLE" : "MOVING")
       << ",t:" << s.travel_time
       << ",sigma:" << s.sigma << "}";
    return os;
}

class EVehicle : public cadmium::Atomic<EVehicleState> {
public:
    cadmium::Port<fe::TravelTime> in;
    cadmium::Port<fe::TravelTime> out;

    explicit EVehicle(const std::string& id)
        : cadmium::Atomic<EVehicleState>(id, EVehicleState()) {

        in  = addInPort<fe::TravelTime>("in");
        out = addOutPort<fe::TravelTime>("out");
    }

    void externalTransition(EVehicleState& s, double e) const override {
        if (s.sigma != std::numeric_limits<double>::infinity()) {
            s.sigma = std::max(0.0, s.sigma - e);
        }

        // Accept new command ONLY if IDLE
        if (s.phase == EVehiclePhase::IDLE && !in->empty()) {
            s.travel_time = in->getBag().back(); // take last message in the bag
            s.phase = EVehiclePhase::MOVING;
            s.sigma = static_cast<double>(s.travel_time);
        }
        // If MOVING: ignore any input (no transition in DEVS graph)
    }

    void output(const EVehicleState& s) const override {
        // Output occurs at end of MOVING
        if (s.phase == EVehiclePhase::MOVING) {
            out->addMessage(s.travel_time);
        }
    }

    void internalTransition(EVehicleState& s) const override {
        // MOVING completes, go back to IDLE
        if (s.phase == EVehiclePhase::MOVING) {
            s.phase = EVehiclePhase::IDLE;
            s.travel_time = 0;
            s.sigma = std::numeric_limits<double>::infinity();
        }
    }

    void confluentTransition(EVehicleState& s, double /*e*/) const override {
        internalTransition(s);
        externalTransition(s, 0.0);
    }

    [[nodiscard]] double timeAdvance(const EVehicleState& s) const override {
        return s.sigma;
    }
};

#endif