#include "Automaton.h"
#include <ostream>
#include <set>
#include <fstream>

//add state then transition.


int main() {
//
//    fa::Automaton aut;
//
//    aut.addState(0);
//    aut.setStateInitial(0);
//    aut.addState(1);
//    aut.setStateFinal(1);
//    aut.setStateInitial(1);
//    aut.addState(3);
//    aut.addState(2);
//    aut.addState(4);
//    aut.setStateFinal(4);
//
//    aut.addTransition(0, 'a', 1);
//    aut.addTransition(0, 'a', 2);
//    aut.addTransition(0, 'b', 2);
//    aut.addTransition(0, 'a', 3);
//    aut.addTransition(1, 'b', 3);
//    aut.addTransition(2, 'a', 3);
//    aut.addTransition(2, 'b', 4);
//    aut.addTransition(3, 'a', 3);
//    aut.addTransition(3, 'b', 4);
//    aut.addTransition(4, 'a', 4);
//
//   for(fa::Transition data : aut.getTransitionCollection()){
//       std::cout << '{' << data.getFrom()->getState() << ", " << data.getTo()->getState() << ", " << data.getTransition_name() << '}' << std::endl;
//   }
//
//    std::ofstream ofstream;
//    ofstream.open("../dot/automate.dot");
//    if (!ofstream){
//        std::cout << "error";
//        return 1;
//    }
//    aut.dotPrint(ofstream);
//    ofstream.close();

    std::map<int, char> a;
    a.insert(std::pair<int, char>(1,'m'));
    a.insert(std::pair<int, char>(15,'r'));

    std::map<int, char> cpy(a);

    for(auto it = cpy.begin(); it != cpy.end(); ++it)
        std::cout << it->first << "   " << it->second << std::endl;



    return 0;
}
