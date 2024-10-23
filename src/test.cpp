// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <WebServer.h>
// #include <ESPmDNS.h>
// #include <Adafruit_NeoPixel.h>
// #include "effect.h"
// #include<Arduino.h>

// Adafruit_NeoPixel ws2812b(NUM_PIXELS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);
// WiFiClient client;
// WiFiServer server(80);

// void connectWiFi(void);
// String checkClient(void);
// void sendBackEcho(String echo);

// int lastState = HIGH;  // the previous state from the input pin
// int currentState; 
// const char *ssid = "BoNhungGiam";
// const char *password = "1223334444";
// String command = ""; // Command received from Android device

// void setup()
// {
//   Serial.begin(9600);
//   ws2812b.begin(); // initialize WS2812B strip object (headerUIRED)
//   ws2812b.setBrightness(10);
//   ws2812b.show();
//   connectWiFi();
//   server.begin();
// }

// void loop()
// {
//   client = server.available();
//   if (!client)
//     return;
//   command = checkClient();
//   if (command == "blue_on" || command == "blue")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {
//       ws2812b.setPixelColor(pixel, ws2812b.Color(0, 0, 255));
//     }
//     ws2812b.show();
//   }
//   else if (command == "azure_on" || command == "azure")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {
//       ws2812b.setPixelColor(pixel, ws2812b.Color(0, 255, 255));
//     }
//     ws2812b.show();
//   }
//   else if (command == "cyan_on" || command == "cyan")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {
//       ws2812b.setPixelColor(pixel, ws2812b.Color(0, 127, 255));
//     }
//     ws2812b.show();
//   }
//   else if (command == "aquamarine_on" || command == "aquamarine")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                           // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(0, 255, 127)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "green_on" || command == "green")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                         // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(0, 255, 0)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "yellow_on" || command == "yellow")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                           // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(255, 255, 0)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "magenta_on" || command == "magenta")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                           // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(255, 0, 255)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "rose_on" || command == "rose")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                           // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(255, 0, 127)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "red_on" || command == "red")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                         // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(255, 0, 0)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "orange_on" || command == "orange")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                           // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(255, 127, 0)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show();
//   }
//   else if (command == "white_on" || command == "white")
//   {
//     for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
//     {                                                             // for each pixel
//       ws2812b.setPixelColor(pixel, ws2812b.Color(255, 255, 255)); // it only takes effect if pixels.show() is called
//     }
//     ws2812b.show(); // update to the WS2812B Led Strip
//   }
//   else if (command == "off")
//   {
//     ws2812b.clear();
//   }
//   else if (command == "chasing_on" || command == "chasing")
//   {
//     ws2812b.clear();
//     theaterChase(ws2812b.Color(255, 255, 255), 50); // White
//     theaterChase(ws2812b.Color(255, 0, 0), 50);     // Red
//     theaterChase(ws2812b.Color(0, 0, 255), 50);     // Blue
//     theaterChase(ws2812b.Color(0, 255, 255), 50);   // Azure
//     theaterChase(ws2812b.Color(0, 127, 255), 50);   // Cyan
//     theaterChase(ws2812b.Color(0, 255, 127), 50);   // Aquamarine
//     theaterChase(ws2812b.Color(0, 255, 0), 50);     // Green
//     theaterChase(ws2812b.Color(255, 255, 0), 50);   // Yellow
//     theaterChase(ws2812b.Color(255, 0, 255), 50);   // magenta
//     theaterChase(ws2812b.Color(255, 0, 127), 50);   // rose
//     theaterChase(ws2812b.Color(255, 127, 0), 50);   // orange
//   }
//   else if (command == "rainbow_on" || command == "rainbow")
//   {
//     ws2812b.clear(); // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     Rainbow(10);
//   }
//   else if (command == "bouncing_balls_on" || command == "bouncing balls")
//   {
//     ws2812b.clear(); // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     byte red_blue_white[3][3] = {{255, 0, 0},
//                                  {255, 255, 255},
//                                  {0, 0, 255}};
//     BouncingColoredBalls(3, red_blue_white, false);
//     byte yellow_green_orange[3][3] = {{255, 255, 0},
//                                       {0, 255, 255},
//                                       {255, 127, 0}};
//     BouncingColoredBalls(3, yellow_green_orange, false);
//     byte azure_magenta_aquamarine[3][3] = {{0, 255, 255},
//                                            {255, 0, 255},
//                                            {0, 255, 127}};

