import pandas as pd
import time
import math
import atexit
import serial
import struct
PORT = '/dev/tty.usbmodem14101'

class RobotControl:
    def __init__(self, path_direction):
        self.pathdirection = path_direction
        self.target_csv = f"../MazeSolutionPaths/" \
                          f"path_{self.pathdirection}.csv"
        self.motor_path = None
        self.start_time = None
        self.elapsed_time = 0
        self.arduino = serial.Serial(PORT, 9600, timeout=1)
        time.sleep(5) # TODO: Do a thing

    def load_path(self):
        try:
            self.motor_path = pd.read_csv(self.target_csv)
            return True
        except FileNotFoundError:
            print("File path is missing... Terminating execution")
            return False

    def execute_path(self):
        self.start_time = time.time()
        old_command = None
        parse_continue = True
        while parse_continue:
            try:
                target_index = list(self.motor_path["Time"]).index(math.floor(self.elapsed_time * 10) / 10)
                motor_command = [int(round(self.motor_path[" A' Angle"][target_index]) + 90),
                                 int(round(self.motor_path[" A Angle"][target_index]) + 90),
                                 int(round(self.motor_path[" B' Angle"][target_index]) + 90),
                                 int(round(self.motor_path[" B Angle"][target_index]) + 90),
                                 int(round(self.motor_path[" C' Angle"][target_index]) + 90),
                                 int(round(self.motor_path[" C Angle"][target_index]) + 90)]
                if tuple(motor_command) != old_command:
                    print("Alpha: " + str(self.motor_path[" alpha"][target_index]))
                    print("Beta: " + str(self.motor_path[" beta"][target_index]))
                    print("Time: " + str(self.motor_path["Time"][target_index]))
                    print(str(motor_command))
                    print(struct.pack(">BBBBBB", *motor_command))
                    self.arduino.write(struct.pack(">BBBBBB", *motor_command))
                old_command = tuple(motor_command)
                time.sleep(0.1) # TODO: Do a thing
                self.elapsed_time = time.time() - self.start_time
            except ValueError:
                parse_continue = False
        self.arduino.write(struct.pack(">BBBBBB", 90, 90, 90, 90, 90, 90))
        self.arduino.close()
        return True


if __name__ == '__main__':
    b1ue = RobotControl("2_to_1")
    command_list = [b1ue.load_path, b1ue.execute_path]
    for command in command_list:
        if not command():
            print(f"Something went wrong in {command.__name__}... Returning to manual control")
            exit()
    maze_solved = "Y"
    maze_solved = input('Is the maze solved? Y/n')
    if not(maze_solved.upper() == "Y"):
        print("Returning to manual control")
        exit()

