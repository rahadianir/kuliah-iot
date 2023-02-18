/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "..."
#define BLYNK_DEVICE_NAME           "..."
#define BLYNK_AUTH_TOKEN            "..."


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "...";
char pass[] = "...";

BlynkTimer timer;

// Set pins
const int trigPin = D1;
const int rcvPin1 = D5;
const int rcvPin2 = D6;
const int rcvPin3 = D7;
long duration;
int distance, distance1, distance2, distance3;

// This function sends Arduino's uptime every second to Virtual Pin 2.
void checkParked()
{
  // Read ultrasonic sensor to determine whether
  // a car is parked in the slot or not.
  distance1 = checkDistance(rcvPin1);
  distance2 = checkDistance(rcvPin2);
  distance3 = checkDistance(rcvPin3);
  
  // distance < 1000cm means there are object
  // blocking the ultrasonic wave travels
  // which means there is car parked in the slot.
  if (distance1 < 1000) {
    // turn on virtual LED in pin V2 if car is parked
    // to show that the parking slot is occupied
    Blynk.virtualWrite(V2, 1);
  } else {
    // turn off virtual LED in pin V2 if car is not parked
    // to show that the parking slot is not occupied
    Blynk.virtualWrite(V2, 0);
  }
  
  // similar to above functions but for other parking slots
  if (distance2 < 1000) {
    Blynk.virtualWrite(V3, 1);
  } else {
    Blynk.virtualWrite(V3, 0);
  }
  
  if (distance3 < 1000) {
    Blynk.virtualWrite(V4, 1);
  } else {
    Blynk.virtualWrite(V4, 0);
  }
}

int checkDistance(int rcvrPin)
{
  digitalWrite(trigPin, LOW); // clean/clear trigger
  delay(10);
  
  // release ultrasonic wave for 10ms
  digitalWrite(trigPin, HIGH); 
  delay(10);
  digitalWrite(trigPin, LOW);
  
  // calculate duration from trigger pin activated
  // until ultrasonic wave is received
  duration = pulseIn(rcvrPin, HIGH);
  
  
  // calculate distance from said duration
  distance = duration * 0.034 / 2;
  
  return distance;
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  
  // Setup pin to receive ultrasonic sensor output
  pinMode(trigPin1, OUTPUT);
  pinMode(rcvPin1, INPUT);

  // Setup a function to be called every second
  timer.setInterval(1000L, checkParked);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

}
