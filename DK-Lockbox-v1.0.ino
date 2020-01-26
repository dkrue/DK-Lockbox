#include <KnobDK.h>
#include <UtilityDK.h>
#include <Bounce.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define midiChannel 1

#define DEBUG
#define onboardLED 13

// Controller knobs (analogPin, midiCC, midiCCShifted, analogMin, analogMax)
// Note: reversed due to joysticks usually being upside down - WIRE knobs backwards!
KnobDK knob[8] = {
  KnobDK(A0, 14, 30, 1023, 0),
  KnobDK(A1, 15, 31, 1023, 0),
  KnobDK(A2, 16, 32, 1023, 0),
  KnobDK(A4, 17, 33, 1023, 0),
  KnobDK(A5, 18, 34, 1023, 0),
  KnobDK(A6, 19, 35, 1023, 0),
  KnobDK(A7, 20, 36, 1023, 0),
  KnobDK(A8, 21, 37, 1023, 0),      
};


// Create debounced shift button with 10ms delay to smooth on/off state
Bounce button[4] = {
  Bounce(10, 10),
  Bounce(9, 10),
  Bounce(8, 10),
  Bounce(7, 10)
};
int buttonCC[4] = {22,23,24,25};

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(3, 17, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP); 

  // Initialize neopixel lights       
  pixels.begin();
  pixels.clear();
  pixels.show(); // needed if not refreshing in the main loop

  for(int i=0; i < 3; i++) {
      pixels.setPixelColor(i, pixels.Color(128,40,1)); // warm white half power
  }
  pixels.show();

  
  #ifdef DEBUG
    pinMode(onboardLED, OUTPUT);
  #endif
}

void loop() {

  // Joystick button loop
  for (int i=0; i < 4; i++)
  { 
    if (button[i].update()) {
        if (button[i].fallingEdge()) {
          usbMIDI.sendControlChange(buttonCC[i], 127, midiChannel);
          #ifdef DEBUG
            Serial.print("Button clicked sent 127 on CC "); 
            Serial.println(buttonCC[i]);
          #endif
        } else if (button[i].risingEdge()) {
          usbMIDI.sendControlChange(buttonCC[i], 0, midiChannel);
          #ifdef DEBUG
            Serial.print("Button released sent 0 on CC "); 
            Serial.println(buttonCC[i]);
          #endif
        }
    }
  }


  // Analog inputs loop
  for (int i=0; i < 8; i++)
  {
    // Refresh controller value
    bool activity = knob[i].refresh();
    
    if(activity)
    {
      #ifdef DEBUG
        digitalWrite(onboardLED, HIGH);
        Serial.print("Knob ");
        Serial.print(i);
        Serial.print(" is ");
        Serial.print(knob[i].val());
        Serial.print(" sent ");
        Serial.print(knob[i].ccVal());
        Serial.print(" on CC ");
        Serial.println(knob[i].ccNum());
      #endif
      
      // Send MIDI CC value
      usbMIDI.sendControlChange(knob[i].ccNum(), knob[i].ccVal(), midiChannel);

    } 
  }

  // Reduce analog sampling rate for smoother action
  delay(20);

  // MIDI Controllers should discard incoming MIDI messages
  while (usbMIDI.read()) {
    // ignore incoming messages
  }

  // Wait to clear onboard LED after all knobs for brightest effect
  #ifdef DEBUG      
    digitalWrite(onboardLED, LOW);
  #endif
}

