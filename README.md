# gb3xx_info
Infomation broadcaster for the GB3XX amateur radio repeater

To simplify the data reading my web server scours the internet for information and hands it over to the program in a simple to extract text format

Example:
10 this is the message; 20 This is another message;

The program knows that the first message has a priority of 10, transmit every 10 minutes (priority 100 is don't transmit)
it then turns "this is the message" into a digital speech wav file, and plays the WAV


At the moment the inputs are simulated with the s, d and e keys.
s toggles squelch open/closed.
d transmits the data.
e exits the program.

outputs are simulated with status messages on the top of the screen.

next job is to check the urgency value that is in the text messages to see when to transmit them.
The I have to interface to real hardware.



Dependencies:
ncurses
curl
pico2wave
aplay
libcw

Instructions:
Make by typing   make    in a command prompt
./run     to make it go

Yes it's really that simple
