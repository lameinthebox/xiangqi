#include "xiangqi.h"


inline bool operator==(const Position& p1, const Position& p2) {
    return (p1.row == p2.row) && (p1.col == p2.col);
}

bool in_castle(const Position& pos) {
    return (3 <= pos.col && pos.col <= 5) && ((0 <= pos.row && pos.row <= 2) || (7 <= pos.row && pos.row <= 9));
}


Piece::Piece(bool _color, Position _pos, int _type, int _point) {
    color = _color;
    pos = _pos;
    type = _type;
    point = _point;
}

bool Piece::operator<(const Piece& p) const {
    if (pos.row < p.pos.row) {
        return true;
    } else if (pos.row == p.pos.row && pos.col < p.pos.col) {
        return true;
    }

    return false;
}

int Piece::get_color(void) {
    return color;
}

Position Piece::get_position(void) {
    return pos;
}

int Piece::get_type(void) {
    return type;
}

int Piece::get_point(void) {
    return point;
}

void Piece::set_position(Position _pos) {
    pos = _pos;
    return;
}

void Piece::print(void) {
    string types[8] = {"None", "General", "Advisor", "Elephant", "Horse", "Chariot", "Cannon", "Soldier"};
    cout << "(" << pos.row << "," << pos.col << ") " << ((color == RED) ? "Red" : "Black") << " " << types[type] << endl;
}


General::General(bool _color, Position _pos) : Piece(_color, _pos, GENERAL, GENERAL_P) {}

void General::get_next_positions(vector<Position>* pos_list, Board* board) {
    int r = pos.row;
    int c = pos.col;

    int dr[3] = {-1, 0, +1};
    int dc[3] = {-1, 0, +1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int nr = r + dr[i];
            int nc = c + dc[j];

            if (color == RED) {
                if (nr < 7 || 9 < nr || nc < 3 || 5 < nc)
                    continue;

                if ((r == 7 || r == 9) && (c == 4) && (nr != r && nc != c))
                    continue;

                if ((c == 3 || c == 5) && (r == 8) && (nr != r && nc != c))
                    continue;

            } else {
                if (nr < 0 || 2 < nr || nc < 3 || 5 < nc)
                    continue;

                if ((r == 0 || r == 2) && (c == 4) && (nr != r && nc != c))
                    continue;

                if ((c == 3 || c == 5) && (r == 1) && (nr != r && nc != c))
                    continue;
            }

            int move = board->can_move(this, {nr, nc});
            if (move == BLANK || move == ENEMY) {
                pos_list->push_back({nr, nc});
            }
        }
    } // end i, j

    return;
}


Advisor::Advisor(bool _color, Position _pos) : Piece(_color, _pos, ADIVSOR, ADIVSOR_P) {}

void Advisor::get_next_positions(vector<Position>* pos_list, Board* board) {
    int r = pos.row;
    int c = pos.col;

    int dr[3] = {-1, 0, +1};
    int dc[3] = {-1, 0, +1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int nr = r + dr[i];
            int nc = c + dc[j];

            if (color == RED) {
                if (nr < 7 || 9 < nr || nc < 3 || 5 < nc)
                    continue;

                if ((r == 7 || r == 9) && (c == 4) && (nr != r && nc != c))
                    continue;

                if ((c == 3 || c == 5) && (r == 8) && (nr != r && nc != c))
                    continue;

            } else {
                if (nr < 0 || 2 < nr || nc < 3 || 5 < nc)
                    continue;

                if ((r == 0 || r == 2) && (c == 4) && (nr != r && nc != c))
                    continue;

                if ((c == 3 || c == 5) && (r == 1) && (nr != r && nc != c))
                    continue;
            }

            int move = board->can_move(this, {nr, nc});
            if (move == BLANK || move == ENEMY) {
                pos_list->push_back({nr, nc});
            }
        }
    } // end i, j

    return;
}


Elephant::Elephant(bool _color, Position _pos) : Piece(_color, _pos, ELEPHANT, ELEPHANT_P) {}

