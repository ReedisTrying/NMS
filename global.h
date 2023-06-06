#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"

#define MAX_NOTES 10
#define MAX_TITLE_LENGTH 128
#define MAX_CATEGORY_LENGTH 128
#define TIMER_ERRORMESSAGE 2

enum WindowState{
    MAIN_WINDOW,
    NEW_NOTE_WINDOW,
    EDIT_NOTE_WINDOW,
    INTRO_WINDOW,
    FIND_WINDOW
};
enum WindowState Window_State;

typedef struct NoteNode NoteNode;

struct NoteNode {
    char title[MAX_TITLE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    double titleY;
    NoteNode *next;
    //FILE fp;
};

//extern struct NoteNode *NoteNode; //struct error

extern double ww,wh;
extern NoteNode *note_head;
extern NoteNode *currentNode;
extern char titleInput[MAX_TITLE_LENGTH];
extern char categoryInput[MAX_TITLE_LENGTH];
extern int noteCount;
extern int errorCode;
extern double curyy;

void drawMainWindow();
void drawNewNoteWindow();
void drawEditNoteWindow(NoteNode *current);
void drawContent();
void drawMenu();
void drawErrorMessage(int errorCode);

void refreshScreen();
void windowsInit();

void saveNewNoteTitle(char *title, char *category);
void deleteNoteNode(NoteNode *current);
void noteTitleClick(NoteNode* current);

void KeyboardEventProcess(int key, int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);

#endif
