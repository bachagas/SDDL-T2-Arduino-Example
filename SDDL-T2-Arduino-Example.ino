// Pin definitions:
const int LED_PIN = 12;

// Commands constants definitions:
const int  MAX_COMMAND_LENGTH  = 128;  //the maximum possible length of a command
const char EMPTY_COMMAND[MAX_COMMAND_LENGTH + 1] = "                                                                                                                                ";
const char COMMAND_MARK        = '#';  //indicates a command to be processed
const char TOGGLE_LED          = '1';  //toggles the LED on/off

// Program control variables:
boolean led = false;
long seconds = 0, miliseconds = 0;
char command[MAX_COMMAND_LENGTH + 1];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Send ""#1"" to turn the LED on/off");
  Serial.println("Note: commands must start with ""#"" and finish with LF + CR");
  Serial.println(seconds);
}

void loop() {
  // print seconds:
  if (millis() > miliseconds + 1000) {
    miliseconds = millis();
    //Serial.println(++seconds);
  }

  //read input:
  if (readSerial(command) > 0) {
    Serial.print("Received: ");
    Serial.println(command);
    
    //if a command is received process it:
    if (command[0] == COMMAND_MARK) {
      if (processCommand(&command[1])) Serial.println("OK");
      else Serial.println("?");
    }
  }
  
  delay(100);
}

int readSerial(char * buf) {
  char c;
  int cont = 0;
  //clean command buffer
  strncpy(buf, EMPTY_COMMAND, MAX_COMMAND_LENGTH);
  //read serial port
  while(Serial.available() > 0){
    c = Serial.read();
    if (c == '\n') {  //command must end with \n
      buf[cont] = '\0';
      break;
    }
    buf[cont]= (char) c;
    cont++;
  }
  return cont;
}

// Parse and process a command.
// Returns true if command is valid (known) and process it; false otherwise.
boolean processCommand(char * commandText) {  
  switch (commandText[0]) {
    //LED control
    case TOGGLE_LED:
      led = !led;
      digitalWrite(LED_PIN, (led ? HIGH : LOW)); 
      return true;
      break;
    default: 
      return false;
  }
}

