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

5.  Run the Python script.

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