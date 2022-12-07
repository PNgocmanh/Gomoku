/*
Phạm Ngọc Mạnh - 1813045
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#define MAX_SIZE 15

const char HORZ = 196;
const char VERT = 179;
const char TL   = 218;
const char TM   = 194;
const char TR   = 191;
const char BL   = 192;
const char BM   = 193;
const char BR   = 217;
const int numW  = 3;
const int charW = 1;
const int numPerLine = 15;
const char VERT_START = 195;
const char VERT_END = 180;
const char VERT_MID = 197;
const string inputCommand = "Previous move/Next move/Stop [p/n/s]: ";
const string endOfHistory = "This is the end of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const string startOfGame = "This is the start of the match.\nPrevious move/Next move/Stop [p/n/s]: ";
const string invalidInput = "Illegal input, please try again: ";

enum Stone {NA, X, O};

string lineString( char left, char mid, char right, char horz, int wcell, int ncell )
{
   string result = "", cell = string( wcell, horz );
   result += left;
   for ( int i = 0; i < ncell - 1; i++ ) result += cell + mid;
   result += cell + right;
   return result;
}

void displayBoard(Stone arr[][MAX_SIZE], int size) {
    //UPPERLINE
    cout << "   ";
    for(int i = 0; i < size; i++) {
        cout << "  " << (char)(i + 'a') << " ";
    }
    cout << endl;
    cout << "   " << lineString( TL, TM, TR, HORZ, 3, numPerLine ) << "\n";

    //MIDDLE
    for(int i = 0; i < size; i++) {
        cout << setw(2) << size - i << " " << VERT;
        for(int j = 0; j < size; j++) {
            if(arr[i][j] == NA) cout << "   " << VERT;
            if(arr[i][j] == X) cout << " X " << VERT;
            if(arr[i][j] == O) cout << " O " << VERT;
        }
        cout << endl;
        if(i != size - 1) cout << "   " << lineString( VERT_START, VERT_MID, VERT_END, HORZ, 3, numPerLine ) << "\n";
    }

    //UNDERLINE
    cout << "   " << lineString( BL, BM, BR, HORZ, 3, numPerLine ) << "\n";
}

void displayBoardSimple(Stone arr[][MAX_SIZE], int size) {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++) {
            cout << arr[i][j];
        }
    }
    cout << endl;
}

int convertInt(char c){
    char arr[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o'};
    int result = -1;
    for(int i = 0; i < MAX_SIZE; ++i){
        if(arr[i] == c){
            result = i;
            break;
        }
    }
    return result;
}

bool makeMove(Stone board[][MAX_SIZE], int size, string playerMove, bool isFirstPlayerTurn){
    //BEGIN TODO
    int length = playerMove.length();
    if(length > 3 || length < 2) return false;
    int row = -1;
    int col = -1;
    if(length == 3){
        int a = playerMove[0] - '0' ;
        int b = playerMove[1] - '0' ;
        row = 15 - (a * 10 + b);
        col = convertInt(playerMove[2]);
        if(col == -1 || row > MAX_SIZE || row < 0) return false;
    } else{
        row = 15 - (playerMove[0] - '0');
        col = convertInt(playerMove[1]);
        if(col == -1 || row > MAX_SIZE || row < 0) return false;
    }
    if(isFirstPlayerTurn){
        if(board[row][col] == NA){
            board[row][col] = X;
            return true;
        } else return false;
    } else{ // Second Player Turn
        if(board[row][col] == NA){
            board[row][col] = O;
            return true;
        } else return false;
    }
    return false;
    //END TODO
}

bool hasWon(Stone board[][MAX_SIZE], int size, bool isFirstPlayerTurn) {
    //BEGIN TODO
    int result = 0;

    Stone spot = NA;
    if(isFirstPlayerTurn) spot = X;
    else spot = O;

    // rows check
    for (int i = 0; i < 15; i++) {
        int rowcheck = 0;
        for (int j = 0; j < 15; j++) {
            if (board[i][j] == spot) {
                rowcheck++;
            } else rowcheck = 0;
            if(rowcheck == 5){
                if(board[i][j+1] == spot) return false; // 6
                else if(isFirstPlayerTurn && board[i][j-5] == O && board[i][j+1] == O) return false; // chan 2 dau'
                else if(!isFirstPlayerTurn && board[i][j-5] == X && board[i][j+1] == X) return false;
                else return true;
            }
        }
    }
    
    // columns check
    for (int i = 0; i < 15; i++) {
        int colcheck = 0;
        for (int j = 0; j < 15; j++) {
            if (board[j][i] == spot){
                colcheck++;
            } else colcheck = 0;
            if(colcheck == 5){
                if(board[j+1][i] == spot) return false; // 6
                else if(isFirstPlayerTurn && board[j-5][i] == O && board[j+1][i] == O) return false; // chan 2 dau'
                else if(!isFirstPlayerTurn && board[j-5][i] == X && board[j+1][i] == X) return false;
                else return true;
            }
        }
    }

    // upper-half top-down diagonal
    // nua tren duong cheo phai
    int checkUpperTopDown = 0;
    for (int j = 0; j < 11; j++) {
        int k = j;
        for (int i = 0; i < 15; i++, k++) {
            if(board[i][k] == spot){
                checkUpperTopDown++;
            } else checkUpperTopDown =  0;
            if(checkUpperTopDown == 5){
                if(board[i+1][k+1] == spot) return false;
                else if(isFirstPlayerTurn && board[i-5][k-5] == O && board[i+1][k+1] == O) return false; // chan 2 dau'
                else if(!isFirstPlayerTurn && board[i-5][k-5] == X && board[i+1][k+1] == X) return false;
                else return true;
            }
        }
    }
    
   
    // lower-half top-down diagonal
    // nua duoi duong cheo phai
    int checkLowerTopDown = 0;
    for (int i = 0; i <= 10; i++) {
        int k = i;
        for (int j = 0; k < 15; k++, j++) {
            if (board[k][j] == spot){
                checkLowerTopDown++;
            } else checkLowerTopDown = 0;
            if(checkLowerTopDown == 5){
                if(board[k+1][j+1] == spot) return false;
                else if(isFirstPlayerTurn && board[k-5][j-5] == O && board[k+1][j+1] == O) return false; // chan 2 dau'
                else if(!isFirstPlayerTurn && board[k-5][j-5] == X && board[k+1][j+1] == X) return false;
                else return true;
            }
        }
    }
    
    // upper-half down-top diagonal
    // nua tren duong cheo trai
    int checkUpperDownTop = 0;
    for (int j = 14; j >= 0; j--) {
        int k = j;
        for (int i = 0; k >= 0; k--, i++) {
            if (board[i][k] == spot) {
                checkUpperDownTop++;
            } else checkUpperDownTop = 0;
            if(checkUpperDownTop == 5){
                if(board[i+1][k-1] == spot) return false;
                else if(isFirstPlayerTurn && board[i-5][k+5] == O && board[i+1][k-1] == O) return false; // chan 2 dau'
                else if(!isFirstPlayerTurn && board[i-5][k+5] == X && board[i+1][k-1] == X) return false;
                else return true;
            }
        }
    }
    
    // lower-half down-top diagonal
    // nua duoi duong cheo trai
    int checkLowerDownTop = 0;
    for (int i = 1; i < 15; i++) {
        int k = i;
        for (int j = 14; k < 15; k++, j--) {
            if (board[k][j] == spot) {
                checkLowerDownTop++;
            } else checkLowerDownTop = 0;
            if(checkLowerDownTop == 5){
                if(board[k+1][j-1] == spot) return false;
                else if(isFirstPlayerTurn && board[k-5][j+5] == O && board[k+1][j-1] == O) return false; // chan 2 dau'
                else if(!isFirstPlayerTurn && board[k-5][j+5] == X && board[k+1][j-1] == X) return false;
                else return true;
            }
        }
    }
    
    return result;

    // return false;
    //END TODO
}

void displayPrev(string * arr, int next, int pre, bool isFirstPlayer){
    Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    if(pre == -1){
        displayBoard(game, MAX_SIZE);
        cout << inputCommand;
        return;
    }
    int i = 0;
    while(i <= pre){
        if(makeMove(game, MAX_SIZE, arr[i], isFirstPlayer)){
            if(hasWon(game, MAX_SIZE, isFirstPlayer)) {
                displayBoard(game, MAX_SIZE);
                cout << ((isFirstPlayer) ? "Player 1 won " : "Player 2 won ");
                return;
            }
        }
        isFirstPlayer = !isFirstPlayer;
        i++;
    }
    displayBoard(game, MAX_SIZE);
    cout << inputCommand;
}

void displayNext(string * arr, int next, int pre, bool isFirstPlayer, bool& end){
    Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    int i = 0;
    while(i <= next){
        if(makeMove(game, MAX_SIZE, arr[i], isFirstPlayer)){
            if(hasWon(game, MAX_SIZE, isFirstPlayer)) {
                displayBoard(game, MAX_SIZE);
                cout << ((isFirstPlayer) ? "Player 1 won " : "Player 2 won ");
                end = true;
                return;
            }
        }
        isFirstPlayer = !isFirstPlayer;
        i++;
    }
    displayBoard(game, MAX_SIZE);
    cout << inputCommand;
}

void stepHistory(string history, string * &arr, int numOfMoves){
    int n = history.size();
    int length = 0;
    for(int i = 0; i < numOfMoves;i++){
        
        string step;
        if(history[length + 1] >= 48 && history[length + 1] <= 57){ // is number
            step = history.substr(length, 3);
            length += step.size();
        } else { // is char
            step = history.substr(length, 2);
            length += step.size();
        }
        arr[i] = step;
    }
}

void displayHistory(string history, int numOfMoves) {
    //BEGIN TODO
    /*Khai báo một mảng 2 chiều kiểu Stone (gọi là game) với kích thước 15x15 để lưu
    trữ trạng thái trận đấu. Khởi tạo các phần tử của mảng về giá trị NA.
    */
    Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    /* Hiển thị sàn đấu hiện tại thông qua hàm displayBoard với các đối số (argument)
    cần thiết để hiển thị bàn đấu trống.
    */
    displayBoard(game, MAX_SIZE);
    
    char input;
    /*tao mang luu tru cac buoc danh caro*/
    string * arr = new string[numOfMoves + 1];
    for(int i = 0; i < numOfMoves;i++){
        arr[i] = "";
    }
    stepHistory(history, arr, numOfMoves);
    int prev = -2;
    int next = -1;
    bool end = false;

    bool player1Turn = true;
    
    /*In ra màn hình chuỗi inputCommand.*/
    cout << inputCommand;
    while(cin >> input) { 
        if(input == 'n') {
            if(next == numOfMoves - 1) cout << endOfHistory;
            else {
                // move
                next++;
                prev++;
                displayNext(arr, next, prev, player1Turn, end);
            }
        }
        else if(input == 'p'){
            if(prev == -2) cout << startOfGame;
            else{
                displayPrev(arr, next, prev, player1Turn);
                next--;
                prev--;
            }
        } else if(input == 's'){
            return;
        }else {
            cout << invalidInput;
        }
        if(end) break;   
    }
    //END TODO
}

