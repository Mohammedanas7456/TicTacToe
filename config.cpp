#include <iostream>
#include "./console_formatting.h"
#include <vector>

string BG_CLR = "Blue";
string BOARD_CLR = "L Blue";
string BOARD_BG_CLR = "Black";
string HIGHLIGHT_CLR = "Red";
string MARKERCLR = "White";
_location WINDOW_SIZE = {80, 41};
_location START_POS = {WINDOW_SIZE.x/2, WINDOW_SIZE.y/2};
_location BOARD_LINE_THICKNESS = {2,1};
_location LINE_GAP = {5,3};
int BOARD_SIZE = 3;

char PLAYER_1_MARKER='X';
char PLAYER_2_MARKER='O';
char EMPTY_MARKER=' ' ;


vector<string> colorCodes = {"Black","Blue","Green","Cyan","Red","Purple","Yellow","White","Gray","L Blue","L Green",
                        "L Cyan", "L Red", "L Purple", "L Yellow", "Bright White"};
vector<string> colorNames = {"Black","Blue","Green","Cyan","Red","Purple","Yellow","White","Gray","Light Blue","Light Green",
                        "Light Cyan", "Vermillion", "Light Purple", "Light Yellow", "Bright White", "Back"};
vector<string> MARKERSTRING = {"O" , "X" , "?" , "#" , "$" , "*" , "@"};
