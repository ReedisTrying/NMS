#include "global.h"
double fontHeight;
bool InitEdit = 0;
double InitX;
double InitY;


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
    ww = GetWindowWidth();
    wh = GetWindowHeight();
    fontHeight = GetFontHeight();
    drawContent();
	if (errorCode) {
        drawErrorMessage(errorCode);
    }
}

void drawMainWindow() {
;
    double NOTE_SPACING = wh /3 /MAX_NOTES;
    double LINE_HEIGHT = wh / 4 * 3;
    double titleX = ww / 6;

    SetPenColor("Black");      // Draw"Notebook" title
    MovePen(ww / 6, LINE_HEIGHT + NOTE_SPACING);
    DrawTextString("Notebook Management System");
	
	
    MovePen(ww / 6, LINE_HEIGHT); // Draw dividing line
    DrawLine(ww * 2/3, 0);

    // Display the list of notes
    NoteNode *current = note_head;
    int i = 0;
    while (current) {
    	if (curyy != -1 && curyy == current->titleY){
    		 drawRectangle(titleX, current->titleY, ww - 2 * titleX, GetFontHeight(), 0);
		} // draw gray blackground - GetFontHeight()
    	
        MovePen(ww / 6, LINE_HEIGHT - (i+1) * NOTE_SPACING);
        DrawTextString(current->title);
        current->titleY = LINE_HEIGHT - (i+1) * NOTE_SPACING; // Update the Y coordinate
        
		double titleWidth = TextStringWidth(current->title);
        MovePen(ww / 6, LINE_HEIGHT - (i+1) * NOTE_SPACING);  // use GetFontHeight() to calculate line position
        DrawLine(titleWidth, 0);
        
        current = current->next;
        i++;
    }
    
    if (button(GenUIID(0), ww * 5 / 6 - ww / 9, LINE_HEIGHT + NOTE_SPACING, ww / 20, wh /20, "+")) {  //Add button
        Window_State = NEW_NOTE_WINDOW;
    }
    
    if (button(GenUIID(0), ww * 5 / 6 - ww / 20, LINE_HEIGHT + NOTE_SPACING, ww / 20, wh / 20, "X")) {  //exit button 
        exit(0);
    }   
}

void drawNewNoteWindow() {
	wh = GetWindowHeight();
    ww = GetWindowWidth();
    if (noteCount >= MAX_NOTES) {
        Window_State = MAIN_WINDOW;
        drawErrorMessage(1);
        return; 
    }
    double titleX = ww / 2 - TextStringWidth("New Note") / 2;
	drawLabel(titleX, wh - 1.25, "New Note");

	double noteTitleLabelX = ww / 2 - TextStringWidth("Note Title:") / 2;
	drawLabel(noteTitleLabelX, wh - 2.5, "Note Title:");
    
    double noteTitleTextboxX = ww / 2 - TextStringWidth("xxxxxxxx") / 2 * 1.6;
    textbox(GenUIID(0), noteTitleTextboxX, wh - 2.8, TextStringWidth("xxxxxxxx") * 1.6, fontHeight * 1.5, titleInput, MAX_TITLE_LENGTH);
    
    double saveButtonX = ww / 2 - 1.2;
    if (button(GenUIID(0), saveButtonX, wh - 4, TextStringWidth("Save") + 0.2, fontHeight + 0.2, "Save")) {
        saveNewNoteTitle(titleInput);
    }//GenUIID(0)
    
    double cancelButtonX = ww / 2 + 0.6;
    if (button(GenUIID(0), cancelButtonX, wh - 4, TextStringWidth("Cancel") + 0.2, fontHeight + 0.2, "Cancel")) {
        Window_State = MAIN_WINDOW;
    }
    
}

void drawEditNoteWindow(NoteNode *current){
	wh = GetWindowHeight();
    ww = GetWindowWidth();
	
    if (!InitEdit){  //InitText
		resetText();
		InitX = ww / 2;
		InitY = wh / 2 - GetFontHeight();
		currentX = InitX;
	}
    InitEdit = 1; 
	
    if(current->fp != NULL) {
		loadNotes(currentNode); //calculate position based on saved version
    	DrawTextString(text);
    }
    else{
    	drawLabel(InitX,InitY,text); // involve move pen
	}
    
    drawCursor(); //isDisplay deleted
    if(!isBlink) {
        isBlink = 1;
        startTimer(TIMER_BLINK, MILLISECONDS);
    } 

    if (button(GenUIID(0), ww - ww / 6, wh * 9 / 10 , ww / 20, wh /20, "Save")) {  //Save button 
        isBlink = 0;
        cancelTimer(TIMER_BLINK);
        Window_State = MAIN_WINDOW;
        saveNote(currentNode);
        InitEdit = 0;
    }
    
    if (button(GenUIID(0), ww - ww / 10, wh * 9 / 10, ww / 20, wh / 20, "X")) {  //exit button 
        isBlink = 0;
        cancelTimer(TIMER_BLINK);
        Window_State = MAIN_WINDOW;
        InitEdit = 0;
    }
    
    if (button(GenUIID(0), ww / 10, wh * 9 / 10, ww / 20, wh / 20, "Delete")) {  //delete note button 
        deleteNoteNode(currentNode);
        cancelTimer(TIMER_BLINK);
        Window_State = MAIN_WINDOW;
        InitEdit = 0;
    }
}

void resetText() {
    // If text is not NULL, free it
    if (text != NULL) {
        free(text);
        text = NULL;
    }
    text = malloc(buffersize * sizeof(char));
    
    if (text == NULL) {
        drawErrorMessage(2);
        Window_State = MAIN_WINDOW;
        exit(1);
    }
    
    // Initialize the buffer to be empty
    text[0] = '\0';
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
        case 3:
            errorMessage = "File open error!";
            startTimer(TIMER_ERRORMESSAGE, 3000);
            break;
        case 4:
            errorMessage = "Cannot close the file!";
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

void drawCursor() {
    double x, y;
    bool erasemode;
    double charWidth = 0;
    char lastChar[2] = {'\0', '\0'};

    if (location > 0 && location <= textlen) {
        char lastChar[2] = {text[location-1], '\0'};
        charWidth = TextStringWidth(lastChar);
    }
	
	//Debug for calculation last char
	FILE *logFile = fopen("log136.txt", "a");
	if(logFile == NULL) {
    	fprintf(stderr, "Error opening log file\n");
    	exit(1);
	}
	fprintf(logFile, "location: %d, textlen: %d, lastchar: %c\n", location, textlen, lastChar[0]);
	fclose(logFile);
	
    x = currentX + curOp * charWidth;
    currentX = x;
    curOp = 0;
    y = InitY;

    erasemode = GetEraseMode(); // Redraw cursor if necessary
    SetEraseMode(isDisplay);
    MovePen(x, y);
    DrawTextString("_");
    SetEraseMode(erasemode); 
}
	/*if (location < textlen) {
        char str[2] = {0, 0};
        str[0] = text[location];
        SetEraseMode(FALSE);
        DrawTextString(str);
    }*/
    
void drawContent() {
    switch (Window_State) {
        case MAIN_WINDOW:
            drawMainWindow();
            break;
        case NEW_NOTE_WINDOW:
            drawNewNoteWindow();
            break;
        case EDIT_NOTE_WINDOW:
        	drawEditNoteWindow(currentNode);//
        	break;
    }
}

void drawMenu(){
	;
}
