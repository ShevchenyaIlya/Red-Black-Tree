#include <iostream>
#include "RedBlackTree.h"
using namespace std;


int main() {
    /*RedBlackTree tree;

    tree.insert(10);
    tree.insert(9);
    tree.insert(8);
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);

    tree.inorder();
    cout << endl << endl;
    tree.levelOrder();

    cout << endl << endl;
    RedBlackTree tree_2;

    tree_2.insert(1);
    tree_2.insert(2);
    tree_2.insert(3);
    tree_2.insert(4);
    tree_2.insert(5);
    tree_2.insert(6);
    tree_2.insert(7);

    tree_2.inorder();
    cout << endl << endl;
    tree_2.levelOrder();*/

    RedBlackTree tree;
    tree.insert(50);
    tree.insert(40);
    tree.insert(60);
    tree.insert(55);
    tree.insert(58);
    tree.insert(52);
    tree.insert(54);
    tree.insert(70);
    tree.insert(30);
    tree.insert(20);
    tree.insert(15);
    tree.insert(10);
    tree.insert(5);
    tree.insert(53);
    tree.remove(30);
    tree.inorder();
    cout << endl << endl;
    tree.levelOrder();
    cout << endl << endl;
    tree.postorder();
    cout << endl << endl;
    tree.preorder();
    cout << endl << tree.vertexCount();
    cout << endl << tree.lovestCommonAncestor(50, 50)->dataField;
    cout << endl << tree.blackHeight(tree.getRoot());
    return 0;
}
