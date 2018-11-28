import pandas as pd
import time
import math
import atexit
import serial
import struct

class RobotControl:
    _FWD_PATH_FILE = "../MazeSolutionPaths/forward_12.csv"
    _BACK_PATH_FILE = "../MazeSolutionPaths/backward_1.csv"
    # _CORRECTION_FILE = "correction_jerk.csv"
    _PORT = '/dev/tty.usbmodem14101'

    def __init__(self):
        # TODO: Change these to forward and backwards paths
        self.backward_path = None
        self.forward_path = None
        self.correction_jerk = None
        self.arduino = None

    def check_ldr(self):
        if self.arduino.read() == 1:
            return True
        else:
            return False

    def close_arduino(self):
        print("Closing arduino port")
        #self.arduino.close()

    def initialize_arduino(self):
        try:
            self.arduino = serial.Serial(RobotControl._PORT, 9600, timeout=1)
            # Make sure we don't send serial commands immediately
            time.sleep(5)
        except serial.SerialException as e:
            print(f"An error has occurred while trying to connect to the Arduino: \n{e}")
            return False
        return True

    def initialize_files(self):
        try:
            self.backward_path = pd.read_csv(RobotControl._BACK_PATH_FILE)
        except FileNotFoundError:
            print("Path 1-2 file path is missing... Terminating execution")
            return False
        try:
            self.forward_path = pd.read_csv(RobotControl._FWD_PATH_FILE)
        except FileNotFoundError:
            print("Path 2-1 file path is missing... Terminating execution")
            return False
        # try:
        #     self.correction_jerk = pd.read_csv(RobotControl._CORRECTION_FILE)
        # except FileNotFoundError:
        #     print("Correction file path is missing... Terminating execution")
            return False
        print("File initialized...")
        return True

    def execute_move(self, command_dir):
        # TODO: Make these an enum or something nicer
        if command_dir == "12":
            motor_path = self.backward_path
        elif command_dir == "21":
            motor_path = self.forward_path
        elif command_dir == "vibe":
            motor_path = self.correction_jerk
        else:
            print("Invalid move command")
            return False

        # Get the time before starting the solve
        start_time = time.time()
        elapsed_time = 0
        old_command = None
        parse_continue = True
        while parse_continue:
            try:
                target_index = list(motor_path["Time"]).index(math.floor(elapsed_time * 10) / 10)
                # Need to add 90-deg to each position since the Arduino
                # doesn't understand negative angles
                motor_command = [int(round(motor_path[" A' Angle"][target_index]) + 90),
                                 int(round(motor_path[" A Angle"][target_index]) + 90),
                                 int(round(motor_path[" B' Angle"][target_index]) + 90),
                                 int(round(motor_path[" B Angle"][target_index]) + 90),
                                 int(round(motor_path[" C' Angle"][target_index]) + 90),
                                 int(round(motor_path[" C Angle"][target_index]) + 90)]
                # Don't do anything if the new position is the same as the old position
                if tuple(motor_command) != old_command:
                    print("Alpha: " + str(motor_path[" alpha"][target_index]))
                    print("Beta: " + str(motor_path[" beta"][target_index]))
                    print("Time: " + str(motor_path["Time"][target_index]))
                    print(str(motor_command))
                    print(struct.pack(">BBBBBB", *motor_command))
                    self.arduino.write(struct.pack(">BBBBBB", *motor_command))
                old_command = tuple(motor_command)
                # time.sleep(0.1) # Delay between sending commands
                elapsed_time = time.time() - start_time
            except ValueError:
                parse_continue = False
        return True

if __name__ == '__main__':
    continue_run = True
    platform_mover = RobotControl()
    platform_mover.initialize_arduino()
    if not platform_mover.initialize_files():
        exit()
    M1to2 = "12"
    M2to1 = "21"
    Mreset = "vibe"
    while continue_run:
        solve_direction = input("Please enter:\n"
                                "1 for solving direction forward path (for marks)\n"
                                "2 for solving direction backwards path\n"
                                "Anything else to exit...\n")
        if solve_direction == '1':
            platform_mover.execute_move(M2to1)
            if platform_mover.check_ldr():
                print("Maze solved in direction 21")
                continue
            else:
                print("Vibing big time")
                platform_mover.execute_move(Mreset)
                if platform_mover.check_ldr():
                    print("Maze solved in direction 21")
                    continue
                else:
                    print("Resetting reverse")
                    platform_mover.execute_move(M1to2)
                    platform_mover.execute_move(M2to1)
        elif solve_direction == '2':
            platform_mover.execute_move(M1to2)
            print("Maze solved in direction 12")
        else:
            print("Terminating program....")
            platform_mover.close_arduino()
            continue_run = False
    platform_mover.close_arduino()

