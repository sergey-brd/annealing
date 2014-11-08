//
//  data.h
//  annealing
//
//  Created by Сергей Иванов on 02.04.14.
//
//

#ifndef annealing_data_h
#define annealing_data_h
#include <string>
#include <vector>

class Data {
private:
	int _numberOfDiscs;				// D
	int _numberOfServers;			// S
	int _numberOfCharacteristics;	// R
	int _periodTime;					// T
    std::vector<std::vector<double>> _serverLoadLimits;		// c_s,r
	std::vector<std::vector<double>> _insertLimits;			// B^w_s,r
	std::vector<std::vector<double>> _ejectionLimits;			// B^e_s,r
    std::vector<std::vector<std::vector<double>>> _discLoad;				// c_d,r,t
    std::vector<std::vector<std::vector<double>>> _insertionCosts;			// b^w_s,d,r
    std::vector<std::vector<std::vector<double>>> _ejectionCosts;			// b^e_s,d,r
	std::vector<int> _initLocation;				// x^0
    std::vector<int> _curLocation;				// для решения
    //Data& operator=(const Data& right);
    //Data(Data &data);

public:
    Data(std::string name);
    void dataOut();
    int numberOfDiscs();
	int numberOfServers();
	int numberOfCharacteristics();
	int periodTime();
	double serverLoadLimits(int s, int r);
	double insertLimits(int s, int r);
	double ejectionLimits(int s, int r);
	double discLoad(int d, int r, int t);
	double insertionCosts(int s, int d, int r);
	double ejectionCosts(int s, int d, int r);
	int initLocation(int d);
    int curLocation(int d);
};



#endif
