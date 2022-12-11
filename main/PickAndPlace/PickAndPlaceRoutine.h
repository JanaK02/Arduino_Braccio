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

  public:
    void Routine(){
        
          
          /*
          Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
          M1=base degrees. Allowed values from 0 to 180 degrees
          M2=shoulder degrees. Allowed values from 15 to 165 degrees
          M3=elbow degrees. Allowed values from 0 to 180 degrees
          M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
          M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
          M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
          */

          // Erster Schwamm
                              //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
          Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
          
          // Warte 1 Sekunde
          delay(1000);

          // Bewegt den Schwamm 
          Braccio.ServoMovement(20,           0,  90, 180, 180,  90,   10);

          // Schließt den Greifer, um den Schwamm anzuheben 
          Braccio.ServoMovement(10,           0,  90, 180, 180,  90,  73 );

          // Bewegt den Schwamm nach oben
          Braccio.ServoMovement(20,         0,   45, 135,  45,  0, 73);

          // Bewegt den Schwamm ueber den Becher
          Braccio.ServoMovement(20,         90,   135, 30,  0,  90, 73);

          // Warte 1 Sekunde
          delay(1000);

          // Laesst den Schwamm in den Becher fallen
          Braccio.ServoMovement(20,         90,   135, 30,  0,  90, 10);




          // Zweiter Schwamm
                              //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
          Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
          
          // Warte 1 Sekunde
          delay(1000);

          // Bewegt den Schwamm 
          Braccio.ServoMovement(20,           0,  90, 180, 180,  90,   10);

          // Schließt den Greifer, um den Schwamm anzuheben 
          Braccio.ServoMovement(10,           0,  90, 180, 180,  90,  73 );

          // Bewegt den Schwamm nach oben
          Braccio.ServoMovement(20,         0,   45, 135,  45,  0, 73);

          // Bewegt den Schwamm ueber den Becher
          Braccio.ServoMovement(20,         45,   135, 30,  0,  90, 73);

          // Warte 1 Sekunde
          delay(1000);

          // Laesst den Schwamm in den Becher fallen
          Braccio.ServoMovement(20,         45,   135, 30,  0,  90, 10);




          // Dritter Schwamm
                              //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
          Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
          
          // Warte 1 Sekunde
          delay(1000);

          // Bewegt den Schwamm 
          Braccio.ServoMovement(20,           0,  90, 180, 180,  90,   10);

          // Schließt den Greifer, um den Schwamm anzuheben 
          Braccio.ServoMovement(10,           0,  90, 180, 180,  90,  73 );

          // Bewegt den Schwamm nach oben
          Braccio.ServoMovement(20,         0,   45, 135,  45,  0, 73);

          // Bewegt den Schwamm ueber den Becher
          Braccio.ServoMovement(20,         0,   135, 30,  0,  90, 73);

          // Warte 1 Sekunde
          delay(1000);

          // Laesst den Schwamm in den Becher fallen
          Braccio.ServoMovement(20,         0,   135, 30,  0,  90, 10);

      
    }

};