//
//  annealing.h
//  annealing
//
//  Created by Сергей Иванов on 08.04.14.
//
//

#ifndef annealing_annealing_h
#define annealing_annealing_h
#include "data.h"
#include "location.h"
#include "neighborhood.h"
#include "move.h"

class Annealing {
private:
    Data &data;
public:
    Annealing(Data &data);
    Location find();
    Location find(double startingTemperature, double constCooling, Neighborhood &neighborhood,
                  int frozen, double length, Location startLocation);
};

#endif
