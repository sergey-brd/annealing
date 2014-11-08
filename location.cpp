//
//  Location.cpp
//  annealing
//
//  Created by Сергей Иванов on 09.04.14.
//
//

#include "location.h"
#include <iostream>

Location::Location(Data &_data): data(_data) {
    location =	std::vector<int>(data.numberOfDiscs());
    for(int d = 0; d < data.numberOfDiscs(); d++) {
        location[d] = data.curLocation(d);
    }
}

void Location::set(int d, int s) {
	location[d] = s;
};
int Location::get(int d) {
    return location[d];
};

Location::Location(const Location& right): data(right.data) {
	data = right.data;
    location =	std::vector<int>(data.numberOfDiscs());
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		location[d] = right.location[d];
	}
};

Location& Location::operator=(const Location& right) {
	if (this == &right) {
		return *this;
	}
	data = right.data;
    location =	std::vector<int>(data.numberOfDiscs());
    
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		location[d] = right.location[d];
	}
	return *this;
}


bool Location::canInsert(int d1, int s1) {
    std::vector<double> serverInsertion(data.numberOfCharacteristics(), 0);
    if(s1 == location[d1]) {
        return true;
    }
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		int s = location[d];
		int s0 = data.initLocation(d);
        if(s == s1 && s0 != s) {
			for(int r = 0; r < data.numberOfCharacteristics(); r++) {
				serverInsertion[r] += data.insertionCosts(s, d, r);
			}
		}
	}
    for(int r = 0; r < data.numberOfCharacteristics(); r++) {
        double load = serverInsertion[r] + data.insertionCosts(s1, d1, r) - data.insertLimits(s1, r);
		if(load > 0) {
            return false;
        }
    }
    return true;
}
bool Location::canEjection(int d1) {
    std::vector<double> serverEjection(data.numberOfCharacteristics(), 0);
	int s1 = data.initLocation(d1);
    if(s1 != location[d1]) {
        return true;
    }
    for(int d = 0; d < data.numberOfDiscs(); d++) {
        int s = location[d];
		int s0 = data.initLocation(d);
        if(s0 == s1 && s0 != s) {
			for(int r = 0; r < data.numberOfCharacteristics(); r++) {
				serverEjection[r] += data.ejectionCosts(s0, d, r);
			}
		}
	}
    for(int r = 0; r < data.numberOfCharacteristics(); r++) {
        double load = serverEjection[r] + data.ejectionCosts(s1, d1, r) - data.ejectionLimits(s1, r);
        if(load > 0) {
            return false;
        }
    }
    return true;
}

double Location::calc() {
    std::vector<std::vector<std::vector<double>>> serverLoadTime(data.numberOfServers(), std::vector<std::vector<double>>(data.numberOfCharacteristics(), std::vector<double>(data.periodTime(), 0)));
	
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		int s = location[d];
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			for(int t = 0; t < data.periodTime(); t++) {
				serverLoadTime[s][r][t] += data.discLoad(d, r, t);
			}
		}
	}
	double f = 0;

	for(int s = 0; s < data.numberOfServers(); s++) {
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			for(int t = 0; t < data.periodTime(); t++) {
				double load = serverLoadTime[s][r][t] - data.serverLoadLimits(s, r);
				if(load > 0) {
					f += load;
				}
			}
		}
	}
    return f;
};
bool Location::allow() {
    std::vector<std::vector<double>> serverInsertion(data.numberOfServers(), std::vector<double>(data.numberOfCharacteristics(), 0));
    std::vector<std::vector<double>> serverEjection(data.numberOfServers(), std::vector<double>(data.numberOfCharacteristics(), 0));
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		int s = location[d];
        int s0 = data.initLocation(d);
        if(s0 != s) {
			for(int r = 0; r < data.numberOfCharacteristics(); r++) {
				serverInsertion[s][r] += data.insertionCosts(s, d, r);
				serverEjection[s0][r] += data.ejectionCosts(s0, d, r);
			}
		}
	}
    
    double load;
    bool ret = true;
	for(int s = 0; s < data.numberOfServers(); s++) {
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			load = serverInsertion[s][r] - data.insertLimits(s, r);
			if(load > 0) {
                //std::cout<<"Allow:: "<<s<<" insert bad characteristic "<<r<<std::endl;
                ret = false;
            }
			load = serverEjection[s][r] - data.ejectionLimits(s, r);
			if(load > 0) {
                //std::cout<<"Allow:: "<<s<<" ejection bad characteristic "<<r<<std::endl;
                ret = false;
			}
			
		}
	}
    std::cout<<"Allow calc:"<<std::endl;
    for(int s = 0; s < data.numberOfServers(); s++) {
        for(int r = 0; r < data.numberOfCharacteristics(); r++) {
            //std::cout<<serverInsertion[s][r] - data.ejectionLimits(s, r)<<std::endl;
            //std::cout<<serverEjection[s][r] - data.insertLimits(s, r)<<std::endl;
        }
    }
	
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			std::cout<<serverInsertion[0][r]<< " " <<data.insertLimits(0, r)<<std::endl;
			std::cout<<serverEjection[0][r]<< " " <<data.ejectionLimits(0, r)<<std::endl;
		}
	std::cout<<"Allow calc END1"<<std::endl;
	for(int r = 0; r < data.numberOfCharacteristics(); r++) {
		std::cout<<data.insertionCosts(0, 4, r)<<std::endl;
	}
	std::cout<<std::endl;

	for(int r = 0; r < data.numberOfCharacteristics(); r++) {
		std::cout<<data.ejectionCosts(0, 4, r)<<std::endl;
	}

	std::cout<<"Allow calc END2"<<std::endl;
    return ret;
}
