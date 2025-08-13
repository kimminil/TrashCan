const int button = A1;
const int debounceDelay = 50;

int lastButtonReading = HIGH;
int buttonState = HIGH;
unsigned long lastDebounceTime = 0;


bool readButton(){
  int currentReading = digitalRead(button);
  if (currentReading != lastButtonReading) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentReading != buttonState) {
      buttonState = currentReading;
      if (buttonState == LOW) {
        return true;
      }
    }
  }  
  lastButtonReading = currentReading;
  return false;
}