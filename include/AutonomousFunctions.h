#include <BlUE_Warfarin-Config.h>

#ifndef AUTOFUNCTIONS
#define AUTOFUNCTIONS

using namespace vex;



/*************************************************************************************************************************************

//Autonomous Functions =================================================================================================================

*************************************************************************************************************************************/



void AnglerAuto(int Config, double Revolutions, int speedPct) // if config =1, set angler to stacking position
                                                              //if config = -1, set anlger to intake position
{
    if(Config ==0 ){
    
    AnglerMotor.rotateFor(directionType::undefined,  Revolutions, rotationUnits::rev, speedPct, velocityUnits::pct);
    } else if(Config == 1){
        do{
          AnglerMotor.spin(directionType::fwd, speedPct, velocityUnits::pct); 
        } while (AnglerBumperBack.pressing() == false);

    } else if(Config == -1){

        do{
          AnglerMotor.spin(directionType::rev, speedPct, velocityUnits::pct); 
        } while (AnglerBumperFront.pressing() == false);
    
    }
  

}




void DriveReset(){
    BackLeft.resetRotation();
    BackRight.resetRotation();
    FrontLeft.resetRotation();
    FrontRight.resetRotation();
}


void DriveFoward ( double X, int speedPct ){

    
    BackLeft.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct,false);
    BackRight.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct);
    //FrontLeft.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct,false);
    //FrontRight.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct);
    }


void Intake(int option, int speed){
  /*if (option ==1)
        {
          LeftIntakeMotor.spin(vex::directionType::fwd, IntakeMotorVelocity, vex::velocityUnits::pct);
          RightIntakeMotor.spin(vex::directionType::rev, IntakeMotorVelocity, vex::velocityUnits::pct);
         } else if(option == -1)
          {   
            LeftIntakeMotor.spin(vex::directionType::rev, IntakeMotorVelocity, vex::velocityUnits::pct);
            RightIntakeMotor.spin(vex::directionType::fwd, IntakeMotorVelocity, vex::velocityUnits::pct);
          } else if(option ==0)
                  {
                    LeftIntakeMotor.stop(brakeType::hold);
                    RightIntakeMotor.stop(brakeType::hold);
                  }*/
      if (option ==1)
      {
          LeftIntakeMotor.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
          RightIntakeMotor.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
         } 
      else if(option == -1)
          {   
            LeftIntakeMotor.spin(vex::directionType::rev, speed, vex::velocityUnits::pct);
            RightIntakeMotor.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct);
          }
      else if(option ==0)
          {
              LeftIntakeMotor.stop(brakeType::hold);
              RightIntakeMotor.stop(brakeType::hold);
          }
      }


void DriveReverse ( double X, int speedPct  ){
    
    BackLeft.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct,false);
    BackRight.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct);
    //FrontLeft.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct, false);
    //FrontRight.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,speedPct,vex::velocityUnits::pct);
}

void DriveLeft( double X ){
    
    BackLeft.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    BackRight.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontLeft.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontRight.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);

}

void DriveRight(double X ){
    BackLeft.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    BackRight.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontLeft.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct, false);
    FrontRight.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
    
}


// Allows robot to rotate
// Theta goes from  -360 to 360 
void DriveRotate( double Theta ){
    
    DegreesToRevolve = (((360 * ((RadiusRobotCM) * (Theta * (PI)))  /  (180)) ) /  (CircumferenceCM)) * GearRatio ;
    
    BackLeft.rotateFor(DegreesToRevolve,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    BackRight.rotateFor(-DegreesToRevolve,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontLeft.rotateFor(DegreesToRevolve,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontRight.rotateFor(-DegreesToRevolve,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
}

// These allow robot to move diagnolly
void DriveFrontRightDiagnol( double X){
    BackLeft.stop(vex::brakeType::coast);
    BackRight.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontLeft.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
    FrontRight.stop(vex::brakeType::coast);
}

void DriveFrontLeftDiagnol( double X){
    BackLeft.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    BackRight.stop(vex::brakeType::coast);
    FrontLeft.stop(vex::brakeType::coast);
    FrontRight.rotateFor(X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);    
}

void DriveBackRightDiagnol( double X ){
    BackLeft.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    BackRight.stop(vex::brakeType::coast);
    FrontLeft.stop(vex::brakeType::coast);
    FrontRight.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
}

void DriveBackLeftDiagnol( double X ){
    BackLeft.stop(vex::brakeType::coast);
    BackRight.rotateFor(-X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
    FrontLeft.rotateFor( -X * DegreesToRotate,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
    FrontRight.stop(vex::brakeType::coast);    
}

void DriveStop(){
    BackLeft.stop(vex::brakeType::coast);
    BackRight.stop(vex::brakeType::coast);
    FrontLeft.stop(vex::brakeType::coast);
    FrontRight.stop(vex::brakeType::coast);
}

void Pre_auton(){  
    BackLeft.resetRotation();
    BackRight.resetRotation();
    FrontLeft.resetRotation();
    FrontRight.resetRotation();    
}



#endif AUTOFUNCTIONS