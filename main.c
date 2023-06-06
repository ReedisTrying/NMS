#include "global.h"


NoteNode *note_head = NULL;
NoteNode *currentNode = NULL;
enum WindowState Window_State = MAIN_WINDOW;
char titleInput[MAX_TITLE_LENGTH]="";
char categoryInput[MAX_TITLE_LENGTH]="";
int noteCount = 0;
int errorCode = 0;
double ww = 0;
double wh = 0;
double curyy = -1;

void Main() {
	windowsInit();

    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
    registerMouseEvent(MouseEventProcess);
	registerTimerEvent(TimerEventProcess);
}


