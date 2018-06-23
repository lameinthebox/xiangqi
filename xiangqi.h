#ifndef XIANGQI_H_
#define XIANGQI_H_

#include <cstdlib>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#define RED     0
#define BLACK   1

#define OB          -1
#define BLANK       2
#define FRIENDLY    -3
#define ENEMY       4

#define GENERAL     1
#define ADIVSOR     2
#define ELEPHANT    3
#define HORSE       4
#define CHARIOT     5
#define CANNON      6
#define SOLDIER     7

#define GENERAL_P   100
#define ADIVSOR_P   4
#define ELEPHANT_P  4
#define HORSE_P     8
#define CHARIOT_P   18
#define CANNON_P    9
#define SOLDIER_P1  2
#define SOLDIER_P2  4

using namespace std;

class Piece;
class Board;

struct Position {
    int row;
    int col;
};

inline bool operator==(const Position&, const Position&);
bool in_castle(const Position&);

class Piece {
public:
    Piece(bool, Position, int, int);

    void print(void);

    int get_color(void);
    Position get_position(void);
    int get_type(void);
    int get_point(void);

    void set_position(Position);

    virtual void get_next_positions(vector<Position>*, Board*) = 0;

    bool operator<(const Piece&) const;

protected:
    bool color;
    Position pos;
    int type;
    int point;
};


class General: public Piece {
public:
    General(bool, Position = {1,1});
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Advisor: public Piece {
public:
    Advisor(bool, Position = {1,1});
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Elephant: public Piece {
public:
    Elephant(bool, Position);
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Horse: public Piece {
public:
    Horse(bool, Position);
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Chariot: public Piece {
public:
    Chariot(bool, Position);
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Cannon: public Piece {
public:
    Cannon(bool, Position);
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Soldier: public Piece {
public:
    Soldier(bool, Position);
    virtual void get_next_positions(vector<Position>*, Board*);
};


class Board {
public:
    Board(void);
    Board(set<Piece*>*);

    int can_move(Piece*, Position);
    bool move(Piece*, Position);
    int get_score(int);
    void render(void);

    set<Piece*>* get_pieces(void);
    Piece* get_piece_at(Position);

private:
    set<Piece*>* pieces;
};

#endif
