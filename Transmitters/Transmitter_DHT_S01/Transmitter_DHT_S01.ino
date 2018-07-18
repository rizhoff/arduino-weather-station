#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/

#include <DHT.h>
#include <LowPower.h>


#define DHTPIN 6     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

float hum;  //Stores humidity value
float temp; //Stores temperature value



String stringOne;


RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);


}
void loop() {


  dht.begin();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setRetries(15,15);
  radio.stopListening();
  
 //           hum = dht.readHumidity();
 //           dtostrf(hum, 5, 2, humi);
              stringOne = "S01";
              stringOne += String("*H");
              stringOne += dht.readHumidity();
              stringOne += String("*T");
              stringOne += dht.readTemperature();
//              Serial.println(stringOne);


// Length (with one extra character for the null terminator)
int str_len = stringOne.length() + 1; 

// Prepare the character array (the buffer) 
char char_array[str_len];

// Copy it over 
stringOne.toCharArray(char_array, str_len);

radio.write(&char_array, str_len);



            
            radio.powerDown (); //shut down the radio to save power
  
 
      // 10 minutes = 10x60x1 = 600 s
      // 600 s / 8 s = 75
      unsigned int sleepCounter;
      
      for (sleepCounter = 1; sleepCounter > 0; sleepCounter--)
          {
            LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
          }


          
}
