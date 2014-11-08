//
//  smartMove.h
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#ifndef __annealing__smartMove__
#define __annealing__smartMove__
#include "neighborhood.h"
class SmartMove : public Neighborhood {
public:
    SmartMove(Data &data):Neighborhood(data){;};
    Location generate(Location preLocation);
    int getLength();
};
#endif /* defined(__annealing__smartMove__) */
