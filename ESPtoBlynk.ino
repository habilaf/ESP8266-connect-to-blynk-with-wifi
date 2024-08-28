#define BLYNK_TEMPLATE_ID "TMPL66Pudzb4E"
#define BLYNK_TEMPLATE_NAME "IoT Hidroponik"
#define BLYNK_AUTH_TOKEN "iv20ITcTSSYh3UJ3wQ1r_mFxKwgj83xH"  // Ganti dengan Auth Token dari Blynk

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define your WiFi credentials
const char* ssid = "iPhone (7)";
const char* password = "1234567()";

// Define pins for ultrasonic sensor
const int trigPin = 5; // D0
const int echoPin = 16;  // D1

// Define pin for TDS sensor
const int tdsPin = A0;  // Analog pin for TDS sensor

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);

  // Connect to WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  Blynk.run();  // Run Blynk

  // Send a pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo time
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  float distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.println("=================================");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read the TDS sensor value
  int tdsValue = analogRead(tdsPin);

  // Convert the analog reading to TDS value (you might need to calibrate this)
  float tdsInPpm = tdsValue * (3.3 / 1023.0) * 500;  // Example conversion formula
  //float tdsInPpm =(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value

  // Print the TDS value to the Serial Monitor
  Serial.print("TDS: ");
  Serial.print(tdsInPpm);
  Serial.println(" ppm");
  Serial.println("=================================");
  Serial.println("");

  // Send data to Blynk
  Blynk.virtualWrite(V0, tdsInPpm);    // Send Ultrasonic sensor data to Virtual Pin V0
  Blynk.virtualWrite(V1, distance);    // Send TDS sensor data to Virtual Pin V1

  // Wait before taking another measurement
  delay(1000);
}
