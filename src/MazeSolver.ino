#include <EEPROM.h>
#include <SPI.h>                   // required by BnrOne.cpp
#include <BnrOneA.h>
#include <stdlib.h>
#include "Robot.h"
#include "NonLinearControl.h"
#include "IntersectionName.h"
#include "Intersection.h"
#include "Line.h"
#include "Path.h"
#include "Pitches.h"
#include "Music.h"

// Ideal Parameters: Speed 40
// Pause: 300

MoveType robotMove = MOVE_NORMAL; //! the type of Movement the robot is doing
Robot myRobot;			//! the main Robot object
int detectFinish=0;		//! flag to signal the end of the Maze

//! Print intersection in LCD
void printIntersection(IntersectionType intersectionType, MoveType robotMove)
{
	if (robotMove != MOVE_NORMAL)
	{
		myRobot._one.lcd1(intersectionStr[intersectionType]);
	}
}

//! Print path in LCD
/*!
	\param path to be printed
	\param lcd line where path is to be printed
*/	
void printPath(String path, int lcd)
{
	char printThePath[path.length()+1];
	for (unsigned int i=0 ; i < path.length() ; i++)
	{
		printThePath[i] = path[i];
	}
	printThePath[path.length()] = '\0';
	if (lcd == 1) 
	{
		myRobot._one.lcd1(printThePath);
	}
	else
	{
		 myRobot._one.lcd2(printThePath);
	}
}

//! Check if robot is at Finish line
bool isFinish (int &detectFinish)
{
	detectFinish++;
	if (detectFinish>=((110-myRobot._speed)/10))
	{
		return true;
	}
	return false;
}

// prints a count dounw in lcd2
void printCountDown()
{
	myRobot._one.lcd2("*****  3  ******");
	delay(500);
	myRobot._one.lcd2("*****  2  ******");
	delay(500);
	myRobot._one.lcd2("*****  1  ******");
	delay(500);
	myRobot._one.lcd2("***** GO! ******");
	delay(100);
}
// Print info on lcd: Exploring Maze or Direct to Goal
void printStep(bool mazeExplored)
{
	if (!mazeExplored)
		myRobot._one.lcd1(" Exploring Maze ");
	else
		myRobot._one.lcd1(" Shortest Path  ");
	printCountDown();
}

//! Setup functions call
void setup()
{
	Serial.begin(57600);
	myRobot.init();
	printStep(false);
}

//! main loop function
void loop()
{
	//variables declarations
	int button=0;
	Line theLine;
	Intersection intersection;
	Intersection previousItersection;
	Path exploredPath;
	Path shortestPath;
	bool mazeExplored = false;
	
	while(true)
	{
		// read line pattern
		myRobot._nonLinearControl._error = myRobot.readLineSensors(theLine.line) - 3500; //half of maximum value
		theLine.lineADConvert();
		theLine.setSignature();
		robotMove = MOVE_NORMAL;
		
		// Check if the line signature is different from the previous or equal to N
		if ( theLine.lineSignature != theLine.previousLineSignature || 
			theLine.lineSignature =='N')
		{
			intersection.getIntersectionType(theLine.lineSignature);
			robotMove = intersection.checkIntersection ();
			if (mazeExplored)
			{
				if (robotMove == MOVE_FORWARD ||
					robotMove == MOVE_LEFT ||
					robotMove == MOVE_RIGHT||
					robotMove == MOVE_TURN_ARROUND)
				robotMove = intersection.checkIntersectionInPath (shortestPath);
			}
			theLine.previousLineSignature=theLine.lineSignature;
		}
		
		// if the line is a black bar check if it is the finish line
		if (theLine.lineSignature == 'B')
		{
			if (isFinish(detectFinish)) 
			{
				myRobot._one.stop();
				myRobot._one.lcd2("----FINISHED!---");		// send info to lcd
				finishMusic();						// play finish music
				delay(3000);						// wait 3s
				printPath(exploredPath.getPath(),1);// show explored path on lcd
				shortestPath.getShortestPath(exploredPath);
				printPath(shortestPath.getPath(),2);// show shortest path on lcd
				mazeExplored = !mazeExplored;		// toggle flag
				while (button==0) button=myRobot._one.readButton(); // wait for button press
				myRobot.Menu();						// show Menu
				printStep(mazeExplored);
				intersection.resetIntersection();	// reset intersection
				detectFinish=0;						// reset finish flag
				exploredPath.setPath("");			// reset explored path
				robotMove = MOVE_NORMAL;
				continue;
			}
		}
		else
		{
			detectFinish=0;
		}
		
		// check if any button was pressed
		button=myRobot._one.readButton();
		if (button)
		{
			myRobot._one.stop();
			myRobot.Menu();
			printStep(mazeExplored);
			intersection.resetIntersection();
			exploredPath.setPath("");
			robotMove = MOVE_NORMAL;
			continue;
		}
		else
		{
			if (myRobot._debug) // check debug mode
			{
				printIntersection(intersection._intersectionType,robotMove);
				myRobot._one.stop();
                                char* emptyString="        ";
				myRobot._one.lcd2 (theLine.lineBin,(unsigned char*)emptyString);
			}
			else
			{
				if(!myRobot.areThereObstacles()) // Check for obstacles
				{
					// detect a dead end
					if (intersection == NONE && previousItersection == DEAD_END)
					{
						robotMove = MOVE_TURN_ARROUND;
						intersection.setType(DEAD_END);
					}
					myRobot.sendToMotors(robotMove, theLine.lineSignature);
				}
			}
		}
		previousItersection = intersection;
		exploredPath.updatePath(robotMove);	
	}
}
