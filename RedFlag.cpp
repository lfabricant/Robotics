#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void driveForward(double r){
    FrontRightWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    FrontLeftWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackRightWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackLeftWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,true);
}

void turnLeft(double r){
    FrontRightWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    FrontLeftWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackRightWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackLeftWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,true);
}

void turnRight(double r){
    FrontRightWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,false);
    FrontLeftWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackRightWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackLeftWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,true);
}

void strafeRight(double r){
    FrontRightWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,false);
    FrontLeftWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackRightWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackLeftWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,true);
}

void strafeLeft(double r){
    FrontRightWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,false);
    FrontLeftWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackRightWheel.rotateFor(-r,rotationUnits::rev,100,velocityUnits::pct,false);
    BackLeftWheel.rotateFor(r,rotationUnits::rev,100,velocityUnits::pct,true);
}

void shoot(){
    Shooter1.rotateFor(6,timeUnits::sec,100,velocityUnits::pct,false);
    Shooter2.rotateFor(6,timeUnits::sec,100,velocityUnits::pct,false);
    Loader.rotateFor(1,timeUnits::sec,100,velocityUnits::pct,true);
    
}

void load(double t){
    Loader.rotateFor(t,timeUnits::sec,100,velocityUnits::pct,true);
}



void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/




void autonomous( void ) {
    strafeLeft(0.5);
    driveForward(2);
    shoot();
    strafeRight(0.5);
    Flip.rotateTo(-160,rotationUnits::deg,50,velocityUnits::pct);
    driveForward(1.6);
    driveForward(-1.95);
    turnRight(2);
   
    driveForward(2.5);
    Flip.rotateTo(0,rotationUnits::deg,50,velocityUnits::pct);  
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

void flipUp(void){
    Flip.rotateTo(0,rotationUnits::deg,50,velocityUnits::pct);
}

void flipDown(void){
    Flip.rotateTo(-160,rotationUnits::deg,50,velocityUnits::pct);
}

void usercontrol( void ) {
    int vel=100;
    while (1){
        BackLeftWheel.spin(vex::directionType::fwd,(1.0*vel/100)*(Controller1.Axis3.value()-Controller1.Axis4.value()), vex::velocityUnits::pct);
        FrontLeftWheel.spin(vex::directionType::fwd,(1.0*vel/100)*(Controller1.Axis3.value()+Controller1.Axis4.value()), vex::velocityUnits::pct);
        BackRightWheel.spin(vex::directionType::fwd,(1.0*vel/100)*(Controller1.Axis2.value()+Controller1.Axis4.value()), vex::velocityUnits::pct);
        FrontRightWheel.spin(vex::directionType::fwd,(1.0*vel/100)*(Controller1.Axis2.value()-Controller1.Axis4.value()), vex::velocityUnits::pct);
    if (Controller1.ButtonR1.pressing()){
        Loader.spin(vex::directionType::rev, 50, velocityUnits::pct);
    }else if (Controller1.ButtonR2.pressing()){
        Loader.spin(vex::directionType::fwd, 50, velocityUnits::pct);
    }else{
        Loader.stop(brakeType::hold);
    }
         
    if (Controller1.ButtonUp.pressing()){
        Shooter1.spin(vex::directionType::fwd, 100000, velocityUnits::pct);
        Shooter2.spin(vex::directionType::rev, 100000, velocityUnits::pct);
    }else if (Controller1.ButtonDown.pressing()){
        Shooter1.spin(vex::directionType::rev, 100000, velocityUnits::pct);
        Shooter2.spin(vex::directionType::fwd, 100000, velocityUnits::pct);
    }else{
        Shooter1.stop(brakeType::hold);
        Shooter2.stop(brakeType::hold);
    }
       
    if (Controller1.ButtonL1.pressing()){
        if(Flip.rotation(rotationUnits::deg)<=0){
            Flip.spin(vex::directionType::fwd, 50, velocityUnits::pct);
        }else{
            Flip.stop(brakeType::hold);
        }
    }else if (Controller1.ButtonL2.pressing()){
        if(Flip.rotation(rotationUnits::deg)>=-160){
            Flip.spin(vex::directionType::rev, 50, velocityUnits::pct);
        }else{
             Flip.stop(brakeType::hold);
        }
    }else{
        Flip.stop(brakeType::hold);
    }

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
    }
}


int main() {
   
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100); //Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
