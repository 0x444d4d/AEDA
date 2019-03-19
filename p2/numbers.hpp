#pragma once

#define DEBG

#include <vector>
#include <iostream>
#include <stdexcept>

#include "number_base.hpp"
#include "number_exeptions.hpp"
#include "numbers-helpers.hpp"


//Numbers<N,B,T>
template <size_t N, size_t B, class T = char>
class numbers : public number_base {

  private:
  T* number_;
  bool negative_;
  unsigned short size_;
  
  public:
  numbers( void ): size_(0), negative_(false) { number_ = new T[N]; }
  numbers( const int number );
  numbers( const numbers<N,B,T>& old);
  ~numbers( void );

  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,B,T>& A ) const;
  bool operator>( const numbers<N,B,T>& A ) const;
  bool operator==( const numbers<N,B,T>& A ) const;
  bool operator!=( const numbers<N,B,T>& A ) const;
  number_base* operator+ ( const number_base* A) const;
  number_base* operator- ( const number_base* A ) const;
  numbers<N,B,T> operator+( const numbers<N,B,T>& A) const;
  numbers<N,B,T> operator-( const numbers<N,B,T>& A) const;
  numbers<N,B,T> operator=( const numbers<N,B,T>& A );

  private:

  void to_base( int input, unsigned pos = 0);
  bool less_than( const numbers<N,B,T>& A ) const;
  bool equals( const numbers<N,B,T>& A ) const;
  void copy( const numbers<N,B,T>& old );
  numbers<N,B,T> sum( const numbers<N,B,T>& A ) const;
  numbers<N,B,T> sub( const numbers<N,B,T>& A ) const;
  number_base* duplicate( void ) const;
  
};

//Numbers<N,2,T>
template <size_t N, class T>
class numbers<N,2,T> : public number_base {

  private:
  T* number_;
  unsigned short size_;
  
  public:

  numbers( void );
  explicit numbers( const int number );
  numbers( const numbers<N,2,T>& old);
  ~numbers( void );

  std::ostream& write( std::ostream& os ) const;
  bool operator<( const numbers<N,2,T>& A ) const;
  bool operator>( const numbers<N,2,T>& A ) const;
  bool operator==( const numbers<N,2,T>& A ) const;
  bool operator!=( const numbers<N,2,T>& A ) const;
  number_base* operator+ ( const number_base* A) const;
  number_base* operator- ( const number_base* A ) const;
  numbers<N,2,T> operator+( const numbers<N,2,T>& A) const;
  numbers<N,2,T> operator-( const numbers<N,2,T>& A) const;
  numbers<N,2,T> operator=( const numbers<N,2,T>& A );

  private:

  void complement( void );
  void fill( const int i );
  void to_base( int input, unsigned pos = 0);
  bool less_than( const numbers<N,2,T>& A ) const;
  bool equals( const numbers<N,2,T>& A ) const;
  void copy( const numbers<N,2,T>& old );
  numbers<N, 2, T> sum( const numbers<N,2,T>& A ) const;
  number_base* duplicate( void ) const;
};

//Bin,Oct,Dec,Hex
class binary_number : public numbers<8,2>{
  public:
  binary_number(int n) : numbers<8,2>(n) {}
};

class octal_number : public numbers<8,8>{
  public:
  octal_number(int n) : numbers<8,8> (n) {}
};

class decimal_number : public numbers <8,10>{
  public:
  decimal_number(int n) : numbers<8,10> (n) {}
};

class hexadecimal_number : public numbers <8,16>{
  public:
  hexadecimal_number(int n) : numbers <8,16> (n) {}
};


//Numbers
//constructor
template <size_t N, size_t B, class T>
numbers<N, B, T>::numbers(const int number):size_(0) {
  if ( B < 2 ) {
    throw base_exception(); 
  }
  if ( number < 0 ) negative_ = true;
  else negative_ = false;
  
  number_ = new T[N];
  
  if ( number_ == NULL) throw "Could not create array";
  else {
    if ( number < 0 ) to_base( -number );
    else to_base( number );
  }
}

//constructor de copia
template <size_t N, size_t B, class T>
numbers<N,B,T>::numbers(const numbers<N,B,T>& old) {
  copy(old);
}


//destructor
template <size_t N, size_t B, class T>
numbers<N,B,T>::~numbers(void) noexcept(false) {
  
  if ( number_ != NULL ) {
    delete number_;
    number_ = NULL;
  } else {
    throw double_free();
  }
  
}

