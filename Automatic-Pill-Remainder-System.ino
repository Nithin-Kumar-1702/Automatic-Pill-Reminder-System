// Automatic Pill Reminder System
// Components: Arduino Uno, Buzzer, RTC Module (DS1307/DS3231), LCD Display (16x2), 3 Push Buttons

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change address if needed

// RTC setup
RTC_DS3231 rtc;

// Pins for buttons
const int buttonSetHourPin = 2;    // Button to set reminder hour
const int buttonSetMinutePin = 3;  // Button to set reminder minute
const int buttonConfirmPin = 4;    // Button to confirm reminder time

// Buzzer pin
const int buzzerPin = 9;

// Variables to store pill reminder time
int reminderHour = 8;   // default reminder hour
int reminderMinute = 0; // default reminder minute

// States
bool settingHour = false;
bool settingMinute = false;
bool reminderSet = false;
bool alarmActive = false;

void setup() {
  // Initialize serial for debugging
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin( 16, 2 );
  lcd.backlight();

  // Initialize RTC
  if (!rtc.begin()) {
    lcd.print("RTC Failed!");
    while (1);
  }

  if (rtc.lostPower()) {
    // Set to a default date/time
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Initialize buttons
  pinMode(buttonSetHourPin, INPUT_PULLUP);
  pinMode(buttonSetMinutePin, INPUT_PULLUP);
  pinMode(buttonConfirmPin, INPUT_PULLUP);

  // Initialize buzzer
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Start display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pill Reminder");
  delay(2000);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();

  // Display current time
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  printTwoDigits(now.hour());
  lcd.print(":");
  printTwoDigits(now.minute());
  lcd.print(":");
  printTwoDigits(now.second());

  // Display reminder time or prompt
  lcd.setCursor(0, 1);
  if (reminderSet) {
    lcd.print("Remind: ");
    printTwoDigits(reminderHour);
    lcd.print(":");
    printTwoDigits(reminderMinute);
    lcd.print("  ");
  } else {
    lcd.print("Set Reminder  ");
  }

  // Check buttons for setting reminder
  if (digitalRead(buttonSetHourPin) == LOW) {
    settingHour = true;
    settingMinute = false;
    delay(300); // debounce
  }

  if (digitalRead(buttonSetMinutePin) == LOW) {
    if (settingHour) {
      settingHour = false;
      settingMinute = true;
    }
    delay(300); // debounce
  }

  if (settingHour) {
    reminderHour++;
    if (reminderHour > 23) reminderHour = 0;
    lcd.setCursor(0, 1);
    lcd.print("Set Hour:      ");
    lcd.setCursor(10, 1);
    printTwoDigits(reminderHour);
    delay(300);
  } else if (settingMinute) {
    reminderMinute++;
    if (reminderMinute > 59) reminderMinute = 0;
    lcd.setCursor(0, 1);
    lcd.print("Set Min:       ");
    lcd.setCursor(10, 1);
    printTwoDigits(reminderMinute);
    delay(300);
  }

  // Confirm button sets the reminder
  if (digitalRead(buttonConfirmPin) == LOW) {
    reminderSet = true;
    settingHour = false;
    settingMinute = false;
    delay(500); // debounce
  }

  // Check if it's time to remind
  if (reminderSet && now.hour() == reminderHour && now.minute() == reminderMinute && now.second() == 0) {
    alarmActive = true;
  }

  if (alarmActive) {
    buzzAlarm();
  }
}

void printTwoDigits(int digits) {
  if (digits < 10) {
    lcd.print("0");
  }
  lcd.print(digits);
}

void buzzAlarm() {
  // Buzz for 10 seconds or until confirm button pressed
  unsigned long start = millis();
  while (millis() - start < 10000) {
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
    delay(200);

    if (digitalRead(buttonConfirmPin) == LOW) {
      alarmActive = false;
      digitalWrite(buzzerPin, LOW);
      delay(500); // debounce
      break;
    }
  }
}

