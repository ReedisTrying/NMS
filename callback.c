#include "global.h"

void KeyboardEventProcess(int key, int event) {
    switch (event) {
        case KEY_DOWN:
            switch (Window_State) {
                case NEW_NOTE_WINDOW:
                    if (key == VK_RETURN) {
                        if (strlen(titleInput) > 0) {
                            saveNewNoteTitle(titleInput);
                        }
                    }
                    break;
            }
            break;
    }
    uiGetKeyboard(key, event);
    refreshScreen();
}

void CharEventProcess(char c) {
    uiGetChar(c);
    refreshScreen();
}

void MouseEventProcess(int x, int y, int button, int event) {
    uiGetMouse(x, y, button, event);
    if (event == MOUSEMOVE) {
    	curyy = -1; 
        double xx = ScaleXInches(x);
        double yy = ScaleYInches(y);
        double ww = GetWindowWidth();
        double titleX = ww / 6;
        NoteNode *current = note_head;
        
        while(current){
            if (xx >= titleX && xx <= ww - titleX &&
                yy >= current->titleY  && yy <= current->titleY + GetFontHeight()) {
                curyy = current->titleY;
                break;
            }
            current = current->next;
        }
        refreshScreen();
    }
    if (button == LEFT_BUTTON && event == BUTTON_DOWN){
		double xx = ScaleXInches(x);
        double yy = ScaleYInches(y);
        double ww = GetWindowWidth();
        double titleX = ww / 6;
        NoteNode *current = note_head;
        
        while(current){
            if (xx >= titleX && xx <= ww - titleX &&
                yy >= current->titleY && yy <= current->titleY + GetFontHeight()) {
				currentNode = current;
				Window_State = EDIT_NOTE_WINDOW;
				noteTitleClick(current);
                break;
            }
            current = current->next;
        }
        refreshScreen();
	}
}

void TimerEventProcess(int timerID) {
	if (timerID == TIMER_ERRORMESSAGE) {
        errorCode = 0; 
		Window_State = MAIN_WINDOW;
		cancelTimer(TIMER_ERRORMESSAGE);
        refreshScreen();
    }
}
