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

//Servo 2 [60-160]
//Servo 3 [60-150]

ServoData axServoData[ ] = { {3,180}, {5,110}, {6,50}, {9,110}};
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

  // Go to stand-by position
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

  // Move into max horizontal height position 
  for (pos = 0; pos <= 90; pos += 1) 
  {  
    axServos[1].write(axServoData[1].m_iStartOffset+pos);
    
    delay(100);
  }

  // Move to grab position
  for (pos = 90; pos >= 28; pos -= 1) 
  {
    axServos[2].write(pos);
    axServos[1].write(90+pos);

    // Minimum delay to minimize whiplash and stop hitting the table.
    delay(200);
  }

  // Grab object
  delay(1000);

  for (pos = 100; pos >= 20; pos -= 1) 
  {
    axServos[0].write(pos);
    
    delay(100);
  }

  // Raise to max horizontal height
  for (pos = 28; pos <= 90; pos += 1) 
  {  
    axServos[2].write(pos);
    axServos[1].write(90+pos);
    
    delay(100);
  }

  // Drop the mic
  delay(500);
  axServos[0].write(0);
  delay(500);

  // Return to start / low effort position
  for (pos = 90; pos <= 0; pos -= 1) 
  {  
    axServos[1].write(90+pos);
    
    delay(20);
  }
}
