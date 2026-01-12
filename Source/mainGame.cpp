#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>   // For sleep
#include <chrono>   // For time intervals

// Check if we are on Windows or not
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <termios.h>
    #include <unistd.h>
    #include <stdio.h>

    // Simulation of Windows _kbhit() for Linux/macOS
    int _kbhit() {
        static const int STDIN = 0;
        static bool initialized = false;
        if (!initialized) {
            termios term;
            tcgetattr(STDIN, &term);
            term.c_lflag &= ~ICANON;
            tcsetattr(STDIN, TCSANOW, &term);
            setbuf(stdin, NULL);
            initialized = true;
        }
        int bytesWaiting;
        ioctl(STDIN, FIONREAD, &bytesWaiting);
        return bytesWaiting;
    }
    // Simulation of Windows _getch()
    char _getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0) perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
        return (buf);
    }
#endif

using namespace std;

const int width = 30;
const int height = 10;

void showMenu();
void showInstructions();
void startGame(int difficulty);
void drawGame(int birdY, int pipeX, int gapY, int score, int highScore);
void updateBird(int &birdY, char input);
bool checkCollision(int birdY, int pipeX, int gapY);
void clearScreen();
void sleepMs(int ms);

int main() {
    int choice;
    do {
        showMenu();
        if (!(cin >> choice)) break;

        switch (choice) {
        case 1: {
            int difficulty;
            cout << "Select Difficulty:\n1. Easy\n2. Medium\n3. Hard\nChoice: ";
            cin >> difficulty;
            cin.ignore();
            startGame(difficulty);
            break;
        }
        case 2:
            showInstructions();
            break;
        case 3:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 3);

    return 0;
}

void showMenu() {
    cout << "\n===== FLAPPY BIRD (PORTABLE) =====\n";
    cout << "1. Start Game\n";
    cout << "2. Instructions\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
}

void showInstructions() {
    cout << "\n--- Instructions ---\n";
    cout << "Press 'w' to jump\n";
    cout << "Bird falls automatically (gravity)\n";
    cout << "Avoid hitting the pipes\n";
    cout << "Passing a pipe gives +1 score\n\n";
}

void startGame(int difficulty) {
    int birdY = height / 2;
    int pipeX = width - 1;
    int gapY;
    int score = 0;
    static int highScore = 0;
    char input = ' ';
    int speed;

    if (difficulty == 1) speed = 1;
    else if (difficulty == 2) speed = 2;
    else speed = 3;

    srand(time(0));
    gapY = rand() % (height - 3) + 1;

    while (true) {
        clearScreen();
        drawGame(birdY, pipeX, gapY, score, highScore);

        input = ' ';
        if (_kbhit()) input = _getch();

        updateBird(birdY, input);

        pipeX -= speed;

        if (pipeX < 0) {
            pipeX = width - 1;
            gapY = rand() % (height - 3) + 1;
            score++;
        }

        if (checkCollision(birdY, pipeX, gapY)) {
            if (score > highScore) highScore = score;
            clearScreen();
            cout << "GAME OVER\n";
            cout << "Score: " << score << endl;
            cout << "High Score: " << highScore << endl;
            cout << "Press any key to return to menu...\n";
            _getch();
            break;
        }

        sleepMs(150);
    }
}

void drawGame(int birdY, int pipeX, int gapY, int score, int highScore) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (x == 5 && y == birdY) cout << "O";
            else if (x == pipeX && (y < gapY || y > gapY+2)) cout << "|";
            else cout << " ";
        }
        cout << endl;
    }
    cout << "Score: " << score << "   High Score: " << highScore << endl;
}

void updateBird(int &birdY, char input) {
    birdY++;
    if (input == 'w' || input == 'W') birdY -= 3; // Adjusted jump for better feel

    if (birdY < 0) birdY = 0;
    if (birdY >= height) birdY = height - 1;
}

bool checkCollision(int birdY, int pipeX, int gapY) {
    // Collision logic: bird is at x=5
    if (pipeX <= 5 && pipeX >= 5 - 1) { // Adjusted for speed jumps
        if (birdY < gapY || birdY > gapY+2) return true;
    }
    return false;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // ANSI escape code: Clear screen and move cursor to (1,1)
    cout << "\033[2J\033[1;1H";
#endif
}

void sleepMs(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
