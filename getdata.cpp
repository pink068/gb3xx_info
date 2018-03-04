#include <unistd.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "getdata.h"
#include <curses.h>

// kp numbers
// 8 = all UK
// 7 = north of london
// 6 = north of newcastle
// 5 = scottish islands

int FilterPage(char * dest, char * source)
{
	int reply;
	source[2]=0;
	reply = atoi(source);
	strcpy(dest,&source[3]);
	return reply;
}


int AnnounceData::Update(void)
{
   char localbuffer[2000];
   mvaddstr(5,2, "Reading Data");
   refresh();

   GetPage(localbuffer,(char*)"http://alphacharlie.org.uk/gb3xx_aurora.php");
   Aurgency = FilterPage(AuroraMessage, localbuffer);
   mvaddstr(6,2, AuroraMessage);
   refresh();
   
   GetPage(localbuffer,(char*)"http://alphacharlie.org.uk/gb3xx_hf.php");
   HFurgency = FilterPage(HFMessage, localbuffer);
   mvaddstr(7,2, HFMessage);
   refresh();

   GetPage(localbuffer,(char*)"http://alphacharlie.org.uk/gb3xx_weather.php");
   Wurgency = FilterPage(WeatherMessage, localbuffer);
   mvaddstr(11,2, WeatherMessage);
   refresh();
   return 0;
}

int AnnounceData::Init(void)
{
	AuroraMessage[0]=0;
	HFMessage[0]=0;
	WeatherMessage[0]=0;	
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
