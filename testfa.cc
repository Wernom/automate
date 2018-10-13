#include <iostream>
#include <iomanip>
#include "gtest/gtest.h"
#include "Automaton.h"

class AutomatonTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        intitAutomatonNotCompleteNotDeterministic(automatonNotCompleteNotDeterministic);
    }

    void intitAutomatonNotCompleteNotDeterministic(fa::Automaton &aut){
        aut.addState(0);
        aut.setStateInitial(0);
        aut.addState(1);
        aut.setStateFinal(1);
        aut.setStateInitial(1);
        aut.addState(3);
        aut.addState(2);
        aut.addState(4);
        aut.setStateFinal(4);
        aut.addTransition(0,'a',1);
        aut.addTransition(0,'a',2);
        aut.addTransition(0,'a',3);
        aut.addTransition(1,'b',3);
        aut.addTransition(2,'a',3);
        aut.addTransition(2,'b',4);
        aut.addTransition(3,'a',3);
        aut.addTransition(3,'b',4);
        aut.addTransition(4,'a',4);
    }

    fa::Automaton automatonNotCompleteNotDeterministic;

};


//TEST_F(AutomatonTest, Empty) {
//    fa::Automaton fa;
//
//    EXPECT_EQ(fa.countStates(), 0u);
//    EXPECT_EQ(fa.countTransitions(), 0u);
//}


//*************************************************************************************
//                  AUTOMATON TEST
//*************************************************************************************

//addState
TEST_F(AutomatonTestFixture, addState){
    EXPECT_EQ(automatonNotCompleteNotDeterministic.countStates(), 5u);
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(0));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(1));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(2));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(3));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(4));
}

//removeState
TEST_F(AutomatonTestFixture, removeState){
    automatonNotCompleteNotDeterministic.removeState(0);
    EXPECT_EQ(automatonNotCompleteNotDeterministic.countStates(), 4u);
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.hasState(0));
}

//Initial/Final
TEST(AutomatonTest, setInitialTestStateDontExist){
    fa::Automaton aut;
    ASSERT_DEATH( { aut.setStateInitial(123); }, "");
}

TEST(AutomatonTest, setInitialTestStateExistIsInitial){
    fa::Automaton aut;
    aut.addState(0);
    aut.setStateInitial(0);
    ASSERT_TRUE(aut.isStateInitial(0));
}

TEST(AutomatonTest, setInitialTestStateExistNotInitial){
    fa::Automaton aut;
    aut.addState(0);
    ASSERT_FALSE(aut.isStateInitial(0));
}



TEST(AutomatonTest, setFinalTestDontExist){
    fa::Automaton aut;
    ASSERT_DEATH( { aut.setStateInitial(123); }, "");
}

TEST(AutomatonTest, setFinalTestStateExistIsInitial){
    fa::Automaton aut;
    aut.addState(0);
    aut.setStateFinal(0);
    ASSERT_TRUE(aut.isStateFinal(0));
}

TEST(AutomatonTest, setFinalTestStateExistNotFinal){
    fa::Automaton aut;
    aut.addState(0);
    ASSERT_FALSE(aut.isStateFinal(0));
}

//addTransition

TEST(AutomatonTest, addTransitionTestStateExistTransitionExist){
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    aut.addTransition(0,'a',1);
    EXPECT_TRUE(aut.hasTransition(0,'a', 1));
    EXPECT_EQ(1u, aut.getAlphabetSize());
    EXPECT_EQ(1u, aut.countTransitions());

}

TEST(AutomatonTest, addTransitionTestStateDontExist){
    fa::Automaton aut;
    EXPECT_DEATH({aut.addTransition(123,'t', 456);}, "");
    EXPECT_EQ(0u, aut.countTransitions());

}

TEST(AutomatonTest, addTransitionTestState2DontExist){
    fa::Automaton aut;
    aut.addState(0);
    EXPECT_DEATH({aut.addTransition(0,'t', 1);}, "");
    EXPECT_EQ(0u, aut.getAlphabetSize());
}

TEST(AutomatonTest, addTransitionTestState1DontExist){
    fa::Automaton aut;
    aut.addState(1);
    EXPECT_DEATH({aut.addTransition(0,'t', 1);}, "");
    EXPECT_EQ(0u, aut.getAlphabetSize());
}


TEST(AutomatonTest, addTransitionTestStateExistTransitionDontExist){
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_FALSE(aut.hasTransition(0,'a', 1));
    EXPECT_EQ(0u, aut.countTransitions());

}

//removeTransition


TEST(AutomatonTest, removeTransitionTestStateExistTransitionExist){
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    aut.addTransition(0,'a',1);
    aut.removeTransition(0,'a', 1);
    EXPECT_FALSE(aut.hasTransition(0,'a', 1));
    EXPECT_EQ(1u, aut.getAlphabetSize());
    EXPECT_EQ(0u, aut.countTransitions());
}

TEST(AutomatonTest, removeTransitionTestStateDontExist){
    fa::Automaton aut;
    EXPECT_DEATH({aut.removeTransition(123,'t', 456);}, "");
}

TEST(AutomatonTest, removeTransitionTestState2DontExist){
    fa::Automaton aut;
    aut.addState(1);
    aut.addState(0);
    aut.addTransition(0,'a',1);
    EXPECT_DEATH({aut.removeTransition(0,'t', 3);}, "");
}

TEST(AutomatonTest, removeTransitionTestState1DontExist){
    fa::Automaton aut;
    aut.addState(1);
    aut.addState(0);
    aut.addTransition(0,'a',1);
    EXPECT_DEATH({aut.removeTransition(3,'t', 1);}, "");
}


TEST(AutomatonTest, removeTransitionTestStateExistTransitionDontExist){
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_DEATH(aut.removeTransition(0,'a', 1), "");
}

/**
 * Print an automaton.
 */
TEST_F(AutomatonTestFixture, prettyPrint){
    automatonNotCompleteNotDeterministic.prettyPrint(std::cout);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
