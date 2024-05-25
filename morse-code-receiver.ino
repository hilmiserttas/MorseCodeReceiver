#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = D5;
const int ledPin = D0;

const long dotTime = 300;       
const long dashTime = 900;      
const long letterSpaceTime = 900; 
const long wordSpaceTime = 2100; 
const float TOLERANCE = 0.10;   

unsigned long signalStartTime = 0;
unsigned long signalEndTime = 0;
unsigned long lastSignalEndTime = 0;

bool signalStarted = false;
String currentMorse = "";
String decodedMessage = "";

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Morse Code Receiver");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.println("READY TO RECEIVE :)");
}

void loop() {
  int sensorState = digitalRead(sensorPin);

  if (sensorState == LOW) {
    if (!signalStarted) {
      signalStartTime = millis();
      signalStarted = true;
      digitalWrite(ledPin, HIGH);
    }
  } else {
    if (signalStarted) {
      signalEndTime = millis();
      unsigned long duration = signalEndTime - signalStartTime;
      signalStarted = false;
      digitalWrite(ledPin, LOW);

      if (checkDurationMatch(duration, dotTime, TOLERANCE)) {
        currentMorse += ".";
      } else if (checkDurationMatch(duration, dashTime, TOLERANCE)) {
        currentMorse += "-";
      } else {
        Serial.print("Duration out of range: ");
        Serial.println(duration);
      }

      lastSignalEndTime = millis();
    }
  }

  unsigned long currentTime = millis();
  unsigned long spaceDuration = currentTime - lastSignalEndTime;

  if (!signalStarted && spaceDuration >= letterSpaceTime * (1 - TOLERANCE) && currentMorse != "") {
    decodeMorse();
    currentMorse = ""; 
    lastSignalEndTime = currentTime;
    if (spaceDuration >= wordSpaceTime * (1 - TOLERANCE)) {
      decodedMessage += " ";
    }
  }

  lcd.setCursor(0, 1);
  lcd.print(decodedMessage);
}

void decodeMorse() {
    const char* MorseTable[] = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        /*SPACE*/ NULL, /*!*/ "-.-.--", /*"*/ ".-..-.", /*#*/ NULL, /*$*/ "...-..-", /*%*/ NULL, /*&*/ ".-...", /*'*/ ".----.",
        /*(*/ "-.--.", /*)*/ "-.--.-", /***/ NULL, /*+*/ ".-.-.", /*,*/ "--..--", /*-*/ "-....-", /*.*/ ".-.-.-", /*/*/ "-..-.",
        /*0*/ "-----", /*1*/ ".----", /*2*/ "..---", /*3*/ "...--", /*4*/ "....-", /*5*/ ".....", /*6*/ "-....", /*7*/ "--...",
        /*8*/ "---..", /*9*/ "----.", /*:*/ "---...", /*;*/ "-.-.-.", /*<*/ NULL, /*=*/ "-...-", /*>*/ NULL, /*?*/ "..--..",
        /*@*/ ".--.-.", /*A*/ ".-", /*B*/ "-...", /*C*/ "-.-.", /*D*/ "-..", /*E*/ ".", /*F*/ "..-.", /*G*/ "--.",
        /*H*/ "....", /*I*/ "..", /*J*/ ".---", /*K*/ "-.-", /*L*/ ".-..", /*M*/ "--", /*N*/ "-.", /*O*/ "---",
        /*P*/ ".--.", /*Q*/ "--.-", /*R*/ ".-.", /*S*/ "...", /*T*/ "-", /*U*/ "..-", /*V*/ "...-",/*W*/ ".--",
        /*X*/ "-..-", /*Y*/ "-.--", /*Z*/ "--.."
    };

    for (int i = 0; i < sizeof(MorseTable) / sizeof(MorseTable[0]); i++) {
        if (MorseTable[i] != NULL && currentMorse == MorseTable[i]) {
            if (i >= 'A' && i <= 'Z') {
                decodedMessage += (char)i;
            } else if (i >= '0' && i <= '9') {
                decodedMessage += (char)i;
            } else {
                switch (i) {
                    case '!': decodedMessage += '!'; break;
                    case '"': decodedMessage += '"'; break;
                    case '$': decodedMessage += '$'; break;
                    case '&': decodedMessage += '&'; break;
                    case '\'': decodedMessage += '\''; break;
                    case '(': decodedMessage += '('; break;
                    case ')': decodedMessage += ')'; break;
                    case '+': decodedMessage += '+'; break;
                    case ',': decodedMessage += ','; break;
                    case '-': decodedMessage += '-'; break;
                    case '.': decodedMessage += '.'; break;
                    case '/': decodedMessage += '/'; break;
                    case ':': decodedMessage += ':'; break;
                    case ';': decodedMessage += ';'; break;
                    case '=': decodedMessage += '='; break;
                    case '?': decodedMessage += '?'; break;
                    case '@': decodedMessage += '@'; break;
                }
            }
            return;
        }
    }
    decodedMessage += "?";
}


bool checkDurationMatch(unsigned long duration, long targetDuration, float tolerance) {
  long lowerBound = targetDuration * (1.0 - tolerance);
  long upperBound = targetDuration * (1.0 + tolerance);
  return duration >= lowerBound && duration <= upperBound;
}
