

#include <BluetoothSerial.h>
#include <driver/ledc.h>


BluetoothSerial SerialBT;

// Motor Driver Pins
#define motor1Pin1   16
#define motor1Pin2   17
#define motor2Pin1   18
#define motor2Pin2   19

#define enA   25
#define enB   26

const int pwmFrequency = 5000;
const int pwmResolution = 8;
const int pwmChannelA = 0;
const int pwmChannelB = 1;

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // Setup PWM channels
  ledcSetup(pwmChannelA, pwmFrequency, pwmResolution);
  ledcSetup(pwmChannelB, pwmFrequency, pwmResolution);

  // Attach PWM channels to GPIO pins
  ledcAttachPin(enA, pwmChannelA);
  ledcAttachPin(enB, pwmChannelB);

  Serial.begin(115200);
  SerialBT.begin("ESP32_Soccer_Robot"); // Name of your ESP32 Bluetooth
  Serial.println("The device started, now you can pair it with Bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.print("Command received: ");
    Serial.println(command);
    
    int motorSpeed = 255;
    int motorSpeed2 = 0;
    int motorSpeed3 = 180;

    if (command == 'f') { // Move Forward
      ledcWrite(pwmChannelA, motorSpeed);
      ledcWrite(pwmChannelB, motorSpeed);
      
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
     
    } else if (command == 'b') { // Move Backward
      ledcWrite(pwmChannelA, motorSpeed);
      ledcWrite(pwmChannelB, motorSpeed);
      
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
     
    } else if (command == 'r') { // Turn Right
      ledcWrite(pwmChannelA, motorSpeed);
      ledcWrite(pwmChannelB, motorSpeed);
      
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    
    } else if (command == 'l') { // Turn Left
      ledcWrite(pwmChannelA, motorSpeed);
      ledcWrite(pwmChannelB, motorSpeed);
      
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
     
    } else if (command == 's' || command == '0') { // Stop
      ledcWrite(pwmChannelA, 0);
      ledcWrite(pwmChannelB, 0);
      
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      
    } else if (command == 'g') { // Custom command 'g'
      ledcWrite(pwmChannelA, motorSpeed3);
      ledcWrite(pwmChannelB, motorSpeed);
     
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      
    } else if (command == 'i') { // Custom command 'i'
      ledcWrite(pwmChannelA, motorSpeed);
      ledcWrite(pwmChannelB, motorSpeed3);
    
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
     
    } else if (command == 'h') { // Custom command 'h'
      ledcWrite(pwmChannelA, motorSpeed3);
      ledcWrite(pwmChannelB, motorSpeed);

      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      
    } else if (command == 'j') { // Custom command 'j'
      ledcWrite(pwmChannelA, motorSpeed);
      ledcWrite(pwmChannelB, motorSpeed3);
    
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
     
    } else {
      ledcWrite(pwmChannelA, 0);
      ledcWrite(pwmChannelB, 0);
     
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
     
    }
  }
}
