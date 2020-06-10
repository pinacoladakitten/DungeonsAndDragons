/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: wiiga
 *
 * Created on June 3, 2020, 9:47 PM
 */

#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

template <class T>
class BSTree {
public:
    struct Node {
        T data;
        struct Node *left, *right;
        Node(T data) {
            this->data=data;
            left = right = nullptr;
        }
    };
    Node* root=nullptr;
    
    BSTree();
    virtual ~BSTree();
    void AddNode(T);
    T PostOrder(Node*);
    T InOrder(Node*);
    T Find(Node*, T);
    void print(char);
    void delNodes(Node* node);
private:
    void lookToAdd(Node*, T);
};

template <class T>
BSTree<T>::BSTree() {
    
}

template <class T>
BSTree<T>::~BSTree() {
    std::cout << std::endl << std::endl;
    delNodes(root);
}

template <class T>
T BSTree<T>::PostOrder(Node* node) {
    if(node==nullptr)return;
    
    PostOrder(node->left);
    PostOrder(node->right);
    
    return node->data;
}

template <class T>
T BSTree<T>::Find(Node* node, T value) {
    static int count = 0;
    if(node==nullptr)return;
    
    if(node->data==value){
        return node->data;
        count = 0;
    }
    count++;
    Find(node->left, value);
    Find(node->right, value);
}

template <class T>
T BSTree<T>::InOrder(Node* node) {
    if(node==nullptr)return NULL;
    
    InOrder(node->left);
    return node->data;
    InOrder(node->right);
}

template <class T>
void BSTree<T>::delNodes(Node* node) {
    if(node==nullptr)return;
    
    delNodes(node->left);
    delNodes(node->right);
    //std::cout << "deleted " << node->data << std::endl;
    delete node;
}

template <class T>
void BSTree<T>::AddNode(T value) {
    if(root==nullptr){
        root = new Node(value);
    }
    else{
        lookToAdd(root, value);
    }
}

template <class T>
void BSTree<T>::print(char type){
    switch(type){
        case 'p':PostOrder(root);break;
        case 'i':InOrder(root);break;
        default : InOrder(root);break;
    }
}

template <class T>
void BSTree<T>::lookToAdd(Node* node, T value) {
    
    if(node->data < value && node->right!=nullptr) {
        lookToAdd(node->right, value);
    }
    else if(node->data > value && node->left!=nullptr) {
        lookToAdd(node->left, value);
    }
    else if(node->data < value && node->right==nullptr) {
        node->right = new Node(value);
    }
    else if(node->data > value && node->left==nullptr) {
        node->left = new Node(value);
    }
}

#endif /* BSTREE_H */

