//
//  neighborhood.cpp
//  annealing
//
//  Created by Сергей Иванов on 09.04.14.
//
//

#include "neighborhood.h"
#include <stdlib.h>     /* srand, rand */
#include "data.h"
#include "location.h"

Neighborhood::Neighborhood(Data &_data): data(_data) {
    //data = _data;
};
/*Location Neighborhood::generate(Location preLocation) {
    return preLocation;
};*/


Neighborhood::~Neighborhood() {
    
};
