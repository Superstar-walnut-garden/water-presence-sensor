#include <Arduino.h>

auto electrode1 = 3, electrode2 = 4; // PORTB.3 and PORTB.4 
auto electrode1ADC = A3, electrode2ADC = A2, potentiometer = A1; // PORTB.3, PORTB.4 and PORTB.2
auto output = 0; // PORTB.0

void dischargeCapacitors()
{
  pinMode(electrode1, OUTPUT);
  pinMode(electrode2, OUTPUT);
  digitalWrite(electrode1, LOW);
  digitalWrite(electrode2, LOW);
  delay(100);
}

bool isWaterDetected(bool direction)
{
  dischargeCapacitors();
  if(direction)
  {
    pinMode(electrode2, INPUT); // set electrode2 as input adc
    pinMode(electrode2ADC, INPUT); // set electrode2 as input adc
    pinMode(electrode1, OUTPUT); // set electrode1 as output
    digitalWrite(electrode1, HIGH); // set electrode1 to high
    delay(100); // Wait for the electrode to stabilize
    return analogRead(electrode2ADC) > analogRead(potentiometer); // Read the ADC value from electrode2

  } else 
  {
    pinMode(electrode1, INPUT); // set electrode1 as input adc 
    pinMode(electrode1ADC, INPUT); // set electrode1 as input adc 
    pinMode(electrode2, OUTPUT); // set electrode2 as output
    digitalWrite(electrode2, HIGH); // set electrode2 to high
    delay(100); // Wait for the electrode to stabilize
    return analogRead(electrode1ADC) > analogRead(potentiometer); // Read the ADC value from electrode1
  }
}

void setup()
{
  pinMode(electrode1, OUTPUT);
  pinMode(electrode2ADC, INPUT);

  pinMode(potentiometer, INPUT);
  pinMode(output, OUTPUT);
}

void loop()
{
  if(isWaterDetected(0) and isWaterDetected(1)) // check if water is detected on both electrodes
  {
    digitalWrite(output, HIGH);
  } else 
  {
    digitalWrite(output, LOW);
  }
}
