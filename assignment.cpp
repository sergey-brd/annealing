//
//  assignment.cpp
//  annealing
//
//  Created by Сергей Иванов on 28.04.14.
//
//

#include "assignment.h"
#include <stdlib.h>
#include <iostream>

#define INF 2000000000

Location Assignment::generate(Location location) {
    //int n = 1;
    std::vector<std::vector<std::vector<double>>> serverLoadTime(data.numberOfServers(), std::vector<std::vector<double>>(data.numberOfCharacteristics(), std::vector<double>(data.periodTime(), 0)));
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		int s = location.get(d);
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			for(int t = 0; t < data.periodTime(); t++) {
				serverLoadTime[s][r][t] += data.discLoad(d, r, t);
			}
		}
	}

    std::vector<int> disk(n);
    std::vector<int> server(data.numberOfServers());
    for(int i = 0; i < data.numberOfServers(); i++) {
        server[i] = i;
    }
    for(int i = 0; i < n; i++) {
        int j = rand() % (data.numberOfServers() - i) + i;
        int tmp = server[i];
        server[i] = server[j];
        server[j] = tmp;
    }

    for(int i = 0; i < n; i++) {
        std::vector<int> diskServer = std::vector<int>();
        int s = server[i];
        for(int d = 0; d < data.numberOfDiscs(); d++) {
            if(location.get(d) == s && location.canEjection(d)) {
                diskServer.push_back(d);
            }
        }
        if(diskServer.size() == 0) {
            return location;
        }
        disk[i] = diskServer[rand() % diskServer.size()];
        int d = disk[i];
        for(int r = 0; r < data.numberOfCharacteristics(); r++) {
            for(int t = 0; t < data.periodTime(); t++) {
                serverLoadTime[s][r][t] -= data.discLoad(d, r, t);
            }
        }

    }
    std::vector<std::vector<double>> a(n, std::vector<double>(data.numberOfServers(), 0));
    
    for(int d = 0; d < n; d++) {
        int d1 = disk[d];
        for(int s = 0; s < data.numberOfServers(); s++) {
            for(int r = 0; r < data.numberOfCharacteristics(); r++) {
                for(int t = 0; t < data.periodTime(); t++) {
                    double load = serverLoadTime[s][r][t] + data.discLoad(d1, r, t) - data.serverLoadLimits(s, r);
                    if(load > 0) {
                        a[d][s] += load;
                    }
                }
            }
            if(!location.canInsert(d1, s)) {
                a[d][s] = INF / 2;
            }

        }
    }
    
    std::vector<double> u = std::vector<double>(n + 1, 0);
    std::vector<double> v = std::vector<double>(data.numberOfServers() + 1, 0);
    std::vector<int> p= std::vector<int>(data.numberOfServers() + 1, 0);
    std::vector<double> way = std::vector<double>(data.numberOfServers() + 1, 0);

    for(int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        std::vector<int> minv(data.numberOfServers() + 1, 0);
        std::vector<bool> used(data.numberOfServers() + 1, 0);
        for(int j = 0; j < data.numberOfServers() + 1; j++) {
            minv[j] = INF;
            used[j] = false;
        }
        do {
            used[j0] = true;
            int i0 = p[j0];
            double delta = INF;
            int j1 = 0;
            for(int j = 1; j <= data.numberOfServers(); j++){
                if(!used[j]) {
                    int cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                    if(cur < minv[j]){
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if(minv[j] < delta){
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for(int j = 0; j <= data.numberOfServers(); ++j){
                if(used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while(p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while(j0);
    }
    //std::cout<<-v[0]<<std::endl;
    for(int i = 0; i < data.numberOfServers(); i++) {
        if(p[i + 1]) {
            location.set(disk[p[i + 1] - 1], i);
        }
    }
    return location;
};
int Assignment::getLength() {
    return (data.numberOfServers());
}
