#include "headers/MyGame2048.h"
#include "headers/Art.h"
#include "headers/Moving.h"
#include "headers/UndoRedo.h"
#include "headers/Player.h"
#include "headers/Account.h"

void doGame()
{

    GamePlay2048 game(4);  // Initialize game with 4x4 board
    ListPlayer playerList; // List player in top 20
    ListAccount accList;   // List account to resume

    const char key = 172;

    // Decode, load memory
    decode("ListPlayer.bin", key);
    playerList.loadListPlayer("ListPlayer.bin");
    Player bestPlayer = playerList.getTop1Player(); // Get the best player

    decode("ListAccount.bin", key);
    accList.loadListAccount("ListAccount.bin");

    // Main menu loop
    Menu(game, bestPlayer, playerList, accList);

    // Save, encode and clean up memory
    playerList.saveListPlayer("ListPlayer.bin");
    encode("ListPlayer.bin", key);
    playerList.releaseListPlayer();

    accList.saveListAccount("ListAccount.bin");
    encode("ListAccount.bin", key);
    accList.releaseListAccount();

    cleanUp(game);
}

// Initialize board game
void init(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            game.boardGame[row][col] = 0;
        }
    }
    // game.boardGame[0][0] = 2;
    // game.boardGame[0][1] = 4;
    // game.boardGame[0][2] = 8;
    // game.boardGame[0][3] = 16;

    // game.boardGame[1][0] = 32;
    // game.boardGame[1][1] = 64;
    // game.boardGame[1][2] = 128;
    // game.boardGame[1][3] = 256;

    // game.boardGame[2][0] = 512;
    // game.boardGame[2][1] = 1024;
    // game.boardGame[2][2] = 1024;
    // game.boardGame[2][3] = 128;

    // game.boardGame[3][0] = 8;
    // game.boardGame[3][1] = 16;
    // game.boardGame[3][2] = 32;
    // game.boardGame[3][3] = 64;

    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<> dist(1, n * n);
    std::uniform_int_distribution<> valueDist(1, 10);

    // game.boardGame[0][0] = 1024;
    // game.boardGame[0][1] = 1024;

    int randomElement1 = 0;
    int randomElement2 = 0;

    do
    {
        randomElement1 = dist(engine);
        randomElement2 = dist(engine);
    } while (randomElement1 == randomElement2);

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (randomElement1 == n * row + col + 1)
            {
                int x = valueDist(engine);
                if (x <= 8)
                {
                    game.boardGame[row][col] = 2;
                }
                else
                {
                    game.boardGame[row][col] = 4;
                }
            }
            if (randomElement2 == n * row + col + 1)
            {
                int x = valueDist(engine);
                if (x <= 8)
                {
                    game.boardGame[row][col] = 2;
                }
                else
                {
                    game.boardGame[row][col] = 4;
                }
            }
        }
    }
}

// Clean up dynamically allocated memory
void cleanUp(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int i = 0; i < n; i++)
    {
        delete[] game.boardGame[i];
    }
    delete[] game.boardGame;
    game.dimension = 0;
    game.boardGame = nullptr;
}

// Clear the game board and reset score
void clearBoard(GamePlay2048 &game)
{
    int n = game.dimension;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            game.boardGame[row][col] = 0;
        }
    }
    game.score = 0;
}

// Encode file
void encode(std::string fileName, const char key)
{
    std::ifstream inFile;
    inFile.open(fileName, std::ios::binary);
    if (!inFile.is_open())
    {
        return;
    }
    else
    {
        inFile.seekg(0, std::ios::end);
        std::size_t fileSize = inFile.tellg();
        char *data = new char[fileSize];
        inFile.seekg(0, std::ios::beg);
        inFile.read(data, fileSize);
        inFile.close();

        std::ofstream outFile;
        outFile.open(fileName, std::ios::binary);
        if (!outFile.is_open())
        {
            return;
        }
        else
        {
            for (std::size_t i = 0; i < fileSize; i++)
            {
                data[i] += key;
            }

            outFile.write(data, fileSize);
            outFile.close();
        }
        delete[] data;
    }
}

