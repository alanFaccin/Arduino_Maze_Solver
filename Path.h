#ifndef PATH_H
#define PATH_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//! Admissible movements
enum  MoveType {MOVE_STOP,MOVE_STRAIGHT,MOVE_NORMAL,MOVE_RIGHT,MOVE_FORWARD,MOVE_LEFT, MOVE_TURN_ARROUND};
	
class Path
{
	public:
	//! retrieves the path
	String getPath();
	
	//! sets the path
	void setPath(String newPath);
	
	//! inserts a newMove to the path
	void updatePath(MoveType newMove);
	
	//! calculates and retrieves the shortest path from the given exploredPath
	void getShortestPath(Path& exploredPath);
	
	private:
	String _path; //!< the path is saved in a String format
};

#endif
