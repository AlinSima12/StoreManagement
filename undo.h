#pragma once
#include "repo_store.h"
#include "produs.h"

#include <assert.h>
#include <stack>

class UndoAction {
public:
    virtual void do_undo() = 0;
    ~UndoAction() = default;
};

class AddUndoAction :public UndoAction {
private:
    RepoAbstract& repo;
    Product produs;

public:
    AddUndoAction(RepoAbstract& _repo, Product& _produs) : repo{ _repo }, produs{ _produs } {};
    void do_undo() {
        this->repo.del_repo(this->produs.get_name());
        int i = 1;
        i++;
    }
};

class ModUndoAction :public UndoAction {
private:
    RepoAbstract& repo;
    Product produs;
public:


    ModUndoAction(RepoAbstract& _repo, Product& _produs) : repo{ _repo }, produs{ _produs } {};
    void do_undo() {
        this->repo.modify_repo(this->produs.get_name(), this->produs.get_type(), this->produs.get_price(), this->produs.get_producer());
    }
};


class RemoveUndoAction :public UndoAction {
private:
    RepoAbstract& repo;
    Product produs;

public:
    RemoveUndoAction(RepoAbstract& _repo, Product& _produs) : repo{ _repo }, produs{ _produs } {};
    void do_undo() {
        this->repo.add_repo(this->produs);
    }
};

class ComplexUndoAction :public UndoAction {
private:
    std::stack<UndoAction*> children;
public:
    ComplexUndoAction() : UndoAction() {};
    void add_child(UndoAction* child) {
        this->children.push(child);
    }
    void do_undo() {
        if (!this->children.empty()) {
            this->children.top()->do_undo();
            this->children.pop();
        }
    }
};

void test_undo_2();
