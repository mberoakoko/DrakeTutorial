//
// Created by mbero-akoko on 9/9/25.
//

#ifndef DRAKETUTORIAL_FIB_RUNNER_H
#define DRAKETUTORIAL_FIB_RUNNER_H
#include <bits/stdc++.h>
#include "fib_ops.h"
#include <drake/systems/analysis/simulator.h>
#include <drake/systems/framework/diagram_builder.h>
#include <drake/systems/primitives/vector_log_sink.h>
namespace examples::fib_sim {
    constexpr double STEPS = 10;
    inline auto run_fibonnacci_simulation() -> void {
        drake::systems::DiagramBuilder<double> builder;
        auto fibonacci = builder.AddSystem<FibbonacciDifferenceEquation>();
        auto logger = drake::systems::LogVectorOutput(fibonacci->GetOutputPort("F_n"), &builder, fib_sim::K_PERIOD);
        auto diagram = builder.Build();
        drake::systems::Simulator<double> simulator(*diagram);
        simulator.AdvanceTo(fib_sim::STEPS * fib_sim::K_PERIOD);


        const auto log = logger->FindLog(simulator.get_context());

        for (int n = 0; n < log.sample_times().size(); ++n) {
            const double t = log.sample_times()[n];
            std::cout << n << ": " << log.data()(0, n) << std::endl;
        }
        std::cout <<log.data() << std::endl;

    }
}
#endif //DRAKETUTORIAL_FIB_RUNNER_H