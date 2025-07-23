#ifndef _MOTOR
#define _MOTOR

struct MotorConfig{
	int pin;
	
	bool bidirectional;
	bool reverse;

	float max_duty;
	float min_duty;

};

class Motor{
	private:
		MotorConfig config;
		bool enabled;
		
		// Setpoint is [0, 1] for unidirectional, [-1, 1] for bidirectional
		float setpoint; 
		
		float duty_cycle;
	public:
		Motor();
		Motor(MotorConfig _config);

		void sendControlSignal();

		void setConfig(MotorConfig _config);
		void setReverse(bool _reverse);
		void setSetpoint(float _setpoint);

		void enable();
		void disable();
		void setToStationary();
};

#endif
