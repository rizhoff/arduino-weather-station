#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

String message_out;
String temp;

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  
  radio.openReadingPipe(0, rxAddr);
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    message_out = "";
    char message_in[32] = {0};
    radio.read(&message_in, sizeof(message_in));
//    Serial.println(message_in);

    char *p = message_in;
    char *str;
    while ((str = strtok_r(p, "*", &p)) != NULL) {// delimiter is the star,  https://arduino.stackexchange.com/questions/21391/how-to-use-strtok-and-strstr-with-arduino


          //Here we pass the sensor station ID
          if (String(str).startsWith("S")) message_out = "{\"BaseStationID\": \"" + String(str) + "\"";
          
          //Here we add the temperature
          if (String(str).startsWith("T")) {
          
            temp = String(str);
            temp.remove(0,1);
            message_out += ",\"Temperature\": \"" + temp + "\"";
          }
          
          //Here we add humidity
          if (String(str).startsWith("H")) {
          
            temp = String(str);
            temp.remove(0,1);
            message_out += ",\"Humidity\": \"" + temp + "\"";
          }
          
          // Other readings to be added, depending on sensors, e.g. altitude, light intensity, etc.
          
          
    }
    message_out += "}"; //Close the JSON
    Serial.println(message_out);

    // Here is what we get from a sensor station - S01*H70.00*T27.10 
    // And here is what we are sending to the web server - {"BaseStationID": "S01","Humidity": "70.00","Temperature": "27.10"}
   
  }
}

