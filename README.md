#  Wi-Fi Based Touchless HMI using ESP8266

A wireless Human-Machine Interface (HMI) built on the NodeMCU ESP8266 that enables smartphone-controlled, touchless menu navigation over Wi-Fi — no physical buttons required.

---

##  Hardware Used

| Component | Specification |
|-----------|--------------|
| Microcontroller | NodeMCU ESP8266 (ESP-12E) |
| Display | 16x2 LCD (I2C interface) |
| Feedback | Active Buzzer |
| Power Supply | 5V via USB / 3.3V onboard regulator |
| Communication | Wi-Fi 802.11 b/g/n |

---

##  Repository Structure

```
wifi-touchless-hmi/
├── src/
│   ├── hmi_main.ino          # Main Arduino sketch
│   ├── web_server.ino        # Onboard HTTP web server logic
│   └── lcd_handler.ino       # LCD display helper functions
├── hardware/
│   ├── circuit_diagram.md    # Pin connections and wiring guide
│   └── components_list.md    # Bill of materials
├── docs/
│   └── working_principle.md  # Detailed system explanation
├── images/                   # Circuit photos / demo screenshots
└── README.md
```

---

##  How It Works

1. ESP8266 boots and connects to a configured Wi-Fi network
2. An onboard HTTP web server starts and serves a control interface
3. User opens the IP address on any smartphone browser — no app needed
4. Button presses on the web page send HTTP GET requests to the ESP8266
5. ESP8266 processes the command, updates the LCD menu, and triggers the buzzer for feedback
6. The entire interaction is touchless — controlled entirely over Wi-Fi

---

##  Features

- **Touchless operation** — ideal for hygiene-sensitive or industrial environments
- **Real-time LCD feedback** — menu updates instantly on command receipt
- **Event-driven firmware** — no blocking delays; uses interrupt-style request handling
- **Buzzer confirmation** — audio feedback on each command
- **Zero external app** — pure browser-based control interface

---

##  Pin Configuration

| ESP8266 Pin | Connected To |
|-------------|-------------|
| D1 (GPIO5)  | LCD SCL (I2C) |
| D2 (GPIO4)  | LCD SDA (I2C) |
| D5 (GPIO14) | Buzzer (+) |
| GND         | Common Ground |
| 3V3         | LCD VCC |

---

##  Getting Started

### Prerequisites
- Arduino IDE 1.8.x or 2.x
- ESP8266 board package installed ([install guide](https://arduino.esp8266.com/stable/package_esp8266com_index.json))
- Libraries required:
  - `ESP8266WiFi`
  - `ESP8266WebServer`
  - `LiquidCrystal_I2C`



---

## 🧠 Key Concepts Demonstrated

- IoT communication over Wi-Fi using ESP8266
- Embedded HTTP web server (no cloud dependency)
- Event-driven firmware architecture
- I2C protocol for LCD communication
- GPIO control for actuator feedback

---

## 📸 Demo

> *Add photos of your hardware setup and a screenshot of the web interface here*

---

## 📄 License

MIT License — free to use, modify, and distribute with attribution.

---

## 👩‍💻 Author

**Aditi S Puranik**  
B.E. Electronics & Communication Engineering  
Vidyavardhaka College of Engineering, Mysuru  
[LinkedIn](https://linkedin.com/in/aditi-s-puranik-598629391) · [GitHub](https://github.com/Adipuranik)
