#include "headers/MyGame2048.h"
#include "headers/Art.h"
#include "headers/Player.h"
#include "headers/Account.h"

int countDigits(int n)
{
    int count = 0;
    while (n > 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

int findMaxDigit(int **boardGame, int n)
{
    int maxDigits = 4;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            int digits = countDigits(boardGame[row][col]);
            if (digits > maxDigits)
            {
                maxDigits = digits;
            }
        }
    }
    return maxDigits;
}

void setColorNumber(int n)
{
    switch (n)
    {
    case 2:
        std::cout << "\033[38;5;226m";
        break;
    case 4:
        std::cout << "\033[38;5;46m";
        break;
    case 8:
        std::cout << "\033[38;5;160m";
        break;
    case 16:
        std::cout << "\033[38;5;154m";
        break;
    case 32:
        std::cout << "\033[38;5;27m";
        break;
    case 64:
        std::cout << "\033[38;5;123m";
        break;
    case 128:
        std::cout << "\033[38;5;201m";
        break;
    case 256:
        std::cout << "\033[38;5;4m";
        break;
    case 512:
        std::cout << "\033[38;5;210m";
        break;
    case 1024:
        std::cout << "\033[38;5;219m";
        break;
    case 2048:
        std::cout << "\033[38;5;195m";
        break;
    default:
        std::cout << "\033[0m";
        break;
    }
}

// Draw game board
void DisplayBoardGame(GamePlay2048 game, Player bestPlayer, bool shouldContinue, bool isUndo, bool isRedo)
{
    if (shouldContinue == false)
    {
        return;
    }

    int n = game.dimension;
    int maxDigits = findMaxDigit(game.boardGame, n);
    int cellWidth = maxDigits + 2;

    for (int row = 0; row < n; row++)
    {
        std::cout << "\t\t\t\t";
        for (int i = 0; i < n; i++)
        {
            std::cout << "+";
            for (int j = 0; j < cellWidth; j++)
            {
                std::cout << "-";
            }
        }

        std::cout << "+\n\t\t\t\t";
        for (int i = 0; i < n; i++)
        {
            std::cout << "|";
            for (int j = 0; j < cellWidth; j++)
            {
                std::cout << " ";
            }
        }
        std::cout << "|\n\t\t\t\t";

        for (int col = 0; col < n; col++)
        {
            std::cout << "| ";
            if (game.boardGame[row][col] != 0)
            {
                setColorNumber(game.boardGame[row][col]);
                int numDigits = countDigits(game.boardGame[row][col]);
                int leftPadding = (cellWidth - numDigits) / 2;
                int rightPadding = cellWidth - numDigits - leftPadding;
                std::cout << std::string(leftPadding, ' ') << game.boardGame[row][col] << std::string(rightPadding - 1, ' ');
                std::cout << "\033[0m"; // Reset color
            }
            else
            {
                std::cout << std::string(cellWidth - 1, ' ');
            }
        }
        std::cout << "|\n";

        std::cout << "\t\t\t\t";
        for (int i = 0; i < n; i++)
        {
            std::cout << "|";
            for (int j = 0; j < cellWidth; j++)
            {
                std::cout << " ";
            }
        }
        std::cout << "|\n";
    }

    std::cout << "\t\t\t\t";
    for (int i = 0; i < n; i++)
    {
        std::cout << "+";
        for (int j = 0; j < cellWidth; j++)
        {
            std::cout << "-";
        }
    }
    std::cout << "+\n";

    std::cout << "\tCURRENT SCORE: " << game.score << '\n';
    std::cout << "\tBEST SCORE: " << bestPlayer.score << '\n';
    std::cout << "\tPress [W, S, A, D or Up, Down, Left, Right] to move up, down, left, right.\n";
    std::cout << (isUndo ? "\tPress [U] to undo.\n" : "");
    std::cout << (isUndo && isRedo ? "\tPress [R] to redo.\n" : "");
    std::cout << "\tPress [E] to exit.\n";
}

