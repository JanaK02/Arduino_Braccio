#include <Braccio.h>
#include <Servo.h>

class PickAndPlaceRoutine {
  private:
    Servo base;
    Servo shoulder;
    Servo elbow;
    Servo wrist_rot;
    Servo wrist_ver;
    Servo gripper;
    int start;

  public:
    void Routine(int start){
        if(start == 1 ) {
          Braccio.begin();
          /*
          Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
          M1=base degrees. Allowed values from 0 to 180 degrees
          M2=shoulder degrees. Allowed values from 15 to 165 degrees
          M3=elbow degrees. Allowed values from 0 to 180 degrees
          M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
          M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
          M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
          */

          //Starting position
                              //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
          Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
          
          //Wait 1 second
          delay(1000);

          //The braccio moves to the sponge. Only the M2 servo will moves
          Braccio.ServoMovement(20,           0,  90, 180, 180,  90,   10);

          //Close the gripper to take the sponge. Only the M6 servo will moves
          Braccio.ServoMovement(10,           0,  90, 180, 180,  90,  60 );

          //Brings the sponge upwards.
          Braccio.ServoMovement(20,         0,   45, 180,  45,  0, 60);

          //Show the sponge. Only the M1 servo will moves
          Braccio.ServoMovement(20,         180,  45, 180,   45,   0,  60);

          //Return to the start position.
          Braccio.ServoMovement(20,         0,   90, 180,  180,  90, 60);

          //Open the gripper
          Braccio.ServoMovement(20,         0,   90, 180,  180,  90, 10 );

      }
      else if (start == 0){
         //Wait 1 second
          delay(1000);
      }
    }

};