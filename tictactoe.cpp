#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ----------------------
// Player Base Class
// ----------------------
class Player {
protected:
    string name;
    char symbol;

public:
    Player(string n, char s) : name(n), symbol(s) {}
    virtual ~Player() {}

    char getSymbol() { return symbol; }
    string getName() { return name; }

    // Polymorphic function
    virtual int getMove() = 0;
};

// ----------------------
// Human Player
// ----------------------
class HumanPlayer : public Player {
public:
    HumanPlayer(string n, char s) : Player(n, s) {}

    int getMove() override {
        int move;
        cout << name << " (" << symbol << ") - Enter your move (1-9): ";
        cin >> move;
        return move;
    }
};

// ----------------------
// Board Class
// ----------------------
class Board {
private:
    vector<char> cells;

public:
    Board() {
        cells = {'1','2','3','4','5','6','7','8','9'};
    }

    void display() {
        cout << "\n";
        cout << " " << cells[0] << " | " << cells[1] << " | " << cells[2] << endl;
        cout << "---+---+---\n";
        cout << " " << cells[3] << " | " << cells[4] << " | " << cells[5] << endl;
        cout << "---+---+---\n";
        cout << " " << cells[6] << " | " << cells[7] << " | " << cells[8] << endl;
        cout << "\n";
    }

    bool isValidMove(int pos) {
        return pos >= 1 && pos <= 9 && cells[pos-1] == '0' + pos;
    }

    void makeMove(int pos, char sym) {
        cells[pos-1] = sym;
    }

    bool checkWin(char sym) {
        int wins[8][3] = {
            {0,1,2},{3,4,5},{6,7,8},
            {0,3,6},{1,4,7},{2,5,8},
            {0,4,8},{2,4,6}
        };

        for (auto &line : wins)
            if (cells[line[0]] == sym && cells[line[1]] == sym && cells[line[2]] == sym)
                return true;

        return false;
    }

    bool isFull() {
        for (char c : cells)
            if (c >= '1' && c <= '9') return false;
        return true;
    }
};

// ----------------------
// Game Class
// ----------------------
class Game {
private:
    Player* p1;
    Player* p2;
    Board board;

public:
    Game(Player* a, Player* b) : p1(a), p2(b) {}

    void start() {
        Player* current = p1;

        while (true) {
            board.display();
            int move = current->getMove();

            if (!board.isValidMove(move)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            board.makeMove(move, current->getSymbol());

            if (board.checkWin(current->getSymbol())) {
                board.display();
                cout << current->getName() << " WINS!\n";
                break;
            }

            if (board.isFull()) {
                board.display();
                cout << "It's a DRAW!\n";
                break;
            }

            current = (current == p1) ? p2 : p1;
        }
    }
};

// ----------------------
// MAIN FUNCTION
// ----------------------
int main() {
    string name1, name2;
    cout << "Enter Player 1 Name: ";
    cin >> name1;
    cout << "Enter Player 2 Name: ";
    cin >> name2;

    HumanPlayer p1(name1, 'X');
    HumanPlayer p2(name2, 'O');

    Game game(&p1, &p2);
    game.start();

    return 0;
}
