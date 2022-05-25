#pragma once
#include "tty.h"

class cmdForRotator {
private:
	std::vector<unsigned char> data; //Current data which will send to rotator

public:
	TTY tty; //A variable containing functions for working with the com-port
	void connectToPort();


	void turnToTheRight(); //[R] command
						   //Start turning the rotator to the right.

	void turnToTheLeft(); //[L] command
						  //Start turning the rotator to the left.

	void turnToTheUp(); //[U] command
						//Start turning the rotator to the up.

	void turnToTheDown(); //[D] command
						  //Start turning the rotator to the down.

	void stopAzimuthRotation(); //[A] command
								//Stop azimuth rotation. (A)

	void stopElevationRotation(); //[E] command
								  //Stop elevation rotation.

	void stopCurrentCommand(); //[S] command
							   //Stop: cancel current command before completion.

	void returnCurrentAzimuth(); //[C] command
								 //Return current azimuth angle in the form “ + 0nnn” degrees.

	void returnCurrentElevation(); //[B] command
								   //Return current elevation angle in the form “ + 0nnn” degrees. 

	void returnAzimuthAndElevation(); //[C2] command
									  //Return azimuthand elevation(“ + 0aaa + 0eee”, 
									  //where aaa = azimuth, eee = elevation). 

	void selectAzimuthSpeed(int); //[Xn] command
							   //Select azimuth rotator turning speed, where n = l (slowest)
							   //to 4 (fastest).This command can be issued during rotation,
							   //and takes effect immediately.There is no equivalent for elevation. 

	void turnToAzimuth(int); //[Maaa] command
						  //Turn to “aaa” degrees azimuth, where aaa is three digits between “000” and “360 or 450: 
						  //vary according to controller type.” Rotation starts. (Maaa)

	void timedTrackingRotation(int, int, int); //[Msss aaa bbb ccc ...] command
								  //This command stores the time value sss seconds to wait 
								  //between stepping from azimuth aaa to bbb, and then to ccc, etc.

	void automaticSteppingRoutine(); //[T] command
									 //Start automatic stepping routine both azimuthand eievation:
									 //turn rotator to next sequentially memorized azimuth,
									 //wait sss seconds, and turn to next angle (or pair), etc.
									 //This command works only if a longform [M] or [W]
									 //has been issued since power-up or the lastreset.

	void returnNumberOfCurrentlyPoint(); //[N] command
										 //Return serial number of currently selected memorized point
										 //[nnnn] , and total number of memorized points[mmmm],
										 // //in the form + nnnn + mmmm.Must be proceeded by either
										 //a long - form[M] or [W], and a T command. Used only during stepping (see [T] command).

	//---------------------------------------------------------------------------------
							//Elevation control commands (Uncompleted)

	void turnToAzimuthAndElevation(); //[Waaa eee] command
									  //Turn to aaa degrees azimuth and eee degrees elevation,
									  //where aaa is three digits between “000” and “360 or
									  //450: vary according to controller type, ”and eee is three
									  //digits between “000”and “180.” Rotators respond immediately.

	void automaticTurnToAzimuthAndElevation(); //[Wsss aaa eee aaa sss ...] command
											   //This command is similar to the [M] command: the first parameter is a time interval,
											   //and succeeding parameters are angles. With this command, however, angles are in azimuthelevation pairs,
											   //each pair representing one antenna location. At most “1900” pairs can be sentand stored in the
											   //Control Interface.As with the other commands, the time interval range is limited to “001” to “999”(seconds),
											   //azimuth to “000” to “360 or 450: vary according to controller type, ”and elevation to “000” to “180.”
											   
	//When this command is sent, the rotators turn to the first
	//aaa azimuth parameterand the first eee elevation parameter, and wait for a subsequent[T] command to begin the
	//actual stepping(to the next azimuth - elevation pair).Stored
	//values remain in effect until another[W] command is issued(this may have no parameters, in which case the “ ? > ”
	//error prompt is returned, but memories are still cleared), or
	//until the controller is turned off or by toggling the GS232A off and on.
};