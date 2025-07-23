#ifndef _RECEIVER
#define _RECEIVER

#include "Constants.hpp"
#include <cstdint>

// Type of channel input. To be used for processing pulses
enum ChannelType{
	TWO_POS,
	THREE_POS,
	STICK
};

struct ChannelConfig{
	ChannelType type;
	uint16_t min_pulse;
	uint16_t max_pulse;
	uint16_t middle_pulse; // Zero point to be used for bidirectional stick.
};

class Receiver{
	private:
		int channel_pins[CHANNEL_COUNT];
		ChannelConfig channel_configs[CHANNEL_COUNT];

		// Pulsewidth measurement variables
		volatile unsigned long pulse_starts[CHANNEL_COUNT];
		volatile uint16_t pulsewidths[CHANNEL_COUNT];
		
		unsigned long last_pulse_time; // Checks when the last pulse was seen for failsafe
		bool failsafe_triggered;
	public:
		Receiver(ChannelConfig _channel_configs[CHANNEL_COUNT], int _channel_pins[CHANNEL_COUNT]);

		uint16_t getPulsewidth(int channel);
		float getValue(int channel); // Maps pulsewidth to value in range [-1, 1]

		bool inFailsafe();

		void displayPulsewidths();
		void displayValues();

		void isr(int channel);
};

#endif
