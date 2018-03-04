class StatusBar
{
  private:
  int item_state[16];
  char itemname[16][20];
  int sitems;
  int srows;
  int scolumns;
  
  public:
  int Init(int items, int rows, int columns);  
  int Name(int namenum, const char* name);
  int Draw(void);  
  int SetStatus(int item, int status);
  int Close();
};

enum LEDNAMES
{
  LED_1=0,
  LED_2,
  LED_3,
  LED_4,
  LED_5
};

enum LEDSTATES
{
  LED_OFF=0,
  LED_ON
};
