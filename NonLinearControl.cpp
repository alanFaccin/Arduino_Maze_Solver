#include "NonLinearControl.h"
#include <math.h>

void NonLinearControl::init()
{
	_error = 0;
}
 
int NonLinearControl::calculateSpeedDif(int refSpeed)
{
	int speedDif=0;
	if (_error < -2500 || _error > 2500) speedDif = refSpeed;
	else
	{
		double rads = (double(_error)-2500.0)/796.0+1.57;
		double speedDifDouble = refSpeed/2+sin(rads)*refSpeed/2;
		speedDif = int(speedDifDouble);
	}
	if (_error < 0) speedDif*=(-1);
	return speedDif;
}


