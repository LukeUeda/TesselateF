#ifndef _ROBOT_STATE
#define _ROBOT_STATE

enum RobotMode{
	FAILSAFE,
	TANK_DRIVE,
	MELTY,
	RADIUS_ADJUST,
	TRANSLATION_OFFSET_ADJUST,
	LED_PATTERN_SELECT
};

class RobotState{
	private:
		RobotMode mode;
	public:
		RobotState();
		void rcToMode(int input_1, int input_2);
		void displayState();

		RobotMode getRobotMode();
		void setRobotMode(RobotMode _mode);
};

#endif
