#ifndef TUNNELER_GAMESTATE_H
#define TUNNELER_GAMESTATE_H

#include <iostream>
#include <fstream>
#include <unistd.h>

#include "macro.h"
#include "Terminal.h"

using namespace std;

class GameState : public Terminal {
protected:
    char player;
    int pos_row, pos_col;
    unsigned int count;
    int gems_collected;
    bool won, dead;
    char old_screen[FRAME_ROWS][FRAME_COLS];
    char screen[FRAME_ROWS][FRAME_COLS];

    // Called only from the Listen_Event() public function
    static Key Read_Key(const char *, int);

public:
    Key key;

    // Constructors and Destructors
    virtual ~GameState() = default;
    GameState() = default;
    GameState(char);

    // Function Override; Same Prototype, but totally different definition
    void Reset();

    // For the Game
    void load_level(const string &game_level_file_path);
    void backup();
    void find_player_position(char);
    void Listen_Event();

    // Pure Virtual Functions
    virtual void Start(const string &) = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif //TUNNELER_GAMESTATE_H



