#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/stdout.hpp>

#include "../top_model/elevator_coupled.hpp"
#include "../data_structures/messages.hpp"

using namespace std;
using namespace cadmium;

/**
 * Coupled experiment frame:
 *  IEStream(acall) -> ElevatorCoupled -> floor
 */
struct ElevatorExperiment : public Coupled {
    Port<fe::Floor> floor;

    explicit ElevatorExperiment(const string& id) : Coupled(id) {

        floor = addOutPort<fe::Floor>("floor");

        auto calls    = addComponent<lib::IEStream<fe::Floor>>(
            "calls", "input_data/elevator_calls_test.txt");
        auto elevator = addComponent<ElevatorCoupled>("Elevator");

        addCoupling(calls->out, elevator->acall);
        addCoupling(elevator->floor, floor);
    }
};

int main() {
    auto model = make_shared<ElevatorExperiment>("ElevatorExperiment");

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<STDOUTLogger>(";");

    rootCoordinator.start();
    rootCoordinator.simulate(60.0);
    rootCoordinator.stop();

    return 0;
}
