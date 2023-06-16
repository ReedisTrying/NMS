#include "global.h"

void KeyboardEventProcess(int key, int event) {
    int i;
    FILE *logFileBefore;
	FILE *logFileIf;
	
    if (event == KEY_DOWN){
        switch(key) {
            case VK_LEFT:
                if (location > 0) {
                    curOp = -1;
                }
                break;
            case VK_RIGHT:
                if (location < textlen) {
                    curOp = 1;
                }
                break;
            case ' ':
				curOp = 1;
                break; // Added this break statement
            case VK_BACK:
			case VK_DELETE: // work as backspace

	
				    // Debugging log before the if condition
				logFileBefore = fopen("log_delete_before.txt", "a");
				if(logFileBefore == NULL) {
				    fprintf(stderr, "Error opening log file\n");
				    exit(1);
				}
				fprintf(logFileBefore, "Before delete: location: %d, textlen: %d, text: %s\n", location, textlen, text);
				fclose(logFileBefore);
			
				if (textlen > 0 && location > 0) {
				        // Debugging log inside the if condition
				    logFileIf = fopen("log_delete_if.txt", "a");
				    if(logFileIf == NULL) {
				        fprintf(stderr, "Error opening log file\n");
				        exit(1);
				    }
				    fprintf(logFileIf, "Inside if before deletion: location: %d, textlen: %d, text: %s\n", location, textlen, text);
				    fclose(logFileIf);
	                for (i = location - 1; i < textlen - 1; i++) { // logic
	                    text[i] = text[i+1];
	                }
                    
					curOp = -1; 
                    textlen--;
                    location--;
                    text[textlen] = '\0';
                    //refreshScreen(); //Consider refresh after/before text is chagned
                }
                break;
            default:
                // no action needed for other keys
                break;
        }
		//location += curOp;
        refreshScreen();
    }
}

	
void MouseEventProcess(int x, int y, int button, int event) {
	uiGetMouse(x, y, button, event);
	if (Window_State == MAIN_WINDOW){
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
	    }		   
	}
	refreshScreen(); //fixed for buttons
}

void CharEventProcess(char c) {
    wh = GetWindowHeight();
    ww = GetWindowWidth();
    SetPenColor("Black");
    
    uiGetChar(c);
    if (Window_State == EDIT_NOTE_WINDOW){

        if (c == '\r'){
            /*if(isBlink && isDisplay){
                SetEraseMode(TRUE);
                DrawTextString("_");
                MovePen(GetCurrentX()-TextStringWidth("_"),GetCurrentY());
            }
            // Clear the text buffer
            textlen = 0;
            text[0] = '\0';

            // Draw the text buffer on the screen and reset the position of the cursor
            MovePen(InitX , InitY);
            DrawTextString(text);
            SetEraseMode(FALSE);
            return;*/
        }
        else {
            if (textlen + 1 >= buffersize) {  // Resize buffer
                buffersize *= 2;

                char* temp = realloc(text, buffersize * sizeof(char));
                if (temp == NULL) {
                    drawErrorMessage(5);
                    return;
                }
                text = temp;
            }

            // Add the character to the text buffer
            text[textlen] = c;
            text[textlen+1] = '\0';
            textlen++;
            currentX += TextStringWidth(&c);
            location++;
            curOp = 1;
        }
        refreshScreen();
    }
}


void TimerEventProcess(int timerID)
{   
    switch (timerID) {
        case TIMER_ERRORMESSAGE:
            errorCode = 0; 
            Window_State = MAIN_WINDOW;
            cancelTimer(TIMER_ERRORMESSAGE);
            break;
        case TIMER_BLINK:
            if (!isBlink) return;
            isDisplay = !isDisplay;
            break;
        default:
            break;
    }
}

