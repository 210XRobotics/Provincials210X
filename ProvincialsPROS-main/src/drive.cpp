#include "main.h"
#include "globals.hpp"

void setDriveMotors(int left, int right, bool pto)
{
  lbmotor = left;
  lmmotor = left;
  ltrmotor = left;

  rbmotor = right;
  rmmotor = right;
  rtlmotor = right;

  if (pto) {
    rtrmotor = right;
    ltlmotor = left;
  }
}

void setDrive(bool pto, bool transmission)
{
  //getting joystick elements
  int rightJoy = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  int leftJoy = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

  //transmission switching
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))
  {
    transmission = !transmission;
    tpiston.set_value(transmission);
  }

  setDriveMotors((rightJoy+leftJoy), (rightJoy-leftJoy), pto);
}
