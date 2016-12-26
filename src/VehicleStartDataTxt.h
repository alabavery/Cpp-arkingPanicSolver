/*
 * VehicleStartDataTxt.h
 *
 *  Created on: Dec 19, 2016
 *      Author: alavery
 */

using namespace std;

#ifndef VEHICLESTARTDATATXT_H_
#define VEHICLESTARTDATATXT_H_

class VehicleStartDataTxt {
private:
	string txtFileName;
	vector< vector<int> > vehicleStartPositions;
	int numberOfVehicles;
	void addVehicleStartPosition(string sz_squaresOccupiedByVehicle);
	void incrementNumberOfVehicles();
public:
	VehicleStartDataTxt(string txtFileName);
	int getNumberOfVehicles();
	vector< vector<int> > getVehicleStartPositions();
};



#endif /* VEHICLESTARTDATATXT_H_ */
