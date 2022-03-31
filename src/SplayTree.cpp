#include <vector>
#include <iostream>

struct Node
{
    Node * left = nullptr;
    Node * right = nullptr;
    Node * parent = nullptr;
    int value = 0;
    Node(int v, Node * l, Node * r)
    {
        value = v;
        left = l;
        right = r;
    }
    ~Node() {}
};

class SplayTree
{
private:
    Node * p(Node * v) const
    {
        return v->parent;
    }

    Node * g(Node * v) const
    {
        return p(p(v));
    }

    void set_parent(Node * child, Node * parent)
    {
        if (child != nullptr) {
            child->parent = parent;
        }
    }

    void keep_parent(Node * v)
    {
        set_parent(v->left, v);
        set_parent(v->right, v);
    }

    void rotate_left(Node * v) const;
    void rotate_right(Node * v) const;
    Node * splay(Node * v) const;
    Node * find(Node * v, int key) const;
    Node * split(int key);
    void inorderTraversal(Node * x, std::vector<int> * vec) const;
    void deleteTree(Node * x);
    mutable Node * root = nullptr;

public:
    SplayTree()
    {
        root = nullptr;
        length = 0;
    }
    std::size_t length = 0;
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);
    std::size_t size() const;
    bool empty() const;
    std::vector<int> values() const;
    ~SplayTree();
};


void SplayTree::rotate_left(Node * v) const
{
    Node * p = v->parent;
    Node * r = v->right;
    if (p != nullptr) {
        if (p->left == v) {
            p->left = r;
        }
        else {
            p->right = r;
        }
    }
    Node * tmp = r->left;
    r->left = v;
    v->right = tmp;
    v->parent = r;
    r->parent = p;
    if (v->right != nullptr) {
        (v->right)->parent = v;
    }
}

void SplayTree::rotate_right(Node * v) const
{
    Node * p = v->parent;
    Node * r = v->left;
    if (p != nullptr) {
        if (p->right == v) {
            p->right = r;
        }
        else {
            p->left = r;
        }
    }
    Node * tmp = r->right;
    r->right = v;
    v->left = tmp;
    v->parent = r;
    r->parent = p;
    if (v->left != nullptr) {
        (v->left)->parent = v;
    }
}

std::vector<int> SplayTree::values() const
{
    std::vector<int> * linkVec = new std::vector<int>;
    inorderTraversal(this->root, linkVec);
    return *linkVec;
}

void SplayTree::inorderTraversal(Node * x, std::vector<int> * vec) const
{
    if (x != nullptr) {
        inorderTraversal(x->left, vec);
        vec->push_back(x->value);
        inorderTraversal(x->right, vec);
    }
}

std::size_t SplayTree::size() const
{
    return length;
}

bool SplayTree::empty() const
{
    return length != 0;
}

Node * SplayTree::find(Node * v, int key) const
{
    if (v == nullptr) {
        return nullptr;
    }
    if (key == v->value) {
        return this->splay(v);
    }
    if (key < v->value && v->left != nullptr) {
        return find(v->left, key);
    }
    if (key > v->value && v->right != nullptr) {
        return find(v->right, key);
    }
    return splay(v);
}

bool SplayTree::contains(int value) const
{
    Node * tmp = find(this->root, value);
    return tmp != nullptr && tmp->value == value;
}

Node * SplayTree::split(int key)
{
    if (root == nullptr) {
        return nullptr;
    }
    Node * r = find(this->root, key);
    if (r->value == key) {
        return r;
    }
    else if (r->value < key) {
        Node * rightTree = r->right;
        set_parent(rightTree, nullptr);
        r->right = nullptr;
        return rightTree;
    }
    else {
        Node * leftTree = r->left;
        set_parent(leftTree, nullptr);
        r->left = nullptr;
        return leftTree;
    }
}

bool SplayTree::insert(int key)
{
    Node * newTree = split(key);
    if (root == nullptr) {
        root = new Node(key, nullptr, nullptr);
        length++;
        return true;
    }
    else if ((root->right == nullptr && key > root->value) || (newTree != nullptr && newTree->value > this->root->value)) {
        root = new Node(key, this->root, newTree);
        keep_parent(root);
        length++;
        return true;
    }
    else if ((root->left == nullptr && key < root->value) || (newTree != nullptr && newTree->value < this->root->value)) {
        root = new Node(key, newTree, this->root);
        keep_parent(root);
        length++;
        return true;
    }
    else {
        return false;
    }
}

bool SplayTree::remove(int val)
{
    if (root == nullptr) {
        return false;
    }
    Node * r = find(this->root, val);
    if (r->value != val) {
        return false;
    }
    Node * leftR = r->left;
    Node * rightR = r->right;
    delete r;
    root = nullptr;
    if (rightR == nullptr && leftR == nullptr){
        length--;
        return true;
    }
    else if (rightR == nullptr) {
        this->root = leftR;
        set_parent(leftR, nullptr);
        length--;
        return true;
    }
    else if (leftR == nullptr) {
        this->root = rightR;
        set_parent(rightR, nullptr);
        length--;
        return true;
    }
    leftR->parent = nullptr;
    rightR->parent = nullptr;
    rightR = find(rightR, leftR->value);
    rightR->left = leftR;
    leftR->parent = rightR;
    length--;
    return true;
}

Node * SplayTree::splay(Node * v) const
{
    while (p(v) != nullptr) {
        if (v == p(v)->left) {
            if (g(v) == nullptr) {
                rotate_right(p(v));
            }
            else if (p(v) == g(v)->left) {
                rotate_right(g(v));
                rotate_right(p(v));
            }
            else {
                rotate_right(p(v));
                rotate_left(p(v));
            }
        }
        else {
            if (g(v) == nullptr) {
                rotate_left(p(v));
            }
            else if (p(v) == g(v)->right) {
                rotate_left(g(v));
                rotate_left(p(v));
            }
            else {
                rotate_left(p(v));
                rotate_right(p(v));
            }
        }
    }
    root = v;
    return v;
}

SplayTree::~SplayTree()
{
    if (root != nullptr) {
        deleteTree(root);
    }
}

void SplayTree::deleteTree(Node * x)
{
    if (x->left != nullptr) {
        deleteTree(x->left);
    }
    if (x->right != nullptr) {
        deleteTree(x->right);
    }
    delete x;
    return;
}
