import speech_recognition
import requests
from os import environ

COMMANDS = {
    "forward": "F",
    "backward": "B",
    "left": "L",
    "right": "R",
    "stop": "S",
}

ESP_IP = environ.get("ESP_IP", "")
ESP_PORT = 80


def send_string_to_esp32(data: str) -> bool:
    url = f"http://{ESP_IP}:{ESP_PORT}/"

    try:
        response = requests.post(url, data=data)
        print("Received from ESP32:", response.text)

    except requests.exceptions.RequestException as e:
        print("Error communicating with ESP32:")
        print(e.args[0])

    else:
        return response.text.strip() == "OK"


def get_audio(source: speech_recognition.AudioSource, recognizer: speech_recognition.Recognizer) -> speech_recognition.AudioData:
    try:
        audio = recognizer.listen(source, timeout=3)

    except speech_recognition.WaitTimeoutError:
        print("Timed out waiting for phrase.")
        print("Press ENTER when ready for next phrase.")

    else:
        return audio

    return None


def recognize_speech(audio: speech_recognition.AudioData, recognizer: speech_recognition.Recognizer) -> str:
    try:
        text = recognizer.recognize_google(audio)
        print("Recognized:", text)
        return text

    except speech_recognition.UnknownValueError:
        print("Didn't understand that.")
        return None

    except speech_recognition.RequestError as e:
        print(f"Couldn't request results from Google Speech Recognition service")
        print(e.args[0])

        return None


def main(main_source: speech_recognition.AudioSource, main_recognizer: speech_recognition.Recognizer):
    print("Say something!")
    audio = get_audio(main_source, main_recognizer)

    if not audio:
        return

    text = recognize_speech(audio, main_recognizer)

    if not text:
        return

    command = COMMANDS.get(text.lower(), 'I')

    if not send_string_to_esp32(command):
        return


if __name__ == "__main__":
    recognizer = speech_recognition.Recognizer()
    
    with speech_recognition.Microphone() as source:
        print("Press ENTER when ready to start recording, or q to quit.")

        while input() != 'q':
            main(source, recognizer)