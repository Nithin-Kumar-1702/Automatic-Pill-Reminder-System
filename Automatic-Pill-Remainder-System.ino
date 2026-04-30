/*
===========================================================
AUTOMATIC PILL REMINDER SYSTEM
===========================================================

Components Used:
1. Arduino Uno
2. RTC Module (DS3231 / DS1307)
3. 16x2 I2C LCD
4. Buzzer
5. 3 Push Buttons

Function:
- Displays current time
- Allows user to set reminder hour and minute
- Activates buzzer when reminder time matches RTC time
- Stops buzzer when confirm button is pressed
===========================================================
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

/*---------------------------------------------------------
  LCD Initialization
---------------------------------------------------------*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*---------------------------------------------------------
  RTC Initialization
---------------------------------------------------------*/
RTC_DS3231 rtc;

/*---------------------------------------------------------
  Pin Definitions
---------------------------------------------------------*/
#define BUTTON_SET_HOUR    2
#define BUTTON_SET_MINUTE  3
#define BUTTON_CONFIRM     4
#define BUZZER_PIN         9

/*---------------------------------------------------------
  Global Variables
---------------------------------------------------------*/
int reminderHour = 8;
int reminderMinute = 0;

unsigned char settingHour = 0;
unsigned char settingMinute = 0;
unsigned char reminderSet = 0;
unsigned char alarmActive = 0;

/*---------------------------------------------------------
  Function Prototypes
---------------------------------------------------------*/
void displayTime(DateTime now);
void displayReminder(void);
void checkButtons(void);
void checkAlarm(DateTime now);
void buzzAlarm(void);
void printTwoDigits(int num);

/*---------------------------------------------------------
  Setup Function
---------------------------------------------------------*/
void setup()
{
    Serial.begin(9600);

    /* Initialize LCD */
    lcd.begin(16, 2);
    lcd.backlight();

    /* Initialize RTC */
    if (!rtc.begin())
    {
        lcd.print("RTC Failed!");
        while (1);
    }

    /* If RTC lost power, set current compile time */
    if (rtc.lostPower())
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    /* Configure Button Pins */
    pinMode(BUTTON_SET_HOUR, INPUT_PULLUP);
    pinMode(BUTTON_SET_MINUTE, INPUT_PULLUP);
    pinMode(BUTTON_CONFIRM, INPUT_PULLUP);

    /* Configure Buzzer */
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    /* Welcome Message */
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pill Reminder");
    delay(2000);
    lcd.clear();
}

/*---------------------------------------------------------
  Main Loop
---------------------------------------------------------*/
void loop()
{
    DateTime now = rtc.now();

    /* Display current time */
    displayTime(now);

    /* Display reminder time */
    displayReminder();

    /* Read button input */
    checkButtons();

    /* Check if alarm should trigger */
    checkAlarm(now);

    /* Activate buzzer if needed */
    if (alarmActive)
    {
        buzzAlarm();
    }
}

/*---------------------------------------------------------
  Display Current Time
---------------------------------------------------------*/
void displayTime(DateTime now)
{
    lcd.setCursor(0, 0);
    lcd.print("Time: ");

    printTwoDigits(now.hour());
    lcd.print(":");

    printTwoDigits(now.minute());
    lcd.print(":");

    printTwoDigits(now.second());
}

/*---------------------------------------------------------
  Display Reminder Time
---------------------------------------------------------*/
void displayReminder(void)
{
    lcd.setCursor(0, 1);

    if (reminderSet)
    {
        lcd.print("Remind: ");
        printTwoDigits(reminderHour);
        lcd.print(":");
        printTwoDigits(reminderMinute);
    }
    else
    {
        lcd.print("Set Reminder ");
    }
}

/*---------------------------------------------------------
  Handle Button Presses
---------------------------------------------------------*/
void checkButtons(void)
{
    /* Set Hour Button */
    if (digitalRead(BUTTON_SET_HOUR) == LOW)
    {
        reminderHour++;

        if (reminderHour > 23)
            reminderHour = 0;

        settingHour = 1;
        settingMinute = 0;

        delay(300);
    }

    /* Set Minute Button */
    if (digitalRead(BUTTON_SET_MINUTE) == LOW)
    {
        reminderMinute++;

        if (reminderMinute > 59)
            reminderMinute = 0;

        settingHour = 0;
        settingMinute = 1;

        delay(300);
    }

    /* Confirm Button */
    if (digitalRead(BUTTON_CONFIRM) == LOW)
    {
        reminderSet = 1;
        settingHour = 0;
        settingMinute = 0;

        delay(500);
    }
}

/*---------------------------------------------------------
  Check Alarm Condition
---------------------------------------------------------*/
void checkAlarm(DateTime now)
{
    if (reminderSet &&
        now.hour() == reminderHour &&
        now.minute() == reminderMinute &&
        now.second() == 0)
    {
        alarmActive = 1;
    }
}

/*---------------------------------------------------------
  Buzzer Alarm Function
---------------------------------------------------------*/
void buzzAlarm(void)
{
    unsigned long start = millis();

    while ((millis() - start) < 10000)
    {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(200);

        digitalWrite(BUZZER_PIN, LOW);
        delay(200);

        /* Stop alarm if confirm button pressed */
        if (digitalRead(BUTTON_CONFIRM) == LOW)
        {
            alarmActive = 0;
            digitalWrite(BUZZER_PIN, LOW);
            delay(500);
            break;
        }
    }
}

/*---------------------------------------------------------
  Print Two Digit Number
---------------------------------------------------------*/
void printTwoDigits(int num)
{
    if (num < 10)
        lcd.print("0");

    lcd.print(num);
}
