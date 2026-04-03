#include <stdio.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */
int main()
{
  int c, nl, nw, nc, state;

  state = OUT;
  nl = nw = nc = 0;
  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n')
      ++nl;
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++nw;
    }
  }
  printf("New lines: %d, Words: %d, Characters: %d\n", nl, nw, nc);
}

// Not sure what to do
// 
// Tests
// Normal
// [exercise-11] echo -ne "Word1\tword2aftertab word3afterblank\nword4afternewline" | ./word-count.out
// New lines: 1, Words: 4, Characters: 54
// [exercise-11]
// 
// 4 spaces
// [exercise-11] echo -ne "    " | ./word-count.out
// New lines: 0, Words: 0, Characters: 4 
// 
// 2 tabs
// [exercise-11] echo -ne "\t\t" | ./word-count.out                        main  ✭ ✱
// New lines: 0, Words: 0, Characters: 2
// 
// 3 new lines
// [exercise-11] echo -ne "\n\n\n" | ./word-count.out                      main  ✭ ✱
// New lines: 3, Words: 0, Characters: 3
// 
// 2 backspaces and 5 letters
// [exercise-11] echo -ne "\b\bchars" | ./word-count.out                   main  ✭ ✱
// New lines: 0, Words: 1, Characters: 7
// 
// Obviously it can't pass this
// No words
//[exercise-11] echo -ne "--- --- ---" | ./word-count.out
// New lines: 0, Words: 3, Characters: 11 