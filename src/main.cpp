#include <BlUE_Warfarin-Config.h>
#include <VisionFunctions.h>
#include <GyroFunctions.h>
#include <BlUE_Warfarin-Config.h>

using namespace vex;
vex::competition Competition;
 
  
/*************************************************************************************************************************************

// sonar  ===================================================================================

*************************************************************************************************************************************/

void DetectCube(){
    if (Sonar.distance(vex::distanceUnits::cm) < 15){
        Brain.Screen.clearScreen(vex::color::green);                   
        
    }else if (Sonar.distance(vex::distanceUnits::cm) > 7){
        Brain.Screen.clearScreen(vex::color::red);
    }
}



/*************************************************************************************************************************************

// Autonomous - Combines all functions ===================================================================================

*************************************************************************************************************************************/
void Autonomous(void){
    
   Pre_auton();
   Intake(1, 75);
   wait(1, timeUnits, sec);

<<<<<<< HEAD
    Intake(1);
    DriveFoward(1.5);
    wait(1, timeUnits::sec);
    
=======
    Intake(1, 75);
    DriveFoward(2.5);
    wait(2, timeUnits::sec);
>>>>>>> 252bcda2535b2101b69f24e0971e5594daf447ea
    //DriveRotate(90);
    PIDGyroRotate(140);
    Intake(0, 0);
    DriveFoward(1.25);
    Intake(-1, 75);
    //AnglerAuto(3.7);
   wait(1, timeUnits, sec);
    DriveReverse(1);
    Intake(0, 0);
    
}
/**************************************************************************************************************************************


//Driver Control functions ====================================================================================================================


*************************************************************************************************************************************/

void Drive(int mode){

  if (mode ==1){
 /*   Mecanum Drive - Basic
- This program allows you to remotely control a robot with mecanum wheels.
- The left joystick Y-axis controls the robot's forward and backward movement.
- The left joystick X-axis controls the robot's left and right movement.
- The right joystick X-axis controls the robot's rotation.*/
  
    FrontRight.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis4.value() - Controller1.Axis1.value())/2, vex::velocityUnits::pct);
    BackRight.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis4.value() - Controller1.Axis1.value())/2, vex::velocityUnits::pct);
    FrontLeft.spin(vex::directionType::fwd, (Controller1.Axis3.value()+ Controller1.Axis4.value() + Controller1.Axis1.value())/2, vex::velocityUnits::pct);
    BackLeft.spin(vex::directionType::fwd, (Controller1.Axis3.value() - Controller1.Axis4.value() + Controller1.Axis1.value())/2, vex::velocityUnits::pct);
    
    vex::task::sleep(20);
}

 if (mode ==0){
 /*   Arcade - Basic
- This program allows you to remotely control a robot with omins wheels.
- The left joystick Y-axis controls the robot's forward and backward movement.
- The left joystick X-axis controls the robot's left and right movement.
- The right joystick X-axis controls the robot's rotation.*/
  
    FrontRight.spin(vex::directionType::fwd, (Controller1.Axis3.value()  - Controller1.Axis1.value()), vex::velocityUnits::pct);
    BackRight.spin(vex::directionType::fwd, (Controller1.Axis3.value()  - Controller1.Axis1.value()), vex::velocityUnits::pct);
    FrontLeft.spin(vex::directionType::fwd, (Controller1.Axis3.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
    BackLeft.spin(vex::directionType::fwd, (Controller1.Axis3.value()  + Controller1.Axis1.value()), vex::velocityUnits::pct);
    
    vex::task::sleep(20);
}




}



void Arms(){
  
    if ( Controller1.ButtonUp.pressing()){
       LeftArm.spin(vex::directionType::fwd, ArmMotorVelocity, vex::velocityUnits::pct);
        RightArm.spin(vex::directionType::fwd, ArmMotorVelocity, vex::velocityUnits::pct);
    } else if(Controller1.ButtonDown.pressing()){
       LeftArm.spin(vex::directionType::rev, ArmMotorVelocity, vex::velocityUnits::pct);
        RightArm.spin(vex::directionType::rev, ArmMotorVelocity, vex::velocityUnits::pct);
    } else {
       LeftArm.stop(vex::brakeType::hold);
        RightArm.stop(vex::brakeType::hold);
    }
    
}

void Intake(){
    if (Controller1.ButtonR1.pressing()){
        LeftIntakeMotor.spin(vex::directionType::fwd, IntakeMotorVelocity, vex::velocityUnits::pct);
        RightIntakeMotor.spin(vex::directionType::rev, IntakeMotorVelocity, vex::velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing()){
        LeftIntakeMotor.spin(vex::directionType::rev, IntakeMotorVelocity, vex::velocityUnits::pct);
        RightIntakeMotor.spin(vex::directionType::fwd, IntakeMotorVelocity, vex::velocityUnits::pct);
    } else {
        LeftIntakeMotor.stop(vex::brakeType::hold);
        RightIntakeMotor.stop(vex::brakeType::hold);
    }
   /* if (Controller1.ButtonR1.pressing()){
        LeftIntakeMotor.spin(vex::directionType::fwd, IntakeMotorVelocity, vex::velocityUnits::pct);
        RightIntakeMotor.spin(vex::directionType::rev, IntakeMotorVelocity, vex::velocityUnits::pct);
    } else if(Controller1.ButtonR2.pressing()){
        LeftIntakeMotor.spin(vex::directionType::rev, IntakeMotorVelocity, vex::velocityUnits::pct);
        RightIntakeMotor.spin(vex::directionType::fwd, IntakeMotorVelocity, vex::velocityUnits::pct);
    } else {
        LeftIntakeMotor.stop(vex::brakeType::hold);
        RightIntakeMotor.stop(vex::brakeType::hold);
    } */
}



void Angler(){
        if(AnglerBumper.pressing() == false){
      if (Controller1.ButtonL1.pressing())
          {
            AnglerMotor.spin(vex::directionType::fwd, AnglerMotorSpeed, vex::velocityUnits::pct);
          

      } else if(Controller1.ButtonL2.pressing()){
          AnglerMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);

      } else {
          AnglerMotor.stop(vex::brakeType::hold);

      } 

    }


    if(AnglerBumper.pressing() == true){
      if (Controller1.ButtonL1.pressing())
          {
            AnglerMotor.spin(vex::directionType::fwd, AnglerMotorSpeed, vex::velocityUnits::pct);
          

      }  else {
          AnglerMotor.stop(vex::brakeType::hold);

      } 

    }


    
    if(AnglerBumperFront.pressing() == true){
      if (Controller1.ButtonL2.pressing())
          {
            AnglerMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
          

      }  else {
          AnglerMotor.stop(vex::brakeType::hold);

      } 
    }

}

/*************************************************************************************************************************************


//  UserControll combines all the functions to be used in driving control ====================================================================================


*************************************************************************************************************************************/

void UserControl(void){
        while(1){
            if(!Controller1.ButtonB.pressing() ==true ){
                Drive(0);
                Arms();
                Intake(); 
                //DetectCube();
                Angler();
            } else if(Controller1.ButtonB.pressing() ==true){ 
                VisionTest1();
                VisionTest2();
        }
    }
}

/*************************************************************************************************************************************

// Main =================================================================================================================================

*************************************************************************************************************************************/
int main() {
 Competition.autonomous(Autonomous);
 Competition.drivercontrol(UserControl);
    vex::task::sleep(100);
}
