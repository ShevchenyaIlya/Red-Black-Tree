//
// Created by shevchenya on 16/04/2020.
//

#ifndef TREE_REDBLACKTREE_H
#define TREE_REDBLACKTREE_H

enum VertexColor {RED, BLACK};

class Vertex
{
public:
    int dataField;
    VertexColor color;
    Vertex *left, *right, *parent;

    explicit Vertex(int data);
};

class RedBlackTree
{
    Vertex *root;
    int count;

    void rotateLeft(Vertex *vertex);
    void rotateRight(Vertex *vertex);
    void fixInsertViolations(Vertex *vertex);
    void fixRemoveViolations(Vertex *vertex);
    Vertex* deleteVertex(Vertex *vertex, int key);
    int vertexDepth(Vertex *vertex);
    static Vertex *next(Vertex *vertex);
    static Vertex *prev(Vertex *vertex);

    void inorderTraversal(Vertex *vertex);
    void preorderTraversal(Vertex *vertex);
    void postorderTraversal(Vertex *vertex);
    void levelOrderTraversal(Vertex *vertex);
public:
    RedBlackTree();
    Vertex *getRoot();
    void insert(int key);
    Vertex *find(Vertex *currentVertex, int value);
    static Vertex *minValue(Vertex *vertex);
    static Vertex *maxValue(Vertex *vertex);
    Vertex *lovestCommonAncestor(int firstKey, int secondKey);
    void remove(int key);
    int vertexCount();
    int blackHeight(Vertex *vertex);

    class Iterator;
    Iterator begin();
    Iterator end();

    void inorder();
    void preorder();
    void postorder();
    void levelOrder();
    class Iterator {
    public:
        Vertex* currentVertex;
        Iterator(Vertex* first) : currentVertex(first) {}

        Vertex& operator ++ ();
        Vertex& operator -- ();
        Vertex& operator ++ (int);
        Vertex& operator -- (int);
        bool operator != (const Iterator &it);
    };
};

#endif //TREE_REDBLACKTREE_H
