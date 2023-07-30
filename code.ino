// 4x4 Matrix


byte patterns[][4] = {
    // Counter
  {B0000, B0000, B0000, B0000}, // 
  {B1000, B0000, B0000, B0000}, //
  {B1100, B0000, B0000, B0000}, //
  {B1110, B0000, B0000, B0000}, // 
  {B1111, B0000, B0000, B0000}, // 
  {B1111, B1000, B0000, B0000}, // 
  {B1111, B1100, B0000, B0000}, // 
  {B1111, B1110, B0000, B0000}, // 
  {B1111, B1111, B0000, B0000}, // 
  {B1111, B1111, B1000, B0000}, // 
  {B1111, B1111, B1100, B0000}, // 
  {B1111, B1111, B1110, B0000}, // 
  {B1111, B1111, B1111, B0000}, // 
  {B1111, B1111, B1111, B1000}, // 
  {B1111, B1111, B1111, B1100}, // 
  {B1111, B1111, B1111, B1110}, // 
  {B1111, B1111, B1111, B1111}, // 

  {B0000, B0000, B0000, B0000}, // All LEDs off
  {B0110, B1001, B1111, B1001}, // A
  {B1110, B1001, B1001, B1110}, // D
  {B1001, B0110, B0110, B1001}, // X
  {B1111, B0100, B0010, B1111}, // Z
  {B1111, B1001, B1001, B1111}, // Square
  {B0000, B0110, B0110, B0000}, // Tiny Square

  {B1000, B0100, B0010, B0001}, // 
  {B0001, B0010, B0100, B1000}, // 
  {B1000, B0100, B0010, B0001}, // 
  {B0001, B0010, B0100, B1000}, // 




  {B1000, B0100, B0010, B0001}, // LEDs moving from top-left to bottom-right
  {B1111, B0000, B0000, B0000}, // LEDs in the first row on
  {B0000, B1111, B0000, B0000}, // LEDs in the second row on
  {B0000, B0000, B1111, B0000}, // LEDs in the third row on
  {B0000, B0000, B0000, B1111}, // LEDs in the fourth row on
  {B1000, B1000, B1000, B1000}, // LEDs in the first column on
  {B0100, B0100, B0100, B0100}, // LEDs in the second column on
  {B0010, B0010, B0010, B0010}, // LEDs in the third column on
  {B0001, B0001, B0001, B0001}, // LEDs in the fourth column on
  {B1111, B1111, B1111, B1111}, // All LEDs on
  {B0001, B0010, B0100, B1000}, // LEDs moving from bottom-left to top-right
  {B1000, B0100, B1000, B0100}, // LEDs blinking diagonally
  {B0001, B1000, B0001, B1000}, // LEDs blinking alternately vertically
  {B1111, B0110, B0110, B1111}, // Hourglass pattern
  {B0010, B0110, B1110, B0110}, // Rotating pattern
  {B0101, B1010, B0101, B1010}, // Cross pattern
  {B0000, B0101, B1010, B0000}, // Diamond pattern
  {B0101, B0101, B0101, B0101}, // Horizontal line pattern
  {B1111, B1111, B1111, B1111}, // All LEDs on (alternate representation)
  {B1001, B1001, B1001, B1001}, // Diagonal line pattern (bottom-left to top-right)
  {B0110, B0110, B0110, B0110}, // Vertical line pattern
  {B1010, B1010, B1010, B1010}, // Diagonal line pattern (top-left to bottom-right)
  {B1111, B1001, B0110, B0011}, // Rotating checkerboard pattern
  {B1110, B0001, B0011, B1100}, // Rotating cross pattern
};

uint8_t colPins[4] = {2, 3, 4, 5}; // specifies column pins, directly connected to Arduino

#define SER_PIN 10
#define SCK_PIN 11
#define RCK_PIN 12

int currentPattern = 0;

void setup() {
  // Turn everything to low
  for (int i = 0; i < 4; i++) {
    pinMode(colPins[i], OUTPUT);
  }
  pinMode(SER_PIN, OUTPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(RCK_PIN, OUTPUT);
  Serial.begin(9600);
}

void write595(byte data) {
  digitalWrite(RCK_PIN, LOW);
  shiftOut(SER_PIN, SCK_PIN, LSBFIRST, data);
  digitalWrite(RCK_PIN, HIGH);
}

void displayPattern(byte* pattern) {
  for (int repeat = 0; repeat < 100; repeat++) { // Repeat the pattern 5 times
    for (int row = 0; row < 4; row++) {
      for (int k = 0; k < 4; k++)
        digitalWrite(colPins[k], HIGH); // Cleanup cols
      write595(1 << (3 - row)); // prepare to write the row
      for (int col = 0; col < 4; col++)
        digitalWrite(colPins[col], pattern[row] & (1 << (3 - col)) ? LOW : HIGH);
      delay(1);
      write595(0);
    }
  }
}

void loop() {
  // Display the current pattern
  displayPattern(patterns[currentPattern]);

  // Move to the next pattern
  currentPattern++;
  if (currentPattern >= sizeof(patterns) / sizeof(patterns[0])) {
    currentPattern = 0;
  }

  // Wait for some time before displaying the next pattern
  delay(1);
}
