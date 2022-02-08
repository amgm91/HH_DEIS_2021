// Import The redbot h file
#include <RedBot.h>
// Define a macro for speed to simplify changing 
// the speed of the robot wihin the code
#define SPEED 120
// Define a macro for the value of the proximity sensor reading when 
// it detects a white trace
#define WHITE 10

// intiate IR Sensors
RedBotSensor Right_IR = RedBotSensor(A6);
RedBotSensor Left_IR = RedBotSensor(A7);
// intiate Motors
RedBotMotors motors;


void setup() {
  
}

void loop() {
  // Check the reading of the 2 proximity sensors
  
    // if both read black road.
    // Move forward
    if(Right_IR.read() > WHITE && Left_IR.read() > WHITE)
    {
      forward();
    }
    // if the right sensor detects white trace and left sensor 
    // detects black road.
    // Turn left
    else if(Right_IR.read() < WHITE && Left_IR.read() > WHITE)
    {
     rotate_left();
    }
    // if the right sensor detects black road and left sensor 
    // detects white trace.
    // Turn right
    else if (Right_IR.read() > WHITE && Left_IR.read() < WHITE)
    {
     rotate_right();
    }
    // if both sensors detect white trace it means that the robot is 
    // outside of the road.
    // Stop the robot
    else if(Right_IR.read() < WHITE && Left_IR.read() < WHITE)
    {
     motors.stop();
    }
}

// This function moves the robot a step forward then stops 
void forward(){
  motors.rightMotor(SPEED);
  motors.leftMotor(-SPEED);
  delay(50);
  motors.stop();
}

// This function uses the pivot command from the redbot library to 
// rotate the robot to the left 
void rotate_left(){
  motors.pivot(-SPEED);
}

// This function uses the pivot command from the redbot library to 
// rotate the robot to the right
void rotate_right(){
  motors.pivot(SPEED);
}
