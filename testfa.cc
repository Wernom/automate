#include <iostream>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
#include "Automaton.h"

class AutomatonTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        intitAutomatonNotCompleteNotDeterministic();
        intitAutomatonNotCompleteDeterministic();
        intitAutomatonCompleteNotDeterministic();
        intitAutomatonCompleteDeterministic();
    }

    void intitAutomatonNotCompleteNotDeterministic() {
        automatonNotCompleteNotDeterministic.addState(0);
        automatonNotCompleteNotDeterministic.setStateInitial(0);
        automatonNotCompleteNotDeterministic.addState(1);
        automatonNotCompleteNotDeterministic.setStateFinal(1);
        automatonNotCompleteNotDeterministic.setStateInitial(1);
        automatonNotCompleteNotDeterministic.addState(3);
        automatonNotCompleteNotDeterministic.addState(2);
        automatonNotCompleteNotDeterministic.addState(4);
        automatonNotCompleteNotDeterministic.setStateFinal(4);
        automatonNotCompleteNotDeterministic.addTransition(0, 'a', 1);
        automatonNotCompleteNotDeterministic.addTransition(0, 'a', 2);
        automatonNotCompleteNotDeterministic.addTransition(0, 'a', 3);
        automatonNotCompleteNotDeterministic.addTransition(1, 'b', 3);
        automatonNotCompleteNotDeterministic.addTransition(2, 'a', 3);
        automatonNotCompleteNotDeterministic.addTransition(2, 'b', 4);
        automatonNotCompleteNotDeterministic.addTransition(3, 'a', 3);
        automatonNotCompleteNotDeterministic.addTransition(3, 'b', 4);
        automatonNotCompleteNotDeterministic.addTransition(4, 'a', 4);
    }

    void intitAutomatonNotCompleteDeterministic() {
        automatonNotCompleteDeterministic.addState(0);
        automatonNotCompleteDeterministic.setStateInitial(0);
        automatonNotCompleteDeterministic.addState(1);
        automatonNotCompleteDeterministic.addState(2);
        automatonNotCompleteDeterministic.setStateFinal(2);
        automatonNotCompleteDeterministic.addTransition(0, 'a', 1);
        automatonNotCompleteDeterministic.addTransition(1, 'b', 2);
        automatonNotCompleteDeterministic.addTransition(2, 'a', 2);
        automatonNotCompleteDeterministic.addTransition(2, 'b', 2);
    }

    void intitAutomatonCompleteNotDeterministic() {
        automatonCompleteNotDeterministic.addState(0);
        automatonCompleteNotDeterministic.setStateInitial(0);
        automatonCompleteNotDeterministic.addState(1);
        automatonCompleteNotDeterministic.setStateFinal(1);
        automatonCompleteNotDeterministic.addTransition(0, 'a', 1);
        automatonCompleteNotDeterministic.addTransition(0, 'b', 1);
        automatonCompleteNotDeterministic.addTransition(1, 'a', 0);
        automatonCompleteNotDeterministic.addTransition(1, 'a', 1);
        automatonCompleteNotDeterministic.addTransition(1, 'b', 1);
    }

    void intitAutomatonCompleteDeterministic() {
        automatonCompleteDeterministic.addState(0);
        automatonCompleteDeterministic.setStateInitial(0);
        automatonCompleteDeterministic.addState(2);
        automatonCompleteDeterministic.setStateFinal(2);
        automatonCompleteDeterministic.addTransition(0, 'a', 2);
        automatonCompleteDeterministic.addTransition(0, 'b', 2);
        automatonCompleteDeterministic.addTransition(2, 'a', 0);
        automatonCompleteDeterministic.addTransition(2, 'b', 2);
    }

    fa::Automaton automatonNotCompleteNotDeterministic;
    fa::Automaton automatonNotCompleteDeterministic;
    fa::Automaton automatonCompleteNotDeterministic;
    fa::Automaton automatonCompleteDeterministic;

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
TEST_F(AutomatonTestFixture, addState) {
    EXPECT_EQ(automatonNotCompleteNotDeterministic.countStates(), 5u);
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(0));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(1));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(2));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(3));
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.hasState(4));
}

//removeState
TEST_F(AutomatonTestFixture, removeState) {
    automatonNotCompleteNotDeterministic.removeState(0);
    EXPECT_EQ(automatonNotCompleteNotDeterministic.countStates(), 4u);
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.hasState(0));
}

//Initial/Final
TEST(AutomatonTest, setInitialTestStateDontExist) {
    fa::Automaton aut;
    ASSERT_DEATH({ aut.setStateInitial(123); }, "");
}

