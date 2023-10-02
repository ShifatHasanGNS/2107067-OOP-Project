#include "Game.h"

void Game::handle_player() {
    switch (key) {
        case Key::Up:
            switch (screen[pos_row - 1][pos_col]) {
                case '$':
                    gems_collected++; // fallthrough
                case ' ':
                case '.':
                    screen[pos_row][pos_col] = ' ';
                    screen[pos_row - 1][pos_col] = '@';
                    --pos_row;
                    break;
                case 'E':
                    won = true;
                    break;
                case 'o':
                case 's':
                    dead = true;
                    break;
                default:
                    break;
            }
            break;
        case Key::Down:
            switch (screen[pos_row + 1][pos_col]) {
                case '$':
                    gems_collected++; // fallthrough
                case ' ':
                case '.':
                    screen[pos_row][pos_col] = ' ';
                    screen[pos_row + 1][pos_col] = '@';
                    ++pos_row;
                    break;
                case 'E':
                    won = true;
                    break;
                default:
                    break;
            }
            break;
        case Key::Right:
            switch (screen[pos_row][pos_col + 1]) {
                case '$':
                    gems_collected++; // fallthrough
                case ' ':
                case '.':
                    screen[pos_row][pos_col] = ' ';
                    screen[pos_row][pos_col + 1] = '@';
                    ++pos_col;
                    break;
                case 'E':
                    won = true;
                    break;
                case 'O':
                    if (screen[pos_row][pos_col + 2] == ' ') {
                        screen[pos_row][pos_col + 2] = 'O';
                        screen[pos_row][pos_col] = ' ';
                        screen[pos_row][pos_col + 1] = '@';
                        pos_col++;
                    }
                    break;
                default:
                    break;
            }
            break;
        case Key::Left:
            switch (screen[pos_row][pos_col - 1]) {
                case '$':
                    gems_collected++; // fallthrough
                case ' ':
                case '.':
                    screen[pos_row][pos_col] = ' ';
                    screen[pos_row][pos_col - 1] = '@';
                    --pos_col;
                    break;
                case 'E':
                    won = true;
                    break;
                case 'O':
                    if (screen[pos_row][pos_col - 2] == ' ') {
                        screen[pos_row][pos_col - 2] = 'O';
                        screen[pos_row][pos_col] = ' ';
                        screen[pos_row][pos_col - 1] = '@';
                        --pos_col;
                    }
                    break;
                default:
                    break;
            }
            break;
        case Key::None:
        default:
            break;
    }
}

void Game::handle_falling_rocks_gems(int row, int col) {
    int falling_gem = screen[row][col] == 's';

    // start to fall
    if (screen[row + 1][col] == ' ') {
        screen[row][col] = ' ';
        screen[row + 1][col] = falling_gem ? 's' : 'o';
        return;
    }

    if (screen[row + 1][col] == 'O' || screen[row + 1][col] == '$') // check left
    {
        // check left
        if (screen[row][col - 1] == ' ' && screen[row + 1][col - 1] == ' ') {
            screen[row][col] = ' ';
            screen[row][col - 1] = falling_gem ? 'p' : 'i';
            return;
        }
        // check right
        if (screen[row][col + 1] == ' ' && screen[row + 1][col + 1] == ' ') {
            screen[row][col] = ' ';
            screen[row][col + 1] = falling_gem ? 's' : 'o';
            return;
        }
    }

    if (screen[row + 1][col] == 'o' || screen[row + 1][col] == 's') return;

    if (screen[row + 1][col] == '@') dead = 1;

    screen[row][col] = falling_gem ? '$' : 'O';
}

void Game::handle_rocks_gems(int row, int col) {
    int gem = screen[row][col] == '$';

    // start to fall
    if (screen[row + 1][col] == ' ') {
        screen[row][col] = gem ? 's' : 'o';
        return;
    }

    if (screen[row + 1][col] == 'O' || screen[row + 1][col] == '$') {
        // check left
        if (screen[row][col - 1] == ' ' && screen[row + 1][col - 1] == ' ') {
            screen[row][col] = gem ? 's' : 'o';
            return;
        }
        // check right
        if (screen[row][col + 1] == ' ' && screen[row + 1][col + 1] == ' ') {
            screen[row][col] = gem ? 's' : 'o';
            return;
        }
    }
}

void Game::update_all_elements() {
    // We will iterate over the screen from bottom to top from right to left
    for (int r = FRAME_ROWS - 1; r > 0; r--) {
        for (int c = FRAME_COLS - 2; c > 0; c--) {
            switch (screen[r][c]) {
                case 'p':
                    screen[r][c] = 's';
                    break;
                case 'i':
                    screen[r][c] = 'o';
                    break;
                case 'O':
                case '$':
                    handle_rocks_gems(r, c);
                    break;
                case 'o':
                case 's':
                    handle_falling_rocks_gems(r, c);
                    break;
                default:
                    break;
            }
        }
    }
}

