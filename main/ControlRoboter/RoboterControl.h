#include <Braccio.h>
#include <Servo.h>

#define M1 20 // Analog Wert des Tasters (Pin A1) 220 Ohm
#define M2 51 // Analog Wert des Tasters (Pin A1) 560 Ohm
#define M3 91 // Analog Wert des Tasters (Pin A1) 1k Ohm
#define M4 217 // Analog Wert des Tasters (Pin A1) 2.7k Ohm
#define M5 325 // Analog Wert des Tasters (Pin A1) 4.7k Ohm
#define M6 440 // Analog Wert des Tasters (Pin A1) 7.5k Ohm


class RoboterControl {
  private:
     // declare roboter
     Servo base;
     Servo shoulder;
     Servo elbow;
     Servo wrist_rot;
     Servo wrist_ver;
     Servo gripper;
     int geschwindigkeit;
     int motor1 = 90; // 0 bis 180
     int motor2 = 80; // 15 bis 165
     int motor3 = 90; // 0 bis 180
     int motor4 = 0; // 0 bis 180
     int motor5 = 0; // 0 bis 180
     int motor6 = 10; // 10 bis 73
    
  public:
    void Controlling(int analogTaster, int analogPoti){
     if(0 == analogPoti || 0 < analogPoti && analogPoti < 341){
          geschwindigkeit = 10;
          Movement(analogTaster, geschwindigkeit);
          Serial.println("Speed 10");
     }
     else if (341 == analogPoti || 341 < analogPoti && analogPoti < 682 || analogPoti == 682){
          geschwindigkeit = 20;
          Movement(analogTaster, geschwindigkeit);
          Serial.println("Speed 20");
     }
     else if (682 < analogPoti && analogPoti< 1023 || analogPoti == 1023){
          geschwindigkeit = 30;
          Movement(analogTaster, geschwindigkeit);
          Serial.println("Speed 30");
     }

    };

    void Movement (int analogTaster, int geschwindigkeit){
     Serial.println("Success method");
     switch (analogTaster) {
          case M1: 
               if(motor1 >= 180){
                    motor1 = motor1 - 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    // Zuruecksetzen auf Anfangsposition des Motors 1
                    motor1 = 0;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M1");
               } 
               else{
                    motor1 = motor1 + 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M1");
                    }
               break;

          case M2: 
          if(motor2 >= 165){
                    motor2 = motor2 - 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    // Zuruecksetzen auf Anfangsposition des Motors 2
                    motor2 = 80;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M2");
               } 
               else{
                    motor2 = motor2 + 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M2");
                    }
               break;

          case M3: 
               if(motor3 >= 180){
                    motor3 = motor3 - 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    // Zuruecksetzen auf Anfangsposition des Motors 3
                    motor3 = 30;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M3");
               } 
               else{
                    motor3 = motor3 + 10; 
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M3");
                    }
               break;

          case M4:  
               if(motor4 >= 180){
                    motor4 = motor4 - 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    // Zuruecksetzen auf Anfangsposition des Motors 4
                    motor4 = 0;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M4");
               } 
               else{
                    motor4 = motor4 + 10; 
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M4");
                    }
               break;

          case M5:  
               if(motor5 >= 180){
                    motor5 = motor5 - 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    // Zuruecksetzen auf Anfangsposition des Motors 5
                    motor5 = 0;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M5");
               } 
               else{
                    motor5 = motor5 + 10; 
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M5");
                    }
               break;

          case M6: 
               if(motor6 >= 73){
                    motor6 = motor6 - 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    // Zuruecksetzen auf Anfangsposition des Motors 6
                    motor6 = 10;
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M6");
               } 
               else{
                    motor6 = motor6 + 10; 
                    Braccio.ServoMovement(geschwindigkeit, motor1, motor2, motor3, motor4, motor5, motor6);
                    Serial.println("Motor M6");
                    }
               break;
          }

    }

};