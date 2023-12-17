//http://blog.livedoor.jp/akf0/archives/51585502.html
//-lws2_32

#include <stdio.h>
#include <winsock2.h>

#define SIZE 15
int your = 1;			//自分の手を1に設定
int com = 2;			//相手の手を２に設定

/*自分の評価値の重み 適宜追加*/
int W1_1=0.9; //四四（自身が後攻のとき打てる）
int W1_2=0.8; //三四
int W1_3=0.7; //４連
int W1_4=0.5; //三三 (自身が後攻のとき打てる）
int W1_5=0.4; //三
int W1_6=0.3; //二
int W1_7=0.2; //一

/*相手の評価値の重み 適宜追加*/
int W2_1=0.8; //三四
int W2_2=0.7; //四四(相手が後攻のとき打たれる)
int W2_3=0.6; //四連
int W2_4=0.5; //三々(相手が後攻のとき打たれる)
int W2_5=0.4; //三連
int W2_6=0.3; //2連
int W2_7=0.2; //一連

// 盤の初期化(追加条項、削除不可)
void initializeBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;		//空いている場所を0に設定
        }
    }
}

//四連を判定
int checkFourInRow(int board[SIZE][SIZE], int row, int col, int player) {

    // 横方向の判定
    int count = 1;
    for (int i = 1; i < 4; i++) {
        if (col + i < SIZE && board[row][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (col - i >= 0 && board[row][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    // 縦方向の判定
    count = 1;
    for (int i = 1; i < 4; i++) {
        if (row + i < SIZE && board[row + i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0 && board[row - i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    // 斜め方向（左上から右下）の判定
    count = 1;
    for (int i = 1; i < 4; i++) {
        if (row + i < SIZE && col + i < SIZE && board[row + i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    // 斜め方向（左下から右上）の判定
    count = 1;
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0 && col + i < SIZE && board[row - i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 4; i++) {
        if (row + i < SIZE && col - i >= 0 && board[row + i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 4) {
        return 1;
    }

    return 0;
}

// 一連が成立しているかを判定する関数
int checkOneInRow(int board[SIZE][SIZE], int row, int col, int player) {
    // 横方向の判定
    if (col + 1 < SIZE && board[row][col + 1] == player) {
        return 1;
    }
    if (col - 1 >= 0 && board[row][col - 1] == player) {
        return 1;
    }

    // 縦方向の判定
    if (row + 1 < SIZE && board[row + 1][col] == player) {
        return 1;
    }
    if (row - 1 >= 0 && board[row - 1][col] == player) {
        return 1;
    }

    // 斜め方向（左上から右下）の判定
    if (row + 1 < SIZE && col + 1 < SIZE && board[row + 1][col + 1] == player) {
        return 1;
    }
    if (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] == player) {
        return 1;
    }

    // 斜め方向（左下から右上）の判定
    if (row - 1 >= 0 && col + 1 < SIZE && board[row - 1][col + 1] == player) {
        return 1;
    }
    if (row + 1 < SIZE && col - 1 >= 0 && board[row + 1][col - 1] == player) {
        return 1;
    }

    return 0;
}

// 2連が成立しているかを判定する関数
int checkTwoInRow(int board[SIZE][SIZE], int row, int col, int player) {
    // 横方向の判定
    if ((col + 1 < SIZE && board[row][col + 1] == player) ||
        (col - 1 >= 0 && board[row][col - 1] == player)) {
        return 1;
    }

    // 縦方向の判定
    if ((row + 1 < SIZE && board[row + 1][col] == player) ||
        (row - 1 >= 0 && board[row - 1][col] == player)) {
        return 1;
    }

    // 斜め方向（左上から右下）の判定
    if ((row + 1 < SIZE && col + 1 < SIZE && board[row + 1][col + 1] == player) ||
        (row - 1 >= 0 && col - 1 >= 0 && board[row - 1][col - 1] == player)) {
        return 1;
    }

    // 斜め方向（左下から右上）の判定
    if ((row - 1 >= 0 && col + 1 < SIZE && board[row - 1][col + 1] == player) ||
        (row + 1 < SIZE && col - 1 >= 0 && board[row + 1][col - 1] == player)) {
        return 1;
    }

    return 0;
}

// 三連が成立しているかを判定する関数
int checkThreeInRow(int board[SIZE][SIZE], int row, int col,int player) {
    // 横方向の判定
    int count = 1;
    for (int i = 1; i < 3; i++) {
        if (col + i < SIZE && board[row][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (col - i >= 0 && board[row][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    // 縦方向の判定
    count = 1;
    for (int i = 1; i < 3; i++) {
        if (row + i < SIZE && board[row + i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (row - i >= 0 && board[row - i][col] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    // 斜め方向（左上から右下）の判定
    count = 1;
    for (int i = 1; i < 3; i++) {
        if (row + i < SIZE && col + i < SIZE && board[row + i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (row - i >= 0 && col - i >= 0 && board[row - i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    // 斜め方向（左下から右上）の判定
    count = 1;
    for (int i = 1; i < 3; i++) {
        if (row - i >= 0 && col + i < SIZE && board[row - i][col + i] == player) {
            count++;
        } else {
            break;
        }
    }
    for (int i = 1; i < 3; i++) {
        if (row + i < SIZE && col - i >= 0 && board[row + i][col - i] == player) {
            count++;
        } else {
            break;
        }
    }
    if (count >= 3) {
        return 1;
    }

    return 0;
}

//３並び判定(追加条項、削除不可)
int checkThreeBrock(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col, int gradient){
    switch(gradient){
        case 0:     //横
            if((col-4 >= 0 && col+2 < SIZE && board[row][col-4] == SecPlayer && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == SecPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && board[row][col-3] == SecPlayer && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == SecPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && board[row][col-2] == SecPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == 0 && board[row][col+4] == SecPlayer)){
                return 0;
            }
            if((col-4 >= 0 && col+1 < SIZE && board[row][col-4] == 0 && board[row][col-3] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == 0) ||
               (col-4 >= 0 && col+1 < SIZE && board[row][col-4] == 0 && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == 0) || 
               (col-4 >= 0 && col+2 < SIZE && board[row][col-4] == 0 && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == 0) ||
               (col-3 >= 0 && col+2 < SIZE && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == 0) ||
               (col-2 >= 0 && col+3 < SIZE && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == 0) ||
               (col-3 >= 0 && col+3 < SIZE && board[row][col-3] == 0 && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && board[row][col-1] == 0 && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] == 0) ||
               (col-2 >= 0 && col+4 < SIZE && board[row][col-2] == 0 && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == 0 && board[row][col+4] == 0)) {
                return 1;
            }
            break;
        case 1:     //縦
            if((row-4 >= 0 && row+2 < SIZE && board[row-4][col] == SecPlayer && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == SecPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && board[row-3][col] == SecPlayer && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == SecPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && board[row-2][col] == SecPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == 0 && board[row+4][col] == SecPlayer)){
                return 0;
            }
            if((row-4 >= 0 && row+1 < SIZE && board[row-4][col] == 0 && board[row-3][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == 0) ||
               (row-4 >= 0 && row+1 < SIZE && board[row-4][col] == 0 && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == 0) || 
               (row-4 >= 0 && row+2 < SIZE && board[row-4][col] == 0 && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == 0) ||
               (row-3 >= 0 && row+2 < SIZE && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == 0) ||
               (row-2 >= 0 && row+3 < SIZE && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == 0) ||
               (row-3 >= 0 && row+3 < SIZE && board[row-3][col] == 0 && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == 0) ||
               (row-1 >= 0 && row+4 < SIZE && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] == 0) ||
               (row-1 >= 0 && row+4 < SIZE && board[row-1][col] == 0 && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] == 0) ||
               (row-2 >= 0 && row+4 < SIZE && board[row-2][col] == 0 && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == 0 && board[row+4][col] == 0)) {
                return 1;
            }
            break;
        case 2:     //左上から右下
            if((col-4 >= 0 && col+2 < SIZE && row-4 >= 0 && row+2 < SIZE && board[row-4][col-4] == SecPlayer && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == SecPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && row-3 >= 0 && row+3 < SIZE && board[row-3][col-3] == SecPlayer && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == SecPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && row-2 >= 0 && row+4 < SIZE && board[row-2][col-2] == SecPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0 && board[row+4][col+4] == SecPlayer)){
                return 0;
            }
            if((col-4 >= 0 && col+1 < SIZE && row-4 >= 0 && row+1 < SIZE && board[row-4][col-4] == 0 && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == 0) ||
               (col-4 >= 0 && col+1 < SIZE && row-4 >= 0 && row+1 < SIZE && board[row-4][col-4] == 0 && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0) || 
               (col-4 >= 0 && col+2 < SIZE && row-4 >= 0 && row+2 < SIZE && board[row-4][col-4] == 0 && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == 0) ||
               (col-3 >= 0 && col+2 < SIZE && row-3 >= 0 && row+2 < SIZE && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0) ||
               (col-2 >= 0 && col+3 < SIZE && row-2 >= 0 && row+3 < SIZE && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0) ||
               (col-3 >= 0 && col+3 < SIZE && row-3 >= 0 && row+3 < SIZE && board[row-3][col-3] == 0 && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row-1 >= 0 && row+4 < SIZE && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row-1 >= 0 && row+4 < SIZE && board[row-1][col-1] == 0 && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == 0) ||
               (col-2 >= 0 && col+4 < SIZE && row-2 >= 0 && row+4 < SIZE && board[row-2][col-2] == 0 && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0 && board[row+4][col+4] == 0)) {
                return 1;
            }
            break;
        case 3:     //右上から左下
            if((col-4 >= 0 && col+2 < SIZE && row+4 >= 0 && row-2 < SIZE && board[row+4][col-4] == SecPlayer && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == SecPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && row+3 >= 0 && row-3 < SIZE && board[row+3][col-3] == SecPlayer && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == SecPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && row+2 >= 0 && row-4 < SIZE && board[row+2][col-2] == SecPlayer && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0 && board[row-4][col+4] == SecPlayer)){
                return 0;
            }
            if((col-4 >= 0 && col+1 < SIZE && row+4 >= 0 && row-1 < SIZE && board[row+4][col-4] == 0 && board[row+3][col-3] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == 0 && board[row-1][col+1] == 0) ||
               (col-4 >= 0 && col+1 < SIZE && row+4 >= 0 && row-1 < SIZE && board[row+4][col-4] == 0 && board[row+3][col-3] == FstPlayer && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0) || 
               (col-4 >= 0 && col+2 < SIZE && row+4 >= 0 && row-2 < SIZE && board[row+4][col-4] == 0 && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == 0) ||
               (col-3 >= 0 && col+2 < SIZE && row+3 >= 0 && row-2 < SIZE && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0) ||
               (col-2 >= 0 && col+3 < SIZE && row+2 >= 0 && row-3 < SIZE && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0) ||
               (col-3 >= 0 && col+3 < SIZE && row+3 >= 0 && row-3 < SIZE && board[row+3][col-3] == 0 && board[row+2][col-2] == 0 && board[row+1][col-1] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row+1 >= 0 && row-4 < SIZE && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == 0) ||
               (col-1 >= 0 && col+4 < SIZE && row+1 >= 0 && row-4 < SIZE && board[row+1][col-1] == 0 && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == 0) ||
               (col-2 >= 0 && col+4 < SIZE && row+2 >= 0 && row-4 < SIZE && board[row+2][col-2] == 0 && board[row+1][col-1] == 0 && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0 && board[row-4][col+4] == 0)) {
                return 1;
            }
            break;
        default:
            break;
    }

    return 0;
}

//4並び判定(追加条項、削除不可)
int checkFourBrock(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col, int gradient){
    switch(gradient){
        case 0:     //横
            if((col-4 >= 0 && col+4 < SIZE && board[row][col-5] != FstPlayer && board[row][col-4] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == FstPlayer && 
                    board[row][col-1] == 0 && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col-3 >= 0 && col+3 < SIZE && board[row][col-4] != FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && 
                    board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col-4 >= 0 && col+3 < SIZE && board[row][col-5] != FstPlayer && board[row][col-4] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && 
                    board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col-3 >= 0 && col+4 < SIZE && board[row][col+5] != FstPlayer && board[row][col+4] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+2] == 0 && 
                    board[row][col+1] == FstPlayer && board[row][col-1] == 0 && board[row][col-2] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-4] != FstPlayer) ||
               (col-4 >= 0 && col+2 < SIZE && board[row][col-5] != FstPlayer && board[row][col-4] == FstPlayer && board[row][col-3] == 0 && board[row][col-2] == FstPlayer && 
                    board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) ||
               (col-2 >= 0 && col+4 < SIZE && board[row][col+5] != FstPlayer && board[row][col+4] == FstPlayer && board[row][col+3] == 0 && board[row][col+2] == FstPlayer && 
                    board[row][col+1] == FstPlayer && board[row][col-1] == 0 && board[row][col-2] == FstPlayer && board[row][col-3] != FstPlayer)){
                return 2; //直線上の四四禁
            }

            if((col-3 >= 0 && col+1 < SIZE && board[row][col-4] != FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] != FstPlayer) ||
               (col-3 >= 0 && col+1 < SIZE && board[row][col-4] != FstPlayer && board[row][col-3] == FstPlayer && board[row][col-2] == 0 && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] != FstPlayer) ||
               (col-2 >= 0 && col+1 < SIZE && board[row][col-3] != FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] != FstPlayer) || 
               (col-2 >= 0 && col+2 < SIZE && board[row][col-3] != FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) ||
               (col-1 >= 0 && col+3 < SIZE && board[row][col-2] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col-2 >= 0 && col+2 < SIZE && board[row][col-3] != FstPlayer && board[row][col-2] == FstPlayer && board[row][col-1] == 0 && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) ||
               (col-1 >= 0 && col+2 < SIZE && board[row][col-2] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] != FstPlayer) || 
               (col-1 >= 0 && col+3 < SIZE && board[row][col-2] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col+3 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] != FstPlayer) ||
               (col+4 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == 0 && board[row][col+3] == FstPlayer && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col+4 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == FstPlayer && board[row][col+2] == FstPlayer && board[row][col+3] == 0 && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col+4 < SIZE && board[row][col-1] != FstPlayer && board[row][col+1] == 0 && board[row][col+2] == FstPlayer && board[row][col+3] == FstPlayer && board[row][col+4] == FstPlayer && board[row][col+5] != FstPlayer) ||
               (col-3 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-4] != FstPlayer) ||
               (col-4 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col-2] == 0 && board[row][col-3] == FstPlayer && board[row][col-4] == FstPlayer && board[row][col-5] != FstPlayer) ||
               (col-4 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == FstPlayer && board[row][col-2] == FstPlayer && board[row][col-3] == 0 && board[row][col-4] == FstPlayer && board[row][col-5] != FstPlayer) ||
               (col-4 >= 0 && board[row][col+1] != FstPlayer && board[row][col-1] == 0 && board[row][col-2] == FstPlayer && board[row][col-3] == FstPlayer && board[row][col-4] == FstPlayer && board[row][col-5] != FstPlayer)) {
                return 1;
            }
            break;
        case 1:     //縦
            if((row-4 >= 0 && row+4 < SIZE && board[row-5][col] != FstPlayer && board[row-4][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == FstPlayer && 
                    board[row-1][col] == 0 && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] == FstPlayer && board[row+5][col] != FstPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && board[row-4][col] != FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && 
                    board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row-4 >= 0 && row+3 < SIZE && board[row-5][col] != FstPlayer && board[row-4][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && 
                    board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row-3 >= 0 && row+4 < SIZE && board[row+5][col] != FstPlayer && board[row+4][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+2][col] == 0 && 
                    board[row+1][col] == FstPlayer && board[row-1][col] == 0 && board[row-2][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-4][col] != FstPlayer) ||
               (row-4 >= 0 && row+2 < SIZE && board[row-5][col] != FstPlayer && board[row-4][col] == FstPlayer && board[row-3][col] == 0 && board[row-2][col] == FstPlayer && 
                    board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && board[row+5][col] != FstPlayer && board[row+4][col] == FstPlayer && board[row+3][col] == 0 && board[row+2][col] == FstPlayer && 
                    board[row+1][col] == FstPlayer && board[row-1][col] == 0 && board[row-2][col] == FstPlayer && board[row-3][col] != FstPlayer)){
                return 2; //直線上の四四禁
            }

            if((row-3 >= 0 && row+1 < SIZE && board[row-4][col] != FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] != FstPlayer) ||
               (row-3 >= 0 && row+1 < SIZE && board[row-4][col] != FstPlayer && board[row-3][col] == FstPlayer && board[row-2][col] == 0 && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] != FstPlayer) ||
               (row-2 >= 0 && row+1 < SIZE && board[row-3][col] != FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] != FstPlayer) || 
               (row-2 >= 0 && row+2 < SIZE && board[row-3][col] != FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) ||
               (row-1 >= 0 && row+3 < SIZE && board[row-2][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row-2 >= 0 && row+2 < SIZE && board[row-3][col] != FstPlayer && board[row-2][col] == FstPlayer && board[row-1][col] == 0 && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) ||
               (row-1 >= 0 && row+2 < SIZE && board[row-2][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] != FstPlayer) || 
               (row-1 >= 0 && row+3 < SIZE && board[row-2][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row+3 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] != FstPlayer) ||
               (row+4 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == 0 && board[row+3][col] == FstPlayer && board[row+4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row+4 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == FstPlayer && board[row+2][col] == FstPlayer && board[row+3][col] == 0 && board[row+4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row+4 < SIZE && board[row-1][col] != FstPlayer && board[row+1][col] == 0 && board[row+2][col] == FstPlayer && board[row+3][col] == FstPlayer && board[row+4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row-3 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-4][col] != FstPlayer) ||
               (row-4 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row-2][col] == 0 && board[row-3][col] == FstPlayer && board[row-4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row-4 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == FstPlayer && board[row-2][col] == FstPlayer && board[row-3][col] == 0 && board[row-4][col] == FstPlayer && board[row-5][col] != FstPlayer) ||
               (row-4 >= 0 && board[row+1][col] != FstPlayer && board[row-1][col] == 0 && board[row-2][col] == FstPlayer && board[row-3][col] == FstPlayer && board[row-4][col] == FstPlayer && board[row-5][col] != FstPlayer)) {
                return 1;
            }

            break;
        case 2:     //左上から右下
            if((row-4 >= 0 && row+4 < SIZE && col-4 >= 0 && col+4 < SIZE && board[row-5][col-5] != FstPlayer && board[row-4][col-4] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == FstPlayer && 
                    board[row-1][col-1] == 0 && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == FstPlayer && board[row+5][col+5] != FstPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && col-3 >= 0 && col+3 < SIZE && board[row-4][col-4] != FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && 
                    board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row-4 >= 0 && row+3 < SIZE && col-4 >= 0 && col+3 < SIZE && board[row-5][col-5] != FstPlayer && board[row-4][col-4] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && 
                    board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row-3 >= 0 && row+4 < SIZE && col-3 >= 0 && col+4 < SIZE && board[row+5][col+5] != FstPlayer && board[row+4][col+4] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+2][col+2] == 0 && 
                    board[row+1][col+1] == FstPlayer && board[row-1][col-1] == 0 && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-4][col-4] != FstPlayer) ||
               (row-4 >= 0 && row+2 < SIZE && col-4 >= 0 && col+2 < SIZE && board[row-5][col-5] != FstPlayer && board[row-4][col-4] == FstPlayer && board[row-3][col-3] == 0 && board[row-2][col-2] == FstPlayer && 
                    board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && col-2 >= 0 && col+4 < SIZE && board[row+5][col+5] != FstPlayer && board[row+4][col+4] == FstPlayer && board[row+3][col+3] == 0 && board[row+2][col+2] == FstPlayer && 
                    board[row+1][col+1] == FstPlayer && board[row-1][col-1] == 0 && board[row-2][col-2] == FstPlayer && board[row-3][col-3] != FstPlayer)){
                return 2; //直線上の四四禁
            }

            if((row-3 >= 0 && row+1 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-4][col-4] != FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] != FstPlayer) ||
               (row-3 >= 0 && row+1 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-4][col-4] != FstPlayer && board[row-3][col-3] == FstPlayer && board[row-2][col-2] == 0 && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] != FstPlayer) ||
               (row-2 >= 0 && row+1 < SIZE && col-2 >= 0 && col+1 < SIZE && board[row-3][col-3] != FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] != FstPlayer) || 
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col-3] != FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) ||
               (row-1 >= 0 && row+3 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-2][col-2] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col-3] != FstPlayer && board[row-2][col-2] == FstPlayer && board[row-1][col-1] == 0 && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) ||
               (row-1 >= 0 && row+2 < SIZE && col-1 >= 0 && col+2 < SIZE && board[row-2][col-2] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] != FstPlayer) || 
               (row-1 >= 0 && row+3 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-2][col-2] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row+3 < SIZE && col+3 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] != FstPlayer) ||
               (row+4 < SIZE && col+4 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == 0 && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row+4 < SIZE && col+4 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == FstPlayer && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == 0 && board[row+4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row+4 < SIZE && col+4 < SIZE && board[row-1][col-1] != FstPlayer && board[row+1][col+1] == 0 && board[row+2][col+2] == FstPlayer && board[row+3][col+3] == FstPlayer && board[row+4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row-3 >= 0 && col-3 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-4][col-4] != FstPlayer) ||
               (row-4 >= 0 && col-4 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row-2][col-2] == 0 && board[row-3][col-3] == FstPlayer && board[row-4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row-4 >= 0 && col-4 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == FstPlayer && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == 0 && board[row-4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row-4 >= 0 && col-4 >= 0 && board[row+1][col+1] != FstPlayer && board[row-1][col-1] == 0 && board[row-2][col-2] == FstPlayer && board[row-3][col-3] == FstPlayer && board[row-4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer)) {
                return 1;
            }

            break;
        case 3:     //右上から左下
            if((row-4 >= 0 && row+4 < SIZE && col-4 >= 0 && col+4 < SIZE && board[row-5][col+5] != FstPlayer && board[row-4][col+4] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == FstPlayer && 
                    board[row-1][col+1] == 0 && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] == FstPlayer && board[row+5][col-5] != FstPlayer) ||
               (row-3 >= 0 && row+3 < SIZE && col-3 >= 0 && col+3 < SIZE && board[row-4][col+4] != FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == 0 && 
                    board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == 0 && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row-4 >= 0 && row+3 < SIZE && col-3 >= 0 && col+4 < SIZE && board[row-5][col+5] != FstPlayer && board[row-4][col+4] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == 0 && 
                    board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row-3 >= 0 && row+4 < SIZE && col-4 >= 0 && col+3 < SIZE && board[row+5][col-5] != FstPlayer && board[row+4][col-4] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+2][col-2] == 0 && 
                    board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] != FstPlayer) ||
               (row-4 >= 0 && row+2 < SIZE && col-2 >= 0 && col+4 < SIZE && board[row-5][col+5] != FstPlayer && board[row-4][col+4] == FstPlayer && board[row-3][col+3] == 0 && board[row-2][col+2] == FstPlayer && 
                    board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) ||
               (row-2 >= 0 && row+4 < SIZE && col-4 >= 0 && col+2 < SIZE && board[row+5][col-5] != FstPlayer && board[row+4][col-4] == FstPlayer && board[row+3][col-3] == 0 && board[row+2][col-2] == FstPlayer && 
                    board[row+1][col-1] == FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] != FstPlayer)){
                return 2; //直線上の四四禁
            }

            if((row-3 >= 0 && row+1 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-4][col+4] != FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == 0 && board[row+1][col-1] == FstPlayer && board[row+2][col-2] != FstPlayer) ||
               (row-3 >= 0 && row+1 < SIZE && col-1 >= 0 && col+3 < SIZE && board[row-4][col+4] != FstPlayer && board[row-3][col+3] == FstPlayer && board[row-2][col+2] == 0 && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] != FstPlayer) ||
               (row-2 >= 0 && row+1 < SIZE && col-1 >= 0 && col+2 < SIZE && board[row-3][col+3] != FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] != FstPlayer) || 
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col+3] != FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) ||
               (row-1 >= 0 && row+3 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-2][col+2] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == 0 && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row-2 >= 0 && row+2 < SIZE && col-2 >= 0 && col+2 < SIZE && board[row-3][col+3] != FstPlayer && board[row-2][col+2] == FstPlayer && board[row-1][col+1] == 0 && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) ||
               (row-1 >= 0 && row+2 < SIZE && col-2 >= 0 && col+1 < SIZE && board[row-2][col+2] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] != FstPlayer) || 
               (row-1 >= 0 && row+3 < SIZE && col-3 >= 0 && col+1 < SIZE && board[row-2][col+2] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row+3 < SIZE && col-3 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] != FstPlayer) ||
               (row+4 < SIZE && col-4 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == 0 && board[row+3][col-3] == FstPlayer && board[row+4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row+4 < SIZE && col-4 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == FstPlayer && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == 0 && board[row+4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row+4 < SIZE && col-4 >= 0 && board[row-1][col+1] != FstPlayer && board[row+1][col-1] == 0 && board[row+2][col-2] == FstPlayer && board[row+3][col-3] == FstPlayer && board[row+4][col-4] == FstPlayer && board[row-5][col-5] != FstPlayer) ||
               (row-3 >= 0 && col+3 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] != FstPlayer) ||
               (row-4 >= 0 && col+4 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == 0 && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row-4 >= 0 && col+4 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == FstPlayer && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == 0 && board[row-4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer) ||
               (row-4 >= 0 && col+4 < SIZE && board[row+1][col-1] != FstPlayer && board[row-1][col+1] == 0 && board[row-2][col+2] == FstPlayer && board[row-3][col+3] == FstPlayer && board[row-4][col+4] == FstPlayer && board[row-5][col+5] != FstPlayer)) {
                return 1;
            }

            break;
        default:
            break;
    }

    return 0;
}

