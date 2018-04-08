#define SAY_LONGMESS 0
#define SAY_SHORTMESS 1

class Say
{
	private:

	  int Phonetics(char * sentence);
	  int Spell(char * sentence);
        
	public:
	  int Initialise(void);
    int SayMessage(char * message);
    int SayWav ( char * filename );
    int TimeSignal(int hours);
    int Close(void);
    int Announce(void);
};
