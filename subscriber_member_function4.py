import rclpy
from rclpy.node import Node

from std_msgs.msg import String
import serial
import time


class MinimalSubscriber(Node):

    def __init__(self):
        super().__init__('minimal_subscriber')
        self.subscription = self.create_subscription(
            String,
            'robotPositions',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        # Subscribe to 'robotPositions' topic to get location from GPS Server

    def listener_callback(self, msg):
        # open a serial connection with baud rate 9600
        ser = serial.Serial('/dev/uno', 9600, timeout = 1)
        # This part seperates the x and y of spiral 7 from the data sent by 
        # the GPS server and it gets the 6th part as the count starts from 0        
        s = msg.data.split(';')[6].split(' ')
        x = float(s[0])
        y = float(s[1])
        # Print the X and Y, this was used to tune the below values
        print("x = %d, y = %d" % (x,y))
        # these dimentions means that the robot is next to the right side road
        # it should turn right to exit the roundabout
        if((x > 90 and x < 300)and(y > 370 and y < 650)):
            print("Right")
            # Send a command to arduino to turn the robot right
            ser.write(str.encode("r\n"))
        # these dimentions means that the robot is next to the left side road
        # it should turn left to exit the roundabout
        elif((x > 730 and x < 920)and(y > 330 and y < 650)):
            print("Left")
            # Send a command to arduino to turn the robot left
            ser.write(str.encode("l\n"))
        # these dimentions means that the robot is in the right lane of the 
        # enterance, it should turn right to enter the roundabout    
        elif((x > 400 and x < 500)and(y > 980 and y < 1050)):
            print("Right Start")
            # Send a command to arduino to turn the robot right
            ser.write(str.encode("r\n"))
        # these dimentions means that the robot is in the left lane of the
        # enterance, it should turn left to enter the roundabout
        elif((x > 510 and x < 600)and(y > 980 and y < 1050)):
            print("Left Start")
            # Send a command to arduino to turn the robot left
            ser.write(str.encode("l\n"))        
        # if the robot is at any other location, run the line follwer part of the code.
        else:
             print("Follow Line")
             # Send a command to arduino to run the line follower part
             ser.write(str.encode("fl\n"))


def main(args=None):
    rclpy.init(args=args)

    minimal_subscriber = MinimalSubscriber()

    rclpy.spin(minimal_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    minimal_subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()