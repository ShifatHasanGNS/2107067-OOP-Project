#include "GameState.h"

GameState::GameState(char _player) :
        player(_player), pos_row(0), pos_col(0), count(0), gems_collected(0), won(false), dead(false) {}

void GameState::Reset() {
    for (int r = 0; r < FRAME_ROWS; r++) {
        for (int c = 0; c < FRAME_COLS; c++) {
            screen[r][c] = ' ';
            screen[r][c] = ' ';
        }
    }
}

void GameState::load_level(const string &game_level_file_path) {
    fstream file(game_level_file_path, ios::in);
    if (file.is_open()) {
        for (int r = 0; r < FRAME_ROWS; r++) {
            for (int c = 0; c < FRAME_COLS; c++) {
                screen[r][c] = file.get();
            }
        }
    } else {
        std::cout << "Sorry! Unable to load the file (" << game_level_file_path << ").\n";
    }
    file.close();
}

void GameState::backup() {
    for (int r = 0; r < FRAME_ROWS; r++) {
        for (int c = 0; c < FRAME_COLS; c++) {
            old_screen[r][c] = screen[r][c];
        }
    }
}

void GameState::find_player_position(char _player) {
    for (int r = 0; r < FRAME_ROWS; r++) {
        for (int c = 0; c < FRAME_COLS; c++) {
            if (screen[r][c] == _player) {
                pos_row = r;
                pos_col = c;
                return;
            }
        }
    }
}

Key GameState::Read_Key(const char *buffer, int i) {
    if (buffer[i] == '\033' && buffer[i + 1] == '[') {
        switch (buffer[i + 2]) {
            case 'A':
                return Key::Up;
            case 'B':
                return Key::Down;
            case 'C':
                return Key::Right;
            case 'D':
                return Key::Left;
        }
    }
    return Key::None;
}

void GameState::Listen_Event() {
    char buffer[4096];
    int n_read = (int) read(STDIN_FILENO, buffer, sizeof(buffer));
    Key final_key = Key::None;
    for (int i = 0; i <= n_read - 3; i += 3) {
        Key _key;
        _key = GameState::Read_Key(buffer, i);
        if (_key == Key::None)
            continue;
        final_key = _key;
    }
    key = final_key;
}




