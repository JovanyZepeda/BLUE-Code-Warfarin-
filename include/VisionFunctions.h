#include <BlUE_Warfarin-Config.h>
#include <Blue-WF-VIsionConfig.h>
#include <AutonomousFunctions.h>



/*************************************************************************************************************************************

// Vision Functions =====================================================================================================================

*************************************************************************************************************************************/
void VisionFoward(){
    BackLeft.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    BackRight.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    FrontLeft.spin(vex::directionType::fwd,50, vex::velocityUnits::pct);
    FrontRight.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
}

void VisionBackward(){
    BackLeft.spin(vex::directionType::rev, VisionMotorVelocity, vex::velocityUnits::pct);
    BackRight.spin(vex::directionType::rev, VisionMotorVelocity, vex::velocityUnits::pct);
    FrontLeft.spin(vex::directionType::rev, VisionMotorVelocity, vex::velocityUnits::pct);
    FrontRight.spin(vex::directionType::rev, VisionMotorVelocity, vex::velocityUnits::pct);
}


void VisionLeft( ){
    
    BackLeft.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct);   // rev
    BackRight.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct);  //fwd
    FrontLeft.spin(vex::directionType::fwd, VisionMotorVelocity,vex::velocityUnits::pct);  // fwd
    FrontRight.spin(vex::directionType::rev, VisionMotorVelocity,vex::velocityUnits::pct);       //rev
}

void VisionRight(){
    BackLeft.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct);    //fwd
    BackRight.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct);   //rev
    FrontLeft.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct);   //rev
    FrontRight.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct);  //fwd
}


void VisionRotateLeft(){   
    BackLeft.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct); //fwd
    BackRight.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct); //rev
    FrontLeft.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct);  //fwd
    FrontRight.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct); // rev
}


void VisionRotateRight(){   
    BackLeft.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct); //rev
    BackRight.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct); //fwd
    FrontLeft.spin(vex::directionType::rev,VisionMotorVelocity,vex::velocityUnits::pct);  //rev
    FrontRight.spin(vex::directionType::fwd,VisionMotorVelocity,vex::velocityUnits::pct); // fwd
}


void VisionDetect1(){
     Vision1.takeSnapshot(1);
    if (Vision1.largestObject.exists && Vision1.largestObject.width>5){
        ActualX = Vision1.largestObject.centerX;
        ActualY = Vision1.largestObject.centerY;
    }
}

void VisionDetect2(){
     Vision1.takeSnapshot(2);
    if (Vision1.largestObject.exists && Vision1.largestObject.width>5){
        ActualX = Vision1.largestObject.centerX;
        ActualY = Vision1.largestObject.centerY;
    }
}

void VisionDetect3(){
     Vision1.takeSnapshot(3);
    if (Vision1.largestObject.exists && Vision1.largestObject.width>5){
        ActualX = Vision1.largestObject.centerX;
        ActualY = Vision1.largestObject.centerY;
    }
}


void VisionTest1(){
   
   VisionDetect1();
        
        if( ActualX < DesiredX - Offset){
            VisionRotateRight();
            vex::task::sleep(5);
            DriveStop();
        } else
        if( ActualX > DesiredX - Offset){
            VisionRotateLeft();
            vex::task::sleep(5);
            DriveStop();
        } 

       if(ActualX > DesiredX - Offset && ActualX < DesiredX + Offset){
            VisionFoward();
            vex::task::sleep(20);
            DriveStop();
       }
} 


void VisionTest2(){
   
   VisionDetect2();
        
        if( ActualX < DesiredX - Offset){
            VisionRight();
            vex::task::sleep(5);
            DriveStop();
        } else
        if( ActualX > DesiredX - Offset){
            VisionLeft();
            vex::task::sleep(5);
            DriveStop();
        } 

       if(ActualX > DesiredX - Offset && ActualX < DesiredX + Offset){
            VisionFoward();
            vex::task::sleep(20);
            DriveStop();
       }
} 


void VisionTest3(){
   
   VisionDetect3();
        
        if( ActualX < DesiredX - Offset){
            VisionRight();
            vex::task::sleep(5);
            DriveStop();
        } else
        if( ActualX > DesiredX - Offset){
            VisionLeft();
            vex::task::sleep(5);
            DriveStop();
        } 

       if(ActualX > DesiredX - Offset && ActualX < DesiredX + Offset){
            VisionFoward();
            vex::task::sleep(20);
       if (Vision1.largestObject.width > 120){
            DriveStop();
            }
       }
} 

