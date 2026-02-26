#ifndef FREIGHT_ELEVATOR_EXPERIMENT_HPP
#define FREIGHT_ELEVATOR_EXPERIMENT_HPP

#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>

#include "freight_elevator_top.hpp"
#include "../data_structures/messages.hpp"

/**
 * - Two IEStreams feed inside/outside call ports
 */
struct FreightElevatorExperiment : public cadmium::Coupled {
    cadmium::Port<fe::Floor> floor;

    FreightElevatorExperiment(const std::string& id,
                              const std::string& inside_calls_file,
                              const std::string& outside_calls_file)
        : cadmium::Coupled(id) {

        floor = addOutPort<fe::Floor>("floor");

        auto inside_calls = addComponent<cadmium::lib::IEStream<fe::Floor>>(
            "inside_calls", inside_calls_file.c_str());

        auto outside_calls = addComponent<cadmium::lib::IEStream<fe::Floor>>(
            "outside_calls", outside_calls_file.c_str());

        auto system = addComponent<FreightElevatorTop>("freight_elevator");

        addCoupling(inside_calls->out, system->inside_call);
        addCoupling(outside_calls->out, system->outside_call);
        addCoupling(system->floor, floor);
    }
};

#endif