// Draw menu
void DisplayMenu(int &choice, ListAccount accList)
{
    bool run = true;
    while (run)
    {
        system("cls");
        printTitle();
        std::cout << "\033[1;33m"
                  << "\t\t\t\t\t\t\tMENU\n" // Center the menu title approximately using tabs
                  << "\033[0m";

        for (int i = 1; i <= 6; i++)
        {
            if (i == choice)
            {
                if (i == 2)
                {
                    if (accList.isEmpty())
                    {
                        std::cout << "\033[1;90m\t\t\t\t\t\t> [" << i << "]. "; // Grey color for highlighted key
                    }
                    else
                    {
                        std::cout << "\033[1;32m\t\t\t\t\t\t> [" << i << "]. "; // Green color for highlighted key
                    }
                }
                else
                {
                    std::cout << "\033[1;32m\t\t\t\t\t\t> [" << i << "]. ";
                }
            }
            else
            {
                std::cout << "\033[0m\t\t\t\t\t\t [" << i << "]. "; // Default color for non-highlighted options
            }
            switch (i)
            {
            case 1:
                std::cout << "New Game\n";
                break;
            case 2:
                std::cout << "Resume\n";
                break;
            case 3:
                std::cout << "Setting\n";
                break;
            case 4:
                std::cout << "Statistics\n";
                break;
            case 5:
                std::cout << "Rules of 2048\n";
                break;
            case 6:
                std::cout << "Exit\n";
                break;
            }
        }
        std::cout << "\033[0m"; // Reset color to default

        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 72: // Up
                if (choice == 1)
                {
                    choice = 6;
                }
                else
                {
                    choice--;
                }
                break;
            case 80: // Down
                if (choice == 6)
                {
                    choice = 1;
                }
                else
                {
                    choice++;
                }
                break;
            default:
                break; // Ignore
            }
        }
        else if (key == 13)
        { // Enter
            run = false;
        }
    }
}

// Draw lose menu
void DisplayLoseMenu(int &choice, GamePlay2048 game, Player newPlayer, Player bestPlayer, ListPlayer playerList,
                     bool shouldContinue, bool isUndo, bool isRedo)
{
    bool run = true;
    while (run)
    {
        system("cls");
        DisplayBoardGame(game, bestPlayer, shouldContinue, isUndo, isRedo);
        std::cout << "\033[1;33m\t\t\tYou lose.\n";

        if (playerList.getPlayerRank(newPlayer) <= 20)
        {
            std::cout << "\t\t\tRanking: " << playerList.getPlayerRank(newPlayer) << '\n';
        }
        std::cout << "\033[0m";

        std::cout << "\t\tDo you want to play again?\n";
        if (choice == 1)
        {
            std::cout << "\033[1;32m\t\t> Yes" << "\033[0m\t\t  No\t\t  Undo\n";
        }
        else if (choice == 2)
        {
            std::cout << "\t\t  Yes\033[1;32m\t\t> No\033[0m\t\t  Undo\n";
        }
        else if (choice == 3)
        {
            std::cout << "\t\t  Yes\t\t  No\033[1;32m\t\t> Undo\n\033[0m";
        }
        std::cout << "\033[0m"; // Reset color

        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 75: // Left
                if (choice == 1)
                {
                    choice = 3;
                }
                else
                {
                    choice--;
                }
                break;
            case 77: // Right
                if (choice == 3)
                {
                    choice = 1;
                }
                else
                {
                    choice++;
                }
                break;
            default:
                continue;
            }
        }
        else if (key == 13)
        { // Enter
            run = false;
        }
    }
}

// Draw win menu
void DisplayWinMenu(int &choice, GamePlay2048 game, Player newPlayer, Player bestPlayer, ListPlayer playerList,
                    bool shouldContinue, bool isUndo, bool isRedo)
{
    bool run = true;
    while (run)
    {
        system("cls");
        DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
        std::cout << "\033[1;33m\t\t\tYou win.\n";
        if (playerList.getPlayerRank(newPlayer) <= 20)
        {
            std::cout << "\t\t\tRanking: " << playerList.getPlayerRank(newPlayer) << '\n';
        }
        std::cout << "\033[0m";
        std::cout << "\t\tKeep playing or quit the game ?\n";
        if (choice == 1)
        {
            std::cout << "\033[1;32m\t\t> Keep playing\t\t \033[0m\t\t  Quit\n";
        }
        else
        {
            std::cout << "\033[0m\t\t  Keep playing\t\t \033[1;32m\t\t> Quit\n";
        }
        std::cout << "\033[0m"; // Reset color

        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 75: // Left
                choice = 1;
                break;
            case 77: // Right
                choice = 2;
                break;
            default:
                continue;
            }
        }
        else if (key == 13)
        { // Enter
            run = false;
        }
    }
}

