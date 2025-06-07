#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "MyGame2048.h"

struct Player
{
    std::string name;
    int score;
    double time;

    Player(std::string name, int score, double time) : name(name), score(score), time(time) {};
};
struct PlayerNode
{
    Player player;
    PlayerNode *next;

    PlayerNode(Player player) : player(player), next(nullptr) {};
};
struct ListPlayer
{
    PlayerNode *head;
    int size;

    ListPlayer() : head(nullptr), size(0) {};

    void addPlayer(std::string, int, double);
    void removePlayer(std::string);
    bool isDuplicateName(std::string) const;
    Player Login() const;

    bool isHigherRankPlayer(Player, Player) const;
    Player getTop1Player() const;
    Player findPlayer(std::string) const;
    int getPlayerRank(Player) const;
    bool isValidUsername(std::string) const;
    void printTop20Players();

    void loadListPlayer(std::string);
    void saveListPlayer(std::string);

    void releaseListPlayer();
};

#endif //_PLAYER_H_