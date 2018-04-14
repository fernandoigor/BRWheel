#include "Config.h"
#include "debug.h"

#ifndef _CONFIGHID_H_
#define _CONFIGHID_H_

typedef struct
{
	uint8_t ReportId;
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
	uint8_t Version;
} USB_ConfigReport;

typedef struct
{
	uint16_t Call : 8;
	uint16_t Rotation : 10;
	uint16_t GeneralGain : 8;
	uint16_t ConstantGain : 8;
	uint16_t DamperGain : 8;
	uint16_t FrictionGain : 8;
	uint16_t SineGain : 8;
	uint16_t SpringGain : 8;
	uint16_t CenterGain : 8;
	uint16_t StopGain : 8;
	uint16_t MaxForce : 9;
	uint16_t MinForce : 9;
	uint16_t Centralize : 1;
	uint16_t Calibrate : 1;
} USB_ConfigReportReturn;


int configHID(USB_ConfigReport *data);

#endif // _CONFIGHID_H_