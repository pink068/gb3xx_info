class AnnounceData
{
  public:
	int Init(void);
	int Update(void);
	char message[10][1000];
    int urgency[10];
      
  private:	
	int GetPage(char * buffer, char * url);
};
 




