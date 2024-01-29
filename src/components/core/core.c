#include "../../headers/defs.h"
#include "../../headers/statics.h"
#include "../../headers/types.h"

void puts(char *s)
{
  while (*s != 0)
  {
    uart_putc(*s++);
  }
}

void printptr(uint64 *ptr)
{
  printlng((long int)ptr, 16);
}

void printlng(long int val, int base)
{
  long l;
  char s[66];
  int i = 0;

  if (val < 0)
  {
    l = -val;
  }
  else
  {
    l = val;
  }

  if (l == 0)
  {
    s[i++] = '0';
  }

  while (l)
  {
    int d = l % base;
    s[i++] = digits[d];
    l = l / base;
  }

  if (base == 16)
  {
    s[i++] = 'x';
    s[i++] = '0';
  }

  if (base == 2)
  {
    s[i++] = 'b';
    s[i++] = '0';
  }

  if (val < 0)
  {
    s[i++] = '-';
  }

  while (i > 0)
  {
    uart_putc(s[--i]);
  }
}