//
// Created by shevchenya on 16/04/2020.
//
#include <iostream>
#include <queue>
#include "RedBlackTree.h"
using namespace std;


Vertex::Vertex(int data)
{
    this->dataField = data;
    this->color = RED;
    left = right = parent = nullptr;
}

RedBlackTree::RedBlackTree()
{
    this->root = nullptr;
    this->count = 0;
}

int RedBlackTree::vertexCount()
{
    return this->count;
}

Vertex *RedBlackTree::getRoot()
{
    return this->root;
}

void RedBlackTree::rotateLeft(Vertex *vertex)
{
    Vertex *pointer = vertex->right;
    vertex->right = pointer->left;

    if (vertex->right != nullptr)
        vertex->right->parent = vertex;

    pointer->parent = vertex->parent;

    if (vertex->parent == nullptr)
        this->root = pointer;
    else if (vertex == vertex->parent->left)
        vertex->parent->left = pointer;
    else
        vertex->parent->right = pointer;

    pointer->left = vertex;
    vertex->parent = pointer;
}

void RedBlackTree::rotateRight(Vertex *vertex)
{
    Vertex *pointer = vertex->left;
    vertex->left = pointer->right;

    if (vertex->left != nullptr)
        vertex->left->parent = vertex;

    pointer->parent = vertex->parent;

    if (vertex->parent == nullptr)
        this->root = pointer;
    else if (vertex == pointer->parent->left)
        vertex->parent->left = pointer;
    else
        vertex->parent->right = pointer;

    pointer->right = vertex;
    vertex->parent = pointer;
}

void RedBlackTree::fixInsertViolations(Vertex* vertex)
{
    Vertex *parent = nullptr;
    Vertex *grandparent = nullptr;

    while ((vertex != root) && (vertex->color != BLACK) && (vertex->parent->color == RED))
    {
        parent = vertex->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left)
        {
            Vertex *uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                vertex = grandparent;
            }
            else {
                if (vertex == parent->right) {
                    rotateLeft(parent);
                    vertex = parent;
                    parent = vertex->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                vertex = parent;
            }
        }
        else {
            Vertex *uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                vertex = grandparent;
            }
            else {
                if (vertex == parent->left)
                {
                    rotateRight(parent);
                    vertex = parent;
                    parent = vertex->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                vertex = parent;
            }

        }
    }

    root->color = BLACK;
}

void RedBlackTree::insert(int data)
{
    auto *node = new Vertex(data);

    if (this->root == nullptr)
    {
        node->color = BLACK;
        this->root = node;
        this->count++;
    }
    else {
        Vertex *pointer = this->root;
        Vertex *parent = nullptr;

        bool equal = false;
        while (pointer != nullptr) {
            parent = pointer;
            if (pointer->dataField < node->dataField)
                pointer = pointer->right;
            else if (pointer->dataField > node->dataField)
                pointer = pointer->left;
            else {
                equal = true;
                break;
            }
        }

        if (!equal)
        {
            this->count++;
            node->parent = parent;

            if (parent != nullptr && parent->dataField < node->dataField)
                parent->right = node;
            else if (parent != nullptr && parent->dataField > node->dataField)
                parent->left = node;
            fixInsertViolations(node);
        }
    }

}

