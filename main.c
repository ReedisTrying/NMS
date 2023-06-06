#include "main.h"

NoteNode *note_head = NULL;
enum WindowState Window_State = MAIN_WINDOW;
char titleInput[MAX_TITLE_LENGTH]="";
char categoryInput[MAX_TITLE_LENGTH]="";
string category[10];

void drawMainWindow() {
    double wh = GetWindowHeight();
    double ww = GetWindowWidth();
    double NOTE_SPACING = wh /3 /MAX_NOTES;
    double LINE_HEIGHT = wh / 4 * 3;

    SetPenColor("Black");      // Draw"Notebook" title
    MovePen(ww / 6, LINE_HEIGHT + NOTE_SPACING);
    DrawTextString("Notebook Management System");


    MovePen(ww / 6, LINE_HEIGHT); // Draw dividing line
    DrawLine(ww * 2/3, 0);

    // Display the list of notes
    NoteNode *current = note_head;
    int i = 0;
    while (current) {
        MovePen(ww / 6, LINE_HEIGHT - (i+1) * NOTE_SPACING);
        DrawTextString(current->title);
        MovePen(ww * 5 / 6 - TextStringWidth(current->category), LINE_HEIGHT - (i+1) * NOTE_SPACING);
        DrawTextString(current->category);
        current = current->next;
        i++;
    }

    if (button(GenUIID(0), ww * 5 / 6 - ww / 9, LINE_HEIGHT + NOTE_SPACING, ww / 20, wh /20, "+")) {  //Add button
        Window_State = NEW_NOTE_WINDOW;
        refreshScreen();
    }

    if (button(GenUIID(0), ww * 5 / 6 - ww / 20, LINE_HEIGHT + NOTE_SPACING, ww / 20, wh / 20, "X")) {  //exit button
        exit(0);
    }



}

void drawNewNoteWindow() {
    if (noteCount >= MAX_NOTES) {
        Window_State = MAIN_WINDOW;
        drawErrorMessage(1);
        refreshScreen();
        return;
    }
    double titleX = windowsWidth / 2 - TextStringWidth("New Note") / 2;
	drawLabel(titleX, windowsHeight - 1.25, "New Note");
	//title
	double noteTitleLabelX = windowsWidth / 2 - TextStringWidth("Note Title:") / 2;
	drawLabel(noteTitleLabelX, windowsHeight - 2.5, "Note Title:");

    double noteTitleTextboxX = windowsWidth / 2 - TextStringWidth("xxxxxxxx") / 2 * 3;
    textbox(GenUIID(0), noteTitleTextboxX, windowsHeight - 2.8, TextStringWidth("xxxxxxxx") * 3, fontHeight * 1.5, titleInput, MAX_TITLE_LENGTH);
    //category
    double noteCategoryLabelX = windowsWidth / 2 - TextStringWidth("Note Category:") / 2;
	drawLabel(noteCategoryLabelX, windowsHeight - 3, "Note Category:");

    textbox(GenUIID(0), noteTitleTextboxX, windowsHeight - 3.3, TextStringWidth("xxxxxxxx") * 3, fontHeight * 1.5, categoryInput, MAX_TITLE_LENGTH);
	//save
    double saveButtonX = windowsWidth / 2 - 1.2;
    if (button(GenUIID(0), saveButtonX, windowsHeight - 4, TextStringWidth("Save") + 0.2, fontHeight + 0.2, "Save")) {
        saveNewNoteTitle(titleInput, categoryInput);
    }

    double cancelButtonX = windowsWidth / 2 + 0.6;
    if (button(GenUIID(0), cancelButtonX, windowsHeight - 4, TextStringWidth("Cancel") + 0.2, fontHeight + 0.2, "Cancel")) {
        Window_State = MAIN_WINDOW;
    }
}

void drawErrorMessage(int errorID) {
	errorCode = errorID;
    char *errorMessage;
    switch (errorCode) {
        case 1:
            errorMessage = "Too many notes";
			startTimer(TIMER_ERRORMESSAGE, 3000);
            break;
        case 2:
            errorMessage = "Memory allocation failed";
			startTimer(TIMER_ERRORMESSAGE, 3000);
            break;
        default:
            return;
    }
    double stringWidth = TextStringWidth(errorMessage);
    double stringX = (GetWindowWidth() - stringWidth) / 2;
    double stringY = GetWindowHeight() / 2;
    MovePen(stringX, stringY);
    DrawTextString(errorMessage);
}

void drawEditNoteWindow(){

}

void drawIntroWindow(){
	double titleX = windowsWidth / 2 - TextStringWidth("This is a note management system.") / 2;
	drawLabel(titleX, windowsHeight - 1.25, "This is a note management system.");

    double cancelButtonX = windowsWidth / 2 - 0.5*(TextStringWidth("Back") + 0.2);
    if (button(GenUIID(0), cancelButtonX, windowsHeight - 4, TextStringWidth("Back") + 0.2, fontHeight + 0.2, "Back")) {
        Window_State = MAIN_WINDOW;
    }
}

