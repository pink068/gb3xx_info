#include <curses.h>
#include <unistd.h>
#include "statusbar.h"
#include "hardware.h"
#include "getdata.h"
#include "say.h"
#include <stdlib.h>
#include <string.h>
#include <libcw.h>
#include <sys/time.h>

StatusBar leds;
Hardware ports;
AnnounceData info;
Say Speak;
int lastminute;

int LastSquelchState;

int RepeaterLogic(void);
int SendInfo(void);

int main()
{
  int inuse;
  initscr();
  start_color();
  ports.Init();
  info.Init();
  Speak.Initialise();
  cw_generator_new(CW_AUDIO_SOUNDCARD, NULL);
  cw_generator_start();
  cw_set_send_speed(18);
  
  lastminute=0;
  LastSquelchState=Port_NotValid;

  info.Update();      
  for(inuse=0;inuse<10;inuse++)
  {
    mvprintw(inuse+10,1,"%i:[%s]",info.urgency[inuse],info.message[inuse]);
  }
  inuse=0;

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);  
  init_pair(4, COLOR_BLACK, COLOR_WHITE);  
  leds.Init(5,1,10);

  leds.Name(LED_1,"Squelch");
  leds.Name(LED_2,"Local");
  leds.Name(LED_3,"RX");
  leds.Name(LED_4,"CW");
  leds.Name(LED_5,"Speak");

  while (ports.Exitcode==0)
  {
    ports.Scan();
    
    leds.SetStatus(LED_1,ports.Squelch);     
    inuse = RepeaterLogic();
    
    if( ports.DataRefresh)
    {
      info.Update();
      ports.DataRefresh=0;
    }

    inuse=0;
    if(!inuse) SendInfo();
    
  }

//getch();
  endwin();
  cw_generator_stop();
  cw_generator_delete();  
  return 0;
}






int RepeaterLogic(void)
{
 // if sq is open then drops send a K.
 if(ports.Squelch == Port_Valid)
 {
   LastSquelchState=Port_Valid;
 }
 else
 {
   if(LastSquelchState==Port_Valid)
   {
    // get here if port is closed, BUT WAS OPEN
    // take control, send a K, release control
    leds.Name(LED_2,"Remote");
    ports.Set(Port_TCVR_Remote);
    
    leds.Name(LED_3,"TX");
    leds.SetStatus(LED_3,LED_ON);
    ports.Set(Port_PTT);
    
    cw_send_character('K');
    cw_wait_for_tone_queue();
    LastSquelchState=Port_NotValid;
    ports.Clear(Port_PTT);
    leds.Name(LED_3,"RX");
    leds.SetStatus(LED_3,LED_OFF);

    ports.Set(Port_TCVR_Local);
    leds.Name(LED_2,"Local ");
   }
 }
 return 1;
}



int SendInfo(void)
{
  int index;
  time_t t;
	struct tm *tmp;
   int minute;
   int trig_time;
    
  t = time(NULL);
	tmp = localtime(&t);
  minute = tmp->tm_min;

//  info.urgency[0]= 10;
//  strcpy(info.message[0],"test 10");

  trig_time=0;
  attrset(COLOR_PAIR(1));  
  if(minute != lastminute)
  {  // if we havn't done it yet
    for(index=0;index<10;index++)
    {
      if (info.urgency[index]>0)
      {
        trig_time = minute%info.urgency[index];    
     
        mvprintw(5,1,"%i,%i=%i\n",minute, info.urgency[index],trig_time);    
        refresh();
        if(trig_time ==0 ) 
        {
          mvprintw(5,10,"%i:%s\n",info.urgency[index],info.message[index]);
          refresh();
          Speak.SayMessage(info.message[index]); 
        } 
      }
    }
    lastminute = minute;
  }

  return 1;
}