void versusComputer() {
    //BEGIN TODO

    //END TODO
}

void startGame() {
    Stone game[15][15];
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int j = 0; j < MAX_SIZE; j++) {
            game[i][j] = NA;
        }
    }
    displayBoard(game, MAX_SIZE);
    string playerMove;
    bool player1Turn = true;
    cout << "Player 1 turn: ";
    while(cin >> playerMove) {
        if(playerMove == "ff") {
            cout << ((player1Turn) ? "Player 2 won " : "Player 1 won ");
            break;
        }
        else if(makeMove(game, MAX_SIZE, playerMove, player1Turn)){
            if(hasWon(game, MAX_SIZE, player1Turn)) {
                displayBoard(game, MAX_SIZE);
                cout << ((player1Turn) ? "Player 1 won " : "Player 2 won ");
                return;
            }
            player1Turn = !player1Turn;
            displayBoard(game, MAX_SIZE);
            cout << ((player1Turn) ? "Player 1 turn: " : "Player 2 turn: ");
        } else {
            cout << "Illegal move, please try again: ";
        }
    }
}

int main()
{
    cout << "Welcome to Gomoku!" << endl;
    cout << "1. Play game" << endl;
    cout << "2. History" << endl;
    cout << "3. Play versus computer" << endl;
    cout << "4. Exit" << endl;
    cout << "Please select mode [1/2/3/4]: ";
    int mode;
    while(cin >> mode){
        if(mode == 1) {
            startGame();
            return 0;
        } else if (mode == 2) {
            int numOfMoves;
            cout << "Please enter number of moves: ";
            cin >> numOfMoves;
            string history;
            cout << "Please enter history: ";
            cin >> history;
            displayHistory(history, numOfMoves);
            return 0;
        } else if (mode == 3) {
            versusComputer();
            return 0;
        } else if (mode == 4) {
            return 0;
        } else {
            cout << "Invalid mode, please try again: ";
        }
    }

    return 0;
}