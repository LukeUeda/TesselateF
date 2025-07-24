#ifndef _MELTYLOCK
#define _MELTYLOCK

#include <SparkFun_LIS331.h>
#include <Wire.h>

enum HeadingState{
	HEADING_LEFT,
	HEADING_RIGHT
};

struct Vector{
	float x;
	float y;
	float m;
};

class Meltylock{
	private:
		LIS331 accel;
		float radius; // Radius of accelerometer from centre of rotation
		float translation_offset; // Switching point of motors relative to heading
		
		// Control Parameters
		float steering; // Adds steering offset to robots heading
		float radius_adjust;
		float translation_offset_adjust;

		Vector last_acceleration;

		volatile float ang_vel; // Angular velocity
		volatile float h_error; // Heading error
		volatile HeadingState heading_state; // Heading state: Left or Right of robot
		volatile unsigned long last_update_time; // Time since last update
	public:
		Meltylock(float _radius, float _translation_offset);

		void readAccelerometer();
		void calculateAngularVelocity();
		
		// Update methods
		void updateHeading(float d_angle);
		void updateParameters(float d_radius, float d_translation);	
		void update(); // Runs all update methods

		float getHeading();
		float getAcceleration();
		HeadingState getHeadingState();

		// Setting control parameters
		void setSteering(float _steering);
		void adjustRadius(float _radius_adjust);
		
		// Debug printing
		void displayRadius();
		void displayAcceleration();
		void displayAngularVelocity();
};

#endif
