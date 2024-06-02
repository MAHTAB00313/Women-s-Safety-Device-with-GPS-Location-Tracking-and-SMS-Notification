#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Create a SoftwareSerial object to communicate with the GPS and GSM modules
SoftwareSerial ss(3, 4); // RX, TX for GPS
SoftwareSerial gsmSerial(6, 7); // RX, TX for GSM

String gMap = "http://www.google.com/maps/place/";

// Pin definitions
const int btn = 8;
const int buzzer = 12;

bool check = true;

// Phone number to send the SMS to
char phoneNumber[] = "+918860805572";

// Create a TinyGPSPlus object
TinyGPSPlus gps;

// Variables to store GPS data
double lat = 0.0;
double lng = 0.0;

void setup() {
  // Start the serial communication for debugging
  Serial.begin(9600);
  
  // Set button pin mode
  pinMode(btn, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  // Debugging message
  Serial.println("GPS and GSM module test");

  // Initialize GPS serial communication
  ss.begin(9600);
}

void loop() {
  // Process GPS data if available
  while(ss.available() > 0) {
    gps.encode(ss.read());
    if(check) {
      Serial.println("GPS is ready!");
      check = false;
    }
  }

  // Check button press
  if(digitalRead(btn) == LOW) {
    // Stop GPS serial communication
    ss.end();

    // Get GPS data and send message
    getGps();

    // Restart GPS serial communication
    ss.begin(9600);

    delay(3000);
    Serial.println("Button function executed.");
  }
}

void getGps() {
  // Check if GPS data is updated
  if (gps.location.isUpdated()) {
    Serial.println("GPS function executed.");
    lat = gps.location.lat(); // Latitude in degrees (double)
    lng = gps.location.lng(); // Longitude in degrees (double)
    alertBuzzer();
    Serial.print("Lat: ");
    Serial.println(lat, 6);
    Serial.print("Lon: ");
    Serial.println(lng, 6);

    // Initialize GSM serial communication
    gsmSerial.begin(9600);
    sendMsg();
    gsmSerial.end();

    alertBuzzer();
  }
}

void sendMsg() {
  // Check if SIM900A is ready
  gsmSerial.println("AT");
  delay(1000);
  if (gsmSerial.available()) {
    String response = gsmSerial.readString();
    if (response.indexOf("OK") != -1) {
      Serial.println("SIM module is ready to transmit!");

      // Set SMS mode to text
      gsmSerial.println("AT+CMGF=1");
      delay(1000);

      // Send SMS command
      gsmSerial.print("AT+CMGS=\"");
      gsmSerial.print(phoneNumber);
      gsmSerial.println("\"");
      delay(1000);

      // Send GPS coordinates
      gsmSerial.print(gMap);
      gsmSerial.print(lat, 6); // 6 digit precision
      gsmSerial.print(",");
      gsmSerial.println(lng, 6); // 6 digit precision
      gsmSerial.write(26); // ASCII code of CTRL+Z
      delay(1000);

      // Read the response from the module
      if (gsmSerial.available()) {
        String sendResponse = gsmSerial.readString();
        if (sendResponse.indexOf("OK") != -1) {
          Serial.println("Message sent successfully");
        } else {
          Serial.println("Failed to send message");
        }
      }
    } else {
      Serial.println("SIM900A not ready");
    }
  } else {
    Serial.println("No response from SIM900A");
  }
}

void alertBuzzer() {
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
}
