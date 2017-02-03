// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

#define HOOK_RESP	"hook-response/ISS_Location"
#define HOOK_PUB	"ISS_Location"
#define HOOK_RESP_ME  "hook-response/my_location"
#define HOOK_PUB_ME  "my_location"
#include "Particle.h"
#include "neopixel.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D7
#define PIXEL_COUNT 8
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

double ISS_x_current;
double ISS_y_current;
double ISS_time_current;
double my_x_current;
double my_y_current;
int State;
int iss_hit;
int my_hit;

void setup() {
 // Subscribe to the integration response event
  Particle.subscribe(HOOK_RESP, ISS_loc_data, MY_DEVICES);
  Particle.subscribe(HOOK_RESP_ME, my_loc_data, MY_DEVICES);\
  strip.begin();
  Particle.variable("iss_x", ISS_x_current);
  Particle.variable("iss_y", ISS_y_current);
  Particle.variable("status", State);
}

void loop() {
    Particle.process();
 compare();
   illuminate();
   strip.show();


  // Get some data
  String data = String(50);
  // Trigger the integration
  //Particle.publish(HOOK_PUB, data, PRIVATE);
  get_iss_loc();
 Serial.print('got ISS loc');
  // Wait 60 seconds
  delay(6000);
  get_my_loc();


  strip.setPixelColor(State, 0, 0, 0);
  strip.show();
  delay(1000);








    Serial.print('got My loc');


    //delay(10000);



}
// void myHandler(const char *event, const char *data) {
//   // Handle the integration response

// }

// lots of this code came from : https://community.particle.io/t/tutorial-webhooks-and-responses-with-parsing-json-mustache-tokens/14612

void get_iss_loc() {
  Serial.print("in Iss Location Request");
  Serial.println();
  bool state = false;
  // publish the event that will trigger our webhook
  Spark.publish(HOOK_PUB);

  unsigned long wait = millis();
  //wait for subscribe to kick in or 5 secs
  while (!state && (millis() < wait + 5000UL)){
    //Tells the core to check for incoming messages from particle cloud
    Spark.process();
  if (!state) {
    Serial.print("ISS get failed");
    Serial.println();
    iss_hit++;
    if (iss_hit > 2) {
      //If 3 webhook call fail in a row, Print fail
      Serial.print("Webhook ISS get failed!");
    }
  }
  else
    state = 0;
}}

void get_my_loc() {
  Serial.print("in my Location Request");
  Serial.println();
  bool state = false;
  // publish the event that will trigger our webhook
  Spark.publish(HOOK_PUB_ME);

  unsigned long wait = millis();
  //wait for subscribe to kick in or 5 secs
  while (!state && (millis() < wait + 5000UL))
    //Tells the core to check for incoming messages from particle cloud
    Spark.process();
        if (!state) {
    Serial.print("MY get failed");
    Serial.println();
    my_hit++;
    if (my_hit > 2) {
      //If 3 webhook call fail in a row, Print fail
      Serial.print("My Webhook failed!");
    }
  }
  else
    state = 0;

}

void ISS_loc_data(const char *name, const char *data) {
    Serial.print("getting ISS Data");
    String str = String(data);
    char xBuff[125] = "";
    char yBuff[125] = "";
    char tBuff[125] = "";
    char strBuffer[250] = "";
    str.toCharArray(strBuffer, 250);
    Spark.publish("debug1", str);

    // example: "\"21~99~75~0~22~98~77~20~23~97~74~10~24~94~72~10~\""
    double ISS_loc = atof(strtok(strBuffer, "/~"));
   Spark.publish("debug2", strBuffer);
   double ISS_x = atof(strtok(strBuffer, "~"));
     Spark.publish("debug3", strBuffer);





    double ISS_y = atof(strtok(NULL, "~"));
    double ISS_time = atof(strtok(NULL, "~"));



      ISS_x_current = ISS_x;
      ISS_y_current = ISS_y;
      Serial.print("Moved Variables");

    bool state = true;
    ISS_time_current = ISS_time;
}
void my_loc_data(const char *name, const char *data) {
    Serial.print("getting my Data");
    String str = String(data);
    char strBuffer[125] = "";
    str.toCharArray(strBuffer, 125); // example: "\"21~99~75~0~22~98~77~20~23~97~74~10~24~94~72~10~\""
    float my_loc = atoi(strtok(strBuffer, "\"~"));
    float my_x = atoi(strtok(NULL, "~"));
    float my_y = atoi(strtok(NULL, "~"));

  my_x_current = my_x;
  my_y_current = my_y;


  Serial.print("Moved my Variables");

    bool state = true;

}

void illuminate(){
    if (State < 9){
        for (int i; i < strip.numPixels(); i ++){
        if (i == State){
            strip.setPixelColor(State, 0, 0, 255);
        }
    }
}   else if (State == 9) {
        for (int i; i< strip.numPixels(); i++){
            strip.setPixelColor(i, 0, 0, 255);
        }
    }




}
void compare(){
    if ( (ISS_x_current) == (my_x_current) && (ISS_y_current) > (my_y_current) ){
      //LED 1 turns on
      State = 1;
      }
    if ( (ISS_x_current) < (my_x_current) && (ISS_y_current) > (my_y_current) ){
      //LED 2 turns on
      State = 2;
      }
    if ( (ISS_x_current) < (my_x_current) && (ISS_y_current) == (my_y_current) ){
      //LED 3 turns on
      State = 3;
      }
    if ( (ISS_x_current) < (my_x_current) && (ISS_y_current) < (my_y_current) ){
      //LED 4 turns on
      State = 4;
      }
    if ( (ISS_x_current) == (my_x_current) && (ISS_y_current) < (my_y_current) ){
      //LED 5 turns on
      State = 5;
      }
    if ( (ISS_x_current) > (my_x_current) && (ISS_y_current) < (my_y_current) ){
      //LED 6 turns on
      State = 6;
      }
    if ( (ISS_x_current) > (my_x_current) && (ISS_y_current) == (my_y_current) ){
      //LED 7 turns on
      State = 7;
      }
    if ( (ISS_x_current) > (my_x_current) && (ISS_y_current) > (my_y_current) ){
      //LED 8 turns on
      State = 8;
      }
    if ( (ISS_x_current) == (my_x_current) && (ISS_y_current) == (my_y_current) ){
      //All LED turn on
      State = 9;
      }

}
