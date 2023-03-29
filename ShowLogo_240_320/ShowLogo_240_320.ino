#include <TFT_eSPI.h>
#include <SPI.h>
#include "sample.h"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  tft.init();
  tft.setRotation(1);  // landscape

  tft.fillScreen(TFT_BLACK);

  // Swap the colour byte order when rendering
  tft.setSwapBytes(true);

  // Draw the icons
  tft.pushImage(0, 0, 320, 240, sample);




}

void loop() {
  // put your main code here, to run repeatedly:

}
