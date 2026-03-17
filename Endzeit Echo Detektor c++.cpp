#include <Arduino.h>
#include <esp_random.h>
// LED Pins
const int PIN_LED_STATUS = 17;
const int PIN_LED_GEIGER = 32;
const int PIN_LED_ANOMALY = 33;
const int PIN_LED_ARTIFACT = 25;
// Buzzer Pin
const int PIN_BUZZER = 26;
// Mode Lever Pins
const int PIN_LEVER_MODE_OFF_0 = 27;
const int PIN_LEVER_MODE_GEIGER_1 = 14;
const int PIN_LEVER_MODE_ANOMALY_2 = 12;
const int PIN_LEVER_MODE_ARTIFACT_3 = 13;
// Sensitivity Lever Pins
const int PIN_LEVER_SENSITIVITY_LOW_0 = 15;
const int PIN_LEVER_SENSITIVITY_MEDIUM_1 = 5;
const int PIN_LEVER_SENSITIVITY_HIGH_2 = 18;
const int PIN_LEVER_SENSITIVITY_ULTRA_3 = 19;

int modeState = 0;
int modeSens = 0;


void abfrageSensitivity() {
	if (digitalRead(PIN_LEVER_SENSITIVITY_LOW_0) == LOW)
	{
		modeSens = 0;
	}
	else if (digitalRead(PIN_LEVER_SENSITIVITY_MEDIUM_1) == LOW)
	{
		modeSens = 1;
	}
	else if (digitalRead(PIN_LEVER_SENSITIVITY_HIGH_2) == LOW)
	{
		modeSens = 2;
	}
	else if (digitalRead(PIN_LEVER_SENSITIVITY_ULTRA_3) == LOW)
	{
		modeSens = 3;
	}
	else (modeSens = 0); // Default to low sensitivity if no lever is activated
}

int randomClickGeiger = 0;
int delayTimeGeiger = 0;
void geigerClick(int modeSens) {
	// Simulate Geiger click sound based on sensitivity
	switch (modeSens) {
	case 0:
		randomClickGeiger = random(500);
		delayTimeGeiger = 1000; // Low sensitivity - slower clicks
		break;
	case 1:
		randomClickGeiger = random(250);
		delayTimeGeiger = 300; // Medium sensitivity - moderate clicks
		break;
	case 2:
		randomClickGeiger = random(125);
		delayTimeGeiger = 150; // High sensitivity - faster clicks
		break;
	case 3:
		randomClickGeiger = random(45);
		delayTimeGeiger = 50; // Ultra sensitivity - very fast clicks
		break;
	default:
		randomClickGeiger = random(500);
		delayTimeGeiger = 1000; // Default to low sensitivity
		break;
	}
	tone(PIN_BUZZER, 4000, 5);
	delay(delayTimeGeiger-randomClickGeiger); // Delay between clicks based on sensitivity
}
int delayTimeAnomaly = 0;

void anomalyClick(int modeSens) {
	// Simulate Geiger click sound based on sensitivity
	switch (modeSens) {
	case 0:
		delayTimeAnomaly = 2000; // Low sensitivity - slower clicks
		break;
	case 1:
		delayTimeAnomaly = 1000; // Medium sensitivity - moderate clicks
		break;
	case 2:
		delayTimeAnomaly = 500; // High sensitivity - faster clicks
		break;
	case 3:
		delayTimeAnomaly = 250; // Ultra sensitivity - very fast clicks
		break;
	default:
		delayTimeAnomaly = 2000; // Default to low sensitivity
		break;
	}
	digitalWrite(PIN_LED_ANOMALY, HIGH);
	tone(PIN_BUZZER, 1200, 6);
	tone(PIN_BUZZER, 2200, 7);
	tone(PIN_BUZZER, 2800, 8);
	tone(PIN_BUZZER, 3400, 8);
	tone(PIN_BUZZER, 3800, 7);
	tone(PIN_BUZZER, 3200, 7);
	tone(PIN_BUZZER, 2600, 8);
	tone(PIN_BUZZER, 2000, 7);
	tone(PIN_BUZZER, 3000, 6);
	tone(PIN_BUZZER, 2400, 6);
	delay(10);
	digitalWrite(PIN_LED_ANOMALY, LOW);
	delay(delayTimeAnomaly); // Delay between clicks based on sensitivity
}
int delayTimeArtifact = 0;

