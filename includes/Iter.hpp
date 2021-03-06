#ifndef ITER_H
#define ITER_H

#include <iostream>

namespace ft
{
    struct input_interator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag {};
    struct bidirectional_iterator_tag {};
    struct random_access_iterator_tag {};

    template < class Iter >
    struct iterator_traits {
        typedef typename Iter::difference_type		difference_type;
        typedef typename Iter::value_type			value_type;
        typedef typename Iter::pointer				pointer;
        typedef typename Iter::reference			reference;
        typedef typename Iter::iterator_category	iterator_category;
    };

    template < class T >
    struct iterator_traits<T*> {
        typedef std::ptrdiff_t					difference_type;
        typedef T								value_type;
        typedef T *								pointer;
        typedef T &								reference;
        typedef random_access_iterator_tag	iterator_category;
    };

    template < class T >
    struct iterator_traits<T* const> {
        typedef std::ptrdiff_t					difference_type;
        typedef T								value_type;
        typedef const T *						pointer;
        typedef const T &						reference;
        typedef random_access_iterator_tag	iterator_category;
    };

    template< typename T >
    class iter
    {
        private:
            T _it;
        public:
            typedef typename iterator_traits<T>::value_type			value_type;
            typedef typename iterator_traits<T>::difference_type	difference_type;
            typedef typename iterator_traits<T>::pointer			pointer;
            typedef typename iterator_traits<T>::reference			reference;
            typedef typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const T			const_iterator_type;

            iter() : _it(T()) {}
            iter(iterator_type x) : _it(x) {}
            template< class U >
            iter(U const & other) : _it(&(*other)) {}
            template< class U >
            iter& operator=(U const & other) {_it = &(*other); return *this;}
            virtual ~iter() {}
            iter& operator++() {_it = _it + 1; return *this;}
            iter operator++(int) {iter retval = *this; ++(*this); return retval;}
            iter& operator--() {_it = _it - 1; return *this;}
            iter operator--(int) {iter retval = *this; --(*this); return retval;}
            iter& operator-=(difference_type n) {_it -= n; return *this;}
            iter operator-(difference_type n) const {return iter(_it - n);}
            iter& operator+=(difference_type n) {_it += n; return *this;}
            iter operator+(difference_type n) const {return iter(_it + n);}
            reference operator[](difference_type n) const {return *(_it + n);}
            pointer operator->() const {return &operator*();}
            reference operator*() const {return *_it;}
            iterator_type base() const {return _it;}

            operator iter<const_iterator_type>()
            {
                return (iter<const_iterator_type>(const_cast<const iterator_type>(_it)));
            }
    };
    template< typename T >
    class reviter
    {
        private:
            T _it;
        public:
            typedef	typename iterator_traits<T>::difference_type		difference_type;
            typedef	typename iterator_traits<T>::value_type			value_type;
            typedef	typename iterator_traits<T>::pointer				pointer;
            typedef	typename iterator_traits<T>::reference			reference;
            typedef	typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const T			const_iterator_type;
            reviter() : _it(T()) {}
            reviter(iterator_type x) : _it(x) {}
            template< class U >
            reviter(U const & other) : _it(other.base()) {}
            template< class U >
            reviter& operator=(U const & other) {_it = other.base(); return *this;}
            virtual ~reviter() {}
            reviter& operator++() {_it--; return *this;}
            reviter operator++(int) {reviter retval = *this; ++(*this); return retval;}
            reviter& operator--() {_it++; return *this;}
            reviter operator--(int) {reviter retval = *this; --(*this); return retval;}
            reviter& operator-=(difference_type n) {_it += n; return *this;}
            reviter operator-(difference_type n) const {return reviter(_it + n);}
            reviter& operator+=(difference_type n) {_it -= n; return *this;}
            reviter operator+(difference_type n) const {return reviter(_it - n);}
            reference operator[](difference_type n) const {return *(_it - n - 1);}
            pointer operator->() const {return &operator*();}
            reference operator*() const {T tmp(_it); return *--tmp;}
            iterator_type base() const {return _it;}

            operator reviter<iter<const_iterator_type> >()
            {
                return (reviter<iter<const_iterator_type> >(iter<const_iterator_type>(_it)));
            }
    };

    template< class Iter>
    iter<Iter> operator+( typename iter<Iter>::difference_type n, const iter<Iter>& it )
    {
        return iter<Iter>(it.base() + n);
    }
    template< class Iterator, class U >
    typename iter<Iterator>::difference_type operator-( const iter<Iterator>& lhs, const iter<U>& rhs )
    {
        return lhs.base() - rhs.base();
    }

