#include "Line.h"

Line::Line()
{
	lineSignature = 'N';
	previousLineSignature= 'N';
}

void Line::lineADConvert()
{
	for (int i=0; i<8; i++)
	{
		if (line[i]<100) lineBin[i]='0';		//white previous:100
		else if (line[i]>450) lineBin[i]='1';	//black previous:600
	}
}


bool Line::isEqualTo (unsigned char aLineBin[8])
{
	for (int i=0; i<8; i++)
	{
		if (lineBin[i] != aLineBin[i]) return false;
	}
	return true;
}

void Line::setSignature ()
{
	unsigned char noLine[8]      = {'0','0','0','0','0','0','0','0'};

	unsigned char blackLine2[8]  = {'0','1','1','0','0','0','0','0'};
	unsigned char blackLine3[8]  = {'0','0','1','1','0','0','0','0'};
	unsigned char blackLine4[8]  = {'0','0','0','1','1','0','0','0'};
	unsigned char blackLine5[8]  = {'0','0','0','0','1','1','0','0'};
	unsigned char blackLine6[8]  = {'0','0','0','0','0','1','1','0'};
	
	unsigned char blackLine8[8]  = {'0','1','1','1','0','0','0','0'};
	unsigned char blackLine9[8]  = {'0','0','1','1','1','0','0','0'};
	unsigned char blackLine10[8] = {'0','0','0','1','1','1','0','0'};
	unsigned char blackLine11[8] = {'0','0','0','0','1','1','1','0'};
	
	unsigned char blackBar[8]   = {'1','1','1','1','1','1','1','1'};
	unsigned char leftTurn[8]   = {'1','1','1','1','1','1','1','0'};
	unsigned char leftTurn0[8]  = {'1','1','1','1','1','1','0','0'};
	unsigned char leftTurn1[8]  = {'1','1','1','1','1','0','0','0'};
	unsigned char leftTurn2[8]  = {'1','1','1','1','0','0','0','0'};
	unsigned char leftTurn3[8]  = {'1','1','1','0','0','0','0','0'};
	//unsigned char leftTurn4[8]  = {'1','1','0','0','0','0','0','0'};
	
	unsigned char rightTurn[8]  = {'0','1','1','1','1','1','1','1'};	
	unsigned char rightTurn0[8] = {'0','0','1','1','1','1','1','1'};
	unsigned char rightTurn1[8] = {'0','0','0','1','1','1','1','1'};
	unsigned char rightTurn2[8] = {'0','0','0','0','1','1','1','1'};
	unsigned char rightTurn3[8] = {'0','0','0','0','0','1','1','1'};
	//unsigned char rightTurn4[8]  = {'0','0','0','0','0','0','1','1'};
		
	if (isEqualTo(blackBar)) lineSignature = 'B';
	else if (isEqualTo(noLine)) lineSignature = 'N';   //no line
	else if (isEqualTo(leftTurn)) lineSignature = 'L'; //left turn
	else if (isEqualTo(leftTurn0)) lineSignature = 'L';
	else if (isEqualTo(leftTurn1)) lineSignature = 'L';
	else if (isEqualTo(leftTurn2)) lineSignature = 'L';
	else if (isEqualTo(leftTurn3)) lineSignature = 'L';
	//else if (isEqualTo(lineBin,leftTurn4)) lineSignature = 'L';
	
	else if (isEqualTo(rightTurn)) lineSignature = 'R'; //right turn
	else if (isEqualTo(rightTurn0)) lineSignature = 'R';
	else if (isEqualTo(rightTurn1)) lineSignature = 'R';
	else if (isEqualTo(rightTurn2)) lineSignature = 'R';
	else if (isEqualTo(rightTurn3)) lineSignature = 'R';
	//else if (isEqualTo(lineBin,rightTurn4)) lineSignature = 'R';
	
	//else if (isEqualTo(lineBin,blackLine1)) lineSignature = 'T'; //on track
	else if (isEqualTo(blackLine2)) lineSignature = 'T';
	else if (isEqualTo(blackLine3)) lineSignature = 'T';
	else if (isEqualTo(blackLine4)) lineSignature = 'T';
	
	else if (isEqualTo(blackLine5)) lineSignature = 'T';
	else if (isEqualTo(blackLine6)) lineSignature = 'T';
	//else if (isEqualTo(blackLine7)) lineSignature = 'T';
	else if (isEqualTo(blackLine8)) lineSignature = 'T';
	else if (isEqualTo(blackLine9)) lineSignature = 'T';
	else if (isEqualTo(blackLine10)) lineSignature = 'T';
	else if (isEqualTo(blackLine11)) lineSignature = 'T';	
}

