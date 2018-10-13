#include "Automaton.h"
#include <ostream>
#include <set>
#include <fstream>

//add state then transition.


int main() {


    fa::Automaton aut;

    aut.addState(0);
    aut.setStateInitial(0);
    aut.addState(1);
    aut.setStateFinal(1);
    aut.setStateInitial(1);
    aut.addState(3);
    aut.addState(2);
    aut.addState(4);
    aut.setStateFinal(4);

    aut.addTransition(0, 'a', 1);
    aut.addTransition(0, 'a', 2);
    aut.addTransition(0, 'a', 3);
    aut.addTransition(1, 'b', 3);
    aut.addTransition(2, 'a', 3);
    aut.addTransition(2, 'b', 4);
    aut.addTransition(3, 'a', 3);
    aut.addTransition(3, 'b', 4);
    aut.addTransition(4, 'a', 4);


   // aut.prettyPrint(std::cout);

    std::ofstream ofstream;
    ofstream.open("../dot/automate.dot");
    if (!ofstream){
        std::cout << "erfffffffffffffffffffffffffffffffffror";
        return 1;

    }
    aut.dotPrint(ofstream);
    ofstream.close();



    return 0;
}