void Elephant::get_next_positions(vector<Position>* pos_list, Board* board) {
    Position curr = get_position();
    int dr[2] = {-1, 1};
    int dc[2] = {-1, 1};
    for (int i = 0; i < 2; ++i) {
        Position next = {curr.row+dr[i], curr.col};
        int move = board->can_move(this, next);
        if (move != BLANK) {
            continue;
        }

        for (int j = 0; j < 2; ++j) {
            if (board->can_move(this, {next.row+dr[i], next.col+dc[j]}) == BLANK
                    && board->can_move(this, {next.row+2*dr[i], next.col+2*dc[j]}) > 0) {

                pos_list->push_back({next.row+2*dr[i], next.col+2*dc[j]});
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        Position next = {curr.row, curr.col+dc[i]};
        int move = board->can_move(this, next);
        if (move != BLANK) {
            continue;
        }

        for (int j = 0; j < 2; ++j) {
            if (board->can_move(this, {next.row+dr[j], next.col+dc[i]}) == BLANK
                    && board->can_move(this, {next.row+2*dr[j], next.col+2*dc[i]}) > 0) {

                pos_list->push_back({next.row+2*dr[j], next.col+2*dc[i]});
            }
        }
    }
    return;
}


Horse::Horse(bool _color, Position _pos) : Piece(_color, _pos, HORSE, HORSE_P) {}

void Horse::get_next_positions(vector<Position>* pos_list, Board* board) {
    Position curr = get_position();
    int dr[2] = {-1, 1};
    int dc[2] = {-1, 1};
    for (int i = 0; i < 2; ++i) {
        Position next = {curr.row+dr[i], curr.col};
        int move = board->can_move(this, next);
        if (move != BLANK) {
            continue;
        }

        for (int j = 0; j < 2; ++j) {
            if (board->can_move(this, {next.row+dr[i], next.col+dc[j]}) > 0) {
                pos_list->push_back({next.row+dr[i], next.col+dc[j]});
            }
        }
    }

    for (int i = 0; i < 2; ++i) {
        Position next = {curr.row, curr.col+dc[i]};
        int move = board->can_move(this, next);
        if (move != BLANK) {
            continue;
        }

        for (int j = 0; j < 2; ++j) {
            if (board->can_move(this, {next.row+dr[j], next.col+dc[i]}) > 0) {
                pos_list->push_back({next.row+dr[j], next.col+dc[i]});
            }
        }
    }
    return;
}


Chariot::Chariot(bool _color, Position _pos) : Piece(_color, _pos, CHARIOT, CHARIOT_P) {}

void Chariot::get_next_positions(vector<Position>* pos_list, Board* board) {
    Position curr = get_position();

    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
        Position next = curr;
        while (true) {
            next = {next.row+dr[i], next.col+dc[i]};
            int move = board->can_move(this, next);
            if (move == OB || move == FRIENDLY) {
                break;
            } else if (move == ENEMY) {
                pos_list->push_back(next);
                break;
            } else {
                pos_list->push_back(next);
            }
        }
    }

    int offset[2] = {0, 7};
    int row[5] = {0, 0, 1, 2, 2};
    int col[5] = {3, 5, 4, 3, 5};
    int drr[4] = {-1, -1, 1, 1};
    int dcc[4] = {-1, 1, -1, 1};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            int nr = row[j]+offset[i];
            int nc = col[j];
            Position pos = {nr, nc};
            if (curr == pos) {
                for (int k = 0; k < 4; ++k) {
                    Position next = curr;
                    while(true) {
                        next = {next.row+drr[k], next.col+dcc[k]};
                        if (!in_castle(next))
                            break;

                        int move = board->can_move(this, next);
                        if (move == OB || move == FRIENDLY) {
                            break;
                        } else if (move == ENEMY) {
                            pos_list->push_back(next);
                            break;
                        } else {
                            pos_list->push_back(next);
                        }
                    }
                }
            }
        }
    }
    return;
}


