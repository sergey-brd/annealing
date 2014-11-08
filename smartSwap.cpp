//
//  smartSwap.cpp
//  annealing
//
//  Created by Сергей Иванов on 25.04.14.
//
//

#include "smartSwap.h"
#define max(a, b) ((a) > (b) ? (a) : (b))

#define serverLoadTime(s, r, t)		serverLoadTime[((s) * data.numberOfCharacteristics() + (r)) * data.periodTime() + (t)]

Location SmartSwap::generate(Location preLocation) {
    double *serverLoad = new double[data.numberOfServers()];
	for(int s = 0; s < data.numberOfServers(); s++) {
        serverLoad[s] = 0;
    }
    double *serverLoadTime = new double[data.numberOfServers() * data.periodTime() * data.numberOfCharacteristics()];
    
    for(int s = 0; s < data.numberOfServers(); s++) {
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			for(int t = 0; t < data.periodTime(); t++) {
				serverLoadTime(s, r, t) = 0;
			}
		}
	}
    for(int d = 0; d < data.numberOfDiscs(); d++) {
		int s = preLocation.get(d);
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			for(int t = 0; t < data.periodTime(); t++) {
				serverLoadTime(s, r, t) += data.discLoad(d, r, t);
			}
		}
	}
	for(int s = 0; s < data.numberOfServers(); s++) {
		for(int r = 0; r < data.numberOfCharacteristics(); r++) {
			for(int t = 0; t < data.periodTime(); t++) {
				double load = serverLoadTime(s, r, t) - data.serverLoadLimits(s, r);
				serverLoad[s] += max(load, 0);
			}
		}
	}
    
	int min = 0;
	int max = 0;
	for(int s = 0; s < data.numberOfServers(); s++) {
		if(serverLoad[s] < serverLoad[min]) {
			min = s;
		}
		if(serverLoad[s] > serverLoad[max]) {
			max = s;
		}
	}
	int *fullServer = new int[data.numberOfServers()];
	int *emptyServer = new int[data.numberOfServers()];
	int *emptyDisk = new int[data.numberOfDiscs()];
	int *fullDisk = new int[data.numberOfDiscs()];
	emptyServer[0] = 0;
    fullServer[0] = 0;
	double load = (serverLoad[max] - serverLoad[min]) / 2;
    load = 0;
	for(int s = 0; s < data.numberOfServers(); s++) {
		if(serverLoad[s] <= serverLoad[min] + load) {
			emptyServer[++emptyServer[0]] = s;
		}
        if(serverLoad[s] >= serverLoad[max] - load) {
            fullServer[++fullServer[0]] = s;
        }
	}
    
	int maxServer = fullServer[1 +rand() % fullServer[0]];
	int minServer = emptyServer[1 +rand() % emptyServer[0]];
	
	for(int d = 0; d < data.numberOfDiscs(); d++) {
		if(preLocation.get(d) == minServer && preLocation.canEjection(d) && preLocation.canInsert(d, maxServer)) {
			emptyDisk[++emptyDisk[0]] = d;
		}
		if(preLocation.get(d) == maxServer && preLocation.canEjection(d) && preLocation.canInsert(d, minServer)) {
			fullDisk[++fullDisk[0]] = d;
		}
	}
	Location curLocation(preLocation);
	int maxDisk = fullDisk[rand() % fullDisk[0] + 1];
	int minDisk = emptyDisk[rand() % emptyDisk[0] + 1];
	
    curLocation.set(maxDisk, minServer);
    curLocation.set(minDisk, maxServer);
		
	delete []fullDisk;
	delete []emptyDisk;
	delete []fullServer;
	delete []emptyServer;
	delete []serverLoad;
    delete []serverLoadTime;
	return curLocation;

};
int SmartSwap::getLength() {
    return (data.numberOfDiscs());
}