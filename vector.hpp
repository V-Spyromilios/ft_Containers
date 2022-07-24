#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <bits/functexcept.h>

#include <memory>



namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> > class vector
	{
		typedef Alloc					alloc;
		typedef std::size_t				tsize;
		typedef std::ptrdiff_t			ptr_diff;
		typedef T&						ref;  //?
		typedef const T&				con_ref;
		typedef typename Alloc::pointer a_ptr;
		typedef typename Alloc::const_pointer a_con_ptr;

		typedef ft::VecIter<value_type>						iter;
		typedef const ft::VecIter<value_type>				con_iter;
		typedef ft::reverse_iterator<iterator>				rev_iter;
		typedef ft::reverse_iterator<const_iterator>		con_rev_iter;
	
	private:

		a_ptr 	_vectoras;
		tsize	_size;
		tsize	_capacity;
		alloc 	_malloc;
	

	public:

	// CONSTRUCTOS
	explicit vector(const alloc& all = allocator_type()):
	_size(0), _capacity(0), _malloc(all) {
		_vectoras = _malloc.allocate(0);
	}

	explicit vector(tsize count, const T& value = T(), const alloc& all = alloc()):
	_capacity(count), _size(0), _malloc(all) {
		_vectoras = _malloc.allocate(count);
		for (tsize j = 0; j < count; j++)
		{
			_malloc.construct(&_vectoras[j], value);
			_size = j + 1;
		}
	}

	//DESTRUCTOR
	~vector() {
		_malloc.deallocate(_vectoras, capacity());
	}

	// COPY CONSTRUCTOR
	vector(const vector<T>& other) :
		_size(other._size);
		_capacity(other._capacity);
		_malloc(other._alloc)
		{
			_vectoras = _malloc.allocate(_capacity);
			for (tsize i = 0; i < _size; i++)
				_malloc.construct(&_vectoras[i, other._vectoras[i]]);
		}

	// = OVERLOADING
	vector& operator=(const  vector<T>& other)
	{
		_size(other._size);
		_capacity(other._capacity);
		_malloc(other._malloc);
		_vectoras = _malloc.allocate(_capacity);
		for (tsize i = 0; i < _size; i++)
			_malloc.construct(&_vectoras[i], other._vectoras[i]);
		return (*this);
	}


	alloc get_allocator() const {
		return (this->_malloc);
	}

	ref front() {
		return (this->_vectoras[0]);
	}

	con_ref front() const {
		return (this->_vectoras[0]);
	}

	ref back() {
		return (this-> _vectoras[size() - 1]);
	}

	con_ref back() const {
		return (this-> _vectoras[size() - 1]);
	}

	T* data(){
			return (this->_vectoras);
	}

	const T* data() const{
			return this->_vectoras;
		}


	// ITERATORS & functions
	iter begin() {
		return (iterator(this->_vectoras));
	}

	con_iter begin() const {
		return ((con_iter(this->_vectoras)))
	}

	iter end() {
		return (iter(this->_vectoras + this->_size));
	}

	con_iter end() const {
		return (con_iter(this->_vectoras + this->_size));
	}

	rev_iter rbegin() {
		return (rev_iter(this->_vectoras + this->_size));
	}

	con_rev_iter rbegin() const {
		return (con_rev_iter(this->_vectoras + this->_size));
	}

	rev_iter rend() { 
		return (rev_iter(this->_vectoras));
	}

	con_rev_iter rend() const { 
	return (con_rev_iter(this->_vectoras));
	}

	iter insert(iter pos, const T& value)
	{
		tsize it = pos - begin();
		insert(pos, 1, value);
		return (iter(_vectoras + it));
	}

	void insert( iter pos, tsize count, const T& value)
	{
		tsize it = pos - begin();
		if (count + size() > capacity())
			reserve(size() + count);
		for(tsize i = 0; i < count; i++)
			_malloc.construct(_vectoras + _size + i, value);
		for (int i = _size -1; i >= 0 && i >= (int)it; i--)
			_vectoras[i + count] = _vectoras[i];
		for (tsize i = it; i < it + count; i++)
			_vectoras[i] = value;
		_size += count;
	}

	iter erase(iter pos)
	{
		tsize i = pos - begin();

		for (; i < _size - 1; i++)
			_vectoras[i] = _vectoras[i + 1];
		_size--;
		_malloc.destroy(_vectoras + _size);
		return (pos);
	}

	iter erase(iter first, iter last)
	{
		tsize i = last - first;

		if (_size == 0 && _capacity == 0)
			reserve(1);
		else if (_size == _capacity)
			reserve(_limit * 2);
		_malloc.construct(_vectoras + _size, value);
		_size++;
	}





	//OTHER FUNCTIONS
	void pop_back()
	{
		if (_size)
		{
			_malloc.destroy(_vectoras + _size - 1);
			_size--;
		}
	}

	void push_back(const ref value)
	{
		if (_size == 0 && _capacity == 0)
			reserve(1);
		else if (_size == _capacity)
			reserve(_capacity * 2);
		_malloc.construst(_vectoras + _size, value);
		_size++;
	}

	void resize(tsize count, T value = T())
	{
		if (_size > count)
			for (tsize i = _size; i > count; i--)
				pop_back();
		else
		{
			reserve(count);
			for (tsize i = _size; i < count; i++)
				push_back(value);
		}
	}

	void swap(vector<T>& other)
	{
		tsize size = _size;
		tsize capacity = _capacity;
		a_ptr vect = _vectoras;
		_size = other._size;
		_capacity = other._capacity;
		_vectoras = other._vectoras;
		other._size = size;
		other._capacity = capacity;
		other._vectoras = vect;
	}

	ref at(tsize pos)
	{
		if (pos >= _size)
			std::__throw_out_of_range_fmt(__N("vector::_M_range_check: __n "
			       "(which is %zu) >= this->size() "
			       "(which is %zu)"),
			   		pos, this->size());
		return (_vectoras[pos]);
	}

	con_ref at(tsize pos) const
	{
		if (pos >= _size)
			std::__throw_out_of_range_fmt(__N("vector::_M_range_check: __n "
			       "(which is %zu) >= this->size() "
			       "(which is %zu)"),
					pos, this->size());
			return (_vectoras[pos]);
	}

	ref operator[](tsize pos) {
		return (*(_vectoras + pos));
	}

	con_ref operator[](tsize pos) {
		return (*(_vectoras + pos));
	}




	bool empty(void) const {
		return (this->_size > 0 ? false: true);
	}

	tsize size(void) const {
		return (this->_size);
	}

	tsize max_size(void) const {
		return (this->_max_size());
	}

	tsize capacity(void) const {
		return (this->_capacity);
	}

	void clear(void) {
		while(this->_size != 0)
			pop_back();
	}



	}
}

#endif