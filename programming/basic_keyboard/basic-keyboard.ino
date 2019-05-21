// Include the keyboard library (for USB HID).
#include <Keyboard.h>

// List of row pins from up to down.
const int rowPins[] = {4, 5, 6, 9};
// List of column pins from left to right.
const int colPins[] = {1, 0, 3, 2, 8, 19, 20, 18, 14, 16, 10, 21};
// Number of row pins.
const int numRows = sizeof(rowPins) / sizeof(int);
// Number of column pins.
const int numCols = sizeof(colPins) / sizeof(int);

// The keyboard layout!
const char layout[numRows][numCols] = {
  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x'},
  {'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
};

// Keeping track of the state of the key.
bool keyStatus[numRows][numCols] = { { false } };

// Variables to keep the current row
// and column index.
int rowNum, colNum;

// This method is called once, when
// the program is first ran.
void setup() {
  // Setting all the rows as HIGH outputs.
  for (rowNum = 0; rowNum < numRows; rowNum++) {
    pinMode(rowPins[rowNum], OUTPUT);
    digitalWrite(rowPins[rowNum], HIGH);
  }
  
  // Setting all the columns as pulled-up inputs.
  for (colNum = 0; colNum < numCols; colNum++) {
    pinMode(colPins[colNum], INPUT_PULLUP);
  }
}

// This method is called after setup()
// and again when it finishes.
void loop() {
  // Iterate through all the rows.
  for (rowNum = 0; rowNum < numRows; rowNum++) {
    // For the selected row, set it to LOW.
    // This causes the voltage of the pins of
    // the pressed switches to drop, making the
    // column read LOW.
    digitalWrite(rowPins[rowNum], LOW);

    // Iterate through all the columns.
    for (colNum = 0; colNum < numCols; colNum++) {
      // Check if the pin is LOW.
      if (digitalRead(colPins[colNum]) == LOW) {
        // If the key is pressed we get here.
        if (!keyStatus[rowNum][colNum]) {
          // And if the key is newly pressed
          // we send the char from the layout
          // array over usb.
          Keyboard.press(layout[rowNum][colNum]);
          // And we mark the key as pressed.
          keyStatus[rowNum][colNum] = true;
        }
      }
      else {
        // If the key is not pressed we get here.
        if (keyStatus[rowNum][colNum]) {
          // And if the key is newly released we
          // release that key from the USB.
          Keyboard.release(layout[rowNum][colNum]);
          // And mark the key as released.
          keyStatus[rowNum][colNum] = 0;
        }
      }
    }

    // Finally we reset the row as HIGH and
    // continue to the next row.
    digitalWrite(rowPins[rowNum], HIGH);
  }
  // When that is done, it does it again, forever.
  delay(3);
}
