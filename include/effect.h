#ifndef __EFFECT_H_
#define __EFFECT_H_

#include <stdint.h>
#include<stdio.h>
#include <stdbool.h>

#define PIN_WS2812B 14  // The ESP32 pin GPIO16 connected to WS2812B
#define NUM_PIXELS 400   // The number of LEDs (pixels) on WS2812B LED strip
//
void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous);
//
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
//
void Fire(int Cooling, int Sparking);
void setPixelHeatColor (int Pixel, byte temperature);
//
void HalloweenEyes(byte red, byte green, byte blue, 
                   int EyeWidth, int EyeSpace, 
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause);
//
void fadeToBlack(int ledNo, byte fadeValue);
void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, 
int SpeedDelay);
//
void Position(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
//
void Rainbow(int wait);
//
void RunningLights(byte red, byte green, byte blue, int WaveDelay);
//
void snowflakes(uint8_t wait);
//
void theaterChase(uint32_t color, int wait);
//
byte * Wheel(byte WheelPos);
void theaterChaseRainbow(int SpeedDelay);
//
void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne);
//
void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) ;
//
void Sparkle(byte red, byte green, byte blue, int SpeedDelay);
#endif