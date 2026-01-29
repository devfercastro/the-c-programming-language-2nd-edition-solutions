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
