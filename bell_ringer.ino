//uses LCD example code library, credit to those authors

// include the library code
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define serv 3
/**********************************************************/
//initialize useful variables
int numDoorOpened = 0;
const int sensor = 5;
int state; // 0 close - 1 open wwitch

Servo s;


int tim = 300;  //the value of delay time
// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
void setup()
{
  Serial.begin(9600);
  pinMode(serv, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);
  
  s.attach(serv);

  lcd.init();  //initialize the lcd
}
/*********************************************************/
void loop() 
{
  state = digitalRead(sensor);
  //debugging purposes
  Serial.print("servo ");
  Serial.println(s.read());
  Serial.print("state ");
  Serial.println(state);
  Serial.print("People ");
  Serial.println(numDoorOpened);

  //initialize the arrays
  char array1[]=" Welcome!                ";  //the string to print on the LCD
  char array2[]=" Number of people entered: ";  //the string to print on the LCD

  
  if (state == HIGH){ //triggers when door is opened
    numDoorOpened++;

    //converts num door opened to something that can be displayed in the array on the LCD
    char b[4];
    String str = String(numDoorOpened);
    str.toCharArray(b,4);
    strcat(array2, b);
    Serial.println(array2);
    
    lcd.backlight();  //open the backlight 
    
    //writes to the servo to ring the bell
    s.write(180);
    delay(400);
    s.write(0);
    delay(400);
    s.write(90);
    delay(400);


    lcd.setCursor(15,0);  // set the cursor to column 15, line 0
    for (int positionCounter1 = 0; positionCounter1 < 26; positionCounter1++)
    {
      lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
      lcd.print(array1[positionCounter1]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 microseconds
    }
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
    lcd.setCursor(15,1);  // set the cursor to column 15, line 1
    for (int positionCounter = 0; positionCounter < 31; positionCounter++)
    {
      lcd.scrollDisplayLeft();  //Scrolls the contents of the display one space to the left.
      lcd.print(array2[positionCounter]);  // Print a message to the LCD.
      delay(tim);  //wait for 250 microseconds
    }
    
    lcd.clear();  //Clears the LCD screen and positions the cursor in the upper-left corner.
    delay(100);
    lcd.noBacklight();
    
    while(digitalRead(sensor) == HIGH){ //runs when door is closed to prevent continuous looping
      delay(1000);
      }
  } else {
    delay(1000);
    }
  
    delay(200);   
   
}
/************************************************************/
