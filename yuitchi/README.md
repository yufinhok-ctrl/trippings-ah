# Yuitchi - ESP32 WiFi Security Tamagotchi

Yuitchi is an ESP32-based project that combines WiFi security testing with a virtual pet concept (similar to Tamagotchi). The device automatically scans for WiFi networks, performs deauthentication attacks to capture WPA2 handshakes, and rewards the user with a virtual pet that grows healthier when handshakes are successfully captured.

## Features

- Automatic WiFi network scanning
- Deauthentication attack automation
- WPA2 handshake capture simulation
- Virtual pet that needs feeding and care
- SSD1306 OLED display for status
- Web UI for monitoring and control
- Automatic cycling through attack phases

## Hardware Requirements

- ESP32 development board
- SSD1306 OLED display (I2C)
- USB cable for power/programming

## Software Dependencies

- Arduino core for ESP32
- SSD1306Wire library
- ESP32WebServer library

## How It Works

1. **Scanning Phase**: The ESP32 scans for available WiFi networks
2. **Deauth Phase**: Sends deauthentication packets to a selected target network
3. **Handshake Phase**: Attempts to capture WPA2 handshake (simulated)
4. **Success Phase**: Displays captured network info and feeds the virtual pet
5. **Repeat**: Cycles back to scanning after a delay

The virtual pet's happiness and hunger levels change over time. Feeding the pet (via web UI or successful handshake) improves its state.

## Web Interface

Access the device's IP address in a browser to:
- View current pet status (happiness, hunger)
- See if a handshake was captured
- Manually feed the pet
- Reset the attack cycle

## Files

- `main.cpp`: Main program logic
- `pet.h/pet.cpp`: Virtual pet implementation
- `String.h`: Simple string class implementation
- `platformio.ini`: PlatformIO configuration

## Note on WiFi Attacks

This project is for educational purposes only. Performing deauthentication attacks on networks you don't own or have explicit permission to test may be illegal in your jurisdiction. Only test on networks you own or have written authorization to assess.

## License

MIT