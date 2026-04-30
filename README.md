# Automatic Pill Reminder System

An embedded system project built using **Arduino Uno** that helps users remember to take medication on time using real-time clock scheduling, LCD notifications, and an audible buzzer alert.

---

## Overview

The **Automatic Pill Reminder System** is designed to provide timely medication reminders using a preset daily alarm.

The system uses a **Real-Time Clock (RTC)** module for accurate timekeeping and alerts the user through:

* **16x2 LCD visual notification**
* **Buzzer alarm alert**

Users can configure the reminder time using push buttons, making the system simple, reliable, and user-friendly.

---

## Features

* Real-time accurate clock using **DS1307 / DS3231 RTC**
* Daily pill reminder scheduling
* 16x2 LCD display for time and reminder status
* Audible buzzer alert
* Easy reminder time configuration using push buttons
* Alarm acknowledgment option
* Repeats automatically every day
* Compact and low-power embedded design

---

## Hardware Components

| Component                  | Quantity    |
| -------------------------- | ----------- |
| Arduino Uno                | 1           |
| DS1307 / DS3231 RTC Module | 1           |
| 16x2 I2C LCD Display       | 1           |
| Piezo Buzzer               | 1           |
| Push Buttons               | 3           |
| Breadboard / PCB           | 1           |
| Jumper Wires               | As required |

---

## Pin Configuration

### Push Buttons

| Function             | Arduino Pin |
| -------------------- | ----------- |
| Set Hour             | D2          |
| Set Minute           | D3          |
| Confirm / Stop Alarm | D4          |

### Output Device

| Device | Arduino Pin |
| ------ | ----------- |
| Buzzer | D9          |

### I2C Connections

| Module | Arduino Uno |
| ------ | ----------- |
| SDA    | A4          |
| SCL    | A5          |

---

## Working Principle

### 1. System Initialization

On power-up:

* LCD initializes
* RTC status is checked
* Default reminder time is loaded
* Welcome message is displayed

---

### 2. Reminder Time Setup

The user sets the daily reminder using buttons:

* **Set Hour Button** → Increments reminder hour
* **Set Minute Button** → Increments reminder minute
* **Confirm Button** → Saves reminder time

---

### 3. Time Monitoring

The RTC continuously provides the current time.

The LCD displays:

**Line 1:** Current Time
**Line 2:** Reminder Time / Setup Prompt

---

### 4. Alarm Trigger

When current RTC time matches the preset reminder time:

* Buzzer starts beeping
* LCD continues displaying reminder status

---

### 5. Alarm Stop

The alarm will:

* Stop automatically after **10 seconds**, or
* Stop immediately when the **Confirm button** is pressed

---

## Usage Instructions

### Step 1

Power the system.

---

### Step 2

Set the reminder hour using the **Set Hour** button.

---

### Step 3

Set the reminder minute using the **Set Minute** button.

---

### Step 4

Press **Confirm** to save the reminder.

---

### Step 5

Wait for the scheduled reminder time.

---

### Step 6

Press **Confirm** to stop the buzzer when the alarm sounds.

---

## Software Requirements

* **Arduino IDE**
* Required Libraries:

### Install via Library Manager

#### 1. RTClib

Used for RTC communication

#### 2. LiquidCrystal_I2C

Used for LCD display

#### 3. Wire

Built-in Arduino I2C library

---

## Code Structure

### `setup()`

Initializes:

* LCD
* RTC
* Buttons
* Buzzer

---

### `loop()`

Handles:

* Time display updates
* Button input detection
* Alarm checking
* Reminder activation

---

### Helper Functions

#### `printTwoDigits()`

Formats time display

#### `buzzAlarm()`

Controls buzzer alert behavior

---

## Installation

### Clone the repository

```bash
git clone <your-repository-link>
```

---

### Open Arduino IDE

Load:

```cpp
Automatic_Pill_Reminder.ino
```

---

### Connect Hardware

Wire components as per the pin configuration table.

---

### Upload Code

Select:

* **Board:** Arduino Uno
* Correct COM Port

Then click **Upload**

---

## Troubleshooting

### RTC Not Working

* Verify I2C wiring
* Check RTC battery
* Confirm RTC library installation

---

### LCD Not Displaying

Check LCD I2C address.

Common addresses:

* `0x27`
* `0x3F`

Modify:

```cpp
LiquidCrystal_I2C lcd(0x27, 16, 2);
```

---

### Buttons Not Responding

* Check wiring
* Ensure internal pull-up configuration is enabled

---

### Buzzer Not Working

* Verify pin connection
* Test buzzer independently

---

## Future Improvements

* Multiple daily reminders
* EEPROM storage for reminder persistence
* RTC interrupt-based alarm triggering
* Bluetooth / Wi-Fi notifications
* Menu-driven LCD interface
* Battery backup support
* Mobile app integration

---

## Applications

* Elderly medication assistance
* Hospital patient care
* Personal healthcare reminder
* Medicine scheduling support

---

## Technologies Used

* Arduino Embedded C++
* I2C Communication
* Real-Time Clock Scheduling
* LCD Interface
* Digital Input/Output Control

---

## Author

**Nithin Kumar**

Embedded Systems Engineer
Focused on Embedded Systems, Microcontroller Programming, and Real-Time Applications

