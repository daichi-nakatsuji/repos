//http://blog.livedoor.jp/akf0/archives/51585502.html
//-lws2_32

#include <stdio.h>
#include <winsock2.h>

#define SIZE 15

// 盤の初期化(追加条項、削除不可)
void initializeBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;		//空いている場所を0に設定
        }
    }
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

//禁じ手判定(追加条項、削除不可)
int checkForbiddenMoves(int board[SIZE][SIZE], int FstPlayer, int SecPlayer, int row, int col){
	int consecutiveCount = 0;
    int checker = 0;
	//三三禁
    for(int i = 0; i < 4; i++){
        if(checkThreeBrock(board,FstPlayer, SecPlayer, row, col, i)){
            consecutiveCount++;
        }
    }
    if(consecutiveCount >=2) return 1; //禁じ手

	//四四禁
    consecutiveCount = 0;
    for(int i = 0; i < 4; i++){
        checker = checkFourBrock(board,FstPlayer, SecPlayer, row, col, i);
        if(checker == 2) return 1; //禁じ手
        if(checker == 1) consecutiveCount++;
    }
    if(consecutiveCount >=2) return 1; //禁じ手

	//長連
	// 横方向
    consecutiveCount = 0;
    for (int i = col - 5; i <= col + 5; i++) {
        if (i < 0 || i >= SIZE) continue;
        if (board[row][i] == FstPlayer) {
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
        if (board[i][col] == FstPlayer) {
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
        if (board[r][c] == FstPlayer) {
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
        if (board[r][c] == FstPlayer) {
            consecutiveCount++;
            if (consecutiveCount == 6) return 1; //禁じ手
        } else {
            consecutiveCount = 0;
        }
    }

	return 0;	//禁じ手なし
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
	int your = 1;			//自分の手を1に設定
	int com = 2;			//相手の手を２に設定

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
			printf("送信メッセージを入力(qで終了)");
			scanf("%s", msg);
			if(msg[0] == 'q' || msg[0] == 'Q'){
				break;
			}

			//勝利判断(今後追加)
			

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