Cannon::Cannon(bool _color, Position _pos) : Piece(_color, _pos, CANNON, CANNON_P) {}

void Cannon::get_next_positions(vector<Position>* pos_list, Board* board) {
    Position curr = get_position();
    int dr[4] = {-1, 0, 1, 0};
    int dc[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
        Position next = curr;
        Piece* first_piece = nullptr;
        while (true) {
            next = {next.row+dr[i], next.col+dc[i]};
            int move = board->can_move(this, next);
            if (move == OB) {
                break;
            } else if (move == FRIENDLY || move == ENEMY) {
                first_piece = board->get_piece_at(next);
                break;
            }
        }

        if (first_piece == nullptr || first_piece->get_type() == CANNON) {
            continue;
        }

        while (true) {
            next = {next.row+dr[i], next.col+dc[i]};
            int move = board->can_move(this, next);
            if (move == OB || move == FRIENDLY) {
                break;
            } else if (move == ENEMY) {
                Piece* second_piece = board->get_piece_at(next);
                if (second_piece->get_type() != CANNON) {
                    pos_list->push_back(next);
                }
                break;
            } else if (move == BLANK) {
                pos_list->push_back(next);
            }
        }
    }

    int offset[2] = {0, 7};
    int row[4] = {0, 0, 2, 2};
    int col[4] = {3, 5, 3, 5};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            int nr = row[j]+offset[i];
            int nc = col[j];
            Position pos = {nr, nc};
            if (curr == pos) {
                Position center = {1+offset[i], 4};
                Piece* center_piece = board->get_piece_at(center);
                if (center_piece->get_type() == CANNON)
                    break;

                Position next = {2*center.row-pos.row, 2*center.col-pos.col};
                int move = board->can_move(this, next);
                if (move == OB || move == FRIENDLY) {
                    // do nothing
                } else if (move == ENEMY) {
                    Piece* target = board->get_piece_at(next);
                    if (target->get_type() != CANNON)
                        pos_list->push_back(next);
                } else {
                    pos_list->push_back(next);
                }
            }
        }
    }
    return;
}

Soldier::Soldier(bool _color, Position _pos) : Piece(_color, _pos, SOLDIER, SOLDIER_P1) {}

void Soldier::get_next_positions(vector<Position>* pos_list, Board* board) {
    int forward = (color == RED) ? -1 : 1;

    int row[3] = {pos.row, pos.row, pos.row + forward};
    int col[3] = {pos.col-1, pos.col+1, pos.col};

    for (int i = 0; i < 3; ++i) {
        int nr = row[i];
        int nc = col[i];

        if (nr < 0 || 9 < nr || nc < 0 || 8 < nc)
            continue;

        int move = board->can_move(this, {nr, nc});
        if (move == BLANK || move == ENEMY) {
            pos_list->push_back({nr, nc});
        }
    } // end for

    return;
}


Board::Board(void) {
    pieces = new set<Piece*>;
    pieces->insert(new General(RED, {8,4}));
    pieces->insert(new Advisor(RED, {9,3}));
    pieces->insert(new Advisor(RED, {9,5}));
    pieces->insert(new Elephant(RED, {9,2}));
    pieces->insert(new Elephant(RED, {9,6}));
    pieces->insert(new Horse(RED, {9,1}));
    pieces->insert(new Horse(RED, {9,7}));
    pieces->insert(new Chariot(RED, {9,0}));
    pieces->insert(new Chariot(RED, {9,8}));
    pieces->insert(new Cannon(RED, {7,1}));
    pieces->insert(new Cannon(RED, {7,7}));
    pieces->insert(new Soldier(RED, {6,0}));
    pieces->insert(new Soldier(RED, {6,2}));
    pieces->insert(new Soldier(RED, {6,4}));
    pieces->insert(new Soldier(RED, {6,6}));
    pieces->insert(new Soldier(RED, {6,8}));

    pieces->insert(new General(BLACK, {1,4}));
    pieces->insert(new Advisor(BLACK, {0,3}));
    pieces->insert(new Advisor(BLACK, {0,5}));
    pieces->insert(new Elephant(BLACK, {0,2}));
    pieces->insert(new Elephant(BLACK, {0,6}));
    pieces->insert(new Horse(BLACK, {0,1}));
    pieces->insert(new Horse(BLACK, {0,7}));
    pieces->insert(new Chariot(BLACK, {0,0}));
    pieces->insert(new Chariot(BLACK, {0,8}));
    pieces->insert(new Cannon(BLACK, {2,1}));
    pieces->insert(new Cannon(BLACK, {2,7}));
    pieces->insert(new Soldier(BLACK, {3,0}));
    pieces->insert(new Soldier(BLACK, {3,2}));
    pieces->insert(new Soldier(BLACK, {3,4}));
    pieces->insert(new Soldier(BLACK, {3,6}));
    pieces->insert(new Soldier(BLACK, {3,8}));
}

