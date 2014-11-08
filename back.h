//
//  back.h
//  annealing
//
//  Created by Сергей Иванов on 19.05.14.
//
//

#ifndef annealing_back_h
#define annealing_back_h
#include "neighborhood.h"
class Back : public Neighborhood {
public:
    Back(Data &data):Neighborhood(data){;}
    Location generate(Location preLocation);
    int getLength();
};


#endif
