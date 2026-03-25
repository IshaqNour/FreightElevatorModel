#include <memory>
#include <string>
#include <limits>

#include <cadmium/modeling/devs/coupled.hpp>
#include <cadmium/lib/iestream.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <cadmium/simulation/logger/stdout.hpp>

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

    explicit EVehicleExperiment(const string& id) : Coupled(id) {

        out = addOutPort<fe::TravelTime>("out");

        auto in_stream = addComponent<lib::IEStream<fe::TravelTime>>(
            "in_stream", "input_data/evehicle_in_test.txt");
        auto veh = addComponent<EVehicle>("EVehicle");

        addCoupling(in_stream->out, veh->in);
        addCoupling(veh->out, out);
    }
};

int main() {
    auto model = make_shared<EVehicleExperiment>("EVehicleExperiment");

    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<STDOUTLogger>(";");

    rootCoordinator.start();
    rootCoordinator.simulate(60.0);
    rootCoordinator.stop();

    return 0;
}
