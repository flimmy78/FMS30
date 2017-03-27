// list standard header
#pragma once

#include <functional>
#include <memory>
#include <stdexcept>

#pragma pack(push,8)
#pragma warning(push,3)

#pragma warning(disable:4284)

#define _GENERIC_BASE _Node

#if _MSC_VER > 1500 // VS2008 is 1500

#define _CPOINTER_X(T, A)		\
	typename A::template rebind<T>::other::const_pointer
 #define _CREFERENCE_X(T, A)	\
	typename A::template rebind<T>::other::const_reference
 #define _POINTER_X(T, A)	\
	typename A::template rebind<T>::other::pointer
 #define _REFERENCE_X(T, A)	\
	typename A::template rebind<T>::other::reference


template<class _Ty,
	class _Diff,
	class _Pointer,
	class _Reference>
	struct _Bidit
		: public _Iterator_base

	{	// base type for container bidirectional iterator classes
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef _Ty value_type;
	typedef _Diff difference_type;
	typedef _Diff distance_type;	// retained
	typedef _Pointer pointer;
	typedef _Reference reference;
	};
#endif
//_STD_BEGIN
		// TEMPLATE CLASS _MV_List_nod
template<class _Ty, class _Alloc>
	class _MV_List_nod
	{	// base class for _MV_List_ptr to hold allocator _Alnod
protected:
	struct _Node;
	friend struct _Node;
	typedef typename _Alloc::template
		rebind<_GENERIC_BASE>::other::pointer _Genptr;

	struct _Node
		{	// list node
		_Node(_Genptr _Nextarg, _Genptr _Prevarg, const _Ty& _Myvalarg)
			: _Next(_Nextarg), _Prev(_Prevarg), _Myval(_Myvalarg)
			{	// construct a node with value
			}

		_Genptr _Next;	// successor node, or first element if head
		_Genptr _Prev;	// predecessor node, or last element if head
		_Ty _Myval;	// the stored value, unused if head
		};

	_MV_List_nod(_Alloc _Al)
		: _Alnod(_Al)
		{	// construct allocator from _Al
		}

	typename _Alloc::template rebind<_Node>::other
		_Alnod;	// allocator object for nodes
	};

		// TEMPLATE CLASS _MV_List_ptr
template<class _Ty,
	class _Alloc>
	class _MV_List_ptr
		: public _MV_List_nod<_Ty, _Alloc>
	{	// base class for _MV_List_val to hold allocator _Alptr
protected:
	typedef typename _MV_List_nod<_Ty, _Alloc>::_Node _Node;
	typedef typename _Alloc::template
		rebind<_Node>::other::pointer _Nodeptr;

	_MV_List_ptr(_Alloc _Al)
		: _MV_List_nod<_Ty, _Alloc>(_Al), _Alptr(_Al)
		{	// construct base, and allocator from _Al
		}

	typename _Alloc::template rebind<_Nodeptr>::other
		_Alptr;	// allocator object for pointers to nodes
	};

		// TEMPLATE CLASS _MV_List_val
template<class _Ty,
	class _Alloc>
	class _MV_List_val
		: public _MV_List_ptr<_Ty, _Alloc>
	{	// base class for list to hold allocator _Alval
protected:
	typedef typename _Alloc::template rebind<_Ty>::other _Alty;

	_MV_List_val(_Alloc _Al = _Alloc())
		: _MV_List_ptr<_Ty, _Alloc>(_Al), _Alval(_Al)
		{	// construct base, and allocator from _Al
		}

	_Alty _Alval;	// allocator object for values stored in nodes
	};

		// TEMPLATE CLASS list
