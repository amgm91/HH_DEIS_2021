// Import The redbot h file
#include <RedBot.h>
// Define a macro for speed to simplify changing 
// the speed of the robot wihin the code
#define SPEED 200
// Define a macro for the value of the proximity sensor reading when 
// it detects a white trace
#define WHITE 10

RedBotSensor Right_IR = RedBotSensor(A6);
RedBotSensor Left_IR = RedBotSensor(A7);
// intiate Motors
RedBotMotors motors;

void setup() {
  // put your setup code here, to run once:
  // Make sure that the robot is stopped when the code runs for the first time
  motors.stop();
  // Start a serial connection with baud rate 9600
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  // this part check if there is a message on the serial connection 
  if (Serial.available() > 0) {
    // Read the message till you find '\n'
    String data = Serial.readStringUntil('\n');
    // if the received message is "f" move forward
    if (data == "f"){
      forward();
      // Print Forward on the monitor, this was used as a check to make sure that 
      // the forward command was successfully ran
      Serial.write("Forward\n");
    }
    // if the received message is "b" move backwards
    else if(data == "b"){
      backward();
      Serial.write("Backward\n");
    }
    // if the received message is "l" turn left
    else if(data == "l"){
      rotate_left();
      Serial.write("Left\n");
    }
    // if the received message is "r" turn right
    else if(data == "r"){
      rotate_right();
      Serial.write("Right\n");
    }
    // if the received message is "s" stop
    else if(data == "s"){
      motors.stop();
      Serial.write("Stop\n");
    }
  }
}

// This function moves the robot forward
void forward(){
  motors.rightMotor(SPEED);
  motors.leftMotor(-SPEED);
}

// This function moves the robot backwards
void backward(){
  motors.rightMotor(-SPEED);
  motors.leftMotor(SPEED);
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
