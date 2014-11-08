//
//  smartSwap.h
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#ifndef __annealing__smartSwap__
#define __annealing__smartSwap__
#include "neighborhood.h"
#include <iostream>
class SmartSwap : public Neighborhood {
public:
    SmartSwap(Data &data):Neighborhood(data){;};
    Location generate(Location preLocation);
    int getLength();
};
#endif /* defined(__annealing__smartSwap__) */
