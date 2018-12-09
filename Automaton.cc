#include "Automaton.h"


//State Configuration's function
fa::StateConfiguration::StateConfiguration(int state) : state(state) {
    this->state = state;
    this->initial = false;
    this->final = false;
    this->transition.empty();
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

void fa::StateConfiguration::setDial(int dial) {
    StateConfiguration::dial = dial;
}

int fa::StateConfiguration::getDial() const {
    return this->dial;
}

//int fa::StateConfiguration::getDial() const {
//    return dial;
//}
//
//void fa::StateConfiguration::setDial(int dial) {
//    StateConfiguration::dial = dial;
//}

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
        std::cerr << "The state " << state << " is already in the Automaton" << std::endl;
    } else {
        fa::StateConfiguration s(state);
        s.setDial((int) this->countStates());
        this->stateCollection.insert(std::pair<int, fa::StateConfiguration>(state, s));
    }
}

void fa::Automaton::removeState(int state) {
    this->stateCollection.erase(state);
    this->initialState.erase(state);
    this->finalState.erase(state);
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
        std::cerr << "Error: the state " << state << " doesn't exist." << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool fa::Automaton::isStateInitial(int state) const {
    if (hasState(state)) {
        return this->stateCollection.find(state)->second.isInitial();
    }
    std::cerr << "Error: the state " << state << " doesn't exist." << std::endl;
    exit(EXIT_FAILURE);
}

void fa::Automaton::setStateFinal(int state) {
    if (hasState(state)) {
        this->stateCollection.find(state)->second.setFinal(true);
        this->finalState.insert(state);
    } else {
        std::cerr << "Error: the state " << state << " doesn't exist." << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool fa::Automaton::isStateFinal(int state) const {
    if (hasState(state)) {
        return this->stateCollection.find(state)->second.isFinal();
    }

    std::cerr << "Error: the state " << state << "doesn't exist." << std::endl;
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
    if (!(isprint(alpha) || alpha == '\0'))  {
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
}

std::size_t fa::Automaton::countTransitions() const {
    return this->numberOfTransition;
}

std::size_t fa::Automaton::getAlphabetSize() const {
    return alphabet.size();
}

void fa::Automaton::prettyPrint(std::ostream &os) const {//TODO: do test

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
            if (trans.getTransition_name() == '\0')
                os << '\t' << state.second.getState() << "->" << trans.getTo()->getState() << " [ label = NUL ];\n";
            else
                os << '\t' << state.second.getState() << "->" << trans.getTo()->getState() << " [ label = "
                   << trans.getTransition_name() << " ];\n";
            hasTransition = true;
        }

        if (!hasTransition)
            os << '\t' << state.second.getState() << ";\n";
    }
    os << '}';
}


bool fa::Automaton::isDeterministic() const {
    if (getAlphabetSize() == 0)
        return true;

    for (std::pair<const int, StateConfiguration> state : this->stateCollection) {
        auto previousTransitionName = (char) NULL;
        for (Transition trans : state.second.transition) {
            if (previousTransitionName == trans.getTransition_name()) {
                return false;
            }

            previousTransitionName = trans.getTransition_name();

        }
    }
    return true;
}

bool fa::Automaton::isComplete() const {
    if (getAlphabetSize() == 0)
        return true;

    for (std::pair<const int, StateConfiguration> state : this->stateCollection) {
        auto previousTransitionName = (char) NULL;
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
    if (this->isDeterministic() && this->isComplete()){
        std::cerr << "The automaton must be deterministic and complete." << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto &data : this->stateCollection) {
        data.second.setFinal(!data.second.isFinal());
    }

}

const std::set<int> &fa::Automaton::getInitialState() const {
    return initialState;
}

bool fa::Automaton::isLanguageEmpty() const {
    if (this->initialState.empty() || this->finalState.empty())
        return true;

    std::set<int> visited;
    for (int state : this->initialState) {
        if (visited.find(state) != visited.end()) {
            std::cout << "rxetcyfvguhbinj" << std::endl;
            continue;
        }//TODO: si un etat initial à deja été parcouru soit on à trouvé un état final soit on en trouvera jamais => inutile.

        if (this->checkPathToFinalState(this->stateCollection.find(state)->second, &visited))
            return false;

    }

    return true;
}

bool fa::Automaton::checkPathToFinalState(fa::StateConfiguration state, std::set<int> *visited) const {
    if (state.isFinal())
        return true;

    visited->insert(state.getState());

    for (Transition trans : state.transition) {

        if (visited->find(trans.getTo()->getState()) != visited->end())
            continue;

        if (this->checkPathToFinalState(*trans.getTo(), visited))
            return true;
    }

    return false;
}

const std::map<int, fa::StateConfiguration> &fa::Automaton::getStateCollection() const {
    return stateCollection;
}

void fa::Automaton::removeNonAccessibleStates() {
    if (this->initialState.empty()) {
        this->stateCollection.clear();
    }
    std::set<int> visited;
    std::map<int, StateConfiguration> newStateCollection;
    for (int state : this->initialState) {
        createAutomatonWithoutNonAccessibleStates(&visited,
                                                  this->stateCollection.find(state)->second);
    }

    for (auto it : this->stateCollection) {
        if (visited.find(it.second.getState()) == visited.end()) {
            this->removeState(it.second.getState());
        }

    }


}

void fa::Automaton::createAutomatonWithoutNonAccessibleStates(std::set<int> *visited,
                                                              fa::StateConfiguration state) {

    if (visited->find(state.getState()) != visited->end())
        return;

    visited->insert(state.getState());
    for (Transition trans : state.transition) {
        createAutomatonWithoutNonAccessibleStates(visited, *trans.getTo());
    }
}


void fa::Automaton::removeNonCoAccessibleStates() {
//TODO: getFinal if empty ->state clear

    std::set<int> visited;
    for (auto state : this->stateCollection) {
        if (visited.find(state.second.getState()) != visited.end())
            continue;
        createAutomatonWithoutNonCoAccessibleStates(&visited, state.second);
    }
}

bool fa::Automaton::createAutomatonWithoutNonCoAccessibleStates(std::set<int> *visited,
                                                                fa::StateConfiguration state) {
    visited->insert(state.getState());
    if (state.isFinal()) {
        return true;
    }

    bool isCoAccessible = false;
    for (Transition trans : state.transition) {
        if (visited->find(trans.getTo()->getState()) != visited->end()) {
            isCoAccessible = true;
        } else
            isCoAccessible =
                    isCoAccessible | this->createAutomatonWithoutNonCoAccessibleStates(visited, *trans.getTo());
    }

    if (!isCoAccessible) {
        this->removeState(state.getState());
    }

    return isCoAccessible;
}

fa::Automaton fa::Automaton::createProduct(const fa::Automaton &lhs, const fa::Automaton &rhs) {

    Automaton res;
    if (lhs.isLanguageEmpty() || rhs.isLanguageEmpty()) {//oui c'est un tapis mais sinon ca crache.
        res.addState(0);
        res.setStateInitial(0);
        return res;
    }
    std::set<int> newState;
    auto stateAmountProcuct = (int) (rhs.countStates() * lhs.countStates());

    for (auto stateLhs : lhs.getInitialState()) {
        for (auto stateRhs : rhs.getInitialState()) {
            int state = lhs.getStateCollection().find(stateLhs)->second.getDial() * (int) rhs.countStates() +
                        rhs.getStateCollection().find(stateRhs)->second.getDial();
            newState.insert(state);
            res.addState(state);
            res.setStateInitial(state);
        }
    }

    createProductRec(lhs, rhs, newState, &res, stateAmountProcuct);

    return res;
}

void fa::Automaton::createProductRec(const fa::Automaton &lhs, const fa::Automaton &rhs, std::set<int> stateToAdd,
                                     fa::Automaton *aut, int stateAmountProduct) {
    if (stateToAdd.empty()) {
        return;
    }

    std::set<int> newStateCollection;

    for (int state : stateToAdd) {
        if (aut->getStateCollection().find(state) == aut->getStateCollection().end()) {
            continue;
        }

        for (auto transLhs : lhs.findByDial(
                state / (int) rhs.countStates()).second.transition) { //TODO SIGSEGV si automate empty.
            for (auto transRhs : rhs.findByDial(state % (int) rhs.countStates()).second.transition) {
                int newState =
                        transLhs.getTo()->getDial() * (int) rhs.countStates() + transRhs.getTo()->getDial();
                if (transLhs.getTransition_name() == transRhs.getTransition_name()) {
                    if (aut->getStateCollection().find(newState) == aut->getStateCollection().end()) {
                        aut->addState(newState);
                        if (transLhs.getTo()->isInitial() && transRhs.getTo()->isInitial())
                            aut->setStateInitial(newState);
                        if (transLhs.getTo()->isFinal() && transRhs.getTo()->isFinal())
                            aut->setStateFinal(newState);

                        newStateCollection.insert(newState);
                    }

                    aut->addTransition(state, transLhs.getTransition_name(), newState);
                }
            }
        }
    }
    createProductRec(lhs, rhs, newStateCollection, aut, stateAmountProduct);
}

bool fa::Automaton::hasEmptyIntersectionWith(const fa::Automaton &other) const {
    Automaton res = createProduct(*this, other);
    return res.isLanguageEmpty();
}

const std::pair<const int, fa::StateConfiguration> &fa::Automaton::findByDial(int dial) const {
    for (auto &it : this->stateCollection) {
        if (it.second.getDial() == dial)
            return it;
    }
    return *this->stateCollection.end();
}


std::set<int> fa::Automaton::readString(const std::string &word) const {
    std::set<int> deriv;

    if (word.empty()){
        for (auto state : this->initialState){
            if (this->stateCollection.find(state)->second.isFinal()){
                deriv.insert(state);
                return deriv;
            }
        }
        return deriv;
    }

    for (auto state : this->initialState) {

        for (auto trans : this->stateCollection.find(state)->second.transition) {
            if (word.at(0) == trans.getTransition_name()){
                if (readStringRec(word, 1, *trans.getTo(), &deriv)){
                    deriv.insert(state);
                    return deriv;
                }
            }

            deriv.clear();
        }
    }

    return std::set<int>();
}

bool fa::Automaton::readStringRec(const std::string &word, unsigned at, StateConfiguration state, std::set<int> *deriv) const {
    if(at >= word.length()){
        if (state.isFinal()){
            deriv->insert(state.getState());
            return true;
        }
        return false;
    }
    for (auto trans : state.transition){
        if (word.at(at) == trans.getTransition_name()){
            if(readStringRec(word, at + 1, *trans.getTo(), deriv)){
                deriv->insert(state.getState());
                return true;
            }
        }
    }
    return false;
}

bool fa::Automaton::match(const std::string &word) const {
    std::set<int> res = readString(word);
    return !res.empty();
}

fa::Automaton fa::Automaton::createDeterministic(const fa::Automaton &automaton) {
    if (automaton.isDeterministic())
        return automaton;

    fa::Automaton newAutomaton;
    std::set <int> treatedState;
    std::set<int> stateCollectionToAdd;
    int newIndex = 0;
    int newStateToAdd = 0;
    bool isFinal = false;
    for (int state : automaton.initialState){
        newStateToAdd += state * (int)pow(10, newIndex);
        newIndex++;
        if (automaton.getStateCollection().find(state)->second.isFinal())
            isFinal = true;
        stateCollectionToAdd.insert(state);
    }

    newAutomaton.addState(newStateToAdd);
    newAutomaton.setStateInitial(newStateToAdd);
    if (isFinal)
        newAutomaton.setStateFinal(newStateToAdd);

    createDeterministicRec(stateCollectionToAdd, &newAutomaton, automaton, newStateToAdd, &treatedState);

    return newAutomaton;
}

void fa::Automaton::createDeterministicRec(std::set<int> stateCollectionToAdd, fa::Automaton *newAutomaton, const fa::Automaton &automaton, int stateToAdd, std::set<int> *treatedState) {
    std::cout << "-> " << stateToAdd << std::endl;
    if(treatedState->find(stateToAdd) != treatedState->end()){
        std::cout << "state skip: " << stateToAdd << std::endl;
        std::cout << "<-" << std::endl;
        return;
    }
    treatedState->insert(stateToAdd);
    std::multimap<char, int> newTransition;

    //get the transition to add
    for (auto state : stateCollectionToAdd){
        for (auto trans : automaton.stateCollection.find(state)->second.transition){
            newTransition.insert(std::pair<char, int>(trans.getTransition_name(),trans.getTo()->getState()));
        }

    }

    int newIndex = 0;
    int newStateToAdd = 0;
    bool final = false;
    bool hasTransition = false;
    std::set<int> newStateCollectionToAdd;
    char lastTransition = newTransition.begin()->first;
    for (auto transToAdd : newTransition){
        hasTransition = true;
        std::cout << "transistion: " << transToAdd.first << std::endl;
        if(lastTransition != transToAdd.first){
            if(newAutomaton->stateCollection.find(newStateToAdd) == newAutomaton->stateCollection.end()){
                std::cout << "state added: "  << newStateToAdd << std::endl;
                newAutomaton->addState(newStateToAdd);

                if(final)
                    newAutomaton->setStateFinal(newStateToAdd);

                createDeterministicRec(newStateCollectionToAdd, newAutomaton, automaton, newStateToAdd, treatedState);
            }
            std::cout << "Transistion added: " << stateToAdd << " -> " << lastTransition << " -> " << newStateToAdd <<std::endl;
            newAutomaton->addTransition(stateToAdd, lastTransition, newStateToAdd);
            newIndex = 0;
            newStateToAdd = 0;
            newStateCollectionToAdd.clear();
        }

        if(automaton.stateCollection.find(transToAdd.second)->second.isFinal())
            final = true;

        newStateToAdd += transToAdd.second * (int)pow(10, newIndex);
        newIndex++;
        lastTransition = transToAdd.first;
        newStateCollectionToAdd.insert(transToAdd.second);
    }

    if (hasTransition){
        if(newAutomaton->stateCollection.find(newStateToAdd) == newAutomaton->stateCollection.end()){
            std::cout << "state added: "  << newStateToAdd << std::endl;
            newAutomaton->addState(newStateToAdd);

            if(final)
                newAutomaton->setStateFinal(newStateToAdd);

            createDeterministicRec(newStateCollectionToAdd, newAutomaton, automaton, newStateToAdd, treatedState);
        }
        std::cout << "Transistion added: " << stateToAdd << " -> " << lastTransition << " -> " << newStateToAdd <<std::endl;
        newAutomaton->addTransition(stateToAdd, lastTransition, newStateToAdd);
        newStateCollectionToAdd.clear();
    }

    std::cout << "<-" << std::endl;
}

bool fa::Automaton::isIncludedIn(const fa::Automaton &other) const {
    fa::Automaton aer = *this;
    fa::Automaton otherCpy = other;
    otherCpy.makeComplement();

    return fa::Automaton::createProduct(*this, otherCpy).isLanguageEmpty();
}

fa::Automaton fa::Automaton::createMinimalMoore(const fa::Automaton &automaton) {
    return fa::Automaton();
}

fa::Automaton fa::Automaton::createWithoutEpsilon(const fa::Automaton &automaton) {

    fa::Automaton res = cpyAutomaton(automaton);


    for (auto state : res.getStateCollection()){
        for (auto transition : state.second.transition){
            if (transition.getTransition_name() == '\0'){
                res.removeTransition(state.second.getState(), '\0', transition.getTo()->getState());

                if (transition.getTo()->isFinal())
                    res.setStateFinal(state.first);

                createWithoutEpsilonRec(res, state.second, *transition.getTo());
            }
        }
    }


    return res;
}

void fa::Automaton::createWithoutEpsilonRec(fa::Automaton &automaton, fa::StateConfiguration &stateRemoveEpsilon, fa::StateConfiguration &stateTo) {
    if (stateTo.getState() == stateRemoveEpsilon.getState())
        return;

    for (auto transition : stateTo.transition){
        if (transition.getTransition_name() == '\0'){
            createWithoutEpsilonRec(automaton, stateRemoveEpsilon, *transition.getTo());
        }else{
            if (automaton.hasTransition(stateRemoveEpsilon.getState(), transition.getTransition_name(), transition.getTo()->getState()))
                continue;

            automaton.addTransition(stateRemoveEpsilon.getState(), transition.getTransition_name(), transition.getTo()->getState());
        }
    }
}

fa::Automaton fa::Automaton::cpyAutomaton(const fa::Automaton &automaton) {
    fa::Automaton res;

    for (auto state : automaton.stateCollection){
        if (res.stateCollection.find(state.first) == res.stateCollection.end())
            res.addState(state.first);

        if (state.second.isFinal())
            res.setStateFinal(state.first);

        if (state.second.isInitial())
            res.setStateInitial(state.first);

        for(auto trans : state.second.transition){
            if (res.stateCollection.find(trans.getTo()->getState()) == res.stateCollection.end())
                res.addState(trans.getTo()->getState());
            res.addTransition(state.first, trans.getTransition_name(), trans.getTo()->getState());

        }
    }

    return res;
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