void drawFindWindow(){
	double wh = GetWindowHeight();
    double ww = GetWindowWidth();
    double NOTE_SPACING = wh /3 /MAX_NOTES;
    double LINE_HEIGHT = wh / 4 * 3;

    SetPenColor("Black");      // Draw"Notebook" title
    MovePen(ww / 6, LINE_HEIGHT + NOTE_SPACING);
    DrawTextString("Find");


    MovePen(ww / 6, LINE_HEIGHT); // Draw dividing line
    DrawLine(ww * 2/3, 0);

    double noteTitleTextboxX = ww * 1/6 ;
    textbox(GenUIID(0), noteTitleTextboxX, windowsHeight - 0.6, TextStringWidth("xxxxx")*10, fontHeight * 1.5, titleInput, MAX_TITLE_LENGTH);

    double findButtonX = ww * 5/6 - (TextStringWidth("Find") + 0.2);
    if (button(GenUIID(0), findButtonX, windowsHeight - 0.6, TextStringWidth("Find") + 0.2, fontHeight * 1.5, "Find")) {
        findNote(titleInput);
    }

	double backButtonX = ww * 5/6 - (TextStringWidth("Back") + 0.2);
	if (button(GenUIID(0), backButtonX, windowsHeight - 4.5, TextStringWidth("Back") + 0.2, fontHeight * 1.5, "Back")) {
        Window_State = MAIN_WINDOW;
    }

}


void KeyboardEventProcess(int key, int event) {
    switch (event) {
        case KEY_DOWN:
            switch (Window_State) {
                case NEW_NOTE_WINDOW:
                    if (key == VK_RETURN) {
                        if (strlen(titleInput) > 0) {
                            saveNewNoteTitle(titleInput, categoryInput);
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

    refreshScreen();
}

void timerEventProcess(int timerID) {
	if (timerID == TIMER_ERRORMESSAGE) {
        errorCode = 0;
		Window_State = MAIN_WINDOW;
		cancelTimer(TIMER_ERRORMESSAGE);
        refreshScreen();
    }
}

void drawMenu(){
	double wh = GetWindowHeight();
    double ww = GetWindowWidth();

    drawMenuBar(0, wh-fontHeight * 1.5, ww, fontHeight * 1.5);

	char * File[] = {"File",
		"Close"};
	char * Option[] = {"Option",
		"Find"};
	char * View[] = {"View"};
	char * Help[] = {"Help",
		"Help"};
	int selection1;
	int selection2;
	int selection3;
	int selection4;

	selection1 = menuList(GenUIID(0), 0, wh-fontHeight * 1.5, ww*1/10, ww*1/10, fontHeight * 1.5, File, sizeof(File)/sizeof(File[0]));
	selection2 = menuList(GenUIID(0), ww*1/10, wh-fontHeight * 1.5, ww*1/10, ww*1/10, fontHeight * 1.5, Option, sizeof(Option)/sizeof(Option[0]));
	selection3 = menuList(GenUIID(0), ww*2/10, wh-fontHeight * 1.5, ww*1/10, ww*1/10, fontHeight * 1.5, View, sizeof(View)/sizeof(View[0]));
	selection4 = menuList(GenUIID(0), ww*3/10, wh-fontHeight * 1.5, ww*1/10, ww*1/10, fontHeight * 1.5, Help, sizeof(Help)/sizeof(Help[0]));

	if( selection1 == 1 ){
		exit(-1);
	}
	if( selection4 == 1 ){
		Window_State = INTRO_WINDOW;
        refreshScreen();
	}

	if( selection2 == 1 ){
        Window_State = FIND_WINDOW;
        refreshScreen();
    }
}

void drawContent() {
    switch (Window_State) {
        case MAIN_WINDOW:
            drawMainWindow();
            break;
        case NEW_NOTE_WINDOW:
            drawNewNoteWindow();
            break;
        case EDIT_NOTE_WINDOW:
            drawEditNoteWindow();
            break;
        case INTRO_WINDOW:
            drawIntroWindow();
            break;
        case FIND_WINDOW:
            drawFindWindow();
            break;
    }
}


void windowsInit() {
    SetWindowTitle("Notebook Management System");
    SetWindowSize(8, 5);
    InitGraphics();

    usePredefinedMenuColors(4);
    usePredefinedButtonColors(4);
    usePredefinedTexBoxColors(4);

}

void refreshScreen() {
    DisplayClear();
    windowsWidth = GetWindowWidth();
    windowsHeight = GetWindowHeight();
    fontHeight = GetFontHeight();
    drawContent();
    if (Window_State == MAIN_WINDOW || Window_State != NULL)
        drawMenu();
	if (errorCode) {
        drawErrorMessage(errorCode);
    }
}


void Main() {
	windowsInit();

    registerKeyboardEvent(KeyboardEventProcess);
    registerCharEvent(CharEventProcess);
    registerMouseEvent(MouseEventProcess);
	registerTimerEvent(timerEventProcess);
}

void noteTitleClick(int index) {
    if (index >= 0 && index < noteCount) {
        // Open the note in a new window to edit
    }
}

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
//find
void findNote(char *text) {
	double wh = GetWindowHeight();
    double ww = GetWindowWidth();
    double NOTE_SPACING = wh /3 /MAX_NOTES;
    double LINE_HEIGHT = wh / 4 * 3;
    NoteNode *current = note_head;
    int i = 0;
    while (current) {
        if(strcmp(current->title,text) == 0){
            MovePen(ww / 6, LINE_HEIGHT - (i+1) * NOTE_SPACING);
            DrawTextString(current->title);
            MovePen(ww * 5 / 6 - TextStringWidth(current->category), LINE_HEIGHT - (i+1) * NOTE_SPACING);
            DrawTextString(current->category);
        }
        current = current->next;
        i++;
    }

}
