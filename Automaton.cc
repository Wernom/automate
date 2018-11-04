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

void fa::StateConfiguration::setTransition(const std::set<fa::Transition, fa::TransitionComparator> &transition) {
    StateConfiguration::transition = transition;
}

void fa::StateConfiguration::insertTransition(fa::Transition transition) {
    this->transition.insert(transition);
}

//Transition's function

fa::StateConfiguration *fa::Transition::getTo() const {
    return stateTo;
}

char fa::Transition::getTransition_name() const {
    return transition_name;
}

fa::Transition::Transition(char transition_name, fa::StateConfiguration *stateTo) : transition_name(transition_name),
                                                                                    stateTo(stateTo) {}

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
        this->initialState.insert(state);
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
        this->finalState.insert(state);
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

    auto itState = this->stateCollection.find(from);
    auto it = itState->second.transition.find(Transition(alpha, &cTo));
    return it != itState->second.transition.end();
}

void fa::Automaton::addTransition(int from, char alpha, int to) {
    if (hasTransition(from, alpha, to)) {
        std::cout << "Warning: the transition {stateFrom=" << from << "; alpha=" << alpha << "; stateTo=" << to
                  << "} already exist." << std::endl;
        exit(EXIT_FAILURE);
    }

    this->numberOfTransition++;
    addToAlphabet(alpha);
    fa::Transition data(alpha, &stateCollection.find(to)->second);


    auto state = this->stateCollection.find(from);

    state->second.insertTransition(data);
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
    this->numberOfTransition--;

    StateConfiguration cTo(to);
    Transition trans(alpha, &cTo);

    this->stateCollection.find(from)->second.transition.erase(trans);

//    auto it = this->stateCollection.find(from);
//    auto itToErase = it->second.getTransition().find(Transition(alpha, &stateCollection.find(to)->second));
//    StateConfiguration cTo(to);
//    this->stateCollection.find(from)->second.getTransition().erase(Transition(alpha, &cTo));
//
//        std::cout << this->stateCollection.find(from)->second.getTransition().find(Transition(alpha, &stateCollection.find(to)->second))->getTransition_name() << std::endl;

}

std::size_t fa::Automaton::countTransitions() const {
    return this->numberOfTransition;
}

std::size_t fa::Automaton::getAlphabetSize() const {
    return alphabet.size();
}

void fa::Automaton::prettyPrint(std::ostream &os) const {

    std::cout << "Initial states:" << std::endl << '\t';

    for (int initial : this->initialState) {
        std::cout << initial << ' ';
    }

    std::cout << std::endl << "Finale states:" << std::endl << '\t';

    for (int final : this->finalState) {
        std::cout << final << ' ';
    }

    std::cout << std::endl << "Transitions:" << std::endl;
    for (auto state : this->stateCollection) {
        if (state.second.transition.begin() == state.second.transition.end()) continue;
        char currentTransition = state.second.transition.begin()->getTransition_name();
        std::cout << "\t\t" << "For state " << state.second.getState() << ':' << std::endl;
        std::cout << "\t\t\t\t" << "For letter " << currentTransition << ": ";

        for (Transition transition : state.second.transition) {
            if (transition.getTransition_name() != currentTransition) {
                currentTransition = transition.getTransition_name();
                std::cout << std::endl << "\t\t\t\t" << "For letter " << transition.getTransition_name() << ": ";
            }
            std::cout << transition.getTo()->getState() << ' ';
        }
        std::cout << std::endl;
    }








//    std::set<int> initialState;
//    std::set<int> finalState;
//    std::map<int, std::map<char, std::set<int>>> transition;
//
//    for (auto data : this->transitionCollection) {
//
//        fa::StateConfiguration *to = data.getTo();
//        fa::StateConfiguration *from = data.getFrom();
//
//        if (to->isInitial())
//            initialState.insert(to->getState());
//
//        if (from->isInitial())
//            initialState.insert(from->getState());
//
//        if (to->isFinal())
//            finalState.insert(to->getState());
//
//        if (from->isFinal())
//            finalState.insert(from->getState());
//
//        transition[from->getState()][data.getTransition_name()].insert(to->getState());
//
//    }
//
//    os << "Initial states:\n\t";
//    for (auto data : initialState) {
//        os << data << ' ';
//    }
//
//    os << "\n\nFinal states: " << std::endl << "\t";
//    for (auto data : finalState) {
//        os << data << ' ';
//    }
//
//    std::map<int, StateConfiguration> cpy(this->stateCollection);
//    os << "\n\nTransitions:";
//    auto it1 = transition.begin();
//    while (it1 != transition.end()) {
//        os << "\n\tFor state " << it1->first << ':';
//        cpy.erase(it1->first);
//
//        auto it2 = it1->second.begin();
//        while (it2 != it1->second.end()) {
//            os << "\n\t\tFor letter " << it2->first << ":  ";
//
//            for (auto data : it2->second) {
//                os << data << "  ";
//            }
//            ++it2;
//        }
//        ++it1;
//    }
//    for (auto data: cpy) {
//        os << "\n\tFor state " << data.first << ':';
//    }
//
//    os << std::endl;
}

