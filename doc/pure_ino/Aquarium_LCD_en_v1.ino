s#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char sensor;
// Input via Serial Monitor
// n = emergency sensor
// t = temperature high sensor
// l = low level sensor
// h = high level sensor

enum states {okay_state, emergency_state};
states state;
enum phases {normal_phase, evacuate_phase, fill_phase};
phases phase;

int event = 0;
// Variable to recognize change of states or phase

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
}

void Serial_Monitor() {
  if (Serial.available()) {
    sensor = Serial.read();
  }
}

void loop() {
  Serial_Monitor();

  switch (state) {
    case emergency_state:
      if (!event) {
        emergency();
      }
      event = 1;
      break;
    case okay_state:
      if (!event) {
        okay();
      }
      if (sensor == 'n') {
        event = 0;
        state = emergency_state;
      }
      if (state == okay_state) {
        switch (phase) {
          case normal_phase:
            if (!event) {
              normal();
            }
            event = 1;
            if (sensor == 't') {
              event = 0;
              phase = evacuate_phase;
            }
            break;
          case evacuate_phase:
            if (!event) {
              evacuate();
            }
            event = 1;
            if (sensor == 'l') {
              event = 0;
              phase = fill_phase;
            }
            break;
          case fill_phase:
            if (!event) {
              fill();
            }
            event = 1;
            if (sensor == 'h') {
              event = 0;
              phase = normal_phase;
            }
        }
      }
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
  display_monitor();
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
