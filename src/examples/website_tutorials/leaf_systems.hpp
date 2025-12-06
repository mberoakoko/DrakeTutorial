//
// Created by mbero-akoko on 9/9/25.
//

#ifndef DRAKETUTORIAL_LEAF_SYSTEMS_HPP
#define DRAKETUTORIAL_LEAF_SYSTEMS_HPP
#include <drake/systems/framework/system.h>
#include <drake/systems/framework/leaf_system.h>
#include <drake/systems/framework/vector_base.h>
namespace examples::authoring_leaf_systems {

    constexpr std::string_view SUM_PORT = "sum";
    constexpr std::string_view DIFFERENCE_PORT = "difference";

    class MyAdder final : public  drake::systems::LeafSystem<double> {

    public:

      explicit MyAdder() {
          this-> DeclareVectorInputPort("a", 2);
          this->DeclareVectorInputPort("b", 2);
          this->DeclareVectorOutputPort(std::string(SUM_PORT).c_str(), 2, &MyAdder::calc_sum);
          this->DeclareVectorOutputPort(std::string(DIFFERENCE_PORT).c_str(), 2, &MyAdder::calc_difference);

      }
        auto calc_sum(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* output) const -> void {
            const auto& a = this->get_input_port(0).Eval(ctx);
            const auto& b =this->get_input_port(1).Eval(ctx);
            output->SetFromVector( a + b);
        }

        auto calc_difference(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* output) const ->  void {
            const auto& a = this->get_input_port(0).Eval(ctx);
            const auto& b = this->get_input_port(1).Eval(ctx);
            output->SetFromVector(a - b);
        }
    };

    inline auto run_adder() -> void {
        MyAdder my_adder;
        auto context = my_adder.CreateDefaultContext();
        Eigen::Vector2d a_input(1.0, 2.0);
        Eigen::Vector2d b_input(1.0, 2.0);

        my_adder.get_input_port(0).FixValue(context.get(), a_input);
        my_adder.get_input_port(1).FixValue(context.get(), b_input);

        auto sum_output = my_adder.AllocateOutput();
        auto differnce_output = my_adder.AllocateOutput();
        using OutputPort_T = drake::systems::OutputPort<double>;
        const OutputPort_T& sum_port  = my_adder.get_output_port(0);
        const OutputPort_T& diff_port = my_adder.get_output_port(1);

        sum_port.Calc(*context, sum_output->GetMutableData(0));

        const auto difference_vector = sum_output->get_vector_data(0)->get_value();
        std::cout << difference_vector << std::endl;

    }

    constexpr std::string_view MY_ACCUMULATOR_INPUT_PORT = "input";
    constexpr std::string_view MY_ACCUMULATOR_OUTPUT_PORT = "output";

    class MyAccumulator final: public drake::systems::LeafSystem<double> {
    public:
        explicit MyAccumulator() {
            this->DeclareDiscreteState(1);
            this->DeclareVectorInputPort(std::string(MY_ACCUMULATOR_INPUT_PORT).c_str(), 1);
            this->DeclareVectorOutputPort(std::string(MY_ACCUMULATOR_OUTPUT_PORT).c_str(),  1, &MyAccumulator::calc_accumulated_sum);
        }

    private:
        auto calc_accumulated_sum(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* output) const -> void {
            const auto& current_state = ctx.get_discrete_state(0).get_value();
            output->SetFromVector(current_state);
        }

        auto calc_discrete_state(const drake::systems::Context<double>& ctx, drake::systems::DiscreteValues<double>* updates) const -> void {
            auto current_state = ctx.get_discrete_state(0).get_value();
            auto x_k = current_state(0);
            const auto& u_k_vector = this->get_input_port(0).Eval(ctx);
            const auto u_k = u_k_vector(0);
            (*updates)[0] = x_k + u_k;
        }

    };


    inline auto run_accumulator() -> void {
        MyAccumulator my_accumulator;
        auto context = my_accumulator.CreateDefaultContext();
        drake::systems::Simulator simulator(my_accumulator, std::move(context));
        double initial_value = 5.0;
        Eigen::Vector<double, 1> input_vector(initial_value);
        std::cout << "input vector : " << input_vector << std::endl;
        my_accumulator.get_input_port(0).FixValue(&simulator.get_mutable_context(), input_vector);
        simulator.AdvanceTo(1);

        const auto& final_context = simulator.get_context();
        const auto& output_port = my_accumulator.get_output_port(0);

        auto output = my_accumulator.AllocateOutput();
        output_port.Calc(final_context, output->GetMutableData(0));

        const auto final_sum = output->get_vector_data(0)->get_value();

        std::cout << "Initial Value x[0]: " << initial_value << std::endl;
        std::cout << "Input Value u[k]: " << input_vector(0) << std::endl;
        std::cout << "Final Accumulated Sum x[1] (at t=1.0): " << final_sum(0) << std::endl;
    }

    namespace continous_integrator {
        namespace config {
            constexpr std::string_view CONTINOUS_INTEGRATOR_INPUT_PORT = "u";
            constexpr std::string_view CONTINOUS_INTEGRATOR_OUTPUT_PORT = "x";

            constexpr std::uint8_t INPUT_PORT_SIZE = 1;
            constexpr std::uint8_t OUTPUT_PORT_SIZE = 1;
        }

        class MyContinousIntegrator final : public drake::systems::LeafSystem<double> {
        public:
            explicit MyContinousIntegrator() {
                this->DeclareVectorInputPort(std::string(config::CONTINOUS_INTEGRATOR_INPUT_PORT).c_str(), config::INPUT_PORT_SIZE);
                this->DeclareVectorOutputPort(std::string(config::CONTINOUS_INTEGRATOR_OUTPUT_PORT).c_str(), config::OUTPUT_PORT_SIZE, &MyContinousIntegrator::output);
            }

        private:
            auto update(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* derivatives) const -> void {

            }


            auto output(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* output) const -> void {

            }
        };
    }
}
#endif //DRAKETUTORIAL_LEAF_SYSTEMS_HPP