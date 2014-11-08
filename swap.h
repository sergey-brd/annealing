//
//  swap.h
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#ifndef __annealing__swap__
#define __annealing__swap__
#include "neighborhood.h"
class Swap : public Neighborhood {
public:
    Swap(Data &data):Neighborhood(data){;}
    Location generate(Location preLocation);
    int getLength();
};
#endif /* defined(__annealing__swap__) */
