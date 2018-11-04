#include <iostream>
#include <iomanip>
#include <fstream>
#include "gtest/gtest.h"
#include "Automaton.h"

#define DOT_PRINT(automaton, fileName, nameOfStream)\
    std::ofstream nameOfStream;\
    nameOfStream.open("../dot/" + fileName +".dot");\
    if (!nameOfStream) {\
    std::cout << "error";\
    exit(EXIT_FAILURE);\
    }\
    automaton.dotPrint(nameOfStream);\
    nameOfStream.close();

class AutomatonTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        intitAutomatonNotCompleteNotDeterministic();
        intitAutomatonNotCompleteDeterministic();
        intitAutomatonCompleteNotDeterministic();
        intitAutomatonCompleteDeterministic();
        initAutomaton();
        initAutomatonInutile();
        initAutomatonCoAccessible();
        initAutomatonEmptyInutileIsInitial();
        initAutomatonEmpty();
        initAutomatonEmptyNoFinal();
        initAutomatonEmptyNoInitial();
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

    void initAutomaton() {
        automaton.addState(0);
        automaton.addState(2);
        automaton.addState(123);
        automaton.addState(3);
        automaton.addState(8);
        automaton.addState(5);
        automaton.addState(7);
        automaton.addState(42);
        automaton.addState(6);
        automaton.setStateInitial(0);
        automaton.setStateInitial(42);
        automaton.setStateInitial(8);
        automaton.setStateFinal(42);
        automaton.setStateFinal(3);
        automaton.setStateFinal(7);
        automaton.addTransition(0, 'o', 2);
        automaton.addTransition(0, 'a', 0);
        automaton.addTransition(0, 'z', 2);
        automaton.addTransition(0, 'u', 8);
        automaton.addTransition(0, (char) 122, 8);
        automaton.addTransition(2, 'a', 123);
        automaton.addTransition(2, 'a', 5);
        automaton.addTransition(3, '7', 2);
        automaton.addTransition(8, 'v', 2);
        automaton.addTransition(5, '0', 0);
        automaton.addTransition(5, '0', 7);
        automaton.addTransition(7, 'j', 42);
        automaton.addTransition(3, 'o', 2);
        automaton.addTransition(3, 'j', 7);
    }

    void initAutomatonInutile() {
        automatonInutile.addState(1);
        automatonInutile.setStateInitial(1);
        automatonInutile.addState(2);
        automatonInutile.setStateFinal(2);
        automatonInutile.addState(3);
        automatonInutile.addTransition(1, 'a', 2);
        automatonInutile.addTransition(2, 'a', 1);
    }

    void initAutomatonCoAccessible() {
        automatonCoAccessible.addState(1);
        automatonCoAccessible.setStateInitial(1);
        automatonCoAccessible.addState(2);
        automatonCoAccessible.setStateFinal(2);
        automatonCoAccessible.addState(3);
        automatonCoAccessible.addTransition(1, 'a', 2);
        automatonCoAccessible.addTransition(1, 'b', 2);
        automatonCoAccessible.addTransition(2, 'a', 1);
        automatonCoAccessible.addTransition(2, 'b', 1);
        automatonCoAccessible.addTransition(3, 'a', 1);
        automatonCoAccessible.addTransition(3, 'a', 2);
    }

    void initAutomatonEmptyInutileIsInitial() {
        automatonEmptyInutileIsInitial.addState(1);
        automatonEmptyInutileIsInitial.addState(2);
        automatonEmptyInutileIsInitial.setStateFinal(2);
        automatonEmptyInutileIsInitial.addState(3);
        automatonEmptyInutileIsInitial.setStateInitial(3);
        automatonEmptyInutileIsInitial.addTransition(1, 'a', 2);
        automatonEmptyInutileIsInitial.addTransition(2, 'a', 1);
    }

    void initAutomatonEmpty() {
        automatonEmpty.addState(1);
        automatonEmpty.setStateInitial(1);
        automatonEmpty.addState(2);
        automatonEmpty.setStateFinal(2);
        automatonEmpty.addState(3);
        automatonEmpty.addTransition(3, 'a', 2);
        automatonEmpty.addTransition(3, 'a', 1);
    }

    void initAutomatonEmptyNoInitial() {
        automatonEmptyNoInitial.addState(1);
        automatonEmptyNoInitial.addState(2);
        automatonEmptyNoInitial.setStateFinal(2);
    }

    void initAutomatonEmptyNoFinal() {
        automatonEmptyNoFinal.addState(1);
        automatonEmptyNoFinal.setStateInitial(1);
        automatonEmptyNoFinal.addState(2);
    }

    fa::Automaton automatonNotCompleteNotDeterministic;
    fa::Automaton automatonNotCompleteDeterministic;
    fa::Automaton automatonCompleteNotDeterministic;
    fa::Automaton automatonCompleteDeterministic;
    fa::Automaton automatonInutile;
    fa::Automaton automatonCoAccessible;
    fa::Automaton automaton;
    fa::Automaton automatonEmptyInutileIsInitial;//TODO: dot print
    fa::Automaton automatonEmpty;//TODO: dot print
    fa::Automaton automatonEmptyNoInitial;//TODO: dot print
    fa::Automaton automatonEmptyNoFinal;//TODO: dot print

};


