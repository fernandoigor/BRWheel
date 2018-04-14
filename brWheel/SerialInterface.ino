#include "Config.h"
#include "debug.h"

//--------------------------------------------------------------------------------------------------------

u8 toUpper(u8 c)
{
	if ((c >= 'a') && (c <= 'z'))
		return(c + 'A' - 'a');
	return(c);
}

void readSerial() {
	if (CONFIG_SERIAL.available() > 0)
	{
		u8 c = toUpper(CONFIG_SERIAL.read());
		//DEBUG_SERIAL.println(c);
		int temp;
		switch (c) {
		case 'V':
			CONFIG_SERIAL.println("BRW Version-"+String(VERSION));
			break;
		case 'S':
			CONFIG_SERIAL.println("State-" + String(brWheelFFB.state));
			break;
		case 'R':
			brWheelFFB.calibrate();
			break;
		case 'C':
			myEnc.Write(ROTATION_MID);
			break;
		case 'G':
			temp = CONFIG_SERIAL.parseInt();
			temp = constrain(temp, 180, 900);
			ROTATION_MAX = (CPR / 360)*temp;
			brWheelFFB.offset = (MAX_ENCODER_ROTATION - ROTATION_MAX)/2;
			break;
		case 'F':
			c = toUpper(CONFIG_SERIAL.read());
			switch (c) {
			case 'G':
				temp = CONFIG_SERIAL.parseInt();
				configGeneralGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'C':
				temp = CONFIG_SERIAL.parseInt();
				configConstantGain = constrain(temp,0,200)/100.0;
				break;
			case 'D':
				temp = CONFIG_SERIAL.parseInt();
				configDamperGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'F':
				temp = CONFIG_SERIAL.parseInt();
				configFrictionGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'S':
				temp = CONFIG_SERIAL.parseInt();
				configSineGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'M':
				temp = CONFIG_SERIAL.parseInt();
				configSpringGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'I':
				temp = CONFIG_SERIAL.parseInt();
				configInertiaGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'A':
				temp = CONFIG_SERIAL.parseInt();
				configCenterGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'B':
				temp = CONFIG_SERIAL.parseInt();
				configStopGain = constrain(temp, 0, 200) / 100.0;
				break;
			case 'J':
				temp = CONFIG_SERIAL.parseInt();
				if (temp < MM_MAX_MOTOR_TORQUE)
				{
					MM_MIN_MOTOR_TORQUE = constrain(temp, 0, 399);
				}
				break;
			case 'K':
				temp = CONFIG_SERIAL.parseInt();
				if (temp > MM_MIN_MOTOR_TORQUE) 
				{
					MM_MAX_MOTOR_TORQUE = constrain(temp, 1, 400);
				}
				break;
			}
			break;
		}
	}
}

