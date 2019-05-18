// This method is called once, when
// the program is first ran.
void setup() {
	// Set a GPIO as an output. Pin 17 is connected
	// to the cathode of the left on board LED.
	pinMode(17, OUTPUT);
}

// This method is called after setup()
// and again when it finishes.
void loop() {
	// Sets the pin as high, thus making the cathode
	// high, so no current flows and no light is emitted.
	digitalWrite(17, HIGH);
	
	// Delays for 500 milliseconds.
	delay(500);

	// Sets the pin as low, thus making the cathode 
	// low, so current flows and light is emitted.
	digitalWrite(17, LOW);
	
	// Delays for 500 milliseconds.
	delay(500);
}
