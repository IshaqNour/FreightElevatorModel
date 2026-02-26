#ifndef ELEVATOR_COUPLED_HPP
#define ELEVATOR_COUPLED_HPP

#include <string>

#include <cadmium/modeling/devs/coupled.hpp>

#include "../atomics/econtrol.hpp"
#include "../atomics/evehicle.hpp"
#include "../data_structures/messages.hpp"

/**
 *  - components: EControl, EVehicle
 *  - in : acall
 *  - out: floor
 *  - IC : EControl.timem -> EVehicle.in
 *  - IC : EVehicle.out -> EControl.fback
 *  - EIC: acall -> EControl.acall
 *  - EOC: EControl.floor -> floor
 */
struct ElevatorCoupled : public cadmium::Coupled {
    cadmium::Port<fe::Floor> acall;
    cadmium::Port<fe::Floor> floor;

    explicit ElevatorCoupled(const std::string& id) : cadmium::Coupled(id) {
        // External ports
        acall = addInPort<fe::Floor>("acall");
        floor = addOutPort<fe::Floor>("floor");

        // Internal components
        auto ctrl = addComponent<EControl>("EControl");
        auto veh  = addComponent<EVehicle>("EVehicle");

        // EIC: input -> controller
        addCoupling(acall, ctrl->acall);

        // IC: controller <-> vehicle
        addCoupling(ctrl->timem, veh->in);
        addCoupling(veh->out, ctrl->fback);

        // EOC: controller -> output
        addCoupling(ctrl->floor, floor);
    }
};

#endif