/*
 * ArrangementNode.h
 *
 *  Created on: Dec 12, 2016
 *      Author: alavery
 */
#include <vector>
#include "Vehicle.h"


#ifndef ARRANGEMENTNODE_H_
#define ARRANGEMENTNODE_H_




class ArrangementNode {

private:

	vector< vector< vector<int> > > allAchievablePositions;

	static vector< vector<int> > visitedIndicesCombos;

	vector<int> squaresOccupationStatus;



	void setSquaresOccupationStatus(int changedVehicleIndex, int newPositionIndex);

	void setVehiclePositionIndices(int changedVehicleIndex, int newPositionIndex);

	void moveVehicle(int changedVehicleIndex, int newPositionIndex);



	bool testMove(int changedVehicleIndex, int moveDirection);

		bool testForVisited(int changedVehicleIndex, int newPositionIndex);

		bool testPositionIndexIsValid(vector< vector<int> > changedVehiclesPositions, int newPositionIndex);

		bool testForOccupation(vector< vector<int> > changedVehiclesPositions, int newPositionIndex, int moveDirection);



	ArrangementNode returnNewArrangementNode(int changedVehicleIndex, int moveDirection);

	vector<int> returnInfoForNextMove();




public:
	vector<int> vehiclePositionIndices;

	string positionIndicesToString();

	static vector< vector<int> > vehiclePositionIndicesStack;

	ArrangementNode(vector< vector< vector<int> > > allAchievablePositions, vector<int> vehiclePositionIndices);

	vector<int> getSqrOccStatusFromPositionIndices(vector<int> vehiclePositionIndices);


	ArrangementNode returnNextArrangement();

	void printNode();

	int level;

	vector<int> parentPositionIndices;
	vector<int> parentSquaresOccupationStatus;
};








vector<int> returnInitialSquaresOccupationStatus(vector< vector<int> > vehicleStartPositions);

vector<int> returnInitialVehiclePositionIndices(vector<Vehicle> vehicles);

vector< vector<int> > returnUnoptimizedSequenceOfPositionIndices(vector< vector< vector<int> > > allAchievablePositions, vector<int> initialVehiclePositionIndices);

#endif /* ARRANGEMENTNODE_H_ */
