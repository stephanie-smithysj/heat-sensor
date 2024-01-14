//temperature and led
const int pinTemp = A0;
const int B=3975;
#define LED 13

//thing speak and wifi setup
#include <SPI.h>
#include "ThingSpeak.h"
#include <WiFiNINA.h>
const char ssid[] = "cs";
const char password[] = "gkmrxuW6";
const unsigned long channel_id = 2402629;
const char write_api_key[] = "CJP6OHOGMX7RKYJE";
WiFiClient client;


void setup()
{
Serial.begin(9600);
pinMode(LED, OUTPUT);

//think speak initialize
Serial.print("Connecting to ");
Serial.print(ssid);
WiFi.begin(ssid,password);
Serial.println();
Serial.println("Connected!");
ThingSpeak.begin(client);

}

void loop()
{
//tempaerature calculating
int val=analogRead(pinTemp);
float resistance=(float)(1023-val)*10000/val;
float temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;

//displays temperature based on range
if (temperature>25) {
  Serial.print("The temperature is: ");
  Serial.print(temperature);
  Serial.println(" degrees, this is too hot");
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
else if (temperature<10){
  Serial.print("The temperature is: ");
  Serial.print(temperature);
  Serial.println(" degrees, this is cold");
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
else{
  Serial.print("The temperature is: ");
  Serial.print(temperature);
  Serial.println(" degrees, this is ok");
  digitalWrite(LED, HIGH);
  delay(2000);
  digitalWrite(LED, LOW);
  delay(2000);
}

// Print the temperature to the serial console.
Serial.println("Posting " + String(temperature, 2) + " to ThingSpeak");
ThingSpeak.setField(1, String(temperature, 2));
ThingSpeak.writeFields(channel_id, write_api_key);
//delay 1 second
delay(1000);

}