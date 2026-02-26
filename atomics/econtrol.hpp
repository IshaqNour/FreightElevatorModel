#ifndef ECONTROL_HPP
#define ECONTROL_HPP

#include <cadmium/modeling/devs/atomic.hpp>
#include <deque>
#include <limits>
#include <ostream>
#include <string>
#include <cstdlib>   
#include <algorithm> 

#include "../data_structures/messages.hpp"

/**
 * EControl
 *
 * Adaptation from CD++ model:
 *  - After ARRIVED if queue is not empty we automatically issue the next move
 *    without requiring a new acall event.
 */

enum class EControlPhase { IDLE, ISSUE_MOVE, WAIT_DONE, ARRIVED };

struct EControlState {
    EControlPhase phase;
    fe::Floor current_floor;
    fe::Floor target_floor;
    std::deque<fe::Floor> queue;
    double sigma;

    EControlState()
        : phase(EControlPhase::IDLE),
          current_floor(1),
          target_floor(1),
          queue(),
          sigma(std::numeric_limits<double>::infinity()) {}
};

inline std::ostream& operator<<(std::ostream& os, const EControlState& s) {
    auto phaseStr = [&]() -> const char* {
        switch (s.phase) {
            case EControlPhase::IDLE: return "IDLE";
            case EControlPhase::ISSUE_MOVE: return "ISSUE_MOVE";
            case EControlPhase::WAIT_DONE: return "WAIT_DONE";
            case EControlPhase::ARRIVED: return "ARRIVED";
        }
        return "UNKNOWN";
    };

    os << "{phase:" << phaseStr()
       << ",cur:" << s.current_floor
       << ",target:" << s.target_floor
       << ",q:" << s.queue.size()
       << ",sigma:" << s.sigma << "}";
    return os;
}

class EControl : public cadmium::Atomic<EControlState> {
public:
    // Ports
    cadmium::Port<fe::Floor>      acall;
    cadmium::Port<fe::TravelTime> fback;
    cadmium::Port<fe::TravelTime> timem;
    cadmium::Port<fe::Floor>      floor;

    explicit EControl(const std::string& id)
        : cadmium::Atomic<EControlState>(id, EControlState()) {

        acall = addInPort<fe::Floor>("acall");
        fback = addInPort<fe::TravelTime>("fback");
        timem = addOutPort<fe::TravelTime>("timem");
        floor = addOutPort<fe::Floor>("floor");
    }

    static fe::TravelTime travelTime(fe::Floor from, fe::Floor to) {
        return static_cast<fe::TravelTime>(std::abs(to - from)); // 1 time unit per floor
    }

    void externalTransition(EControlState& s, double e) const override {
        if (s.sigma != std::numeric_limits<double>::infinity()) {
            s.sigma = std::max(0.0, s.sigma - e);
        }

        // 1) Handle incoming calls: enqueue all floors from the bag
        if (!acall->empty()) {
            for (const auto& f : acall->getBag()) {
                s.queue.push_back(f);
            }

            // If IDLE, immediately start servicing the first queued request
            if (s.phase == EControlPhase::IDLE && !s.queue.empty()) {
                s.target_floor = s.queue.front();
                s.queue.pop_front();
                s.phase = EControlPhase::ISSUE_MOVE;
                s.sigma = 0.0;
            }
        }

        // 2) Handle feedback
        if (!fback->empty() && s.phase == EControlPhase::WAIT_DONE) {
            // fback is treated as a completion signal (value can be ignored)
            s.phase = EControlPhase::ARRIVED;
            s.sigma = 0.0;
        }
    }

    void output(const EControlState& s) const override {
        if (s.phase == EControlPhase::ISSUE_MOVE) {
            timem->addMessage(travelTime(s.current_floor, s.target_floor));
        }

        if (s.phase == EControlPhase::ARRIVED) {
            floor->addMessage(s.target_floor);
        }
    }

    void internalTransition(EControlState& s) const override {
        if (s.phase == EControlPhase::ISSUE_MOVE) {
            // After issuing a move command, wait for vehicle feedback
            s.phase = EControlPhase::WAIT_DONE;
            s.sigma = std::numeric_limits<double>::infinity();
            return;
        }

        if (s.phase == EControlPhase::ARRIVED) {
            // Update current floor to where we arrived
            s.current_floor = s.target_floor;

            // If more requests exist, issue next move immediately
            if (!s.queue.empty()) {
                s.target_floor = s.queue.front();
                s.queue.pop_front();
                s.phase = EControlPhase::ISSUE_MOVE;
                s.sigma = 0.0;
            } else {
                s.phase = EControlPhase::IDLE;
                s.sigma = std::numeric_limits<double>::infinity();
            }
        }
    }

    void confluentTransition(EControlState& s, double /*e*/) const override {
        internalTransition(s);
        externalTransition(s, 0.0);
    }

    [[nodiscard]] double timeAdvance(const EControlState& s) const override {
        return s.sigma;
    }
};

#endif