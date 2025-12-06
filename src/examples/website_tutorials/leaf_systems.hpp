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
          this->DeclareVectorOutputPort(std::string(SUM_PORT).c_str(), 2, &MyAdder::calc_difference);
          this->DeclareVectorOutputPort(std::string(DIFFERENCE_PORT).c_str(), 2, &MyAdder::calc_sum);

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
            this->DeclareDiscreteState(0.0);
            this->DeclareVectorInputPort(std::string(MY_ACCUMULATOR_INPUT_PORT).c_str(), 1);
            this->DeclareVectorOutputPort(std::string(MY_ACCUMULATOR_OUTPUT_PORT).c_str(),  1, &MyAccumulator::calc_accumulated_sum);
        }

    private:
        auto calc_accumulated_sum(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* output) const -> void {
            const auto input_value = this->get_input_port(0).Eval(ctx);
            const auto internal_state = ctx.get_discrete_state();

        }

        auto calc_discrete_state(const drake::systems::Context<double>& ctx, drake::systems::BasicVector<double>* output) const -> void {

        }

    };
}
#endif //DRAKETUTORIAL_LEAF_SYSTEMS_HPP