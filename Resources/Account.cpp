#include "headers/MyGame2048.h"
#include "headers/Account.h"
#include "headers/Player.h"
#include "headers/UndoRedo.h"
#include "headers/Art.h"

// Add a new account to the list
void ListAccount::addAccount(Account &acc)
{
    AccountNode *newNode = new AccountNode(acc);

    if (head == nullptr)
    {
        head = newNode;
        size++;
        return;
    }

    AccountNode *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
    size++;
}

// Check if the list accounts is empty
bool ListAccount::isEmpty() const
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

// Release memory of the list accounts
void ListAccount::releaseListAccount()
{
    AccountNode *current = head;
    while (current != nullptr)
    {
        AccountNode *acc_temp = current;
        MyStack game_temp = current->acc.listState;
        current = current->next;
        game_temp.clear();
        delete acc_temp;
    }
    head = nullptr;
    size = 0;
}

// Remove an account from the list by name
void ListAccount::removeAccount(std::string nameToRemove)
{
    AccountNode *current = head;
    AccountNode *previous = nullptr;

    while (current != nullptr)
    {
        if (current->acc.name == nameToRemove)
        {
            if (previous == nullptr)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            MyStack temp = current->acc.listState;
            temp.clear();
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

// Allow user to choose an account and remove it
void ListAccount::chooseAccountToRemove()
{
    bool run = true;
    int choice = 1;
    bool chosen = false;

    while (run)
    {
        system("cls");

        std::cout << "Choose an account to remove: \n";

        int index = 1;
        AccountNode *current = head;
        while (current != nullptr && index <= 6)
        {
            if (index == choice)
            {
                std::cout << "\033[1;32m\t\t> [" << index << "]."
                          << "User name: " << current->acc.name << '\n';
            }
            else
            {
                std::cout << "\033[0m\t\t [" << index << "]."
                          << "User name: " << current->acc.name << '\n';
            }

            index++;
            current = current->next;
        }

        if (index == choice)
        {
            std::cout << "\033[1;32m\t\t> [" << index << "]. Exit\n";
        }
        else
        {
            std::cout << "\033[0m\t\t [" << index << "]. Exit";
        }
        std::cout << "\033[0m";
        int key = _getch();
        if (key == 0 || key == 224)
        {
            key = _getch();
            switch (key)
            {
            case 72:
                if (choice == 1)
                {
                    choice = index;
                }
                else
                {
                    choice--;
                }
                break;
            case 80:
                if (choice == index)
                {
                    choice = 1;
                }
                else
                {
                    choice++;
                }
                break;
            case 13:
                break;
            default:
                continue;
            }
        }
        else if (key == 13)
        {
            if (choice <= index - 1)
            {
                AccountNode *selected = head;
                for (int i = 1; i < choice; i++)
                {
                    selected = selected->next;
                }
                removeAccount(selected->acc.name);
                chosen = true;
                run = false;
            }
            else if (choice == index)
            {
                run = false;
            }
        }
    }
}

// Replace an existing accounts
void ListAccount::replaceAccount(Account &acc)
{
    AccountNode *current = head;
    while (current != nullptr && current->acc.name != acc.name)
    {
        current = current->next;
    }

    if (current != nullptr)
    {
        current->acc.score = acc.score;
        current->acc.time = acc.time;

        current->acc.listState.clear();
        MyStack undo_temp = acc.listState;
        while (!undo_temp.isEmpty())
        {
            current->acc.listState.push(undo_temp.top());
            undo_temp.pop();
        }
    }
}

// Check if an account with a given name exists in the list
bool ListAccount::isDuplicate(std::string name) const
{
    AccountNode *current = head;
    while (current != nullptr && current->acc.name != name)
    {
        current = current->next;
    }

    if (current != nullptr)
    {
        return true;
    }
    return false;
}

// Save the list to binary file
void ListAccount::saveListAccount(std::string fileName)
{
    std::ofstream outFile;
    outFile.open(fileName, std::ios::binary);

    if (!outFile.is_open())
    {
        std::cerr << "Unable to open file.\n";
    }
    else
    {
        outFile.write(reinterpret_cast<char *>(&size), sizeof(size));

        AccountNode *current = head;

        while (current != nullptr)
        {

            int nameLength = current->acc.name.size();
            outFile.write(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
            outFile.write(current->acc.name.c_str(), nameLength);

            int score = current->acc.score;
            outFile.write(reinterpret_cast<char *>(&score), sizeof(score));

            double time = current->acc.time;
            outFile.write(reinterpret_cast<char *>(&time), sizeof(time));

            int n = current->acc.listState.head->game.dimension;
            outFile.write(reinterpret_cast<char *>(&n), sizeof(n));

            int listStatesize = current->acc.listState.size;
            outFile.write(reinterpret_cast<char *>(&listStatesize), sizeof(listStatesize));

            GameState *current_temp = current->acc.listState.head;
            while (current_temp != nullptr)
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        int val = current_temp->game.boardGame[i][j];
                        outFile.write(reinterpret_cast<char *>(&val), sizeof(val));
                    }
                }
                int boardScore = current_temp->game.score;
                outFile.write(reinterpret_cast<char *>(&boardScore), sizeof(boardScore));

                current_temp = current_temp->next;
            }

            current = current->next;
        }
        outFile.close();
    }
}

// Load the list from binary file
void ListAccount::loadListAccount(std::string fileName)
{
    std::ifstream inFile(fileName, std::ios::binary);

    if (!inFile.is_open())
    {
        std::cerr << "Unable to open file.\n";
    }
    else
    {
        int listSize = 0;
        inFile.read(reinterpret_cast<char *>(&listSize), sizeof(listSize));

        for (int i = 0; i < listSize; i++)
        {
            int nameLength = 0;
            inFile.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));

            std::string name;
            name.resize(nameLength);
            inFile.read(&name[0], nameLength);

            int score = 0;
            inFile.read(reinterpret_cast<char *>(&score), sizeof(score));

            double time = 0;
            inFile.read(reinterpret_cast<char *>(&time), sizeof(time));

            int n = 0;
            inFile.read(reinterpret_cast<char *>(&n), sizeof(n));

            int listSizeStack = 0;
            inFile.read(reinterpret_cast<char *>(&listSizeStack), sizeof(listSizeStack));

            MyStack listState;
            for (int j = 0; j < listSizeStack; j++)
            {
                GamePlay2048 game(n);

                for (int x = 0; x < n; x++)
                {
                    for (int y = 0; y < n; y++)
                    {
                        int val = 0;
                        inFile.read(reinterpret_cast<char *>(&val), sizeof(val));
                        game.boardGame[x][y] = val;
                    }
                }

                int boardScore = 0;
                inFile.read(reinterpret_cast<char *>(&boardScore), sizeof(boardScore));
                game.score = boardScore;

                listState.push(game);
            }
            listState.reverse();

            Account acc(name, score, time, listState);
            addAccount(acc);
        }
        inFile.close();
    }
}