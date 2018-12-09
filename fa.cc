#include "Automaton.h"
#include <ostream>
#include <set>
#include <fstream>

//add state then transition.


void foo1(int i, std::set<int> *data){
    data->insert(i);

    for(auto d : *data){
        std::cout << d << ' ';
    }
    std::cout << std::endl;

}

void foo0(){
    std::set<int> data;

    for(int i = 0; i < 5; i++){
        foo1(i, &data);
    }

}

int main() {

    std::cout << "0 -> " << isprint( '\0') << std::endl;


    return 0;
}

