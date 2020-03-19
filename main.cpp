#include "./config.cpp"
#include <cmath>
#include <stdlib.h>
using namespace std;

//functions signatures
void main_menu();
void setting_menu();
void bg_color_menu();
void bl_color_menu();
void b_back_color_menu();

struct State {
    char main_array[BOARD_SIZE][BOARD_SIZE];
    bool curr_player;
    _location curr_pos;
    bool game_over;
};
State state;

void fillCellColor(string color , int x , int y)
    {
        int factor = BOARD_SIZE/2;
    _location offset = {LINE_GAP.x + BOARD_LINE_THICKNESS.x, LINE_GAP.y + BOARD_LINE_THICKNESS.y};
    _location start = {START_POS.x - factor*offset.x - LINE_GAP.x/2, START_POS.y - factor*offset.y - LINE_GAP.y/2};
    int x1 = start.x + x*offset.x;
    int x2 = x1 + LINE_GAP.x;
    int y1 = start.y + y*offset.y;
    int y2 = y1 + LINE_GAP.y;
    clrdLine(color,x1,y1,x2,y2);
    }

//fill initial state array
void fill_array(char arr[][BOARD_SIZE], char marker){
    for(int i=0; i<BOARD_SIZE; i++)
        {
            for(int j=0; j<BOARD_SIZE; j++)
            {
                arr[i][j]=marker;
            }

        }
}

void init(){
    setBgClr(BG_CLR, true);
    setConsoleDimensions(WINDOW_SIZE.x, WINDOW_SIZE.y);
    setConsoleScrollBarVisibility(false);
    cursorVisAndSize(false);
    enableConsoleResize(false);
}

char GetArrowKeysInput(){
    while(1)
    {
    switch(getch())
    {
    case 72:
        return 'U';
    case 80:
        return 'D';
    case 75:
        return 'L';
    case 77:
        return 'R';
    case 13:
        return 'E';
    }
    }
}

void renderBoard(){

    /*int y1 = START_POS.y - LINE_GAP.y/2 - (BOARD_SIZE/2)*LINE_GAP.y - (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.y;
    int y2 = START_POS.y + LINE_GAP.y/2 + (BOARD_SIZE/2)*LINE_GAP.y + (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.y;
    int x1 = START_POS.x - LINE_GAP.x/2 - (BOARD_SIZE/2)*LINE_GAP.x - (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.x;
    int x2 = START_POS.x + LINE_GAP.x/2 + (BOARD_SIZE/2)*LINE_GAP.x + (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.x;
    clrdLine(BOARD_BG_CLR,x1,y1,x2,y2);*/

    for(int i=0; i<BOARD_SIZE+1 ; i++)
    {
        //horizontal line
        int lhy1 = START_POS.y - LINE_GAP.y/2 - (BOARD_SIZE/2 - i)*LINE_GAP.y - (BOARD_SIZE/2 + 1 - i)*BOARD_LINE_THICKNESS.y;
        int lhy2 = lhy1 + BOARD_LINE_THICKNESS.y;
        int lhx1 = START_POS.x - LINE_GAP.x/2 - (BOARD_SIZE/2)*LINE_GAP.x - (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.x;
        int lhx2 = START_POS.x + LINE_GAP.x/2 + (BOARD_SIZE/2)*LINE_GAP.x + (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.x;
        clrdLine(BOARD_CLR, lhx1, lhy1, lhx2, lhy2);

        //vertical line
        int lvy1 = START_POS.y - LINE_GAP.y/2 - (BOARD_SIZE/2)*LINE_GAP.y - (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.y;
        int lvy2 = START_POS.y + ceil(LINE_GAP.y/2.0) + (BOARD_SIZE/2)*LINE_GAP.y + (BOARD_SIZE/2 + 1)*BOARD_LINE_THICKNESS.y;
        int lvx1 = START_POS.x - LINE_GAP.x/2 - (BOARD_SIZE/2 - i)*LINE_GAP.x - (BOARD_SIZE/2 + 1 - i)*BOARD_LINE_THICKNESS.x;
        int lvx2 = lvx1 + BOARD_LINE_THICKNESS.x;
        clrdLine(BOARD_CLR, lvx1, lvy1, lvx2, lvy2);
    }
}

void printMarkerOnBoard(char marker, int x, int y){
    int factor = BOARD_SIZE/2;
    _location offset = {LINE_GAP.x + BOARD_LINE_THICKNESS.x, LINE_GAP.y + BOARD_LINE_THICKNESS.y};
    _location start = {START_POS.x - factor*offset.x, START_POS.y - factor*offset.y};

    string textBgClr = HIGHLIGHT_CLR;
    if(state.curr_pos.x != x || state.curr_pos.y != y) textBgClr = BOARD_BG_CLR;
    WriteTextAtLoc(marker, start.x + x*offset.x, start.y + y*offset.y, "White", textBgClr);
}

void stateArray2Board(){
    for(int r=0; r<BOARD_SIZE; ++r){
        for(int c=0; c<BOARD_SIZE; ++c){
            if(state.curr_pos.x != c || state.curr_pos.y != r)
                fillCellColor(BOARD_BG_CLR, c, r);
            char currMarker = state.main_array[r][c];
            if(currMarker != EMPTY_MARKER)
                printMarkerOnBoard(state.main_array[r][c], c, r);
        }
    }
}

char getCurrMarker(bool currPlayer){
    if(state.curr_player==0)
    {
        return PLAYER_1_MARKER;
    }
    else
    {
        return PLAYER_2_MARKER;
    }
}

void gameLogic(int row=BOARD_SIZE, int col=BOARD_SIZE){
    bool isDrawn = true;

    //for rows
    for(int r=0; r<row; ++r){
        char firstMarker = state.main_array[r][0];
        int hCounter = 0;
        for(int c=0; c<col; ++c){
            if(state.main_array[r][c] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][c]) break;
            else hCounter++;
        }
        if(hCounter == col){
            cout << "Row " << r << r << r << " filled!";
            state.game_over = true;
            return;
        }
    }

    //for cols
    for(int c=0; c<col; ++c){
        char firstMarker = state.main_array[0][c];
        int vCounter = 0;
        for(int r=0; r<row; ++r){
            if(state.main_array[r][c] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][c]) break;
            else vCounter++;
        }
        if(vCounter == row){
            cout << "Column " << c << " filled!";
            state.game_over = true;
            return;
        }
    }

     char firstMarker = state.main_array[1][1];

     //for left diagonal
     int ldCounter = 0;
     for(int r=0; r<row; ++r){
        if(state.main_array[r][r] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][r]) break;
            else ldCounter++;
     }
     if(ldCounter == row){
            cout << "Diagonal left filled!";
            state.game_over = true;
            return;
    }

    //for right diagonal
    int rdCounter = 0;
     for(int r=0; r<row; ++r){
        if(state.main_array[r][row-r-1] == EMPTY_MARKER) {
                isDrawn = false;
                break;
            }
            else if(firstMarker != state.main_array[r][row-r-1]) break;
            else rdCounter++;
     }
     if(rdCounter == row){
            cout << "Diagonal right filled!";
            state.game_over = true;
            return;
        }

    //check draw condition
    if(isDrawn){
        cout << "Match Drawn";
        WriteTextAtLoc("Match Drawn", 0, 0);
        state.game_over = true;
        return;
    }

    state.curr_player= !state.curr_player;
}

