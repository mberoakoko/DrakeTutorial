//
// Created by mbero-akoko on 12/5/25.
//

#ifndef DRAKETUTORIAL_BEHAVIORAL_SUBTYPING_HPP
#define DRAKETUTORIAL_BEHAVIORAL_SUBTYPING_HPP
#include <algorithm>
#include <bits/stdc++.h>

namespace fun_with_types {
    constexpr double ARM_MINIMUM_LOAD = 20;
    template<double Mass>
    struct PayLoad {
        double mass = Mass;
    };

    template<double M_Payload, double M_MinRequired>
    concept RequiredMass = M_Payload >= M_MinRequired;

    template<double Value>
    void  move_robot_arm(const PayLoad<Value> pay_load) requires RequiredMass<PayLoad<Value>::mass, ARM_MINIMUM_LOAD>{
        std::cout<< "Moving robot arm with mass " << pay_load.mass <<std::endl;
    };

    auto invoke_move_robot_arm() -> void {
        PayLoad<10.1> pay_load;
        move_robot_arm<10.1>(pay_load);
    }
}

#endif //DRAKETUTORIAL_BEHAVIORAL_SUBTYPING_HPP