#ifndef TAMEZX_GAME_H
#define TAMEZX_GAME_H

#include "../include/headers.h"

class Game : public GameState {
private:
    void handle_player();
    void handle_falling_rocks_gems(int row, int col);
    void handle_rocks_gems(int row, int col);

    void update_all_elements();

public:
    Game(char _player) : GameState(_player) {}

    void Start(const string &);
    
    void Update();
    void Render();
    void End_Message();
};

#endif //TAMEZX_GAME_H




