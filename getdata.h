class AnnounceData
{
  public:
	int Init(void);
	int Update(void);
	char AuroraMessage[1000];
	char HFMessage[1000];
	char WeatherMessage[2000];	
	int Aurgency;
	int HFurgency;  
	int Wurgency;
  
  private:	
	int GetPage(char * buffer, char * url);
};
 




