#include <curses.h>
#include <unistd.h>
#include "statusbar.h"
#include "hardware.h"
#include "getdata.h"
#include "say.h"
#include <stdlib.h>
#include <libcw.h>


StatusBar leds;
Hardware ports;
AnnounceData info;
Say Speak;

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
  
  LastSquelchState=Port_NotValid;

//  info.Update();      
//  SendInfo();

  cw_generator_new(CW_AUDIO_SOUNDCARD, NULL);
  cw_generator_start();
//  printf("%d",cw_get_send_speed());
  cw_set_send_speed(18);

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_GREEN);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);  
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
    if(!inuse) SendInfo();
    
  }

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
    // get here if port is closed
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
 return 1;
}


int SendInfo(void)
{
  int index;
  
  for(index=0;index<10;index++)
  {
//    printf("%i:%s\n",info.urgency[index],info.message[index]);
    if(info.urgency[index]>0) 
    {
      Speak.BuildMessage(info.message[index]);
    }
  }
  Speak.SayMessage(); 
  return 1;
}

