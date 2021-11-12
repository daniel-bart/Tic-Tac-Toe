#include <iostream>
#include<vector>
#include<Windows.h>
#include <fstream>
#include <string>
#include <sstream> 
#include <array>
#include <algorithm>
using namespace std;

vector<vector<int>> new_board(int size) {
    vector<vector<int>> empty(size, vector<int>(size, 0)); // 
    return empty;
};
void render(vector<vector<int>>board) {
    int max_y = board.size();
    int max_x = board[0].size();
    for (int i = 0; i < max_y; i++) {
        if (i == 0) {
            cout << "  ";
            for (int a = 1; a <= max_x; a++) {
                cout << a;
            }
            cout << endl << "  ";
            for (int b = 1; b <= max_x; b++) {
                cout << "-";
            }
            cout << endl;
        }
        for (int j = 0; j < max_x; j++) {
            if (j == 0) {
                cout << i + 1 << "|";
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
            if (j == max_x - 1) {
                cout << "|";
            }

        }

        cout << endl;
        if (i == max_y - 1) {
            cout << "  ";
            for (int c = 1; c <= max_x; c++) {
                cout << "-";
            }
            cout << endl;
        }
    }
}
bool move_legal(array <int, 2> move, vector<vector<int>> board) {
    int y = move[0] - 1;
    int x = move[1] - 1;
    if (y >= board.size() or x >= board[0].size() or y < 0 or x < 0 or board[y][x] == 1 or board[y][x] == 2) {
        return false;
    }
    else {
        return true;
    }
}

vector<vector<int>> make_move(vector<vector<int>> old_board, array <int, 2> move, int player) {
    int y = move[0] - 1;
    int x = move[1] - 1;
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
        if (y >= old_board.size() or x >= old_board[0].size() or y < 0 or x < 0) {
            throw invalid_argument("Square out of range");
        }
        else if (old_board[y][x] == 1 or old_board[y][x] == 2) {
            throw invalid_argument("Square already taken");
        }
        else {
            new_board[y][x] = playervar;
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
    int std_x = board[0].size() - 1;
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
        diaglines[1][k] = board[k][std_x - k];
    }
    vector<vector<int>> alllines = hlines;  // for all lines
    alllines.insert(alllines.end(), vlines.begin(), vlines.end());
    alllines.insert(alllines.end(), diaglines.begin(), diaglines.end());
    for (int l = 0; l < alllines.size(); l++) {
        if (all_of(alllines[l].begin(), alllines[l].end(), [&](int i) {return i == 1; })) {
            winner = 1;
            break;
        }
        else if (all_of(alllines[l].begin(), alllines[l].end(), [&](int i) {return i == 2; })) {
            winner = 2;
            break;
        }
    }
    return winner;
}
array<int, 2> find_winningmove(vector<vector<int>> board, int player) {
    array<int, 2> move;
    int max_x = board[0].size();
    int max_y = board.size();
    int std_x = board[0].size() - 1;
    array<int, 2> win_move = { max_y + 1, max_x + 1 };
    int win = max_x - 1;
    int a = 0;
    int b = 0;
    for (int i = 0; i < max_y; i++) {
        a = 0;
        b = 0;
        for (int j = 0; j < max_x; j++) {
            if (board[i][j] == player) {
                a++;
            }
            else if (board[i][j] == 0) {
                b++;
                move = { i + 1, j + 1 };
            }
        }
        if (a == win and b == 1) {
            win_move = move;
            break;
        }
    }
    int c = 0;
    int d = 0;
    for (int j = 0; j < max_x; j++) {
        c = 0;
        d = 0;
        for (int i = 0; i < max_y; i++) {
            if (board[i][j] == player) {
                c++;
            }
            else if (board[i][j] == 0) {
                d++;
                move = { i + 1, j + 1 };
            }
        }
        if (c == win and d == 1) {
            win_move = move;
            break;
        }
    }
    int e = 0;
    int f = 0;
    int g = 0;
    int h = 0;
    for (int k = 0; k < max_y; k++) {
        if (board[k][k] == player) {
                e++;
            }
        else if (board[k][k] == 0) {
                f++;
                move = { k + 1, k + 1 };
            }
        }
    if (e == win and f == 1) {
            win_move = move;
        }
    for (int l = 0; l < max_y; l++) {
        if (board[l][std_x-l] == player) {
            g++;
        }
        else if (board[l][std_x -l] == 0) {
            h++;
            move = { l + 1, std_x-l + 1 };
        }
    }
    if (g == win and h == 1) {
        win_move = move;
    }
    return win_move;
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

int minimax(vector<vector<int>> board, int player, int depth) {
    int opponent = 0;
    vector<vector<int>> legal_moves (9, vector<int> (2,0));
    vector<vector<int>> new_board;
    vector<int> scores;
    int score;
    array<int, 2> move;
    int max_x = board[0].size();
    int max_y = board.size();
    if (get_winner(board) == 1) {
        return +10 - depth;
    }
    else if (get_winner(board) == 2) {
        return depth - 10;
    }
    else if (board_full(board)) {
        return 0;
    }
    depth++;
    int a = 0;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            if (board[i][j] == 0) {
                legal_moves[a][0] = i+1;
                legal_moves[a][1] = j+1;
                a++;
            }
        }
    }
    for (int k = 0; k < a; k++) {
        move[0] = legal_moves[k][0];
        move[1] = legal_moves[k][1];
        new_board = make_move(board, move, player);
        if (player == 1) {
            opponent = 2;
        }
        else if (player == 2) {
            opponent = 1;
        }
        score = minimax(new_board, opponent, depth);
        scores.push_back(score);
    }
    if (player == 1) {
        return *max_element(begin(scores), end(scores));
    }
    else if (player == 2) {
        return *min_element(begin(scores), end(scores));
    }
}
array<int, 2> move_KI(vector<vector<int>> board) {
    array<int, 2> input;
    int max_y = board.size();
    int max_x = board[0].size();
    array<int, 2> default_move = { max_y + 1, max_x + 1 };
    while (true) {
        if (find_winningmove(board,1) != default_move) {
            input = find_winningmove(board,1);      //search for a winning move for itself
            break;
        }
        else if (find_winningmove(board, 2) != default_move) {
            input = find_winningmove(board, 2);     // defeat loss
            break;
        }
        else {
            input[0] = rand() % max_y + 1; // random move by KI
            input[1] = rand() % max_x + 1;
            if (move_legal(input, board)) { // only use random move if legal
                break;
            }
            else {
                continue;
            }
        }
    }

    return input;
}
array<int, 2> minmax_move(vector<vector<int>> board) {
    int max_y = board.size();
    int max_x = board[0].size();
    vector<vector<int>> legal_moves(9, vector<int>(2, 0));
    vector<vector<int>> new_board;
    array<int,9> score_moves;
    array<int, 2> move;
    array<int, 2> best_move;
    int a = 0;
    int index;
    for (int i = 0; i < max_y; i++) {
        for (int j = 0; j < max_x; j++) {
            if (board[i][j] == 0) {
                legal_moves[a][0] = i + 1;
                legal_moves[a][1] = j + 1;
                a++;
            }
        }
    }
    for (int k = 0; k < a; k++) {
        move[0] = legal_moves[k][0];
        move[1] = legal_moves[k][1];
        new_board = make_move(board, move, 1);
        score_moves[k] = minimax(new_board, 2, 1);
    }
    index = max_element(score_moves.begin(), score_moves.end()) - score_moves.begin();
    best_move[0] = legal_moves[index][0];
    best_move[1] = legal_moves[index][1];
    return best_move;
}
array<int, 2> getmove(string player, vector<vector<int>> board) {
    array<int, 2> playerinput;
    if (player == "AI1336") {
        cout << "It's AI's move." << endl;
        Sleep(500);
        playerinput = minmax_move(board);
        
    }
    else {
        cout << "It's " << player << "'s move." << endl;
        cout << "What's your moves x coordinate? ";
        cin >> playerinput[1];
        cout << endl << "What's your moves y coordinate? ";
        cin >> playerinput[0];
        cout << endl;
    }
    return playerinput;

}

