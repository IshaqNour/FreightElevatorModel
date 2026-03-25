#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/stdout.hpp>

#include "../atomics/econtrol.hpp"
#include "../data_structures/messages.hpp"

using namespace std;
using namespace cadmium;

/**
 * EControlExperiment
 * Coupled wrapper (experiment frame) around EControl atomic model.
 */
struct EControlExperiment : public Coupled {
    Port<fe::TravelTime> timem;
    Port<fe::Floor>      floor;

    explicit EControlExperiment(const string& id) : Coupled(id) {

        timem = addOutPort<fe::TravelTime>("timem");
        floor = addOutPort<fe::Floor>("floor");

        auto calls = addComponent<lib::IEStream<fe::Floor>>(
            "calls", "input_data/econtrol_queue_calls.txt");
        auto fback = addComponent<lib::IEStream<fe::TravelTime>>(
            "fback", "input_data/econtrol_queue_fback.txt");

        auto ctrl = addComponent<EControl>("EControl");

        addCoupling(calls->out, ctrl->acall);
        addCoupling(fback->out, ctrl->fback);

        addCoupling(ctrl->timem, timem);
        addCoupling(ctrl->floor, floor);
    }
};

int main() {
    auto model = make_shared<EControlExperiment>("EControlExperiment");

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<STDOUTLogger>(";");

    rootCoordinator.start();
    rootCoordinator.simulate(50.0);
    rootCoordinator.stop();

    return 0;
}
