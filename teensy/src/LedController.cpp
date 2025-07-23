#include "../include/LedController.hpp"
#include <Arduino.h>

LedController::LedController(int _led_pins[5]){
	// Set all LED outputs
	for(int i = 0; i < 5; i++){
		led_pins[i] = _led_pins[i];
		pinMode(led_pins[i], OUTPUT);
	}

	pattern = FAILSAFE_PATTERN;
}

void LedController::updateLed(float _heading_error){
	switch(pattern){
		case FAILSAFE_PATTERN:
			for(int i = 0; i < LED_COUNT; i++){
				digitalWrite(led_pins[i], HIGH);
			}
			break;
		case LOADING:
			switch((millis() * 4/1000) % 12){	
				case 0:
					digitalWrite(led_pins[4], HIGH);
					break;
				case 1:
					digitalWrite(led_pins[3], HIGH);
					break;
				case 2:
					digitalWrite(led_pins[2], HIGH);
					break;
				case 3:
					digitalWrite(led_pins[1], HIGH);
					break;
				case 4:
					digitalWrite(led_pins[0], HIGH);
					break;
				case 5:
					digitalWrite(led_pins[4], LOW);
					break;
				case 6:
					digitalWrite(led_pins[3], LOW);
					break;
				case 7:
					digitalWrite(led_pins[2], LOW);
					break;
				case 8:
					digitalWrite(led_pins[1], LOW);
					break;
				case 9:
					digitalWrite(led_pins[0], LOW);
					break;
			}
			break;
		case SIMPLE_ARC:
			if(abs(_heading_error) < SIMPLE_ARC_ANGLE/2){
				for(int i = 0; i < LED_COUNT; i++){
					digitalWrite(led_pins[i], HIGH);
				}
			} else {
				for(int i = 0; i < LED_COUNT; i++){
					digitalWrite(led_pins[i], LOW);
				}
			}
	}
}

void LedController::setPattern(LedPattern _pattern){
	if(pattern != _pattern){
		pattern = _pattern;
		//for(int i = 0; i < LED_COUNT; i++){
		//	digitalWrite(led_pins[i], LOW);
		//}
	}
}
