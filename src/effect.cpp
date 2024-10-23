#include <Adafruit_NeoPixel.h>
#include "effect.h"
extern bool newCommandReceived;
Adafruit_NeoPixel WS2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void BouncingColoredBalls(int BallCount, byte colors[][3], boolean continuous)
{
    float Gravity = -9.81;
    int StartHeight = 1;

    float Height[BallCount];
    float ImpactVelocityStart = sqrt(-2 * Gravity * StartHeight);
    float ImpactVelocity[BallCount];
    float TimeSinceLastBounce[BallCount];
    int Position[BallCount];
    long ClockTimeSinceLastBounce[BallCount];
    float Dampening[BallCount];
    boolean ballBouncing[BallCount];
    boolean ballsStillBouncing = true;

    for (int i = 0; i < BallCount; i++)
    {
        ClockTimeSinceLastBounce[i] = millis();
        Height[i] = StartHeight;
        Position[i] = 0;
        ImpactVelocity[i] = ImpactVelocityStart;
        TimeSinceLastBounce[i] = 0;
        Dampening[i] = 0.90 - float(i) / pow(BallCount, 2);
        ballBouncing[i] = true;
    }

    while (ballsStillBouncing)
    {
        for (int i = 0; i < BallCount; i++)
        {
            TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
            Height[i] = 0.5 * Gravity * pow(TimeSinceLastBounce[i] / 1000, 2.0) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;

            if (Height[i] < 0)
            {
                Height[i] = 0;
                ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
                ClockTimeSinceLastBounce[i] = millis();

                if (ImpactVelocity[i] < 0.01)
                {
                    if (continuous)
                    {
                        ImpactVelocity[i] = ImpactVelocityStart;
                    }
                    else
                    {
                        ballBouncing[i] = false;
                    }
                }
            }
            Position[i] = round(Height[i] * (NUM_PIXELS - 1) / StartHeight);
        }

        ballsStillBouncing = false; // assume no balls bouncing
        for (int i = 0; i < BallCount; i++)
        {
            WS2812b.setPixelColor(Position[i], colors[i][0], colors[i][1], colors[i][2]);
            if (ballBouncing[i])
            {
                ballsStillBouncing = true;
            }
        }

        WS2812b.show();
    }
}

void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{

    for (int i = 0; i < NUM_PIXELS - EyeSize - 2; i++)
    {
        WS2812b.setPixelColor(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(i + j, red, green, blue);
        }
        WS2812b.setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        WS2812b.show();
        delay(SpeedDelay);
    }

    delay(ReturnDelay);

    for (int i = NUM_PIXELS - EyeSize - 2; i > 0; i--)
    {
        WS2812b.setPixelColor(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(i + j, red, green, blue);
        }
        WS2812b.setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        WS2812b.show();
        delay(SpeedDelay);
    }

    delay(ReturnDelay);
}

void Fire(int Cooling, int Sparking)
{
    static byte heat[NUM_PIXELS];
    int cooldown;

    // Step 1.  Cool down every cell a little
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        cooldown = random(0, ((Cooling * 10) / NUM_PIXELS) + 2);

        if (cooldown > heat[i])
        {
            heat[i] = 0;
        }
        else
        {
            heat[i] = heat[i] - cooldown;
        }
    }

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = NUM_PIXELS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if (random(255) < Sparking)
    {
        int y = random(7);
        heat[y] = heat[y] + random(160, 255);
        // heat[y] = random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for (int j = 0; j < NUM_PIXELS; j++)
    {
        setPixelHeatColor(j, heat[j]);
    }

    WS2812b.show();
}

void setPixelHeatColor(int Pixel, byte temperature)
{
    // Scale 'heat' down from 0-255 to 0-191
    byte t192 = round((temperature / 255.0) * 191);

    // calculate ramp up from
    byte heatramp = t192 & 0x3F; // 0..63
    heatramp <<= 2;              // scale up to 0..252

    // figure out which third of the spectrum we're in:
    if (t192 > 0x80)
    { // hottest
        WS2812b.setPixelColor(Pixel, 255, 255, heatramp);
    }
    else if (t192 > 0x40)
    { // middle
        WS2812b.setPixelColor(Pixel, 255, heatramp, 0);
    }
    else
    { // coolest
        WS2812b.setPixelColor(Pixel, heatramp, 0, 0);
    }
}