/*void RedBlackTree::remove(int key)
{
    Vertex *pointer = root;

    while (pointer->dataField != key)
    {
        if (pointer->dataField < key)
            pointer = pointer->right;
        else
            pointer = pointer->left;
    }

    if (pointer->left == nullptr && pointer->right == nullptr)
    {
        if (pointer == this->root)
        {
            this->root = nullptr;
        }
        else {
            Vertex *parent = pointer->parent;
            if (pointer == parent->left)
                parent->left = nullptr;
            else
                parent->right = nullptr;
        }
    }
    else if (pointer->right == nullptr || pointer->left == nullptr)
    {
        Vertex *children = pointer->right == nullptr ? pointer->left: pointer->right;
        Vertex *parent = pointer->parent;

        if (pointer == parent->left)
        {
            parent->left = children;
            children->parent = parent;
        }
        else {
            parent->right = children;
            children->parent = parent;
        }
    }
    else
    {
        // TODO: Change stupid name
        Vertex *swapWith = pointer->right;
        while (swapWith->left != nullptr)
        {
            swapWith = swapWith->left;
        }

        pointer->dataField = swapWith->dataField;
        Vertex *parent = swapWith->parent;
        if (swapWith == parent->left)
        {
            parent->left = swapWith->right;
            if (swapWith->right != nullptr)
                swapWith->right->parent = parent;
        }
        else {
            parent->right = swapWith->left;
            if (swapWith->left != nullptr)
                swapWith->right->parent = parent;
        }
        pointer = swapWith;
    }
    if (pointer->color == BLACK)
        fixRemoving(pointer);
}*/

void RedBlackTree::fixRemoveViolations(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    if (vertex == this->root)
    {
        root = nullptr;
        return;
    }

    if (vertex->color == RED || (vertex->left != nullptr && vertex->left->color == RED) || (vertex->right != nullptr && vertex->right->color == RED))
    {
        Vertex *children = vertex->left != nullptr ? vertex->left: vertex->right;
        Vertex *parent = vertex->parent;

        if (vertex == parent->left)
        {
            parent->left = children;
            if (children != nullptr) {
                children->parent = parent;
                children->color = BLACK;
            }
            delete(vertex);
        }
        else {
            parent->right = children;
            if (children != nullptr)
            {
                children->parent = parent;
                children->color = BLACK;
            }
            delete(vertex);
        }
    }
    else {
        Vertex *brother = nullptr;
        Vertex *parent = nullptr;
        bool isBreak = false;

        while (!isBreak && vertex != root) {
            parent = vertex->parent;
            if (vertex == parent->left) {
                brother = parent->right;
                if (brother->color == RED) {
                    brother->color = BLACK;
                    parent->color = RED;
                    rotateLeft(parent);
                } else {
                    if ((brother->left == nullptr || brother->left->color == BLACK) &&
                        (brother->right == nullptr || brother->right->color == BLACK)) {
                        brother->color = RED;
                        if (parent->color == RED) {
                            parent->color = BLACK;
                            isBreak = true;
                        }
                        vertex = parent;
                    } else {
                        if (brother->right == nullptr || brother->right->color == BLACK) {
                            brother->left->color = BLACK;
                            brother->color = RED;
                            rotateRight(brother);
                            brother = parent->right;
                        }
                        brother->color = parent->color;
                        parent->color = BLACK;
                        brother->right->color = BLACK;
                        rotateLeft(parent);
                        vertex = this->root;
                    }
                }
            } else {
                brother = parent->left;
                if (brother->color == RED) {
                    brother->color = BLACK;
                    parent->color = RED;
                    rotateRight(parent);
                } else {
                    if ((brother->left == nullptr || brother->left->color == BLACK) &&
                        (brother->right == nullptr || brother->right->color == BLACK)) {
                        brother->color = RED;
                        if (parent->color == RED) {
                            parent->color = BLACK;
                            isBreak = true;
                        }
                        vertex = vertex->parent;
                    } else {
                        if (brother->left == nullptr || brother->left->color == BLACK) {
                            brother->right->color = BLACK;
                            brother->color = RED;
                            rotateLeft(brother);
                            brother = parent->left;
                        }
                        brother->color = parent->color;
                        parent->color = BLACK;
                        brother->left->color = BLACK;
                        rotateRight(parent);
                        vertex = this->root;
                    }
                }
            }
        }
        if (vertex == parent->left)
            parent->left = nullptr;
        else
            parent->right = nullptr;

        root->color = BLACK;
    }
}

