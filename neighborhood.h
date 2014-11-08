//
//  neighborhood.h
//  annealing
//
//  Created by Сергей Иванов on 09.04.14.
//
//

#ifndef annealing_neighborhood_h
#define annealing_neighborhood_h
#include "data.h"
#include "location.h"

class Neighborhood {
protected:
    Data &data;
public:
    Neighborhood(Data &_data);
    virtual Location generate(Location preLocation) = 0;
    virtual int getLength() = 0;
    ~Neighborhood();
};


#endif