void HalloweenEyes(byte red, byte green, byte blue,
                   int EyeWidth, int EyeSpace,
                   boolean Fade, int Steps, int FadeDelay,
                   int EndPause)
{

    randomSeed(analogRead(0));

    int i;
    int StartPoint = random(0, NUM_PIXELS - (2 * EyeWidth) - EyeSpace);
    int Start2ndEye = StartPoint + EyeWidth + EyeSpace;

    for (i = 0; i < EyeWidth; i++)
    {
        WS2812b.setPixelColor(StartPoint + i, red, green, blue);
        WS2812b.setPixelColor(Start2ndEye + i, red, green, blue);
    }

    WS2812b.show();

    if (Fade == true)
    {
        float r, g, b;

        for (int j = Steps; j >= 0; j--)
        {
            r = j * (red / Steps);
            g = j * (green / Steps);
            b = j * (blue / Steps);

            for (i = 0; i < EyeWidth; i++)
            {
                WS2812b.setPixelColor(StartPoint + i, r, g, b);
                WS2812b.setPixelColor(Start2ndEye + i, r, g, b);
            }

            WS2812b.show();
            delay(FadeDelay);
        }
    }
    delay(EndPause);
}

void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay)
{
    for (int i = 0; i < NUM_PIXELS + NUM_PIXELS; i++)
    {
        // fade brightness all LEDs one step
        for (int j = 0; j < NUM_PIXELS; j++)
        {
            if ((!meteorRandomDecay) || (random(10) > 5))
            {
                fadeToBlack(j, meteorTrailDecay);
            }
        }

        // draw meteor
        for (int j = 0; j < meteorSize; j++)
        {
            if ((i - j < NUM_PIXELS) && (i - j >= 0))
            {
                WS2812b.setPixelColor(i - j, red, green, blue);
            }
        }

        WS2812b.show();
        delay(SpeedDelay);
    }
}

void fadeToBlack(int ledNo, byte fadeValue)
{
#ifdef ADAFRUIT_NEOPIXEL_H
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;

    oldColor = WS2812b.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r = (r <= 10) ? 0 : (int)r - (r * fadeValue / 256);
    g = (g <= 10) ? 0 : (int)g - (g * fadeValue / 256);
    b = (b <= 10) ? 0 : (int)b - (b * fadeValue / 256);

    WS2812b.setPixelColor(ledNo, r, g, b);
#endif
#ifndef ADAFRUIT_NEOPIXEL_H
#endif
}