//三三禁
int sansankin(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
    int consecutiveCount = 0;
    int checker = 0;
    for(int i = 0; i < 4; i++){
        if(checkThreeBrock(board,FstPlayer, SecPlayer, row, col, i)){
            consecutiveCount++;
        }
    }
    if(consecutiveCount >=2) return 1; //禁じ手
    return 0;
}

//四四禁
int yonyonkin(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
    int consecutiveCount = 0;
    int checker = 0;
    for(int i = 0; i < 4; i++){
        checker = checkFourBrock(board,FstPlayer, SecPlayer, row, col, i);
        if(checker == 2) return 1; //禁じ手
        if(checker == 1) consecutiveCount++;
    }
    if(consecutiveCount >=2) return 1; //禁じ手
    return 0;
}

// 長連が成立しているかを判定する関数
int checkLongRen(int board[SIZE][SIZE],int player, int row, int col) {
    // 横方向
    int consecutiveCount = 0;
    for (int i = col - 5; i <= col + 5; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[row][i] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6) return 1; //禁じ手
        } else {
            consecutiveCount = 0;
        }
    }

    // 縦方向
    consecutiveCount = 0;
    for (int i = row - 5; i <= row + 5; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[i][col] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6) return 1; //禁じ手
        } else {
            consecutiveCount = 0;
        }
    }

    // 斜め方向 (左上から右下)
    consecutiveCount = 0;
    for (int i = -5; i <= 5; i++) {
        int r = row + i;
        int c = col + i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6) return 1; //禁じ手
        } else {
            consecutiveCount = 0;
        }
    }

    // 斜め方向 (右上から左下)
    consecutiveCount = 0;
    for (int i = -5; i <= 5; i++) {
        int r = row + i;
        int c = col - i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 6) return 1; //禁じ手
        } else {
            consecutiveCount = 0;
        }
    }

    return 0;
}

