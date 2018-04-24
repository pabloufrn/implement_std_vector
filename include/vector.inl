#include "vector.h"

using namespace sc;

// MYITERATOR CLASS METHOD


template < typename T >
MyIterator<T>::MyIterator(MyIterator<T>::pointer pt){
    this->current = pt;
}

template < typename T >
MyIterator<T>::MyIterator( const MyIterator<T> &) = default;

template < typename T >
MyIterator<T>::~MyIterator() = default;

// O operator-> retorna a referencia do ponteiro atual?

template < typename T >
MyIterator<T> * MyIterator<T>::operator->( void ) const{
    return &this->current;
}

template < typename T >
MyIterator<T> & MyIterator<T>::operator=( const MyIterator<T> & rhs ){
    this->current = rhs.current;
    return *this;
}

template < typename T >
typename MyIterator<T>::reference MyIterator<T>::operator*( void ) const{
    return *this->current;
}

template < typename T >
sc::MyIterator<T> & MyIterator<T>::operator++( void ){
    ++this->current;
    return *this;
}

template < typename T >
sc::MyIterator<T> MyIterator<T>::operator++( int ){
         auto temp(*this);
         ++this->current;
         return temp;
}

template < typename T >
sc::MyIterator<T> & MyIterator<T>::operator--( void ){
    --this->current;
    return *this;
}

template < typename T >
sc::MyIterator<T> MyIterator<T>::operator--( int ){
    auto temp(*this);
    --this->current;
    return temp;
}

template < typename T >
bool sc::MyIterator<T>::operator==( const MyIterator<T> & rhs ) const {
    return this->current == rhs.current;
}

template < typename T >
bool sc::MyIterator<T>::operator!=( const MyIterator<T> & rhs ) const {
    return this->current != rhs.current;
}

template < typename T >
MyIterator<T> MyIterator<T>::operator-( const MyIterator & rhs ) const{
    return this->current - rhs.current;
}

// [I] SPECIAL MEMBERS
template<class T>
sc::vector<T>::vector( ) {
    this->m_end = DEFAULT_SIZE;
    this->m_capacity = DEFAULT_SIZE+1;
    this->m_storage = new T[DEFAULT_SIZE+1];
}

template < typename T >
sc::vector<T>::~vector( ) {
    delete [] m_storage;
}

/*
 * template < typename T >
 * vector<T>::vector(const vector& vtr)
 * {
 *    size_type capacity = vtr.capacity();
 *	
 *    this->m_capacity = capacity;	
 *    this->m_storage = new T[capacity];
 *    this->m_end = vtr.size();
 *    
 *	std::copy(vtr.begin(), vtr.end(), this->m_storage);
 *    
 * }
 */
//vector(vector&&);
//template < typename InputItr >
//vector( InputItr, InputItr );
/*
 * template < typename T >
 * vector<T> & vector<T>::operator=( const vector<T> & vtr ) {
 * 
 *	size_type capacity = vtr.capacity();
 *	this->m_storage = new T[capacity];
 *	this->m_end = vtr.size();
 *	this->m_capacity = capacity;
 * 
 *    auto vtr_storage = vtr.begin();
 *    
 *	for( auto i(0u); i < capacity; i++ ){
 *        this->m_storage[i] = vtr_storage[i];
 *	}
 *	return *this;
 * }
 */
// vector & operator=( vector && );

// [II] ITERATORS

template < typename T >
typename vector<T>::iterator vector<T>::begin(void) {
    return vector<T>::iterator(this->m_storage);
}

template < typename T >
typename vector<T>::iterator vector<T>::end(void) {
    return vector<T>::iterator(this->m_storage + this->m_end );
}

template < typename T >
typename vector<T>::const_iterator vector<T>::cbegin(void) const {
    return vector<T>::const_iterator ( this->m_storage );
}

template < typename T >
typename vector<T>::const_iterator vector<T>::cend(void) const {
    return vector<T>::const_iterator( this->m_storage  + this->m_end);
}


// [III] Capacity

template < typename T >
typename vector<T>::size_type vector<T>::size( void ) const {
    return this->m_end;
}

template < typename T >
typename vector<T>::size_type vector<T>::capacity( void ) const {
    return this->m_capacity;
}

template < typename T >
bool vector<T>::empty( void ) const {
    return this->m_end == 0;
}

// [IV] Modifiers

template < typename T >
void vector<T>::clear( void ){
    delete [] this->m_storage;
    this->m_storage = new T[DEFAULT_SIZE + 1];
    this->m_capacity = DEFAULT_SIZE + 1;
    this->m_end = DEFAULT_SIZE;
}
/*
 * template < typename T >
 * void vector<T>::push_front( const_reference value ){
 *    for( auto i(this->m_end) ; i > 0 ; i-- ){
 *        swap(*(this->m_storage+i-1), *(this->m_storage+i));
 *    }
 *(this->m_storage) = value;
 * 
 * }
 */
