#ifndef INTERSECTION_H
#define INTERSECTION_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Path.h"

//! Intersection Types
enum IntersectionType{
  NONE,
  DEAD_END,
  CROSS,
  T_JUNCTION,
  RIGHT_TURN,
  LEFT_TURN,
  RIGHT_STRAIGHT,
  LEFT_STRAIGHT,
  LINE
};

class Intersection
{
	public:
	
	//!default constructor
	Intersection();
	
	//!operators overload
	inline bool operator==(const IntersectionType& rhs) const { return _intersectionType==rhs; }
	inline void operator=(const Intersection& rhs) { _intersectionType=rhs._intersectionType; }
		
	//!Sets the type of intersection
	inline void setType(const IntersectionType& type){_intersectionType = type;};
	
	//! Retrieves the type of intersection
	inline IntersectionType getType() const {return _intersectionType;};
	
	//! resets intersection
	void resetIntersection();
	
	//! Retrieves the type of movement to be performed after a given intersection type been recognized
	/*!
		\param intersectionType one of the recognized types or NONE otherwise
		\return the type of movement to be performed by the robot (e.g. rotate 90º to the left)
	*/	
	MoveType checkIntersection();

	//! Retrieves the next movement of the shortest path to be performed after recognising any valid intersection
	/*!
		\param intersectionType one of the recognized types or NONE otherwise
		\param shortestPath the shortest path computed after the exploration step
		\return the type of movement to be performed by the robot (e.g. rotate 90º to the left)
	*/
	MoveType checkIntersectionInPath(Path &shortestPath);

	//! Sets the intersection type after successfully recognizing a sequence of line signatures
	/*!
		\param lineSignature the current line type (e.g. line, turn right, turn left) observed by the line sensors
		\param lineBin the corresponding binary conversion
	*/
	void getIntersectionType(char lineSignature);
	
	IntersectionType _intersectionType; //!< the Type
};

#endif /* INTERSECTION_H */