//     BouncingColoredBalls(3, azure_magenta_aquamarine, false);
//   }
//   else if (command == "cylonbounce_on" || command == "cylonbounce")
//   {
//     ws2812b.clear();                       // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     CylonBounce(255, 0, 0, 4, 10, 50);     // red
//     CylonBounce(0, 255, 255, 4, 10, 50);   // azure
//     CylonBounce(0, 127, 255, 4, 10, 50);   // cyan
//     CylonBounce(0, 255, 127, 4, 10, 50);   // aquamarine
//     CylonBounce(0, 255, 0, 4, 10, 50);     // green
//     CylonBounce(255, 255, 0, 4, 10, 50);   // yellow
//     CylonBounce(255, 0, 255, 4, 10, 50);   // magenta
//     CylonBounce(255, 0, 127, 4, 10, 50);   // rose
//     CylonBounce(255, 127, 0, 4, 10, 50);   // orange
//     CylonBounce(255, 255, 255, 4, 10, 50); // white
//     CylonBounce(0, 0, 255, 4, 10, 50);     // blue
//   }
//   else if (command == "twinkle_on" || command == "twinkle")
//   {
//     ws2812b.clear();                        // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     Twinkle(255, 0, 0, 10, 100, false);     // red
//     Twinkle(0, 0, 255, 10, 100, false);     // blue
//     Twinkle(0, 255, 255, 10, 100, false);   // azure
//     Twinkle(0, 127, 255, 10, 100, false);   // cyan
//     Twinkle(0, 255, 127, 10, 100, false);   // aquamarine
//     Twinkle(0, 255, 0, 10, 100, false);     // green
//     Twinkle(255, 255, 0, 10, 100, false);   // yellow
//     Twinkle(255, 0, 255, 10, 100, false);   // magenta
//     Twinkle(255, 0, 127, 10, 100, false);   // rose
//     Twinkle(255, 127, 0, 10, 100, false);   // orange
//     Twinkle(255, 255, 255, 10, 100, false); // white
//   }
//   else if (command == "position_on" || command == "position")
//   {
//     ws2812b.clear();
//     Position(255, 0, 0, 8, 10, 50);   // red
//     Position(0, 0, 255, 8, 10, 50);   // blue
//     Position(0, 255, 255, 8, 10, 50); // azure
//     Position(0, 127, 255, 8, 10, 50); // cyan
//     Position(0, 255, 127, 8, 10, 50); // aquamarine
//     Position(0, 255, 0, 8, 10, 50);   // green
//     Position(255, 255, 0, 8, 10, 50); // yellow
//     Position(255, 0, 255, 8, 10, 50); // magenta
//     Position(255, 0, 127, 8, 10, 50); // rose
//     Position(255, 127, 0, 8, 10, 50); // orange
//   }
//   else if (command == "meteor_rain_on" || command == "meteor rain")
//   {
//     ws2812b.clear();
//     meteorRain(255, 255, 255, 10, 64, true, 30);
//   }
//   else if (command == "twinkle_random_on" || command == "twinkle random")
//   {
//     ws2812b.clear(); // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     TwinkleRandom(20, 100, false);
//   }
//   else if (command == "running_lights_on" || command == "running lights")
//   {
//     ws2812b.clear();                  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     RunningLights(0, 0, 255, 50);     // blue
//     RunningLights(0, 255, 255, 50);   // azure
//     RunningLights(0, 127, 255, 50);   // cyan
//     RunningLights(0, 255, 127, 50);   // aquamarine
//     RunningLights(0, 255, 0, 50);     // green
//     RunningLights(255, 255, 0, 50);   // yellow
//     RunningLights(255, 0, 255, 50);   // magenta
//     RunningLights(255, 255, 255, 50); // white
//     RunningLights(255, 0, 127, 50);   // rose
//     RunningLights(255, 127, 0, 50);   // orange
//     RunningLights(255, 0, 0, 50);     // red
//   }
//   else if (command == "eyes_on" || command == "eyes")
//   {
//     ws2812b.clear(); // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
//     HalloweenEyes(255, 0, 0,
//                   1, 4,
//                   true, random(5, 50), random(50, 150),
//                   random(1000, 10000));
//     HalloweenEyes(0, 0, 255,
//                   2, 4,
//                   true, random(5, 50), random(50, 150),
//                   random(1000, 10000));
//     HalloweenEyes(0, 127, 255,
//                   3, 4,
//                   true, random(5, 50), random(50, 150),
//                   random(1000, 10000));
//     HalloweenEyes(0, 255, 127,
//                   4, 4,
//                   true, random(5, 50), random(50, 150),
//                   random(1000, 10000));
//     HalloweenEyes(0, 255, 0,
//                   2, 4,
//                   true, random(5, 50), random(50, 150),
//                   random(1000, 10000));
//     HalloweenEyes(255, 127, 0,
//                   2, 4,
//                   true, random(5, 50), random(50, 150),
//                   random(1000, 10000));
//   }
//   else if (command == "chase_rainbow_on" || command == "chase rainbow")
//   {
//     ws2812b.clear();
//     theaterChaseRainbow(50);
//   }

//   // save the the last state
//   sendBackEcho(command); // send command echo back to android device
//   command = "";
// }

// /* connecting WiFi */
// void connectWiFi()
// {
//   Serial.println("Connecting to WIFI");
//   WiFi.begin(ssid, password);
//   while ((!(WiFi.status() == WL_CONNECTED)))
//   {
//     delay(300);
//     Serial.print("..");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("ESP32 Local IP is : ");
//   Serial.print((WiFi.localIP()));
// }

// /* check command received from Android Device */
// String checkClient(void)
// {
//   while (!client.available())
//     delay(1);
//   String request = client.readStringUntil('\r');
//   request.remove(0, 5);
//   request.remove(request.length() - 9, 9);
//   return request;
// }

// /* send command echo back to android device */
// void sendBackEcho(String echo)
// {
//   client.println("HTTP/1.1 200 OK ");
//   client.println("Content-Type: text/html");
//   client.println("");
//   client.println("<!DOCTYPE HTML>");
//   client.println("<html>");
//   client.println(echo);
//   client.println("</html>");
//   client.stop();
//   delay(1);
// }
