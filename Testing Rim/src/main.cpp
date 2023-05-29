#include <Arduino.h>  //Arduino library
#include <HX711.h>    //Library for the HX711 amplifier

// HX711 circuit wiring
const int LOADCELL_DAT_PIN = 2;  //Names of the pins can be found on the HX711 board
const int LOADCELL_CLK_PIN = 3;  //Names of the pins can be found on the HX711 board
const float CALIBRATION_VALUE = 105750.f;  //This goes into the set_scale() function
const int DATA_LOGGING_SPEED = 1000;  //Speed at which the serial monitor prints the values measured (in Milicesonds)

HX711 scale;

void setup() {
  Serial.begin(9600);

  Serial.println("HX711 testing:");
  Serial.println("Initialization Started");
  scale.begin(LOADCELL_DAT_PIN, LOADCELL_CLK_PIN);

  Serial.println("Before set up:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());		

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));	

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 3);	

  scale.set_scale(CALIBRATION_VALUE);   
  scale.tare();  // Tare the loadcell

  //! -------------- After Set Up --------------

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());  // print a raw reading

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  // print the average of 20 readings

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));	 // print the average of 5 readings the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 3);  // print the average of 5 readings minus tare weight, divided
	                                        // by the CALIBRATION_VALUE parameter set with set_scale
  Serial.println("Readings:");

}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 3);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 3);

  scale.power_down();			       
  delay(DATA_LOGGING_SPEED);
  scale.power_up();
}

