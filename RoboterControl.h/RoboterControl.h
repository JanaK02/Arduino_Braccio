#include <Braccio.h>
#include <Servo.h>

class RoboterControl {
  private:
    // declare roboter
    Servo base;
    Servo shoulder;
    Servo elbow;
    Servo wrist_rot;
    Servo wrist_ver;
    Servo gripper;
    
    // declare variables
    int keyVal = 0;                     // stores the analog value from the resistor ladder
    int Mkey = 0;                        // stores the button that is pressed
    int gripperbutton = 0;                // stores the state of the toggle button

    // declare pins
    const int servoPin = A0; 
    const int gripperPin = 3;

  public:
    void Control(int M1, int M2, int M3, int M4, int M5, int M6){
        Braccio.begin();
        pinMode(gripperPin, INPUT);
        //Starting position
                           //(step delay,  M1 , M2 , M3 , M4 , M5 , M6);
        //Braccio.ServoMovement(20,           0,  45, 180, 180,  90,  10);



        keyVal = analogRead(servoPin);                       // analog value of the key             // wait for a second
        gripperbutton = digitalRead(gripperPin);               // gripper button state
        
        /*
        if (keyVal > 1005) {Mkey = 1;}                       // first key is pressed
        else if (keyVal > 900) {Mkey = 2;}                   // second key is pressed  
        else if (keyVal > 800) {Mkey = 3;}                   // third key is pressed
        else if (keyVal > 400) {Mkey = 4;}                   // fourth key is pressed
        else {Mkey = 0;}                                     // no key is pressed
        
        // determine the note to play based on if the toggle button is up or down
       switch (gripperbutton) {
            case 0:
             //Open the gripper
             Braccio.ServoMovement(20,         M1,   M2, M3,  M4,  M5, 10);
             M6 = 10;
             break;
            
            case 1:
             //Close the gripper to take the sponge. Only the M6 servo will moves
             Braccio.ServoMovement(10,           M1,  M2, M3, M4,  M5,  M6 + 10 );
             M6 = M6 + 10;
             break;
        }

        // if a specific key is pressed, the corresponding servo moves; otherwise, don't move
        if (Mkey == 1) {
             Braccio.ServoMovement(20,           M1 + 10,  M2, M3, M4,  M5,   M6);
             M1 = M1 + 10;
             //Wait 1 second
             delay(1000);

        }
        else  if(Mkey == 2){
             Braccio.ServoMovement(20,           M1,  M2 + 10, M3, M4,  M5,   M6);
             M2 = M2 + 10;
             //Wait 1 second
             delay(1000);
             
        }
        else  if(Mkey == 3){
             Braccio.ServoMovement(20,           M1,  M2, M3 + 10, M4,  M5,   M6);
             M3 = M3 + 10;
             //Wait 1 second
             delay(1000);
        }
        else  if(Mkey == 4){
             Braccio.ServoMovement(20,           M1,  M2, M3, M4 + 10,  M5,   M6);
             M4 = M4 + 10;
             //Wait 1 second
             delay(1000);
        }
        */
    }

};