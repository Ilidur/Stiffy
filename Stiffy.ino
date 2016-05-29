#include <Servo.h>

class ServoData
{
  public:
  
  int m_iPortNumber;
  int m_iStartOffset;

  ServoData(int iPortNumber, int iStartOffset = 90 )
  {
    m_iPortNumber = iPortNumber;
    m_iStartOffset = iStartOffset;
  }
  
};

ServoData axServoData[ ] = { 3, {5,100}, {6,0}, {9,110}, 10, 11 };
int iButtonPin = 2;

const int servoCount = 4;
Servo axServos[5];
int pos = 0;    // variable to store the servo position

void setup()
{
  for (int i =0; i < servoCount; i++)
  {
    axServos[i].attach(axServoData[i].m_iPortNumber);
  }

  pinMode(iButtonPin, INPUT);
}

void loop()
{

   for (int i =0; i <servoCount ; i++)
  {
    axServos[i].write(axServoData[i].m_iStartOffset);
  }  
  
  //Wait for button to be pressed
  int iButtonState;
  do 
  {
    iButtonState = digitalRead(iButtonPin);
  } 
  while (iButtonState == LOW );

  for (pos = 0; pos <= 90; pos += 1) 
  {  
    axServos[1].write(axServoData[1].m_iStartOffset+pos);
    
    delay(50);
  }

  for (pos = 90; pos >= 25; pos -= 1) 
  {
    axServos[0].write(pos);
    axServos[1].write(90+pos);
    
    delay(50);
  }

  for (pos = 0; pos <= 90; pos += 1) 
  {
    axServos[2].write(pos);
    
    delay(20);
  }
  
  for (pos = 25; pos <= 90; pos += 1) 
  {  
    axServos[0].write(pos);
    axServos[1].write(90+pos);
    
    delay(50);
  }

  for (pos = 90; pos >= 0; pos -= 1) 
  {
    axServos[2].write(pos);
    
    delay(20);
  }

    for (pos = 90; pos <= 0; pos -= 1) 
  {  
    axServos[1].write(90+pos);
    
    delay(50);
  }
}

