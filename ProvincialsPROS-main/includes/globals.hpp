#pragma once

#include "main.h"

//controller declarations
pros::Controller master(pros::E_CONTROLLER_MASTER);

//motor declarations
//pros::Motor (motorname)(port#, motor-cartridge, reversedmotor, motorencoders)
extern pros::Motor ltlmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor ltrmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lmmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor lbmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

pros::Motor rtrmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rtlmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rmmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor rbmotor(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

//piston declarations
pros::ADIDigitalOut tpiston('A');
pros::ADIDigitalOut ptopiston('B');

//encoders, gyros, inertials, etc
