
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
const int MAX_MISSED = 20;   // Missed balls limit
const int HIGH_SCORE = 25;   // High score target

struct Ball {
    int x, y;
};

void draw(vector<Ball> &balls, int playerX) {
    system("cls");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            bool printed = false;

            // Player
            if (i == HEIGHT - 1 && (j == playerX || j == playerX + 1)) {
                cout << "0";
                printed = true;
            }

            // Falling balls
            for (auto &b : balls) {
                if (b.x == j && b.y == i) {
                    cout << "B";
                    printed = true;
                }
            }

            if (!printed) cout << ".";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    int playerX = WIDTH / 2;
    vector<Ball> balls;

    int score = 0;
    int missed = 0;
    int speed = 200;
    bool gameOver = false;

    while (!gameOver) {
        // Occasionally add new ball
        if (rand() % 10 < 2) balls.push_back({rand() % WIDTH, 0});

        // Player input
        while (_kbhit()) {
            char c = _getch();
            if (c == 'L' || c == 'l') playerX--;
            if (c == 'R' || c == 'r') playerX++;
            if (c == 'Q' || c == 'q') gameOver = true; // Quit game

            if (playerX < 0) playerX = 0;
            if (playerX > WIDTH - 2) playerX = WIDTH - 2;
        }

        // Update balls
        for (auto &b : balls) b.y++;

        // Catch or miss check
        for (int i = 0; i < balls.size(); i++) {
            if (balls[i].y == HEIGHT - 1 && (balls[i].x == playerX || balls[i].x == playerX + 1)) {
                score++;
                balls.erase(balls.begin() + i);
                i--;
            } else if (balls[i].y >= HEIGHT) {
                missed++;
                balls.erase(balls.begin() + i);
                i--;
            }
        }

        draw(balls, playerX);
        cout << "Score: " << score << "    Missed: " << missed << endl;

        // Auto game over conditions
        if (missed >= MAX_MISSED || score >= HIGH_SCORE) gameOver = true;

        Sleep(speed);
    }

    // Final static screen after game over
    system("cls");
    cout << "\n\n\tGAME OVER\n";

    // Decide message
    if (missed >= MAX_MISSED || score < HIGH_SCORE) {
        cout << "\tYOU LOSE\n";
    } else if (score >= HIGH_SCORE) {
        cout << "\tYOU WIN!\n";
    }

    cout << "\tYour Score: " << score << endl;
    cout << "\tHigh Score: " << HIGH_SCORE << endl;

    // Keep screen static until user presses a key
    while (!_kbhit()) { }

    return 0;
}
