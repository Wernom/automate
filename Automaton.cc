#include "Automaton.h"


//State Configuration's function
fa::StateConfiguration::StateConfiguration(int state) : state(state) {
    this->state = state;
    this->initial = false;
    this->final = false;
}

bool fa::StateConfiguration::isInitial() const {
    return this->initial;
}

void fa::StateConfiguration::setInitial(bool is_initial) {
    StateConfiguration::initial = is_initial;
}

bool fa::StateConfiguration::isFinal() const {
    return this->final;
}

void fa::StateConfiguration::setFinal(bool is_final) {
    StateConfiguration::final = is_final;
}

int fa::StateConfiguration::getState() const {
    return this->state;
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
        exit(EXIT_FAILURE);
    }
}

bool fa::Automaton::isStateInitial(int state) const {
    if (hasState(state)) {
        return this->stateCollection.find(state)->second.isInitial();
    }
    std::cerr << "Error: the state doesn't exist." << std::endl;
    exit(EXIT_FAILURE);
}

void fa::Automaton::setStateFinal(int state) {
    if (hasState(state)) {
        this->stateCollection.find(state)->second.setFinal(true);
    } else {
        std::cerr << "Error: the state doesn't exist." << std::endl;
        exit(EXIT_FAILURE);
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
    if (hasTransition(from, alpha, to)) {
        std::cout << "Warning: the transition {stateFrom=" << from << "; alpha=" << alpha << "; stateTo=" << to
                  << "} already exist." << std::endl;
        exit(EXIT_FAILURE);
    }

    addToAlphabet(alpha);
    fa::Transition data(&stateCollection.find(from)->second, alpha, &stateCollection.find(to)->second);
    transitionCollection.insert(data);
}


void fa::Automaton::addToAlphabet(char alpha) {
    if (!((alpha >= 48 && alpha <= 57) || (alpha >= 65 && alpha <= 90) || (alpha >= 97 && alpha <= 122))) {
        std::cerr << "Error: character ASCII: \"" << (int) alpha << "\" is not supported";
        exit(EXIT_FAILURE);
    }
    alphabet.insert(alpha);
}

void fa::Automaton::removeTransition(int from, char alpha, int to) {
    if (!hasTransition(from, alpha, to)) {
        std::cout << "Error: the transition {stateFrom=" << from << "; alpha=" << alpha << "; stateTo=" << to
                  << "} doesn't exist." << std::endl;
        exit(EXIT_FAILURE);
    }

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
    for (auto data : finalState) {
        os << data << ' ';
    }

    std::map<int, StateConfiguration> cpy(this->stateCollection);
    os << "\n\nTransitions:";
    auto it1 = transition.begin();
    while (it1 != transition.end()) {
        os << "\n\tFor state " << it1->first << ':';
        cpy.erase(it1->first);

        auto it2 = it1->second.begin();
        while (it2 != it1->second.end()) {
            os << "\n\t\tFor letter " << it2->first << ":  ";

            for (auto data : it2->second) {
                os << data << "  ";
            }
            ++it2;
        }
        ++it1;
    }
    for (auto data: cpy) {
        os << "\n\tFor state " << data.first << ':';
    }

    os << std::endl;
}

void fa::Automaton::dotPrint(std::ostream &os) const {
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

    os << "digraph automaton{\n\trankdir=LR;\n\tnode[shape = point, color=white, fontcolor=white];";

    for (auto data : initialState) {
        os << " start" << data << ';';
    }


    os << "\n\tnode [shape = doublecircle, color=black, fontcolor=black];";
    for (auto data : finalState) {
        os << ' ' << data << ';';
    }

    os << std::endl << "\tnode [shape = circle];\n";

    std::map<int, StateConfiguration> cpy(this->stateCollection);
    auto it1 = transition.begin();
    std::set<int> exist;
    while (it1 != transition.end()) {
        auto it2 = it1->second.begin();
        cpy.erase(it1->first);
        while (it2 != it1->second.end()) {
            for (auto data : it2->second) {
                os << '\t';
                if (initialState.find(it1->first) != initialState.end() && exist.find(it1->first) == exist.end()) {
                    os << "start" << it1->first << "->" << it1->first << ';' << std::endl << '\t';
                    exist.insert(it1->first);
                }
                os << it1->first << "->";
                os << data << "  ";
                os << "[ label = " << it2->first << " ];" << std::endl;
            }
            ++it2;
        }
        ++it1;
    }

    for (auto data: cpy) {
        if(!data.second.isFinal()){
            os << '\t';
            os << data.first << ';' << std::endl;
        }
    }


    for (auto data: cpy) {
        os << '\t';
        if (data.second.isFinal())
            os << "node [shape = doublecircle, color=black, fontcolor=black];" << data.first <<';' << std::endl;

        if (data.second.isInitial()) {
            os << "node[shape = point, color=white, fontcolor=white]; start" << data.first << ';' << std::endl;
            os << "\tstart" << data.first << "->" << data.first << ';';
        }
    }

    os << '}';
}

const std::set<fa::Transition, fa::TransitionComparator> &fa::Automaton::getTransitionCollection() const {
    return transitionCollection;
}


bool fa::Automaton::isDeterministic() const {
    if (getAlphabetSize() == 0)
        return true;
    char beforeTransitionName = (char) NULL;
    int beforeState = (int) NULL;

    for (Transition data : this->transitionCollection) {
        if (beforeState == data.getFrom()->getState()) {
            if (beforeTransitionName == data.getTransition_name())
                return false;
            beforeTransitionName = data.getTransition_name();
        } else {
            beforeTransitionName = data.getTransition_name();
            beforeState = data.getFrom()->getState();
        }
    }

    return true;
}

bool fa::Automaton::isComplete() const {
    if (getAlphabetSize() == 0)
        return true;
    char beforeTransitionName = this->transitionCollection.begin()->getTransition_name();
    int beforeState = this->transitionCollection.begin()->getFrom()->getState();
    size_t sizeAlphabet = this->getAlphabetSize();
    size_t countLetter = 1;
    std::map<int, StateConfiguration> cpyState(this->stateCollection);

    for (Transition data : this->transitionCollection) {
        if (beforeState == data.getFrom()->getState()) {
            if (beforeTransitionName == data.getTransition_name())
                continue;
            beforeTransitionName = data.getTransition_name();
            ++countLetter;
        } else {
            cpyState.erase(beforeState);
            if (countLetter != sizeAlphabet)
                return false;

            sizeAlphabet = this->getAlphabetSize();
            beforeTransitionName = data.getTransition_name();
            beforeState = data.getFrom()->getState();
            countLetter = 1;
        }
    }
    cpyState.erase(beforeState);
    if (countLetter != sizeAlphabet)
        return false;
    return cpyState.empty();
}

void fa::Automaton::makeComplete() {
    bool found = false;
    int trashState = -1;
    std::map<int, StateConfiguration> cpyState(this->stateCollection);
    std::map<int, std::set<char>> missingTrans;
    for (auto data : this->stateCollection) {
        missingTrans[data.first] = std::set<char>(this->alphabet);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 10000000);

    while (!found) {//if -1 state is taken.
        if (!hasState(trashState))
            found = true;
        else
            trashState = dis(gen);
    }

    for (Transition data : this->transitionCollection) {
        missingTrans[data.getFrom()->getState()].erase(data.getTransition_name());
        if (missingTrans.count(data.getFrom()->getState()) == 0)
            missingTrans.erase(data.getFrom()->getState());
    }

    if (!missingTrans.empty())
        this->addState(trashState);

    for (auto data : missingTrans) {
        for (auto alpha : data.second)
            this->addTransition(data.first, alpha, trashState);
    }

    for (auto data : this->alphabet)
        this->addTransition(trashState, data, trashState);

}

void fa::Automaton::makeComplement() {

    for (auto &data : this->stateCollection) {
        data.second.setFinal(!data.second.isFinal());
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
