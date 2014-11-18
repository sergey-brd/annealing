//
//  annealing.cpp
//  annealing
//
//  Created by Сергей Иванов on 08.04.14.
//
//

#include "annealing.h"
#include "location.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <cmath>
#include "neighborhood.h"

#include "swap.h"
#include "move.h"

#include "smartSwap.h"
#include "smartMove.h"

#include "assignment.h"

#include "back.h"
#include <iostream>

Annealing::Annealing(Data &_data): data(_data){
    //data = _data;
}

Location Annealing::find(double startingTemperature, double constCooling, Neighborhood &neighborhood,
                         int frozen, double length, Location startLocation) {
    
    Location preLocation = startLocation;
	Location curLocation = startLocation;
	Location resultLocation(data);

	int i;
	double temperature;
	double delta = 0;
	double curObjectiveFunction;
	double preObjectiveFunction;
	double resultObjectiveFunction;
	
	
	srand((unsigned)time(0));
	preObjectiveFunction = preLocation.calc();
    curObjectiveFunction = curObjectiveFunction;
	resultObjectiveFunction = resultLocation.calc();
    
	temperature = startingTemperature;

    int count = 0;

	while(count < frozen) {
        //curLocation = resultLocation;
        //curObjectiveFunction = resultObjectiveFunction;
		for(i = 0; i < length * neighborhood.getLength(); i++) {
            curLocation = neighborhood.generate(preLocation);
            curObjectiveFunction = curLocation.calc();
			delta = curObjectiveFunction - preObjectiveFunction;
            //std::cout<<delta<<std::endl;
            if(curLocation.allow()) {
                if(delta <= 0) {
                    preLocation = curLocation;
                    preObjectiveFunction = curObjectiveFunction;
                    if(preObjectiveFunction < resultObjectiveFunction) {
                        resultLocation = preLocation;
                        resultObjectiveFunction = preObjectiveFunction;
                        //std::cout<<count<<std::endl;
                        count = 0;
                        std::cout<<resultObjectiveFunction<<std::endl;

                    }
                } else {
                    if(1.0 * rand() / RAND_MAX < exp(- delta / temperature)) {
                        preLocation = curLocation;
                        preObjectiveFunction = curObjectiveFunction;
                    }
                }
            } else {
                //std::cout<<"error! "<<number<<std::endl;
                //return resultLocation;
            }
            //std::cout<<preObjectiveFunction<<std::endl;
		}
        count++;
        //std::cout<<count<<std::endl;
        //
        //std::cout<<600000<<std::endl;
        /*Assignment assignment(data, 10);
        for(int i = 0; i < 10; i++) {
            preLocation = assignment.generate(preLocation);
        }
        preObjectiveFunction = preLocation.calc();*/
		temperature *= constCooling;
        //if(count >= 10 && number == 0) {
        //    number++;
        //    startingTemperature
        //}
	}
    //std::cout<<"T = "<<temperature<<std::endl;

    //std::cout<<resultLocation.calc()<<std::endl;
    int a[] = {10, 1};
    for(int j = 0; j < 2; j++) {
        Assignment N(data, a[j]);
        for(int i = 0; i < 2000; i++) {
            //std::cout<<resultLocation.calc()<<" "<<resultLocation.allow()<<std::endl;
            resultLocation = N.generate(resultLocation);
        }
    }
    resultObjectiveFunction = resultLocation.calc();
    //std::cout<<resultLocation.calc()<<std::endl;

	return resultLocation;
}

Location Annealing::find() {
    Move move(data);
    double startingTemperature = 1000;
    double constCooling = 0.97;
    int frozen = 10;
    double length = 2;
    return find(startingTemperature, constCooling, move, frozen, length, Location(data));
}