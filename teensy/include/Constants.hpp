#ifndef _CONSTANTS
#define _CONSTANTS

#define DEBUG 				true

// Motor constants
#define ANALOG_WRITE_RESOLUTION_BITS 	12
#define ANALOG_WRITE_RESOLUTION 	4095
#define ANALOG_WRITE_FREQUENCY 		250
#define FRAME_DURATION_MS 		4

#define MOTOR_PIN_1 			4
#define MOTOR_PIN_2 			3

#define BIDIRECTIONAL 			true
#define MAX_DUTY 			0.5
#define MIN_DUTY 			0.25

// LED controller constants
#define LED_COUNT 			5

#define LED_PIN_0 			8
#define LED_PIN_1 			9
#define LED_PIN_2 			10
#define LED_PIN_3 			11
#define LED_PIN_4 			12

// LED pattern constants
#define SIMPLE_ARC_ANGLE		60

// Receiver constants
#define CHANNEL_COUNT 			6

#define CHANNEL_PIN_0 			16
#define CHANNEL_PIN_1			23
#define CHANNEL_PIN_2 			22
#define CHANNEL_PIN_3 			17
#define CHANNEL_PIN_4 			20
#define CHANNEL_PIN_5 			21

#define CHANNEL_0_TYPE 			STICK
#define CHANNEL_0_MIN_PULSE 		1000
#define CHANNEL_0_MID_PULSE 		1500
#define CHANNEL_0_MAX_PULSE 		2000

#define CHANNEL_1_TYPE 			STICK
#define CHANNEL_1_MIN_PULSE 		1000
#define CHANNEL_1_MID_PULSE 		1500
#define CHANNEL_1_MAX_PULSE 		2000

#define CHANNEL_2_TYPE 			STICK
#define CHANNEL_2_MIN_PULSE 		1000
#define CHANNEL_2_MID_PULSE 		1500
#define CHANNEL_2_MAX_PULSE 		2000

#define CHANNEL_3_TYPE 			STICK
#define CHANNEL_3_MIN_PULSE 		0
#define CHANNEL_3_MID_PULSE 		1000
#define CHANNEL_3_MAX_PULSE 		2000

#define CHANNEL_4_TYPE 			THREE_POS
#define CHANNEL_4_MIN_PULSE 		1000
#define CHANNEL_4_MID_PULSE 		1500
#define CHANNEL_4_MAX_PULSE 		2000

#define CHANNEL_5_TYPE			THREE_POS
#define CHANNEL_5_MIN_PULSE 		1000
#define CHANNEL_5_MID_PULSE 		1500
#define CHANNEL_5_MAX_PULSE 		2000

#define SWITCH_POS_THRESHOLD		200
#define PULSE_DEADZONE 			20
#define FAILSAFE_THRESHOLD		1000

// Meltylock constants
#define ACCEL_RADIUS 			98.8490524292
#define TRANSLATION_OFFSET		0

#define SDA_PIN 			18
#define SCL_PIN 			19

// Control constants
#define STEER_SPEED			360	
#define TRANSLATE_DECEL_FACTOR		1
#define TRANSLATE_ACCEL_FACTOR		1

#define RADIUS_ADJUST_SPEED		5
#define TRANSLATION_OFFSET_ADJUST_SPEED	180
#endif
