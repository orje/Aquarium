#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char sensor;
// Input via Serial Monitor
// n = emergency sensor
// t = temperature high sensor
// l = low level sensor
// h = high level sensor

enum states {okay_state, emergency_state};
states state;
/* Es gibt grundsätzlich den Status "Notaus" oder "Betrieb".
"Notaus" muss in jedem/r Status, bzw. Phase zuschlagen können.*/
/*******************************************************************/
/* Den Status "Betrieb" kann ich sparen, da "Nicht-Notaus"-Status. */
/*******************************************************************/

enum phases {normal_phase, evacuate_phase, fill_phase};
phases phase;
// Im Status "Betrieb" gibt es 3 Phasen

byte event = true;
// Variable to recognize an event that changes the state or phase

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  if (event) {
    display_monitor();
  }

  sensor = Serial_Monitor();

  switch (state) {
    case emergency_state:
      if (event) {
        emergency();
        event = false;
      }
      break;
    case okay_state:
      if (event) {
        okay();
      }
      if (sensor == 'n') {
        state = emergency_state;
        event = true;
      }
      switch (phase) {
        case normal_phase:
          if (event) {
            normal();
            event = false;
          }
          if (sensor == 't') {
            phase = evacuate_phase;
            event = true;
          }
          break;
        case evacuate_phase:
          if (event) {
            evacuate();
            event = false;
          }
          if (sensor == 'l') {
            phase = fill_phase;
            event = true;
          }
          break;
        case fill_phase:
          if (event) {
            fill();
            event = false;
          }
          if (sensor == 'h') {
            phase = normal_phase;
            event = true;
          }
      }
  }
}

char Serial_Monitor() {
  if (Serial.available()) {
    return Serial.read();
  }
}
void okay() {
  display_state("okay_state      ");
}
void emergency() {
  display_state("emergency_state ");
}
void normal() {
  display_phase("normal_phase    ");
}
void evacuate() {
  display_phase("evacuate_phase  ");
}
void fill() {
  display_phase("fill_phase      ");
}
void display_state(char *state_text) {
  lcd.setCursor(0, 0);
  lcd.print(state_text);
}
void display_phase(char *phase_text) {
  lcd.setCursor(0, 1);
  lcd.print(phase_text);
}
void display_monitor() {
  Serial.print("sensor");
  Serial.print("\t");
  Serial.print(sensor);
  Serial.print("\t");
  Serial.print("state");
  Serial.print("\t");
  Serial.print(state);
  Serial.print("\t");
  Serial.print("phase");
  Serial.print("\t");
  Serial.println(phase);
}
