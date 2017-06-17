// NonLinearControl.h

#ifndef _NONLINEARCONTROL_h
#define _NONLINEARCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class NonLinearControl
{
 public:
	int _error; //!< the diference of the detected line to the center of the line sensor
	
	//! sets the error to 0
	void init();
	
	//! Calculates the speed reduction to be applied
    /*!
      \param refSpeed the reference speed of the robot
      \return the speed to be added/subtracted to each motor
    */
	int calculateSpeedDif(int refSpeed);
};

#endif

