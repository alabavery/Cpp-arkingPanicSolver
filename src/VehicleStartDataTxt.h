/*
 * VehicleStartDataTxt.h
 *
 *  The text file that is used to construct this class is a numeric
 *  description of the starting positions of the vehicles for a given level
 *  of Parking Panic.  The parking lot is divided into a grid of 36 squares
 *  numbered 0 through 35.  A vehicle's starting position is then described
 *  by the numbers of the squares it occupies.  In the text file, each line
 *  represents a vehicle.
 *
 *  Example:
 *
 *  13 14
 *  0 1
 *  5 11 17
 *  6 12 18
 *  9 15 21
 *  24 30
 *  28 29
 *  32 33 34
 *
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
