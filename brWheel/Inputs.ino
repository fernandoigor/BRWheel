/*
Copyright 2015  Etienne Saint-Paul
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

#include "debug.h"
#include <Wire.h>
#include <digitalWriteFast.h>
#include "Config.h"
#include "QuadEncoder.h"
//#include "HX711.h"
#include <USBDesc.h>

//#define ENCODER_OPTIMIZE_INTERRUPTS
//#include <Encoder.h>

//--------------------------------------- Globals --------------------------------------------------------

s16 adc_val = 0;

u8 digital_inputs_pins[] = {3,6,7,8,11,12};
//u8 digital_inputs_pins[] = { 3,6,7,8,11,12,A4,A3,A2,A1,A0 };

u8 analog_inputs_pins[] = 
{
	ACCEL_PIN,
	BRAKE_PIN,
	CLUTCH_PIN
};

u8 axis_shift_n_bits[] = 
{
	Z_AXIS_NB_BITS - ADC_NB_BITS,
	Y_AXIS_NB_BITS - ADC_NB_BITS,
	RX_AXIS_NB_BITS - ADC_NB_BITS
};

s32 analog_inputs[sizeof(analog_inputs_pins)];

u8 load_cell_channel;
s32 nb_mes;

//----------------------------------------- Options -------------------------------------------------------

/*#ifdef USE_DSP56ADC16S
void ss_falling()
{
	adc_val = (spi_buffer[0] << 8) + spi_buffer[1];
	spi_bp = 0;
}

ISR(SPI_STC_vect)
{
	spi_buffer[spi_bp] = SPDR;
	if (spi_bp<3)
		spi_bp++;
}
#endif
*/

//--------------------------------------------------------------------------------------------------------

/*
void InitADC ()
{
#ifdef USE_DSP56ADC16S
	pinMode(ADC_PIN_CLKIN,OUTPUT);
	pinMode(ADC_PIN_FSO,INPUT);
	pinMode(ADC_PIN_SDO,INPUT);
	pinMode(ADC_PIN_SCO,INPUT);

	SPCR = _BV(SPE);		// Enable SPI as slave
	SPCR |= _BV(SPIE);		// turn on SPI interrupts
	TCCR3A = 0b10100000;
	TCCR3B = 0b00010001;
	ICR3 = 8;
	OCR3A = 4;									// 1 MHz clock for the DSP56ADC16S
	attachInterrupt(0,ss_falling,FALLING);
#endif
}
*/

/*
b8 InitLoadCell ()
{
#ifdef USE_LOAD_CELL
	gLoadCell.power_down();
	gLoadCell.power_up();
	u32 mil = millis();
	last_send = mil;
	while ((mil - last_send) < 100)
	{
		mil = millis();
		if (gLoadCell.is_ready())
		{
			gLoadCell.set_gain(128);
			gLoadCell.tare(30);	//Assuming there is no weight on the scale at start up, reset the scale to 0
			return(true);
		}
	}
#endif
	return(false);
}
*/
void InitInputs()
{
	/*for (u8 i = 0; i < sizeof(digital_inputs_pins); i++)
		pinMode(digital_inputs_pins[i],INPUT_PULLUP);

	for (u8 i = 0; i < sizeof(analog_inputs_pins); i++)
		pinMode(analog_inputs_pins[i],INPUT);*/


/*#ifdef USE_QUADRATURE_ENCODER
	//myEnc.Init(ROTATION_MID + gCalibrator.mOffset);
#endif*/

#ifdef USE_SHIFT_REGISTER
	InitShiftRegister();
#endif

	//InitADC();
	//InitLoadCell();

	nb_mes = 0;
	//load_cell_channel = 0;
}

//--------------------------------------------------------------------------------------------------------

short int SHIFTREG_STATE;
//unsigned int bytesVal = 0;
u16 bytesVal_SW;		// Temporary variables for read input Shift Steering Wheel (8-bit)
u16 bytesVal_H;			// Temporary variables for read input Shift H-Shifter (Dual 8-bit)
u16 btnVal_SW=0;
u16 btnVal_H = 0;
int i = 0;

void InitShiftRegister() {
	pinMode(SHIFTREG_CLK, OUTPUT);
	pinMode(SHIFTREG_DATA_SW, INPUT);
	pinMode(SHIFTREG_DATA_H, INPUT);
	pinMode(SHIFTREG_PL, OUTPUT);
	SHIFTREG_STATE = 0;
	bytesVal_SW = 0;
}

void nextInputState() {
	long bitVal = 0;
	if (SHIFTREG_STATE > 33) {	// SINGLE SHIFT = 25 states  DUAL SHIFT = 49 states (both zero include), 33 for 16 shifts
		SHIFTREG_STATE = 0;
		btnVal_SW = bytesVal_SW;
		btnVal_H = bytesVal_H;
		bytesVal_SW = 0;
		bytesVal_H = 0;
		i = 0;
	}

	if (SHIFTREG_STATE < 2) {
		//DEBUG_SERIAL.println("PL");
		if (SHIFTREG_STATE == 0) {
			//Serial.println("PL low");
			digitalWrite(SHIFTREG_PL, LOW);
		}
		else {
			//Serial.println("PL high");
			digitalWrite(SHIFTREG_PL, HIGH);
		}
	}
	else {
		if (SHIFTREG_STATE % 2 == 0) {
			bitVal = digitalRead(SHIFTREG_DATA_SW);
			bytesVal_SW |= (bitVal << ((8 - 1) - i));

			bitVal = digitalRead(SHIFTREG_DATA_H);
			bytesVal_H |= (bitVal << ((16 - 1) - i));

			i++;
			digitalWrite(SHIFTREG_CLK, HIGH);
		}
		else if (SHIFTREG_STATE % 2 == 1) {
			//DEBUG_SERIAL.println("CLK HIGH");
			digitalWrite(SHIFTREG_CLK, LOW);
		}
	}

	SHIFTREG_STATE++;
}

u32 readInputButtons() {
	
	u32 buttons = 0;
	u32 bmask = 1;
	for (u8 i = 0; i < 8; i++)
	{
		if (((btnVal_SW >> i) & 1) == 1)  
			buttons |= bmask;
		bmask <<= 1;

	}
	for (u8 i = 0; i <16; i++)
	{
		if (((btnVal_H >> i) & 1) == 1)
			buttons |= bmask;
		bmask <<= 1;
	}
	//DEBUG_SERIAL.println(btnVal_H);
	
	return(buttons);
}
//--------------------------------------------------------------------------------------------------------

void ClearAnalogInputs ()
{
	for (u8 i = 0; i < sizeof(analog_inputs_pins); i++)
		analog_inputs[i] = 0;
	nb_mes = 0;
}

int ReadAnalogInputs ()
{
	for (u8 i = 0; i < sizeof(analog_inputs_pins); i++)
		analog_inputs[i] += analogRead(analog_inputs_pins[i]);
	nb_mes++;

	return nb_mes;
}

void AverageAnalogInputs ()
{
	for (u8 i = 0; i < sizeof(analog_inputs_pins); i++)
		analog_inputs[i] = (analog_inputs[i] << axis_shift_n_bits[i]) / nb_mes;
}
