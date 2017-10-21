#ifndef _QUAD_ENCODER_H
#define _QUAD_ENCODER_H

#define QUAD_ENC_PIN_A		0
#define QUAD_ENC_PIN_B		1
#define QUAD_ENC_PIN_I		2

#define	ROTATION_DEG	900	
#define	CPR				3960	// 4*990
#define MAX_ENCODER_ROTATION 9900
int ROTATION_MAX = MAX_ENCODER_ROTATION;
#define	ROTATION_MID	(ROTATION_MAX>>1)

//-----------------------------------------------------------------------------------------------

class cQuadEncoder
{
public:
	void Init (s32 position,b8 pullups = false);
	s32 Read ();
	void Write (s32 pos);
	void Update ();

private:
// 	volatile b8 mIndexFound;
// 	volatile u8 mLastState;
// 	volatile s32 mPosition;
};

extern cQuadEncoder gQuadEncoder;

#endif // _QUAD_ENCODER_H