//禁じ手判定(追加条項、削除不可)
int checkForbiddenMoves(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
	int consecutiveCount = 0;
    int checker = 0;
	//三三禁
    consecutiveCount = sansankin(board, FstPlayer, SecPlayer, row, col);
    if(consecutiveCount == 1) return 1;

	//四四禁
    consecutiveCount = yonyonkin(board, FstPlayer, SecPlayer, row, col);
    if(consecutiveCount == 1) return 1;
    
	//長連
	consecutiveCount = checkLongRen(board, FstPlayer, row, col);
    if(consecutiveCount == 1) return 1;

	return 0;	//禁じ手なし
}

// 同時に三連と四連ができるかを判定する関数
int checkThreeAndFourInRow(int board[SIZE][SIZE], int row, int col, int player) {
    // 与えられた座標に仮の手を打つ
    board[row][col] = player;

    // 三連が成立しているか判定
    int threeInRow = checkThreeInRow(board, row, col, player);

    // 四連が成立しているか判定
    int fourInRow = checkFourInRow(board, row, col, player);

    // 与えた座標に打った駒を元に戻す
    board[row][col] = 0;

    // 同時に三連と四連ができる場合は1を返す
    return threeInRow && fourInRow;
}

int CheckScore(int Advance, int board[SIZE][SIZE], int row, int col){
    int score1 = 0; //自分の評価値
    int score2 = 0; //相手の評価値
    //自分に対する各メソッドの評価値
    int s1_1=0;//四四禁
    int s1_4=0;//三三禁
    if(Advance == 2){ //自分が後攻の場合
        s1_1 = yonyonkin(board, com , your, row, col) * W1_1; //四四
        s1_4 = sansankin(board, com, your, row, col) * W1_4; //三三
    }
    int s1_2 = checkThreeAndFourInRow(board, row , col, your) * W1_2; //三四
    int s1_3 = checkFourInRow(board, row , col, your) * W1_3; //四連
    int s1_5 = checkThreeInRow(board, row, col, your) * W1_5;//三連
    int s1_6 = checkTwoInRow(board, row, col, your) * W1_6; //二連
    int s1_7 = checkOneInRow(board, row, col, your) * W1_7; //一連

    //相手に対する各メソッドの評価値
    int s2_2=0;//四四禁
    int s2_4=0;//三三禁
    if(Advance == 1){ //相手が後攻の場合
        s2_2 = yonyonkin(board, com , your, row, col) * W2_2; //四四
        s2_4 = sansankin(board, com, your, row, col) * W2_4; //三三
    }
    int s2_1 = checkThreeAndFourInRow(board, row, col, com) * W2_1;//三四
    int s2_3 = checkFourInRow(board, row , col, com) * W2_3;//四連
    int s2_5 = checkThreeInRow(board, row, col, com) * W2_5;//三連
    int s2_6 = checkTwoInRow(board, row, col, com) * W2_6; //二連
    int s2_7 = checkOneInRow(board, row, col, com) * W2_7; //一連

    //各scoreでの総計
    score1 = s1_1 + s1_2 + s1_3 + s1_4 + s1_5 + s1_6 + s1_7;
    score2 = s2_1 + s2_2 + s2_3 + s2_4 + s2_5 + s2_6 + s2_7;

    //総scoreの集計
    int score = score1 + score2;
    return score;
}

