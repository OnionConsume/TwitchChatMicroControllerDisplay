# TwitchChatMicroControllerDisplay
This shows your twitch chat on a display, it is easy to setup. 



Welcome to the TwitchChatMicroControllerDisplay wiki!

Step 1: Obtain Twitch OAuth Token
If you don't have one already, you'll need to obtain a Twitch OAuth token for your bot.
Navigate to the Twitch Developer site and log in to your account.
Create a new application to obtain the required OAuth token.
Make sure to follow the instructions carefully to generate the token.
Check the youtube video, if you cannot find it. https://www.youtube.com/watch?v=dJwrFcBKvJw


Step 2: Hardware Connections
Connect your ESP8266 microcontroller to the OLED screen.
Ensure that the necessary pins are correctly connected for the communication interface you are using (e.g., SDA and SCL for I2C).


Step 3: Configure Wi-Fi Credentials
In the code, locate the lines where the Wi-Fi credentials are specified:
const char* ssid = "Wifi"; // put your own wifi SSID / Name here
const char* password = "Broodje"; // Put your wifi password here
Replace "Wifi" with your actual Wi-Fi network SSID and "Broodje" with your Wi-Fi password.


Step 4: Twitch Configuration
Replace the placeholder with your Twitch OAuth token:
const char* oauth = "awda212rw3fg132t123123"; // put your Twitch Oauth token here
Replace the channel name with your own channel name:
const char* channel = "#GAMINGHOUND"; // example put your channel name in here


Step 5: Upload the Code
Connect your ESP8266 to your computer and open the Arduino IDE.
Make sure the necessary libraries (Wire, Adafruit_GFX, Adafruit_SSD1306, ESP8266WiFi) are installed.
Open the provided code in the Arduino IDE and make the necessary modifications.
Upload the code to your ESP8266 microcontroller.


Step 6: Monitor Serial Output
Connect your microcontroller to your computer via USB.
Open the serial monitor in the Arduino IDE to view any debug information and ensure the Wi-Fi and Twitch connections are established without any errors.


Step 7: Test the Display
Make sure your ESP8266 is connected to your Wi-Fi network.
Check the OLED screen to verify that the messages received from your Twitch channel are being displayed correctly.


Step 8: Error Handling and Debugging
Test the code thoroughly to ensure it works as intended.
Handle potential errors, such as network disconnections or errors from the Twitch IRC server, gracefully within the code.
By following these steps, you can successfully set up the provided code with Twitch and your microcontroller. Make sure to test the code thoroughly and handle any errors that may arise during the process.
