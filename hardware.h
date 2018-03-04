enum InPortStates
{
 Port_NotValid=0,
 Port_Valid =1,
 Port_TCVR_Remote,
 Port_TCVR_Local,
 Port_PTT,
 Port_LastEnum

};



class Hardware
{
  private:
  
  public:
  int Init(void);  
  int Set( int port);
  int Clear( int port);
  int Scan(void);
  int Squelch;
  int DataRefresh;
  int Exitcode;
  int Close(void);
};
