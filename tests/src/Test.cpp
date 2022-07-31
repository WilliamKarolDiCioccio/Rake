#include <iostream>

#include <CppUnitTest.h>

#include "Containers/BinaryTree.hpp"

using namespace std;
using namespace Rake::Containers;

int main()
{
    BinaryTree<char> tree;
    tree.AddNode('A');
    tree.GetRoot()->childRight = tree.AddNode('B');
    tree.GetRoot()->childRight->childRight = tree.AddNode('C');
    tree.GetRoot()->childLeft = tree.AddNode('D');

    cout << tree.GetRoot()->data << '\n';
    cout << tree.GetRoot()->childRight->data << '\n';
    cout << tree.GetRoot()->childRight->childRight->data << '\n';
    cout << tree.GetRoot()->childLeft->data << '\n';

    tree.RemoveNode(tree.GetRoot()->childRight, tree.GetRoot()->childLeft);

    cout << tree.GetRoot()->childLeft->data << '\n';
    cout << tree.GetRoot()->childLeft->childRight->data << '\n';

    system("pause");

    return 0;
}
