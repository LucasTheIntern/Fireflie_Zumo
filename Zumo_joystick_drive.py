#%% 0 = A
# 1 = B
# 2 = X
# 3 = Y
# 4 = LEFT_FIRE
# 5 = RIGHT_FIRE
# 6 = BACK
# 7 = START
# 8 = LEFT_JOYSTICK_PRESS
# 9 = RIGHT_JOYSTICK_PRESS
# axis 0 = Left_Joystick_FB
# axis 1 = Left_Joystick_LR
# axis 2 = Right_Joystick_LR
# axis 3 = Right_Joystick_FB
# hat 0 = pad

import serial
import pygame
import serial.tools.list_ports
import time

# Create a serial connection
ports = list(serial.tools.list_ports.comports())
for p in ports:
    if 'USB Serial Device' in p.description:
        ser = serial.Serial(p.device, 9600)
        print(f'Connected to {p.description} on port {p.device}')
        break

print('Use left joystick to move the robot. Press ESC to exit.')

# Initialize pygame
pygame.init()

# Initialize the joystick
pygame.joystick.init()

# Assume that we have a joystick
joystick = pygame.joystick.Joystick(0)
joystick.init()

speedfactor = 1 # integer between 1 and 4

try:
    while True:
        # Required to get latest events
        pygame.event.pump()

        # Get directions and magnitudes for both joysticks
        left_joystick_direction = (joystick.get_axis(0), joystick.get_axis(1))
        left_joystick_magnitude = (abs(left_joystick_direction[0]), abs(left_joystick_direction[1]))

        right_joystick_direction = (joystick.get_axis(2), joystick.get_axis(3))
        right_joystick_magnitude = (abs(right_joystick_direction[0]), abs(right_joystick_direction[1]))

        # Get action button states
        action_button_states = [joystick.get_button(i) for i in range(joystick.get_numbuttons())]

        # Print the information
        # print(f"Left joystick: direction {left_joystick_direction}, magnitude {left_joystick_magnitude}")
        # print(f"Right joystick: direction {right_joystick_direction}, magnitude {right_joystick_magnitude}")
        # print(f"Action button states: {action_button_states}")

        if action_button_states[5] == 1:
            speedfactor = speedfactor + 1
            if speedfactor > 4:
                speedfactor = speedfactor - 1
            time.sleep(0.5)
        if action_button_states[4] == 1:
            speedfactor = speedfactor - 1
            if speedfactor < 1:
                speedfactor = speedfactor + 1
            time.sleep(0.5)

        # Wait for a second
        time.sleep(0.01)

        # Map directions from left joystick to range [-100, 100]
        Speed = int(-100 * left_joystick_direction[1])*speedfactor
        Differential = int(100 * left_joystick_direction[0])*speedfactor
        
        # Get wheel speeds
        speedLeft = Speed + Differential
        speedRight = Speed - Differential

        # send wheel speeds over serial
        ser.write(f'{speedLeft},{speedRight}\n'.encode())

except KeyboardInterrupt:
    print("Exiting")
    pygame.quit()