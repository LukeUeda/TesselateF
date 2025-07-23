#ifndef _CONFIG
#define _CONFIG

#include "Motor.hpp"
#include "Constants.hpp"
#include "Receiver.hpp"

// All configurations defined here are fully
// defined by constants, therefore it is
// intended that any modifications to 
// configs be done through <Constants.hpp>.

MotorConfig LEFT_MOTOR_CONFIG = {
	.pin = MOTOR_PIN_1,
	.bidirectional = BIDIRECTIONAL,
	.max_duty = MAX_DUTY,
	.min_duty = MIN_DUTY,
};

MotorConfig RIGHT_MOTOR_CONFIG = {
	.pin = MOTOR_PIN_2,
	.bidirectional = BIDIRECTIONAL,
	.max_duty = MAX_DUTY,
	.min_duty = MIN_DUTY
};

int LED_PINS[LED_COUNT] = {
	LED_PIN_0, 
	LED_PIN_1, 
	LED_PIN_2, 
	LED_PIN_3, 
	LED_PIN_4
};

int CHANNEL_PINS[CHANNEL_COUNT] = {
	CHANNEL_PIN_0,
	CHANNEL_PIN_1,
	CHANNEL_PIN_2,
	CHANNEL_PIN_3,
	CHANNEL_PIN_4,
	CHANNEL_PIN_5
};

ChannelConfig CHANNEL_0_CONFIG = {
	.type = CHANNEL_0_TYPE,
	.min_pulse = CHANNEL_0_MIN_PULSE,
	.max_pulse = CHANNEL_0_MAX_PULSE,
	.middle_pulse = CHANNEL_0_MID_PULSE
};

ChannelConfig CHANNEL_1_CONFIG = {
	.type = CHANNEL_1_TYPE,
	.min_pulse = CHANNEL_1_MIN_PULSE,
	.max_pulse = CHANNEL_1_MAX_PULSE,
	.middle_pulse = CHANNEL_1_MID_PULSE
};

ChannelConfig CHANNEL_2_CONFIG = {
	.type = CHANNEL_2_TYPE,
	.min_pulse = CHANNEL_2_MIN_PULSE,
	.max_pulse = CHANNEL_2_MAX_PULSE,
	.middle_pulse = CHANNEL_2_MID_PULSE
};

ChannelConfig CHANNEL_3_CONFIG = {
	.type = CHANNEL_3_TYPE,
	.min_pulse = CHANNEL_3_MIN_PULSE,
	.max_pulse = CHANNEL_3_MAX_PULSE,
	.middle_pulse = CHANNEL_3_MID_PULSE
};

ChannelConfig CHANNEL_4_CONFIG = {
	.type = CHANNEL_4_TYPE,
	.min_pulse = CHANNEL_4_MIN_PULSE,
	.max_pulse = CHANNEL_4_MAX_PULSE,
	.middle_pulse = CHANNEL_4_MID_PULSE
};

ChannelConfig CHANNEL_5_CONFIG = {
	.type = CHANNEL_5_TYPE,
	.min_pulse = CHANNEL_5_MIN_PULSE,
	.max_pulse = CHANNEL_5_MAX_PULSE,
	.middle_pulse = CHANNEL_5_MID_PULSE
};

ChannelConfig CHANNEL_CONFIGS[CHANNEL_COUNT] = {
	CHANNEL_0_CONFIG,
	CHANNEL_1_CONFIG,
	CHANNEL_2_CONFIG,
	CHANNEL_3_CONFIG,
	CHANNEL_4_CONFIG,
	CHANNEL_5_CONFIG
};

#endif
