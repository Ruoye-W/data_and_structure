//
// Created by 王银峰 on 2021/4/10.
//

#ifndef DATA_AND_STRUCTURE_BINARYSEARCHTREE_H
#define DATA_AND_STRUCTURE_BINARYSEARCHTREE_H

#include <iostream>

template<typename T>
class BinarySearchTree {
private:
    struct BinaryNode{
        T val;
        BinaryNode* left;
        BinaryNode* right;
        BinaryNode(const T& _val, BinaryNode* lt, BinaryNode* rt)
                :val(_val), left(lt), right(rt) {}
    };

    BinaryNode* root;

public:
    BinarySearchTree() = default;

    BinarySearchTree(const BinarySearchTree& rhs) {
        root = clone(rhs.root);
    }

    ~BinarySearchTree() { makeEmpty(); }

    void makeEmpty() {
        makeEmpty(root);
    }

    const BinaryNode* findMin(BinaryNode* head) const {
        if(head == nullptr)
            return nullptr;

        if(head->left == nullptr)
            return head;

        return findMin(head->left);
    }

    const BinaryNode* findMax(BinaryNode* head) const{
        if(head == nullptr)
            return nullptr;

        if(head->right == nullptr)
            return head;

        return findMax(head->left);
    }

    bool contains(const T& data) const {
        return contains(root, data);
    }

    bool isEmpty() const { return root == nullptr; }

    void preOrder(BinaryNode* head) const {
        if(head == nullptr)
            return;
        std::cout << head->val << std::endl;
        preOrder(head->left);
        preOrder(head->right);
    }

    void inOrder(BinaryNode* head) const {
        if(head == nullptr)
            return;

        preOrder(head->left);
        std::cout << head->val << std::endl;
        preOrder(head->right);
    }

    void postOrder(BinaryNode* head) const{
        if(head == nullptr)
            return;

        preOrder(head->left);
        preOrder(head->right);
        std::cout << head->val << std::endl;
    }

    void printTree() const {
        return printTree(root);
    }

    void printTree(BinaryNode* head) const {
        preOrder(root);
    }

    void insert(const T& data) {
        return insert(data, root);
    }

    void remove(const T& data) {
        return remove(data, root);
    }

    BinarySearchTree& operator= (const BinarySearchTree& rhs) {
        if(this != &rhs){
            makeEmpty(root);
            root = clone(rhs.root);
        }
        return *this;
    }

    BinaryNode clone(BinaryNode* head) const {
        if(head == nullptr)
            return nullptr;

        return new BinaryNode(head->val, clone(head->left), clone(head->right));
    }

private:
    void makeEmpty(const BinaryNode* &head) {
        if(head != nullptr) {
            makeEmpty(head->left);
            makeEmpty(head->right);
            delete head;
        }
        head = nullptr;
    }

    bool contains(BinaryNode* head, const T& data) const {
        if(head == nullptr)
            return false;

        if(head->val < data)
            return contains(head->right, data);
        else if(head->val > data)
            return contains(head->left, data);
        else
            return true;
    }

    void remove(const T& data, BinaryNode* & head) {
        if(head == nullptr)
            return;

        if(head->val < data)
            return remove(data, head->right);
        else if(head->val > data)
            return remove(data, head->left);
        else {
            if(head->left != nullptr && head->right != nullptr){
                head->val = findMin(head->right)->val;
                remove(head->val, head->right);
            } else {
                BinaryNode* t = head;
                head = head->left==nullptr? head->right : head->left;
                delete t;
            }
        }
    }

    void insert(const T& data, BinaryNode* & head) {

        if(head == nullptr)
            head = new BinaryNode(data, nullptr, nullptr);

        if(head->val < data)
            insert(data, head->right);
        else if(head->val > data)
            insert(data, head->left);
        else
            return;
    }
};

#endif //DATA_AND_STRUCTURE_BINARYSEARCHTREE_H
