#include <unistd.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "getdata.h"
#include <curses.h>

int AnnounceData::Update(void)
{
   char localbuffer[10000];
   char * start;
   char * end;
   int index;
   char temp[1000];
   
   mvaddstr(5,2, "Reading Data");
   refresh();
   GetPage(localbuffer,(char*)"http://alphacharlie.org.uk/gb3xx_info.php");
//  strcpy(localbuffer, "12;Aurora state 0.67 KP. No visibility;34; 40 meters Open.. 30 meters Open..;00;The weather is forecasted to be light drizzle with daytime temperature reaching 4 °c. Night time temperature are expected to be 1 °c.We expect around 3.1 mm of precipitation to fall. The visibility is going to be around 11 km i.e. 6 miles and an atmospheric pressure of 989 mb. We expect around 3.1 mm of precipitation to fall and cloud covering 98% of the sky, the humidity will be around 99%.;");
//  strcat(localbuffer,";;");


 	index=0;
  start = localbuffer;
  temp[0]=0;
  do
  {
    end = strstr(start,";");
    if (!end ) break;
    end[0]=0;   // null the string end
    strcpy(temp,start);
    urgency[index]=atoi(temp);
    start=end+1;
    
    end = strstr(start,";");
    if (!end ) break;
    end[0]=0;   // null the string end
    strcpy(message[index],start);        
    start=end+1;
    
    index++;
       
  } while (end);
   return 0;
}

int AnnounceData::Init(void)
{
int a;
  for(a=0;a<10;a++)
  {
	message[a][0]=0;
	urgency[a]=0;
  }
  return 0;
}











/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * Shows how the write callback function can be used to download data into a
 * chunk of memory instead of storing it in a file.
 * </DESC>
 */



struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

int AnnounceData::GetPage(char * buffer, char * url)
{
  CURL *curl_handle;
  CURLcode res;


  struct MemoryStruct chunk;

  chunk.memory = (char *) malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  res = curl_easy_perform(curl_handle);

  /* check for errors */
  if(res != CURLE_OK) 
  {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else 
  {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */

//    printf("[%s]\n", chunk.memory); 
//    printf("%lu bytes retrieved\n", (long)chunk.size);
    chunk.memory[chunk.size]=0;
    strcpy(buffer, (char *)chunk.memory);
  }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  free(chunk.memory);

  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();

  return (int)chunk.size;
}