// 引き分け判定(追加条項、削除不可)
int checkDraw(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0; // ボードがまだ埋まっていない
            }
        }
    }
    return 1; // ボードが埋まっている
}

//勝利判定(追加条項、削除不可)
int checkWin(int board[SIZE][SIZE], int player, int row, int col) {
    int consecutiveCount = 0;

    // 横方向
    for (int i = col - 4; i <= col + 4; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[row][i] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    // 縦方向
    consecutiveCount = 0;
    for (int i = row - 4; i <= row + 4; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[i][col] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    // 斜め方向 (左上から右下)
    consecutiveCount = 0;
    for (int i = -4; i <= 4; i++) {
        int r = row + i;
        int c = col + i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    // 斜め方向 (右上から左下)
    consecutiveCount = 0;
    for (int i = -4; i <= 4; i++) {
        int r = row + i;
        int c = col - i;
        if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) continue;
        if (board[r][c] == player) {
            consecutiveCount++;
            if (consecutiveCount == 5) return 1; // 勝利
        } else {
            consecutiveCount = 0;
        }
    }

    return 0; // 勝利なし
}

// 最善手を調査し出力する関数
int getNextIndex(int Advance, int board[SIZE][SIZE]){
    int maxIndexRow = 0; //評価値が最大の手の行番号
    int maxIndexCol = 0; //評価値が最大の手の列番号
    int maxScore = 0; //最大評価値
    int result[2] = {0,0}; //最大の評価値を取る配列の行列番号(index)を格納

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] == 0){//盤面が空の場合
                int row = i;
                int col = j;
                // 禁じ手の判断(追加事項、削除不可)
                if(Advance == com && checkForbiddenMoves(board, com, your, row, col) == 1){
                    continue;
                }

                //最善手調査
                //自分の勝利判断
                if(checkWin(board, your, row, col)){
                    result[0] = row;
                    result[1] = col;
                    return result;
                }
                //相手の勝利判断
                if(checkWin(board, com, row, col)){
                    result[0] = row;
                    result[1] = col;
                    return result;
                }
                if(Advance = 1 && checkLongRen(board, com, row, col) == 1){///相手が後攻で、長連を作れる場合
                    result[0] = row;
                    result[1] = col;
                    return result;
                }
                //累積評価値の算出
                int score = CheckScore(Advance, board, row, col); //評価値の計算
                if (score > maxScore) {
                    result[0] = row;
                    result[1] = col;
                    maxScore = score;
                }
                result[0] = maxIndexRow;
                result[1] = maxIndexCol;
            }continue; //盤面が1or2の場合
            
        }
    }
    return result;

}