template < typename T >
void vector<T>::push_back( vector<T>::const_reference value ){
    if(m_end == this->m_capacity)
        this->reserve(this->m_capacity * 2);
    this->m_storage[this->m_end++] = value;
}

// void pop_back( void );
//void pop_front( void );
//iterator insert( iterator , const_reference );
//template < typename InputItr >
//iterator insert( iterator , InputItr , InputItr );
//iterator insert( iterator, std::initializer_list< value_type > );


template < typename T >
void vector<T>::reserve(vector<T>::size_type size)
{
    if(size <= this->m_capacity)
        return;
    T* new_storage = new T[size];
    this->m_capacity = size;
    auto end(this->m_end);
    for(auto i(0u); i < end; ++i) {
        new_storage[i] = this->m_storage[i]; 
    }
    delete [] this->m_storage;
    this->m_storage = new_storage;
}
//void shrink_to_fit( void );

template < typename T >
void vector<T>::assign( vector<T>::const_reference value )
{
    auto first = m_storage;
    auto last = m_storage + m_end;
    
    while(first < last)
        *(first++) = value;
}

//void assign( std::initializer_list<T> );
//template < typename InputItr >
//void assign( InputItr, InputItr );

template < typename T >
typename vector<T>::iterator vector<T>::erase( vector<T>::iterator first, vector<T>::iterator last){
    auto aux = last;
    auto p_m_end = this->m_storage + this->m_end;
    while(aux < p_m_end)
    {
        *(first++) = *(aux++);
    }
    
}

//iterator erase( iterator );

// [V] Element access

template < typename T >
typename vector<T>::const_reference vector<T>::back( void ) const {
    return const_cast< vector<T>::const_reference > ( this->m_storage[this->m_end-1] );
}

template < typename T >
typename vector<T>::const_reference vector<T>::front( void ) const {
    return const_cast< vector<T>::const_reference > ( * this->m_storage );
}

template < typename T >
typename vector<T>::const_reference vector<T>::operator[]( size_type pos ) const {
    return const_cast< vector<T>::const_reference > ( this->m_storage [pos] );
}

template < typename T >
typename vector<T>::reference vector<T>::operator[]( size_type pos ) {
    return this->m_storage [pos];
}

template < typename T >
typename vector<T>::const_reference vector<T>::at( vector<T>::size_type pos ) const
{
    if(pos >= this->m_end || pos < 0)
        throw std::out_of_range("Index provided is outside the array range.");
    return this->m_storage[pos];
}

template < typename T >
typename vector<T>::reference vector<T>::at( vector<T>::size_type pos )
{
    if(pos >= this->m_end || pos < 0)
        throw std::out_of_range("Index provided is outside the array range.");
    return this->m_storage[pos];
}


template < typename T >
typename vector<T>::pointer vector<T>::data( void ) {
    return this->m_storage;
}

template < typename T >
typename vector<T>::const_reference vector<T>::data( void ) const
{
    return const_cast< vector<T>::const_reference > ( * this->m_storage );
}


// [VI] Operators


template < typename T >
bool vector<T>::operator==( const vector<T> & vtr) const{
    if( this->m_end == vtr.m_end && this->m_capacity == vtr.m_capacity ){
        for( auto i(0u) ; i < this->m_capacity ; i++ ){
            if(*(this->m_storage+i) != *(vtr.m_storage+i))
                return false;
        }
        return true;
    }
    
    return false;
}

template < typename T >
bool vector<T>::operator!=( const vector & vtr) const{
    if( this->m_end == vtr.m_end && this->m_capacity == vtr.m_capacity ){
        for( auto i(0u) ; i < this->m_capacity ; i++ ){
            if(*(this->m_storage+i) == *(vtr.m_storage+i))
                return false;
        }
        return true;
    }
    
    return true;
}

// [VII] Friend functions.


template < typename T >
void swap(vector<T>& first_, vector<T> & second_ ){
    auto valor = *first_;
    *first_ = *second_;
    *second_ = valor;
}

// [+] Non-member functions

template < typename T >
bool operator==( const vector<T>& lhs, const vector<T>& rhs ){
    if( lhs.m_end == rhs.m_end && lhs.m_capacity == rhs.m_capacity ){
        for( auto i(0u) ; i < lhs.m_capacity ; i++ ){
            if(*(lhs.m_storage+i) != *(rhs.m_storage+i))
                return false;
        }
        return true;
    }
    
    return false;
}

template < typename T >
bool operator!=( const vector<T>& lhs, const vector<T>& rhs ){
    if( lhs.m_end == rhs.m_end && lhs.m_capacity == rhs.m_capacity ){
        for( auto i(0u) ; i < lhs.m_capacity ; i++ ){
            if(*(lhs.m_storage+i) != *(rhs.m_storage+i))
                return true;
        }
        return false;
    }
    
    return true;
}
