#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>

#include "../atomics/evehicle.hpp"
#include "../data_structures/messages.hpp"

using namespace std;
using namespace cadmium;

/**
 * EVehicleExperiment
 * Coupled wrapper (experiment frame) around EVehicle atomic model.
 */
struct EVehicleExperiment : public Coupled {
    Port<fe::TravelTime> out;

    EVehicleExperiment(const string& id, const char* in_path)
        : Coupled(id) {

        out = addOutPort<fe::TravelTime>("out");

        auto in_stream = addComponent<lib::IEStream<fe::TravelTime>>("in_stream", in_path);
        auto veh = addComponent<EVehicle>("EVehicle");

        addCoupling(in_stream->out, veh->in);
        addCoupling(veh->out, out);
    }
};

int main(int argc, char* argv[]) {
    string in_path = "input_data/evehicle_single_in.txt";
    string out_csv = "simulation_results/A4_evehicle.csv";

    if (argc >= 2) in_path = argv[1];
    if (argc >= 3) out_csv = argv[2];

    auto model = make_shared<EVehicleExperiment>("EVehicleExperiment", in_path.c_str());

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>(out_csv, ";");

    rootCoordinator.start();
    rootCoordinator.simulate(60.0);
    rootCoordinator.stop();

    return 0;
}