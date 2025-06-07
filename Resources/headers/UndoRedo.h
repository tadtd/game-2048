#pragma once

#ifndef _UNDOREDO_H_
#define _UNDOREDO_H_

struct GameState;
struct GamePlay2048;

struct MyStack
{
    GameState *head;
    int size;

    MyStack() : head(nullptr), size(0) {};

    MyStack(const MyStack &other) : head(nullptr), size(0)
    {
        GameState *current = other.head;
        while (current != nullptr)
        {
            push(current->game);
            current = current->next;
        }
    }

    MyStack &operator=(const MyStack &other)
    {
        if (this != &other)
        {
            clear();
            GameState *current = other.head;
            while (current != nullptr)
            {
                push(current->game);
                current = current->next;
            }
        }
        return *this;
    }
    bool isEmpty() const;
    void push(GamePlay2048);
    void pop();
    GamePlay2048 top() const;
    void reverse();
    void clear();
};

void updateUndoState(GamePlay2048 &, MyStack &, bool);
void UndoProcess(GamePlay2048 &, MyStack &, MyStack &);

void updateRedoState(GamePlay2048 &, MyStack &);
void RedoProcess(GamePlay2048 &, MyStack &, MyStack &);

#endif //_UNDOREDO_H_