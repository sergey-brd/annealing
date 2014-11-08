//
//  main.cpp
//  annealing
//
//  Created by Сергей Иванов on 02.04.14.
//
//

#include <iostream>
#include "data.h"
#include "annealing.h"
#include <ctime>

int main(int argc, const char * argv[]) {
    Data data("/Users/ivanov/Dropbox/projects/annealing/annealing/in/inst1.txt");
    if(argc > 1) {
        std::cout<<"first param must be name of file" <<std::endl;
        Data data(argv[1]);
        //return 0;
    }
    //data.dataOut();
    Annealing annealing(data);
    //Location init(&data);
    //double length[] = {0.5, 1, 2, 4, 8, 16};
    Move move = Move::Move(data);
    //std::cout<<"\a";
    /*for(int i = 0; i < 6; i++) {
        //std::cout<<"Length = "<<length[i]<<std::endl;
        for(int j = 0; j < 1; j++) {
            clock_t clockStart = clock();
            Location result = annealing.find(1000, 0.97, move, 10, 2, Location(data));
            clock_t clockEnd = clock();
            std::cout<<result.calc()<<std::endl;
            std::cout<<(clockEnd - clockStart) / CLOCKS_PER_SEC<<std::endl;
            std::cout<<"\a";

        }
    }*/
    Location result = Location(data);
    
    //Location result = annealing.find(1000, 0.97, move, 10, 2 , Location(data));
    std::cout<<result.calc()<<std::endl;
    if(result.allow()) {
        std::cout<<"allow"<<std::endl;
    } else {
        std::cout<<"NOTallow"<<std::endl;
    }
    return 0;
}
