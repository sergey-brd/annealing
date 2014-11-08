//
//  move.cpp
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#include "move.h"
#include <stdlib.h>
#include <iostream>
Location Move::generate(Location preLocation) {
    std::vector<int> disk(data.numberOfDiscs(), 0);
    for(int d = 0; d < data.numberOfDiscs(); d++) {
        disk[d] = d;
    }
    std::vector<int> server(data.numberOfServers(), 0);
    for(int s = 0; s < data.numberOfServers(); s++) {
        server[s] = s;
    }
    
    for(int d = 0; d < data.numberOfDiscs(); d++) {
        int j = rand() % (data.numberOfDiscs() - d) + d;
        int tmp = disk[d];
        disk[d] = disk[j];
        disk[j] = tmp;
        if(preLocation.canEjection(disk[d])) {
            for(int s = 0; s < data.numberOfServers(); s++) {
                if(d == 0) {
                    int j = rand() % (data.numberOfServers() - s) + s;
                    int tmp = server[s];
                    server[s] = server[j];
                    server[j] = tmp;
                }
                if(preLocation.canInsert(disk[d], server[s])) {
                    preLocation.set(disk[d], server[s]);
                    return preLocation;
                }
            }
        }
    }
    return preLocation;
};
int Move::getLength() {
    return (data.numberOfDiscs() * data.numberOfServers());
}