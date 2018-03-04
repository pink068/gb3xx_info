#include <curses.h>
#include "statusbar.h"
#include <string.h>

int ColumnWidth;
char ledname[10][10];
int chome;



int StatusBar::Name(int item, const char * name)
{
  strcpy(ledname[item],name);
  mvaddstr(2,(item*(ColumnWidth+1))+2, ledname[item]);
  move(4,1);
  refresh();
  return 0;
}


int StatusBar::SetStatus(int item, int status)
{

  if(status==0)
  {
    attrset(COLOR_PAIR(1)); // draw in dk green if disabled
    
  }
  else
  {
    attrset(COLOR_PAIR(2)); // draw bright green if active
  }
  mvaddstr(2,(item*(ColumnWidth+1))+2, ledname[item]);
  move(4,1);
  refresh();
  return 0;
}


int StatusBar::Init( int items, int rows, int colwidth)
{
  int a;
  int b;  
  
  ColumnWidth =  colwidth;
  attrset(COLOR_PAIR(3));
  
//  draws the top row
  mvaddch(1,1,ACS_ULCORNER);  
  for(a=0;a<items;a++)
  {
    for(b=0;b<colwidth;b++)
    {
      addch(ACS_HLINE);
    }
    addch(ACS_TTEE);
  } // end of a 
  addch(ACS_URCORNER);
  
// draws the middle row with dividers
  mvaddch(2,1,ACS_VLINE);  
  for(a=0;a<items;a++)
  {
    for(b=0;b<colwidth;b++)
    {
      addch(' ');  
    }
    addch(ACS_VLINE);
  } // end of a 
  addch(ACS_VLINE);
  
// draws the bottom row  
  mvaddch(3,1,ACS_LLCORNER);  
  for(a=0;a<items;a++)
  {
    for(b=0;b<colwidth;b++)
    {
      addch(ACS_HLINE);
    }
    addch(ACS_BTEE);
  } // end of a 
  addch(ACS_LRCORNER);
  mvaddstr(4,2, "    Press E to exit");  
  refresh();
  return 0;
}

int StatusBar::Close()
{
  return 0;
}



#ifdef hfagfahgflds
/* VT100 symbols begin here */
#define ACS_ULCORNER	NCURSES_ACS('l') /* upper left corner */
#define ACS_LLCORNER	NCURSES_ACS('m') /* lower left corner */
#define ACS_URCORNER	NCURSES_ACS('k') /* upper right corner */
#define ACS_LRCORNER	NCURSES_ACS('j') /* lower right corner */
#define ACS_LTEE	NCURSES_ACS('t') /* tee pointing right */
#define ACS_RTEE	NCURSES_ACS('u') /* tee pointing left */
#define ACS_BTEE	NCURSES_ACS('v') /* tee pointing up */
#define ACS_TTEE	NCURSES_ACS('w') /* tee pointing down */
#define ACS_HLINE	NCURSES_ACS('q') /* horizontal line */
#define ACS_VLINE	NCURSES_ACS('x') /* vertical line */
#define ACS_PLUS	NCURSES_ACS('n') /* large plus or crossover */
#define ACS_S1		NCURSES_ACS('o') /* scan line 1 */
#define ACS_S9		NCURSES_ACS('s') /* scan line 9 */
#define ACS_DIAMOND	NCURSES_ACS('`') /* diamond */
#define ACS_CKBOARD	NCURSES_ACS('a') /* checker board (stipple) */
#define ACS_DEGREE	NCURSES_ACS('f') /* degree symbol */
#define ACS_PLMINUS	NCURSES_ACS('g') /* plus/minus */
#define ACS_BULLET	NCURSES_ACS('~') /* bullet */
/* Teletype 5410v1 symbols begin here */
#define ACS_LARROW	NCURSES_ACS(',') /* arrow pointing left */
#define ACS_RARROW	NCURSES_ACS('+') /* arrow pointing right */
#define ACS_DARROW	NCURSES_ACS('.') /* arrow pointing down */
#define ACS_UARROW	NCURSES_ACS('-') /* arrow pointing up */
#define ACS_BOARD	NCURSES_ACS('h') /* board of squares */
#define ACS_LANTERN	NCURSES_ACS('i') /* lantern symbol */
#define ACS_BLOCK	NCURSES_ACS('0') /* solid square block */
#endif
