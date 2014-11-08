//
//  back.cpp
//  annealing
//
//  Created by Сергей Иванов on 19.05.14.
//
//

#include "back.h"
#include <stdlib.h>
Location Back::generate(Location preLocation) {
    double calc;
    Location curLocation(preLocation);
    
    curLocation.set(0, data.initLocation(0));
    calc = curLocation.calc();
    curLocation.set(0, preLocation.get(0));
    int dmin = 0;
    double curCalc;
    for(int d = 1; d < data.numberOfDiscs(); d++) {
        curLocation.set(d, data.initLocation(d));
        curCalc = curLocation.calc();
        if(curCalc < calc) {
            dmin = d;
            calc = curCalc;
        }
        curLocation.set(d, preLocation.get(d));
    }

    preLocation.set(dmin, data.initLocation(dmin));
    return preLocation;
};
int Back::getLength() {
    return 1;
}