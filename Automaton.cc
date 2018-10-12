#include "Automaton.h"


//State Configuration's function
fa::StateConfiguration::StateConfiguration(int state) : state(state) {
    this->state = state;
    this->initial = false;
    this->final = false;
}

bool fa::StateConfiguration::isInitial() const {
    return initial;
}

void fa::StateConfiguration::setInitial(bool is_initial) {
    StateConfiguration::initial = is_initial;
}

bool fa::StateConfiguration::isFinal() const {
    return final;
}

void fa::StateConfiguration::setFinal(bool is_final) {
    StateConfiguration::final = is_final;
}

int fa::StateConfiguration::getState() const {
    return state;
}

void fa::StateConfiguration::setState(int state) {
    StateConfiguration::state = state;
}

//Transition's function

fa::Transition::Transition(fa::StateConfiguration *stateFrom, char transition_name, fa::StateConfiguration *stateTo)
        : stateFrom(stateFrom),
          transition_name(transition_name),
          stateTo(stateTo) {}


fa::StateConfiguration *fa::Transition::getFrom() const {
    return stateFrom;
}

fa::StateConfiguration *fa::Transition::getTo() const {
    return stateTo;
}

char fa::Transition::getTransition_name() const {
    return transition_name;
}

//Automaton's function

void fa::Automaton::addState(int state) {
    if (hasState(state)) {
        std::cerr << "This state is already in the Automaton" << std::endl;
    } else {
        fa::StateConfiguration s(state);
        this->stateCollection.insert(std::pair<int, fa::StateConfiguration>(state, s));
    }
}

void fa::Automaton::removeState(int state) {
    this->stateCollection.erase(state);
}

bool fa::Automaton::hasState(int state) const {
    return this->stateCollection.count(state) == 1;
}

bool fa::Automaton::hasCoupleState(int from, int to) const {
    return hasState(from) && hasState(to);
}


std::size_t fa::Automaton::countStates() const {
    return this->stateCollection.size();
}

void fa::Automaton::setStateInitial(int state) {
    if (hasState(state)) {
        this->stateCollection.find(state)->second.setInitial(true);
    } else {
        std::cerr << "Error: the state doesn't exist." << std::endl;
    }
}

bool fa::Automaton::isStateInitial(int state) const {
    if (hasState(state)) {
        return this->stateCollection.find(state)->second.isInitial();
    }

    std::cerr << "Error: the state doesn't exist." << std::endl;
    exit(1);
}

void fa::Automaton::setStateFinal(int state) {
    if (hasState(state)) {
        this->stateCollection.find(state)->second.setFinal(true);
    } else {
        std::cerr << "Error: the state doesn't exist." << std::endl;
    }
}

bool fa::Automaton::isStateFinal(int state) const {
    if (hasState(state)) {
        return this->stateCollection.find(state)->second.isFinal();
    }

    std::cerr << "Error: the state doesn't exist." << std::endl;
    exit(1);
}

bool fa::Automaton::hasTransition(int from, char alpha, int to) const {
    if (!hasCoupleState(from, to)) {
        std::cerr << "Error: the state " << from << " and/or the state " << to << " are not in the automaton."
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    fa::StateConfiguration cFrom(from);
    fa::StateConfiguration cTo(to);


    auto it = this->transitionCollection.find(Transition(&cFrom, alpha, &cTo));
    return it != this->transitionCollection.end();
    }

void fa::Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to))
        std::cout << "Warning: the transition {stateFrom=" << from << "; alpha=" << alpha << "; stateTo=" << to
                  << "} already exist." << std::endl;

    addToAlphabet(alpha);
    fa::Transition data(&stateCollection.find(from)->second, alpha, &stateCollection.find(to)->second);
    transitionCollection.insert(data);
}


void fa::Automaton::addToAlphabet(char alpha) {
    alphabet.insert(alpha);
}

void fa::Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasTransition(from, alpha, to))
        std::cout << "Error: the transition {stateFrom=" << from << "; alpha=" << alpha << "; stateTo=" << to
                  << "} doesn't exist." << std::endl;

    fa::Transition data(&stateCollection.find(from)->second, alpha, &stateCollection.find(to)->second);

    transitionCollection.erase(data);
}

std::size_t fa::Automaton::countTransitions() const {
    return transitionCollection.size();
}

std::size_t fa::Automaton::getAlphabetSize() const {
    return alphabet.size();
}

void fa::Automaton::prettyPrint(std::ostream &os) const {
    std::set<int> initialState;
    std::set<int> finalState;
    std::map<int, std::map<char, std::set<int>>> transition;

    for (auto data : this->transitionCollection) {

        fa::StateConfiguration *to = data.getTo();
        fa::StateConfiguration *from = data.getFrom();

        if (to->isInitial())
            initialState.insert(to->getState());

        if (from->isInitial())
            initialState.insert(from->getState());

        if (to->isFinal())
            finalState.insert(to->getState());

        if (from->isFinal())
            finalState.insert(from->getState());

        transition[from->getState()][data.getTransition_name()].insert(to->getState());

    }

    os << "Initial states:\n\t";
    for (auto data : initialState) {
        os << data << ' ';
    }

    os << "\n\nFinal states: " << std::endl << "\t";
    for (auto data : finalState){
        os << data << ' ';
    }

    os << "\n\nTransitions:";
    auto it1 = transition.begin();
    while(it1 != transition.end()){
        os << "\n\tFor state " << it1->first;

        auto it2 = it1->second.begin();
        while(it2 != it1->second.end()){
            os << "\n\t\tFor letter " << it2->first << ":  ";

            for(auto data : it2->second){
                os << data << "  ";
            }
            ++it2;
        }
        ++it1;
    }
}

//******************************************************************
//                          Comparator
//******************************************************************


bool fa::StateConfigurationComparator::operator()(const fa::StateConfiguration &state1,
                                                  const fa::StateConfiguration &state2) const {

    return state1.getState() < state2.getState();

}

bool fa::TransitionComparator::operator()(const fa::Transition &transition1, const fa::Transition &transition2) const {
    if (transition1.getFrom()->getState() == transition2.getFrom()->getState()) {
        if (transition1.getTransition_name() == transition2.getTransition_name())
            return transition1.getTo()->getState() < transition2.getTo()->getState();
        return transition1.getTransition_name() < transition2.getTransition_name();
    }
    return transition1.getFrom()->getState() < transition2.getFrom()->getState();
}