    template< class Iter >
    reviter<Iter> operator+( typename reviter<Iter>::difference_type n, const reviter<Iter>& it )
    {
        return reviter<Iter>(it.base() - n);
    }
    template< class Iterator, class U >
    typename reviter<Iterator>::difference_type operator-( const reviter<Iterator>& lhs, const reviter<U>& rhs )
    {
        return rhs.base() - lhs.base();
    }

    template<typename Iterator1, typename Iterator2>
	bool			operator==(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(iter<Iterator1> const &lhs, iter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}

    template<typename Iterator1, typename Iterator2>
	bool			operator==(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) { return (lhs.base() == rhs.base()); }
    template<typename Iterator1, typename Iterator2>
    bool operator!=(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() != rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() < rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator>=(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() <= rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() > rhs.base());}
    template<typename Iterator1, typename Iterator2>
    bool operator<=(reviter<Iterator1> const &lhs, reviter<Iterator2> const &rhs) {return (lhs.base() >= rhs.base());}

    template< typename T >
    class biIter
    {
        private:
            T _it;
        public:
            typedef typename iterator_traits<T>::value_type			value_type;
            typedef typename iterator_traits<T>::difference_type	difference_type;
            typedef typename iterator_traits<T>::pointer			pointer;
            typedef typename iterator_traits<T>::reference			reference;
            typedef typename iterator_traits<T>::iterator_category	iterator_category;
            typedef T iterator_type;
            typedef const T			const_iterator_type;

            biIter() : _it(T()) {}
            biIter(iterator_type x) : _it(x) {}
            template< class U >
            biIter(U const & other) : _it(&(*other)) {}
            template< class U >
            biIter& operator=(U const & other) {_it = &(*other); return *this;}
            virtual ~biIter() {}
            bool operator==(biIter const &rhs) const { return (_it == rhs._it);}
		    bool operator!=(biIter const &rhs) const { return (!(_it == rhs._it));}
            biIter& operator++()
            {
                if (_it && _it->right)
                {
                    _it = _it->right;
                    while (_it->left)
                        _it = _it->left;
                }
                else if (_it)
                {
                    // std::cout << "++" << std::endl;
                    while (_it->parent && _it == _it->parent->right)
                    {
                        // std::cout << "it parent right" << std::endl;
                        _it = _it->parent;
                    }
                    // if (_it->parent)
                    // std::cout << "it parent = " << _it->parent->first << std::endl;
                    _it = _it->parent;
                }
                return *this;
            }
            biIter operator++(int)
            {
                T tmp = _it;
                
                if (_it && _it->right)
                {
                    _it = _it->right;
                    while (_it->left)
                        _it = _it->left;
                }
                else if (_it)
                {
                    // std::cout << "++" << std::endl;
                    while (_it->parent && _it == _it->parent->right)
                    {
                        // std::cout << "it parent right" << std::endl;
                        _it = _it->parent;
                    }
                    // if (_it->parent)
                    // std::cout << "it parent = " << _it->parent->first << std::endl;
                    _it = _it->parent;
                }
                return tmp;
            }
            biIter& operator--()
            {
                if (_it && _it->left)
                    {
                        _it = _it->left;
                        while (_it->right)
                            _it = _it->right;
                    }
                else if (_it)
                {
                    while (_it->parent && _it == _it->parent->left)
                        _it = _it->parent;
                    _it = _it->parent;
                }
                return *this;
            }
            biIter operator--(int)
            {
                T tmp = _it;
                if (_it && _it->left)
                    {
                        _it = _it->left;
                        while (_it->right)
                            _it = _it->right;
                    }
                else if (_it)
                {
                    while (_it->parent && _it == _it->parent->left)
                        _it = _it->parent;
                    _it = _it->parent;
                }
                return tmp;
            }
            pointer operator->() const {return &operator*();}
            reference operator*() const {return *_it;}
            iterator_type base() const {return _it;}

            operator biIter<const_iterator_type>()
            {
                return (biIter<const_iterator_type>(const_cast<const iterator_type>(_it)));
            }
    };
    template<typename Iterator>
    class biReviter
    {
        public:
            typedef Iterator                                                        iterator_type;
            typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;
            typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
            typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
            typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
            typedef typename ft::iterator_traits<iterator_type>::reference			reference;
        private:
            iterator_type															_it;
            template<typename _Tp>
            static _Tp* Get_Deference(_Tp *_x) { return _x; }
            
            template<typename _Tp>
            static pointer Get_Deference(_Tp _x) { return _x.operator->(); }
        public:
            
            biReviter() : _it() {};
            explicit biReviter(iterator_type x) : _it(x) {};
            biReviter(const biReviter & x) : _it(x.base()) {};

            template<typename Iter>
            biReviter(const biReviter<Iter> & x) : _it(x.base()) {}

            virtual ~biReviter() {};
            

            iterator_type base() const { return _it; };
            
            
            biReviter operator+(difference_type n) const { return biReviter(_it - n); }
            biReviter operator++() { --_it; return (*this); }
            biReviter operator++(int) { biReviter tmp = *this; --_it; return tmp; }
            biReviter & operator+=(difference_type n) { _it -= n; return *this; }
            

            
            biReviter operator-(difference_type n) const { return biReviter(_it + n); }
            biReviter & operator--() { ++_it; return (*this); }
            biReviter operator--(int) { biReviter tmp = (*this); ++_it; return tmp; }
            biReviter & operator-=(difference_type n) { _it += n; return *this; }
            

            
            reference operator*() const { Iterator tmp = _it; return (*--tmp); }
            pointer operator->() const { Iterator tmp = _it; --tmp; return Get_Deference(tmp); }
            reference operator[](difference_type n) const { return *(*this + n); }
            
        };

        /**
        * 	Non-member function overloads
        */
        
            
            template<typename Iterator>
            inline bool operator==(const biReviter<Iterator> & lhs, const biReviter<Iterator> & rhs)
            { return lhs.base() == rhs.base(); }

            template<typename Iterator>
            inline bool operator!=(const biReviter<Iterator> & lhs, const biReviter<Iterator> & rhs)
            { return !(lhs == rhs); }

            template<typename Iterator>
            inline bool operator<(const biReviter<Iterator> & lhs, const biReviter<Iterator> & rhs)
            { return rhs.base() < lhs.base(); }

            template<typename Iterator>
            inline bool operator<=(const biReviter<Iterator> & lhs, const biReviter<Iterator> & rhs)
            { return !(rhs < lhs); }

            template<typename Iterator>
            inline bool operator>(const biReviter<Iterator> & lhs, const biReviter<Iterator> & rhs)
            { return rhs < lhs; }

            template<typename Iterator>
            inline bool operator>=(const biReviter<Iterator> & lhs, const biReviter<Iterator> & rhs)
            { return !(lhs < rhs); }
            
            
            template<typename IteratorLeft, typename IteratorRight>
            inline bool operator==(const biReviter<IteratorLeft> & lhs, const biReviter<IteratorRight> & rhs)
            { return lhs.base() == rhs.base(); }

            template<typename IteratorLeft, typename IteratorRight>
            inline bool operator<(const biReviter<IteratorLeft> & lhs, const biReviter<IteratorRight> & rhs)
            { return lhs.base() > rhs.base(); }

            template<typename IteratorLeft, typename IteratorRight>
            inline bool operator!=(const biReviter<IteratorLeft> & lhs, const biReviter<IteratorRight> & rhs)
            { return lhs.base() != rhs.base(); }

            template<typename IteratorLeft, typename IteratorRight>
            inline bool operator>(const biReviter<IteratorLeft> & lhs, const biReviter<IteratorRight> & rhs)
            { return lhs.base() < rhs.base(); }

            template<typename IteratorLeft, typename IteratorRight>
            inline bool operator<=(const biReviter<IteratorLeft> & lhs, const biReviter<IteratorRight> & rhs)
            { return lhs.base() >= rhs.base(); }

            template<typename IteratorLeft, typename IteratorRight>
            inline bool operator>=(const biReviter<IteratorLeft> & lhs, const biReviter<IteratorRight> & rhs)
            { return lhs.base() <= rhs.base(); }
            
        

        
        template<typename Iterator>
        inline typename biReviter<Iterator>::difference_type operator-(const biReviter<Iterator>& lhs, const biReviter<Iterator>& rhs)
        { return rhs.base() - lhs.base(); }

        template<typename IteratorLeft, typename IteratorRight>
        inline typename biReviter<IteratorLeft>::difference_type operator-(const biReviter<IteratorLeft>& lhs, const biReviter<IteratorRight>& rhs)
        { return rhs.base() - lhs.base(); }

        template<typename Iterator>
        inline biReviter<Iterator> operator+(typename biReviter<Iterator>::difference_type diff, const biReviter<Iterator>& lhs)
        { return biReviter<Iterator>(lhs.base() - diff); }
        
}

#endif