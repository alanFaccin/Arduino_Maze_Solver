#ifndef LINE_H
#define LINE_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// N None
// B Black
// R Right
// L Left
// T Track

class Line
{
	public:
	//! class variables
	unsigned int line[8];
	unsigned char lineBin[8];
	char lineSignature;
	char previousLineSignature;
	
	//! default constructor
	Line();
	
	//! converts line analog information to digital bits
	void lineADConvert();
	
	//! set the signature based on LineBin
	void setSignature();
	
	//! retrieves true if lines are exactly equal
	bool isEqualTo(unsigned char aLineBin[8]);
};

#endif