void getUserMove(){
    char Input=GetArrowKeysInput();
    if(Input=='U' && state.curr_pos.y > 0)
        state.curr_pos.y--;
    else if(Input=='D' && state.curr_pos.y < BOARD_SIZE-1)
        state.curr_pos.y++;
    else if(Input=='L' && state.curr_pos.x > 0)
        state.curr_pos.x--;
    else if(Input=='R' && state.curr_pos.x < BOARD_SIZE-1)
        state.curr_pos.x++;
    else if(Input=='E') {
        if(state.main_array[state.curr_pos.y][state.curr_pos.x] == EMPTY_MARKER){
            state.main_array[state.curr_pos.y][state.curr_pos.x]= getCurrMarker(state.curr_player);
             gameLogic();
        }
    }
}

void startGame(){
    fill_array(state.main_array, EMPTY_MARKER);
    state.curr_player = 0;
    state.curr_pos = {0, 0};
    state.game_over = false;

    renderBoard();
    //programlogic
    while(state.game_over == false)
        {
            //rendering board
            //renderBoard();
            fillCellColor(HIGHLIGHT_CLR, state.curr_pos.x, state.curr_pos.y);
            stateArray2Board();
            getUserMove();
        }

}

void setting_menu(){
    Menu settingMenu({"BOARD SIZE" , "BACKGROUND COLOR", "BOARD LINES COLOR" , "BOARD BACK COLOR" , "PLAYER MARKER" , "BACK"});
    system("cls");
    settingMenu.setHeading("SETTINGS");
    switch(settingMenu.drawMenu()){
    case 1 :
            cout << "FEATURE NOT INTRODUCED";
            break;
    case 2 :
        bg_color_menu();
        break;
    case 3 :
        bl_color_menu();
        break;
    case 4 :
        b_back_color_menu();
        break;
    case 5 :
        break;
    case 6 :
        main_menu();
        break;
    }

}

void bg_color_menu()
{
    system("cls");
    Menu bgClrMenu(colorNames);
    bgClrMenu.setHeading("SELECT COLOR");
    int selectedColor = bgClrMenu.drawMenu();
    if(selectedColor == colorNames.size())
        setting_menu();
    else{
    setBgClr(colorCodes[selectedColor-1],true);
    bg_color_menu();
    }

}

void bl_color_menu()
{
{
    system("cls");
    Menu blClrMenu(colorNames);
    blClrMenu.setHeading("SELECT COLOR");
    int selectedColor = blClrMenu.drawMenu();
    if(selectedColor == colorNames.size())
        setting_menu();
    else{
    BOARD_CLR=(colorCodes[selectedColor-1]);
    setting_menu();
    }
}
}

void b_back_color_menu()
{
    system("cls");
    Menu bBackClrMenu(colorNames);
    bBackClrMenu.setHeading("SELECT COLOR");
    int selectedColor = bBackClrMenu.drawMenu();
    if(selectedColor < colorNames.size())
        BOARD_BG_CLR=(colorCodes[selectedColor-1]);
    setting_menu();
}

void main_menu(){
    system("cls");
    Menu mainMenu({"Two Players" , "Player VS C.P.U" , "Settings", "Exit"});
    mainMenu.setHeading("TIK - TAK - TOE GAME");
    switch(mainMenu.drawMenu())
    {
        case 1 :
                system("cls");
                startGame();
                break;
        case 2 :
                system("cls");
                cout << "FEATURE IS NOT YET INTRODUCED";
                break;
        case 3 :
                system("cls");
                setting_menu();
                break;
        case 4 :
                break;
    }
}


int main(){
    init();
    main_menu();
}
