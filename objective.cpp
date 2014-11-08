    //
//  Objective.cpp
//  annealing
//
//  Created by Сергей Иванов on 02.04.14.
//
//

#include "Objective.h"
#include <iostream>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define INF 2000000001

Objective::Objective(Data *_data){
    data = _data;
}
Objective::Objective() {
}
Objective::~Objective() {
}
double Objective::calc(Location result) {
	double f = 0;
	double load;
    std::vector<std::vector<std::vector<double>>> serverLoadTime(data->numberOfServers(), std::vector<std::vector<double>>(data->numberOfCharacteristics(), std::vector<double>(data->periodTime(), 0)));

    for(int d = 0; d < data->numberOfDiscs(); d++) {
		int s = result.get(d);
		for(int r = 0; r < data->numberOfCharacteristics(); r++) {
			for(int t = 0; t < data->periodTime(); t++) {
				serverLoadTime[s][r][t] += data->discLoad(d, r, t);
			}
		}
	}
	for(int s = 0; s < data->numberOfServers(); s++) {
		for(int r = 0; r < data->numberOfCharacteristics(); r++) {
			for(int t = 0; t < data->periodTime(); t++) {
				load = serverLoadTime[s][r][t] - data->serverLoadLimits(s, r);
				f += max(load, 0);
				//printf("sum = %lf\n", serverLoad(s, r, t));
				//printf("d = %lf\n", serverLoadLimits(s, r));
			}
		}
	}
    return f;
};
bool Objective::allow(Location result) {
    std::vector<std::vector<double>> serverInsertion(data->numberOfServers(), std::vector<double>(data->numberOfCharacteristics(), 0));
    std::vector<std::vector<double>> serverEjection(data->numberOfServers(), std::vector<double>(data->numberOfCharacteristics(), 0));
    for(int d = 0; d < data->numberOfDiscs(); d++) {
		int s = result.get(d);
        int s0 = data->initLocation(d);
        if(s0 != s) {
			for(int r = 0; r < data->numberOfCharacteristics(); r++) {
				serverInsertion[s][r] += data->insertionCosts(s, d, r);
				serverEjection[s0][r] += data->ejectionCosts(s0, d, r);
			}
		}
	}
    
    double load;
    bool ret = true;
	for(int s = 0; s < data->numberOfServers(); s++) {
		for(int r = 0; r < data->numberOfCharacteristics(); r++) {
			load = serverInsertion[s][r] - data->insertLimits(s, r);
			if(load > 0) {
                //std::cout<<"Allow:: "<<s<<" insert bad characteristic "<<r<<std::endl;
                ret = false;
            }
			load = serverEjection[s][r] - data->ejectionLimits(s, r);
			if(load > 0) {
                //std::cout<<"Allow:: "<<s<<" ejection bad characteristic "<<r<<std::endl;
                ret = false;
			}
			
		}
	}
    //std::cout<<"Allow calc:"<<std::endl;
    for(int s = 0; s < data->numberOfServers(); s++) {
        for(int r = 0; r < data->numberOfCharacteristics(); r++) {
            //std::cout<<serverInsertion[s][r] - data->ejectionLimits(s, r)<<std::endl;
            //std::cout<<serverEjection[s][r] - data->insertLimits(s, r)<<std::endl;
        }
    }
    return ret;
}