template<class _Ty,
	class _Ax = allocator<_Ty> >
	class TMvSTLList
		: public _MV_List_val<_Ty, _Ax>
	{	// bidirectional linked list
public:
	typedef TMvSTLList<_Ty, _Ax> _Myt;
	typedef _MV_List_val<_Ty, _Ax> _Mybase;
	typedef typename _Mybase::_Alty _Alloc;

protected:
	typedef typename _MV_List_nod<_Ty, _Ax>::_Genptr _Genptr;
	typedef typename _MV_List_nod<_Ty, _Ax>::_Node _Node;
	typedef _POINTER_X(_Node, _Alloc) _Nodeptr;
	typedef _REFERENCE_X(_Nodeptr, _Alloc) _Nodepref;
	typedef typename _Alloc::reference _Vref;

	static _Nodepref _Nextnode(_Nodeptr _Pnode)
		{	// return reference to successor pointer in node
		return ((_Nodepref)(*_Pnode)._Next);
		}

	static _Nodepref _Prevnode(_Nodeptr _Pnode)
		{	// return reference to predecessor pointer in node
		return ((_Nodepref)(*_Pnode)._Prev);
		}

	static _Vref _Myval(_Nodeptr _Pnode)
		{	// return reference to value in node
		return ((_Vref)(*_Pnode)._Myval);
		}

public:
	typedef _Alloc allocator_type;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type _Dift;
	typedef _Dift difference_type;
	typedef typename _Alloc::pointer _Tptr;
	typedef typename _Alloc::const_pointer _Ctptr;
	typedef _Tptr pointer;
	typedef _Ctptr const_pointer;
	typedef typename _Alloc::reference _Reft;
	typedef _Reft reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::value_type value_type;

		// CLASS const_iterator
	class const_iterator;
	friend class const_iterator;

	class const_iterator
#if _MSC_VER > 1500 // VS2008 is 1500
		: public _Bidit<_Ty, _Dift, _Ctptr, const_reference>
#else
		: public std::_Bidit<_Ty, _Dift, _Ctptr, const_reference>
#endif
		{	// iterator for nonmutable list
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef _Ty value_type;
		typedef _Dift difference_type;
		typedef _Ctptr pointer;
		typedef const_reference reference;

		const_iterator()
			: _Ptr(0)
			{	// construct with null node pointer
			}

		const_iterator(_Nodeptr _Pnode)
			: _Ptr(_Pnode)
			{	// construct with node pointer _Pnode
			}

		const_reference operator*() const
			{	// return designated value
			return (_Myval(_Ptr));
			}

		_Ctptr operator->() const
			{	// return pointer to class object
			return (&**this);
			}

		const_iterator& operator++()
			{	// preincrement
			_Ptr = _Nextnode(_Ptr);
			return (*this);
			}

		const_iterator operator++(int)
			{	// postincrement
			const_iterator _Tmp = *this;
			++*this;
			return (_Tmp);
			}

		const_iterator& operator--()
			{	// predecrement
			_Ptr = _Prevnode(_Ptr);
			return (*this);
			}

		const_iterator operator--(int)
			{	// postdecrement
			const_iterator _Tmp = *this;
			--*this;
			return (_Tmp);
			}

		bool operator==(const const_iterator& _Right) const
			{	// test for iterator equality
			return (_Ptr == _Right._Ptr);
			}

		bool operator!=(const const_iterator& _Right) const
			{	// test for iterator inequality
			return (!(*this == _Right));
			}

		_Nodeptr _Mynode() const
			{	// return node pointer
			return (_Ptr);
			}


	protected:
		_Nodeptr _Ptr;	// pointer to node
		};

		// CLASS iterator
	class iterator;
	friend class iterator;

	class iterator
		: public const_iterator
		{	// iterator for mutable list
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef _Ty value_type;
		typedef _Dift difference_type;
		typedef _Tptr pointer;
		typedef _Reft reference;

		iterator()
			{	// construct with null node
			}

		iterator(_Nodeptr _Pnode)
			: const_iterator(_Pnode)
			{	// construct with node pointer _Pnode
			}

		reference operator*() const
			{	// return designated value
			return ((reference)**(const_iterator *)this);
			}

		_Tptr operator->() const
			{	// return pointer to class object
			return (&**this);
			}

		iterator& operator++()
			{	// preincrement
			++(*(const_iterator *)this);
			return (*this);
			}

		iterator operator++(int)
			{	// postincrement
			iterator _Tmp = *this;
			++*this;
			return (_Tmp);
			}

		iterator& operator--()
			{	// predecrement
			--(*(const_iterator *)this);
			return (*this);
			}

		iterator operator--(int)
			{	// postdecrement
			iterator _Tmp = *this;
			--*this;
			return (_Tmp);
			}
		};

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	TMvSTLList()
		: _Mybase(), _Myhead(_Buynode()), _Mysize(0)
		{	// construct empty list
		}

	explicit TMvSTLList(const _Alloc& _Al)
		: _Mybase(_Al), _Myhead(_Buynode()), _Mysize(0)
		{	// construct empty list, allocator
		}

	explicit TMvSTLList(size_type _Count)
		: _Mybase(), _Mysize(0)
		{	// construct list from _Count * _Ty()
		_Ty _Val = _Ty();
		_Myhead = _Buynode();
		_Construct_n(_Count, _Val);
		}

	TMvSTLList(size_type _Count, const _Ty& _Val)
		: _Mybase(), _Myhead(_Buynode()), _Mysize(0)
		{	// construct list from _Count * _Val
		_Construct_n(_Count, _Val);
		}

	TMvSTLList(size_type _Count, const _Ty& _Val, const _Alloc& _Al)
		: _Mybase(_Al), _Myhead(_Buynode()), _Mysize(0)
		{	// construct list, allocator from _Count * _Val
		_Construct_n(_Count, _Val);
		}

	TMvSTLList(const _Myt& _Right)
		: _Mybase(_Right._Alval),
			_Myhead(_Buynode()), _Mysize(0)
		{	// construct list by copying _Right
		_TRY_BEGIN
		insert(begin(), _Right.begin(), _Right.end());
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	template<class _Iter>
		TMvSTLList(_Iter _First, _Iter _Last)
		: _Mybase(), _Myhead(_Buynode()), _Mysize(0)
		{	// construct list from [_First, _Last)
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		TMvSTLList(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _Mybase(_Al), _Myhead(_Buynode()), _Mysize(0)
		{	// construct list, allocator from [_First, _Last)
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Construct(_Iter _Count, _Iter _Val, std::_Int_iterator_tag)
		{	// construct list from _Count * _Val
		_Construct_n((size_type)_Count, (_Ty)_Val);
		}

	template<class _Iter>
		void _Construct(_Iter _First,
			_Iter _Last, std::input_iterator_tag)
		{	// construct list from [_First, _Last), input iterators
		_TRY_BEGIN
		insert(begin(), _First, _Last);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	void _Construct_n(size_type _Count,
		const _Ty& _Val)
		{	// construct from _Count * _Val
		_TRY_BEGIN
		_Insert_n(begin(), _Count, _Val);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	~TMvSTLList()
		{	// destroy the object
		_Tidy();
		}

	_Myt& operator=(const _Myt& _Right)
		{	// assign _Right
		if (this != &_Right)
			assign(_Right.begin(), _Right.end());
		return (*this);
		}

	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(_Nextnode(_Myhead)));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_Nextnode(_Myhead)));
		}

	iterator end()
		{	// return iterator for end of mutable sequence
		return (iterator(_Myhead));
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		return (const_iterator(_Myhead));
		}

	reverse_iterator rbegin()
		{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend()
		{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const
		{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
		}

	void resize(size_type _Newsize)
		{	// determine new length, padding with _Ty() elements as needed
		resize(_Newsize, _Ty());
		}

	void resize(size_type _Newsize, _Ty _Val)
		{	// determine new length, padding with _Val elements as needed
		if (_Mysize < _Newsize)
			_Insert_n(end(), _Newsize - _Mysize, _Val);
		else
			while (_Newsize < _Mysize)
				pop_back();
		}

	size_type size() const
		{	// return length of sequence
		return (_Mysize);
		}

	size_type max_size() const
		{	// return maximum possible length of sequence
		return (this->_Alval.max_size());
		}

	bool empty() const
		{	// test if sequence is empty
		return (_Mysize == 0);
		}

	allocator_type get_allocator() const
		{	// return allocator object for values
		return (this->_Alval);
		}

	reference front()
		{	// return first element of mutable sequence
		return (*begin());
		}

	const_reference front() const
		{	// return first element of nonmutable sequence
		return (*begin());
		}

	reference back()
		{	// return last element of mutable sequence
		return (*(--end()));
		}

	const_reference back() const
		{	// return last element of nonmutable sequence
		return (*(--end()));
		}

	void push_front(const _Ty& _Val)
		{	// insert element at beginning
		_Insert(begin(), _Val);
		}

	void pop_front()
		{	// erase element at beginning
		erase(begin());
		}

	void push_back(const _Ty& _Val)
		{	// insert element at end
		_Insert(end(), _Val);
		}

	void pop_back()
		{	// erase element at end
		erase(--end());
		}

	template<class _Iter>
		void assign(_Iter _First, _Iter _Last)
		{	// assign [_First, _Last)
		_Assign(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Assign(_Iter _Count, _Iter _Val, std::_Int_iterator_tag)
		{	// assign _Count * _Val
		_Assign_n((size_type)_Count, (_Ty)_Val);
		}

	template<class _Iter>
		void _Assign(_Iter _First, _Iter _Last, std::input_iterator_tag)
		{	// assign [_First, _Last), input iterators
		clear();
		insert(begin(), _First, _Last);
		}

	void assign(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Assign_n(_Count, _Val);
		}

	iterator insert(iterator _Where, const _Ty& _Val)
		{	// insert _Val at _Where
		_Insert(_Where, _Val);
		return (--_Where);
		}

	void _Insert(iterator _Where,
		const _Ty& _Val)
		{	// insert _Val at _Where
		_Nodeptr _Pnode = _Where._Mynode();
		_Nodeptr _Newnode = _Buynode(_Pnode, _Prevnode(_Pnode), _Val);
		_Incsize(1);
		_Prevnode(_Pnode) = _Newnode;
		_Nextnode(_Prevnode(_Newnode)) = _Newnode;
		}

	void insert(iterator _Where, size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, _Count, _Val);
		}

	template<class _Iter>
		void insert(iterator _Where, _Iter _First, _Iter _Last)
		{	// insert [_First, _Last) at _Where
		_Insert(_Where, _First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Insert(iterator _Where, _Iter _Count, _Iter _Val,
			std::_Int_iterator_tag)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, (size_type)_Count, (_Ty)_Val);
		}

	template<class _Iter>
		void _Insert(iterator _Where,
			_Iter _First, _Iter _Last, std::input_iterator_tag)
		{	// insert [_First, _Last) at _Where, input iterators
		size_type _Num = 0;

		_TRY_BEGIN
		for (; _First != _Last; ++_First, ++_Num)
			_Insert(_Where, *_First);
		_CATCH_ALL
		for (; 0 < _Num; --_Num)
			{	// undo inserts
			iterator _Before = _Where;
			erase(--_Before);
			}
		_RERAISE;
		_CATCH_END
		}

	template<class _Iter>
		void _Insert(iterator _Where,
			_Iter _First, _Iter _Last, std::forward_iterator_tag)
		{	// insert [_First, _Last) at _Where, forward iterators
		_Iter _Next = _First;

		_TRY_BEGIN
		for (; _First != _Last; ++_First)
			_Insert(_Where, *_First);
		_CATCH_ALL
		for (; _Next != _First; ++_Next)
			{	// undo inserts
			iterator _Before = _Where;
			erase(--_Before);
			}
		_RERAISE;
		_CATCH_END
		}

	iterator erase(iterator _Where)
		{	// erase element at _Where
		_Nodeptr _Pnode = (_Where++)._Mynode();
		if (_Pnode != _Myhead)
			{	// not list head, safe to erase
			_Nextnode(_Prevnode(_Pnode)) = _Nextnode(_Pnode);
			_Prevnode(_Nextnode(_Pnode)) = _Prevnode(_Pnode);
			this->_Alnod.destroy(_Pnode);
			this->_Alnod.deallocate(_Pnode, 1);
			--_Mysize;
			}
		return (_Where);
		}

	iterator erase(iterator _First, iterator _Last)
		{	// erase [_First, _Last)
		if (_First == begin() && _Last == end())
			clear();
		else
			while (_First != _Last)
				_First = erase(_First);
		return (_Last);
		}

	void clear()
		{	// erase all
		_Nodeptr _Pnext;
		_Nodeptr _Pnode = _Nextnode(_Myhead);
		_Nextnode(_Myhead) = _Myhead;
		_Prevnode(_Myhead) = _Myhead;
		_Mysize = 0;

		for (; _Pnode != _Myhead; _Pnode = _Pnext)
			{	// delete an element
			_Pnext = _Nextnode(_Pnode);
			this->_Alnod.destroy(_Pnode);
			this->_Alnod.deallocate(_Pnode, 1);
			}
		}

	void swap(_Myt& _Right)
		{	// exchange contents with _Right
		if (this->_Alval == _Right._Alval)
			{	// same allocator, swap control information
			std::swap(_Myhead, _Right._Myhead);
			std::swap(_Mysize, _Right._Mysize);
			}
		else
			{	// different allocator, do splices
			iterator _Where = begin();
			splice(_Where, _Right);
			_Right.splice(_Right.begin(), *this, _Where, end());
			}
		}

	void splice(iterator _Where, _Myt& _Right)
		{	// splice all of _Right at _Where
		if (this != &_Right && !_Right.empty())
			{	// worth splicing, do it
			_Splice(_Where, _Right, _Right.begin(), _Right.end(),
				_Right._Mysize);
			}
		}

	void splice(iterator _Where, _Myt& _Right, iterator _First)
		{	// splice _Right [_First, _First + 1) at _Where
		if (_First != _Right.end())

			{	// element exists, try splice
			iterator _Last = _First;
			++_Last;
			if (this != &_Right
				|| (_Where != _First && _Where != _Last))
				_Splice(_Where, _Right, _First, _Last, 1);
			}
		}

	void splice(iterator _Where,
		_Myt& _Right, iterator _First, iterator _Last)
		{	// splice _Right [_First, _Last) at _Where
		if (_First != _Last && (this != &_Right || _Where != _Last))
			{	// worth splicing, do it
			size_type _Count = 0;
			if (this == &_Right)
				;	// just rearrange this list
			else if (_First == _Right.begin() && _Last == _Right.end())
				_Count = _Right._Mysize;	// splice in whole list
			else
				_Distance(_First, _Last, _Count);	// splice in partial list
			_Splice(_Where, _Right, _First, _Last, _Count);
			}
		}

	void remove(const _Ty& _Val)
		{	// erase each element matching _Val
		iterator _Last = end();
		for (iterator _First = begin(); _First != _Last; )
			if (*_First == _Val)
				_First = erase(_First);
			else
				++_First;
		}

	template<class _Pr1>
		void remove_if(_Pr1 _Pred)
		{	// erase each element satisfying _Pr1
		iterator _Last = end();
		for (iterator _First = begin(); _First != _Last; )
			if (_Pred(*_First))
				_First = erase(_First);
			else
				++_First;
		}

	void unique()
		{	// erase each element matching previous
		if (2 <= _Mysize)
			{	// worth doing
			iterator _First = begin();
			iterator _After = _First;
			for (++_After; _After != end(); )
				if (*_First == *_After)
					_After = erase(_After);
				else
					_First = _After++;
			}
		}

	template<class _Pr2>
		void unique(_Pr2 _Pred)
		{	// erase each element satisfying _Pred with previous
		if (2 <= _Mysize)
			{	// worth doing
			iterator _First = begin();
			iterator _After = _First;
			for (++_After; _After != end(); )
				if (_Pred(*_First, *_After))
					_After = erase(_After);
				else
					_First = _After++;
			}
		}

	void merge(_Myt& _Right)
		{	// merge in elements from _Right, both ordered by operator<
		if (&_Right != this)
			{	// safe to merge, do it
			iterator _First1 = begin(), _Last1 = end();
			iterator _First2 = _Right.begin(), _Last2 = _Right.end();

			while (_First1 != _Last1 && _First2 != _Last2)
				if (*_First2 < *_First1)
					{	// splice in an element from _Right
					iterator _Mid2 = _First2;
					_Splice(_First1, _Right, _First2, ++_Mid2, 1);
					_First2 = _Mid2;
					}
				else
					++_First1;

			if (_First2 != _Last2)
				_Splice(_Last1, _Right, _First2, _Last2,
					_Right._Mysize);	// splice remainder of _Right
			}
		}

	template<class _Pr3>
		void merge(_Myt& _Right, _Pr3 _Pred)
		{	// merge in elements from _Right, both ordered by _Pred
		if (&_Right != this)
			{	// safe to merge, do it
			iterator _First1 = begin(), _Last1 = end();
			iterator _First2 = _Right.begin(), _Last2 = _Right.end();

			while (_First1 != _Last1 && _First2 != _Last2)
				if (_Pred(*_First2, *_First1))
					{	// splice in an element from _Right
					iterator _Mid2 = _First2;
					_Splice(_First1, _Right, _First2, ++_Mid2, 1);
					_First2 = _Mid2;
					}
				else
					++_First1;

			if (_First2 != _Last2)
				_Splice(_Last1, _Right, _First2, _Last2,
					_Right._Mysize);	// splice remainder of _Right
			}
		}

	void sort()
		{	// order sequence, using operator<
		if (2 <= _Mysize)
			{	// worth sorting, do it
			const size_t _MAXBINS = 25;
			_Myt _Templist(this->_Alval), _Binlist[_MAXBINS + 1];
			size_t _Maxbin = 0;

			while (!empty())
				{	// sort another element, using bins
				_Templist.splice(_Templist.begin(), *this, begin());
				size_t _Bin;

				for (_Bin = 0; _Bin < _Maxbin && !_Binlist[_Bin].empty();
					++_Bin)
					{	// merge into ever larger bins
					_Binlist[_Bin].merge(_Templist);
					_Binlist[_Bin].swap(_Templist);
					}

				if (_Bin == _MAXBINS)
					_Binlist[_Bin - 1].merge(_Templist);
				else
					{	// spill to new bin, while they last
					_Binlist[_Bin].swap(_Templist);
					if (_Bin == _Maxbin)
						++_Maxbin;
					}
				}

			for (size_t _Bin = 1; _Bin < _Maxbin; ++_Bin)
				_Binlist[_Bin].merge(_Binlist[_Bin - 1]);	// merge up
			swap(_Binlist[_Maxbin - 1]);	// replace from last bin
			}
		}

	template<class _Pr3>
		void sort(_Pr3 _Pred)
		{	// order sequence, using _Pred
		if (2 <= _Mysize)
			{	// worth sorting, do it
			const size_t _MAXBINS = 25;
			_Myt _Templist(this->_Alval), _Binlist[_MAXBINS + 1];
			size_t _Maxbin = 0;

			while (!empty())
				{	// sort another element, using bins
				_Templist.splice(_Templist.begin(), *this, begin());
				size_t _Bin;

				for (_Bin = 0; _Bin < _Maxbin && !_Binlist[_Bin].empty();
					++_Bin)
					{	// merge into ever larger bins
					_Binlist[_Bin].merge(_Templist, _Pred);
					_Binlist[_Bin].swap(_Templist);
					}

				if (_Bin == _MAXBINS)
					_Binlist[_Bin - 1].merge(_Templist, _Pred);
				else
					{	// spill to new bin, while they last
					_Binlist[_Bin].swap(_Templist);
					if (_Bin == _Maxbin)
						++_Maxbin;
					}
				}

			for (size_t _Bin = 1; _Bin < _Maxbin; ++_Bin)
				_Binlist[_Bin].merge(_Binlist[_Bin - 1],
					_Pred);	// merge up
			swap(_Binlist[_Maxbin - 1]);	// replace with last bin
			}
		}

	void reverse()
		{	// reverse sequence
		if (2 <= _Mysize)
			{	// worth doing
			iterator _Last = end();
			for (iterator _Next = ++begin(); _Next != _Last; )
				{	// move next element to beginning
				iterator _Before = _Next;
				_Splice(begin(), *this, _Before, ++_Next, 1);
				}
			}
		}

	void _Splice(iterator _Where,
		_Myt& _Right, iterator _First, iterator _Last, size_type _Count)
		{	// splice _Right [_First, _Last) before _Where

		if (this->_Alval == _Right._Alval)
			{	// same allocator, just relink

			if (this != &_Right)
				{	// splicing from another list, adjust counts
				_Incsize(_Count);
				_Right._Mysize -= _Count;
				}
			_Nextnode(_Prevnode(_First._Mynode())) = _Last._Mynode();
			_Nextnode(_Prevnode(_Last._Mynode())) = _Where._Mynode();
			_Nextnode(_Prevnode(_Where._Mynode())) = _First._Mynode();
			_Nodeptr _Pnode = _Prevnode(_Where._Mynode());
			_Prevnode(_Where._Mynode()) = _Prevnode(_Last._Mynode());
			_Prevnode(_Last._Mynode()) = _Prevnode(_First._Mynode());
			_Prevnode(_First._Mynode()) = _Pnode;
			}
		else
			{	// different allocator, copy nodes then erase source
			insert(_Where, _First, _Last);
			_Right.erase(_First, _Last);
			}
		}

protected:
	void _Assign_n(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Ty _Tmp = _Val;	// in case _Val is in sequence
		clear();
		_Insert_n(begin(), _Count, _Tmp);
		}

	_Nodeptr _Buynode()
		{	// allocate a head node and set links
		_Nodeptr _Pnode = this->_Alnod.allocate(1);
		int _Linkcnt = 0;

		_TRY_BEGIN
		this->_Alptr.construct(&_Nextnode(_Pnode), _Pnode);
		++_Linkcnt;
		this->_Alptr.construct(&_Prevnode(_Pnode), _Pnode);
		_CATCH_ALL
		if (0 < _Linkcnt)
			this->_Alptr.destroy(&_Nextnode(_Pnode));
		this->_Alnod.deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END
		return (_Pnode);
		}

	_Nodeptr _Buynode(_Nodeptr _Next,
		_Nodeptr _Prev, const _Ty& _Val)
		{	// allocate a node and set links and value
		_Nodeptr _Pnode = this->_Alnod.allocate(1);
		_TRY_BEGIN
		new ((void *)_Pnode) _Node(_Next, _Prev, _Val);
		_CATCH_ALL
		this->_Alnod.deallocate(_Pnode, 1);
		_RERAISE;
		_CATCH_END
		return (_Pnode);
		}

	void _Tidy()
		{	// free all storage
		clear();
		this->_Alptr.destroy(&_Nextnode(_Myhead));
		this->_Alptr.destroy(&_Prevnode(_Myhead));
		this->_Alnod.deallocate(_Myhead, 1);
		_Myhead = 0;
		}

	void _Insert_n(iterator _Where,
		size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		size_type _Countsave = _Count;

		_TRY_BEGIN
		for (; 0 < _Count; --_Count)
			_Insert(_Where, _Val);
		_CATCH_ALL
		for (; _Count < _Countsave; ++_Count)
			{	// undo inserts
			iterator _Before = _Where;
			erase(--_Before);
			}
		_RERAISE;
		_CATCH_END
		}

	void _Incsize(size_type _Count)
		{	// alter element count, with checking
		if (max_size() - _Mysize < _Count)
			_THROW(length_error, "list<T> too long");
		_Mysize += _Count;
		}


public:
	_Nodeptr _Myhead;	// pointer to head node
	size_type _Mysize;	// number of elements
	};

		// list TEMPLATE OPERATORS
template<class _Ty, class _Alloc> inline
	void swap(TMvSTLList<_Ty, _Alloc>& _Left, TMvSTLList<_Ty, _Alloc>& _Right)
	{	// swap _Left and _Right lists
	_Left.swap(_Right);
	}

template<class _Ty, class _Alloc> inline
	bool operator==(const TMvSTLList<_Ty, _Alloc>& _Left,
		const TMvSTLList<_Ty, _Alloc>& _Right)
	{	// test for list equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
	}

template<class _Ty, class _Alloc> inline
	bool operator!=(const TMvSTLList<_Ty, _Alloc>& _Left,
		const TMvSTLList<_Ty, _Alloc>& _Right)
	{	// test for list inequality
	return (!(_Left == _Right));
	}

template<class _Ty, class _Alloc> inline
	bool operator<(const TMvSTLList<_Ty, _Alloc>& _Left,
		const TMvSTLList<_Ty, _Alloc>& _Right)
	{	// test if _Left < _Right for lists
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
	}

template<class _Ty, class _Alloc> inline
	bool operator>(const TMvSTLList<_Ty, _Alloc>& _Left,
		const TMvSTLList<_Ty, _Alloc>& _Right)
	{	// test if _Left > _Right for lists
	return (_Right < _Left);
	}

template<class _Ty, class _Alloc> inline
	bool operator<=(const TMvSTLList<_Ty, _Alloc>& _Left,
		const TMvSTLList<_Ty, _Alloc>& _Right)
	{	// test if _Left <= _Right for lists
	return (!(_Right < _Left));
	}

template<class _Ty, class _Alloc> inline
	bool operator>=(const TMvSTLList<_Ty, _Alloc>& _Left,
		const TMvSTLList<_Ty, _Alloc>& _Right)
	{	// test if _Left >= _Right for lists
	return (!(_Left < _Right));
	}


//_STD_END
#pragma warning(pop)
#pragma pack(pop)


/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Hewlett-Packard Company makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 V3.13:0009 */
