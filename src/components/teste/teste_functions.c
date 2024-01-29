#include <stdarg.h>

int perimeter(int sides, ...)
{
  int per = 0;
  va_list ap; // variable that stores the list of arguments
  va_start(ap, sides);

  for (int i = 0; i < sides; i++)
  {
    per += va_arg(ap, int);
  }

  return per;
}