#pragma once
#ifndef _ART_H_
#define _ART_H_

#include <windows.h>

struct GamePlay2048;
struct Player;
struct ListPlayer;

struct ListAccount;

int countDigits(int);
int findMaxDigits(int **, int);
void setColorNumber(int);

void DisplayBoardGame(GamePlay2048, Player, bool, bool, bool);
void DisplayMenu(int &, ListAccount);
void DisplayLoseMenu(int &, GamePlay2048, Player, Player, ListPlayer, bool, bool, bool);
void DisplayWinMenu(int &, GamePlay2048, Player, Player, ListPlayer, bool, bool, bool);
void DisplayExitMenu(int &, GamePlay2048, Player, Player, ListPlayer, bool, bool);
void DisplayResumeMenu(int &, int &, ListAccount);
void DisplaySettingMenu(int &, GamePlay2048 &, bool, bool);
void SelectDimension(int &);

void printTitle();
void printRules();
void printValidUserName();

#endif //_ART_H_