#pragma once

#ifndef _MYGAME2048_H_
#define _MYGAME2048_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <tchar.h>
#include <conio.h>
#include <random>

struct GamePlay2048
{
    int **boardGame;
    int dimension;
    int score;

    GamePlay2048(int dimension) : dimension(dimension), score(0)
    {
        boardGame = new int *[dimension];
        for (int i = 0; i < dimension; i++)
        {
            boardGame[i] = new int[dimension];
            for (int j = 0; j < dimension; j++)
            {
                boardGame[i][j] = 0;
            }
        }
    }

    // Copy constructor
    GamePlay2048(const GamePlay2048 &other) : dimension(other.dimension), score(other.score)
    {
        boardGame = new int *[dimension];
        for (int i = 0; i < dimension; i++)
        {
            boardGame[i] = new int[dimension];
            for (int j = 0; j < dimension; j++)
            {
                boardGame[i][j] = other.boardGame[i][j];
            }
        }
    }

    // Assign one object to another
    GamePlay2048 &operator=(const GamePlay2048 &other)
    {
        if (this != &other)
        {
            for (int i = 0; i < dimension; i++)
            {
                delete[] boardGame[i];
            }
            delete[] boardGame;
        }
        boardGame = nullptr;

        dimension = other.dimension;
        score = other.score;

        boardGame = new int *[dimension];
        for (int i = 0; i < dimension; i++)
        {
            boardGame[i] = new int[dimension];
            for (int j = 0; j < dimension; j++)
            {
                boardGame[i][j] = other.boardGame[i][j];
            }
        }
        return *this;
    }
};

struct GameState
{
    GamePlay2048 game;
    GameState *next;

    GameState(GamePlay2048 &game) : game(game), next(nullptr) {};
};

struct MyStack;
struct Player;
struct ListPlayer;
struct Account;
struct ListAccount;

void doGame();

void init(GamePlay2048 &);
void cleanUp(GamePlay2048 &);
void clearBoard(GamePlay2048 &);
void GameProcess(GamePlay2048 &, bool &, bool &, bool, MyStack &, MyStack &, Player &, Player &, ListPlayer &, ListAccount &);

void Menu(GamePlay2048 &, Player &, ListPlayer &, ListAccount &);
void Resume(ListAccount &, Account &, Player &, GamePlay2048 &, MyStack &);
void Setting(GamePlay2048 &, bool &, bool &);
void Statistics(ListPlayer);

void ProcessNewState(GamePlay2048 &, Player, bool, bool, bool);
void ProcessWarning(GamePlay2048, bool &, bool &);

void encode(std::string, const char);
void decode(std::string, const char);

#endif // _MYGAME2048_H_