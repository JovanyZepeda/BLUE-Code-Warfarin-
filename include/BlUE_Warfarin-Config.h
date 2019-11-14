
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#ifndef CONFIG //Add this header guard so that the compiler does not compile this header file more than twice
#define CONFIG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "v5.h"
#include "v5_vcs.h"




//  Variables
    #define PI 3.141592
    double WheelDiameterCM = 10.16;
    double CircumferenceCM = PI * WheelDiameterCM;
    double TravelTargetCM = 60; 
    double GearRatio = 1.66667;
    double DegreesToRotate = (360 * (TravelTargetCM/CircumferenceCM) * GearRatio);
    double MotorVelocity = 50; 
    double ArmMotorVelocity = 30;
    double RadiusRobotCM = 33.5; // This is equal the distance of the center of one wheel to the center of the wheel on the other side
    double DegreesToRevolve;
    double IntakeMotorVelocity = 100;
    double AnglerMotorSpeed = 30;

// vision variables
    int DesiredX = 158; // the x coordinate i want the object to be at
    int DesiredY = 106; // the y coordinate i want the object to be at
    int Offset = 25;    // offsets the desired x/y to create an interval (target zone)
    int ActualX;        // x coordinate from sensor
    int ActualY;       // x coordinate from sensor
    double VisionMotorVelocity = 5; 



//Brain and controller
vex::brain Brain;
vex::controller Controller1 = vex::controller();

// define your global instances of motors and other devices here

vex::motor FrontLeft        = vex::motor( vex::PORT11);
vex::motor FrontRight       = vex::motor( vex::PORT1); //Add true to reverse the direction of right motor
vex::motor BackLeft         = vex::motor( vex::PORT19 );
vex::motor BackRight        = vex::motor( vex::PORT20,  true);


//Scoring Mechanism
vex::motor LeftArm          = vex::motor( vex::PORT3);
vex::motor RightArm         = vex::motor( vex::PORT8, true);
vex::motor LeftIntakeMotor  = vex::motor( vex::PORT14);
vex::motor RightIntakeMotor = vex::motor( vex::PORT16);
vex::motor AnglerMotor      = vex::motor( vex::PORT4);
 

//Devices
vex::sonar Sonar            = vex::sonar(Brain.ThreeWirePort.B);
vex::gyro Gyro              = vex::gyro(Brain.ThreeWirePort.A);
vex::bumper AnglerBumper    = vex::bumper(Brain.ThreeWirePort.C);
vex::bumper AnglerBumperFront    = vex::bumper(Brain.ThreeWirePort.D);
vex::bumper RightArmBumper       = vex::bumper(Brain.ThreeWirePort.E);
vex::bumper LeftArmBumper        = vex::bumper(Brain.ThreeWirePort.F);

#endif CONFIG //End of the definition of Config