Vertex* RedBlackTree::deleteVertex(Vertex *current, int data) {
    if (root == nullptr)
        return root;

    if (data < current->dataField)
        return deleteVertex(current->left, data);
    else if (data > current->dataField)
        return deleteVertex(current->right, data);
    else if (current->left == nullptr || current->right == nullptr)
        return current;

    Vertex *temp = minValue(current->right);
    current->dataField = temp->dataField;
    return deleteVertex(current->right, temp->dataField);
}

void RedBlackTree::remove(int data) {
    if (find(this->root, data) != nullptr) {
        this->count--;
        Vertex *node = deleteVertex(this->root, data);
        fixRemoveViolations(node);
    }
}

void RedBlackTree::inorderTraversal(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    inorderTraversal(vertex->left);
    cout << vertex->dataField << " ";
    inorderTraversal(vertex->right);
}

void RedBlackTree::preorderTraversal(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    cout << vertex->dataField << " ";
    preorderTraversal(vertex->left);
    preorderTraversal(vertex->right);
}

void RedBlackTree::postorderTraversal(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    preorderTraversal(vertex->left);
    preorderTraversal(vertex->right);
    cout << vertex->dataField << " ";

}

void RedBlackTree::levelOrderTraversal(Vertex *vertex)
{
    if (vertex == nullptr)
        return;

    queue<Vertex*> q;
    q.push(root);

    while(!q.empty())
    {
        Vertex *temp = q.front();
        cout << temp->dataField << " ";
        q.pop();

        if (temp->left != nullptr)
            q.push(temp->left);
        if (temp->right != nullptr)
            q.push(temp->right);
    }
}

int RedBlackTree::blackHeight(Vertex *vertex)
{
    int blackVertexCount = 0;
    while (vertex != nullptr)
    {
        if (vertex->color == BLACK)
            blackVertexCount++;
        vertex = vertex->right;
    }

    return blackVertexCount;
}

void RedBlackTree::inorder()
{
    cout << "Inorder traversal:" << endl;
    inorderTraversal(this->root);
}

void RedBlackTree::levelOrder()
{
    cout << "Traversal, that describe levels of tree (walk around traversal):" << endl;
    levelOrderTraversal(this->root);
}

void RedBlackTree::postorder()
{
    cout << "Postorder traversal:" << endl;
    postorderTraversal(this->root);
}

void RedBlackTree::preorder()
{
    cout << "Preorder traversal:" << endl;
    preorderTraversal(this->root);
}

Vertex *RedBlackTree::minValue(Vertex *node) {
    Vertex *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Vertex *RedBlackTree::maxValue(Vertex *node) {
    Vertex *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

Vertex * RedBlackTree::find(Vertex *current, int data)
{
    if (current == nullptr || data == current->dataField)
        return current;

    if (data < current->dataField)
        return find(current->left, data);
    else
        return find(current->right, data);
}

int RedBlackTree::vertexDepth(Vertex *vertex)
{
    int depth = 0;
    if (vertex != nullptr)
    {
        Vertex *pointer = vertex;
        while (pointer != this->root)
        {
            pointer = pointer->parent;
            depth++;
        }
    }

    return depth;
}

Vertex* RedBlackTree::lovestCommonAncestor(int firstKey, int secondKey)
{
    Vertex *firstVertex = find(this->root, firstKey), *secondVertex = find(this->root, secondKey);
    int firstVertexDepth = vertexDepth(firstVertex), secondVertexDepth = vertexDepth(secondVertex);

    while (firstVertexDepth != secondVertexDepth)
    {
        if (firstVertexDepth > secondVertexDepth)
        {
            firstVertex = firstVertex->parent;
            firstVertexDepth--;
        }
        else {
            secondVertex = secondVertex->parent;
            secondVertexDepth--;
        }
    }

    while (firstVertex != secondVertex)
    {
        firstVertex = firstVertex->parent;
        secondVertex = secondVertex->parent;
    }

    return firstVertex;
}