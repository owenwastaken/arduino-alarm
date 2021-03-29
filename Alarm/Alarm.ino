#include <LiquidCrystal.h>

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

int scn, mte, hr;

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  lcd.begin(16, 2);
  hr = settime("Hour", 24); //The settime function has a default max value of 60, so we only have to declare it here
  mte = settime("Minute");
  scn = settime("Second");
  lcd.clear();
}

void loop() {
  scn = scn + 1;
  //The following IF chain checks to see if any value has reached its limit
  if(scn == 60)
  {
    scn = 0;
    mte = mte + 1;
    if(mte == 60)
    {
      mte = 0;
      hr = hr + 1;
      if(hr == 24)
      {
        hr = 0;
      }
    }
  }

  //Future alarm code will go here
  
  lcd.setCursor(0, 0);
  lcd.print(hr);
  lcd.print(":");
  lcd.print(mte);
  lcd.print(":");
  lcd.print(scn);
  lcd.print("     ");
  delay(1000);
}


int settime(String varname, int maxnumber = 60)
{
  int var;
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
          var = 0;
        }
        else
        {
          var = var + 1;
        }
      }
      if(downstate == LOW)
      {
        if(var == 0)
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
