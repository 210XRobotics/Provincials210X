#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
 struct PathPoint {
    float x;
    float y;
    float w;
  	float curvature;
    float distance;
};
float x_loc = 0, y_loc = 0;
pros::Motor left_mtr(1);
pros::Motor right_mtr(2);
pros::Inertia imu_sensor(8);

void getCurrLocation(){
  float distance = (left_mtr.rotation(vex::rotationUnits::deg) + right_mtr.rotation(vex::rotationUnits::deg))/2;
	x_loc += distance * cos(Inertia.get_rotation());
  y_loc += distance * sin(rInertia.get_rotation());
  //^^This gives the location of the robot relative to its starting location
}

vector<float> tarx,tary;
void autonomous() { 
	tarx.insert(tarx.begin(),0);//starting point
	tary.insert(tary.begin(),0);//starting point
	tarx.insert(tarx.begin(),10);
	tary.insert(tary.begin(),10);// these values can be changed to the coordinate of the target point, I do not know what units these are in, so have fun :)

	vector<float> pointsx,pointsy;
	float yvalue;
	float spacing = 1;
	vector<float> newpointsx(1000),newpointsy(1000);
	int counter1=0;
	for(int b=0;b<tarx.size()-1;b++){
		for(int i=0;i<abs(tarx[0]-tarx[1]);i+= spacing){
			counter1++;
			pointsx.insert(pointsx.begin(),i);
			yvalue = (abs(tary[1]-tary[0])/abs(tarx[1]-tarx[0]))*i;
		}

	}
	
	//time to smooth :'DDDDDDDDDDD

	float bb=.8; 
	float aa = 1-bb;
	float tolerance = .001;

	double change = tolerance;

	while(change >=tolerance){
		change = 0.0;
		for(int a=1;a<pointsx.size();a++){

			for(int b=0;b<pointsy.size();b++){
								double aux = newpointsx[a];
				newpointsx[a] += aa*(pointsx[a]-newpointsx[a])+bb *(newpointsx[a-1]+newpointsx[a+1] - (2.0*newpointsx[a])));

				newpointsy[a] += aa*(pointsy[a]-newpointsy[a])+bb *(newpointsy[a-1]+newpointsy[a+1] - (2.0*newpointsy[a]))); //if there are any errors in terms of how or where the robot moves, please kindly stare at this mess of a equation, thank you.
			}

		}
		change += abs(aux - newpointsx[a]);
	}

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;
		pros::delay(20);
	}
}
