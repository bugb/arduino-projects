// ============================================================================
// LED Animation Controller
// ============================================================================

// Configuration Constants
const int FIRST_LED_PIN = 2;
const int LAST_LED_PIN = 12;
const int TOTAL_LEDS = LAST_LED_PIN - FIRST_LED_PIN + 1;
const int ANIMATION_DELAY = 100;  // milliseconds between LED updates

// ============================================================================
// Setup
// ============================================================================
void setup() {
  initializeLEDs();
}

void loop() {
  runChaserAnimation();
}

// ============================================================================
// LED Initialization
// ============================================================================
void initializeLEDs() {
  for (int pin = FIRST_LED_PIN; pin <= LAST_LED_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);  // Ensure all LEDs start off
  }
}

// ============================================================================
// Animation Functions
// ============================================================================

/**
 * Creates a 3-LED chaser effect that moves across all LEDs
 */
void runChaserAnimation() {
  const int CHASER_LENGTH = 3;
  
  // Move the 3-LED window across the LED strip
  for (int position = 0; position <= TOTAL_LEDS - CHASER_LENGTH; position++) {
    // Turn on current window of LEDs
    for (int offset = 0; offset < CHASER_LENGTH; offset++) {
      digitalWrite(FIRST_LED_PIN + position + offset, HIGH);
    }
    
    delay(ANIMATION_DELAY);
    
    // Turn off current window of LEDs
    for (int offset = 0; offset < CHASER_LENGTH; offset++) {
      digitalWrite(FIRST_LED_PIN + position + offset, LOW);
    }
  }
}

/**
 * Alternative chaser with wrapping (uncomment to use)
 */
void runWrappingChaser() {
  const int CHASER_LENGTH = 3;
  int ledStates[TOTAL_LEDS] = {0};  // Track LED states
  
  for (int position = 0; position < TOTAL_LEDS; position++) {
    // Clear all LEDs
    setAllLEDs(LOW);
    
    // Turn on LEDs in chaser pattern (with wrapping)
    for (int offset = 0; offset < CHASER_LENGTH; offset++) {
      int ledIndex = (position + offset) % TOTAL_LEDS;
      digitalWrite(FIRST_LED_PIN + ledIndex, HIGH);
    }
    
    delay(ANIMATION_DELAY);
  }
}

/**
 * Single LED bouncing back and forth
 */
void runBouncingLED() {
  // Forward direction
  for (int pin = FIRST_LED_PIN; pin <= LAST_LED_PIN; pin++) {
    digitalWrite(pin, HIGH);
    delay(ANIMATION_DELAY);
    digitalWrite(pin, LOW);
  }
  
  // Reverse direction
  for (int pin = LAST_LED_PIN; pin >= FIRST_LED_PIN; pin--) {
    digitalWrite(pin, HIGH);
    delay(ANIMATION_DELAY);
    digitalWrite(pin, LOW);
  }
}

/**
 * Fill up LEDs then drain them
 */
void runFillAndDrain() {
  // Fill up
  for (int pin = FIRST_LED_PIN; pin <= LAST_LED_PIN; pin++) {
    digitalWrite(pin, HIGH);
    delay(ANIMATION_DELAY);
  }
  
  // Drain
  for (int pin = LAST_LED_PIN; pin >= FIRST_LED_PIN; pin--) {
    digitalWrite(pin, LOW);
    delay(ANIMATION_DELAY);
  }
}

// ============================================================================
// Utility Functions
// ============================================================================

/**
 * Set all LEDs to the same state
 * @param state HIGH or LOW
 */
void setAllLEDs(int state) {
  for (int pin = FIRST_LED_PIN; pin <= LAST_LED_PIN; pin++) {
    digitalWrite(pin, state);
  }
}

/**
 * Turn off all LEDs
 */
void clearAllLEDs() {
  setAllLEDs(LOW);
}