void fa::Automaton::dotPrint(std::ostream &os) const {

    os << "digraph automaton{\n\trankdir=LR;\n\tnode[shape = point, color=white, fontcolor=white];";
    for (int initial : this->initialState) {
        os << "start" << initial << ';';
    }

    os << "\n\tnode [shape = doublecircle, color=black, fontcolor=black];";
    for (int final : this->finalState) {
        os << final << ';';
    }

    os << "\n\tnode [shape = circle];\n";

    for (auto state : this->stateCollection) {
        bool hasTransition = false;
        if (state.second.isInitial()) {
            os << "\tstart" << state.second.getState() << "->" << state.second.getState() << std::endl;
        }

        for (Transition trans : state.second.transition) {
            os << '\t' << state.second.getState() << "->" << trans.getTo()->getState() << " [ label = "
               << trans.getTransition_name() << " ];\n";
            hasTransition =true;
        }

        if(!hasTransition)
            os << '\t' << state.second.getState() <<";\n";
    }


    os << '}';

//    std::set<int> initialState;
//    std::set<int> finalState;
//    std::map<int, std::map<char, std::set<int>>> transition;
//
//    for (auto data : this->transitionCollection) {
//
//        fa::StateConfiguration *to = data.getTo();
//        fa::StateConfiguration *from = data.getFrom();
//
//        if (to->isInitial())
//            initialState.insert(to->getState());
//
//        if (from->isInitial())
//            initialState.insert(from->getState());
//
//        if (to->isFinal())
//            finalState.insert(to->getState());
//
//        if (from->isFinal())
//            finalState.insert(from->getState());
//
//        transition[from->getState()][data.getTransition_name()].insert(to->getState());
//    }
//
//    os << "digraph automaton{\n\trankdir=LR;\n\tnode[shape = point, color=white, fontcolor=white];";
//
//    for (auto data : initialState) {
//        os << " start" << data << ';';
//    }
//
//
//    os << "\n\tnode [shape = doublecircle, color=black, fontcolor=black];";
//    for (auto data : finalState) {
//        os << ' ' << data << ';';
//    }
//
//    os << std::endl << "\tnode [shape = circle];\n";
//
//    std::map<int, StateConfiguration> cpy(this->stateCollection);
//    auto it1 = transition.begin();
//    std::set<int> exist;
//    while (it1 != transition.end()) {
//        auto it2 = it1->second.begin();
//        cpy.erase(it1->first);
//        while (it2 != it1->second.end()) {
//            for (auto data : it2->second) {
//                os << '\t';
//                if (initialState.find(it1->first) != initialState.end() && exist.find(it1->first) == exist.end()) {
//                    os << "start" << it1->first << "->" << it1->first << ';' << std::endl << '\t';
//                    exist.insert(it1->first);
//                }
//                os << it1->first << "->";
//                os << data << "  ";
//                os << "[ label = " << it2->first << " ];" << std::endl;
//            }
//            ++it2;
//        }
//        ++it1;
//    }
//
//    for (auto data: cpy) {
//        if (!data.second.isFinal()) {
//            os << '\t';
//            os << data.first << ';' << std::endl;
//        }
//    }
//
//
//    for (auto data: cpy) {
//        os << '\t';
//        if (data.second.isFinal())
//            os << "node [shape = doublecircle, color=black, fontcolor=black];" << data.first << ';' << std::endl;
//
//        if (data.second.isInitial()) {
//            os << "node[shape = point, color=white, fontcolor=white]; start" << data.first << ';' << std::endl;
//            os << "\tstart" << data.first << "->" << data.first << ';';
//        }
//    }
//
//    os << '}';
}


