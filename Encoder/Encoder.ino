#define CLK_PIN 2  //  Clock+ Pin - Yellow
#define DATA_PIN 3  //  Data+ Pin - White
#define S1




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