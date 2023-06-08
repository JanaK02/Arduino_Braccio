#include "KeyboardCat.cpp"

void dancing(){
    music();
    Braccio.ServoMovement(20,           0,     45, 180, 180,   90,   10);
    Braccio.ServoMovement(20,         180,     45, 180, 180,  110,   73);
    Braccio.ServoMovement(20,         180,    135,   0,  20,   10,   73);
    Braccio.ServoMovement(20,         180,    135,   0,  20,   40,   10);
    
}