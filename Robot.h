#ifndef ROBOT_H
#define ROBOT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "NonLinearControl.h"
#include <BnrOneA.h>
#include "Intersection.h"

class Robot
{
  public:
    //! creates an instance of the class Robot
    Robot();
	
	//! Configures the robot to be used with Bot'n Roll One
    /*!
      Reads saved configuration values (e.g. speed and other parameters) from the EEPROM
      Writes a welcome message to the LCD
	  Launches the Menu
    */
    void init();
    
	//! Reads IR obstacles sensors and sends commands to motors avoiding obstacles
	/*!
	  \return true if obstacles detected, false otherwise
	*/
	bool areThereObstacles();
	
	//! Sends commands to motors
    /*!
      \param robotMove the type of movement to be performed
    */
	void sendToMotors(MoveType robotMove, char lineSignature);
		
	//! Writes an integer to the EEPROM
    /*!
      \param p_address the address where the value is to be written
      \param p_value the value to be written
    */
    void EEPROMWriteInt(int p_address, int p_value);
	
	//! Reads an integer from the EEPROM
    /*!
      \param p_address the address from where the value is to be read from
      \return the value read
    */
    unsigned int EEPROMReadInt(int p_address);
	
	//! Reads all the saved values from the EEPROM (e.g. speed and other parameters) 
    void writeEEPROM();
	
	//! Stores all the relevant values on the EEPROM (e.g. speed and other parameters) 
    void readEEPROM();
    
    //! Read the calibrated line Sensor
    void readQTR8A(unsigned int* line);
	
    //! Read the line Sensor
	int readLineSensors(unsigned int* sensor_values);
    
    //! Launches the Menu for User Interface
    void Menu();

    BnrOneA _one;					//!< the interface to the Bot'n Roll One A 
    int _speed;						//!< the reference speed of the robot
	int _leftWheelSpeed;			//!< the left wheel speed
	int _rightWheelSpeed;			//!< the right wheel speed
    bool _debug;					//!< when true sends debug messages to LCD/Serial interface
	int _pause;						//!< the pause in milliseconds for 90º fixed turnings 
	NonLinearControl _nonLinearControl; //!< Non-linear control values
};

#endif /* ROBOT_H */
