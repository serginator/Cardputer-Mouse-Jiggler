# Cardputer Mouse Jiggler v1.0.2

This program for the M5Stack Cardputer moves the mouse cursor at random intervals to prevent the computer from going to sleep. It's perfect for keeping your computer active during long video sessions or presentations.

## Features

- Adjustable minimum and maximum jiggle intervals
- Start/stop with a button press
- Display the remaining time until the next move
- Display the current status (jiggling or not)
- Display the battery level
- Show jiggle count
- Toggle display with a button press (feat by [@jholubinka](https://github.com/jholubinka), thanks!)

## Setup

1. Install PlatformIO in your development environment.
2. Clone this repository.
3. Open the project in PlatformIO.
4. Build and upload the code to your M5Stack Cardputer.

## Generate release

Run `sh generate-release.sh` to generate a new version, update version in files and create a new release.

## Generate firmware

Install esptool.py: `pip install esptool`.
Then run `sh build-firmware.sh` to generate the firmware to be uploaded to M5Burner.
You will find it in the `generated_firmwares` folder.

## Usage

- Use Up/Down buttons to adjust the minimum jiggle interval.
- Use Left/Right buttons to adjust the maximum jiggle interval.
- Press OK to start/stop jiggling.
- Press SPACE button to toggle display on/off.

## Note

Ensure your computer's security settings allow for USB HID devices to be connected and used.
