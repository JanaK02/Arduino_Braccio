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
    void RoutineFirst() 
    {
      //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
      Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
      // Warte 1 Sekunde
      delay(1000);
      // Bewegt den Schwamm
      Braccio.ServoMovement(20,           0,  93, 180, 180,  90,   10);
      // Schließt den Greifer, um den Schwamm anzuheben 
      Braccio.ServoMovement(10,           0,  93, 180, 180,  90,  73 );
      // Bewegt den Schwamm nach oben
      //Braccio.ServoMovement(20,         0,   45, 135,  45,  0, 73);

    };

    void RoutineSecond()
    {
                                //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
      Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);        
      // Warte 1 Sekunde
      delay(1000);
      // Bewegt den Schwamm 
      Braccio.ServoMovement(20,           0,  103, 180, 180,  90,   10);
      // Schließt den Greifer, um den Schwamm anzuheben 
      Braccio.ServoMovement(10,           0,  103, 180, 180,  90,  73 );
      // Bewegt den Schwamm nach oben
      //Braccio.ServoMovement(20,         0,   45, 135,  45,  0, 73);

    };

    void RoutineThird()
    {
                                //(step delay  M1 , M2 , M3 , M4 , M5 , M6);
      Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);
      // Warte 1 Sekunde
      delay(1000);
      // Bewegt den Schwamm
      Braccio.ServoMovement(20,           0,  110, 180, 180,  90,   10);
      // Schließt den Greifer, um den Schwamm anzuheben 
      Braccio.ServoMovement(10,           0,  110, 180, 180,  90,  73 );
      // Bewegt den Schwamm nach oben
      //Braccio.ServoMovement(20,         0,   45, 135,  45,  0, 73);

    };

    
    void SensorPosition()
    {
      Braccio.ServoMovement(20,         90,   90, 163,  180,  90, 73);
    };


    void ColorSort(char color)
    {
      /*
        Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
        M1=base degrees. Allowed values from 0 to 180 degrees
        M2=shoulder degrees. Allowed values from 15 to 165 degrees
        M3=elbow degrees. Allowed values from 0 to 180 degrees
        M4=wrist vertical degrees. Allowed values from 0 to 180 degrees
        M5=wrist rotation degrees. Allowed values from 0 to 180 degrees
        M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
      */

      switch(color)
      {
          case '1':
              // Farbe Rot

              // Bewegt den Schwamm ueber den Becher
              Braccio.ServoMovement(20,         90,   135, 30,  0,  90, 73);

              // Warte 1 Sekunde
              delay(1000);

              // Laesst den Schwamm in den Becher fallen
              Braccio.ServoMovement(20,         90,   135, 30,  0,  90, 10);

              break;

          case '2':
              // Farbe Gruen

              // Bewegt den Schwamm ueber den Becher
              Braccio.ServoMovement(20,         45,   135, 30,  0,  90, 73);

              // Warte 1 Sekunde
              delay(1000);

              // Laesst den Schwamm in den Becher fallen
              Braccio.ServoMovement(20,         45,   135, 30,  0,  90, 10);

              break;

          case '3':
              // Farbe Blau

              // Bewegt den Schwamm ueber den Becher
              Braccio.ServoMovement(20,         0,   135, 30,  0,  90, 73);

              // Warte 1 Sekunde
              delay(1000);

              // Laesst den Schwamm in den Becher fallen
              Braccio.ServoMovement(20,         0,   135, 30,  0,  90, 10);

              break;
                  
          default: 
              // Keine Farbe
              break;
      }
    };
   

};