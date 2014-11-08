//
//  move.h
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#ifndef __annealing__move__
#define __annealing__move__
#include "neighborhood.h"
class Move : public Neighborhood {
public:
    Move(Data &data) : Neighborhood(data){;};
    Location generate(Location preLocation);
    int getLength();
};
#endif /* defined(__annealing__swap__) */
