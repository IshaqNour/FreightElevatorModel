#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>

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

    ElevatorExperiment(const string& id, const char* calls_path)
        : Coupled(id) {

        floor = addOutPort<fe::Floor>("floor");

        auto calls    = addComponent<lib::IEStream<fe::Floor>>(
            "calls", calls_path);
        auto elevator = addComponent<ElevatorCoupled>("Elevator");

        addCoupling(calls->out, elevator->acall);
        addCoupling(elevator->floor, floor);
    }
};

int main(int argc, char* argv[]) {
    string calls_path = "input_data/elevator_calls_test.txt";
    string out_csv    = "simulation_results/C1_elevator.csv";

    if (argc >= 2) {
        calls_path = argv[1];
    }
    if (argc >= 3) {
        out_csv = argv[2];
    }

    auto model = make_shared<ElevatorExperiment>("ElevatorExperiment", calls_path.c_str());

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>(out_csv, ";");

    rootCoordinator.start();
    rootCoordinator.simulate(60.0);
    rootCoordinator.stop();

    return 0;
}
