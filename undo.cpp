#include "undo.h"

void test_undo_2() {
    FileRepository repo{ "test.txt" };
    Product p = Product("a", "a", 1, "a");
    repo.add_repo(p);
    repo.add_repo(p);
    ComplexUndoAction stack;
    stack.add_child(new AddUndoAction(repo, p));
    stack.do_undo();

    repo.add_repo(p);
    repo.del_repo("a");
    stack.add_child(new RemoveUndoAction(repo, p));
    stack.do_undo();

    //repo.add_repo(p);
    repo.modify_repo("a", "b", 2, "b");
    stack.add_child(new ModUndoAction(repo, p));
    stack.do_undo();


}