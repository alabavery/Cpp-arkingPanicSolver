/*
 * ArrangementNode.h
 *
 *  Created on: Dec 12, 2016
 *      Author: alavery
 */
#include <vector>
#include "Vehicle.h"
using namespace std;

#ifndef ARRANGEMENTNODE_H_
#define ARRANGEMENTNODE_H_




class ArrangementNode {

private:

	vector< vector< vector<int> > > allAchievablePositions;

	static vector< vector<int> > visitedIndicesCombos;

	vector<int> vehiclePositionIndices;

	vector<int> squaresOccupationStatus;



	void setSquaresOccupationStatus(int changedVehicleIndex, int newPositionIndex);

	void setVehiclePositionIndices(int changedVehicleIndex, int newPositionIndex);

	void moveVehicle(int changedVehicleIndex, int newPositionIndex);



	bool testMove(int changedVehicleIndex, int moveDirection);

		bool testForVisited(int changedVehicleIndex, int newPositionIndex);

		bool testPositionIndexIsValid(vector< vector<int> > changedVehiclesPositions, int newPositionIndex);

		bool testForOccupation(vector< vector<int> > changedVehiclesPositions, int newPositionIndex, int moveDirection);



	ArrangementNode returnChildArrangementNode(int changedVehicleIndex, int moveDirection);

	vector<int> returnInfoForNextMove();




public:

	ArrangementNode(vector< vector< vector<int> > > allAchievablePositions, vector<int> vehiclePositionIndices, vector<int> squaresOccupationStatus);

	ArrangementNode returnNextArrangement();

	void printNode();

	ArrangementNode *parent;

	int level;

	ArrangementNode(vector<int> parentPositionIndices, vector<int> parentSquaresOccupationStatus, vector< vector< vector<int> > > allAchievablePositions, vector<int> vehiclePositionIndices, vector<int> squaresOccupationStatus);
	vector<int> parentPositionIndices;
	vector<int> parentSquaresOccupationStatus;
};








vector<int> returnInitialSquaresOccupationStatus(vector< vector<int> > vehicleStartPositions);

vector<int> returnInitialVehiclePositionIndices(vector<Vehicle> vehicles);



#endif /* ARRANGEMENTNODE_H_ */