//to_base
template <size_t N, size_t B, class T>
void numbers<N, B, T>::to_base(int input, unsigned pos ) {
  if ( (long unsigned)input < B ) {
    number_[pos] = input;
    ++size_;
  }
  else {
    number_[pos]  = input % B;
    ++size_;
    input = input / B;
    to_base( input, ++pos );
  }
}

//sum
template <size_t N, size_t B, class T>
numbers<N, B, T> numbers<N, B, T>::sum( const numbers& A ) const {
  numbers<N, B, T> C; //resultado de la suma.
  size_t result_size = size_ < A.size_ ? A.size_ : size_; //tamaño del resultado.
  unsigned aux; //resultado de la suma de dos digitos.
  uint_fast8_t carry = 0;
  unsigned short inx;


  for ( inx = 0; inx < result_size; ++inx ) {

    if ( inx < A.size_ && inx < size_ )
      aux = A.number_[inx] + number_[inx] + carry;
    else if ( inx < size_ ) 
      aux = number_[inx] + carry;
    else 
      aux = A.number_[inx] + carry;
    
    carry = 0;

    if ( aux < B ) {
      C.number_[inx] = aux;
      ++C.size_;
    } else {
      C.number_[inx] = ( aux - B );
      ++C.size_;
      carry = 1;
    }
  }

  if ( carry ) {

    if ( inx >= N ) {
      throw out_of_range();
    } else {
      C.number_[inx] = 1;
      ++C.size_;
    }
  }
  return C;
}

//sub
template <size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::sub( const numbers& A ) const {
  numbers<N,B,T> X,Y,C;
  size_t result_size = size_ < A.size_ ? A.size_ : size_;
  uint_fast8_t borrow = 0;
  int aux = 0;
  if ( less_than(A) ) {
    C.negative_ = true;

    X = A;
    Y = *this;
  } else {
    C.negative_ = false;

    X = *this;
    Y = A;
  }


  C.size_ = 0;

  for ( int inx = 0; inx < result_size; ++inx ) {

    if ( inx < X.size_ && inx < Y.size_ ) {
      aux =  X.number_[inx] - Y.number_[inx] - borrow;
    } else if ( inx < X.size_ ) {
      aux = X.number_[inx] - borrow;
    } else  {
      aux = Y.number_[inx] - borrow;
    }

    //if ( borrow ) --aux;

    if ( aux < 0 ) {
      aux += B;
      C.number_[inx] = aux;
      ++C.size_;
      borrow = 1;
    } else {
       
      C.number_[inx] = aux;
      ++C.size_;
      borrow = 0;
    }
  }
    
  for (int inx = (C.size_ - 1); inx >= 0; --inx ) {
    if ( C.number_[inx] == 0 ) --C.size_;
    else break;
  }

  return C;
}

template< size_t N, size_t B, class T>
void numbers<N,B,T>::copy( const numbers<N,B,T>& old) {
  size_ = old.size_;
  negative_ = old.negative_;
  number_ = new T[N];

  if ( number_ == NULL) 
    throw std::bad_alloc();
  else {
    for (int inx = 0; inx < size_; ++inx)
      number_[inx] = old.number_[inx];
  }

  //return *this;
}

//write
template <size_t N, size_t B, class T>
std::ostream& numbers<N, B, T>::write( std::ostream& os ) const {
  if ( negative_ ) os << "-";
  if ( size_ == 0 ) {
    os << 0;
  } else {
    for (int inx = (size_ - 1); inx >= 0; --inx ){
      os << int_to_char( number_[inx] );
    }
  }

  fflush(stdout);
  return os;
}

template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::less_than(const numbers& A) const {
  if ( size_ < A.size_ ) return true;
  if ( size_ == A.size_ ) {
    for( int inx = (size_ - 1); inx >= 0; --inx) {
      if ( number_[inx] < A.number_[inx] ) return true;
      if ( number_[inx] > A.number_[inx] ) return false;
    }
  }
  return false;
}

template<size_t N, size_t B, class T> 
bool numbers<N,B,T>::equals(const numbers& A) const {
  if ( size_ == A.size_ ) {
    for ( int inx = 0; inx < size_; ++inx )
      if ( number_[inx] != A.number_[inx] ) return false;
    return true;
  }
  return false;
}



