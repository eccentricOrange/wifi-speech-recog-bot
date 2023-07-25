import requests
import speech_recognition

COMMANDS = {
    "forward": "F",
    "backward": "B",
    "left": "L",
    "right": "R",
    "stop": "S",
}

voice = 'bsdk'  # this comes from the speech recognition module
command = COMMANDS.get(voice, 'I')

ESP_IP = "192.168.137.249"  # Replace with the ESP32's IP address on the Wi-Fi network
ESP_PORT = 80

def send_string_to_esp32(data):
    url = f"http://{ESP_IP}:{ESP_PORT}/"
    payload = data
    try:
        response = requests.post(url, data=payload)
        print("Received from ESP32:", response.text)
    except requests.exceptions.RequestException as e:
        print("Error communicating with ESP32:", e)

if __name__ == "__main__":
    your_string = 'F'
    send_string_to_esp32(your_string)