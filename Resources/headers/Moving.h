#pragma once

#ifndef _MOVING_H
#define _MOVING_H

#include "MyGame2048.h"

void swap(int &, int &);
bool isMoveUp(GamePlay2048);
void ProcessUp(GamePlay2048 &);

bool isMoveDown(GamePlay2048);
void ProcessDown(GamePlay2048 &);

bool isMoveLeft(GamePlay2048);
void ProcessLeft(GamePlay2048 &);

bool isMoveRight(GamePlay2048);
void ProcessRight(GamePlay2048 &);
#endif //_MOVING_H