// Decode file
void decode(std::string fileName, const char key)
{
    std::ifstream inFile;
    inFile.open(fileName, std::ios::binary);
    if (!inFile.is_open())
    {
        return;
    }
    else
    {
        inFile.seekg(0, std::ios::end);
        std::size_t fileSize = inFile.tellg();
        char *data = new char[fileSize];
        inFile.seekg(0, std::ios::beg);
        inFile.read(data, fileSize);
        inFile.close();

        std::ofstream outFile;
        outFile.open(fileName, std::ios::binary);
        if (!outFile.is_open())
        {
            return;
        }
        else
        {
            for (std::size_t i = 0; i < fileSize; i++)
            {
                data[i] -= key;
            }

            outFile.write(data, fileSize);
            outFile.close();
        }
        delete[] data;
    }
}

// Menu function to display and handle game menu
void Menu(GamePlay2048 &game, Player &bestPlayer, ListPlayer &playerList, ListAccount &accList)
{
    bool isUndo = true;
    bool isRedo = true;
    int choice = 1; // Start with the first choice selected
    bool run = true;

    MyStack undo; // Stack for undo operation
    MyStack redo; // Stack for redo operation

    // Main menu loop
    while (run)
    {
        DisplayMenu(choice, accList); // Display menu options
        switch (choice)
        {
        case 1:
        { // New game
            system("cls");

            init(game);
            Player newPlayer = playerList.Login();                    // Log in player
            DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo); // Display the game board
            GameProcess(game, isUndo, isRedo, false, undo, redo, newPlayer, bestPlayer, playerList, accList);

            clearBoard(game); // Clear the game board
            undo.clear();     // Clear undo stack
            redo.clear();     // Clear redo stack
            break;
        }
        case 2:
        { // Resume
            system("cls");

            Player newPlayer("", 0, 0);
            Account accResume("", 0, 0, undo);

            GamePlay2048 gameResume(4);
            Resume(accList, accResume, newPlayer, gameResume, undo); // Resume a saved game
            if (!newPlayer.name.empty())
            {
                DisplayBoardGame(gameResume, bestPlayer, true, isUndo, isRedo);
                GameProcess(gameResume, isUndo, isRedo, true, undo, redo, newPlayer, bestPlayer, playerList, accList);

                cleanUp(gameResume); // Clean up resumed game
                undo.clear();
                redo.clear();
            }
            break;
        }
        case 3:
        { // Setting
            system("cls");
            Setting(game, isUndo, isRedo);
            break;
        }
        case 4:
        { // Statistics
            system("cls");
            Statistics(playerList);
            break;
        }
        case 5:
        { // Rules of 2048 game
            system("cls");
            int key = 0;
            printRules();
            std::cout << "\033[1;93m";
            std::cout << "\t Press Enter to exit\n";
            std::cout << "\033[0m";
            while (1)
            {
                key = _getch();

                if (key == 13)
                {
                    break;
                }
                else
                {
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            break;
        }
        case 6:
        { // Exit
            system("cls");
            std::cout << "Thanks for playing UwU\n";
            run = false; // Exit menu loop
            break;
        }
        }
    }
    undo.clear();
    redo.clear();
}

void GameProcess(GamePlay2048 &game, bool &isUndo, bool &isRedo, bool isResume, MyStack &undo, MyStack &redo, Player &newPlayer, Player &bestPlayer, ListPlayer &playerList, ListAccount &accList)
{
    char choice;     // Player input choice
    bool run = true; // Game loop
    bool shouldContinue = true;
    bool isGameOver = false;
    bool isWinning = false;
    bool continueAfterWin = false;

    undo.push(game); // Save the initial game state to the undo stack

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    double time_temp = newPlayer.time;

    // Main game loop
    while (run)
    {
        ProcessWarning(game, isGameOver, isWinning);

        // Game over
        if ((isGameOver && !isWinning) || (isGameOver && continueAfterWin) || (isResume && isGameOver))
        {

            int choice = 1; // 1 for Yes, 2 for No, 3 for Undo
            DisplayLoseMenu(choice, game, newPlayer, bestPlayer, playerList, shouldContinue, isUndo, isRedo);
            if (choice == 1)
            { // Yes
                isGameOver = false;
                isWinning = false;
                continueAfterWin = false;

                clearBoard(game);
                undo.clear();
                redo.clear();

                init(game);
                if (isUndo)
                {
                    undo.push(game);
                }
                system("cls");

                newPlayer.score = 0;
                newPlayer.time = 0;

                start = std::chrono::system_clock::now();

                DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
            }
            else if (choice == 2)
            { // No
                run = false;
            }
            else if (choice == 3)
            {
                undo.pop();
                GamePlay2048 gamePrevious = undo.top();
                game = gamePrevious;
                isGameOver = false;

                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                newPlayer.time = elapsed.count();

                if (playerList.isDuplicateName(newPlayer.name))
                {
                    Player foundPlayer = playerList.findPlayer(newPlayer.name);

                    if (playerList.getPlayerRank(newPlayer) <= playerList.getPlayerRank(foundPlayer))
                    {
                        playerList.removePlayer(foundPlayer.name);
                        playerList.addPlayer(newPlayer.name, newPlayer.score, newPlayer.time);
                    }
                }
                else if (playerList.getPlayerRank(newPlayer) < 20)
                {
                    playerList.addPlayer(newPlayer.name, newPlayer.score, newPlayer.time);
                }

                system("cls");
                DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
            }
        }
        // Continue after win
        else if (((isWinning && !continueAfterWin) || (isResume && isWinning && !continueAfterWin)) && !continueAfterWin)
        {
            int choice = 1; // 1 for Yes, 2 for No
            DisplayWinMenu(choice, game, newPlayer, bestPlayer, playerList, shouldContinue, isUndo, isRedo);
            if (choice == 1)
            { // Yes
                continueAfterWin = true;

                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                newPlayer.time = elapsed.count();

                if (playerList.isDuplicateName(newPlayer.name))
                {
                    Player foundPlayer = playerList.findPlayer(newPlayer.name);

                    if (playerList.getPlayerRank(newPlayer) <= playerList.getPlayerRank(foundPlayer))
                    {
                        playerList.removePlayer(foundPlayer.name);
                        playerList.addPlayer(newPlayer.name, newPlayer.score, newPlayer.time);
                    }
                }
                else if (playerList.getPlayerRank(newPlayer) < 20)
                {
                    playerList.addPlayer(newPlayer.name, newPlayer.score, newPlayer.time);
                }
                system("cls");
                DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
            }
            else if (choice == 2)
            { // No
                run = false;
            }
        }
        else
        {
            std::cout << "Enter directions: ";
            choice = getch();

            switch (choice)
            {
            case 'W':
            case 'w': // Move up
            case 72:
                system("cls");
                redo.clear();
                shouldContinue = isMoveUp(game);
                ProcessUp(game);
                ProcessNewState(game, bestPlayer, shouldContinue, isUndo, isRedo);
                newPlayer.score = game.score; // Update player's score
                if (newPlayer.score > bestPlayer.score)
                {
                    bestPlayer = newPlayer; // Update best player
                }
                updateUndoState(game, undo, shouldContinue); // Update undo and redo stack
                DisplayBoardGame(game, bestPlayer, shouldContinue, isUndo, isRedo);
                std::cout << "Previous move: Up\n";
                break;

            case 'S':
            case 's': // Move down
            case 80:
                system("cls");
                redo.clear();
                shouldContinue = isMoveDown(game);
                ProcessDown(game);
                ProcessNewState(game, bestPlayer, shouldContinue, isUndo, isRedo);
                newPlayer.score = game.score; // Update player's score
                if (newPlayer.score > bestPlayer.score)
                {
                    bestPlayer = newPlayer; // Update best player
                }
                updateUndoState(game, undo, shouldContinue); // Update undo and redo stack
                DisplayBoardGame(game, bestPlayer, shouldContinue, isUndo, isRedo);
                std::cout << "Previous move: Down\n";
                break;

            case 'A':
            case 'a': // Move left
            case 75:
                system("cls");
                redo.clear();
                shouldContinue = isMoveLeft(game);
                ProcessLeft(game);
                ProcessNewState(game, bestPlayer, shouldContinue, isUndo, isRedo);
                newPlayer.score = game.score; // Update player's score
                if (newPlayer.score > bestPlayer.score)
                {
                    bestPlayer = newPlayer; // Update best player
                }
                updateUndoState(game, undo, shouldContinue); // Update undo and redo stack
                DisplayBoardGame(game, bestPlayer, shouldContinue, isUndo, isRedo);
                std::cout << "Previous move: Left\n";
                break;

            case 'D':
            case 'd': // Move right
            case 77:
                system("cls");
                redo.clear();
                shouldContinue = isMoveRight(game);
                ProcessRight(game);
                ProcessNewState(game, bestPlayer, shouldContinue, isUndo, isRedo);
                newPlayer.score = game.score; // Update player's score
                if (newPlayer.score > bestPlayer.score)
                {
                    bestPlayer = newPlayer; // Update best player
                }
                updateUndoState(game, undo, shouldContinue);
                DisplayBoardGame(game, bestPlayer, shouldContinue, isUndo, isRedo);
                std::cout << "Previous move: Right\n";
                break;

            case 'U': // Undo process
            case 'u':
                if (isUndo)
                {
                    system("cls");
                    UndoProcess(game, undo, redo); // Undo
                    DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
                }
                else
                {
                    std::cout << "Invalid choice. Please try again.\n";
                }
                break;

            case 'R': // Redo process
            case 'r':
                if (isUndo)
                {
                    system("cls");
                    if (isRedo)
                    {
                        RedoProcess(game, undo, redo); // Redo
                        DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                }
                else
                {
                    std::cout << "Invalid choice. Please try again.\n";
                }
                break;

            case 'E':
            case 'e': // Player exit
            {
                int choice = 1;
                DisplayExitMenu(choice, game, newPlayer, bestPlayer, playerList, isUndo, isRedo);
                if (choice == 1)
                {
                    run = false;
                }
                else if (choice == 2)
                {
                    system("cls");
                    DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
                }
                break;
            }
            }
        }
    }

    // Calculate and update the player's game time duration
    newPlayer.time = time_temp;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    newPlayer.time += elapsed.count();

    // Add and remove account to the list account to resume
    Account newAccount(newPlayer.name, newPlayer.score, newPlayer.time, undo);
    if (accList.isDuplicate(newAccount.name))
    {
        accList.replaceAccount(newAccount);
    }
    else if (accList.size > 4)
    {
        while (accList.size > 4)
        {
            accList.chooseAccountToRemove();
        }
        accList.addAccount(newAccount);
    }
    else
    {
        accList.addAccount(newAccount);
    }
    // Check duplicate player in list and replace it if this player has higher record
    if (playerList.isDuplicateName(newPlayer.name))
    {
        Player foundPlayer = playerList.findPlayer(newPlayer.name);
        if (playerList.getPlayerRank(newPlayer) <= playerList.getPlayerRank(foundPlayer))
        {
            playerList.removePlayer(foundPlayer.name);
            playerList.addPlayer(newPlayer.name, newPlayer.score, newPlayer.time);
        }
    }
    else if (playerList.getPlayerRank(newPlayer) <= 20)
    {
        playerList.addPlayer(newPlayer.name, newPlayer.score, newPlayer.time);
        std::cout << playerList.getPlayerRank(newPlayer) << '\n';
    }
}

// Resume game
void Resume(ListAccount &accList, Account &acc, Player &player, GamePlay2048 &gameResume, MyStack &undo)
{
    if (accList.isEmpty())
    {
        std::cout << "No accounts available to resume.\n";
        return;
    }

    bool run = true;
    int index = 1;
    int choice = 1;

    while (run)
    {
        DisplayResumeMenu(choice, index, accList);
        if (choice < index)
        {
            AccountNode *selected = accList.head;
            for (int i = 1; i < choice; i++)
            {
                selected = selected->next;
            }
            gameResume = selected->acc.listState.top(); // Restore a game state from selected account
            player = Player(selected->acc.name, selected->acc.score, selected->acc.time);

            // Clear current undo stack
            undo.clear();
            // Transfer undo states
            MyStack undo_temp = selected->acc.listState;
            while (!undo_temp.isEmpty())
            {
                undo.push(undo_temp.top());
                undo_temp.pop();
            }
            if (undo.head->next != nullptr)
            {
                undo.pop();
            }

            run = false;
        }
        else if (choice == index)
        {
            run = false;
        }
    }
}

// Setting menu
void Setting(GamePlay2048 &game, bool &isUndo, bool &isRedo)
{
    bool run = true;
    int choice = 1; // Start with the first choice selected

    while (run)
    {
        DisplaySettingMenu(choice, game, isUndo, isRedo);

        switch (choice)
        {
        case 1:
        { // Set the board size
            int dimension = 4;
            SelectDimension(dimension);
            game = GamePlay2048(dimension);
            break;
        }
        case 2: // Turn on / off undo
            isUndo = !isUndo;
            if (!isUndo)
            {
                isRedo = false;
            }
            break;
        case 3: // Turn on / off redo
            if (!isUndo)
            {
                std::cout << "\033[1m\tCan't turn on / turn off redo mode because undo mode is off.\n\033[0m";
                _getch();
            }
            else
            {
                isRedo = !isRedo;
            }
            break;
        case 4:
            std::cout << "Exiting.\n";
            run = false;
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }
}

// Print top 20 players
void Statistics(ListPlayer playerList)
{
    bool run = true;
    int choice;
    system("cls");
    playerList.printTop20Players();
    std::cout << "\033[1;93m";
    std::cout << "\t Press Enter to exit\n";
    std::cout << "\033[0m";
    while (run)
    {
        choice = _getch();
        if (choice == 13)
        {
            run = false;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Update new state of game board
void ProcessNewState(GamePlay2048 &game, Player bestPlayer, bool shouldContinue, bool isUndo, bool isRedo)
{
    int n = game.dimension;

    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<> dist(0, n - 1);
    std::uniform_int_distribution<> valueDist(1, 10);

    if (shouldContinue)
    {
        bool run = true;
        do
        {
            int i = dist(random_device);
            int j = dist(random_device);

            if (game.boardGame[i][j] == 0)
            {
                int x = valueDist(random_device);
                if (x <= 8)
                {
                    game.boardGame[i][j] = 2;
                }
                else
                {
                    game.boardGame[i][j] = 4;
                }
                run = false;
            }
        } while (run);
    }
    else
    {
        DisplayBoardGame(game, bestPlayer, true, isUndo, isRedo);
        std::cout << "Invalid move.\n";
    }
}

// Check if win or lose
void ProcessWarning(GamePlay2048 game, bool &isGameOver, bool &isWinning)
{
    int n = game.dimension;
    if (!isMoveUp(game) && !isMoveDown(game) && !isMoveLeft(game) && !isMoveRight(game))
    {
        isGameOver = true;
    }

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (game.boardGame[row][col] >= 2048)
            {
                isWinning = true;
                break;
            }
        }
        if (isWinning)
        {
            break;
        }
    }
}