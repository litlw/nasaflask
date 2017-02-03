// all varibles
double issLat // Longitude of the international Space Station
double issLon // Latitude of the international Space Station
double userLat // Longitude of the User by internet IP
double userLon // Latitude of the User by internet IP
const int buttonPin = 2; // Button Pin address (change this to move it to another pin)
const int ledPin = 13; // Led Pin address (change this to move Led to another pin)

int buttonState = 0; // state of the button durring its unchanged off placement

void setup() {
  // put your setup code here, to run once:

  Serial.begin(19200); // Data rate 9600 bits per minute
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT); // declaring the button as a user command

}


void loop() {

}

void compare() {
    // put your main code here, to run repeatedly:



    //go into if states GPS locator
    Serial.println("currently running");

    //if Commands for Led grid locator

    /* HUE Please put all the led locations here as they will change from my feather to the Photon,
       please follow the image of the led locations and addresses for this math to make sense. */
    if ( (ISS_xy[0]) == (user_xy[0]) && (ISS_xy[1]) > (user_xy[1]) ){
      //LED 1 turns on
      }
    if ( (ISS_xy[0]) < (user_xy[0]) && (ISS_xy[1]) > (user_xy[1]) ){
      //LED 2 turns on
      }
    if ( (ISS_xy[0]) < (user_xy[0]) && (ISS_xy[1]) == (user_xy[1]) ){
      //LED 3 turns on
      }
    if ( (ISS_xy[0]) < (user_xy[0]) && (ISS_xy[1]) < (user_xy[1]) ){
      //LED 4 turns on
      }
    if ( (ISS_xy[0]) == (user_xy[0]) && (ISS_xy[1]) < (user_xy[1]) ){
      //LED 5 turns on
      }
    if ( (ISS_xy[0]) > (user_xy[0]) && (ISS_xy[1]) < (user_xy[1]) ){
      //LED 6 turns on
      }
    if ( (ISS_xy[0]) > (user_xy[0]) && (ISS_xy[1]) == (user_xy[1]) ){
      //LED 7 turns on
      }
    if ( (ISS_xy[0]) > (user_xy[0]) && (ISS_xy[1]) > (user_xy[1]) ){
      //LED 8 turns on
      }
    if ( (ISS_xy[0]) == (user_xy[0]) && (ISS_xy[1]) == (user_xy[1]) ){
      //All LED turn on
      }

    }

  
