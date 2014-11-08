//
//  objective.h
//  annealing
//
//  Created by Сергей Иванов on 02.04.14.
//
//

#ifndef annealing_objective_h
#define annealing_objective_h
#include "data.h"
#include "location.h"
class Objective {
private:
    Data *data;
public:
    Objective(Data *_data);
    Objective();
    ~Objective();
    double calc(Location location);
    bool allow(Location location);
};


#endif