int main()
{
    try {
        // Build empty Board
        int size;
        cout << "What should the size of the board be? (whole number) ";
        cin >> size;
        getchar(); // get /n
        vector<vector<int>> board1 = new_board(size);
        vector<vector<int>> board2;
        // Get Player Names
        array<int, 2> move_coords; // used for temp. user move input
        string player1;
        string player2;
        string active_player;
        char replay;
        int winner;
        char choice;
        int playernumber = 1; // Active player
        while (true) {
            cout << endl << "Do you want to play alone? (y/n) ";
            cin >> choice;
            getchar(); // get /n
            if (choice == 'y') {
                cout << endl << "What's your name? ";
                getline(cin, player1);
                player2 = "AI1336";
                system("cls");
                break;
            }
            else if (choice == 'n') {
                cout << endl << "Name of Player1: ";
                getline(cin, player1);
                cout << endl << "Name of Player2 : ";
                getline(cin, player2);
                system("cls");
                break;
            }
            else {
                cout << endl << "What?! Please try again!";
                continue;
            }
        }

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
                move_coords = getmove(active_player, board1);


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
                cout << "Replay? (y/n) ";
                cin >> replay;
                getchar(); // get /n
                if (replay == 'y') {
                    board1 = new_board(size);
                }
                else {
                    break;
                }
            }
            else if (winner == 2) {
                render(board1);
                cout << player2 << " has won the game!" << endl;
                cout << "Replay? (y/n) ";
                cin >> replay;
                getchar(); // get /n
                if (replay == 'y') {
                    board1 = new_board(size);
                }
                else {
                    break;
                }
            }
            else if (board_full(board1)) {
                cout << "It's a draw!" << endl;
                cout << "Replay? (y/n) ";
                cin >> replay;
                getchar(); // get /n
                if (replay == 'y') {
                    board1 = new_board(size);
                }
                else {
                    break;
                }
            }

        }
    }
    catch (const exception& error_) {
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }
    //cout << endl << "Run without Problems";
    return 0;
}

