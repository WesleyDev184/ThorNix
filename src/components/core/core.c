#include <stdarg.h>

#include "../../headers/defs.h"
#include "../../headers/statics.h"
#include "../../headers/types.h"

/**
 * Prints a string to the UART.
 *
 * @param s The string to be printed.
 */
void puts(char *s)
{
  while (*s != 0)
  {
    uart_putc(*s++);
  }
}

/**
 * Prints formatted output to the UART.
 *
 * @param format The format string.
 * @param ... Additional arguments to be formatted and printed.
 */
void printf(char *format, ...)
{
  va_list arg;
  int c;
  char *str;

  va_start(arg, format);
  for (; (c = *format) != 0; format++)
  {
    if (c != '%')
    {
      uart_putc(c);
    }
    else
    {
      c = *++format;
      switch (c)
      {
      case 'd':
        printlng(va_arg(arg, int), 10);
        break;
      case 'x':
        printlng(va_arg(arg, int), 16);
        break;
      case 'b':
        printlng(va_arg(arg, int), 2);
        break;
      case 'l':
        printlng(va_arg(arg, long), 10);
        break;
      case 's':
        str = va_arg(arg, char *);
        puts(str);
        break;
      case 'c':
        uart_putc(va_arg(arg, int));
        break;
      case 'p':
        printptr(va_arg(arg, void *));
        break;
      case '%':
        puts("%");
        break;
      }
    }
  }
}

/**
 * Prints a pointer value to the UART.
 *
 * @param ptr The pointer value to be printed.
 */
void printptr(void *ptr)
{
  uint64 addr = (uint64)ptr;
  char s[66];
  int i = 0;

  while (addr)
  {
    s[i++] = digits[addr % 16];
    addr = addr / 16;
  }

  s[i++] = 'x';
  s[i++] = '0';

  while (i >= 0)
  {
    uart_putc(s[--i]);
  }
}

/**
 * Prints a long integer value to the UART.
 *
 * @param val The long integer value to be printed.
 * @param base The base for printing (e.g., 10 for decimal, 16 for hexadecimal).
 */
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

  if (val < 0)
  {
    s[i++] = '-';
  }

  while (i > 0)
  {
    uart_putc(s[--i]);
  }
}

/**
 * Copies a string from source to destination.
 *
 * @param dest The destination string.
 * @param src The source string.
 */
void strcopy(char *dest, char *src)
{
  while (*src != 0)
  {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = 0;
}

/**
 * Prints a panic message to the UART and enters an infinite loop.
 *
 * @param msg The panic message to be printed.
 */
void panic(char *msg)
{
  printf("\u2671 Panic: %s\n", msg);
  while (1)
    ;
}