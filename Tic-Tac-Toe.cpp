#include <iostream>
#include<vector>
#include<Windows.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <array>
#include <algorithm>
using namespace std;

vector<vector<int>> new_board() {
    vector<vector<int>> empty(3, vector<int>(3, 0)); // extensible?
    return empty;
};
void render(vector<vector<int>>board) {
    for (int i = 0; i < 3; i++) { // todo make it extensible
        if (i == 0) {
            cout << "  123" << endl;
            cout << "  ---" << endl;
        }
        for (int j = 0; j < 3; j++) {
            if (j == 0) {
                cout << i+1 <<"|";
            }
            if (board[i][j] == 0) {   
                cout << " ";
            }
            else if (board[i][j] == 1) {
                cout << "X";
            }
            else if (board[i][j] == 2) {
                cout << "O";
            }
            if (j == 2) {
                cout << "|";
            }
       
        }
        
        cout << endl;
        if (i == 2) {
            cout << "  ---" << endl;
        }
}
}
array<int, 2> getmove(string player) {
    array<int, 2> playerinput;
    cout << "It's " << player << "'s move." << endl;
    cout << "What's your moves x coordinate? ";
    cin >> playerinput[1];
    cout << endl << "What's your moves y coordinate? ";
    cin >> playerinput[0];
    cout << endl;
    return playerinput;

}
bool move_legal(array <int, 2> move, vector<vector<int>> board) {
    int y = move[0];
    int x = move[1];
    if (y > board.size() or x > board[0].size() or y < 1 or x < 1 or board[y-1][x-1] == 1 or board[y-1][x-1] == 2) {
        return false;
    }
    else {
        return true;
    }
}
vector<vector<int>> make_move(vector<vector<int>> old_board, array <int, 2> move, int player) {
    int y = move[0];
    int x = move[1];
    vector<vector<int>> new_board = old_board;
    try {
        int playervar = 0;
        if (player == 1) {
            playervar = 1;
        }
        else if (player == 2) {
            playervar = 2;
        }
        else {
            throw invalid_argument("Undefined Playernumber");
        }
            if (y > old_board.size() or x > old_board[0].size() or y < 1 or x < 1) {
                throw invalid_argument("Square out of range");
            }
            else if (old_board[y-1][x-1] == 1 or old_board[y-1][x-1] == 2) {
                throw invalid_argument("Square already taken");
            }
            else {
                new_board[y-1][x-1] = playervar;
            }
            return new_board;
    }
    catch (const invalid_argument& error_) {
        cout << "Caught exception: " << error_.what() << endl;
        exit(EXIT_FAILURE);
    }
}
int get_winner(vector<vector<int>> board) {
    int winner = 0;
    int max_x = board[0].size();
    int max_y = board.size();
    vector<vector<int>> hlines = board; // all horizontal lines
    vector<vector<int>> vlines(max_y, vector<int>(max_x, 0)); // for vertical lines
    vector<vector<int>> diaglines(2, vector<int>(max_x, 0)); // for diagonal lines
    
    for (int i = 0; i < max_x; i++) {
        for (int j = 0; j < max_y; j++) {
            vlines[i][j] = board[j][i];
        }
    }
    for (int k = 0; k < max_y; k++) {
        diaglines[0][k] = board[k][k];
        diaglines[1][k] = board[k][max_x - 1 - k];
    }
    vector<vector<int>> alllines = hlines;  // for all lines
    alllines.insert(alllines.end(), vlines.begin(), vlines.end());
    alllines.insert(alllines.end(), diaglines.begin(), diaglines.end());
    for (int l = 0; l < alllines.size(); l++) {
        if (all_of(alllines[l].begin(), alllines[l].end(), [&](int i) {return i == 1; })) {
            winner = 1;
        }
        if (all_of(alllines[l].begin(), alllines[l].end(), [&](int i) {return i == 2; })) {
            winner = 2;
        }
    }
    return winner;
}
bool board_full(vector<vector<int>> board) {
    int max_y = board.size();
    int max_x = board[0].size();
    int sum = 0;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            if (board[i][j] == 1 or board[i][j] == 2) {
                sum++;
            }
        }
    }
    if (sum == max_x * max_y) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    try {
    // Build empty Board
    vector<vector<int>> board1 = new_board();
    vector<vector<int>> board2;
    // Get Player Names
    array<int, 2> move_coords; // used for temp. user move input
    string player1;
    string player2;
    string active_player;
    int winner;
    int playernumber = 1; // Active player
    cout << "Name of Player1: ";
    getline(cin, player1);
    cout << endl << "Name of Player2 : ";
    getline(cin, player2);

    
        while (true) //Loop till a winner is declared or full board
        {
 
            // Print Board
            render(board1);
            // Set active player
            if (playernumber == 1)
            {
                active_player = player1;
            }
            else if (playernumber == 2) {
                active_player = player2;
            }

            //Get Move fom Player
            while (true) {
                move_coords = getmove(active_player);
                

                // Check Move
                if (move_legal(move_coords, board1)) {
                    break;
                }
                else {
                    cout << "Illegal Move, please try again!" << endl;
                    continue;
                }
                
                    
            }
            //cout << "Legal Move x: " << move_coords[1] << " y: " << move_coords[0] << endl;
            // Execute Move
            board2 = make_move(board1, move_coords, playernumber);
            system("cls");
            //render(board2);
            // switch activ player
            if (playernumber == 1) {
                playernumber = 2;
            }
            else if (playernumber == 2) {
                playernumber = 1;
            }
            // Copy new board over old board
            board1 = board2;
            //Check for Winner
            winner = get_winner(board1);

            //Break Loop if Winner != None or Board is full
            if (winner == 1) {
                render(board1);
                cout << player1 << " has won the game!" << endl;
                break;
            }
            else if (winner == 2) {
                render(board1);
                cout << player2 << " has won the game!" << endl;
                break;
            }
            else if (board_full(board1)) {
                cout << "It's a draw!" << endl;
                break;
            }

        }  
    }
    catch (const exception& error_){
            cout << "Caught exception: " << error_.what() << endl;
            return 1;
        }
    //cout << endl << "Run without Problems";
    return 0;
}

