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
  // runFillTopToBottomThenBottomToTop();
  // delay(500);  // Brief pause between animations

  //// Uncomment to test other animations:
  runLayeredFill();
  delay(500);
  // runFillThenDrainReverse();
  // delay(500);

  // runFillAndDrain();
  // delay(500);

  // runBouncingLED();
  // delay(500);

  // runChaserAnimation();
  // delay(500);

  // runWrappingChaser();
  // delay(500);
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

// Fill like liquid: bottom->top (fill up), then top->bottom (drain down)
void runFillTopToBottomThenBottomToTop() {
  // Fill UP from bottom to top (reverse order through array)
  for (int i = NUM_PINS - 1; i >= 0; --i) {
    digitalWrite(pins[i], HIGH);    // turn this LED on (and leave previous ones on)
    delay(ANIMATION_DELAY);
  }

  delay(ANIMATION_DELAY); // hold full for a moment

  // Drain DOWN from top to bottom (forward order through array)
  for (int i = 0; i < NUM_PINS; ++i) {
    digitalWrite(pins[i], LOW);    // turn this LED off (draining from top)
    delay(ANIMATION_DELAY);
  }

  delay(300); // pause before next cycle
}

// Layered liquid fill - fills bottom-to-top, drains top-to-bottom, then fills top-to-bottom
void runLayeredFill() {
  // Define layers - each array contains the pin numbers that light up together
  const int layer1[] = {4, 2, 5};      // bottom layer
  const int layer2[] = {3, 6};         // second layer
  const int layer3[] = {8, 10};        // third layer
  const int layer4[] = {9};            // top layer
  
  const int layer1_size = 3;
  const int layer2_size = 2;
  const int layer3_size = 2;
  const int layer4_size = 1;
  
  // Fill UP (bottom to top) - turn on each layer
  for (int i = 0; i < layer1_size; i++) {
    digitalWrite(layer1[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer2_size; i++) {
    digitalWrite(layer2[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer3_size; i++) {
    digitalWrite(layer3[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer4_size; i++) {
    digitalWrite(layer4[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  delay(ANIMATION_DELAY * 2); // hold full
  
  // Drain DOWN (top to bottom) - turn off each layer in reverse
  for (int i = 0; i < layer4_size; i++) {
    digitalWrite(layer4[i], LOW);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer3_size; i++) {
    digitalWrite(layer3[i], LOW);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer2_size; i++) {
    digitalWrite(layer2[i], LOW);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer1_size; i++) {
    digitalWrite(layer1[i], LOW);
  }
  delay(ANIMATION_DELAY * 3);
  
  delay(ANIMATION_DELAY * 2); // pause before reverse
  
  // Fill DOWN (top to bottom) - turn on each layer from top
  for (int i = 0; i < layer4_size; i++) {
    digitalWrite(layer4[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer3_size; i++) {
    digitalWrite(layer3[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer2_size; i++) {
    digitalWrite(layer2[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  for (int i = 0; i < layer1_size; i++) {
    digitalWrite(layer1[i], HIGH);
  }
  delay(ANIMATION_DELAY * 3);
  
  delay(ANIMATION_DELAY * 2); // hold full
  
  // Clear all for next cycle
  clearAllLEDs();
}

// Fill top->bottom, then drain bottom->top (turn off in reverse)
void runFillThenDrainReverse() {
  // Fill top -> bottom
  for (int i = 0; i < NUM_PINS; ++i) {
    digitalWrite(pins[i], HIGH);
    delay(ANIMATION_DELAY);
  }

  delay(ANIMATION_DELAY);

  // Drain bottom -> top (turn off in reverse order)
  for (int i = NUM_PINS - 1; i >= 0; --i) {
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
