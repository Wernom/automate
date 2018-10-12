#include <iostream>
#include <iomanip>
#include "gtest/gtest.h"
#include "Automaton.h"

class AutomatonTest : public ::testing::Test {
protected:
    void SetUp() override {
        automatonNotCompleteNotDeterministic.addState(0);
        automatonNotCompleteNotDeterministic.setStateInitial(0);
        automatonNotCompleteNotDeterministic.addState(1);
        automatonNotCompleteNotDeterministic.setStateFinal(1);
        automatonNotCompleteNotDeterministic.setStateInitial(1);
        automatonNotCompleteNotDeterministic.addState(3);
        automatonNotCompleteNotDeterministic.addState(2);
        automatonNotCompleteNotDeterministic.addState(4);
        automatonNotCompleteNotDeterministic.setStateFinal(4);
    }

    fa::Automaton automatonNotCompleteNotDeterministic;

};


//TEST_F(AutomatonTest, Empty) {
//    fa::Automaton fa;
//
//    EXPECT_EQ(fa.countStates(), 0u);
//    EXPECT_EQ(fa.countTransitions(), 0u);
//}

/**
 * Print an automaton
 */
TEST_F(AutomatonTest, prettyPrint){
    automatonNotCompleteNotDeterministic.prettyPrint(std::cout);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
