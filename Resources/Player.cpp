#include "headers/Player.h"
#include "headers/Art.h"

void ListPlayer::addPlayer(std::string name, int score, double time)
{
    Player newPlayer(name, score, time);
    PlayerNode *newNode = new PlayerNode(newPlayer);

    if (head == nullptr)
    {
        head = newNode;
        size++;
        return;
    }

    if (head->next == nullptr)
    {
        if (isHigherRankPlayer(newPlayer, head->player))
        {
            newNode->next = head;
            head = newNode;
        }
        else
        {
            head->next = newNode;
        }
        size++;
        return;
    }

    PlayerNode *current = head;
    PlayerNode *previous = nullptr;

    // Iterate through the list to find the correct position to insert the new player
    while (current != nullptr && isHigherRankPlayer(current->player, newPlayer))
    {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        previous->next = newNode;
        newNode->next = current;
    }
    size++;

    // Check if the size is greater than 20, remove the last player
    while (size > 20)
    {
        PlayerNode *temp = head;
        PlayerNode *tempPrev = nullptr;
        while (temp->next != nullptr)
        {
            tempPrev = temp;
            temp = temp->next;
        }
        delete temp;
        tempPrev->next = nullptr;
        size--;
    }
}

// Remove a player from a list by name
void ListPlayer::removePlayer(std::string name)
{
    if (head == nullptr)
    {
        return;
    }

    if (head->player.name == name)
    {
        PlayerNode *temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    PlayerNode *current = head;
    PlayerNode *previous = nullptr;
    while (current != nullptr && current->player.name != name)
    {
        previous = current;
        current = current->next;
    }

    // If the player is found, remove it from the list
    if (current != nullptr)
    {
        previous->next = current->next;
        delete current;
        current = nullptr;
        size--;
    }
}

// Check duplicate name in the list
bool ListPlayer::isDuplicateName(std::string name) const
{
    PlayerNode *current = head;
    while (current != nullptr)
    {
        if (name == current->player.name)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Check if a username is valid for log in
bool ListPlayer::isValidUsername(std::string name) const
{
    if (name.size() < 4 || name.size() > 25)
    {
        return false;
    }

    if (name[name.size() - 1] == ' ')
    {
        return false;
    }

    if (!isalpha(name[0]))
    {
        return false;
    }

    for (int i = 0; i < name.size(); i++)
    {
        if (!isalnum(name[i]) && name[i] != '_' && name[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

// Log in username
Player ListPlayer::Login() const
{
    system("cls");

    std::string name;
    printValidUserName();
    std::cout << "\tPlease enter a user name: ";
    std::getline(std::cin, name);

    while (!isValidUsername(name) || isDuplicateName(name))
    {
        if (!isValidUsername(name))
        {
            std::cout << "\tInvalid username.\n";
        }
        if (isDuplicateName(name))
        {
            std::cout << "\tDuplicate username.\n";
        }
        std::cout << "\tPlease enter a valid username: ";
        std::getline(std::cin, name);
    }

    return Player(name, 0, 0.0);
}

// Function to determine if player1 has higher rank than player2
bool ListPlayer::isHigherRankPlayer(Player player1, Player player2) const
{
    if (player1.score > player2.score)
    {
        return true;
    }
    else if (player1.score == player2.score)
    {
        if (player1.time < player2.time)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

// Get best player
Player ListPlayer::getTop1Player() const
{
    if (head == nullptr)
    {
        return Player("", 0, 0.0);
    }
    return head->player;
}

// Find player with the given name
Player ListPlayer::findPlayer(std::string name) const
{
    PlayerNode *current = head;

    while (current != nullptr)
    {
        if (current->player.name == name)
        {
            return current->player;
        }
        current = current->next;
    }
    return Player("", 0, 0.0);
}

// Get the rank of a specific player in the list
int ListPlayer::getPlayerRank(Player player) const
{
    int rank = 1;
    PlayerNode *current = head;
    while (current != nullptr)
    {
        if (isHigherRankPlayer(current->player, player))
        {
            rank++;
        }
        current = current->next;
    }

    return rank;
}

// Converts a given time in seconds to a string format of minutes and seconds
std::string formatTime(double time)
{
    int minute = static_cast<int>(time) / 60;
    int second = static_cast<int>(time) % 60;

    return std::to_string(minute) + "m" + std::to_string(second) + "s";
}

// Prints the top 20 players in the list
void ListPlayer::printTop20Players()
{
    PlayerNode *current = head;
    int count = 0;
    std::cout << "\033[1;36m";
    std::cout << "\t\t\t\t\tTop 20 players: \n";
    std::cout << "\033[0m";
    std::cout << "\t\t" << std::left << std::setw(5) << "Rank"
              << std::setw(30) << "Name"
              << std::setw(15) << "Score"
              << std::setw(7) << "Time" << '\n';
    std::cout << "\t\t" << std::setw(5) << "-----"
              << std::setw(30) << "------------------------------"
              << std::setw(15) << "---------------"
              << std::setw(7) << "------" << '\n';

    while (current != nullptr)
    {
        std::cout << "\t\t" << std::setw(5) << count + 1
                  << std::setw(30) << current->player.name
                  << std::setw(15) << current->player.score
                  << std::setw(7) << formatTime(current->player.time)
                  << '\n';
        count++;
        current = current->next;
    }
}

// Load the list of players from a binary file
void ListPlayer::loadListPlayer(std::string fileName)
{
    std::ifstream inFile;
    inFile.open(fileName, std::ios::binary);

    if (!inFile.is_open())
    {
        std::cerr << "Unable to open file.\n";
        return;
    }

    int numberOfPlayers = 0;
    inFile.read(reinterpret_cast<char *>(&numberOfPlayers), sizeof(numberOfPlayers));
    for (int i = 0; i < numberOfPlayers; i++)
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

        addPlayer(name, score, time);
    }
    inFile.close();
}

// Save the list of players to a binary file
void ListPlayer::saveListPlayer(std::string fileName)
{
    std::ofstream outFile;
    outFile.open(fileName, std::ios::binary);

    if (!outFile.is_open())
    {
        std::cerr << "Unable to open file.\n";
        return;
    }

    int numberOfPlayers = size;

    outFile.write(reinterpret_cast<char *>(&numberOfPlayers), sizeof(numberOfPlayers));

    PlayerNode *current = head;
    int count = 0;

    while (current != nullptr && count <= 20)
    {
        int nameLength = current->player.name.size();
        outFile.write(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));
        outFile.write(current->player.name.c_str(), nameLength);

        int score = current->player.score;
        outFile.write(reinterpret_cast<char *>(&score), sizeof(score));

        double time = current->player.time;
        outFile.write(reinterpret_cast<char *>(&time), sizeof(time));

        current = current->next;
        count++;
    }
    outFile.close();
}

// Releases all players from the list and resets the list to an empty state
void ListPlayer::releaseListPlayer()
{
    PlayerNode *current = head;
    while (current != nullptr)
    {
        PlayerNode *temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    size = 0;
}