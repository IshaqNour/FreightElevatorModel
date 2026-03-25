#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/stdout.hpp>

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

    explicit ECallExperiment(const string& id) : Coupled(id) {

        call_gen = addOutPort<fe::Floor>("call_gen");

        auto inside_calls = addComponent<lib::IEStream<fe::Floor>>(
          "inside_calls", "input_data/ecall_inside.txt");

        auto outside_calls = addComponent<lib::IEStream<fe::Floor>>(
          "outside_calls", "input_data/ecall_outside.txt");

        auto ecall = addComponent<ECall>("ECall");

        // Input couplings
        addCoupling(inside_calls->out, ecall->inside_call);
        addCoupling(outside_calls->out, ecall->outside_call);

        // Output coupling
        addCoupling(ecall->call_gen, call_gen);
    }
};

int main() {
    auto model = make_shared<ECallExperiment>("ECallExperiment");

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<STDOUTLogger>(";");

    rootCoordinator.start();
    rootCoordinator.simulate(50.0); 
    rootCoordinator.stop();

    return 0;
}
