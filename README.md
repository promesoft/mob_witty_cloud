# mob_witty_cloud
Programming the Witty Cloud board with Arduino 

Step 1 - Flash the Witty Cloud with NodeMCU firmware:
Windows: https://github.com/nodemcu/nodemcu-flasher
(Just use the default flash - no need to make your own)

Step 2 - Setup Wemos in Arduino
http://www.wemos.cc/tutorial/get_started_in_arduino.html
1. Install Arduino 1.6.7 from the Arduino website.

2. Start Arduino and open Preferences window.

3. Enter 
   
   http://arduino.esp8266.com/stable/package_esp8266com_index.json
   
   into Additional Boards Manager URLs field. 
   You can add multiple URLs, separating them with commas.

4. Open Tools→Board:xxx→Boards Manager and install esp8266 by ESP8266 Community 
   (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

Step 3 - Use Wemos D1 as a device 

Step 4 - Apply this code to Arduino IDE and upload it to your Witty Cloud device

Notes:
From "http://www.esp8266.com/viewtopic.php?f=13&t=7409"
the pins seem to be:

LDR = A0;
RED = 15;
GREEN = 12;
BLUE = 13;
BUTTON = 4; - See more at: http://www.esp8266.com/viewtopic.php?f=13&t=7409#sthash.S6VFMz0Q.dpuf
