
 // Program uses backtracking algorithm to solve any sudoku puzzle
 // Input a text file that contains a incomplete sudoku board
 // Outputs the initial puzzle and then the solved puzzle 

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


// Function prints out the sudoku board(2d array)

void printBoard(int board[][9], int r, int c) {
    for (int i = 0; i < r; i++) {
        if (i % 3 == 0) {
            cout << setfill('-') << setw(25) << "-" << endl;
        }
        for (int j = 0; j < c; j++) {
            if (j % 3 == 0) {
                // lines used to make formatting nice like a grid
                cout << "| ";   
            }
            // blank spaces in the board are represented by dashes
            if (board[i][j] == 0) {
                cout << "- "; 
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << "|" << endl;
    }

    cout << setfill('-') << setw(25) << "-" << endl;

}

// Function to check if number is already in the board in any row, column, or 3x3 grid

bool validNumber (int board[][9], int r, int c, int number) {
    // variables needed for the smaller grid check within the puzzle
    int smallerGridRow, smallerGridCol;
    // check if the number is already in the row
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == number) {
            return false;
        }
    }
    // check if the number is in the column
    for (int i = 0; i < 9; i++) {
        if (board[i][c] == number) {
            return false;
        }
    }
    // make the smaller grid size for the variables
    smallerGridRow = r - r % 3;
    smallerGridCol = c - c % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i+smallerGridRow][j+smallerGridCol] == number) {
                return false;
            }
        }
    }
    // returns true if all of the checks above are good
    return true;

    
}

// Function mplements backtracking algorithm to solve the sudoku puzzle
bool sudoku (int board[][9], int r, int c) {
    // base case
    if (r == 8 && c == 9) {
        // if we made it to the 8th row and 9th column
        // the board is complete and the function returns true
        return true;
    }

    // once we reach the last column start on the next row
    // and make the column 0 again
    if (c == 9) {
        r++;
        c = 0;
    }
    // if the spot in the board already has a number in it, call this funciton
    // and go on to the next number
    if (board[r][c] != 0) {
        return sudoku(board, r, c+1);
    }
    
    // loop through all 9 numbers that can be put in the list
    for (int i = 1; i <= 9; i++) {
        // call the valid function to see if the number is good
        bool isValid = validNumber(board, r, c, i);
        if (isValid == true) {
            // if its a good number, put it in the board
            board[r][c] = i;
            if(sudoku(board, r, c +1)) {
                return true;
            }
        }
        // if number is not valid make the spot blank
        board[r][c] = 0;
    }
    // return false if none of the above conditions are met
    return false;
   
}

int main() {
    // variables to handle file input
    string fileName;
    ifstream inFile;
    int numberReadIn;

    // two dimensional array for the sudoku board
    int row = 9; 
    int column = 9;
    int board[9][9] = {};   

    do {
        //prompt user until they give a valid file to open
        cout << endl;
        while (true) {
            cout << "Enter initial sudoku board file: ";
            cin >> fileName;
            if (fileName == "NO") {
                return 0;
            }
            inFile.open (fileName);
            if (inFile.is_open()) 
                break;
        }   

        // read in the integers from the given puzzle text file
        for (int i = 0; i < row; i++)  {
            for (int j = 0; j < column; j++) {
                inFile >> board[i][j];

            }
        }
        inFile.close();

        // print out the initial board 
        cout << endl << "Initial board read in" << endl << endl;
        printBoard(board, row, column);

        // call sudoke backtracking function
        // as soon as it returns true, the board is complete
        if (sudoku(board, 0, 0)) {
            // print out the solved puzzle
            cout << endl << "Sudoku puzzle solved" << endl << endl;
            printBoard(board, row, column);
        }
    } while (true);
    
    return 0;
}