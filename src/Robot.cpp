#include <SPI.h>                   // required by BnrOne.cpp
#include <EEPROM.h>
#include "Robot.h"

//constants definitions
#define SSPIN  2    //Slave Select (SS) pin for SPI communication
#define M1  1       //Motor1
#define M2  2       //Motor2

Robot::Robot():_speed(43),_leftWheelSpeed(0),_rightWheelSpeed(0),_debug(true),_pause(294)
{
	
}

void Robot::init()
{
	_one.spiConnect(SSPIN);
	_one.stop();              // stops all move
	delay(5);
	_one.lcd1(" Bot'n Roll ONE");
	_one.lcd2("www.botnroll.com");
	delay(500);

	readEEPROM();
	Menu();
	writeEEPROM();
	delay(100);
}

bool Robot::areThereObstacles()
{
	unsigned char obstacles=_one.obstacleSensors(); //Read obstacle sensors
	switch(obstacles)
	{
		case 0:   // no obstacles detected
			return false;
			break;
		case 1:   // obstacle detected on Left sensor
			_one.move(_speed,-_speed);  		// Rotate Right
			break;
		case 2:   // obstacle detected on Right sensor
			_one.move(-_speed,_speed);    // Rotate Left
			break;
		case 3:   // obstacle detected on both sensors
			_one.move(0,-_speed);   // Move Backwards Left
			delay(1000);
			break;
		default:
		break;
	}
	return true;
}

void Robot::sendToMotors(MoveType robotMove, char lineSignature)
{
	static int speedDif=0;
	
	switch (robotMove)
	{
		case MOVE_STRAIGHT:
			_one.lcd2("MOVE_STRAIGHT");
			_one.move (_speed*0.7,_speed*0.7);
			break;
		case MOVE_NORMAL:
			{
				speedDif=_nonLinearControl.calculateSpeedDif(_speed);
				constrain(speedDif, -_speed, _speed);
				if(speedDif < 0) _one.move(_speed+speedDif, _speed);
				else  _one.move(_speed, (_speed-speedDif));	
			}
			break;
		case MOVE_FORWARD:
			_one.lcd2("MOVE_FORWARD");
			break;
		case MOVE_LEFT:
			_one.move (-_speed,_speed);
			_one.lcd2("MOVE_LEFT");
			delay(_pause);
			break;
		case MOVE_RIGHT:
			_one.move (_speed,-_speed);
			_one.lcd2("MOVE_RIGHT");
			delay(_pause);
			break;
		case MOVE_TURN_ARROUND:
			_one.lcd2("MOVE_TURN_ARROUND");
			speedDif=_nonLinearControl.calculateSpeedDif(_speed);
			constrain(speedDif, -_speed, _speed);
			_one.move(speedDif, -speedDif);
			break;
		default:
			_one.lcd2("ERROR");
			_one.move (0,0);
			delay(_pause);
		break;
	}
}

void Robot::EEPROMWriteInt(int p_address, int p_value)
{
	unsigned char lowByte = ((p_value >> 0) & 0xFF);
	unsigned char highByte = ((p_value >> 8) & 0xFF);
	
	EEPROM.write(p_address, lowByte);
	EEPROM.write(p_address + 1, highByte);
}

unsigned int Robot::EEPROMReadInt(int p_address)
{
	unsigned char lowByte = EEPROM.read(p_address);
	unsigned char highByte = EEPROM.read(p_address + 1);
	
	return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void Robot::writeEEPROM()
{
	int initAddr=20;
	int debug = (_debug==true) ? 1: 0;
	EEPROMWriteInt(initAddr+0,debug);
	EEPROMWriteInt(initAddr+2,_speed);
	EEPROMWriteInt(initAddr+4,_pause);
}

void Robot::readEEPROM()
{
	int initAddr=20;
	int debug = EEPROMReadInt(initAddr);
	_debug = (debug==1) ? true : false;
	_speed=EEPROMReadInt(initAddr+2);
	_pause=EEPROMReadInt(initAddr+4);
}

void Robot::Menu()
{
	bool start_run=false;
        const int NUM_OPTIONS = 4;
        const int NUM_PARAMS = 2;
	int param[NUM_PARAMS]={_speed,_pause};
	int param_max[NUM_PARAMS]={101,1001};
	char menu_param[NUM_PARAMS+1][8]={"Speed: ","Pause:","Debug: "};
	char var_menu[NUM_OPTIONS][15]={ "1.Start Run", "2.Set speed", "3.Set Pause","4.Set debug" };
	int button=0, option=0;
	bool select=false;
	bool valuesChanged=false;
	while (!start_run)
	{
		int count = 0;
                const int debounce = 2;
		_one.lcd1("Menu:");
		_one.lcd2(" ");
		while((button=_one.readButton()));
		while (!select)
		{
			_one.lcd1("Menu:");
			_one.lcd2(var_menu[option]);
			while(!(button=_one.readButton()));
			switch (button)
			{
				case 1: --option; count=0;break;
				case 2: ++option; count=0;break;
				case 3: ++count;
				if (count >= debounce)  select=true ;
				break;
			}
			option=(NUM_OPTIONS+option)%NUM_OPTIONS;
			delay(400);
		}
		select=false;

		_one.lcd2("  ");
		switch (option)
		{
			case 0:
				_speed = param[0];
				_pause=param[1];
				_one.lcd1("Running ...");
				start_run = true;
				if (valuesChanged)	writeEEPROM();
			break;
			case 1:
			case 2:
				valuesChanged = true;
				count=0;
				_one.lcd1(menu_param[option-1]);
				while((button=_one.readButton()));
				while (!select)
				{
					_one.lcd1(menu_param[option-1],param[option-1]);
					while(!(button=_one.readButton()));
					switch (button)
					{
						case 1: ++(param[option-1]); count=0; break;
						case 2: --(param[option-1]); count=0; break;
						case 3: ++count;
						if (count >= debounce)  select=true ;
						break;
					}
					param[option-1]=(param_max[option-1]+param[option-1])%param_max[option-1];
					delay(50);
				}
			break;
			case 3:
				_debug=!(_debug);
				if (_debug==false) _one.lcd1("DEBUG: OFF "); else _one.lcd1("DEBUG: ON ");
				delay(1500);
			break;
		}
		select=false;
	}
}

void Robot::readQTR8A(unsigned int* line)
{
	for(int i=0;i<8;i++)
	{
		line[i]=_one.readAdc(i);
	}
}

int Robot::readLineSensors(unsigned int* sensor_values)
{
	unsigned char i, on_line = 0;
	unsigned long avg; // this is for the weighted total, which is long
	// before division
	unsigned int sum; // this is for the denominator which is <= 64000
	static int last_value=0; // assume initially that the line is left.
	
	readQTR8A(sensor_values);
	
	avg = 0;
	sum = 0;
	int _numSensors=8;
	for(i=0;i<_numSensors;i++) {
		int value = sensor_values[i];
		
		// keep track of whether we see the line at all
		if(value > 200) {
			on_line = 1;
		}
		// only average in values that are above a noise threshold
		if(value > 50) {
			avg += (long)(value) * (i * 1000);
			sum += value;
		}
	}
	
	if(!on_line)
	{
		// If it last read to the left of center, return 0.
		if(last_value < (_numSensors-1)*1000/2)
		return 0;
		
		// If it last read to the right of center, return the max.
		else
		return (_numSensors-1)*1000;
		
	}
	last_value = avg/sum;
	return last_value;
}