void artifactClick(int modeSens) {
	// Simulate Geiger click sound based on sensitivity
	switch (modeSens) {
	case 0:
		delayTimeArtifact = 2000; // Low sensitivity - slower clicks
		break;
	case 1:
		delayTimeArtifact = 1000; // Medium sensitivity - moderate clicks
		break;
	case 2:
		delayTimeArtifact = 500; // High sensitivity - faster clicks
		break;
	case 3:
		delayTimeArtifact = 250; // Ultra sensitivity - very fast clicks
		break;
	default:
		delayTimeArtifact = 2000; // Default to low sensitivity
		break;
	}
	digitalWrite(PIN_LED_ARTIFACT, HIGH);
	tone(PIN_BUZZER, 3000, 100);
	delay(10);
	digitalWrite(PIN_LED_ARTIFACT, LOW);
	delay(delayTimeArtifact); // Delay between clicks based on sensitivity
}


void abfrageModus(int modeState) {
	// Handle mode selection
	switch (modeState) {
	case 0:
		// OFF mode
		digitalWrite(PIN_LED_GEIGER, LOW);
		digitalWrite(PIN_LED_ANOMALY, LOW);
		digitalWrite(PIN_LED_ARTIFACT, LOW);
		digitalWrite(PIN_BUZZER, LOW);
		digitalWrite(PIN_LED_STATUS, LOW);
		break;
	case 1:
		// GEIGER mode
		digitalWrite(PIN_LED_GEIGER, HIGH);
		digitalWrite(PIN_LED_ANOMALY, LOW);
		digitalWrite(PIN_LED_ARTIFACT, LOW);
		digitalWrite(PIN_LED_STATUS, HIGH);
		break;
	case 2:
		// ANOMALY mode
		digitalWrite(PIN_LED_GEIGER, LOW);
		digitalWrite(PIN_LED_ARTIFACT, LOW);
		digitalWrite(PIN_LED_STATUS, HIGH);
		break;
	case 3:
		// ARTIFACT mode
		digitalWrite(PIN_LED_GEIGER, LOW);
		digitalWrite(PIN_LED_ANOMALY, LOW);
		digitalWrite(PIN_LED_STATUS, HIGH);
		break;
	default:
		// Invalid state
		break;
	}
}






void setup() {
	// put your setup code here, to run once:
	pinMode(PIN_LED_STATUS, OUTPUT);
	pinMode(PIN_LED_GEIGER, OUTPUT);
	pinMode(PIN_LED_ANOMALY, OUTPUT);
	pinMode(PIN_LED_ARTIFACT, OUTPUT);
	pinMode(PIN_LEVER_MODE_OFF_0, INPUT_PULLUP); //INPUT_PULLUP for lever inputs (reverse logic) constantly HIGH when not activated, LOW when activated
	pinMode(PIN_LEVER_MODE_GEIGER_1, INPUT_PULLUP);
	pinMode(PIN_LEVER_MODE_ANOMALY_2, INPUT_PULLUP);
	pinMode(PIN_LEVER_MODE_ARTIFACT_3, INPUT_PULLUP);
	pinMode(PIN_LEVER_SENSITIVITY_LOW_0, INPUT_PULLUP);
	pinMode(PIN_LEVER_SENSITIVITY_MEDIUM_1, INPUT_PULLUP);
	pinMode(PIN_LEVER_SENSITIVITY_HIGH_2, INPUT_PULLUP);
	pinMode(PIN_LEVER_SENSITIVITY_ULTRA_3, INPUT_PULLUP);
	pinMode(PIN_BUZZER, OUTPUT);
}


void loop() {
	// put your main code here, to run repeatedly:
	if (digitalRead(PIN_LEVER_MODE_OFF_0) == LOW)
	{
		int modeState = 0;
		abfrageModus(modeState);
	}
	else if (digitalRead(PIN_LEVER_MODE_GEIGER_1) == LOW)
	{
		int modeState = 1;
		abfrageModus(modeState);
		abfrageSensitivity();
		geigerClick(modeSens);
	}
	else if (digitalRead(PIN_LEVER_MODE_ANOMALY_2) == LOW)
	{
		int modeState = 2;
		abfrageModus(modeState);
		abfrageSensitivity();
		anomalyClick(modeSens);
	}
	else if (digitalRead(PIN_LEVER_MODE_ARTIFACT_3) == LOW)
	{
		int modeState = 3;
		abfrageModus(modeState);
		abfrageSensitivity();
		artifactClick(modeSens);
	}
}
