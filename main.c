#include "global.h"

NoteNode *note_head = NULL;
NoteNode *currentNode = NULL;
enum WindowState Window_State = MAIN_WINDOW;
char titleInput[MAX_TITLE_LENGTH]="";
int noteCount = 0;
int errorCode = 0;

double wh = 0; 
double ww = 0;
double curyy = -1;
int location = 0;
double currentX = 0;

bool isBlink = 0;
bool isDisplay = 0;
int textlen = 0;
char *text = NULL;
int buffersize = 64;
int curOp = 0;
 

void Main() {
	windowsInit();

    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
    registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
}
