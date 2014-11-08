//
//  result.h
//  annealing
//
//  Created by Сергей Иванов on 09.04.14.
//
//

#ifndef annealing_result_h
#define annealing_result_h
#include "data.h"
#include <vector>

class Location {
private:
    Data &data;
    std::vector<int> location;

public:
    Location(const Location& location);
    Location(Data &data);
    Location& operator=(const Location& right);

    double calc();
    bool allow();
    void set(int d, int s);
    int get(int d);
    bool canInsert(int d, int s);
    bool canEjection(int d);
};
#endif
