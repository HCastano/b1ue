void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // serial read section
  while (Serial.available()) // this will be skipped if no data present, leading to
                             // the code sitting in the delay function below
  {
    delay(30);  //delay to allow buffer to fill 
    if (Serial.available() > 0)
    {
      char c = Serial.read();  //gets one byte from serial buffer
      // readString += c; //makes the string readString
      Serial.println(c);
    }
  }

  delay(500);
  Serial.flush();
}
