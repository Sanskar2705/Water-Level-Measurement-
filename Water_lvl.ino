#define TRIGGER_PIN  D0 
#define ECHO_PIN     D2 

double total_depth_cm; 

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Enter the total depth of the water tank in centimeters:");
  while (!Serial.available()) {} 
  total_depth_cm = Serial.parseFloat(); 
}

void loop() {
  long duration;
  double distance_cm;
  double filled_cm;
  double percentage_filled;
  
  digitalWrite(TRIGGER_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH); 
  delayMicroseconds(10); 
  
  digitalWrite(TRIGGER_PIN, LOW); // Wait for the pulse to return
  
  duration = pulseIn(ECHO_PIN, HIGH);
  
  distance_cm = duration * 0.0343 / 2; 
  filled_cm = total_depth_cm - distance_cm;
  percentage_filled = 100 - ((distance_cm / total_depth_cm) * 100);


  if (percentage_filled > 100) {
    percentage_filled = 100;
  } else if (percentage_filled < 0) {
    percentage_filled = 0;
  }
  
  
  // Serial.print("How much is empty: ");
  // Serial.print(distance_cm);
  // Serial.println(" cm");

  Serial.print("How much is full: ");
  Serial.print(filled_cm);
  Serial.println(" cm");

  
  Serial.print("Percentage filled: ");
  Serial.print(percentage_filled);
  Serial.println("%");
  
  delay(2000);
}
