#include <Keyboard.h>

// uncomment to use for serial terminal debugging rather than usb hid device
// this is so you can see the ascii values to verify
//#define SERIAL_DEBUG

#define p1 2
#define p2 3
#define p3 4
#define p4 5
#define p5 6
#define p6 7
#define p7 8
#define p8 9
#define p9 10
#define p10 16
#define p11 14
#define p12 15
#define p13 A0
#define p14 A1
#define p15 A2

bool _shiftState  = false;
int  _lastKeyCode = 0;
int  _ctrlState = false;

void setup() {

#ifdef SERIAL_DEBUG
  Serial.begin(9600);
#else
  Keyboard.begin();
#endif

  pinMode(p1, OUTPUT); // shift (1-5)
  pinMode(p2, INPUT_PULLUP);
  pinMode(p3, INPUT_PULLUP);
  pinMode(p4, INPUT_PULLUP);
  pinMode(p5, INPUT_PULLUP);
  pinMode(p6, INPUT_PULLUP);
  pinMode(p7, INPUT_PULLUP);
  pinMode(p8, OUTPUT);
  pinMode(p9, INPUT_PULLUP);
  pinMode(p10, INPUT_PULLUP);
  pinMode(p11, OUTPUT);
  pinMode(p12, OUTPUT);
  pinMode(p13, OUTPUT);
  pinMode(p14, OUTPUT);
  pinMode(p15, OUTPUT);
}

void outputStrobeState(int x) {

  digitalWrite(p1, HIGH);
  digitalWrite(p8, HIGH);
  digitalWrite(p11, HIGH);
  digitalWrite(p12, HIGH);
  digitalWrite(p13, HIGH);
  digitalWrite(p14, HIGH);
  digitalWrite(p15, HIGH);

  switch (x) {
    case 0:
      digitalWrite(p1, LOW); // only SHIFT is on this strobe
      break;
    case 1:
      digitalWrite(p8, LOW);
      break;
    case 2:
      digitalWrite(p11, LOW);
      break;
    case 3:
      digitalWrite(p12, LOW);
      break;
    case 4:
      digitalWrite(p13, LOW);
      break;
    case 5:
      digitalWrite(p14, LOW);
      break;
    case 6:
      digitalWrite(p15, LOW);
      break;
  }

  delay(10);
}

int getKeyPressed() {

  for (int x = 0; x < 7; x++) {

    outputStrobeState(x);

    int keyPress = 0;

    // Check CTRL before everything else
    keyPress += !digitalRead(p7) * 0x60;

    if (x == 1) {

      if (keyPress == 0x60) {

        keyPress = 0;

        _ctrlState = true;
      } else {

        _ctrlState = false;
      }
    }

    // Now check SHIFT
    keyPress += !digitalRead(p5) * 0x40;

    if (x == 0) {

      if (keyPress == 0x40) {

        keyPress = 0;

        _shiftState = true;
      } else {

        _shiftState = false;
      }
    }

    // Continue checking the rest
    keyPress += !digitalRead(p2) * 0x10;
    keyPress += !digitalRead(p3) * 0x20;
    keyPress += !digitalRead(p4) * 0x30;
    keyPress += !digitalRead(p6) * 0x50;
    keyPress += !digitalRead(p9) * 0x70;
    keyPress += !digitalRead(p10) * 0x80;

    if (keyPress)
      return (x * 0x01)  +  keyPress;
  }

  return 0;
}

int _lastMillis = 0;

