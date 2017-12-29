/* Force Feedback Wheel

Copyright 2015  Etienne Saint-Paul  (esaintpaul [at] gameseed [dot] fr)
Copyright 2017  Fernando Igor  (fernandoigor [at] msn [dot] com)

Permission to use, copy, modify, distribute, and sell this
software and its documentation for any purpose is hereby granted
without fee, provided that the above copyright notice appear in
all copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name of the author not be used in
advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

The author disclaim all warranties with regard to this
software, including all implied warranties of merchantability
and fitness.  In no event shall the author be liable for any
special, indirect or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether
in an action of contract, negligence or other tortious action,
arising out of or in connection with the use or performance of
this software.
*/

#include "ffb.h"
#include "ffb_pro.h"
//#include "DualVNH5019MotorShield.h"
#include "debug.h"
#include <Wire.h>
#include <digitalWriteFast.h>
//#include <EEPROM.h>
#include "Config.h"
#include "QuadEncoder.h"
//#include "HX711.h"
#include <USBDesc.h>


//--------------------------------------- Globals --------------------------------------------------------

u8 spi_buffer[4];
u8 spi_bp = 0;
u8 spi_data_ready = false;

u32 last_send;
u32 last_nextShift = 0;
u32 last_ConfigSerial = 0;
u32 last_refresh;
b8 fault;
s32 accel,brake,clutch,turn;



cFFB gFFB;
BRFFB brWheelFFB;

extern s32 analog_inputs[];

s32 command = 0;
u32 now_micros = micros();
u32 time_diff = now_micros - last_send;
//u32 timeDiffNextShift = now_micros;
u32 timeDiffConfigSerial = now_micros;




//----------------------------------------- Options -------------------------------------------------------

/*
#ifdef USE_LOAD_CELL
HX711 gLoadCell(PD_OUT,PD_SCK);
#endif
*/

#ifdef USE_QUADRATURE_ENCODER
cQuadEncoder myEnc;
#endif

#ifdef USE_VNH5019

DualVNH5019MotorShield ms;

void stopIfFault()
{
	if (ms.getM1Fault())
	{
		DEBUG_SERIAL.println("M1 fault");
		while (1);
	}
	if (ms.getM2Fault())
	{
		DEBUG_SERIAL.println("M2 fault");
		while (1);
	}
}
#endif

//--------------------------------------------------------------------------------------------------------
//-------------------------------------------- SETUP -----------------------------------------------------
//--------------------------------------------------------------------------------------------------------

void setup()
{
	last_nextShift = last_send = last_refresh = micros();
	fault = false;
	accel = 0;
	brake = 0;
	clutch = 0;
	turn = 0;

	//ReadEEPROMConfig();

	CONFIG_SERIAL.begin(115200);

 	//pinMode(LCSYNC_LED_PIN,OUTPUT);
 	//pinMode(SYNC_LED_PIN,OUTPUT);
  	//pinMode(LED_PIN, OUTPUT);

// 	pinMode(SCK,INPUT); //11,INPUT);
// 	pinMode(MISO,INPUT); //12,INPUT);
// 	pinMode(MOSI,INPUT); //13,INPUT);

	myEnc.Init(ROTATION_MID - brWheelFFB.offset,true);//ROTATION_MID + gCalibrator.mOffset);

	InitInputs();

	FfbSetDriver(0);

#ifdef USE_VNH5019
	ms.init();
#endif

#ifdef USE_PWM
	InitPWM();
	setPWM(0);
#endif

#ifdef USE_QUADRATURE_ENCODER
	(CALIBRATE_AT_INIT ? brWheelFFB.calibrate() : myEnc.Write(ROTATION_MID - brWheelFFB.offset));
#else
	myEnc.Write(ROTATION_MID - brWheelFFB.offset);
#endif
}

//--------------------------------------------------------------------------------------------------------
void loop()
{
	ReadAnalogInputs();				// Some reading to take an average
	now_micros = micros();
	{
		time_diff = now_micros - last_send;
		//timeDiffNextShift = now_micros - last_nextShift;
		timeDiffConfigSerial = now_micros - last_ConfigSerial;

#ifdef USE_QUADRATURE_ENCODER
		if ((now_micros - last_refresh) >= CONTROL_PERIOD)
		{
			//SYNC_LED_HIGH();
			last_refresh = now_micros;
			
			turn = myEnc.Read() - ROTATION_MID - brWheelFFB.offset;

			command = gFFB.CalcTorqueCommand(turn);

			if (command > 0)
				command = map(command, 0, 1000, MM_MIN_MOTOR_TORQUE, MM_MAX_MOTOR_TORQUE);
			else if (command < 0)
				command = -map(-command, 0, 1000, MM_MIN_MOTOR_TORQUE, MM_MAX_MOTOR_TORQUE);
			else
				command = 0;
			setPWMDir(command);

			turn = (turn*X_AXIS_PHYS_MAX) / ROTATION_MAX;
			turn = constrain(turn,-MID_REPORT_X,MID_REPORT_X);

			
			nextInputState();						// Refresh state shift-register

			// USB Report
			{
				last_send = now_micros;
				AverageAnalogInputs();				// Average readings
				accel = analog_inputs[ACCEL_INPUT];
				brake = analog_inputs[BRAKE_INPUT];
				clutch = analog_inputs[CLUTCH_INPUT];

				//u16 buttons = ReadDigitalInputs();
				u16 buttons = readInputButtons();
				SendInputReport((s16)turn, (u16)accel, (u16)brake, (u16)clutch, buttons);

				ClearAnalogInputs();
				if (timeDiffConfigSerial > CONFIG_SERIAL_PERIOD) {
					readSerial();
					last_ConfigSerial = now_micros;
				}
			}
		}
#endif
	}
}