// Draw exit menu
void DisplayExitMenu(int &choice, GamePlay2048 game, Player newPlayer, Player bestPlayer, ListPlayer playerList,
                     bool isUndo, bool isRedo)
{

    bool run = true;
    while (run)
    {
        system("cls");
        DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
        if (playerList.getPlayerRank(newPlayer) <= 20)
        {
            std::cout << "\033[1;33m\t\t\tRanking: " << playerList.getPlayerRank(newPlayer) << '\n';
        }
        std::cout << "\033[0m";
        std::cout << "\t\t\tDo you really want to exit ?\n";
        if (choice == 1)
        {
            std::cout << "\033[1;32m\t\t\t> Yes";
            std::cout << "\033[0m\t\t\t  No\n";
        }
        else
        {
            std::cout << "\033[0m\t\t\t  Yes";
            std::cout << "\033[1;32m\t\t\t> No\n";
        }
        std::cout << "\033[0m";

        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 75:
                choice = 1;
                break;
            case 77:
                choice = 2;
                break;
            default:
                continue;
            }
        }
        else if (key == 13)
        {
            run = false;
        }
    }
}

// Draw resume menu
void DisplayResumeMenu(int &choice, int &index, ListAccount accList)
{
    bool run = true;

    while (run)
    {
        index = 1;
        system("cls");
        std::cout << "Choose an account to resume:\n";
        AccountNode *current = accList.head;
        while (current != nullptr)
        {
            if (index == choice)
            {
                std::cout << "\033[1;32m\t\t> [" << index << "]. User name: " << current->acc.name << "\033[0m\n";
            }
            else
            {
                std::cout << "\t\t  [" << index << "]. User name: " << current->acc.name << "\n";
            }
            index++;
            current = current->next;
        }

        if (index == choice)
        {
            std::cout << "\033[1;32m\t\t> [" << index << "]. Exit\033[0m\n";
        }
        else
        {
            std::cout << "\t\t  [" << index << "]. Exit\n";
        }

        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 72: // Up
                if (choice == 1)
                {
                    choice = index;
                }
                else
                {
                    choice--;
                }
                break;
            case 80: // Down
                if (choice == index)
                {
                    choice = 1;
                }
                else
                {
                    choice++;
                }
                break;
            default:
                break;
            }
        }
        else if (key == 13)
        { // Enter
            run = false;
        }
    }
}

// Draw setting menu
void DisplaySettingMenu(int &choice, GamePlay2048 &game, bool isUndo, bool isRedo)
{
    bool run = true;
    while (run)
    {
        system("cls");
        for (int i = 1; i <= 4; ++i)
        {
            if (i == choice)
            {
                std::cout << "\033[1;32m\t\t\t> [" << i << "].";
            }
            else
            {
                std::cout << "\033[0m\t\t\t [" << i << "].";
            }
            switch (i)
            {
            case 1:
                std::cout << "Set Board Size (Default: 4x4)\n"
                          << "\t\t\tCurrent size of board game: " << game.dimension << 'x' << game.dimension << '\n';
                break;
            case 2:
                std::cout << "Set Undo mode: " << (isUndo ? "On\n" : "Off\n");
                break;
            case 3:
                std::cout << "Set Redo Mode: " << ((isUndo && isRedo) ? "On\n" : "Off\n");
                break;
            case 4:
                std::cout << "Exit\n";
                break;
            }
        }
        std::cout << "\033[0m";

        int key = _getch();

        if (key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 72: // Up
                if (choice == 1)
                {
                    choice = 4;
                }
                else
                {
                    choice--;
                }
                break;
            case 80: // Down
                if (choice == 4)
                {
                    choice = 1;
                }
                else
                {
                    choice++;
                }
                break;
            default:
                break;
            }
        }
        else if (key == 13)
        { // Enter
            run = false;
        }
    }
}

