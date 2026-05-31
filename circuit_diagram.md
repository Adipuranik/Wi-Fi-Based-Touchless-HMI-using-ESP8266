# Circuit Diagram & Wiring Guide — Wi-Fi Touchless HMI

## Pin Connections

### NodeMCU ESP8266 → 16x2 LCD (I2C Module)

```
NodeMCU         I2C LCD Module
─────────       ──────────────
D1 (GPIO5)  --> SCL
D2 (GPIO4)  --> SDA
3V3         --> VCC
GND         --> GND
```

> The I2C LCD module typically has address 0x27 or 0x3F.
> Run an I2C scanner sketch if LCD does not display — address may differ.

---

### NodeMCU ESP8266 → Active Buzzer

```
NodeMCU         Active Buzzer
─────────       ─────────────
D5 (GPIO14) --> (+) Positive pin
GND         --> (-) Negative pin
```

> Use an active buzzer (not passive) — it beeps on HIGH signal without PWM.

---

## Full Wiring Diagram (Text)

```
                    ┌─────────────────────────┐
                    │     NodeMCU ESP8266      │
                    │                         │
  USB/Power ──────► │ VIN              D1/SCL │──────► LCD SCL
                    │                  D2/SDA │──────► LCD SDA
                    │                  D5     │──────► Buzzer(+)
                    │                  3V3    │──────► LCD VCC
                    │                  GND    │──────► LCD GND
                    │                  GND    │──────► Buzzer(-)
                    └─────────────────────────┘
```

---

## Notes
- Power the NodeMCU via USB (5V). The onboard regulator provides 3.3V for peripherals.
- Keep buzzer wire short to avoid interference with I2C signals.
- LCD backlight brightness can be adjusted via the potentiometer on the I2C module.
