#include "Config.h"
#include "debug.h"
#include "ConfigHID.h"


void configHID(USB_ConfigReport *data) {
	if (data->Info == 1) {
		int rotation = data->Rotation;
		rotation = constrain(rotation, 180, 900);
		ROTATION_MAX = (CPR / 360)*rotation;
		brWheelFFB.offset = (MAX_ENCODER_ROTATION - ROTATION_MAX) / 2;

		if(data->Calibrate == 1)
			brWheelFFB.calibrate();

		configGeneralGain = constrain(data->GeneralGain, 0, 200) / 100.0;
		configConstantGain = constrain(data->ConstantGain, 0, 200) / 100.0;		
		configDamperGain = constrain(data->DamperGain, 0, 200) / 100.0;		
		configFrictionGain = constrain(data->FrictionGain, 0, 200) / 100.0;
		configSineGain = constrain(data->SineGain, 0, 200) / 100.0;	
		configSpringGain = constrain(data->SpringGain, 0, 200) / 100.0;	
		configInertiaGain = constrain(data->InertiaGain, 0, 200) / 100.0;
		configCenterGain = constrain(data->CenterGain, 0, 200) / 100.0;
		configStopGain = constrain(data->StopGain, 0, 200) / 100.0;
				
		int temp = data->MinForce;
		if (temp < MM_MAX_MOTOR_TORQUE)
		{
			MM_MIN_MOTOR_TORQUE = constrain(temp, 0, 399);
			data->Info = 99;
		}

		temp = data->MaxForce;
		if (temp > MM_MIN_MOTOR_TORQUE)
		{
			data->Info = 99;
			MM_MAX_MOTOR_TORQUE = constrain(temp, 1, 400);
		}

	}
	else if (data->Info == 255) {
		/*uint8_t ReportId;
		uint16_t Rotation;
		uint8_t GeneralGain;
		uint8_t ConstantGain;
		uint8_t DamperGain;
		uint8_t FrictionGain;
		uint8_t SineGain;
		uint8_t SpringGain;
		uint8_t InertiaGain;
		uint8_t CenterGain;
		uint8_t StopGain;
		uint16_t MaxForce;
		uint16_t MinForce;
		uint8_t Centralize;
		uint8_t Calibrate;
		uint8_t Info;
		uint8_t Version;*/
		data->Rotation = ROTATION_MAX / (CPR / 360);
		data->GeneralGain = configGeneralGain*100;
		data->ConstantGain = (int)configConstantGain*100;
		data->DamperGain = (int)configDamperGain*100;
		data->FrictionGain = (int)configFrictionGain*100;
		data->SineGain = (int)configSineGain*100;
		data->SpringGain = (int)configSpringGain*100;
		data->InertiaGain = (int)configInertiaGain*100;
		data->CenterGain = (int)configCenterGain*100;
		data->StopGain = (int)configStopGain*100;
		data->MaxForce = MM_MAX_MOTOR_TORQUE;
		data->MinForce = MM_MIN_MOTOR_TORQUE;

	}
	data->Version = VERSION;
	//uint8_t *response = (uint8_t*)data;
	HID_SendReport(0xF2, (uint8_t*)data, 64);
}