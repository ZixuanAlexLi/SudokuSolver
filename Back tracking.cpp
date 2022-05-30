#include <iostream>
#include <cstring>
using namespace std;

int board[9][9];
bool in(int x, string y){ ///This function can indicate whether a string is in another string. For example, "ersonal" is in "Personal_project" while "ersa" is not. 
    for (int i = 0; i < y.size(); i ++){
        if (x == y[i] - 48){
            return false;
        }
    }
    return true;
}
string State_restrictions(int x, int y){ //This function can state restrictions to a singular block with index (x,y).
    string restrict = "";
    for (int i = 0; i < 9; i ++){ //Add the unavailable numbers forbitted by its column to the outputed string from this function. 
        if (in(board[y][i], restrict)){
            restrict += to_string(board[y][i]);
        }
    }
    for (int i = 0; i < 9; i ++){ //Add the unavailable numbers forbitted by its row to the outputed string from this function. 
        if (in(board[i][x], restrict)){
            restrict += to_string(board[i][x]);
        }
        
    }
    int a = x % 3;
    int b = y % 3;
    for (int i = 0; i < 9; i ++){ //Add the unavailable numbers forbitted by its corresponding 3 by 3 box to the outputed string from this function. 
        if (in(board[y + i /3 - b][x + i%3 - a], restrict)){
            restrict += to_string(board[y + i /3 - b][x + i%3 - a]);
        }
    }
    return restrict;
}

bool solve(){
    for (int y = 0 ; y < 9; y ++){
        for (int x = 0; x < 9; x ++){ 
            if (board[y][x] == 0){ //This if statement only allow empty boxes passing through. Prevent assigned values inputted from being motified. 
                string res;
                int test[9], testc = 0;
                res = State_restrictions(x, y); //Forbitted values.
                for (int i = 1; i <= 9; i ++){ //Which number from 1-9 are still eligible for testing. 
                    if (in (i, res)){
                        test[testc] = i;
                        testc ++;
                    }
                }
                for (int i = 0; i < testc; i ++){ //Guess and check all of the possible outcome to the current box. 
                    board[y][x] = test[i]; 
                    if (solve()){ // Move to the next box. 
                        return true;
                    }
                    else{
                        board[y][x] = 0; 
                    }
                }
                return false; // If there aren't any possible testing values, the sudoku will retreat to another possible outcome before.
            }
        }
    }
    return true; 
}
int main(){
    for (int i = 0; i < 81; i ++){ //Acess the input, storge the input in to a 2D array. 
        cin>>board[i/9][i%9];
    }
    solve(); //Complete the sudoku. 
    cout<<endl;
    for (int i = 0; i < 9; i ++){ //Output the values inside the sudoku board. 
        for (int j = 0; j < 9; j ++){
            cout<<board[i][j]<<' ';
        }
        cout<<endl;
    }

    return 0;
}
//Below are the two test cases.

// 0 0 0 0 0 3 6 0 0
// 0 3 1 6 4 2 8 0 0
// 0 0 7 0 9 0 0 0 4
// 0 0 0 4 0 7 0 9 8
// 0 0 0 5 0 0 0 0 6
// 0 0 6 0 0 0 7 0 2
// 0 9 0 0 0 0 5 0 7
// 0 4 2 0 1 0 0 0 0
// 6 7 0 9 0 8 4 0 0

// 5 3 0 0 7 0 0 0 0
// 6 0 0 1 9 5 0 0 0
// 0 9 8 0 0 0 0 6 0
// 8 0 0 0 6 0 0 0 3
// 4 0 0 8 0 3 0 0 1
// 7 0 0 0 2 0 0 0 6
// 0 6 0 0 0 0 2 8 0
// 0 0 0 4 1 9 0 0 5
// 0 0 0 0 8 0 0 7 9