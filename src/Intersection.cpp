#include "Intersection.h"
#include <SPI.h>                   // required by BnrOne.cpp
#include <stdlib.h>
#include <BnrOneA.h>
#include "Robot.h"
#include "Pitches.h"

void insertNewLineSignature(String& lineSignaturesBuffer, char newLineSignature)
{
	lineSignaturesBuffer = lineSignaturesBuffer.substring(1,5)+newLineSignature;
}

Intersection::Intersection()
{
	_intersectionType = NONE;
}

void Intersection::resetIntersection()
{
	for (int i = 0; i < 5 ; i++)
	{
		getIntersectionType('N'); // reseting the lineSignaturesBuffer	
	}
}

MoveType Intersection::checkIntersection()
{
	switch (_intersectionType)
	{
		case NONE:
			return MOVE_NORMAL;
			break;
		case LINE:
			return MOVE_NORMAL;
			break;
		case DEAD_END:
			tone(9, NOTE_C5 ,50);
			return MOVE_TURN_ARROUND;
			break;
		case CROSS:
		case T_JUNCTION:
		case LEFT_TURN:
		case LEFT_STRAIGHT:
			tone(9, NOTE_C4 ,50);
			return MOVE_LEFT;
			break;
		case RIGHT_TURN:
			tone(9, NOTE_C3 ,50);
			return MOVE_RIGHT;
			break;
		case RIGHT_STRAIGHT:
			tone(9, NOTE_G3 ,50);
			return MOVE_FORWARD;
			break;
		default:
			//tone(9, NOTE_C2 ,1000/4);
			return MOVE_STOP;
			break;
	}
}

MoveType Intersection::checkIntersectionInPath(Path& shortestPath)
{
	MoveType newMove;
	String tempShortestPath = shortestPath.getPath();
	
	switch (tempShortestPath[0])  //LRFB
	{
		case 'B':
			newMove = MOVE_TURN_ARROUND;
			break;
		case 'L':
			newMove = MOVE_LEFT;
			break;
		case 'R':
			newMove = MOVE_RIGHT;
			break;
		case 'F':
			newMove = MOVE_FORWARD;
			break;
		default:
			newMove = MOVE_NORMAL;
			break;
	}
	tempShortestPath.remove(0,1);
	shortestPath.setPath(tempShortestPath);
	return newMove;
}

void Intersection::getIntersectionType(char lineSignature)
{
	static String lineSignaturesBuffer="NNNNN";
	_intersectionType=NONE;

	insertNewLineSignature(lineSignaturesBuffer,lineSignature);
	
	// N - None
	// T - Track (line)
	// R - Right
	// L - Left
	// B - Black
	
	if (lineSignaturesBuffer.substring(2,5)== "TNN") _intersectionType = DEAD_END;
	//lineSignaturesBuffer.substring(2,5))
	else if (lineSignaturesBuffer.substring(2,5)== "TBT") _intersectionType = CROSS;
	else if (lineSignaturesBuffer.substring(2,5)== "TBN") _intersectionType = T_JUNCTION;
	else if (lineSignaturesBuffer.substring(2,5)== "TRN") _intersectionType = RIGHT_TURN;
	else if (lineSignaturesBuffer.substring(2,5)== "TLN") _intersectionType = LEFT_TURN;
	else if (lineSignaturesBuffer.substring(2,5)== "TRT") _intersectionType = RIGHT_STRAIGHT;
	else if (lineSignaturesBuffer.substring(2,5)== "TLT") _intersectionType = LEFT_STRAIGHT;
	//lineSignaturesBuffer.substring(1,5)
	else if (	lineSignaturesBuffer.substring(1,5) == "TLBT" ||
				lineSignaturesBuffer.substring(1,5) == "TRBT" ||
				lineSignaturesBuffer.substring(1,5) == "TBRT" ||
				lineSignaturesBuffer.substring(1,5) == "TBLT" )
			_intersectionType = CROSS;
	else if (	lineSignaturesBuffer.substring(1,5) == "TBLN" ||
				lineSignaturesBuffer.substring(1,5) == "TBRN" ||
				lineSignaturesBuffer.substring(1,5) == "TLBN" ||
				lineSignaturesBuffer.substring(1,5) == "TRBN" )
			_intersectionType = T_JUNCTION;
	/*else if ( lineSignaturesBuffer.substring(1,5) == "TRTN" ) 
			_intersectionType = RIGHT_TURN;
	else if ( lineSignaturesBuffer.substring(1,5) == "TLTN" ) 
			_intersectionType = LEFT_TURN;*/
	//lineSignaturesBuffer
	else if (	lineSignaturesBuffer == "TLBLT" ||
				lineSignaturesBuffer == "TLBLT" ||
				lineSignaturesBuffer == "TLBRT" ||
				lineSignaturesBuffer == "TRBRT") 
			_intersectionType = CROSS;
	else if (	lineSignaturesBuffer == "TLBRN" ||
				lineSignaturesBuffer == "TRBRN" ||
				lineSignaturesBuffer == "TRBLN" ||
				lineSignaturesBuffer == "TLBLN" ) 
			_intersectionType = T_JUNCTION;
	else if ( lineSignaturesBuffer.substring(4,5) == "T" ) 
			_intersectionType = LINE;
}
