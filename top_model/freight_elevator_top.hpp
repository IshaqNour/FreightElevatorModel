#ifndef FREIGHT_ELEVATOR_TOP_HPP
#define FREIGHT_ELEVATOR_TOP_HPP

#include <string>
#include <cadmium/modeling/devs/coupled.hpp>

#include "../atomics/ecall.hpp"
#include "elevator_coupled.hpp"
#include "../data_structures/messages.hpp"

/**
 *  - Inputs : inside_call, outside_call
 *  - Output : floor
 *  - Components: ECall, ElevatorCoupled
 *  - Couplings:
 *      inside_call  -> ECall.inside_call
 *      outside_call -> ECall.outside_call
 *      ECall.call_gen -> ElevatorCoupled.acall
 *      ElevatorCoupled.floor -> floor
 */
struct FreightElevatorTop : public cadmium::Coupled {
    cadmium::Port<fe::Floor> inside_call;
    cadmium::Port<fe::Floor> outside_call;
    cadmium::Port<fe::Floor> floor;

    explicit FreightElevatorTop(const std::string& id) : cadmium::Coupled(id) {
        // External ports
        inside_call  = addInPort<fe::Floor>("inside_call");
        outside_call = addInPort<fe::Floor>("outside_call");
        floor        = addOutPort<fe::Floor>("floor");

        // Components
        auto ecall    = addComponent<ECall>("ECall");
        auto elevator = addComponent<ElevatorCoupled>("Elevator");

        // Input couplings
        addCoupling(inside_call,  ecall->inside_call);
        addCoupling(outside_call, ecall->outside_call);

        // Internal coupling
        addCoupling(ecall->call_gen, elevator->acall);

        // Output coupling
        addCoupling(elevator->floor, floor);
    }
};

#endif