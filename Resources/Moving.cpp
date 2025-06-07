#include "headers/Moving.h"
#include "headers/MyGame2048.h"

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Check if up movement is possible
bool isMoveUp(GamePlay2048 game)
{
    int n = game.dimension;
    for (int col = 0; col < n; col++)
    {
        for (int row = 0; row < n - 1; row++)
        {
            if (game.boardGame[row][col] != 0)
            { // If the current cell is non-zero
                // Check if the next cell has the value equal to the value of the current cell
                if (game.boardGame[row][col] == game.boardGame[row + 1][col])
                {
                    return true;
                }
            }
            else if (game.boardGame[row][col] == 0)
            { // If the current cell is zero
                int pos = row + 1;
                while (pos < n && game.boardGame[pos][col] == 0)
                { // Find position where the cell has non-zero value
                    pos++;
                }
                if (pos < n)
                { // If a non-zero value is found
                    return true;
                }
            }
        }
    }
    return false;
}
// Process up movement
void ProcessUp(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int col = 0; col < n; col++)
    {
        for (int row = 0; row < n - 1; row++)
        {
            int pos = row + 1; // Start position to check is the next row
            // Find position where the cell has non-zero value
            while (pos < n && game.boardGame[pos][col] == 0)
            {
                pos++;
            }
            if (pos < n)
            { // If a non-zero value is found
                if (game.boardGame[row][col] != 0)
                { // If the current cell is not zero
                    // Check if the current cell and the found cell has the same value
                    if (game.boardGame[pos][col] == game.boardGame[row][col])
                    {
                        game.boardGame[row][col] *= 2; // Combines the values
                        game.boardGame[pos][col] = 0;
                        game.score += game.boardGame[row][col]; // Calculate score
                    }
                }
                else if (game.boardGame[row][col] == 0)
                {                                                             // If the current cell is zero
                    swap(game.boardGame[pos][col], game.boardGame[row][col]); // Swap with the cell is not zero
                    pos++;
                    // Find next non-zero value
                    while (pos < n && game.boardGame[pos][col] == 0)
                    {
                        pos++;
                    }
                    if (pos < n)
                    { // If another non-zero value is found (similar to previous search)
                        if (game.boardGame[pos][col] == game.boardGame[row][col])
                        {
                            game.boardGame[row][col] *= 2; // Combines the values
                            game.boardGame[pos][col] = 0;
                            game.score += game.boardGame[row][col]; // Calculate score
                        }
                    }
                }
            }
        }
    }
}
// Check if down movement is possible
bool isMoveDown(GamePlay2048 game)
{
    int n = game.dimension;
    for (int col = 0; col < n; col++)
    {
        for (int row = n - 1; row > 0; row--)
        {
            if (game.boardGame[row][col] != 0)
            { // If the current cell is not zero
                // Check if the next cell has the value equal to the value of the current cell
                if (game.boardGame[row][col] == game.boardGame[row - 1][col])
                {
                    return true;
                }
            }
            else if (game.boardGame[row][col] == 0)
            { // If the current cell is zero
                int pos = row - 1;
                while (pos >= 0 && game.boardGame[pos][col] == 0)
                { // Find position where the cell has non-zero value
                    pos--;
                }
                if (pos >= 0)
                { // If a non-zero value is found
                    return true;
                }
            }
        }
    }
    return false;
}
// Process down movement
void ProcessDown(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int col = 0; col < n; col++)
    {
        for (int row = n - 1; row >= 0; row--)
        {
            int pos = row - 1; // Start position to check is the next row
            // Find position where the cell has non-zero value
            while (pos >= 0 && game.boardGame[pos][col] == 0)
            {
                pos--;
            }
            if (pos >= 0)
            {
                if (game.boardGame[row][col] != 0)
                { // If a non-zero value is found
                    // Check if the current cell and the found cell has the same value
                    if (game.boardGame[pos][col] == game.boardGame[row][col])
                    {
                        game.boardGame[row][col] *= 2; // Combines the values
                        game.boardGame[pos][col] = 0;
                        game.score += game.boardGame[row][col];
                    }
                }
                else if (game.boardGame[row][col] == 0)
                {                                                             // If the current cell is zero
                    swap(game.boardGame[pos][col], game.boardGame[row][col]); // Swap with the cell is not zero
                    pos--;
                    // Find next non-zero value
                    while (pos >= 0 && game.boardGame[pos][col] == 0)
                    {
                        pos--;
                    }
                    if (pos >= 0)
                    { // If another non-zero value is found (similar to previous search)
                        if (game.boardGame[pos][col] == game.boardGame[row][col])
                        {
                            game.boardGame[row][col] *= 2; // Combines the values
                            game.boardGame[pos][col] = 0;
                            game.score += game.boardGame[row][col];
                        }
                    }
                }
            }
        }
    }
}
// Check if left movement is possible
bool isMoveLeft(GamePlay2048 game)
{
    int n = game.dimension;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n - 1; col++)
        {
            if (game.boardGame[row][col] != 0)
            { // If the current cell is non-zero
                // Check if the next cell has the value equal to the value of the current cell
                if (game.boardGame[row][col] == game.boardGame[row][col + 1])
                {
                    return true;
                }
            }
            else if (game.boardGame[row][col] == 0)
            { // If the current cell is zero
                int pos = col + 1;
                while (pos < n && game.boardGame[row][pos] == 0)
                { // Find position where the cell has non-zero value
                    pos++;
                }
                if (pos < n)
                { // If a non-zero value is found
                    return true;
                }
            }
        }
    }
    return false;
}
// Process left movement
void ProcessLeft(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n - 1; col++)
        {
            int pos = col + 1; // Start position to check is the next column
            // Find position where the cell has non-zero value
            while (pos < n && game.boardGame[row][pos] == 0)
            {
                pos++;
            }
            if (pos < n)
            { // If a non-zero value is found
                if (game.boardGame[row][col] != 0)
                {
                    // Check if the current cell and the found cell has the same value
                    if (game.boardGame[row][pos] == game.boardGame[row][col])
                    {
                        game.boardGame[row][col] *= 2; // Combines the values
                        game.boardGame[row][pos] = 0;
                        game.score += game.boardGame[row][col];
                    }
                }
                else if (game.boardGame[row][col] == 0)
                {                                                             // If the current cell is zero
                    swap(game.boardGame[row][pos], game.boardGame[row][col]); // Swap with the cell is not zero
                    pos++;
                    // Find next non-zero value
                    while (pos < n && game.boardGame[row][pos] == 0)
                    {
                        pos++;
                    }
                    if (pos < n)
                    { // If another non-zero value is found (similar to previous search)
                        if (game.boardGame[row][pos] == game.boardGame[row][col])
                        {
                            game.boardGame[row][col] *= 2; // Combines the values
                            game.boardGame[row][pos] = 0;
                            game.score += game.boardGame[row][col];
                        }
                    }
                }
            }
        }
    }
}
// Check if right movement is possible
bool isMoveRight(GamePlay2048 game)
{
    int n = game.dimension;
    for (int row = 0; row < n; row++)
    {
        for (int col = n - 1; col > 0; col--)
        {
            if (game.boardGame[row][col] != 0)
            { // If the current cell is non-zero
                // Check if the next cell has the value equal to the value of the current cell
                if (game.boardGame[row][col] == game.boardGame[row][col - 1])
                {
                    return true;
                }
            }
            else if (game.boardGame[row][col] == 0)
            { // If the current cell is zero
                int pos = col - 1;
                while (pos >= 0 && game.boardGame[row][pos] == 0)
                { // Find position where the cell has non-zero value
                    pos--;
                }
                if (pos >= 0)
                { // If a non-zero value is found
                    return true;
                }
            }
        }
    }
    return false;
}
// Process right movement
void ProcessRight(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int row = 0; row < n; row++)
    {
        for (int col = n - 1; col > 0; col--)
        {
            int pos = col - 1; // Start position to check is the next column
            // Find position where the cell has non-zero value
            while (pos >= 0 && game.boardGame[row][pos] == 0)
            {
                pos--;
            }
            if (pos >= 0)
            { // If a non-zero value is found
                if (game.boardGame[row][col] != 0)
                {
                    if (game.boardGame[row][pos] == game.boardGame[row][col])
                    {
                        game.boardGame[row][col] *= 2; // Combines the values
                        game.boardGame[row][pos] = 0;
                        game.score += game.boardGame[row][col];
                    }
                }
                else if (game.boardGame[row][col] == 0)
                {                                                             // If the current cell is zero
                    swap(game.boardGame[row][pos], game.boardGame[row][col]); // Swap with the cell is not zero
                    pos--;
                    // Find next non-zero value
                    while (pos >= 0 && game.boardGame[row][pos] == 0)
                    {
                        pos--;
                    }
                    if (pos >= 0)
                    { // If another non-zero value is found (similar to previous search)
                        if (game.boardGame[row][pos] == game.boardGame[row][col])
                        {
                            game.boardGame[row][col] *= 2; // Combines the values
                            game.boardGame[row][pos] = 0;
                            game.score += game.boardGame[row][col];
                        }
                    }
                }
            }
        }
    }
}