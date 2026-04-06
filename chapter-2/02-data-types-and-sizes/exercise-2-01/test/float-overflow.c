#include <stdio.h>

int main() {
  float f = 3.402823e+38;
  while (1) {
    printf("%f\n", f);
    ++f;
  }
}