int main(void) {	

	//接続するサーバの情報の構造体を用意

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//サーバの情報を入力

	char destination[100];  //アドレス
	int port;		//ポート番号

	printf("アドレスを入力してください");
	scanf("%s", destination);
	printf("ポート番号を入力してください");
	scanf("%d", &port);
	dest.sin_port = htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(destination);



	//ソケット通信の準備・生成
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	//サーバへの接続
	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {
		printf("%sに接続できませんでした\n", destination);
		return -1;

	}

	printf("%sに接続しました\n", destination);
	
	char msg[1024];
	char buffer[1024];
	int board[SIZE][SIZE];	//盤の作成
	initializeBoard(board);	//盤の初期化

	boolean isFirst = TRUE;	//名前入力かどうかの判定
	int Advance;		//先攻かどうか
	int row, col;			//打った手の位置

	//先攻か後攻か(追加条項、削除不可)
	if(port == 12345){
		Advance = your;		//自身が先攻
	}else{
		Advance = com;	//自身が後攻
	}

	//サーバからデータを受信
	recv(s, buffer, 1024, 0);
	printf("→ %s\n\n", buffer);

	while(1){
		char buffer2[1024];
		
		if(isFirst){
			//名前の入力
			printf("送信メッセージを入力(qで終了)");
			scanf("%s", msg);
			if(msg[0] == 'q' || msg[0] == 'Q'){
				break;
			}
            isFirst = FALSE;
		}else{
			// 相手の手を代入(追加事項、削除不可)
			if(strcmp(buffer2, "start") != 0){
                sscanf(buffer2, "%d,%d", &row, &col);
				row--;
				col--;
				board[row][col] = com;
			}
			
			// 禁じ手の判断(追加事項、削除不可)
			if(Advance == com && checkForbiddenMoves(board, com, your, row, col) == 1){
				const char Forbidden[1024] = "Yuor hands is Forbidden";
				send(s, Forbidden, strlen(Forbidden), 0);
				break;
			}

			// 引き分け判断(追加条項、削除不可)
			if (checkDraw(board)) {
				const char drow[1024] = "The game is a draw!";
				send(s, drow, strlen(drow), 0);
				break;
			}

			//自分の手を決定(今後変更)
			int *nextpoint = getNextIndex(Advance, board);
            sprintf(msg, "%d,%d", nextpoint[0], nextpoint[1]);

			//勝利判断(今後追加)
			if(checkWin(board, your, row, col)){
                sprintf(msg, "%d,%d,win", nextpoint[0], nextpoint[1]);
            }

		}
		//サーバにデータを送信
		send(s, msg, strlen(msg), 0);

		//サーバからデータを受信
        memset(buffer2, 0, sizeof(buffer2));
		recv(s, buffer2, 1024, 0);
		printf("→ %s\n\n", buffer2);
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();
	return 0;

}