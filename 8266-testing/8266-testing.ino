#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
Adafruit_ADS1015 ads;     /* Use thi for the 12-bit version */

#define SWITCH_PIN0 D5
#define SWITCH_PIN1 D6
#define SWITCH_PIN2 D7

#define LED_PIN0 12
#define LED_PIN1 13
#define LED_PIN2 14

void setup() {
  
  pinMode(LED_PIN0, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);

  pinMode(SWITCH_PIN0, INPUT);
  pinMode(SWITCH_PIN1, INPUT);
  pinMode(SWITCH_PIN2, INPUT);


  Serial.begin(115200);
  Serial.println("Hello!");
  
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  
  ads.begin();
}

void loop() {
  int16_t adc0, adc1, adc2, adc3;
  
  int brightVal0 = readPot(1);
  int brightVal1 = readPot(2);
  int brightVal2 = readPot(3);

  int SW0 = digitalRead(SWITCH_PIN0);
  int SW1 = digitalRead(SWITCH_PIN1);
  int SW2 = digitalRead(SWITCH_PIN2);

  if (SW0 == HIGH) analogWrite(LED_PIN0, brightVal0);
  if (SW1 == HIGH) analogWrite(LED_PIN1, brightVal1);
  if (SW2 == HIGH) analogWrite(LED_PIN2, brightVal2);

  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  
  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.println(" ");
  Serial.print("SW0: "); Serial.println(SW0);
  Serial.print("SW1: "); Serial.println(SW1);
  Serial.print("SW2: "); Serial.println(SW2);
  Serial.println(" ");
  Serial.print("LED0: "); Serial.println(brightVal0);
  Serial.print("LED1: "); Serial.println(brightVal1);
  Serial.print("LED2: "); Serial.println(brightVal2);
  
  delay(1000);
}

float readPot(int POTPIN){
  int val = ads.readADC_SingleEnded(POTPIN);
  int brightVal = map(val, 0, 1100, 0, 1024);
  return brightVal;
}
