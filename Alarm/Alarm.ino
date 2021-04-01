#include <LiquidCrystal.h>
#include <Wire.h>
#include <DS3231.h> //Get ds3231FS from the Tools > Manage Libraries > DS3231

RTClib myRTC;

DS3231 Clock;

//Declaring data pins
const int lcd1 = 2;
const int lcd2 = 3;
const int lcd3 = 4;
const int lcd4 = 5;
const int lcd5 = 6;
const int lcd6 = 7;
const int button1 = 8; //Up Button
const int button2 = 9; //Down Button
const int button3 = 10; //Set Button

LiquidCrystal lcd(lcd1, lcd2, lcd3, lcd4, lcd5, lcd6);

//The settime function is before start and loop beacuse older versions of arduino require it.
int settime(String varname, int maxnumber = 60, int minnumber = 0)
{
  int var = minnumber;
  int setvar = 1;
  while(setvar == 1)
    {
      int upstate, downstate, setstate;
      lcd.setCursor(0, 0);
      lcd.print("Set ");
      lcd.print(varname);
      lcd.setCursor(0, 1);
      lcd.print(var);
      lcd.print(" ");
      upstate = digitalRead(button1);
      downstate = digitalRead(button2);
      setstate = digitalRead(button3);
      delay(250);
      if(upstate == LOW)
      {
        if(var == maxnumber)
        {
          var = minnumber;
        }
        else
        {
          var = var + 1;
        }
      }
      if(downstate == LOW)
      {
        if(var == minnumber)
        {
          var = maxnumber;
        }
        else
        {
          var = var - 1;
        }
      }
      if(setstate == LOW)
      {
        setvar = 0;
        return(var);
      }
    }
}

void setup() {
  Wire.begin();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  lcd.begin(16, 2);
  Clock.setClockMode(false);
  Clock.setHour(settime("Hour", 24)); //The settime function has a default max value of 60, so we only have to declare it here
  Clock.setMinute(settime("Minute"));
  Clock.setSecond(settime("Second"));
  Clock.setDate(settime("Day", 31));
  Clock.setMonth(settime("Month", 12));
  Clock.setYear(settime("Year", -1, 2000));
  lcd.clear();
}

void loop() {
  DateTime now = myRTC.now();
  
  lcd.setCursor(0, 0);
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print(now.day());
  lcd.print("/");
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.year());
    //Future alarm code will go here

  delay(1000);
}