void Game::Update() {
    memcpy(screen, old_screen, sizeof(screen));

    handle_player();
    update_all_elements();

    ++count;
}

void Game::Render() {
    for (int r = 0; r < FRAME_ROWS; r++) {
        for (int c = 0; c < FRAME_COLS; c++) {
            char ch = GameState::screen[r][c];

            // Change gem's color frequently
            if (ch == '$' || ch == 's') {
                int l = (int) ((GameState::count + r + 3 * c) % 16) / 8;
                CURSOR_POSITION(r + 1, c + 1);
                if (l == 0) {
                    RGBA_FG(153, 51, 255, 255);
                    RGBA_BG(10, 10, 40, 255);
                    cout << "$";
                    RGBA_RESET;
                } else {
                    RGBA_FG(33, 61, 255, 255);
                    RGBA_BG(10, 10, 40, 255);
                    cout << "$";
                    RGBA_RESET;
                }
                continue;
            }

            CURSOR_POSITION(r + 1, c + 1);

            switch (ch) {
                case '\n':
                case '\r':
                    cout << "\n";
                    break;
                case 'x': {
                    RGBA_FG(91, 91, 91, 255);
                    RGBA_BG(51, 51, 81, 255);
                    cout << "x";
                    RGBA_RESET;
                    break;
                }
                case '.': {
                    RGBA_FG(51, 0, 25, 255);
                    RGBA_BG(80, 76, 60, 255);
                    cout << " ";
                    RGBA_RESET;
                    break;
                }
                case ' ': {
                    RGBA_BG(20, 20, 40, 255);
                    cout << " ";
                    RGBA_RESET;
                    break;
                }
                case 'O': {
                    RGBA_FG(202, 198, 195, 255);
                    RGBA_BG(10, 10, 40, 255);
                    cout << "O";
                    RGBA_RESET;
                    break;
                }
                case 'o': {
                    RGBA_FG(202, 198, 19, 255);
                    RGBA_BG(10, 10, 40, 255);
                    cout << "o";
                    RGBA_RESET;
                    break;
                }
                case '@': {
                    RGBA_FG(235, 51, 51, 255);
                    RGBA_BG(10, 10, 40, 255);
                    cout << "@";
                    RGBA_RESET;
                    break;
                }
                case 'E': {
                    RGBA_FG(251, 251, 251, 255);
                    RGBA_BG(10, 10, 40, 255);
                    cout << "E";
                    RGBA_RESET;
                    break;
                }
                default:
                    break;
            }
        }
    }
    fflush(stdout);
}

void Game::End_Message() {
    SCREEN_CLEAR_ALL;
    WINDOW_RESIZE(7, FRAME_COLS);
    CURSOR_POSITION(1, 1);

    int gems;
    ifstream ifile("../files/best_status");
    ifile >> gems;
    ifile.close();

    ofstream ofile("../files/last_status");
    ofile << GameState::gems_collected;
    ofile.close();

    if (GameState::gems_collected > gems) {
        ofile.open("../files/best_status");
        ofile << GameState::gems_collected;
        ofile.close();

        cout << "Congratulations !!! You've made a new record...\n";
        if (gems > 0)
            cout << "Your past record was: " << gems << " Gems.\n";
    }

    if (GameState::dead) {
        cout << "You died after collecting " << GameState::gems_collected << " Gems!\nBetter luck next time...\n";
    } else if (GameState::won) {
        cout << "You won! And, You've collected " << GameState::gems_collected << " Gems.\n";
    }
}

void Game::Start(const string &game_level_file_path) {
    Terminal::Set();
    struct timespec sleep_time;

    GameState::Reset();
    GameState::load_level(game_level_file_path);
    Game::Render();
    GameState::find_player_position(player);
    GameState::backup();

    clock_t start, end;

    // Game Loop
    while (true) {
        start = clock();
        
        GameState::Listen_Event();
        Game::Update();
        if (won || dead) break;
        Game::Render();
        GameState::backup();
        
        end = clock();
        
        double time_taken = (double) (end - start) / CLOCKS_PER_SEC;
        if (time_taken > FRAME_CYCLE) continue;
        
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = (FRAME_CYCLE - time_taken) * 1000000000;
        nanosleep(&sleep_time, NULL);
    }
    
    Terminal::Reset();
    Game::End_Message();
}






















