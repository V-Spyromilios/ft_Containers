#ifndef VECTOR_HPP
# define VECTOR_HPP


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
	
	private:

		a_ptr 	_vectoras;
		tsize	_size;
		tsize	_capacity;
		alloc 	_malloc;
	

	public:

	explicit vector(const alloc& all = allocator_type()):
	_size(0), _capacity(0), _malloc(all) {
		_vectoras = _malloc.allocate(0);
	}

	explicit vector(tsize count, const T& value = T(), const alloc& all = alloc()):
	_capacity(count), _size(0), _malloc(all) {
		_vectoras = _malloc.allocate(count);
		for (tsize j = 0; j < count; j++) {
			_malloc.construct(&_vectoras[j], value);
			_size = j + 1;
		}
	} 


	}
}