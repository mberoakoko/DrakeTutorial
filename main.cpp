#include <iostream>

#include <drake/systems/framework/leaf_system.h>
#include <drake/systems/primitives/adder.h>
#include <drake/common/text_logging.h>

#include "src/examples/fibonnaci_diff_eqn/fib_runner.h"

namespace examples {
    auto do_main() -> void {
        drake::log()->info("hello from main");
    }

    class ExampleDiscreteSystem: public drake::systems::LeafSystem<double> {
    public:
        DRAKE_NO_COPY_NO_MOVE_NO_ASSIGN(ExampleDiscreteSystem)
        explicit ExampleDiscreteSystem() {
            this->DeclareDiscreteState(1);

            this->DeclarePeriodicDiscreteUpdateEvent(kPeriod, kOffset, &ExampleDiscreteSystem::update);
            this->DeclareVectorOutputPort("Sn", 1, &ExampleDiscreteSystem::output);
        }

        static constexpr double kPeriod = 1 / 50.;  // Update at 50Hz (h=1/50).
        static constexpr double kOffset = 0.;

    private:
        auto update(const drake::systems::Context<double>& ctx, drake::systems::DiscreteValues<double>* xd) const -> void {
            const double x_n = ctx.get_discrete_state()[0];
            (*xd)[0] = x_n + 1.0;
        }

        auto output(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* result) const -> void {
            const double x_n = ctx.get_discrete_state()[0];
            const double s_n = 10 + x_n;
            (*result)[0] = s_n;
        }
    };

    auto run_simulation() -> void {

    }
}


int main() {
    examples::fib_sim::run_fibonnacci_simulation();
    return 0;
}