// Draw menu for select dimension
void SelectDimension(int &dimension)
{
    bool chooseDimension = true;
    int selectedDimension = dimension;

    while (chooseDimension)
    {
        system("cls");
        std::cout << "\033[1;36m Choose a dimension: \033[0m\n";
        for (int i = 2; i <= 11; ++i)
        {
            if (i == selectedDimension)
            {
                std::cout << "\033[1;32m\t\t\t > ";
            }
            else
            {
                std::cout << "\033[0m\t\t\t ";
            }

            if (i >= 2 && i <= 10)
            {
                std::cout << i << 'x' << i << '\n';
            }
            else
            {
                std::cout << "Exit.\n";
            }
            std::cout << "\033[0m";
        }

        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 72: // Up
                if (selectedDimension == 2)
                {
                    selectedDimension = 11;
                }
                else
                {
                    selectedDimension--;
                }
                break;
            case 80: // Down
                if (selectedDimension == 11)
                {
                    selectedDimension = 2;
                }
                else
                {
                    selectedDimension++;
                }
                break;
            case 13: // Enter
                break;
            default:
                continue;
            }
        }
        else if (key == 13)
        {
            if (selectedDimension == 11)
            {
                chooseDimension = false;
            }
            else
            {
                dimension = selectedDimension;
                chooseDimension = false;
            }
        }
    }
}

// Draw title of the game
void printTitle()
{
    std::cout << "\t\t\t\t  ______         _______              ____        _______             \n"
              << "\t\t\t\t /  ___  \\      / _____ \\            /   |       /  ___  \\         \n"
              << "\t\t\t\t/  /   \\  |    / /     \\ \\          / /| |      /  /   \\  \\      \n"
              << "\t\t\t\t|__|   |  |    | |     | |         / / | |     /  /     \\  \\        \n"
              << "\t\t\t\t      /  /     | |     | |        / /  | |     \\  \\     /  /        \n"
              << "\t\t\t\t     /  /      | |     | |       / /   | |      \\  \\___/  /         \n"
              << "\t\t\t\t    /  /       | |     | |      / /    | |       |  ___   |           \n"
              << "\t\t\t\t   /  /        | |     | |     / /_____| |___   /  /   \\  \\         \n"
              << "\t\t\t\t  /  /         | |     | |    /________   ___| /  /     \\  \\        \n"
              << "\t\t\t\t /  /          | |     | |             | |     \\  \\     /  /        \n"
              << "\t\t\t\t/  /______     \\ \\_____/ /             | |      \\  \\___/  /       \n"
              << "\t\t\t\t|_________|     \\_______/              |_|       \\_______/          \n"
              << "\n";
}

// Print rules of 2048 game
void printRules()
{
    std::cout << "\033[1;36m \t\t\t2048 Game Rules:\n"
              << "\033[0m"
              << "\033[3m"
              << "1. Objective: Create a tile with the number 2048 on a n x n grid.\n"
              << "2. Gameplay: Slide tiles in 4 directions to merge them. New tiles (2 or 4) appear after each move.\n"
              << "3. Merging: Tiles with the same number merge into one, doubling their value.\n"
              << "4. Winning: Achieve 2048. Continue for higher scores.\n"
              << "5. Losing: Game ends when no merges or moves are possible.\n"
              << "6. Scoring: Sum of numbers on all tiles for the highest score.\n"
              << "\033[0m";
}

// Print valid username constraints
void printValidUserName()
{
    std::cout << "\tA username is considered valid if all the following constraints are satisfied:\n"
              << "\033[3m"
              << "1. The username consists of 4 to 25 characters inclusive.\n"
              << "2. The username can only contain alphanumeric characters (lowercase, uppercase, digits) and underscore (_)\n"
              << "3. The first character of the username must be an alphabetic character (lowercase or uppercase).\n"
              << "4. The username cannot end with a space.\n"
              << "\033[0m";
}