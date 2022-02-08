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
            'action',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        # Subscribe to the 'action' topic to receive commands from 
        # GPS Server

    def listener_callback(self, msg):
        # start a serial connection with baud rate of 9600
        ser = serial.Serial('/dev/uno', 9600, timeout = 1)
        
        # Check the message received
        
        # if it contains "120;120", make the command "f\n"
        # it makes the arduino move the robot forward
        if "120;120" in msg.data:
            m = "f\n"
        # if it contains "-120;-120", make the command "b\n"
        # it makes the arduino move the robot backward    
        elif "-120;-120" in msg.data:
            m = "b\n"
        # if it contains "0;120", make the command "l\n"
        # it makes the arduino move the robot left    
        elif "0;120" in msg.data:
            m = "l\n"
        # if it contains "120;0", make the command "r\n"
        # it makes the arduino move the robot right    
        elif "120;0" in msg.data:
            m = "r\n"
        # if it contains "0;0", make the command "s\n"
        # it makes the arduino stop the robot   
        elif "0;0" in msg.data:
            m = "s\n"
            
        # Send the command to the arduino using the serial connection 
        # and encode the message to utf-8 required by the arduino 
        # to understand the message
        ser.write(str.encode(m))


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