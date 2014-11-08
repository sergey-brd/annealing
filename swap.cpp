//
//  swap.cpp
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#include "swap.h"
#include <stdlib.h>
#include <iostream>
Location Swap::generate(Location preLocation) {

    std::vector<int> disk(data.numberOfDiscs(), 0);
    for(int d = 0; d < data.numberOfDiscs(); d++) {
        disk[d] = d;
    }
    for(int d1 = 0; d1 < data.numberOfDiscs() - 1; d1++) {
        if(d1 == 0) {
            int j = rand() % (data.numberOfDiscs() - d1) + d1;
            int tmp = disk[d1];
            disk[d1] = disk[j];
            disk[j] = tmp;
        }
        for(int d2 = d1 + 1; d2 < data.numberOfDiscs(); d2++) {
            if(d1 == 0) {
                int j = rand() % (data.numberOfDiscs() - d2) + d2;
                int tmp = disk[d2];
                disk[d2] = disk[j];
                disk[j] = tmp;
            }
            if(d1 != d2) {
                int s1 = preLocation.get(disk[d1]);
                int s2 = preLocation.get(disk[d2]);
                if(preLocation.canEjection(disk[d1]) && preLocation.canEjection(disk[d2]) && preLocation.canInsert(disk[d1], s2) &&preLocation.canInsert(disk[d2], s1)) {
                    preLocation.set(disk[d1], s2);
                    preLocation.set(disk[d2], s1);
                    return preLocation;
                }
            }
        }

    }
    //std::cout<<":("<<std::endl;
    return preLocation;
};
int Swap::getLength() {
    return (data.numberOfDiscs() * data.numberOfDiscs());
}
