# Automatic-Pill-Remainder-System

Automatic Pill Reminder System
Overview
This project is an Automatic Pill Reminder System built using an Arduino Uno, DS1307/DS3231 Real Time Clock (RTC) module, 16x2 LCD display, a buzzer, and three push buttons. It helps users to timely remember taking their pills by providing an audible alarm and a visual reminder on the LCD at a preset daily time. The system allows easy setup of the daily pill reminder time through button inputs.

Features
Real-time clock based accurate timekeeping using DS1307 or DS3231 RTC module.

Time and pill reminder displayed on a 16x2 LCD screen.

Three push buttons to interact with the system:

Set the hour for the reminder time.

Set the minute for the reminder time.

Confirm and save the reminder time, also stop the alarm.

Buzzer alarm that sounds for 10 seconds at the reminder time or until acknowledged.

Simple user interface to set daily pill reminder time.

Low power components and compact design for easy implementation.

Hardware Components
Arduino Uno microcontroller board

DS1307 or DS3231 RTC Module (for timekeeping)

16x2 I2C LCD Display (address 0x27 commonly)

Piezo Buzzer

3 Push Buttons

Connecting wires and breadboard or PCB

Wiring Summary
RTC Module connected via I2C pins (SDA to A4, SCL to A5 on Arduino Uno).

LCD connected via I2C (SDA to A4, SCL to A5).

Push Buttons connected to digital pins 2 (Set Hour), 3 (Set Minute), and 4 (Confirm) with internal pull-up resistors.

Buzzer connected to digital pin 9.

Common ground shared between components and Arduino.

Usage Instructions
Power the Arduino with the RTC, LCD, buzzer, and buttons connected.

The LCD will display the current time and prompt to set the pill reminder.

Press the Set Hour button repeatedly to increment the reminder hour.

Press the Set Minute button to switch to minute setting mode, then press repeatedly to increment the reminder minutes.

Press the Confirm button to save the reminder time.

When the set time matches the RTC time, the buzzer will beep for 10 seconds.

Press the Confirm button during the alarm to stop the buzzer.

The reminder will repeat daily at the set time.

Code Structure
setup(): Initializes the LCD, RTC, buttons, and buzzer. Checks if the RTC is running correctly.

loop(): Continuously updates the current time display, processes button inputs to set reminder time, triggers alarm at the set time.

Helper functions for printing numbers on the LCD and buzzing alarm.

Libraries Required
Wire (built-in Arduino library for I2C communication)

RTClib by Adafruit (for DS1307/DS3231 RTC)

LiquidCrystal_I2C (for 16x2 LCD display with I2C interface)

Installation
Install the required libraries via Arduino IDE Library Manager:

Search for and install RTClib

Search for and install LiquidCrystal_I2C (make sure you have a compatible version)

Connect the hardware components as per wiring summary.

Open the Arduino IDE and load the sketch_sep14a.ino code.

Upload the code to the Arduino Uno.

Open the Serial Monitor (optional) for debugging messages.

Troubleshooting
RTC not working: Ensure RTC module is connected correctly, check battery on the RTC, and confirm library support.

LCD not displaying properly: Check I2C address of your LCD (0x27 is common but may differ), adjust LiquidCrystal_I2C lcd(0x27,16,2); accordingly.

Buttons not responding: Confirm buttons are wired correctly with pull-up resistors or use Arduino internal pull-ups as in the code.

Buzzer not buzzing: Check buzzer wiring and test with direct 5V power.

Future Improvements
Add multiple reminder times in one day.

Use an RTC alarm interrupt for more precise buzzer control.

Add LCD menu navigation for easier setting without pressing multiple buttons.

Integrate wireless notifications (e.g., Bluetooth or Wi-Fi).

Use EEPROM for saving reminder time permanently.
