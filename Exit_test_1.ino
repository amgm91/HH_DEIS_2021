// Import The redbot h file
#include <RedBot.h>
// Define a macro for speed to simplify changing 
// the speed of the robot wihin the code
#define SPEED 100
// Define a macro for the value of the proximity sensor reading when 
// it detects a white trace
#define WHITE 50

// intiate IR Sensors
RedBotSensor Right_IR = RedBotSensor(A6);
RedBotSensor Left_IR = RedBotSensor(A7);
// intiate Motors
RedBotMotors motors;

void setup() {
  // put your setup code here, to run once:
  // Start a serial connection with baud rate 9600
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // this part check if there is a message on the serial connection 
  if (Serial.available() > 0) {
    // Read the message till you find '\n'
     String data = Serial.readStringUntil('\n');
     // if the received message is "fl" run the line follower function
     if (data == "fl"){
      line_follower();
      Serial.write("FL\n");
    }
    // if the received message is "f" move forward
    else if(data == "f"){
      forward();
      Serial.write("F\n");
    }
    // if the received message is "b" move backward
    else if(data == "b"){
      backward();
      Serial.write("B\n");
    }
    // if the received message is "l" run move left manuver
    else if(data == "l"){
      Serial.write("L\n");
      // move left for 0.5 second
      rotate_left();
      delay(500);
      // move forward for 0.5 seconds
      forward();
      delay(500);
    }
    // if the received message is "r" run move right manuver
    else if(data == "r"){
      Serial.write("R\n");
      // move right for 0.5 second
      rotate_right();
      delay(500);
      // move forward for 0.5 seconds
      forward();
      delay(500);
    }
    // if the received message is "s" stop
    else if(data == "s"){
      motors.stop();
      Serial.write("S\n");
    }
  }
}

// This function moves the robot forward
void forward(){
  motors.rightMotor(SPEED);
  motors.leftMotor(-SPEED);
}

// This function moves the robot backward
void backward(){
  motors.rightMotor(-SPEED);
  motors.leftMotor(SPEED);
}

// This function turn the robot left
void rotate_left(){
  motors.pivot(-SPEED);
}

// This function turns the robot right
void rotate_right(){
  motors.pivot(SPEED);
}


// This function makes the robot follow the black line and avoid 
// the white trace
void line_follower() {
  // if both sensors read black road.
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
