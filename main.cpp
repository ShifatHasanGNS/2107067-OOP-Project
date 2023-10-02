#include "src/Game.h"

int main() {
    TUNNELER;

    OPTION:
    WINDOW_RESIZE(7, FRAME_COLS);
    SCREEN_CLEAR_ALL;

    cout << "1. Play #\n";
    cout << "2. Status $\n";
    cout << "0. Exit ->\n";

    int choice;
    cout << "\n\n Select an option :  ";
    cin >> choice;

    if (choice == 0) {
        SCREEN_CLEAR_ALL;
        CURSOR_SHOW;
        char res;
        cout << "\n\n Really Want to Exit? (y/n) : ";
        fflush(stdin);
        cin >> res;
        FLUSH;
        
        if (res == 'y')
            goto END_OF_PROGRAM;
        
        else goto OPTION;
    } 
    
    else if (choice == 1) {
        Game tunneler('@');
        tunneler.Start(Workspace + "/files/playground");

        char res;
        cout << "\n\n Want to return Homepage? (y/n) : ";
        fflush(stdin);
        cin >> res;
        FLUSH;
        
        if (res == 'y')
            goto OPTION;
        
        else goto STATUS;
    } 
    
    else if (choice == 2) {
        STATUS:
        WINDOW_RESIZE(7, FRAME_COLS);
        SCREEN_CLEAR_ALL;

        int gems;

        ifstream file;
        file.open(Workspace + "/files/last_status");
        file >> gems;
        file.close();
        cout << "Last Status: " << gems << " Gems\n";
        file.open(Workspace + "/files/best_status");
        file >> gems;
        file.close();
        cout << "Best Status: " << gems << " Gems\n";

        CURSOR_SHOW;
        char res;
        cout << "\n\n Want to return Homepage? (y/n) : ";
        fflush(stdin);
        cin >> res;
        FLUSH;
        
        if (res == 'y')
            goto OPTION;
        
        else goto STATUS;
    } 
    
    else {
        WINDOW_RESIZE(7, FRAME_COLS);
        SCREEN_CLEAR_ALL;
        cout << "\n Invalid Option...\n";
        sleep(2);
        
        goto OPTION;
    }

    END_OF_PROGRAM:
    SCREEN_CLEAR_ALL;
    cout << "\n Press ENTER to Leave The Playground... ";
    fflush(stdin);
    getchar();
    FLUSH;
    
    SCREEN_CLEAR_ALL;
    WINDOW_RESIZE(20, 60);
    MainTerminal;
}
