#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <malloc.h>
#include "say.h"


// [0] maps to accii 48 (0)
char phonetic[][65]={"zerow.","1.","2.","3.","4.","5.","6.","7.","8.","9.", \
". , .","Semicolon","less than","equal","greater than","question","at", \
"Alpha.","Bravo.","Charlie.","Delta.","Echo.","Fox-Trot.","Golf.","Hotel.", \
"India.","Juliet.","Kilo.","Lima.","Mike.","November.","Ozzzska.","Papa.",\
"Quebec.","Romeo.","Sierra.","Tango.","Uniform.","Victor.","Whiskey.","X-Ray.",\
"Yankee.","Zulu."};


int Say::Initialise(void)
{
	  return 0;
}

int Say::Announce(void)
{
  char bigmessage[1000];
  char localbuffer[5000];
  time_t t;
  struct tm *tmp; 
  t = time(NULL);
	tmp = localtime(&t);

  strftime(bigmessage,45,"G  B  3  X  X.. Information at %H:%M..",tmp);
  sprintf(localbuffer,"pico2wave -l en-GB -w temp.wav \"%s\"", bigmessage);
  printf("[%s]\n" ,localbuffer);
  system(localbuffer);
  system("aplay temp.wav");
 
  return 0;
}

int Say::TimeSignal(int hours)
{
  char bigmessage[1000];
  char localbuffer[5000];

  if(hours < 6)
  {
    sprintf(bigmessage,"G B 3 X X. The time is %i O Clock.. bip, bip, bip, bip, bip, BEEEEP..... ",hours);
    strcat(bigmessage,"I really don't know why i bother at this time of the morning");
    sprintf(localbuffer,"pico2wave -l en-GB -w time.wav \"%s\"", bigmessage);
    printf("[%s]\n" ,localbuffer);

  }
  else
  {
    if (hours > 12) hours-=12;
    sprintf(bigmessage,"G B 3 X X. The time is %i O Clock",hours);
    sprintf(localbuffer,"pico2wave -l en-GB -w time.wav \"%s\"", bigmessage);
    printf("[%s]\n" ,localbuffer);    
    
  }
  
  system(localbuffer);
  system("aplay time.wav");   
  return 0;  
}
  


int Say::SayText ( char * subject)
{  
  char localbuffer[5000];
  
  sprintf(localbuffer,"pico2wave -l en-GB -w temp.wav \"%s\"", subject);
  printf("[%s]\n" ,localbuffer);
  system(localbuffer);
  system("aplay temp.wav");
  return 0;
}


int Say::MakeWav ( char * filename, char * buffer )
{  
  char localbuffer[5000];
  sprintf(localbuffer,"pico2wave -l en-GB -w %s \"%s\"",filename, buffer);
  system(localbuffer);
  return 0;
}

int Say::SayWav ( char * filename )
{  
  char localbuffer[50];
  sprintf(localbuffer,"aplay %s",filename);
  system(localbuffer);
  return 0;
}


int Say::Close(void)
{
  return 0;
}

