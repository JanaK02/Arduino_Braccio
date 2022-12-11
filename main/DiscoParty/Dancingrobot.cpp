#include <Braccio.h>
#include <Servo.h>

void dancingrobot(){
    Servo base;
    Servo shoulder;
    Servo elbow;
    Servo wrist_rot;
    Servo wrist_ver;
    Servo gripper;


          /*
          Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
          M1=base degrees. Allowed values from 0 to 180 degrees
          M2=shoulder degrees. Allowed values from 15 to 165 degrees
          M3=elbow degrees. Allowed values from 0 to 180 degrees
          M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
          M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
          M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
          */


    Braccio.ServoMovement(10,           0,     45, 180, 180,   90,   10);
    Braccio.ServoMovement(10,         180,     45, 180, 180,  110,   73);
    Braccio.ServoMovement(10,         180,    135,   0,  20,   10,   73);
    Braccio.ServoMovement(10,         180,    135,   0,  20,   40,   10);
    
}