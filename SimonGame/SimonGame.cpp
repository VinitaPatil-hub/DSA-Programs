#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <limits> // To clear input buffer

using namespace std;

enum Color {
    RED,
    GREEN,
    BLUE,
    YELLOW
};

const string colorNames[] = { "Red", "Green", "Blue", "Yellow" };

// Function to get a random color
Color getRandomColor() {
    return static_cast<Color>(rand() % 4);
}

// Function to display the current sequence
void displaySequence(queue<Color> colorQueue) {
    cout << "Current Sequence: ";
    while (!colorQueue.empty()) {
        cout << colorNames[colorQueue.front()] << " ";
        colorQueue.pop();
    }
    cout << endl;
}

// Function to play the Simon game
void playSimonGame() {
    queue<Color> colorQueue;
    int round = 0;

    while (true) {
        Color newColor = getRandomColor();
        colorQueue.push(newColor);
        round++;
        displaySequence(colorQueue);

        // Set time limit based on the round
        int timeLimit = 5 + round * 2;  // Start with 5 seconds and increase by 2 each round
        cout << "Repeat the sequence (Enter numbers: 0-3) within " << timeLimit << " seconds: ";

        int playerInput[100];
        bool timedOut = false;

        // Start the timer
        time_t startTime = time(0);

        for (int i = 0; i < round; ++i) {
            cin >> playerInput[i];

            // Check the elapsed time after each input
            time_t currentTime = time(0);
            int elapsedTime = difftime(currentTime, startTime);

            if (elapsedTime > timeLimit) {
                timedOut = true;
                break;
            }
        }

        if (timedOut) {
            cout << "\nTime's up! You failed to repeat the sequence in time." << endl;
            cout << "You reached round " << round << "." << endl;
            break;
        }

        bool isCorrect = true;
        queue<Color> tempQueue = colorQueue;
        for (int i = 0; i < round; ++i) {
            if (tempQueue.empty() || tempQueue.front() != playerInput[i]) {
                isCorrect = false;
                break;
            }
            tempQueue.pop();
        }

        if (isCorrect) {
            cout << "Correct! Get ready for the next round." << endl;
        } else {
            cout << "Wrong! Game Over. You reached round " << round << "." << endl;
            break;
        }

        // Delay for a short time before the next round (can use a simple loop or other mechanisms here)
    }
}



int main() {
    srand(time(0)); // Seed the random number generator
    char playAgain;

    do {
        cout << "\n                  Welcome to Simon Game!                 \n";
        cout << "Red == 0      Green == 1      Blue == 2      Yellow == 3\n" << endl;
        playSimonGame();
        
        // Clear input buffer before asking to play again
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        // Clear the console before the next game if the user wants to play again
        if (playAgain == 'y' || playAgain == 'Y') {
            system("cls");
        }

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\n\nThank you for playing!" << endl;
    return 0;
}
