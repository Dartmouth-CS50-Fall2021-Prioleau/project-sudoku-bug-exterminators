#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main(){
    // ds
    int*** board = malloc(sizeof(int**) * 3);
    for(int i=0; i<3; i++){
        board[i] = malloc(sizeof(int*)*3);
    }

    // read from stdin
    char c;
    int c_number;
    int row = 0;
    int col = 0;

    while((c = getchar()) != EOF){
        if(isdigit(c) || c == '.'){
            c_number = c == '.' ? 0 : c - '0';
            
            board[row][col] = malloc(sizeof(int));

            *(board[row][col]) = c_number;

            col++;
            if(col >= 3){
                row++;
                col = 0;
            }
        }
    }

    return 0;
}