template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator<( const numbers& A ) const {
  return less_than( A );
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator>( const numbers& A ) const {
  if ( !equals(A) ) return !less_than( A );
  return false;
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator==( const numbers& A ) const {
  return equals( A );
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator=( const numbers& A ) {
  copy(A);
  return *this;
}

template< size_t N, size_t B, class T>
bool numbers<N,B,T>::operator!=( const numbers& A ) const {
  return !equals( A );
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator+( const numbers& A ) const {
  numbers<N,B,T> X;

  if (!negative_ && A.negative_ ) {
    X = A;
    return sub(X);
  } else if ( !negative_ && !A.negative_ ) {
    return sum(A);
  } else if ( negative_ && A.negative_ ) {
    X = sum(A);
    X.negative_ = true;
    return X;

  } else if ( negative_ && !A.negative_ ) {
    return A.sub(*this);
  }
}

template< size_t N, size_t B, class T>
numbers<N,B,T> numbers<N,B,T>::operator-( const numbers& A ) const {
  numbers<N,B,T> X;

  if (!negative_ && A.negative_ ) {
    X = A;
    return sum(X);
  } else if ( !negative_ && !A.negative_ ) {
    return sub(A);
  } else if ( negative_ && A.negative_ ) {
    return sub(A);
  } else if ( negative_ && !A.negative_ ) {
    X = A.sum(*this);
    X.negative_ = true;
    return X;
  }
}

template< size_t N, size_t B, class T>
std::ostream& operator<<(std::ostream& os, const numbers<N,B,T>& A) {
  return A.write(os);
}

template < size_t N, size_t B, class T>
number_base* numbers<N,B,T>::duplicate( void ) const {
  return new numbers<N,B,T>(*this);
}

template < size_t N, size_t B, class T>
number_base* numbers<N,B,T>::operator+ (const number_base* A) const {
  const numbers<N,B,T>* l=dynamic_cast<const numbers<N,B,T>*>(A);
  numbers<N,B,T>* r=dynamic_cast<numbers<N,B,T>*>(duplicate());

  *r = *this + *l;
  return r;
}

template < size_t N, size_t B, class T>
number_base* numbers<N,B,T>::operator- (const number_base* A) const {
  const numbers<N,B,T>* l=dynamic_cast<const numbers<N,B,T>*>(A);
  numbers<N,B,T>* r=dynamic_cast<numbers<N,B,T>*>(duplicate());

  *r = *this - *l;
  return r;
}


//Binary numbers
template <size_t N, class T>
numbers<N, 2, T>::numbers(void):size_(0) {
  number_ = new T[N];
  fill(0);
}

//constructor
template <size_t N, class T>
numbers<N, 2, T>::numbers(const int number):size_(0) {

    number_ = new T[N];

    if ( number_ == NULL) 
      throw std::bad_alloc();
    else {
      fill(0);

      if ( number < 0 ) {
        to_base( -number );
        complement();
      }
      else{
        to_base( number );
      }
    }
}

//constructor de copia
template <size_t N, class T>
numbers<N,2,T>::numbers(const numbers<N,2,T>& old) {
  copy(old);
}



//destructor
template <size_t N, class T>
numbers<N,2,T>::~numbers(void) noexcept(false) {
  
  if ( number_ != NULL ) {
    delete number_;
    number_ = NULL;
  } else {
    throw "Double free";
  }
  
}


//fill
template <size_t N, class T>
void numbers<N,2,T>::fill( const int i ) {
  for (int inx = 0; inx < N; ++inx)
    number_[inx] = i;
}


//to_base
template <size_t N, class T>
void numbers<N, 2, T>::to_base(int input, unsigned pos ) {
  if ( input < 2 ) {
    number_[pos] = input;
    ++size_;
  }
  else {
    number_[pos]  = input % 2;
    ++size_;
    input = input / 2;
    to_base( input, ++pos );
  }
}


template <size_t N, class T>
void numbers<N,2,T>::complement( void ) {
  bool neg_flag = false;
  for (unsigned short inx = 0; inx < N; ++inx ) {
    if ( neg_flag ) {
      if ( number_[inx] == 0  ) number_[inx] = 1;
      else number_[inx] = 0;
    } else {
      if ( number_[inx] == 1 ) neg_flag = true;
    }
  } 
}

//sum
template <size_t N, class T>
numbers<N, 2, T> numbers<N, 2, T>::sum( const numbers& A ) const {
  numbers<N, 2, T> C; //resultado de la suma.
  //size_t result_size = size_ < A.size_ ? A.size_ : size_; //tamaño del resultado.
  unsigned aux; //resultado de la suma de dos digitos.
  uint_fast8_t carry = 0;
  unsigned short inx;


  for ( inx = 0; inx < N; ++inx ) {

    aux = A.number_[inx] + number_[inx] + carry;
    
    carry = 0;

    if ( aux < 2 ) {
      C.number_[inx] = aux;
      ++C.size_;
    } else {
      C.number_[inx] = ( aux - 2 );
      ++C.size_;
      carry = 1;
    }
  }

  if ( carry == 1 ) {

  }
  return C;
}

template< size_t N, class T>
void numbers<N,2,T>::copy( const numbers<N,2,T>& old) {
  size_ = old.size_;
  number_ = new T[N];

  if ( number_ == NULL) 
    throw "Could not create array";
  else {
    for (int inx = 0; inx < N; ++inx)
      number_[inx] = old.number_[inx];
  }

  //return *this;
}

//write
template <size_t N, class T>
std::ostream& numbers<N, 2, T>::write( std::ostream& os ) const {
  if ( size_ == 0 ) {
    os << 0;
  } else {
    for (int inx = (N - 1); inx >= 0; --inx ){
      os << int_to_char( number_[inx] );
    }
  }

  fflush(stdout);
  return os;
}


template<size_t N, class T> 
bool numbers<N,2,T>::less_than(const numbers& A) const {
  if ( size_ < A.size_ ) return true;
  if ( size_ == A.size_ ) {
    for( int inx = (size_ - 1); inx >= 0; --inx) {
      if ( number_[inx] < A.number_[inx] ) return true;
      if ( number_[inx] > A.number_[inx] ) return false;
    }
  }
  return false;
}



template<size_t N, class T> 
bool numbers<N,2,T>::equals(const numbers& A) const {
  if ( size_ == A.size_ ) {
    for ( int inx = 0; inx < size_; ++inx )
      if ( number_[inx] != A.number_[inx] ) return false;
    return true;
  }
  return false;
}



template< size_t N, class T>
bool numbers<N,2,T>::operator<( const numbers& A ) const {
  return less_than( A );
}

template< size_t N, class T>
bool numbers<N,2,T>::operator>( const numbers& A ) const {
  if ( !equals(A) ) return !less_than( A );
  return false;
}

template< size_t N, class T>
bool numbers<N,2,T>::operator==( const numbers& A ) const {
  return equals( A );
}

template< size_t N, class T>
numbers<N,2,T> numbers<N,2,T>::operator=( const numbers& A ) {
  copy(A);
  return *this;
}

template< size_t N, class T>
bool numbers<N,2,T>::operator!=( const numbers& A ) const {
  return !equals( A );
}

template< size_t N, class T>
numbers<N,2,T> numbers<N,2,T>::operator+( const numbers& A ) const {
  return sum( A );
}

template< size_t N, class T>
numbers<N,2,T> numbers<N,2,T>::operator-( const numbers& A ) const {
  numbers<N,2,T> X(A);
  
  if ( A.number_[N - 1] == 1 ) {
    X.complement();
    return sum(X); 
  } else return sum( A );
}

template< size_t N, class T>
std::ostream& operator<<(std::ostream& os, const numbers<N,2,T>& A) {
  return A.write(os);
}

template < size_t N, class T>
number_base* numbers<N,2,T>::duplicate( void ) const {
  return new numbers<N,2,T>(*this);
}

template < size_t N, class T>
number_base* numbers<N,2,T>::operator+ (const number_base* A) const {
  const numbers<N,2,T>* l=dynamic_cast<const numbers<N,2,T>*>(A);
  std::cout << "operator+: l: " << *l << std::endl;
  numbers<N,2,T>* r=dynamic_cast<numbers<N,2,T>*>(duplicate());
  std::cout << "operator+: this: " << *this << std::endl;
  

  std::cout << *this + *l <<std:: endl;
  *r = (*this + *l);
  std::cout << "operator+: r: " << *r << std::endl;
  return r;
}

template < size_t N, class T>
number_base* numbers<N,2,T>::operator- (const number_base* A) const {
  const numbers<N,2,T>* l=dynamic_cast<const numbers<N,2,T>*>(A);
  numbers<N,2,T>* r=dynamic_cast<numbers<N,2,T>*>(duplicate());

  *r = (*this - *l);
  return r;
}

