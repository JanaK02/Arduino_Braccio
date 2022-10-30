#include "PickAndPlaceRoutine.h/PickAndPlaceRoutine.h"
#include "RoboterControl.h/RoboterControl.h"
#include <Servo.h>
#include <Braccio.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
PickAndPlaceRoutine testRoutine;
RoboterControl testControls;
int start = 1;



void setup(){
  testRoutine.Routine(start);



};
 
void loop(){
  //testControls.Control(M1, M2, M3, M4, M5, M6);
  
}