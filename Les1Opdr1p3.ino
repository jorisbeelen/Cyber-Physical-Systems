#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Basic Calculator Ready!");
  Serial.println("Type: 8 + 3  or  4.5*2  (Newline ending in Serial Monitor)");
  Serial.println();
}

void loop() {
  if (Serial.available() == 0) return;

  String input = Serial.readStringUntil('\n');
  input.trim();  // remove spaces and \r

  if (input.length() == 0) return;

  // Replace common multiply symbols
  input.replace("×", "*");
  input.replace("x", "*");
  input.replace("X", "*");

  Serial.print("Raw input received: '");
  Serial.print(input);
  Serial.println("'");

  // Find operator (+, -, *, /)
  int opPos = -1;
  char opChar = 0;
  const char ops[] = "+-*/";
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);
    for (size_t j = 0; j < sizeof(ops) - 1; j++) {
      if (c == ops[j]) {
        opPos = i;
        opChar = c;
        break;
      }
    }
    if (opPos != -1) break;
  }

  if (opPos == -1) {
    Serial.println("Error: no operator found (+, -, *, /)");
    return;
  }

  // Split into left and right numbers
  String left = input.substring(0, opPos);
  String right = input.substring(opPos + 1);
  left.trim();
  right.trim();

  // Convert to float using built-in Arduino method
  float a = left.toFloat();
  float b = right.toFloat();

  // Check if conversion worked
  if ((a == 0.0 && left != "0" && left != "0.0") ||
      (b == 0.0 && right != "0" && right != "0.0")) {
    Serial.println("Error: invalid number input. Use '.' for decimals.");
    return;
  }

  // Perform operation
  float result = 0.0;
  bool ok = true;

  switch (opChar) {
    case '+': result = a + b; break;
    case '-': result = a - b; break;
    case '*': result = a * b; break;
    case '/':
      if (b == 0) {
        Serial.println("Error: division by zero");
        ok = false;
      } else result = a / b;
      break;
    default:
      Serial.println("Error: unknown operator");
      ok = false;
  }

  if (ok) {
    Serial.print("Result: ");
    Serial.println(result, 6); // up to 6 decimals
  }

  Serial.println();
}
