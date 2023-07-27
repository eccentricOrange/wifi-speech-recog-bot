# Wi-Fi Speech Recognition Robot

This project is a Wi-Fi speech recognition robot that can be controlled using voice commands. It uses an [ESP32](https://www.espressif.com/en/products/socs/esp32) board, your laptop's microphone, and a motor driver to control the movement of the robot. The robot can be connected to a Wi-Fi network and controlled using a Python script located in the server folder.

The Python script listens for incoming requests from the robot and uses the [Google Cloud Speech-to-Text API](https://cloud.google.com/speech-to-text) to convert the audio to text, through [SpeechRecognition](https://github.com/Uberi/speech_recognition). The text is then parsed and [executed on the robot using the DDBot](https://github.com/eccentricOrange/DDBot).

## Usage
1.  **\[OPTIONAL STEP\]** Use a Python virtual environment.

    Create a Python virtual environment in the `server` folder.

    ```sh
    python -m venv .venv
    ```

    Activate the virtual environment, following the [documentation from Python](https://docs.python.org/3/tutorial/venv.html).

2.  Install the required Python packages.

    ```sh
    python -m pip install -r requirements.txt
    ``` 

3.  Configure the Wi-Fi credentials in the `secrets.h` file.

    To set up the Wi-Fi credentials, create a file named `secrets.h` in the `include` folder. The file should contain the following code:

    ```c++
    #define SSID "your_wifi_ssid"
    #define PASSWORD "your_wifi_password"
    ```

    Ensure to replace `your_wifi_ssid` and `your_wifi_password` with your Wi-Fi credentials.

4.  Upload the code to the ESP32 board.

5.  Set the IP address and run the Python script.

    You need to set the IP address of the ESP32 board as an environment variable named `ESP_IP`.
    
    To do so in Windows (no PowerShell), run the following command:

    ```pwsh
    $env:ESP_IP = "your_esp_ip_address"
    ```

    To do so in Linux, run the following command:

    ```sh
    export ESP_IP="your_esp_ip_address"
    ```

    Ensure to replace `your_esp_ip_address` with the IP address of the ESP32 board.

    Then, run the Python script.

    ```sh
    python main.py
    ```

    Remember to run this from the `server` folder, and activate the virtual environment if you created one.

The script will listen for speech commands once you press the Enter key. You can say the following commands:
* "Forward"
* "Backward"
* "Left"
* "Right"
* "Stop"

## Using with Arduino IDE
This project is meant to be used with the [PlatformIO](https://platformio.org/) IDE. However, you can also use the Arduino IDE to upload the code to the ESP32 board. To do this, follow the steps below:

1.  Install the [ESP32 Arduino Core](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/installing.html) from the board manager, and DDBot from the library manager.
2.  Create a new project in the Arduino IDE.
3.  Copy the contents of the `src/main.cpp` file to the new project. This is the main sketch file.
4.  Create a new file named `secrets.h` in the root folder of the project (instead of creating in the `include` folder), as described in step 3 of the [Usage](#usage) section.
5.  Upload the code to the ESP32 board.