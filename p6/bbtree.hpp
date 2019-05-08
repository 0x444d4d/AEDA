#include "node.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include "contador.hpp"
//#include "dni.hpp"

namespace aeda {

template <class T>
class bbtree {
    private:
    node<T>* root_;
    aeda::Contador<> counter_;

    public:
    bbtree(void): root_(nullptr) {}
    bool insert( T data );
    bool insert( node<T>* &node, T data );

    bool search( T data );
    bool search( node<T>* &node,  T data );

    bool remove( T data );
    bool remove( node<T>* &node, T data );

    bool replace( node<T>* &node );

    void printTree(void);
    void make_queue( std::vector<node<T>*> nodeVect, std::queue<T> &printQueue, std::vector<unsigned> &sizes);
};


template <class T>
bool bbtree<T>::insert(T data) {
    return insert( root_, data );
}


template <class T>
bool bbtree<T>::insert( node<T>* &node, T data ) {
    if ( node == nullptr ) {
        node = new aeda::node<T>(data);
        return true;
    }
    if ( data > *node ) insert( node->right_, data);
    //counter_++;
    if ( data < *node ) insert( node->left_, data);
    //counter_++;
    return 0;
    
}

template <class T>
bool bbtree<T>::search( T data ) {
    return search( root_, data );
}

template <class T>
bool bbtree<T>::search( node<T>* &node, T data ) {
    //counter_++;
    if ( data < *node ) {
        if ( node->left_ == nullptr ) return false;
        return  search( node->left_, data );
    }
    //counter_++;
    if ( data > *node ) {
        if ( node->right_ == nullptr ) return false;
        return  search( node->right_, data );
    }
    return false;
}


template <class T>
bool bbtree<T>::remove( T data ) {
    return remove( root_, data );
}


template <class T>
bool bbtree<T>::remove( node<T>* &node, T data ) {
    if (node == nullptr) return false;

    if ( *node < data ) {
        if ( *(node->right_ ) == data ) return replace( node->right_ );
        //counter_++;
        return remove( node->right_, data );
    } 
    if (*node > data) {
        if ( *(node->left_) == data ) return replace( node->left_ );
        //counter_++;
        return remove( node->left_, data );
    }
    return false;
}


template <class T>
bool bbtree<T>::replace( node<T>* &node ) {
    aeda::node<T>* aux;
    aeda::node<T>* tmp;
    aeda::node<T>* last;

    if ( node->left_ == nullptr && node->right_ == nullptr ) {
        delete node;
        node = nullptr;
        return true;
    }

    aux = node;
    if ( node->left_ != nullptr && node->right_ != nullptr ) {
//Code here
        node = node->left_; 
        aeda::node<T>* last = node;
        tmp = node;
        
        while ( tmp != nullptr ) {
            last = tmp;
            if ( *aux->right_ < *last ) tmp = tmp->left_;
            //counter_++;
            if ( *aux->right_ > *last ) tmp = tmp->right_;
            //counter_++;
        }

        if ( *aux->right_  < *last ) {
            last->left_ = aux->right_;
            //counter_++;
        }
        else if ( *aux->right_  > *last) {
            last->right_ = aux->right_;
            //counter_++;
        }
        else return false;

    } else {
        if ( node->left_ == nullptr ) node = node->right_;
        else if ( node->right_ == nullptr ) node = node->left_;
    }

    delete aux;
    aux = nullptr;

    return true;
}


template <class T>
void bbtree<T>::printTree(void) {
    std::queue<T> printQueue;
    std::vector<node<T>*> nodeVect;
    nodeVect.push_back(root_);
    std::vector<unsigned> sizes;
    unsigned vpos = 0;
    //printQueue.push(*root_);

    make_queue(nodeVect, printQueue, sizes);

    while (printQueue.size() > 0) {
        std::cout << vpos << ": ";
        for ( unsigned inx = 0; inx < sizes[vpos]; ++inx ) {
            std::cout << "[" <<printQueue.front() << "] ";
            printQueue.pop();
        }
        ++vpos;
        std::cout << std::endl;
    }
/*
    visited.push_back( root_->left_);
    visited.push_back( root_->right_);

    printQueue.push(root_->left_);
    printQueue.push(root_->right_);
*/
}

template <class T>
void bbtree<T>::make_queue( std::vector<node<T>*> nodeVect, std::queue<T> &printQueue, std::vector<unsigned> &sizes ) {
    std::vector<node<T>*> newVect;

    if (nodeVect.size() == 0 ) return;

    sizes.push_back( nodeVect.size() );
    for ( auto node: nodeVect ) {
        if (node != nullptr) {

            printQueue.push(*node);
            newVect.push_back(node->left_);
            newVect.push_back(node->right_);
        } else --sizes[sizes.size() - 1];
    }
    
    make_queue( newVect, printQueue, sizes );    
}


}//namespace
