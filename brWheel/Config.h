#ifndef _CONFIG_H_
#define _CONFIG_H_

//------------------------------------- Options ----------------------------------------------------------

//#define USE_VNH5019				// Pololu dual 24V DC motor drive
//#define USE_SM_RS485				// Granite devices simple motion protocol
#define USE_PWM						// PWM output for drive torque input
//#define USE_LCD					// LCD (not used)
//#define USE_DSP56ADC16S			// 16 bits Stereo ADC
#define USE_QUADRATURE_ENCODER		// Position Quadrature encoder
//#define USE_LOAD_CELL				// Load cell shield
#define USE_SHIFT_REGISTER			// 8-bit Parallel-load shift registers G27 board steering wheel
//#define USE_DUAL_SHIFT_REGISTER		// Dual 8-bit Parallel-load shift registers G27 board shifter

#define CALIBRATE_AT_INIT	1

//------------------------------------- Pins -------------------------------------------------------------

#define LED_PIN				13
//#define	LCSYNC_LED_PIN		8
//#define	SYNC_LED_PIN		7

#define ACCEL_PIN			A0
#define BRAKE_PIN			A1
#define CLUTCH_PIN			A2
//#define TURN_PIN			A3		// NOT USED
#define SHIFTER_X_PIN		A4
#define SHIFTER_Y_PIN		A5

#define SHIFTREG_PL			4		// PL SH/LD (Shift or Load input)
#define SHIFTREG_CLK		5		// CLOCK 8-bit Parallel shift
#define SHIFTREG_DATA_SW	6		// DATA Steering Wheel
#define SHIFTREG_DATA_H		7		// DATA Shifter H (Dual 8-bit)
#define SHIFTREG_DATA_OUT	3		// DATA Shift-Out LED (8-bit)   ###### NOT YET IMPLEMENTED ######


/* NOT USED
#define ADC_PIN_CLKIN		5
#define ADC_PIN_FSO			3//10	// Hack : This pin has been connected to mcu SS
#define ADC_PIN_SDO			13		// Hack : This pin has been connected to ICSP MOSI
#define ADC_PIN_SCO			11		// Hack : This pin has been connected to ICSP SCK


#define PIN_MISO			12		// Hack : This pin has been connected to ICSP MISO
*/

#define	PWM_PIN				9 
#define	DIR_PIN				10
#define	REVERSE_DIR_PIN		11

#define ACCEL_INPUT 0
#define BRAKE_INPUT 1
#define CLUTCH_INPUT 2
/*
#ifdef USE_LOAD_CELL
#define TURN_INPUT 1
#else
#define TURN_INPUT 2
#endif
*/


//------------------------------------- Helpers -----------------------------------------------------

#define	LCSYNC_LED_HIGH()		//digitalWriteFast(LCSYNC_LED_PIN,HIGH)
#define	LCSYNC_LED_LOW()		//digitalWriteFast(LCSYNC_LED_PIN,LOW)
#define	SYNC_LED_HIGH()			//digitalWriteFast(SYNC_LED_PIN,HIGH)
#define	SYNC_LED_LOW()			//digitalWriteFast(SYNC_LED_PIN,LOW)

//------------------------------------- EEPROM Config -----------------------------------------------------

#define PARAM_ADDR_VERSION			0
#define PARAM_ADDR_OFFSET			4
#define PARAM_ADDR_MAX_ROTATION		8

#define VERSION		0x00000007

#define GetParam(m_offset,m_data)	getParam((m_offset),(u8*)&(m_data),sizeof(m_data))
#define SetParam(m_offset,m_data)	setParam((m_offset),(u8*)&(m_data),sizeof(m_data))

//void SetDefaultConfig();
//u32 ReadEEPROMConfig();

//------------------------------------- Main Config -----------------------------------------------------

#define CONTROL_FPS		500
#define CONTROL_PERIOD	2000

#define SEND_PERIOD		4000

#define CONFIG_SERIAL_PERIOD 50000



//------------------------------------- FFB Config -----------------------------------------------------

f32 configDamperGain = 0.5;		//ok
f32 configFrictionGain = 0.5;	//OK
f32 configConstantGain = 1.0;	//OK
f32 configSineGain = 1.0f;		//OK
f32 configSpringGain = 1.0f;	//OK
f32 configInertiaGain = 1.0f;	//OK
f32 configGeneralGain = 1.0f;	//OK
f32 configCenterGain = 0.7f;	//OK
f32 configStopGain = 1.0f;	//OK

int MM_MIN_MOTOR_TORQUE=200;
int MM_MAX_MOTOR_TORQUE=400;



#endif // _CONFIG_H_
