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
    
//adjust gyro
   wait(2, timeUnits::sec);
   Pre_auton();
   Intake(1, 75);
  // vex::wait(2, timeUnits::sec);
    

  //  Intake(1);
    DriveFoward(4, 40); //collect 2 cubes
    //task::sleep(1000);

    Intake(0, 0);
    DriveReset();
    DriveReverse(2.6, 45);
    //DriveRotate(90);
    Intake(0, 0);
    wait(500, timeUnits::msec);
    PIDGyroRotate(-135);
/*if it doesn't work, gyro either makes robot spin forever, 
or rotates to position then stops function altogether
*/
    Intake(-1, 45);
    wait(500, timeUnits::msec);
    Intake(1, 75); //adjust
    Intake(0, 0);

    DriveFoward(.75, 50);

    AnglerAuto(0, 2, 60); 

    Intake(-1, 50);
    wait(500, timeUnits::msec);
    Intake(-1, 30);

    AnglerAuto(1, 0, 40); //stack
    Intake(0, 0);
    DriveFoward(.15, 20);
    DriveReset();
    wait(500, timeUnits::msec);
    Intake(-1, 5);
    DriveReverse(2, 100);
    Intake(0, 0);
 
    //
    //Intake(0);
    

    /*
     DriveFoward(1.2, 30);
      
    wait(500, timeUnits::msec);
    DriveReverse(1.2, 70);
    */

  
    
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



void MoveRamp(){

//this will set the ramp at the right position for rading the arms. This will also reset the ramp
//from any position, back to the intake position

  if(Controller1.ButtonA.pressing() == true && AnglerBumperFront.pressing()== true){ //foward if: it is in the intaking position

      AnglerMotor.rotateFor(directionType::fwd, 2, rotationUnits::rev, 100, velocityUnits::pct);
  } 

  if(Controller1.ButtonY.pressing() == true && LeftArmBumper.pressing() == true ){ //reset ramp if: the arms are fully down/lowered

      do{ 
      AnglerMotor.spin(directionType::rev, 200, percentUnits::pct); 
      } while (AnglerBumperFront.pressing()==false); //this will move the angler moter back until it presses the from bump switch(intake position)


  }

}







void Arms(){

/*
This function will operate the arms motors; it used two bummp switches to sense if the arms are already in the intake position. 
This is also a way to recallibrate the arms if they get mis-aligned. 
*/


    if ( Controller1.ButtonUp.pressing() && AnglerBumperFront.pressing() == false){ //check is button up is pressed and that anlger is not in intake position

        LeftArm.spin(vex::directionType::fwd, ArmMotorVelocity, vex::velocityUnits::pct);
        RightArm.spin(vex::directionType::fwd, ArmMotorVelocity, vex::velocityUnits::pct);
   
    } else if(Controller1.ButtonDown.pressing()){ // check is the button down is pressed => Move arms down if....


        if(RightArmBumper.pressing() == false && LeftArmBumper.pressing() == false) // Move both arms down at same time
        { 

          LeftArm.spin(vex::directionType::rev, ArmMotorVelocity, vex::velocityUnits::pct);
          RightArm.spin(vex::directionType::rev, ArmMotorVelocity, vex::velocityUnits::pct);
      
        } else if(RightArmBumper.pressing()==false && LeftArmBumper.pressing() == true){ // if left bumper is pressed, only move the right arm down
        
          LeftArm.setBrake(brakeType::coast);
          RightArm.spin(vex::directionType::rev, ArmMotorVelocity, vex::velocityUnits::pct);
      
        } else if(RightArmBumper.pressing()== true && LeftArmBumper.pressing() == false){ //if right bumper is pressed, only move the left arm down
        
          RightArm.setBrake(brakeType::coast);
          LeftArm.spin(vex::directionType::rev, ArmMotorVelocity, vex::velocityUnits::pct
          );
      
        } else if(RightArmBumper.pressing() == true && LeftArmBumper.pressing() == true){ //if both arm buttons are pressed, stop them from rotating

          RightArm.setBrake(brakeType::coast);
          LeftArm.setBrake(brakeType::coast);

        }



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
}



void Angler(){

  //this function will allow user to operate the angler to move the ramp
    if(AnglerBumperBack.pressing() == false){ //check if the ramp is not already it its maximum foward position for stacking
      if (Controller1.ButtonL1.pressing())
          {
            AnglerMotor.spin(vex::directionType::fwd, AnglerMotorSpeed, vex::velocityUnits::pct);
          

      } else if(Controller1.ButtonL2.pressing() && LeftArmBumper.pressing() == true){ //move ramp back only if the arms are down and lowered
          AnglerMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);

      } else {
          AnglerMotor.stop(vex::brakeType::hold); //hold the position of the ramp

      } 

    }


    if(AnglerBumperFront.pressing() == true){ //if the ramp is already in minumum position (intakeing)...
      if (Controller1.ButtonL1.pressing()) //move ramp back
          {
            AnglerMotor.spin(vex::directionType::fwd, AnglerMotorSpeed, vex::velocityUnits::pct);
          

      }  else {
          AnglerMotor.stop(vex::brakeType::hold);

      } 

    }


    
    if(AnglerBumperBack.pressing() == true){ //if the ramp is already in the maximum foward position for stacking
      if (Controller1.ButtonL2.pressing()) //only allow the ramp to move back
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
                MoveRamp();
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
