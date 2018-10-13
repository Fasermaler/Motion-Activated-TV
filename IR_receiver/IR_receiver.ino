#include <IRremote.h>
// Receiver Pin Declaration
int RECV_PIN = 12;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // Start the Receiver
  irrecv.enableIRIn(); 
}

void HEXdecode(decode_results *results) {
  int count = results->rawlen;
  // Sorts out what sort of encoding is used
  if (results->decode_type == UNKNOWN) {
    Serial.print("Unknown: ");
  } else if (results->decode_type == NEC) {
    Serial.print("NEC: ");
  } else if (results->decode_type == SONY) {
    Serial.print("SONY: ");
  } else if (results->decode_type == RC5) {
    Serial.print("RC5: ");
  } else if (results->decode_type == RC6) {
    Serial.print("RC6: ");
  } else if (results->decode_type == PANASONIC) {
    Serial.print("PANASONIC: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  } else if (results->decode_type == LG) {
    Serial.print("LG: ");
  } else if (results->decode_type == JVC) {
    Serial.print("JVC: ");
  } else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("AIWA_RC_T501: ");
  } else if (results->decode_type == WHYNTER) {
    Serial.print("WHYNTER: ");
  }
  Serial.print(results->value, HEX);
  Serial.println(" ");
}

void loop() {
  if (irrecv.decode(&results)) {
    // Prints the results in HEX
    Serial.println(results.value, HEX);
    HEXdecode(&results);
    // Resume IR receiver operation
    irrecv.resume(); 
  }
}
