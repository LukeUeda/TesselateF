#ifndef _LED_CONTROLLER
#define _LED_CONTROLLER

#include "Constants.hpp"

enum LedPattern{
	FAILSAFE_PATTERN,
	INITIALISING,

	SIMPLE_ARC,
	INVERTED_ARC,
	ANIMATED_ARC,
	WAKA_WAKA,
	LOADING
};

class LedController{
	private:
		int led_pins[LED_COUNT];
		
		volatile bool led_states[LED_COUNT];
		volatile unsigned long last_update_time;

		LedPattern pattern;
	public:
		LedController(int _led_pins[LED_COUNT]);

		void updateLed(float _heading_error);
		void setPattern(LedPattern _pattern);
};

#endif
