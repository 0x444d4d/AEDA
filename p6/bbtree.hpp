#include "node.hpp"

namespace aeda {

template <class T>
class bbtree {
    private:
    node<T>* root_;

    public:
    bbtree(void): root_(nullptr) {}
    bool insert( T data );
    bool insert( node<T>* &node, T data );

    bool remove( T data );
    bool remove( node<T>* &node, T data );

    bool replace( node<T>* &node );
};


template <class T>
bool bbtree<T>::insert(T data) {
    return insert( root_, data );
}


template <class T>
bool bbtree<T>::insert( node<T>* &node, T data ) {
    if ( node == nullptr ) {
        node = new node<T>(data);
        return true;
    }
    if ( *node.data_ < data  ) insert( *node.left_, data);
    if ( *node.data_ > data  ) insert( *node.right_, data);
    return 0;
    
}


template <class T>
bool bbtree<T>::remove( T data ) {
    return remove( root_, data );
}


template <class T>
bool bbtree<T>::remove( node<T>* &node, T data ) {
    if (node == nullptr) return false;

    if ( *node.data_ < data ) {
        if ( *node.right == data ) return replace( *node.right );
        return remove( *node.right, data );
    } 
    if (*node.data_ > data) {
        if ( *node.left == data ) return replace( *node.left );
        return remove( *node.left, data );
    }
}


template <class T>
bool bbtree<T>::replace( node<T>* &node ) {
    node<T>* aux;
    if ( *node.left == nullptr && *node.right == nullptr ) {
        node = nullptr;
        return true;
    }

    aux = node;
    if ( *node.left != nullptr ) node = *node.left;
    if ( *node.right != nullptr ) node = *node.right;
    delete aux;
    return true;
}



}//namespace
