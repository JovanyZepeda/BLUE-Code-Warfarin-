
#include <BlUE_Warfarin-Config.h>
//Variables for GYRO






/************************************************************************************************************************

/// GRYO PID Functions ==================================================================================================================================

*************************************************************************************************************************/

// PID Global Vairables---------------------------------------
// These need to be tuned experimentally to see what works; typically, Kp > Ki > Kd
float Kp = .8; //.8
float Ki = .1; //.1
float Kd = .1;


double CurrentDeg; // This the degree that the robot is pointing at at that moment

double LastError = 0;  // Initally, the last error is zero
double ErrorSum = 0;   //Initially, the error sum is zero

// Allows robot to rotate
// Theta goes from  -360 to 360 
void PIDGyroRotate( double TargetDeg ){
    
    while( CurrentDeg < TargetDeg || CurrentDeg > TargetDeg ){ //CurrentDeg < TargetDeg || CurrentDeg > TargetDeg

        CurrentDeg = Gyro.value(vex::rotationUnits::deg);
        double Error = TargetDeg - CurrentDeg;
        ErrorSum = ErrorSum + Error;
        LastError = Error;
        
        double Proportion = Error;
        double Integral = ErrorSum;
        double Derivative = (Error - LastError)/.005; // derivative is change in error over time, .005 is 
                                                       // the amount of miliseconds it takes to refresh
        if (Error == 0){
            Derivative = 0;
        }
        
        double PID = Kp * Proportion + Ki * Integral + Kd*Derivative; // Derivative portion may be removed if not necessary
        double DTR = ((360 * (RadiusRobotCM) * (PID * (3.14)/(180)))/(CircumferenceCM)); // DTR = Degrees to rotate
        // the variable PID is in deg so it must be converted to Radians, hence 3.14(pi)/180 above
        //DTR is the amount of degrees that the shaft must turn to reach targetDeg

        BackLeft.rotateFor(DTR,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
        BackRight.rotateFor(-DTR,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
        //FrontLeft.rotateFor(DTR,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct,false);
        //FrontRight.rotateFor(-DTR,vex::rotationUnits::deg,MotorVelocity,vex::velocityUnits::pct);
        //vex::task::sleep(50);

    }      
}

