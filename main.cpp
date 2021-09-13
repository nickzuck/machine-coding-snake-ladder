#include <iostream>
#include<map>
#include <utility>
#include<vector>

using namespace  std ;

class Dice {
public:
    int roll_dice();
};

class Player {
private :
    string name  ;
public:
    int getCurrPos() const;

private:
    int currPos ;
public :
    Player(string name);

    void setCurrPos(int currPos);

    const string &getName() const;
};

Player::Player(string n) {
    name = n;
    currPos = 0 ;
}

int Player::getCurrPos() const {
    return currPos;
}

void Player::setCurrPos(int currPos) {
    Player::currPos = currPos;
}

const string &Player::getName() const {
    return name;
}


class Board{
private :
    map<int,int> snakes, ladders ;
    int size ;
public:
    Board(int size);

    const map<int, int> &getSnakes() const;

    void addSnake(int start, int end);

    const map<int, int> &getLadders() const;

    void addLadder(int start, int end);

    int getSize() const;

    int move(int pos, int steps);
};

const map<int, int> &Board::getSnakes() const {
    return snakes;
}

void Board::addSnake(int start, int end) {
    this->snakes[start] = end ;
}

const map<int, int> &Board::getLadders() const {
    return ladders;
}

void Board::addLadder(int start, int end) {
    this->ladders[start] = end ;
}

int Board::getSize() const {
    return size;
}

int Dice::roll_dice() {
    return 1 + (rand() % 6) ;
}

int Board::move(int pos, int steps) {
    if (pos + steps > this->size){
        return pos ;
    }
    pos += steps ;
    map<int, int>::iterator it ;
    it = this->snakes.find(pos)  ;
    if (it != this->snakes.end()){
        pos = it->second ;
        pos = move(pos, 0);
    }

    it = this->ladders.find(pos) ;
    if (it != this->ladders.end()){
        pos = it->second ;
        pos = move(pos, 0 );
    }
    return pos ;
}

Board::Board(int size) : size(size) {}

int main() {
    int snakes, ladders, start , end ;
    cin >> snakes ;
    Board board = Board(100);
    for (int i = 0; i < snakes; ++i) {
        cin >> start >> end ;
        board.addSnake(start, end);
    }

    cin >> ladders;
    for (int i = 0; i < ladders; ++i) {
        cin >> start >> end ;
        board.addLadder(start, end);
    }

    int numPlayers ;
    string name ;
    cin >> numPlayers ;
    vector<Player> allPlayers ;
    for (int i = 0; i < numPlayers; ++i) {
        cin >> name ;
        allPlayers.push_back(Player(name)) ;
    }

    bool finished = false ;
    Dice d = Dice();
    while (!finished){
        for (int i = 0; i < numPlayers; ++i) {
            Player p = allPlayers[i] ;
            cout << "Player " << p.getName() << "rolled dice" << endl;
            int steps = d.roll_dice() ;
            cout << "Got: " << steps << endl ;
            int oldPos = p.getCurrPos();
            int pos = board.move(oldPos, steps);
            allPlayers[i].setCurrPos(pos);
            cout << "Player " << p.getName() << " moved from " << oldPos << " to " << pos << endl ;
            if (pos == board.getSize()){
                finished = true ;
            }
        }
    }
}