bool fa::Automaton::isDeterministic() const {
    if (getAlphabetSize() == 0)
        return true;

    for (std::pair<const int, StateConfiguration> state : this->stateCollection) {
        char previousTransitionName = (char) NULL;
        for (Transition trans : state.second.transition) {
            if (previousTransitionName == trans.getTransition_name()) {
                return false;
            }

            previousTransitionName = trans.getTransition_name();

        }
    }



//    char beforeTransitionName = (char) NULL;
//    int beforeState = (int) NULL;
//
//    for (Transition data : this->transitionCollection) {
//        if (beforeState == data.getFrom()->getState()) {
//            if (beforeTransitionName == data.getTransition_name())
//                return false;
//            beforeTransitionName = data.getTransition_name();
//        } else {
//            beforeTransitionName = data.getTransition_name();
//            beforeState = data.getFrom()->getState();
//        }
//    }

    return true;
}

bool fa::Automaton::isComplete() const {
    if (getAlphabetSize() == 0)
        return true;

    for (std::pair<const int, StateConfiguration> state : this->stateCollection) {
        char previousTransitionName = (char) NULL;
        size_t countLetter = 0;
        for (Transition trans : state.second.transition) {
            if (previousTransitionName == trans.getTransition_name()) {
                continue;
            } else {
                countLetter++;
                previousTransitionName = trans.getTransition_name();
            }
        }

        if (countLetter != this->getAlphabetSize())
            return false;
    }

    return true;
}

void fa::Automaton::makeComplete() {
    bool found = false;
    bool trashStateAlreadyCreated = false;
    int trashState = -1;
    std::map<int, StateConfiguration> cpyState(this->stateCollection);
    std::map<int, std::set<char>> missingTransition;
    for (auto data : this->stateCollection) {
        missingTransition[data.first] = std::set<char>(this->alphabet);
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

    for (std::pair<const int, StateConfiguration> state : this->stateCollection) {
        for (Transition trans : state.second.transition) {
            missingTransition[state.first].erase(trans.getTransition_name());
        }

        if (!missingTransition.empty() && !trashStateAlreadyCreated) {
            this->addState(trashState);
            trashStateAlreadyCreated = true;
        }

        for (char transitionName : missingTransition[state.first]) {
            addTransition(state.first, transitionName, trashState);
        }
    }

    for (char transitionName : this->alphabet)
        this->addTransition(trashState, transitionName, trashState);

}

void fa::Automaton::makeComplement() {

    for (auto &data : this->stateCollection) {
        data.second.setFinal(!data.second.isFinal());
    }

}

const std::set<int> &fa::Automaton::getInitialState() const {
    return initialState;
}

bool fa::Automaton::isLanguageEmpty() const {
    if (this->initialState.empty() || this->finalState.empty())
        return false;

    std::set<int> visited;
    for (int state : this->initialState) {
        if (visited.find(state) !=
            visited.end())//TODO: si un etat initial à deja été parcouru soit on à trouvé un état final soit on en trouvera jamais => inutile.
            continue;

        if (this->checkPathToFinalState(this->stateCollection.find(state)->second, &visited))
            return false;

    }

    return true;
}

bool fa::Automaton::checkPathToFinalState(fa::StateConfiguration state, std::set<int> *visited) const {
    if (state.isFinal())
        return true;

    visited->insert(state.getState());

    std::cout  << visited->size() << std::endl;

    for (Transition trans : state.transition){

        if(visited->find(trans.getTo()->getState()) != visited->end())
            continue;

        if(this->checkPathToFinalState(*trans.getTo(), visited))
            return true;
    }

    return false;
}

const std::map<int, fa::StateConfiguration> &fa::Automaton::getStateCollection() const {
    return stateCollection;
}



//******************************************************************
//                          Comparator
//******************************************************************


bool fa::StateConfigurationComparator::operator()(const fa::StateConfiguration &state1,
                                                  const fa::StateConfiguration &state2) const {

    return state1.getState() < state2.getState();

}

bool fa::TransitionComparator::operator()(const fa::Transition &transition1, const fa::Transition &transition2) const {
    if (transition1.getTransition_name() == transition2.getTransition_name()) {
        return transition1.getTo()->getState() < transition2.getTo()->getState();
    }
    return transition1.getTransition_name() < transition2.getTransition_name();
}
