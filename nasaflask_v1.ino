// This #include statement was automatically added by the Particle IDE.
#include "compare.h"

// This #include statement was automatically added by the Particle IDE.
#include "application.h"
#include "HttpClient/HttpClient.h"

// create two arrays to hold the X and the Y coordinates of the... stuff.

// they need to be doubles because the coordinates will be larger than a standard float.
//this will be the user


double user_xy[2];
// this is the api address for the user's locatio
char user_url[]="http://ip-api.com";
char user_path[]="/json";

// and this will be the international space station
double ISS_xy[2];
// this is the api address for the ISS location
char ISS_url[]="http://api.open-notify.org";
char ISS_path[]="/iss-now.json";
// this will be our timer
// int f will be the comparative number, to give us a reset time.
int t=10000;
int f=10000;
int s=1; // this is the state.

double issLat // Longitude of the international Space Station
double issLon // Latitude of the international Space Station
double userLat // Longitude of the User by internet IP
double userLon // Latitude of the User by internet IP
const int buttonPin = 2; // Button Pin address (change this to move it to another pin)
const int ledPin = 13; // Led Pin address (change this to move Led to another pin)

unsigned int nextTime = 0;    // Next time to contact the server
HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Accept" , "*/*"},
    { NULL, NULL } // NOTE: Always terminate headers will NULL
};

http_request_t request;
http_response_t response;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (t == f) {
        //run the program
        if (s == 1){
            // if state is in state 1; then run the first part
            // the first part will be collecting the user data
            // and storing it
            Serial.println();
            Serial.println("Application>\tStart of USER Loop.");
            // Request path and body can be set at runtime or at setup.
            request.hostname = user_url;
            request.port = 80;
            request.path = user_path;

            // The library also supports sending a body with your request:
            //request.body = "{\"key\":\"value\"}";

            // Get request
            http.get(request, response, headers);
            Serial.print("Application>\tResponse of USER status: ");
            Serial.println(response.status);

            Serial.print("Application>\tHTTP Response of USER Body: ");
            Serial.println(response.body);

        } else if(s == 2){
            // if state is in state 2; run the second part
            // the second part is collecting the ISS data
            // and storing it

            Serial.println();
            Serial.println("Application>\tStart of ISS Loop.");
            // Request path and body can be set at runtime or at setup.
            request.hostname = ISS_url;
            request.port = 80;
            request.path = ISS_path;

            // The library also supports sending a body with your request:
            //request.body = "{\"key\":\"value\"}";

            // Get request
            http.get(request, response, headers);
            Serial.print("Application>\tResponse of ISS status: ");
            Serial.println(response.status);

            Serial.print("Application>\tHTTP Response of ISS Body: ");
            Serial.println(response.body);

        } else {
            // else should be when the state is 3
            // now compare the two data sets.



        }
        //terminate
        return;
        t = 0;
    } else {
        t ++;
    }

    Serial.println();
    Serial.println("Application>\tStart of Loop.");
    // Request path and body can be set at runtime or at setup.
    request.hostname = "www.timeapi.org";
    request.port = 80;
    request.path = "/utc/now";

    // The library also supports sending a body with your request:
    //request.body = "{\"key\":\"value\"}";

    // Get request
    http.get(request, response, headers);
    Serial.print("Application>\tResponse status: ");
    Serial.println(response.status);

    Serial.print("Application>\tHTTP Response Body: ");
    Serial.println(response.body);

    nextTime = millis() + 10000;
}