TEST(AutomatonTest, setInitialTestStateExistIsInitial) {
    fa::Automaton aut;
    aut.addState(0);
    aut.setStateInitial(0);
    ASSERT_TRUE(aut.isStateInitial(0));
}

TEST(AutomatonTest, setInitialTestStateExistNotInitial) {
    fa::Automaton aut;
    aut.addState(0);
    ASSERT_FALSE(aut.isStateInitial(0));
}


TEST(AutomatonTest, setFinalTestDontExist) {
    fa::Automaton aut;
    ASSERT_DEATH({ aut.setStateInitial(123); }, "");
}

TEST(AutomatonTest, setFinalTestStateExistIsInitial) {
    fa::Automaton aut;
    aut.addState(0);
    aut.setStateFinal(0);
    ASSERT_TRUE(aut.isStateFinal(0));
}

TEST(AutomatonTest, setFinalTestStateExistNotFinal) {
    fa::Automaton aut;
    aut.addState(0);
    ASSERT_FALSE(aut.isStateFinal(0));
}

//addTransition

TEST(AutomatonTest, addTransitionTestStateExistTransitionExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    aut.addTransition(0, 'a', 1);
    EXPECT_TRUE(aut.hasTransition(0, 'a', 1));
    EXPECT_EQ(1u, aut.getAlphabetSize());
    EXPECT_EQ(1u, aut.countTransitions());

}

TEST(AutomatonTest, addTransitionTestStateDontExist) {
    fa::Automaton aut;
    EXPECT_DEATH({ aut.addTransition(123, 't', 456); }, "");
    EXPECT_EQ(0u, aut.countTransitions());

}

TEST(AutomatonTest, addTransitionTestState2DontExist) {
    fa::Automaton aut;
    aut.addState(0);
    EXPECT_DEATH({ aut.addTransition(0, 't', 1); }, "");
    EXPECT_EQ(0u, aut.getAlphabetSize());
}

TEST(AutomatonTest, addTransitionTestState1DontExist) {
    fa::Automaton aut;
    aut.addState(1);
    EXPECT_DEATH({ aut.addTransition(0, 't', 1); }, "");
    EXPECT_EQ(0u, aut.getAlphabetSize());
}


TEST(AutomatonTest, addTransitionTestStateExistTransitionDontExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_FALSE(aut.hasTransition(0, 'a', 1));
    EXPECT_EQ(0u, aut.countTransitions());

}

//removeTransition


TEST(AutomatonTest, removeTransitionTestStateExistTransitionExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    aut.addTransition(0, 'a', 1);
    aut.removeTransition(0, 'a', 1);
    EXPECT_FALSE(aut.hasTransition(0, 'a', 1));
    EXPECT_EQ(1u, aut.getAlphabetSize());
    EXPECT_EQ(0u, aut.countTransitions());
}

TEST(AutomatonTest, removeTransitionTestStateDontExist) {
    fa::Automaton aut;
    EXPECT_DEATH({ aut.removeTransition(123, 't', 456); }, "");
}

TEST(AutomatonTest, removeTransitionTestState2DontExist) {
    fa::Automaton aut;
    aut.addState(1);
    aut.addState(0);
    aut.addTransition(0, 'a', 1);
    EXPECT_DEATH({ aut.removeTransition(0, 't', 3); }, "");
}

TEST(AutomatonTest, removeTransitionTestState1DontExist) {
    fa::Automaton aut;
    aut.addState(1);
    aut.addState(0);
    aut.addTransition(0, 'a', 1);
    EXPECT_DEATH({ aut.removeTransition(3, 't', 1); }, "");
}


TEST(AutomatonTest, removeTransitionTestStateExistTransitionDontExist) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_DEATH(aut.removeTransition(0, 'a', 1), "");
}

/**
 * Print an automaton.
 */
TEST_F(AutomatonTestFixture, prettyPrint) {
    automatonNotCompleteNotDeterministic.prettyPrint(std::cout);
    std::ofstream ofstream;
    ofstream.open("../dot/automate.dot");
    if (!ofstream) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonCompleteNotDeterministic.dotPrint(ofstream);
    ofstream.close();
}

//******************************************************
//              Part 2
//******************************************************

//Deterministic

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonCompleteDeterministic) {
    EXPECT_TRUE(automatonCompleteDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonNotCompleteDeterministic) {
    EXPECT_TRUE(automatonNotCompleteDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministiTestAutomatonCompleteNotDeterministic) {
    EXPECT_FALSE(automatonCompleteNotDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministiTestAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isDeterministic());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
