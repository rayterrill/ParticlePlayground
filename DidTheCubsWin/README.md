# ParticlePlayground
## DidTheCubsWin
Allows a Particle device (Photon, etc) to subscribe to a IFTTT ESPN feed to light up an Adafruit NeoPixel 8x8 LED square to show
whether the Cubbies won or lost.

I tried to find someone else who had done this, and while I saw a lot of people who had tried, I didn't see any successful builds.

Hope someone finds this useful!

To use:

* Log into IFTTT, and create a recipe
* Click This, and choose the ESPN channel
* Choose the New Final Score trigger
* Pick MLB and the Chicago Cubs
* Click That, and choose the Particle channel
* Choose the Publish an event action
* Change the "Then publish (Event Name)" section to "DidTheCubsWin"
* Leave the "The event includes (Data)" section as "AlertBody"
* Select private in the "Is this a public or private event?" section, and click "Create action"