void Position(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
    RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    LeftToRight(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    RightToLeft(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    OutsideToCenter(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
    CenterToOutside(red, green, blue, EyeSize, SpeedDelay, ReturnDelay);
}

void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
    for (int i = ((NUM_PIXELS - EyeSize) / 2); i >= 0; i--)
    {
        WS2812b.setPixelColor(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(i + j, red, green, blue);
        }
        WS2812b.setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);

        WS2812b.setPixelColor(NUM_PIXELS - i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(NUM_PIXELS - i - j, red, green, blue);
        }
        WS2812b.setPixelColor(NUM_PIXELS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

        WS2812b.show();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
    for (int i = 0; i <= ((NUM_PIXELS - EyeSize) / 2); i++)
    {
        WS2812b.setPixelColor(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(i + j, red, green, blue);
        }
        WS2812b.setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);

        WS2812b.setPixelColor(NUM_PIXELS - i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(NUM_PIXELS - i - j, red, green, blue);
        }
        WS2812b.setPixelColor(NUM_PIXELS - i - EyeSize - 1, red / 10, green / 10, blue / 10);

        WS2812b.show();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

// used by Position
void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
    for (int i = 0; i < NUM_PIXELS - EyeSize - 2; i++)
    {
        WS2812b.setPixelColor(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(i + j, red, green, blue);
        }
        WS2812b.setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        WS2812b.show();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

// used by Position
void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay)
{
    for (int i = NUM_PIXELS - EyeSize - 2; i > 0; i--)
    {
        WS2812b.setPixelColor(i, red / 10, green / 10, blue / 10);
        for (int j = 1; j <= EyeSize; j++)
        {
            WS2812b.setPixelColor(i + j, red, green, blue);
        }
        WS2812b.setPixelColor(i + EyeSize + 1, red / 10, green / 10, blue / 10);
        WS2812b.show();
        delay(SpeedDelay);
    }
    delay(ReturnDelay);
}

void Rainbow(int wait)
{
    // 5 cycles of all colors on wheel
    for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256)
    {
        WS2812b.rainbow(firstPixelHue);
        WS2812b.show(); // Update strip with new contents
        delay(wait);    // Pause for a moment
    }
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay)
{
    int Position = 0;

    for (int i = 0; i < NUM_PIXELS * 2; i++)
    {
        if (newCommandReceived)
        {
            return;
        }
        Position++; // = 0; //Position + Rate;
        for (int i = 0; i < NUM_PIXELS; i++)
        {
            // sine wave, 3 offset waves make a rainbow!
            // float level = sin(i+Position) * 127 + 128;
            // setPixel(i,level,0,0);
            // float level = sin(i+Position) * 127 + 128;
            WS2812b.setPixelColor(i, ((sin(i + Position) * 127 + 128) / 255) * red,
                                  ((sin(i + Position) * 127 + 128) / 255) * green,
                                  ((sin(i + Position) * 127 + 128) / 255) * blue);
        }

        WS2812b.show();
        delay(WaveDelay);
    }
}

void snowflakes(uint8_t wait)
{
    // Setup the pixel array
    int pixel[60];
    for (int p = 0; p < 60; p++)
    {
        pixel[p] = random(0, 255);
    }

    // Run some snowflake cycles
    for (int j = 0; j < 200; j++)
    {
        // Every five cycles, light a new pixel
        if ((j % 5) == 0)
        {
            WS2812b.setPixelColor(random(0, 60), 255, 255, 255);
        }

        // Dim all pixels by 10
        for (int p = 0; p < 60; p++)
        {
            WS2812b.setPixelColor(p, pixel[p], pixel[p], pixel[p]);
            pixel[p] = pixel[p] - 10;
        }
        WS2812b.show();
        delay(wait);
    }
}

void theaterChase(uint32_t color, int wait)
{
    for (int a = 0; a < 10; a++)
    {
        if (newCommandReceived)
        {
            return;
        } // Repeat 10 times...
        for (int b = 0; b < 3; b++)
        {                    //  'b' counts from 0 to 2...
            WS2812b.clear(); //   Set all pixels in RAM to 0 (off)
            // 'c' counts up from 'b' to end of strip in steps of 3...
            for (int c = b; c < WS2812b.numPixels(); c += 3)
            {
                WS2812b.setPixelColor(c, color); // Set pixel 'c' to value 'color'
            }
            WS2812b.show(); // Update strip with new contents
            delay(wait);    // Pause for a moment
        }
    }
}

void theaterChaseRainbow(int SpeedDelay)
{
    byte *c;

    for (int j = 0; j < 256; j++)
    {
        // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++)
        {
            for (int i = 0; i < NUM_PIXELS; i = i + 3)
            {
                c = Wheel((i + j) % 255);
                WS2812b.setPixelColor(i + q, *c, *(c + 1), *(c + 2)); // turn every third pixel on
            }
            WS2812b.show();

            delay(SpeedDelay);

            for (int i = 0; i < NUM_PIXELS; i = i + 3)
            {
                WS2812b.setPixelColor(i + q, 0, 0, 0); // turn every third pixel off
            }
        }
    }
}

byte *Wheel(byte WheelPos)
{
    static byte c[3];

    if (WheelPos < 85)
    {
        c[0] = WheelPos * 3;
        c[1] = 255 - WheelPos * 3;
        c[2] = 0;
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        c[0] = 255 - WheelPos * 3;
        c[1] = 0;
        c[2] = WheelPos * 3;
    }
    else
    {
        WheelPos -= 170;
        c[0] = 0;
        c[1] = WheelPos * 3;
        c[2] = 255 - WheelPos * 3;
    }
    return c;
}

void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne)
{
    for (int i = 0; i < Count; i++)
    {
        WS2812b.setPixelColor(random(NUM_PIXELS), red, green, blue);
        WS2812b.show();
        delay(SpeedDelay);
        if (OnlyOne)
        {
        }
    }
    delay(SpeedDelay);
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne)
{
    for (int i = 0; i < Count; i++)
    {
        WS2812b.setPixelColor(random(NUM_PIXELS), random(0, 255), random(0, 255), random(0, 255));
        WS2812b.show();
        delay(SpeedDelay);
        if (OnlyOne)
        {
        }
    }
    delay(SpeedDelay);
}

void Sparkle(byte red, byte green, byte blue, int SpeedDelay)
{
    int Pixel = random(NUM_PIXELS);
    WS2812b.setPixelColor(Pixel, red, green, blue);
    WS2812b.show();
    delay(SpeedDelay);
    WS2812b.setPixelColor(Pixel, 0, 0, 0);
}
