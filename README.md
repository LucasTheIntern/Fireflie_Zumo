1. "Arduino Flex Drive":
   - Arduino code for recieving drive commands either by usb serial from "Zumo_joystick_drive.py" or from the html webpage.
   - Same as "UNO receive and drive".
   - Open and flash with Arduino IDE.
2. "UNO receive and drive":
   - Arduino code for recieving drive commands either by usb serial from "Zumo_joystick_drive.py" or from the html webpage.
   - Same as "Arduino Flex Drive".
   - Open and flash with VS code and PIO extension.
3. "Wifi Zumo":
   - Code for SEEED XIAO module to act as access point for wifi control.
   - Open and flash using VS code and PIO extension.
   - To control with wifi,
       a. Power on Zumo
       b. On a laptop (doesn't work on mobile), find the "ESP32-Network" in available wifi networks and connect.
       c. When prompted for the network security key, enter "Esp32-Password".
       d. Once connected (will not have internet connection), Enter "http://192.168.4.1/" in a browser search bar.
       e. Click "Arm Zumo" and then drive as desired. Note that the webpage is buggy and often slow to respond... drive accordingly!
4. "Zumo_joystick_drive.py":
   - Python script for controlling the Zumo robot with a game controller.
   - May need to update your pygame and pyserial libraries if it's been a while.
   - To use, connect USB cable to the Arduino onboard the zumo and run the python script. I like to use VS code with the Jupyter notebooks extension... haven't tested otherwise.
   - Use the left joystick to control direction with differential steering. The controller has two buttons along the top "edge" The right one will increase the factor by which the input is scaled, and the left one will decrease it.
   - Much smoother and more reliable than wifi control, but requires a long and rather bulky cable to be attached.
   - CAN be used at the same time as wifi control, but this is NOT recommended! 
5. "SolidWorks":
   - CAD models (sldprt files) for the 3D printed mounts. 


Other notes:

The zumo robot can drive in a straight line continuously for approximately three hours on a full charge with no load. 