TEST(AutomatonTest, Empty) {
    fa::Automaton fa;

    EXPECT_EQ(fa.countStates(), 0u);
    EXPECT_EQ(fa.countTransitions(), 0u);
}


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

TEST(AutomatonTest, addAlphabetTestNotPrintable) {
    fa::Automaton aut;
    aut.addState(0);
    aut.addState(1);
    EXPECT_DEATH(aut.addTransition(0, (char) 12, 1), "");
}

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
    automaton.prettyPrint(std::cout);
    std::ofstream ofstream;
    ofstream.open("../dot/automate.dot");
    if (!ofstream) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automaton.dotPrint(ofstream);
    ofstream.close();

    std::ofstream ofstream1;
    ofstream1.open("../dot/automatonNotCompleteNotDeterministic.dot");
    if (!ofstream1) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonNotCompleteNotDeterministic.dotPrint(ofstream1);
    ofstream1.close();

    std::ofstream ofstream2;
    ofstream2.open("../dot/automatonNotCompleteDeterministic.dot");
    if (!ofstream2) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonNotCompleteDeterministic.dotPrint(ofstream2);
    ofstream2.close();

    std::ofstream ofstream3;
    ofstream3.open("../dot/automatonCompleteNotDeterministic.dot");
    if (!ofstream3) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonCompleteNotDeterministic.dotPrint(ofstream3);
    ofstream3.close();

    std::ofstream ofstream5;
    ofstream5.open("../dot/automatonInutile.dot");
    if (!ofstream5) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonInutile.dotPrint(ofstream5);
    ofstream5.close();

    std::ofstream ofstream6;
    ofstream6.open("../dot/automatonCompleteDeterministic.dot");
    if (!ofstream6) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonCompleteDeterministic.dotPrint(ofstream6);
    ofstream6.close();

    std::ofstream ofstream7;
    ofstream7.open("../dot/automatonCoAccessible.dot");
    if (!ofstream7) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonCoAccessible.dotPrint(ofstream7);
    ofstream7.close();

    DOT_PRINT(automatonEmptyInutileIsInitial, std::string("automatonEmptyInutileIsInitial"), ofstream8);
    DOT_PRINT(automatonEmpty, std::string("automatonEmpty"), ofstream9);
    DOT_PRINT(automatonEmptyNoInitial, std::string("automatonEmptyNoInitial"), ofstream10);
    DOT_PRINT(automatonEmptyNoFinal, std::string("automatonEmptyNoFinal"), ofstream11);

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

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonCompleteNotDeterministic) {
    EXPECT_FALSE(automatonCompleteNotDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTcestAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTcestAutomaton) {
    EXPECT_FALSE(automaton.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonInutile) {
    EXPECT_TRUE(automatonInutile.isDeterministic());
}

TEST_F(AutomatonTestFixture, isDeterministicTestAutomatonCoAccessible) {
    EXPECT_FALSE(automatonCoAccessible.isDeterministic());
}

//Complete

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonCompleteDeterministic) {
    EXPECT_TRUE(automatonCompleteDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonNotCompleteDeterministic) {
    EXPECT_FALSE(automatonNotCompleteDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonCompleteNotDeterministic) {
    EXPECT_TRUE(automatonCompleteNotDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomaton) {
    EXPECT_FALSE(automaton.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonInutile) {
    EXPECT_FALSE(automatonInutile.isComplete());
}

TEST_F(AutomatonTestFixture, isCompleteTestAutomatonCoAccessible) {
    EXPECT_FALSE(automatonCoAccessible.isComplete());
}
//make Complete

TEST_F(AutomatonTestFixture, makeCompleteTestNotComplete) {
    size_t size = automatonNotCompleteNotDeterministic.getAlphabetSize();
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isComplete());

    automatonNotCompleteNotDeterministic.makeComplete();
    std::ofstream ofstream1;
    ofstream1.open("../dot/automatonNotCompleteNotDeterministic1.dot");
    if (!ofstream1) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonNotCompleteNotDeterministic.dotPrint(ofstream1);
    ofstream1.close();
    EXPECT_EQ(size, automatonNotCompleteNotDeterministic.getAlphabetSize());
    EXPECT_TRUE(automatonNotCompleteNotDeterministic.isComplete());
}

TEST_F(AutomatonTestFixture, makeCompleteTestAutomaton) {
    size_t size = automaton.getAlphabetSize();
    EXPECT_FALSE(automaton.isComplete());

    automaton.makeComplete();
    std::ofstream ofstream1;
    ofstream1.open("../dot/automaton1.dot");
    if (!ofstream1) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automaton.dotPrint(ofstream1);
    ofstream1.close();
    EXPECT_EQ(size, automaton.getAlphabetSize());
    EXPECT_TRUE(automaton.isComplete());
}

TEST_F(AutomatonTestFixture, makeCompleteTestAlphabetSame) {
    size_t i = automatonNotCompleteNotDeterministic.getAlphabetSize();
    automatonNotCompleteNotDeterministic.makeComplete();
    EXPECT_EQ(i, automatonNotCompleteNotDeterministic.getAlphabetSize());
}

TEST_F(AutomatonTestFixture, makeCompleteTestComplete) {
    EXPECT_TRUE(automatonCompleteNotDeterministic.isComplete());
    automatonNotCompleteNotDeterministic.makeComplete();
    EXPECT_TRUE(automatonCompleteNotDeterministic.isComplete());
}

//make Complement

TEST_F(AutomatonTestFixture, makeComplement) {
    automatonInutile.makeComplement();
    std::ofstream ofstream;
    ofstream.open("../dot/automatonInutileComplment.dot");
    if (!ofstream) {
        std::cout << "error";
        exit(EXIT_FAILURE);
    }
    automatonInutile.dotPrint(ofstream);
    ofstream.close();
    EXPECT_TRUE(automatonInutile.isStateFinal(1));
    EXPECT_FALSE(automatonInutile.isStateFinal(2));
    EXPECT_TRUE(automatonInutile.isStateFinal(3));
}

//******************************************************
//              Part 3
//******************************************************

TEST_F(AutomatonTestFixture, toDELELTE) {
    for (const auto &it : automaton.getTransitionCollection()) {
        std::cout << it.getFrom()->getState() << '\t' << it.getTransition_name() << '\t' << it.getTo()->getState()
                  << std::endl;
    }


    std::cout << &automaton.getStateCollection().begin()->second.getItFirstTransition() << std::endl;

}

//isLanguageEmpty

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomate) {
    EXPECT_FALSE(automaton.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonCoAccessible) {
    EXPECT_FALSE(automatonCoAccessible.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonCompleteDeterministic) {
    EXPECT_FALSE(automatonCompleteDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonCompleteNotDeterministic) {
    EXPECT_FALSE(automatonCompleteNotDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonNotCompleteNotDeterministic) {
    EXPECT_FALSE(automatonNotCompleteNotDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmpty) {
    EXPECT_TRUE(automatonEmpty.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmptyInutileIsInitial) {
    EXPECT_TRUE(automatonEmptyInutileIsInitial.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmptyNoFinal) {
    EXPECT_TRUE(automatonEmptyNoFinal.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonInutile) {
    EXPECT_FALSE(automatonInutile.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonNotCompleteDeterministic) {
    EXPECT_FALSE(automatonNotCompleteDeterministic.isLanguageEmpty());
}

TEST_F(AutomatonTestFixture, isLanguageEmptyAutomatonEmptyNoInitial) {
    EXPECT_FALSE(automatonEmptyNoInitial.isLanguageEmpty());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
