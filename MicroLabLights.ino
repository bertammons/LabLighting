#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
 
#define NUM_LEDS 3
#define DATA_PIN 2

#define POT_PIN0 A0
#define POT_PIN1 A1
#define POT_PIN2 A2

#define SWITCH_PIN0 16
#define SWITCH_PIN1 14
#define SWITCH_PIN2 15

#define LED_PIN0 3
#define LED_PIN1 5
#define LED_PIN2 6

CRGB leds[NUM_LEDS];

void setup() {
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

	pinMode(LED_PIN0, OUTPUT);
	pinMode(LED_PIN1, OUTPUT);
	pinMode(LED_PIN2, OUTPUT);
}

void loop() { 
	int brightVal0 = readPot(POT_PIN0);
	int brightVal1 = readPot(POT_PIN1);
	int brightVal2 = readPot(POT_PIN2);

	int SW0 = digitalRead(SWITCH_PIN0);
	int SW1 = digitalRead(SWITCH_PIN1);
	int SW2 = digitalRead(SWITCH_PIN2);

	if (SW0 == HIGH) analogWrite(LED_PIN0, brightVal0);
	if (SW1 == HIGH) analogWrite(LED_PIN1, brightVal1);
	if (SW2 == HIGH) analogWrite(LED_PIN2, brightVal2);

	//FastLED.setBrightness(brightVal);
	
	// FastLED.clear();
	// for (int led = 0; led < NUM_LEDS; led++) {
	// 	if (led < NUM_LEDS/2) {
	// 	  leds[led]= CRGB::Red;
	// 	}
	// 	else if (led > NUM_LEDS/2) {
	// 	  leds[led]= CRGB::Green;
	// 	}
	// }

 //    FastLED.show(); 
 //    delay(3); 
}

void readPot(int POTPIN){
	int val = analogRead(POTPIN);
	int brightVal = map(val, 0, 1023, 0, 255);
	return brightVal
}

