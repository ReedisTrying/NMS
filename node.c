#include "global.h"


void saveNewNoteTitle(char *title) {
    if (strlen(title) > 0 && strlen(title) <= MAX_TITLE_LENGTH - 1) {
        // Create a new node
        NoteNode *newNode = (NoteNode *) malloc(sizeof(NoteNode));
		if (newNode == NULL) {
		    drawErrorMessage(2); // Handle memory allocation error
		    return;
		}
        strncpy(newNode->title, title, MAX_TITLE_LENGTH - 1);
        newNode->title[MAX_TITLE_LENGTH - 1] = '\0';
        newNode->fp = NULL;
        newNode->next = NULL;

        // Add the new node to the linked list
        if (!note_head) {
            note_head = newNode;
        } else {
        
		NoteNode *current = note_head;
        while (current->next) {
            current = current->next;
        }
        
		current->next = newNode;
        
        }

        noteCount++;
        
        memset(titleInput, 0, sizeof(titleInput));

        Window_State = MAIN_WINDOW; // Return to the main window
        refreshScreen();
    }
}

void deleteNoteNode(NoteNode *node) {
    NoteNode *current = note_head;
    NoteNode *previous = NULL;

    while (current != NULL) {
        if (current == node) {
            if (previous == NULL) {
                note_head = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
}

void noteTitleClick(NoteNode *current){
	;
}

void saveNote(NoteNode *current) {
    char filename[MAX_TITLE_LENGTH + 5];  // +5 for extension and null terminator
    snprintf(filename, sizeof(filename), "%s.txt", current->title);

    if(current->fp == NULL) {
        if((current->fp = fopen(filename, "w")) == NULL) {
            drawErrorMessage(3);  // File open error
            return;  // Exit the function instead of the whole program
        }
    } else {
        if((current->fp = fopen(filename, "r+")) == NULL) {
            drawErrorMessage(3);  // File open error
            return;  // Exit the function instead of the whole program
        }
    }

    if(current->fp != NULL) {
        fwrite(text, 1, textlen, current->fp);
        if(fclose(current->fp)) {
            drawErrorMessage(4);  // Cannot close the file
            return;  // Exit the function instead of the whole program
        }
        current->fp = NULL;
    } else {
        drawErrorMessage(3);  // File open error
    }
    Window_State = MAIN_WINDOW;
}


void loadNote(NoteNode *current) {
    char filename[MAX_TITLE_LENGTH + 5];
    snprintf(filename, sizeof(filename), "%s.txt", current->title);

    if(current->fp == NULL) {
        if((current->fp = fopen(filename, "r")) == NULL) {
            drawErrorMessage(3);
            return;
        }
    } else {
        if((current->fp = fopen(filename, "r+")) == NULL) {
            drawErrorMessage(3);
            return;
        }
    }

    if(current->fp != NULL) {
        fseek(current->fp, 0, SEEK_END);
        textlen = ftell(current->fp);
        fseek(current->fp, 0, SEEK_SET);

        fread(text, 1, textlen, current->fp);
        text[textlen] = '\0';
        location = textlen;

        if(fclose(current->fp)) {
            drawErrorMessage(4);
            return;
        }
        current->fp = NULL;
    } else {
        drawErrorMessage(3);
    }
}
