#include <memory>

#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>

#include "experiment.hpp"

using namespace std;
using namespace cadmium;

int main(int argc, char** argv) {
    string inside_path  = (argc > 1) ? argv[1] : "input_data/fe_inside_calls.txt";
    string outside_path = (argc > 2) ? argv[2] : "input_data/fe_outside_calls.txt";
    string out_csv      = (argc > 3) ? argv[3] : "simulation_results/T2_top.csv";

    auto model = std::make_shared<FreightElevatorExperiment>(
        "freight_elevator_experiment",
        inside_path,
        outside_path
    );

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>(out_csv, ";");

    rootCoordinator.start();
    rootCoordinator.simulate(90.0);
    rootCoordinator.stop();

    return 0;
}