void loop() {

  int keyCode = getKeyPressed();

  if (keyCode == 0) {

    _lastKeyCode = 0;

    return;
  }

  if (_lastKeyCode != keyCode) {

    _lastKeyCode = keyCode;
  } else if (_lastKeyCode == keyCode && _lastMillis + 300 > millis()) {

    return;
  }

  _lastMillis = millis();

#ifdef SERIAL_DEBUG

  Serial.print(_ctrlState);
  Serial.print(" ");
  Serial.print(_shiftState);
  Serial.print(" ");
  Serial.print(keyCode);
  Serial.println();

#else

  if (keyCode == 118)
    Keyboard.write(KEY_ESC);
  else if (keyCode == 17)
    Keyboard.write(' ');

  if (_ctrlState) {

    if (keyCode == 65)
      Keyboard.write(1);
    else if (keyCode == 36)
      Keyboard.write(2);
    else if (keyCode == 35)
      Keyboard.write(3);
    else if (keyCode == 66)
      Keyboard.write(4);
    else if (keyCode == 98)
      Keyboard.write(5);
    else if (keyCode == 51)
      Keyboard.write(6);
    else if (keyCode == 67)
      Keyboard.write(7);
    else if (keyCode == 52)
      Keyboard.write(8);
    else if (keyCode == 85)
      Keyboard.write(9);
    else if (keyCode == 68)
      Keyboard.write(10);
    else if (keyCode == 53)
      Keyboard.write(11);
    else if (keyCode == 69)
      Keyboard.write(12);
    else if (keyCode == 37)
      Keyboard.write(13);
    else if (keyCode == 20)
      Keyboard.write(14);
    else if (keyCode == 101)
      Keyboard.write(15);
    else if (keyCode == 86)
      Keyboard.write(16);
    else if (keyCode == 81)
      Keyboard.write(17);
    else if (keyCode == 83)
      Keyboard.write(18);
    else if (keyCode == 50)
      Keyboard.write(19);
    else if (keyCode == 99)
      Keyboard.write(20);
    else if (keyCode == 100)
      Keyboard.write(21);
    else if (keyCode == 19)
      Keyboard.write(22);
    else if (keyCode == 82)
      Keyboard.write(23);
    else if (keyCode == 18)
      Keyboard.write(24);
    else if (keyCode == 84)
      Keyboard.write(25);
    else if (keyCode == 34)
      Keyboard.write(26);

  } else if (_shiftState) {

    if (keyCode == 102)
      Keyboard.write(KEY_BACKSPACE);

    if (keyCode == 65)
      Keyboard.write('A');
    else if (keyCode == 36)
      Keyboard.write('B');
    else if (keyCode == 35)
      Keyboard.write('C');
    else if (keyCode == 66)
      Keyboard.write('D');
    else if (keyCode == 98)
      Keyboard.write('E');
    else if (keyCode == 51)
      Keyboard.write('F');
    else if (keyCode == 67)
      Keyboard.write('G');
    else if (keyCode == 52)
      Keyboard.write('H');
    else if (keyCode == 85)
      Keyboard.write('I');
    else if (keyCode == 68)
      Keyboard.write('J');
    else if (keyCode == 53)
      Keyboard.write('K');
    else if (keyCode == 69)
      Keyboard.write('L');
    else if (keyCode == 37)
      Keyboard.write('M');
    else if (keyCode == 20)
      Keyboard.write('N');
    else if (keyCode == 101)
      Keyboard.write('O');
    else if (keyCode == 86)
      Keyboard.write('P');
    else if (keyCode == 81)
      Keyboard.write('Q');
    else if (keyCode == 83)
      Keyboard.write('R');
    else if (keyCode == 50)
      Keyboard.write('S');
    else if (keyCode == 99)
      Keyboard.write('T');
    else if (keyCode == 100)
      Keyboard.write('U');
    else if (keyCode == 19)
      Keyboard.write('V');
    else if (keyCode == 82)
      Keyboard.write('W');
    else if (keyCode == 18)
      Keyboard.write('X');
    else if (keyCode == 84)
      Keyboard.write('Y');
    else if (keyCode == 34)
      Keyboard.write('Z');

    else if (keyCode == 113)
      Keyboard.write('=');
    else if (keyCode == 130)
      Keyboard.write('"');
    else if (keyCode == 114)
      Keyboard.write('#');
    else if (keyCode == 131)
      Keyboard.write('$');
    else if (keyCode == 115)
      Keyboard.write('+');
    else if (keyCode == 132)
      Keyboard.write('-');
    else if (keyCode == 116)
      Keyboard.write('/');
    else if (keyCode == 133)
      Keyboard.write('*');
    else if (keyCode == 117)
      Keyboard.write('(');
    else if (keyCode == 134)
      Keyboard.write(')');

    else if (keyCode == 21)
      Keyboard.write('<');
    else if (keyCode == 38)
      Keyboard.write('>');

    else if (keyCode == 49)
      Keyboard.write('^');
    else if (keyCode == 129)
      Keyboard.write('/');
    else if (keyCode == 33)
      Keyboard.write('?');
    else if (keyCode == 22)
      Keyboard.write('%');

  } else {

    if (keyCode == 102)
      Keyboard.write(KEY_RETURN);

    if (keyCode == 65)
      Keyboard.write('a');
    else if (keyCode == 36)
      Keyboard.write('b');
    else if (keyCode == 35)
      Keyboard.write('c');
    else if (keyCode == 66)
      Keyboard.write('d');
    else if (keyCode == 98)
      Keyboard.write('e');
    else if (keyCode == 51)
      Keyboard.write('f');
    else if (keyCode == 67)
      Keyboard.write('g');
    else if (keyCode == 52)
      Keyboard.write('h');
    else if (keyCode == 85)
      Keyboard.write('i');
    else if (keyCode == 68)
      Keyboard.write('j');
    else if (keyCode == 53)
      Keyboard.write('k');
    else if (keyCode == 69)
      Keyboard.write('l');
    else if (keyCode == 37)
      Keyboard.write('m');
    else if (keyCode == 20)
      Keyboard.write('n');
    else if (keyCode == 101)
      Keyboard.write('o');
    else if (keyCode == 86)
      Keyboard.write('p');
    else if (keyCode == 81)
      Keyboard.write('q');
    else if (keyCode == 83)
      Keyboard.write('r');
    else if (keyCode == 50)
      Keyboard.write('s');
    else if (keyCode == 99)
      Keyboard.write('t');
    else if (keyCode == 100)
      Keyboard.write('u');
    else if (keyCode == 19)
      Keyboard.write('v');
    else if (keyCode == 82)
      Keyboard.write('w');
    else if (keyCode == 18)
      Keyboard.write('x');
    else if (keyCode == 84)
      Keyboard.write('y');
    else if (keyCode == 34)
      Keyboard.write('z');

    else if (keyCode == 113)
      Keyboard.write('1');
    else if (keyCode == 130)
      Keyboard.write('2');
    else if (keyCode == 114)
      Keyboard.write('3');
    else if (keyCode == 131)
      Keyboard.write('4');
    else if (keyCode == 115)
      Keyboard.write('5');
    else if (keyCode == 132)
      Keyboard.write('6');
    else if (keyCode == 116)
      Keyboard.write('7');
    else if (keyCode == 133)
      Keyboard.write('8');
    else if (keyCode == 117)
      Keyboard.write('9');
    else if (keyCode == 134)
      Keyboard.write('0');

    else if (keyCode == 21)
      Keyboard.write(',');
    else if (keyCode == 38)
      Keyboard.write('.');

    else if (keyCode == 49)
      Keyboard.write(KEY_UP_ARROW);
    else if (keyCode == 129)
      Keyboard.write(KEY_RIGHT_ARROW);
    else if (keyCode == 33)
      Keyboard.write(KEY_DOWN_ARROW);
    else if (keyCode == 22)
      Keyboard.write(KEY_LEFT_ARROW);
  }
#endif

  delay(50);
}
