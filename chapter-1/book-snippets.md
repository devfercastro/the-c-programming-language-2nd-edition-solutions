# Chapter 1

## 1.5 Character Input and Output

### 1.5.1 File Copying

```c
#include <stdio.h>
/* copy input to output; 1st version */
main()
{
  int c;

  c = getchar();
  while (c != EOF) {
    putchar(c);
    c = getchar();
  }
}
```

```c
#include <stdio.h>
/* copy input to output; 2nd version */
main()
{
  int c;

  while ((c = getchar()) != EOF)
    putchar(c);
}
```

### 1.5.2 Character Counting

```c
#include <stdio.h>
/* count characters in input; 1st version */
main()
{
  long nc;

  nc = 0;
  while (getchar() != EOF)
    ++nc;
  printf("%ld\n", nc);
}
```

```c
#include <stdio.h>
/* count characters in input; 2nd version */
main()
{
  double nc; // switch to `double` for even bigger numbers

  for (nc = 0; gechar() != EOF; ++nc)
  ;
  printf("%.0f\n", nc);
}
```

### 1.5.3 Line Counting

```c
#include <stdio.h>
/* count lines in input */
main()
{
  int c, nl;

  nl = 0;
  while ((c = getchar()) != EOF)
    if (c == '\n')
    ++nl;
  printf("%d\n", nl);
}
```

### 1.5.4 Word Counting

```c
#include <stdio.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

/* count lines, words, and characters in input */
main()
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
  printf("%d %d %d\n", nl, nw, nc);
}
```

## 1.6 Arrays

```c
#include <stdio.h>
/* count digits, white space, others */
main()
{
  int c, i, nwhite, nother;
  int ndigit[10];
  nwhite = nother = 0;

  for (i = 0; i < 10; ++i)
    ndigit[i] = 0;

  while ((c = getchar()) != EOF)
    if (c >= '0' && c <= '9')
      ++ndigit[c-'0'];
    else if (c == ' ' || c == '\n' || c == '\t')
      ++nwhite;
    else
      ++nother;

  printf("digits =");

  for (i = 0; i < 10; ++i)
    printf(" %d", ndigit[i]);

  printf(", white space = %d, other = %d\n", nwhite, nother);
}
```

## 1.7 Functions

```c
#include <stdio.h>

int power(int m, int n);

/* test power function */
main()
{
  int i;

  for (i = 0; i < 10; ++i)
    printf("%d %d %d\n", i, power(2,i), power(-3,i));

  return 0;
}

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
  int i, p;

  p = 1;
  for (i = 1; i <= n; ++i)
    p = p * base;

  return p;
}
```