Board::Board(set<Piece*>* _pieces) {
    pieces = _pieces;
}

set<Piece*>* Board::get_pieces(void) {
    return pieces;
}

Piece* Board::get_piece_at(Position p) {
    set<Piece*>::iterator iter;
    for (iter = pieces->begin(); iter != pieces->end(); ++iter) {
        if ((*iter)->get_position() == p) {
            return (*iter);
        }
    }
    return nullptr;
}

int Board::can_move(Piece* piece, Position to) {
    if (to.row < 0 || 9 < to.row || to.col < 0 || 8 < to.col)
        return OB;

    set<Piece*>::iterator iter;
    for (iter = pieces->begin(); iter != pieces->end(); ++iter) {
        if ((*iter)->get_position() == to) {
            if ((*iter)->get_color() == piece->get_color()) {
                return FRIENDLY;
            } else {
                return ENEMY;
            }
        }
    }
    return BLANK;
}

bool Board::move(Piece* piece, Position to) {
    set<Piece*>::iterator iter;
    for (iter = pieces->begin(); iter != pieces->end(); ++iter) {
        Piece* piece_ptr = *iter;
        Position pos = piece_ptr->get_position();

        if (pos.row == to.row && pos.col == to.col) {
            pieces->erase(iter);
            break;
        }
    }

    piece->set_position(to);

    return false;
}

int Board::get_score(int color) {
    int score = 0;

    set<Piece*>::iterator iter;
    for (iter = pieces->begin(); iter != pieces->end(); ++iter) {
        if ((*iter)->get_color() == color) {
            score += (*iter)->get_point();
        }
    }
    return score;
}

void Board::render(void) {
    char piece[8] = {'\0', 'G', 'A', 'E', 'H', 'R', 'C', 'S'};
    int board[10][9] = {};

    set<Piece*>::iterator iter;
    for (iter = pieces->begin(); iter != pieces->end(); ++iter) {
        int type = (*iter)->get_type();
        Position p = (*iter)->get_position();

        if (p.row < 0 || 9 < p.row || p.col < 0 || 8 < p.col)
            continue;

        if ((*iter)->get_color() == RED) {
            board[p.row][p.col] = type;
        } else {
            board[p.row][p.col] = -type;
        }
    }

    cout << "  ";
    for (int col = 0; col < 9; ++col) {
        cout << col << " ";
    }
    cout << endl;

    for (int row = 0; row < 10; ++row) {
        cout << row << " ";

        for (int col = 0; col < 9; ++col) {
            int p = board[row][col];

            if (0 < p) {
                cout << "\033[1;31m" << piece[p] << " \033[0m";
            } else if (p == 0) {
                cout << "· ";
            } else {
                cout << "\033[1;37m" << piece[-p] << " \033[0m";
            }
        }
        cout << row << " ";
        cout << endl;
    }
    cout << "  ";
    for (int col = 0; col < 9; ++col) {
        cout << col << " ";
    }
    cout << endl << endl;
    cout << "\t" << "R\t" << "B\t" << endl;
    cout << "points\t" << get_score(RED) << "\t" << get_score(BLACK) << "\t" << endl;

    return;
}

