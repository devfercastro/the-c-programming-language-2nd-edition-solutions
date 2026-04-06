// Integers constants
int a = 1234;             // simple
int b = 50000;            // too big for int, is taken as long
long c = 1234L;           // long
unsigned int d = 1234U;   // unsigned int
unsigned long e = 1234UL; // unsigned long

// Floating-point contants
float f = 123.4;  // simple, take as double by default
float g = 1e-2;   // scientific notation, take as double by default
float h = 123.4f; // take as float

// octal and hexadecimal constants
int octal = 037;     // 31 decimal
int hexa = 0x1F;     // 31 decimal
int octall = 037L;   // long octal
int hexal = 0x1FL;   // long hexa
int octalul = 037LU; // octal long unsigned
int hexaul = 0xFLU;  // hexa long unsigned

// character constants
char ch = '0';
char byte_s_octal = '\123'; // byte-sized pattern specified by three octal nums
char byte_s_hexa = '\xFF';  // byte-sized pattern specified by two hexa

// strings
char str[] = "cosa"
             " buena"; // equivalent to "cosa buena"
/* strlen: return length of s */
int strlen(char s[]) {
  int i;
  while (s[i] != '\0')
    ++i;
  return i;
}

// enums
enum boolean { NO, YES };
enum months {
  JAN = 1,
  FEB,
  MAR,
  APR,
  MAY,
  JUN,
  JUL,
  AUG,
  SEP,
  OCT,
  NOV,
  DEC
}; /* FEB = 2, MAR = 3, etc. */
