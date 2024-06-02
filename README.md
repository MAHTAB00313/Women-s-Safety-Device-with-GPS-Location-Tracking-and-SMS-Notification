# Women-s-Safety-Device-with-GPS-Location-Tracking-and-SMS-Notification
Women's Safety Device: A GPS and GSM based system using Arduino. Alerts emergency contacts via SMS with location link when a distress button is pressed. Ensures quick response during emergencies. Developed for enhanced safety and peace of mind.

Components Used
  1. Arduino board (e.g., Arduino Uno)
  2. GPS module (e.g., Ublox NEO-6M)
  3. GSM module (e.g., SIM900A)
  4. Buzzer
  5. Push button
  6. Connecting wires
  7. Setup Instructions

Hardware Setup:
  Connect the GPS module to Arduino:
    GPS RX to Arduino pin 4 (TX)
    GPS TX to Arduino pin 3 (RX)
    Connect the GSM module to Arduino:
    GSM RX to Arduino pin 7 (TX)
    GSM TX to Arduino pin 6 (RX)
    Connect the push button to Arduino pin 8 and ground.
    Connect the buzzer to Arduino pin 12 and ground.

Software Setup:
  1. Install Arduino IDE on your computer if not already installed.
  2. Clone or download the project repository from GitHub.
  3. Open the Arduino IDE, navigate to File -> Open, and open the .ino file from the downloaded repository.
  4. Upload Code to Arduino:

  5. Select the correct board and COM port from Tools menu in Arduino IDE.

  6. Click on the upload button to compile and upload the code to Arduino.
  7. Configure Phone Number:

Replace phoneNumber[] with the emergency contact's phone number in the code (+91xxxxxxxxx).

Testing:
  Power the Arduino using a USB cable or external power source.
  Wait until the GPS module acquires satellite signals (LED indicator on GPS module stops blinking).
  Press the push button to trigger the device:
  It will fetch GPS coordinates, alert with a buzzer, and send an SMS with a Google Maps location link to the configured phone number.

Deployment:
  Mount the device in a secure and accessible location (e.g., bag, pocket).
  Ensure the device is charged or connected to a power source for continuous operation.
  Additional Notes
  Ensure the GSM module has an active SIM card with sufficient balance for SMS transmission.
  Test the device in different locations to ensure GPS reception is reliable.
