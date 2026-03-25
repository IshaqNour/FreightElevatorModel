#include <memory>

#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/stdout.hpp>

#include "experiment.hpp"

using namespace std;
using namespace cadmium;

int main() {
    auto model = std::make_shared<FreightElevatorExperiment>(
        "freight_elevator_experiment",
        "input_data/fe_inside_calls.txt",
        "input_data/fe_outside_calls.txt"
    );

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<STDOUTLogger>(";");

    rootCoordinator.start();
    rootCoordinator.simulate(90.0);
    rootCoordinator.stop();

    return 0;
}
