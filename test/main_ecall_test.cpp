#include <memory>
#include <string>

#include <cadmium/modeling/devs/coupled.hpp>
#include <limits>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/csv.hpp>

#include "../atomics/ecall.hpp"
#include "../data_structures/messages.hpp"

using namespace std;
using namespace cadmium;

/**
 * ECallExperiment
 * Coupled wrapper (experiment frame) around ECall atomic model.
 *
 */
struct ECallExperiment : public Coupled {
    Port<fe::Floor> call_gen;  // output port (mirrors ECall output)

    ECallExperiment(const string& id,
                    const string& inside_calls_path,
                    const string& outside_calls_path)
        : Coupled(id) {

        call_gen = addOutPort<fe::Floor>("call_gen");

        auto inside_calls = addComponent<lib::IEStream<fe::Floor>>(
          "inside_calls", inside_calls_path.c_str());

        auto outside_calls = addComponent<lib::IEStream<fe::Floor>>(
          "outside_calls", outside_calls_path.c_str());

        auto ecall = addComponent<ECall>("ECall");

        // Input couplings
        addCoupling(inside_calls->out, ecall->inside_call);
        addCoupling(outside_calls->out, ecall->outside_call);

        // Output coupling
        addCoupling(ecall->call_gen, call_gen);
    }
};

int main(int argc, char* argv[]) {
    // Defaults are relative to repo root 
    string inside_path  = "input_data/ecall_inside.txt";
    string outside_path = "input_data/empty_outside.txt";

    // Default output path
    string out_path = "simulation_results/A1_ecall.csv";
    
    // Optional override:
    if (argc >= 3) {
        inside_path  = argv[1];
        outside_path = argv[2];
    }
    if (argc >= 4) {
        out_path = argv[3];
    }

    auto model = make_shared<ECallExperiment>("ECallExperiment", inside_path, outside_path);

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>(out_path, ";");

    rootCoordinator.start();
    rootCoordinator.simulate(50.0); 
    rootCoordinator.stop();

    return 0;
}