#include "global.h"

void saveNewNoteTitle(char *title, char *category) {
    if (strlen(title) > 0 && strlen(title) <= MAX_TITLE_LENGTH - 1) {
        // Create a new node
        NoteNode *newNode = (NoteNode *) malloc(sizeof(NoteNode));
		if (newNode == NULL) {
		    drawErrorMessage(2); // Handle memory allocation error
		    return;
		}
        strncpy(newNode->title, title, MAX_TITLE_LENGTH - 1);
        strncpy(newNode->category, category, MAX_TITLE_LENGTH - 1);
        newNode->title[MAX_TITLE_LENGTH - 1] = '\0';
        newNode->category[MAX_TITLE_LENGTH - 1] = '\0';
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

