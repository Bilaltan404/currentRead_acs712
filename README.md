# ADC Reading with FreeRTOS on ESP32

This project demonstrates how to read analog data using the ADC (Analog-to-Digital Converter) on an ESP32 with FreeRTOS. The code reads the ADC value from a specific channel (ADC1_CHANNEL_3) and prints the result to the serial console every 2 seconds.

## Requirements

- **ESP32 Development Board**
- **ESP-IDF Framework**
- **FreeRTOS**
- **Connected Analog Sensor** (e.g., potentiometer, temperature sensor, etc.)

## Features

- **FreeRTOS Task**: The project creates a task using FreeRTOS to continuously read ADC values in a loop.
- **ADC Configuration**: The ADC is configured with 12-bit resolution and attenuation of 11dB.
- **Periodic ADC Reading**: The ADC value is read every 2 seconds and printed to the console.

## Project Structure

. ├── main │ ├── main.c # Main source code file │ └── CMakeLists.txt # Build configuration file ├── CMakeLists.txt # Root build configuration file └── README.md # Project description file


## Code Explanation

1. **Task Creation**:
   - A FreeRTOS task `adcReadTask` is created in the `app_main` function, which will read the ADC values periodically.
   - The task is created with a stack size of `4096` bytes and a priority of `5`.

2. **ADC Configuration**:
   - The ADC1 channel 3 is configured using `adc1_config_channel_atten` with 11dB attenuation. 
   - ADC resolution is set to 12 bits (0-4095) using `adc1_config_width`.

3. **Reading ADC**:
   - In the `adcReadTask` function, the ADC value is read using `adc1_get_raw(ADC1_CHANNEL_3)` and printed to the console.
   - A delay of 2000 milliseconds (2 seconds) is applied between readings using `vTaskDelay`.

## How to Use

1. **Set up ESP-IDF**: 
   - Make sure you have [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) installed and configured properly on your development environment.

2. **Clone the Repository**:
   ```bash
   git clone <repository-url>
   cd <project-directory>

3. **Build the Project:**:
   ```bash
   idf.py build

4. **Flash the Project to the ESP32:**:
   ```bash
    idf.py flash

5. **Monitor the Serial Output:**:
   ```bash
    idf.py monitor

## Example Output
    ```bash
ADC Value: 1234
ADC Value: 1456
ADC Value: 1600
