//
//  data.cpp
//  annealing
//
//  Created by Сергей Иванов on 02.04.14.
//
//

#include "data.h"
#include <iostream>
#include <fstream>

Data::Data(std::string name) {
	std::ifstream file(name.c_str());
	if(!file.is_open()) {
		std::cerr<<"Can't open file " + name << std::endl;
		exit(0);
	}
	file>>_numberOfDiscs>>_numberOfServers>>_numberOfCharacteristics>>_periodTime;
	_serverLoadLimits = std::vector<std::vector<double>>(_numberOfServers, std::vector<double>(_numberOfCharacteristics, 0));
	_insertLimits = std::vector<std::vector<double>>(_numberOfServers, std::vector<double>(_numberOfCharacteristics, 0));	_ejectionLimits = std::vector<std::vector<double>>(_numberOfServers, std::vector<double>(_numberOfCharacteristics, 0));
	_discLoad =	std::vector<std::vector<std::vector<double>>>(_numberOfDiscs, std::vector<std::vector<double>>(_numberOfCharacteristics, std::vector<double>(_periodTime, 0)));
	_insertionCosts = std::vector<std::vector<std::vector<double>>>(_numberOfServers, std::vector<std::vector<double>>(_numberOfDiscs, std::vector<double>(_numberOfCharacteristics, 0)));
	_ejectionCosts = std::vector<std::vector<std::vector<double>>>(_numberOfServers, std::vector<std::vector<double>>(_numberOfDiscs, std::vector<double>(_numberOfCharacteristics, 0)));

	_initLocation =	std::vector<int>(_numberOfDiscs);
	_curLocation =	std::vector<int>(_numberOfDiscs);

	for(int s = 0; s < _numberOfServers; s++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			file>>_serverLoadLimits[s][r];
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			file>>_insertLimits[s][r];
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			file>>_ejectionLimits[s][r];
		}
	}
	for(int d = 0; d < _numberOfDiscs; d++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			for(int t = 0; t < _periodTime; t++) {
				file>>_discLoad[d][r][t];
			}
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int d = 0; d < _numberOfDiscs; d++) {
			for(int r = 0; r < _numberOfCharacteristics; r++) {
				file>>_insertionCosts[s][d][r];
			}
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int d = 0; d < _numberOfDiscs; d++) {
			for(int r = 0; r < _numberOfCharacteristics; r++) {
				file>>_ejectionCosts[s][d][r];
			}
		}
	}
	for(int d = 0; d < _numberOfDiscs; d++) {
		file>>_initLocation[d];
		_initLocation[(d)] -= 1;
	}
	if(file.peek() != std::ifstream::traits_type::eof()) {
		for(int d = 0; d < _numberOfDiscs; d++) {
			file>>_curLocation[d];
			_curLocation[(d)] -= 1;
		}
	} else {
		for(int d = 0; d < _numberOfDiscs; d++) {
			_curLocation[(d)] = _initLocation[(d)];
		}
	}
	
}
    
int Data::numberOfDiscs() {
	return _numberOfDiscs;
};
int Data::numberOfServers() {
	return _numberOfServers;
};
int Data::numberOfCharacteristics() {
	return _numberOfCharacteristics;
};
int Data::periodTime() {
	return _periodTime;
};
double Data::serverLoadLimits(int s, int r) {
	return _serverLoadLimits[s][r];
};
double Data::insertLimits(int s, int r) {
	return _insertLimits[s][r];
};
double Data::ejectionLimits(int s, int r) {
	return _ejectionLimits[s][r];
};
double Data::discLoad(int d, int r, int t) {
	return _discLoad[d][r][t];
};
double Data::insertionCosts(int s, int d, int r) {
	return _insertionCosts[s][d][r];
};
double Data::ejectionCosts(int s, int d, int r) {
	return _ejectionCosts[s][d][r];
};
int Data::initLocation(int d) {
	return _initLocation[d];
}
int Data::curLocation(int d) {
	return _curLocation[d];
}
void Data::dataOut() {
	std::cout<<_numberOfDiscs<<std::endl<<_numberOfServers<<std::endl<<_numberOfCharacteristics<<std::endl<<_periodTime<<std::endl;
	for(int s = 0; s < _numberOfServers; s++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			std::cout<<_serverLoadLimits[s][r]<<std::endl;
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			std::cout<<_insertLimits[s][r]<<std::endl;
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			std::cout<<_ejectionLimits[s][r]<<std::endl;
		}
	}
	for(int d = 0; d < _numberOfDiscs; d++) {
		for(int r = 0; r < _numberOfCharacteristics; r++) {
			for(int t = 0; t < _periodTime; t++) {
				std::cout<<_discLoad[d][r][t]<<std::endl;
			}
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int d = 0; d < _numberOfDiscs; d++) {
			for(int r = 0; r < _numberOfCharacteristics; r++) {
				std::cout<<_insertionCosts[s][d][r]<<std::endl;
			}
		}
	}
	for(int s = 0; s < _numberOfServers; s++) {
		for(int d = 0; d < _numberOfDiscs; d++) {
			for(int r = 0; r < _numberOfCharacteristics; r++) {
				std::cout<<_ejectionCosts[s][d][r]<<std::endl;
			}
		}
	}
	for(int d = 0; d < _numberOfDiscs; d++) {
		std::cout<<_initLocation[(d)]<<std::endl;
	}
	for(int d = 0; d < _numberOfDiscs; d++) {
		std::cout<<_curLocation[(d)]<<std::endl;
	}
}

