// ============================================================================
// LED Animation Controller - array-based pin order
// ============================================================================

const int pins[] = {4, 2, 3, 8, 9, 10, 6, 5}; // update to physical order you want to use
const int NUM_PINS = sizeof(pins) / sizeof(pins[0]);

const int ANIMATION_DELAY = 100;  // milliseconds between LED updates

// ============================================================================
// Setup
// ============================================================================
void setup() {
  initializeLEDs();
}

void loop() {
  runFillAndDrain();
  delay(500);  // Brief pause between animations

  runBouncingLED();
  delay(500);

  runChaserAnimation();
  delay(500);

  runWrappingChaser();
  delay(500);
}

// ============================================================================
// LED Initialization
// ============================================================================
void initializeLEDs() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);  // Ensure all LEDs start off
  }
}

// ============================================================================
// Animation Functions (array-indexed)
// ============================================================================

/**
 * Creates a 3-LED chaser effect that moves across the pins[]
 */
void runChaserAnimation() {
  const int CHASER_LENGTH = 3;
  if (CHASER_LENGTH > NUM_PINS) return; // nothing to do

  // Move the CHASER_LENGTH window across the array
  for (int pos = 0; pos <= NUM_PINS - CHASER_LENGTH; pos++) {
    // Turn on current window of LEDs
    for (int off = 0; off < CHASER_LENGTH; off++) {
      digitalWrite(pins[pos + off], HIGH);
    }

    delay(ANIMATION_DELAY);

    // Turn off current window of LEDs
    for (int off = 0; off < CHASER_LENGTH; off++) {
      digitalWrite(pins[pos + off], LOW);
    }
  }
}

/**
 * Alternative chaser with wrapping (wraps around the pins[] array)
 */
void runWrappingChaser() {
  const int CHASER_LENGTH = 3;
  if (CHASER_LENGTH > NUM_PINS) return;

  for (int pos = 0; pos < NUM_PINS; pos++) {
    // Clear all LEDs first
    setAllLEDs(LOW);

    // Turn on LEDs in chaser pattern (with wrapping)
    for (int off = 0; off < CHASER_LENGTH; off++) {
      int idx = (pos + off) % NUM_PINS;
      digitalWrite(pins[idx], HIGH);
    }

    delay(ANIMATION_DELAY);
  }
}

/**
 * Single LED bouncing back and forth across the pins[] order
 */
void runBouncingLED() {
  // Forward direction
  for (int i = 0; i < NUM_PINS; i++) {
    digitalWrite(pins[i], HIGH);
    delay(ANIMATION_DELAY);
    digitalWrite(pins[i], LOW);
  }

  // Reverse direction
  for (int i = NUM_PINS - 1; i >= 0; i--) {
    digitalWrite(pins[i], HIGH);
    delay(ANIMATION_DELAY);
    digitalWrite(pins[i], LOW);
  }
}

/**
 * Fill up LEDs then drain them (uses pins[] order)
 */
void runFillAndDrain() {
  // Fill up
  for (int i = 0; i < NUM_PINS; i++) {
    digitalWrite(pins[i], HIGH);
    delay(ANIMATION_DELAY);
  }

  // Drain
  for (int i = NUM_PINS - 1; i >= 0; i--) {
    digitalWrite(pins[i], LOW);
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
  for (int i = 0; i < NUM_PINS; i++) {
    digitalWrite(pins[i], state);
  }
}

/**
 * Turn off all LEDs
 */
void clearAllLEDs() {
  setAllLEDs(LOW);
}
