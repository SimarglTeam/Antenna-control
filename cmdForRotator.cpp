#include "cmdForRotator.h"

void cmdForRotator::connectToPort() {
	tty.Connect(L"COM1", 9600); //Connecting to port "COM1", speed of port: 9600
}

void cmdForRotator::turnToTheRight() {
	data.push_back('R');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::turnToTheLeft() {
	data.push_back('L');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::turnToTheUp() {
	data.push_back('U');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::turnToTheDown() {
	data.push_back('D');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::stopAzimuthRotation() {
	data.push_back('A');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::stopElevationRotation() {
	data.push_back('E');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::stopCurrentCommand() {
	data.push_back('S');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::returnCurrentAzimuth() {
	data.push_back('C');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::returnCurrentElevation() {
	data.push_back('B');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::returnAzimuthAndElevation() {
	data.push_back('C2');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::selectAzimuthSpeed(int n) {
	data.push_back('C');
	data.push_back(n);
	tty.Write(data);
	data.pop_back();
	data.pop_back();
}

void cmdForRotator::turnToAzimuth(int azimuth) {
	data.push_back('M');
	data.push_back(azimuth);
	tty.Write(data);
	data.pop_back();
	data.pop_back();
}

void cmdForRotator::timedTrackingRotation(int time, int currentCoord, int nextCoord) {
	data.push_back('M');
	data.push_back(time);
	data.push_back(currentCoord);
	data.push_back(nextCoord);
	tty.Write(data);
	for (int i = 0; i < data.size(); i++) {
		data.pop_back();
	}
}

void cmdForRotator::automaticSteppingRoutine() {
	data.push_back('T');
	tty.Write(data);
	data.pop_back();
}

void cmdForRotator::returnNumberOfCurrentlyPoint() {
	data.push_back('N');
	tty.Write(data);
	data.pop_back();
}