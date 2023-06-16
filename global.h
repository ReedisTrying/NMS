#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include <time.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"

#define MAX_NOTES 10
#define MAX_TITLE_LENGTH 64
#define MAX_NOTE_LENGTH 1024
#define MILLISECONDS 1000
#define TIMER_BLINK 1
#define TIMER_ERRORMESSAGE 2


enum WindowState{
    MAIN_WINDOW,
    NEW_NOTE_WINDOW,
    EDIT_NOTE_WINDOW
};
enum WindowState Window_State;

typedef struct NoteNode NoteNode;

struct NoteNode {
    char title[MAX_TITLE_LENGTH];
    double titleY;
    NoteNode *next;
    FILE *fp;
};

extern double ww,wh; //position
extern double curyy;
extern double currentX;

extern NoteNode *note_head; //node
extern NoteNode *currentNode;
extern char titleInput[MAX_TITLE_LENGTH];
extern int noteCount;
extern int errorCode;


extern bool isBlink; //text
extern bool isDisplay;
extern char *text;
extern int textlen;
extern int buffersize;
extern int location;
extern int curOp; 
extern double InitX;
extern double InitY;

void drawMainWindow();
void drawNewNoteWindow();
void drawEditNoteWindow(NoteNode *current);
void drawContent();
void drawMenu();
void drawErrorMessage(int errorCode);
void drawCursor();

void refreshScreen();
void windowsInit();

void saveNewNoteTitle(char *title);
void deleteNoteNode(NoteNode *current);
void noteTitleClick(NoteNode* current);
void saveNote(NoteNode *current);
void loadNotes(NoteNode *current); 
void resetText();

void KeyboardEventProcess(int key, int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

#endif
