#include "headers/MyGame2048.h"
#include "headers/UndoRedo.h"

// MyStack implement
bool MyStack::isEmpty() const
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}

void MyStack::push(GamePlay2048 game)
{
    GameState *newNode = new GameState(game);
    newNode->next = head;
    head = newNode;
    size++;
}

GamePlay2048 MyStack::top() const
{
    if (isEmpty())
    {
        return GamePlay2048(0);
    }

    return head->game;
}

void MyStack::pop()
{
    if (head == nullptr)
        return;
    GameState *temp = head;
    head = temp->next;
    cleanUp(temp->game);
    delete temp;
    size--;
}

// Reverse a singly linked-list
void MyStack::reverse()
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    GameState *current = head;
    GameState *previous = nullptr;
    GameState *after = nullptr;

    while (current != nullptr)
    {
        after = current->next;
        current->next = previous;
        previous = current;
        current = after;
    }
    head = previous;
}

void MyStack::clear()
{
    GameState *current = head;
    while (current != nullptr)
    {
        GameState *temp = current;
        current = current->next;
        cleanUp(temp->game);
        delete temp;
    }
    size = 0;
    head = nullptr;
}

// Update the undo state with the current state if it the move is valid
void updateUndoState(GamePlay2048 &game, MyStack &undo, bool shouldContinue)
{
    if (shouldContinue)
    {
        undo.push(game);
    }
}

// Undo operation
void UndoProcess(GamePlay2048 &game, MyStack &undo, MyStack &redo)
{
    if (undo.head->next != nullptr)
    {
        updateRedoState(undo.head->game, redo); // Update redo state
        undo.pop();                             // Pop the undo stack
    }
    else
    {
        std::cout << "No available previous move.\n";
    }
    // Set the current game state to the top of the undo stack
    GamePlay2048 previousState = undo.top();
    game = previousState;
}

// Update the redo state with current game state
void updateRedoState(GamePlay2048 &game, MyStack &redo)
{
    redo.push(game);
}

// Redo operation
void RedoProcess(GamePlay2048 &game, MyStack &undo, MyStack &redo)
{
    if (!redo.isEmpty())
    {
        updateUndoState(redo.head->game, undo, true); // Update undo state
        GamePlay2048 nextState = redo.top();          // Pop the redo stack
        // Set the current game state to the next state
        game = nextState;
        redo.pop();
    }
    else
    {
        std::cout << "No available next move.\n";
    }
}