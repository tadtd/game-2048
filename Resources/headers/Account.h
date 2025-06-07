#pragma once
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "UndoRedo.h"
#include <string>

struct Account
{
    std::string name;
    int score;
    double time;
    MyStack listState;

    Account(std::string name, int score, double time, MyStack listState) : name(name), score(score), time(time), listState(listState) {};
};
struct AccountNode
{
    Account acc;
    AccountNode *next;

    AccountNode(Account acc) : acc(acc), next(nullptr) {};
};
struct ListAccount
{
    AccountNode *head;
    int size;

    ListAccount() : head(nullptr), size(0) {};

    void addAccount(Account &);
    void removeAccount(std::string);
    void chooseAccountToRemove();
    void replaceAccount(Account &);

    bool isDuplicate(std::string) const;
    bool isEmpty() const;

    void loadListAccount(std::string);
    void saveListAccount(std::string);

    void releaseListAccount();
};

#endif // _ACCOUNT_H_