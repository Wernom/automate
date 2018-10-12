#ifndef AUTOMATE_AUTOMATON_H
#define AUTOMATE_AUTOMATON_H

#include <vector>
#include <map>
#include <set>
#include <iostream>

//TODO: faire test afficher automate.
//TODO: cf operator.

namespace fa {
    /**
     * Describe the state configuration
     */
    class StateConfiguration {
        bool initial;
        bool final;
        int state;

    public:

        bool isInitial() const;

        void setInitial(bool is_initial);

        bool isFinal() const;

        void setFinal(bool is_final);

        int getState() const;

        void setState(int state);

        explicit StateConfiguration(int state);

    };


    /**
     * Comparator for StateConfiguration class.
     */
    struct StateConfigurationComparator { //public by default
        bool operator()(const StateConfiguration &state1, const StateConfiguration &state2) const;
    };

    /**
     * Describe a transition.
     */
    class Transition {
        StateConfiguration *stateFrom;
        char transition_name;
        StateConfiguration *stateTo;

    public:
        Transition(StateConfiguration *stateFrom, char transition_name, StateConfiguration *stateTo);

        StateConfiguration *getFrom() const;

        StateConfiguration *getTo() const;

        char getTransition_name() const;

    };

    /**
     * Comparator for Transation class
     */
    struct TransitionComparator {
        bool operator()(const Transition &transition1, const Transition &transition2) const;
    };

    /**
     * Describe an automaton
     */
    class Automaton {
        //TODO: implement collection set<*StateConfiguration> final and initial.
        std::set<char> alphabet;
        std::map<int, StateConfiguration> stateCollection; // int the state, StateConfiguration the configuration of the state.
        std::set<Transition, fa::TransitionComparator> transitionCollection; //int -> start node, state -> the transitionCollection state value   We use map for a transitionCollection we can access, add, an element in O(log n)

    public:
        /**
         * Add a state  to the  automaton.
         *
         * The  state  must  not be  already  present. By default ,
         * a newly  added  state  is not  initial  and  not  final.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         *
         * @param state The state to add in the automaton
         */
        void addState(int state);

        /**
         * Remove a state  from  the  automaton.
         *
         * The  state  must be  present. The  transitions
         * involving  the  state  are  also  removed.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         *
         * @param state The state to remove of the automaton
         */
        void removeState(int state);

        /**
         * Tell if the  state  is  present  in the  automaton.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         *
         * @param state The state to check in the automaton
         */
        bool hasState(int state) const;

        /**
         * Tell if the  state are present in the automaton.
         *
         * @param from One of the state to check in the automaton
         * @param to One of the state to check in the automaton
         * @return true if they are in the automaton false if not.
         */
        bool hasCoupleState(int from, int to) const;

        /**
         * Compute  the  number  of  states.
         *
         * Expected  complexity: O(1)
         *
         * @return The number of states in the automaton
         */
        std::size_t countStates() const;


        /**
         * Set the  state  initial.
         *
         * The  state  must be  present.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         */
        void setStateInitial(int state);

        /**
         * Tell if the  state  is  initial.
         *
         * The  state  must be  present.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         */
        bool isStateInitial(int state) const;

        /**
         * Set the  state  final.
         *
         * The  state  must be  present.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         */
        void setStateFinal(int state);

        /**
         * Tell if the  state  is final.
         *
         * The  state  must be  present.
         *
         * Expected  complexity: O(log n)
         * Max  allowed  complexity: O(n)
         */
        bool isStateFinal(int state) const;

        /**
         * Add a transition
         *
         * The two  states  must be  present. The  character  is
         * added  to the  alphabet.
         *
         * Expected  complexity: O(log n + log m)
         * Max  allowed  complexity: O(n + m)
         */
        void addTransition(int from, char alpha, int to);

        /**
         * Add a charactere to the alphabet.
         *
         * @param alpha charactere to add in the alphabet.
         */
        void addToAlphabet(char alpha);

        /**
         * Remove a transition
         *
         * The  transition  must be  present. The  character  is
         * not  deleted  from  the  alphabet , even if it is the
         * last  transition  with  this  letter.
         *
         * Expected  complexity: O(log n + log m)
         * Max  allowed  complexity: O(n + m)
         */
        void removeTransition(int from, char alpha, int to);

        /**
         * Tell if a transition  is  present.
         *
         * The two  states  must be  present.
         *
         * Expected  complexity: O(log n + log m)
         * Max  allowed  complexity: O(n + m)
         */
        bool hasTransition(int from, char alpha, int to) const;

        /**
         * Compute  the  number  of  transitions.
         *
         * Expected  complexity: O(n + m)
         */
        std::size_t countTransitions() const;

        /**
         * Get the  size of the  alphabet
         *
         * Expected  complexity: O(1)
         * Max  allowed  complexity: O(m)
         */
        std::size_t getAlphabetSize() const;


        /**
         * Print  the  automaton  in a friendly  way
         */
        void prettyPrint(std::ostream &os) const;
    };
}


#endif //AUTOMATE_AUTOMATON_H
