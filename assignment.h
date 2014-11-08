//
//  assignment.h
//  annealing
//
//  Created by Сергей Иванов on 28.04.14.
//
//

#ifndef __annealing__assignment__
#define __annealing__assignment__
#include "neighborhood.h"
class Assignment : public Neighborhood {
private:
    int n;
public:
    Assignment(Data &data, int _n = 1) : Neighborhood(data){n = _n;};
    Location generate(Location location);
    int getLength();
};


#endif /* defined(__annealing__assignment__) */
