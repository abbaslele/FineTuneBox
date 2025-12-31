#define CLK_PIN 2  //  Clock+ Pin - Yellow
#define DATA_PIN 3  //  Data+ Pin - White
#define SSI_BITS 18  // 18bit resolution


#define RESOLUTION 262144

void setup() {
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(DATA_PIN, INPUT);
  digitalWrite(CLK_PIN, HIGH);  //  Clock Initialization
  Serial.begin(19200);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    int Command = command.toInt();
    if (Command == 1) {
      Serial.println("Encoder is ready!");
      digitalWrite(4, HIGH);
      delay(300);
      digitalWrite(4, LOW);
    }
    else if (Command == 0) {
      unsigned long grayCode = readSSI();  //  readSSI Function Call
      unsigned long position = grayToBinary(grayCode);  // grayToBinary Function Call
      float angle = (float(position) / RESOLUTION) * 360.0; // Binary to Angle Scale
    //Serial.print("Gray Code: ");
    //Serial.print(grayCode, BIN);
    //Serial.print(" | Position: ");
    //Serial.print(position);
    //Serial.print(" | Angle: ");
      Serial.println(angle, 3);
    //delay();
    }
  }
}

// Receive Gray from Encoder:
unsigned long readSSI() {
  unsigned long value = 0;
  for (int i = 0; i < SSI_BITS; i++) {
    digitalWrite(CLK_PIN, LOW);
    delayMicroseconds(1);  //  Clock LOW Time
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(1);  // Clock HIGH Time
    value <<= 1;  //  bit Shift
    if (digitalRead(DATA_PIN) == HIGH) {
      value |= 1;
    }
  }
  return value;
}

// Gray to Binary Function:
unsigned long grayToBinary(unsigned long gray) {
  unsigned long binary = gray;
  while (gray >>= 1) {
    binary ^= gray;
  }
  return binary;
}