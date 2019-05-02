
namespace aeda {

template <class T>
class node {

    public:
    T data_;
    node<T>* left;
    node<T>* right;

    node(T data): data_(data) {}
};



}//namespace
