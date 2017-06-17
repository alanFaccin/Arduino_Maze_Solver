#ifndef PIDCONTROL_H
#define PIDCONTROL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*! A test class */
class PIDControl
{
  public:
  	//! creates a PID control object
    PIDControl();
	
	//! reset function 
	/*!
        sets the m_error, m_last_error and m_integral to zero
    */
    void reset();
	
	//! calculates the differential speed to be sent to motors
    /*!
      \param speedRobot the current reference speed
      \return the value to be added/subtracted to the speed of left/right motors
    */
    int move(int speedRobot);
	
	//! sets the Kp value	
	inline void setKp(const int& KpValue) {m_Kp = KpValue;} ;
	//! sets the Ki value
	inline void setKi(const int& KiValue) {m_Ki = KiValue;} ;
	//! sets the Kd value
	inline void setKd(const int& KdValue) {m_Kd = KdValue;} ;
	//! retrieves the stored Kp value
	inline int getKp() const {return m_Kp;} ;
	//! retrieves the stored Ki value
	inline int getKi() const {return m_Ki;} ;
	//! retrieves the stored Kd value
	inline int getKd() const {return m_Kd;} ;	
	
	int m_error;				//!< the current error value
  private:
    int m_Kp;					//!< Proportional gain (use values between 0 and 100)
    int m_Ki;					//!< Integral gain(use values between 0 and 100)
    int m_Kd;					//!< Differential gain(use values between 0 and 100)
	unsigned int m_last_error;	//!< Previous error value
    int m_integral;				//!< Accumulated integral value 
};

#endif /* PIDCONTROL_H */
