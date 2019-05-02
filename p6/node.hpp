
namespace aeda {

template <class T>
class node {

    public:
    T data_;
    node<T>* left_;
    node<T>* right_;

    node(T data): data_(data) {}
    operator T() { return data_; }
    //node<T> operator =(node<T> node) { node =  }
};



}//namespace
