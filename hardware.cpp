#include <curses.h>
#include "hardware.h"
#include <string.h>


int Hardware::Init( void)
{
  keypad(stdscr,TRUE);
  cbreak();
  Exitcode=0;
  return 0;
}

int Hardware::Close()
{
  return 0;
}

int Hardware::Scan()
{
  int key;
  key = getch();
  switch(key)
  {
    case 's':
      Squelch ++;
      Squelch &= 1;
      break;

    case 'd':
      DataRefresh ++;
      DataRefresh &= 1;
      break;

    case 'e':
      Exitcode=1;
      break;
      
    default:
      break;
  }
    
  return 0;
}

int Hardware::Set(int port)
{
 
  return 0;
}

int Hardware::Clear(int port)
{
 
  return 0;
}
