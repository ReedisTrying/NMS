#ifndef _MAIN_H_
#define _MAIN_H_

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

int noteCount = 0;
int errorCode = 0;

double windowsWidth,windowsHeight;
double fontHeight;


double noteTitleTextboxX;
double noteTitleTextboxY;
double noteTitleTextboxW;
double noteTitleTextboxH;

enum WindowState{
    MAIN_WINDOW,
    NEW_NOTE_WINDOW,
    EDIT_NOTE_WINDOW,
    INTRO_WINDOW,
    FIND_WINDOW
};

typedef struct NoteNode NoteNode;

struct NoteNode {
    char title[MAX_TITLE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    NoteNode *next;
};

void drawMainWindow();
void drawNewNoteWindow();
void drawEditNoteWindow();
void drawContent();
void drawMenu();
void drawErrorMessage(int errorCode);

void addButtonClick(void);
void noteTitleClick(int index);
void createNewNoteWindow(void);
void saveNewNoteTitle(char *title, char *category);
void refreshScreen();
void windowsInit();


void KeyboardEventProcess(int key, int event);
void CharEventProcess(char c);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);
#endif
