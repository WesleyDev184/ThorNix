#include "../../headers/defs.h"
#include "../../headers/console.h"
#include "../../headers/proc.h"
#include "../../headers/riscv.h"
#include "../../headers/memlayout.h"

#define WIDTH 20
#define HEIGHT 20
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

// typedef struct SnakeBody
// {
//   int x;
//   int y;
//   struct snakeGame *next;
// } snakeBody;

uint64 *mtimecmp = (uint64 *)CLINT_MTIMECMP(0);
uint64 *mtime = (uint64 *)CLINT_MTIME;

int x, y, gameover;
int tailX[100], tailY[100];
int nTail;
char dir;

void Setup()
{
  gameover = 0;
  dir = RIGHT;
  x = WIDTH / 2;
  y = HEIGHT / 2;
  nTail = 0;
}

void Draw()
{
  puts(CURSOR_UP_LEFT); /* Clear screen and move cursor to 1,1 */
  for (int i = 0; i < WIDTH + 2; i++)
    printf("■");
  printf("\n");

  for (int i = 0; i < HEIGHT; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      if (j == 0)
        printf("■");
      if (i == y && j == x)
        printf("$");
      else
      {
        int printTail = 0;
        for (int k = 0; k < nTail; k++)
        {
          if (tailX[k] == j && tailY[k] == i)
          {
            printf("$");
            printTail = 1;
          }
        }
        if (!printTail)
          printf(" ");
      }
      if (j == WIDTH - 1)
        printf("■");
    }
    printf("\n");
  }

  for (int i = 0; i < WIDTH + 2; i++)
    printf("■");
  printf("\n");
}

void Input()
{
  int c = uart_getc();
  if (c == -1)
    return;

  switch (c)
  {
  case LEFT:
    if (dir != RIGHT)
      dir = LEFT;
    break;
  case RIGHT:
    if (dir != LEFT)
      dir = RIGHT;
    break;
  case UP:
    if (dir != DOWN)
      dir = UP;
    break;
  case DOWN:
    if (dir != UP)
      dir = DOWN;
    break;
  case 'x':
    gameover = 1;
    break;
  default:
    break;
  }
}

void Logic()
{
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = x;
  tailY[0] = y;
  for (int i = 1; i < nTail; i++)
  {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }
  switch (dir)
  {
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;
  }
  if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
    gameover = 1;
  for (int i = 0; i < nTail; i++)
  {
    if (tailX[i] == x && tailY[i] == y)
      gameover = 1;
  }
}

int snakeGameMain()
{
  puts(CLEAR_SCREEN CURSOR_UP_LEFT); /* Clear screen and move cursor to 1,1 */

  Setup();
  while (!gameover)
  {
    Draw();
    Input();
    Logic();

    int sec = 1;
    int start = *mtime;
    int end = start + sec * 10000000;
    while (*mtime < end)
      ;
  }
  return 0;
}
