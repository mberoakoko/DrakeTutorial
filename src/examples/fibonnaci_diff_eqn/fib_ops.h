//
// Created by mbero-akoko on 9/9/25.
//

#ifndef DRAKETUTORIAL_FIB_OPS_H
#define DRAKETUTORIAL_FIB_OPS_H

#include <drake/systems/framework/event.h>
#include <drake/systems/framework/leaf_system.h>

namespace examples::fib_sim {
    constexpr double K_PERIOD = 0.1;

    class FibbonacciDifferenceEquation: public drake::systems::LeafSystem<double> {
    public:
        explicit FibbonacciDifferenceEquation() {
            this->DeclareDiscreteState(Eigen::Vector2<double>{0.0, 1.0});
            this->DeclarePeriodicDiscreteUpdateEvent(fib_sim::K_PERIOD, 0, &FibbonacciDifferenceEquation::update);
            this->DeclareVectorOutputPort("F_n", 1, &FibbonacciDifferenceEquation::output);
        }

    private:
        auto update(const drake::systems::Context<double>& ctx, drake::systems::DiscreteValues<double>* xd) const -> void {
            const auto& x_n = ctx.get_discrete_state();
            (*xd)[0] = x_n[0] + x_n[1];
            (*xd)[1] = x_n[0];
        }

        auto output(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* result) const -> void {
            const auto f_n = ctx.get_discrete_state()[0];
            (*result)[0] = f_n;
        }
    };

}
#endif //DRAKETUTORIAL_FIB_OPS_H