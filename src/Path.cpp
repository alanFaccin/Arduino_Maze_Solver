#include "Path.h"

String Path::getPath()
{
	return _path;	
}

void Path::setPath(String newPath)
{
	_path = newPath;
}

void Path::updatePath(MoveType newMove)
{
	static MoveType previousMove = MOVE_STOP;
	char turn= 'N';  //'L'= LEFT,'F'= Forward,'R'=Right,'B'=Backwards};
	switch(newMove)
	{
		case MOVE_LEFT:
		turn= 'L';
		break;
		case MOVE_FORWARD:
		turn= 'F';
		break;
		case MOVE_RIGHT:
		turn= 'R';
		break;
		case MOVE_TURN_ARROUND:
		if (previousMove != MOVE_TURN_ARROUND)
		{
			turn= 'B';
		}
		break;
		default:
		turn= 'N';
		break;
	}
	previousMove = newMove;
	if (turn!='N')	_path = _path+turn;
}

void Path::getShortestPath(Path& exploredPath)
{
	_path = exploredPath._path;
	int Bindex=_path.indexOf('B');
	int count=0;
	int initialLenght=_path.length();

	while(	Bindex != (-1) &&
	Bindex != (_path.length()-1) &&
	_path.lastIndexOf('B')!=0)
	{
		_path.replace("LBF","R");
		_path.replace("LBL","F");
		_path.replace("FBL","R");
		_path.replace("FBF","B");
		_path.replace("RBL","B");
		_path.replace("FBR","L");
		_path.replace("LBR","B");
		
		_path.replace("RBF","L");
		_path.replace("RBR","F");
		_path.replace("BB","F");
		Bindex=_path.indexOf('B');
		count++;
		if (count>initialLenght)	break;
	}
}
