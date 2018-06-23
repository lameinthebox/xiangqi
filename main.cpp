#include "xiangqi.h"


int main(void) {
    /*
    set<Piece*> pieces;
    pieces.insert(new Chariot(RED, {8,4}));
    pieces.insert(new Chariot(RED, {7,3}));

    Board board = Board(&pieces);
    */
    Board board;
    while (true) {
        int cmd = 0;
        int cnt = 0;
        vector<Position> next;
        Piece* piece = nullptr;
        Position pos1;

        system("clear");
        board.render();
        cout << endl;
        cout << "1. Select piece" << endl;
        cout << "2. Show best move" << endl;
        cout << "> ";
        cin >> cmd;

        switch (cmd) {
        case 1:
            cout << endl;
            cout << "> Pos: ";
            cin >> pos1.row >> pos1.col;
            getchar();

            piece = board.get_piece_at(pos1);
            if (piece == nullptr) {
                cout << "No piece at position" << endl;
                break;
            }

            cout << endl;
            piece->print();

            cout << endl;
            cout << "  Possible moves" << endl;
            piece->get_next_positions(&next, &board);
            cnt = next.size();
            for (int i = 0; i < cnt; ++i) {
                cout << i << ". (" << next[i].row << "," << next[i].col << ")" << endl;
            }
            cout << cnt << ". cancel" << endl;

            int idx;
            cout << "> ";
            cin >> idx;
            getchar();

            if (idx < cnt)
                board.move(piece, next[idx]);

            break;
        case 2:
            cout << endl;
            cout << "Not Implemented" << endl;
            getchar();
            break;
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}
