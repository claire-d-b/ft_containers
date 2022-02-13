#ifndef MAP_H
#define MAP_H

#include "pair3.hpp"
#include "EnableIf.hpp"
#include <stdexcept>
#include <iostream>
#include <cstddef>
#include <algorithm>
#include <cmath>
#define TRUE 1
#define FALSE 0

namespace ft
{
    template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<Key, T> > >
    class map
    {
        class value_compare
            {   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
                protected:
                    Compare comp;  // constructed with map's comparison object
                public:
                    typedef bool result_type;
                    typedef Key first_argument_type;
                    typedef T second_argument_type;
                    value_compare (Compare c) : comp(c) {}
                    bool operator() (Leaf< Key, T > const & x, Leaf< Key, T > const & y) const
                    {
                        return comp(x.first, y.first);
                    };
            };
        private:
            value_compare _value_compare;
            Compare _key_compare;
            RBTree<Key, T, Compare> _p;
            size_t _n;
            size_t _capacity;
            Allocator _alloc;
        public:
            typedef Key key_type;
            typedef T mapped_type;
            typedef Leaf< Key, T > leaf_type;
            typedef const Leaf< Key, T > const_leaf_type;
            typedef pair< Key, T > value_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef biIter< leaf_type* > iterator;
            typedef biIter< const_leaf_type* > const_iterator;
            typedef biReviter< iterator > reverse_iterator;
            typedef biReviter< const_iterator > const_reverse_iterator;
            typedef std::allocator<ft::Leaf< Key, T > > _leaf_alloc;
            explicit map(const Compare& comp = key_compare(), const Allocator& alloc = Allocator()) : _value_compare(comp), _key_compare(comp), _p(RBTree< Key, T, Compare >(comp)), _n(0), _capacity(0), _alloc(alloc)
            {
                Leaf< Key, T > *end;
                Leaf< Key, T > *begin;
                end = _leaf_alloc().allocate(1);
                begin = _leaf_alloc().allocate(1);
                _leaf_alloc().construct(end, Leaf< Key, T >(key_type(), mapped_type()));
                _leaf_alloc().construct(begin, Leaf< Key, T >(key_type(), mapped_type()));
                _p.setLast(end);
                _p.setBegin(begin);
            }
            template< class InputIt >
            map(InputIt first, InputIt last, const Compare& comp = key_compare(), const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL) : _value_compare(comp), _key_compare(comp), _p(RBTree< Key, T, Compare >(comp)), _n(0), _capacity(0), _alloc(alloc)
            {
                Leaf< Key, T > *end;
                Leaf< Key, T > *begin;
                end = _leaf_alloc().allocate(1);
                begin = _leaf_alloc().allocate(1);
                _leaf_alloc().construct(end, Leaf< Key, T >(key_type(), mapped_type()));
                _leaf_alloc().construct(begin, Leaf< Key, T >(key_type(), mapped_type()));
                _p.setLast(end);
                _p.setBegin(begin);
                insert(first, last);
            }
            map(const map& other) : _value_compare(other._value_compare), _key_compare(other._key_compare), _p(RBTree< Key, T, Compare >(other._key_compare)), _n(0), _capacity(0), _alloc(other._alloc)
            {
                clear();
                Leaf< Key, T > *end;
                Leaf< Key, T > *begin;
                end = _leaf_alloc().allocate(1);
                begin = _leaf_alloc().allocate(1);
                _leaf_alloc().construct(end, Leaf< Key, T >(key_type(), mapped_type()));
                _leaf_alloc().construct(begin, Leaf< Key, T >(key_type(), mapped_type()));
                _p.setLast(end);
                _p.setBegin(begin);
                insert(other.begin(), other.end());
            }
            virtual ~map()
            {
                clear();
                _leaf_alloc().destroy(_p.getLast());
                _leaf_alloc().deallocate(_p.getLast(), 1);
                _leaf_alloc().destroy(_p.getBegin());
                _leaf_alloc().deallocate(_p.getBegin(), 1);
            }
            map& operator=(const map& other)
            {
                clear();
                _value_compare = other._value_compare;
                _key_compare = other._key_compare;
                _n = 0;
                _capacity = 0;
                _alloc = other._alloc;

                _p = RBTree< Key, T, Compare >(_key_compare);
                Leaf< Key, T > *end;
                Leaf< Key, T > *begin;
                end = _leaf_alloc().allocate(1);
                begin = _leaf_alloc().allocate(1);
                _leaf_alloc().construct(end, Leaf< Key, T >(key_type(), mapped_type()));
                _leaf_alloc().construct(begin, Leaf< Key, T >(key_type(), mapped_type()));
                _p.setLast(end);
                _p.setBegin(begin);
                insert(other.begin(), other.end());
                return *this;
            }
            key_compare key_comp() const
            {
                return _key_compare;
            }
            value_compare value_comp() const
            {
                return _value_compare;
            }
            allocator_type get_allocator() const
            {
                return allocator_type();
            }
            mapped_type& operator[](const Key& key)
            {
                if (find(key) == end())
                    return (*((insert(pair< Key, T >(key ,mapped_type()))).first)).second;
                return _p.find(Leaf< Key, T >(key ,mapped_type()))->second;
            }
            iterator begin()
            {
                if (_p.getRoot())
                    return iterator(_p.findMinimum(_p.getRoot()));
                return iterator(_p.getLast());
            }
            const_iterator begin() const
            {
                if (_p.getRoot())
                    return const_iterator(_p.findMinimum(_p.getRoot()));
                return const_iterator(_p.getLast());
            }
            iterator end()
            {
                return iterator(_p.getLast());
            }
            const_iterator end() const
            {
                return const_iterator(_p.getLast());
            }
            reverse_iterator rbegin()
            {
                if (_p.getRoot())
                    return reverse_iterator(iterator(end()));
                return (reverse_iterator(iterator(_p.getBegin())));
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(rbegin());
            }
            reverse_iterator rend()
            {
                return reverse_iterator(iterator(_p.findMinimum(_p.getRoot())));
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(rend());
            }
            bool empty() const
            {
                if (!_n)
                    return TRUE;
                return FALSE;
            }
            size_type size() const
            {
                return _n;
            }
            size_type max_size() const
            {
                return _alloc.max_size();
            }
            void clear()
            {
                erase(begin(), end());
            }
            pair<iterator, bool> insert(const value_type& value)
            {
                iterator it;
                bool exists = find(value.first) == end();
				if ((it = iterator(_p.find(Leaf< Key, T >(value.first, value.second)))) == end())
                {
                    _n++;
					_p.insert(Leaf< Key, T >(value.first, value.second));
                }
				return pair<iterator, bool>(iterator(_p.find(Leaf< Key, T >(value.first, value.second))), exists);
            }
            iterator insert(iterator hint, const value_type& value)
            {
                (void)hint;
                Leaf< Key, T > lf(value.first, value.second);
                if (iterator(_p.find(lf)) == end())
                {
                    _n++;
                    _p.insert(lf);
                }
                return iterator(_p.find(lf));
            }
            template< class InputIt >
            void insert(InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value>::type* = NULL)
            {
                while (first != last)
                {
                    Leaf< Key, T > lf(first->first, first->second);
                    if (iterator(_p.find(lf)) == end())
                    {
                        _n++;
                        _p.insert(lf);
                    }
                    first++;
                }
            }
            void erase(iterator pos, typename ft::enable_if<!is_integral<iterator>::value>::type* = NULL)
            {
                if (!_p.getRoot())
                    return ;
                if (iterator(_p.find(*pos)) != end())
                {
                    _n--;
                    _p.deleteNode(pos->first);
                }
            }
            void erase(iterator first, iterator last, typename ft::enable_if<!is_integral<iterator>::value>::type* = NULL)
            {
                if (!_p.getRoot())
                    return ;
                iterator it = first;
				iterator	tmp;
				size_type	difference = 0;
				for (; it != last; it++)
					difference++;
                it = first;
				for (size_type i = 0; i < difference; i++)
				{
					tmp = it;
					if (i != difference - 1)
						it++;
                    if (iterator(_p.find(*tmp)) != end())
                    {
                        _n--;
                        _p.deleteNode(tmp->first);
                    }
					if (i != difference - 1)
						it = iterator(_p.find(*it));
				}
            }
            size_type erase(const Key& key)
            {
                if (!_p.getRoot())
                    return 0;
                size_type exists = find(key) != end();
                if (iterator(_p.find(Leaf< Key, T >(key, T()))) != end())
                {
                    _n--;
                    _p.deleteNode(key);
                }
                return exists;
            }
            void swap(map& x)
            {
                size_type tmpN = x._n;
                allocator_type tmpA = x._alloc;
                x._n = _n;
                x._alloc = _alloc;
                _n = tmpN;
                _alloc = tmpA;
                _p.swap(&_p, &x._p);
            }
            size_type count(const Key& key) const
            {
                if (find(key) != end())
                    return TRUE;
                return FALSE;
            }
            iterator find(const Key& key)
            {
                return iterator(_p.find(Leaf< Key, T >(key, T())));
            }	
            const_iterator find(const Key& key) const
            {
                return const_iterator(_p.find(Leaf< Key, T >(key, T())));
            }
            pair< iterator,iterator > equal_range(const Key& key)
            {
                return pair< iterator, iterator >(lower_bound(key), upper_bound(key));
            }
            pair< const_iterator,const_iterator > equal_range(const Key& key) const
            {
                return pair< const_iterator, const_iterator >(lower_bound(key), upper_bound(key));
            }
            iterator lower_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (!_key_compare(it->first, key))
                        return it;
                    it++;
                }
                return it;
            }
            const_iterator lower_bound(const Key& key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while (it != ite)
                {
                    if (!_key_compare(it->first, key))
                        return it;
                    it++;
                }
                return it;
            }
            iterator upper_bound(const Key& key)
            {
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (_key_compare(key, it->first))
                        return it;
                    it++;
                }
                return it;
            }
            const_iterator upper_bound(const Key& key) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while (it != ite)
                {
                    if (_key_compare(key, it->first))
                        return it;
                    it++;
                }
                return it;
            }
            void print()
            {
                _p.prettyPrint();
            }
        //template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::RBTree<const Key, T> > >
    };

    template< class Key, class T, class Compare, class Alloc >
    bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return FALSE;
        for (typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin(), it2 = rhs.begin(); it != lhs.end(); it++, it2++)
		{
            if (it.base()->first != it2.base()->first || it.base()->second != it2.base()->second)
				return FALSE;
        }
        return TRUE;
    }	
    template< class Key, class T, class Compare, class Alloc >
    bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
	template< class Key, class T, class Compare, class Alloc >
    bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return ((lhs == rhs || lhs < rhs));
    }
	template< class Key, class T, class Compare, class Alloc >
    bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return (!(lhs <= rhs));
    }
    template< class Key, class T, class Compare, class Alloc >
    bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }
}

#endif
