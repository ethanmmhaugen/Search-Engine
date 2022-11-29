//
// Created by ethan on 11/2/2022.
//

#ifndef FINALPROJEXAMPLES_AVL_TREE_H
#define FINALPROJEXAMPLES_AVL_TREE_H

#define DEBUG

#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <queue>

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x (with rebalancing)
// void remove( x )       --> Remove x (with rebalancing)
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************

template <typename Comparable>
class AvlTree
{
private:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ele}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

public:
    /**
     * @brief Construct a new Avl Tree object
     */
    AvlNode* getRoot(){
        return root;
    }
    AvlTree() : root{nullptr}
    {
    }

    /**
     * @brief Copy constructor
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Copy assignment operator
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    Comparable& find(const Comparable &x) const
    {
        if(contains(x)) {
            return find(x, root);
        }
        else{
            throw std::runtime_error ("Not Found, in main find");
        }
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    void balancedInsert(const Comparable &x)
    {
        balancedInsert(x, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    AvlNode* remove(const Comparable &x)
    {
        AvlNode* t =remove(root, x);
        return t;
    }

    void saveToFile(string& name){
        ofstream file;
        file.open(name);

            if(root == nullptr){
                return;
            }
            queue<AvlNode*> level;
            level.push(root);
            while(!level.empty()){
                AvlNode* node = level.front();
                level.pop();
                file << node->element.toString() << endl;
                if(node->left != nullptr){
                    level.push(node->left);
                }
                if(node->right != nullptr){
                    level.push(node->right);
                }
            }

        file.close();
    }
/*
    void saveToFile(string& name){
        fstream file;
        file.open(name);
        if(file.good()){
            saveToFile(file, root);
        }
        file.close();
    }
*/
private:
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

 /*   void saveToFile(fstream& file, AvlNode* t){
        if(t == NULL){
            return;
        }
        //string name = t->element.toString();
        file << t->element.toString() << endl;
        saveToFile(file, t->left);
        saveToFile(file, t->right);
    }
    */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr, 0};
            return; // a single node is always balanced
        }

        if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
        {
        } // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance once where
        // the tree got imbalanced.
        balance(t);
    }

    void balancedInsert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr, 0};
            return; // a single node is always balanced
        }

        if (x < t->element)
            balancedInsert(x, t->left);
        else if (t->element < x)
            balancedInsert(x, t->right);
        else
        {
        } // Duplicate; do nothing
    }

    int balanceFactor(AvlNode* t){
        int leftHeight, rightHeight;
        if(t == NULL){
            return 0;
        }
        if(t->left == NULL){
            leftHeight = 0;
        }
        else{
            leftHeight = 1+t->left->height;
        }
        if(t->right == NULL){
            rightHeight = 0;
        }
        else{
            rightHeight = 1+t->right->height;
        }
        return (leftHeight-rightHeight);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    AvlNode* remove(AvlNode *&t, const Comparable &x)
    {
        cout << "we in this bitch" << endl;
        if(contains(x)) {
            AvlNode *p;
            if (x > t->element) {
                t->right = remove(t->right, x);
                if(balanceFactor(t) == 2){
                    if(balanceFactor(t ->left) >=0){
                        t = LL(t);
                    }
                    else{
                        t = LR(t);
                    }
                }
            } else if (x < t->element) {
                t->left = remove(t->left, x);
                if(balanceFactor(t)==-2){
                    if(balanceFactor(t->right)<=0){
                        t =RR(t);
                    }
                    else{
                        t =RL(t);
                    }
                }

            } else{
                if(t->right != NULL){
                    p = t->right;
                    while(p->left != NULL){
                        p = p->left;
                    }
                    t->element = p->element;
                    t->right = remove(t->right, p->element);

                    if(balanceFactor(t) == 2){
                        if(balanceFactor(t->left) >= 0){
                            t = LL(t);
                        }
                        else{
                            t = LR(t);
                        }
                    }
                }
                else{
                    return(t->left);
                }

            }
            t ->height = height(t);
            // don't forget to balance
            return(t);
        }
        else{
            return NULL;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;

        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }

    Comparable& find(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            throw std::runtime_error ("Not Found");

        else if (x < t->element)
            return find(x, t->left);
        else if (t->element < x)
            return find(x, t->right);
        else
            return (t->element); // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const Comparable & x, AvlNode *t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match
            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    // Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

        std::cout << prefix;
        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
        std::cout << node->element << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }

    // Avl manipulations

    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
    // but the search less efficient.

    // Assume t is balanced or within one of being balanced since we check this after each manipulation
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;

    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
    AvlNode * RR(AvlNode *T)
    {

        T = rotateleft(T);
        return(T);
    }
    AvlNode* LL(AvlNode  *T)
    {
        T = rotateright(T);
        return(T);
    }

    AvlNode * LR(AvlNode *T)
    {

        T -> left = rotateleft(T->left);
        T = rotateright(T);
        return(T);
    }

    AvlNode * RL(AvlNode *T)
    {
        T -> right = rotateright(T->right);
        T = rotateleft(T);
        return(T);
    }
    AvlNode * rotateright(AvlNode *x)
    {

        AvlNode *y;
        y = x -> left;
        x -> left = y -> right;
        y -> right = x;
        x -> height = height(x);
        y -> height = height(y);
        return(y);
    }

    AvlNode * rotateleft(AvlNode *x)
    {
        AvlNode *y;
        y = x -> right;
        x -> right = y -> left;
        y -> left = x;
        x -> height = height(x);
        y -> height = height(y);
        return(y);
    }
};

#endif //FINALPROJEXAMPLES_AVL_TREE_H
