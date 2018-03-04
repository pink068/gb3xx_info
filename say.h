#define SAY_LONGMESS 0
#define SAY_SHORTMESS 1

class Say
{
	private:

	  int Phonetics(char * sentence);
	  int Spell(char * sentence);
        
	public:
	  int Initialise(void);
    int BuildMessage(char*);
    int SayMessage(void);
    
    int SayText (char * subject);
    // if shortmess =1 it says the short message

    int IfImportant (char * subject);
    int AnnounceIfImportant(void);
    int Announce(void);
    int MakeWav ( char * filename, char * buffer );
    int SayWav ( char * filename );
    int TimeSignal(int hours);
    int Close(void);
};
