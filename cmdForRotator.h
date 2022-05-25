#pragma once
#include "tty.h"

class cmdForRotator {
private:
	std::vector<unsigned char> data; 

public:
	TTY tty; 
	void connectToPort();

	void turnToTheRight(); 						   

	void turnToTheLeft(); 						  

	void turnToTheUp(); 						

	void turnToTheDown(); 						  

	void stopAzimuthRotation(); 								

	void stopElevationRotation(); 								  

	void stopCurrentCommand(); 							  

	void returnCurrentAzimuth(); 								 

	void returnCurrentElevation(); 								   

	void returnAzimuthAndElevation(); 

	void selectAzimuthSpeed(int); 

	void turnToAzimuth(int); 

	void timedTrackingRotation(int, int, int); 

	void automaticSteppingRoutine(); 

	void returnNumberOfCurrentlyPoint(); 
	
	void turnToAzimuthAndElevation(); 

	void automaticTurnToAzimuthAndElevation();
};