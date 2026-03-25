#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>

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

    EControlExperiment(const string& id,
                       const char* calls_path,
                       const char* fback_path)
        : Coupled(id) {

        timem = addOutPort<fe::TravelTime>("timem");
        floor = addOutPort<fe::Floor>("floor");

        auto calls = addComponent<lib::IEStream<fe::Floor>>(
            "calls", calls_path);
        auto fback = addComponent<lib::IEStream<fe::TravelTime>>(
            "fback", fback_path);

        auto ctrl = addComponent<EControl>("EControl");

        addCoupling(calls->out, ctrl->acall);
        addCoupling(fback->out, ctrl->fback);

        addCoupling(ctrl->timem, timem);
        addCoupling(ctrl->floor, floor);
    }
};

int main(int argc, char* argv[]) {
    string calls_path = "input_data/econtrol_queue_calls.txt";
    string fback_path = "input_data/econtrol_queue_fback.txt";
    string out_csv    = "simulation_results/A6_econtrol.csv";

    if (argc >= 3) {
        calls_path = argv[1];
        fback_path = argv[2];
    }
    if (argc >= 4) {
        out_csv = argv[3];
    }

    auto model = make_shared<EControlExperiment>(
        "EControlExperiment", calls_path.c_str(), fback_path.c_str());

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>(out_csv, ";");

    rootCoordinator.start();
    rootCoordinator.simulate(50.0);
    rootCoordinator.stop();

    return 0;
}
