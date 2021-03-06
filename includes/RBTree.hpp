#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <memory>
#include "Iter.hpp"

namespace ft
{
    template< class T1, class T2 >
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;
        first_type first;
        second_type second;
        pair() : first(first_type()), second(second_type()) {}
        pair( const T1& x, const T2& y ) : first(x), second(y) {}
        template<class U, class V>
        pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
        pair& operator=(const pair& pr) { first = pr.first; second = pr.second; return *this; }
    };
    template <typename _T1, typename _T2>
	inline pair<_T1, _T2> make_pair(_T1 x, _T2 y)
	{ return pair<_T1, _T2>(x, y); }

    template< class Key, class T >
    struct Leaf
    {
        Key first;
        T second;
        Leaf< Key, T > *parent; // pointer to the parent
        Leaf< Key, T > *left; // pointer to left child
        Leaf< Key, T > *right;
        int color; // 1 -> Red, 0 -> Black
        typedef Leaf< Key, T > value_type;
        typedef std::ptrdiff_t difference_type;
        typedef Leaf< Key, T >* pointer;
        typedef Leaf< Key, T >& reference;
        typedef bidirectional_iterator_tag iterator_category;

        Leaf() : first(Key()), second(T()), parent(NULL), left(NULL), right(NULL), color(0) {}
        Leaf(Leaf const & rhs) : first(rhs.first), second(rhs.second), parent(NULL), left(NULL), right(NULL), color(0) {}
        Leaf( Key const & key, T const & val ) : first(key), second(val), parent(NULL), left(NULL), right(NULL), color(0) {}
        Leaf & operator=(Leaf const & rhs) { first = rhs.first; second = rhs.second; parent = NULL; left = NULL; right = NULL; color = 0; return *this; }
        virtual ~Leaf() {}
        Leaf< Key, T > make_leaf(Key const & key, T const & val)
        {
            return Leaf< Key, T >(key, val);
        }
        operator     Leaf<const Key, T>()
        {
            Leaf<const Key, T> leaf(first, second);
            leaf->parent = reinterpret_cast<Leaf<const Key, T> *>(parent);
            leaf->left = reinterpret_cast<Leaf<const Key, T> *>(left);
            leaf->right = reinterpret_cast<Leaf<const Key, T> *>(right);
            leaf->color = color;
            return (leaf);
        }
    };
    template< class Key, class T, class Compare, class alloc = std::allocator<Leaf< Key, T > > >
    class RBTree
    {
        public:
        typedef Compare                                         key_compare;
        template< typename U >
            class value_compare: public std::binary_function<U,U,bool> {
                friend class RBTree;
                protected:
                    Compare comp;

                public:
                    typedef	bool result_type;
                    typedef U	first_argument_type;
                    typedef U	second_argument_type;
                    value_compare	(Compare c): comp(c) {};
                    bool	operator() (const U &x, const U &y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
        private:

            // initializes the nodes with appropirate values
            // all the pointers are set to point to the null pointer
            void initializeNode(Leaf< Key, T > *node)
            {
                node->first = key_type();
                node->second = mapped_type();
                node->parent = NULL;
                node->left = NULL;
                node->right = NULL;
                node->color = 0;
            }
        protected:
            typedef Key key_type;
            typedef T mapped_type;
            key_compare _key_compare;
            value_compare< Leaf< Key, T > > _value_compare;
            pair< Key, T > _pair_type;
            Leaf< Key, T > *root;
            Leaf< Key, T > *last;
            Leaf< Key, T > *begin;
        public:
            typedef Leaf< Key, T >* NodePtr;

            RBTree() : _key_compare(key_compare()), _value_compare(_key_compare), root(NULL), last(NULL), begin(NULL) {}
            RBTree(key_compare comp) : _key_compare(comp), _value_compare(_key_compare), root(NULL), last(NULL), begin(NULL) {}
            RBTree(RBTree const & rhs) : _key_compare(rhs._key_compare), _value_compare(rhs._value_compare), root(NULL), last(NULL), begin(NULL) {}
            RBTree & operator=(RBTree const & rhs) { _key_compare = rhs._key_compare; _value_compare = rhs._value_compare; root = NULL; last = NULL; begin = NULL; return *this; }
            virtual ~RBTree() {}
            void swap(RBTree< Key, T, Compare, alloc > *x, RBTree< Key, T, Compare, alloc > *y)
            {
                RBTree< Key, T, Compare, alloc >* tmp = y;
                y = x;
                x = tmp;
                NodePtr tmpRoot = x->root;
                NodePtr tmpLast = x->last;
                NodePtr tmpBegin = x->begin;
                x->root = root;
                x->last = last;
                x->begin = begin;
                root = tmpRoot;
                last = tmpLast;
                begin = tmpBegin;
            }
            NodePtr find(Leaf< Key, T> const & toFind) const
            {
                NodePtr fromRoot = root;
                while (fromRoot)
                {
                    if (fromRoot == last || fromRoot == begin)
                        return last;
                    if (_value_compare(toFind, *fromRoot))
                        fromRoot = fromRoot->left;
                    else if (!_value_compare(toFind, *fromRoot) && toFind.first != fromRoot->first)
                        fromRoot = fromRoot->right;
                    else
                        return fromRoot;
                }
                return last;
            }
            NodePtr findMinimum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->left && origin->left != begin)
                    origin = origin->left;
                return origin;
            }
            NodePtr findMaximum(NodePtr node) const
            {
                NodePtr origin = node;
                while (origin->right && origin->right != last)
                    origin = origin->right;
                return origin;
            }
            void leftRotate(NodePtr x)
            {
                NodePtr y = x->right;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr leftY = y->left;
                NodePtr parentX = x->parent;

                x->right = leftY;
                if (y->left)
                    y->left->parent = x;
                y->parent = parentX;
                if (!parentX)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                root->color = 0;
                y->left =  tmpX;
                x->parent = tmpY;
            }
            void rightRotate(NodePtr x)
            {
                NodePtr y = x->left;
                NodePtr tmpY = y;
                NodePtr tmpX = x;
                //NodePtr rightX = x->right;
                //NodePtr rightY = y->right;
                NodePtr rightY = y->right;
                NodePtr parentX = x->parent;

                x->left = rightY;
                if (y->right)
                    y->right->parent = x;
                y->parent = parentX;
                if (!parentX)
                    root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
                root->color = 0;
                y->right =  tmpX;
                x->parent = tmpY;
            }
            size_t countNodesLeft(NodePtr min)
            {
                NodePtr limit = root;
                size_t count = 0;
                
                while (min != limit)
                {
                    if (min && min->right)
                    {
                        min = min->right;
                        count++;
                        while (min->left && min != limit)
                        {
                            min = min->left;
                            count++;
                        }
                    }
                    else if (min)
                    {
                        while (min->parent && min == min->parent->right && min != limit)
                        {
                            min = min->parent;
                            count++;
                        }
                        if (min != limit)
                        {
                            min = min->parent;
                            count++;
                        }
                    }
                }
                return count;
            }
            size_t countNodesRight(NodePtr max)
            {
                NodePtr limit = root;
                size_t count = 0;

                while (max != limit)
                {
                    if (max && max->left)
                        {
                            max = max->left;
                            count++;
                            while (max->right && max != limit)
                            {
                                max = max->right;
                                count++;
                            }
                        }
                    else if (max)
                    {
                        while (max->parent && max == max->parent->left && max != limit)
                        {
                            max = max->parent;
                            count++;
                        }
                        if (max != limit)
                        {
                            max = max->parent;
                            count++;
                        }
                    }
                }
                return count;
            }
            void insert(Leaf< Key, T > const &toInsert)
            {
                NodePtr node;
                node = alloc().allocate(1);
                alloc().construct(node, Leaf< Key, T >(key_type(), mapped_type()));
                initializeNode(node);
                node->second = toInsert.second;
                node->first = toInsert.first;
                node->color = 1; // new node must be red
                
                NodePtr fromRoot = root;
                NodePtr parentNode = NULL;
                NodePtr child = NULL;
                int rotate = 0;
                initializeNode(last);
                initializeNode(begin);
                if (root)
                {
                    while (root->left && countNodesRight(findMaximum(root)) < countNodesLeft(findMinimum(root)))
                    {
                        rightRotate(root);
                    }
                    while (root->right && countNodesRight(findMaximum(root)) > countNodesLeft(findMinimum(root)))
                    {
                        leftRotate(root);
                    }
                }
                while (fromRoot && fromRoot != last && fromRoot != begin)
                {
                    parentNode = fromRoot;
                    if (_value_compare(*node, *fromRoot))
                        fromRoot = fromRoot->left;
                    else if (!_value_compare(*node, *fromRoot) && node->first != fromRoot->first)
                        fromRoot = fromRoot->right;
                    else
                        return ;
                    if (fromRoot)
                    {
                        child = fromRoot;
                        child->parent = parentNode;
                    }
                }
                if (!parentNode)
                {
                    root = node;
                    root->right = last;
                    root->left = begin;
                    last->parent = root;
                    begin->parent = root;
                    node->color = 0;
                    return ;
                }
                if (parentNode && parentNode->parent)
                    {
                        if (!parentNode->parent->left)
                            rotate--;
                        if (!parentNode->parent->right)
                            rotate++;
                    }
                    if (rotate < 0)
                    {
                        leftRotate(parentNode->parent);
                        leftRotate(parentNode->parent);
                    }
                    if (rotate > 0)
                    {
                        rightRotate(parentNode->parent);
                        rightRotate(parentNode->parent);
                    }
                    fromRoot = root;
                    while (fromRoot && fromRoot != last && fromRoot != begin)
                    {
                        parentNode = fromRoot;
                        if (_value_compare(*node, *fromRoot))
                            fromRoot = fromRoot->left;
                        else if (!_value_compare(*node, *fromRoot) && node->first != fromRoot->first)
                            fromRoot = fromRoot->right;
                        else
                            return ;
                        if (fromRoot)
                        {
                            child = fromRoot;
                            child->parent = parentNode;
                        }
                    }
                node->parent = parentNode;
                if (_value_compare(*node, *parentNode))
                {
                    parentNode->left = node;
                }
                else if (!_value_compare(*node, *parentNode) && node->first != parentNode->first)
                {
                    parentNode->right = node;
                }
                NodePtr max = findMaximum(root);
                max->right = last;
                last->parent = max;
                NodePtr min = findMinimum(root);
                min->left = begin;
                begin->parent = min;
                if (node->parent)
                    recolor(root);
            }
            NodePtr getRoot() const
            {
                return root;
            }
            NodePtr getLast() const
            {
                return last;
            }
            NodePtr getBegin() const
            {
                return begin;
            }
            void setLast(NodePtr node)
            {
                last = node;
            }
            void setBegin(NodePtr node)
            {
                begin = node;
            }
            void recolor (NodePtr node)
            {
                if (node != NULL)
                {
                    if (node->left && node->left->color)
                    {
                        if (node->left->right)
                            node->left->right->color = 0;
                        if (node->left->left)
                            node->left->left->color = 0;
                    }
                    if (node->right && node->right->color)
                    {
                        if (node->right->right)
                            node->right->right->color = 0;
                        if (node->right->left)
                            node->right->left->color = 0;
                    }
                    recolor(node->left);
                    recolor(node->right);
                }
                if (root->right)
                    root->right->color = 0;
                if (root->left)
                    root->left->color = 0;
            }
            int isDeletable(NodePtr found)
            {
                if (found->left && found->right && found->right != last && (!found->left->left || found->left->left == begin) && !found->left->right && !found->right->left && (found->right->right == last || !found->right->right))
                {
                    if (found == found->parent->right)
                    {
                        found->parent->right = found->left;
                        found->left->parent = found->parent;
                        found->parent->right->right = found->right;
                        found->right->parent = found->left;
                        initializeNode(found);
                        alloc().destroy(found);
                        alloc().deallocate(found, 1);
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        NodePtr min = findMinimum(root);
                        min->left = begin;
                        begin->parent = min;
                    }
                    else
                    {
                        found->parent->left = found->right;
                        found->right->parent = found->parent;
                        found->parent->left->left = found->left;
                        found->left->parent = found->right;
                        initializeNode(found);
                        alloc().destroy(found);
                        alloc().deallocate(found, 1);
                        NodePtr max = findMaximum(root);
                        max->right = last;
                        last->parent = max;
                        NodePtr min = findMinimum(root);
                        min->left = begin;
                        begin->parent = min;
                    }
                    return 1;
                }
                return 0;
            }
            int isRoot(NodePtr found)
            {
                if (found == root)
                {
                    while (found == root && found->right != last)
                    {
                        leftRotate(root);
                    }
                    if (found == root && found->right == last && found->left && found->left != begin)
                    {
                        root = found->left;
                        found->left->parent = NULL;
                        initializeNode(found);
                        initializeNode(last);
                        initializeNode(begin);
                        alloc().destroy(found);
                        alloc().deallocate(found, 1);
                        root->right = last;
                        last->parent = root;
                        root->left = begin;
                        begin->parent = root;
                        return 1;
                    }
                    if (found == root && found->right == last && (!found->left || found->left == begin))
                    {
                        initializeNode(found);
                        initializeNode(last);
                        initializeNode(root);
                        initializeNode(begin);
                        alloc().destroy(found);
                        alloc().deallocate(found, 1);
                        last->parent = NULL;
                        begin->parent = NULL;
                        root = NULL;
                        return 1;
                    }
                }
                return 0;
            }
            void deleteNode(Key value)
            {
                NodePtr found = NULL;
                NodePtr node = getRoot();
                while (node && node != last && node != begin)
                {
                    if (node->first == value)
                    {
                        found = node;
                    }
                    if (!_value_compare(Leaf< Key, T >(value, T()), *node) && value != node->first)
                    {
                        node = node->right;
                    }
                    else
                        node = node->left;
                }
                if (!found)
                {
                    return;
                }
                if (isRoot(found) || isDeletable(found))
                    return ;
                if (found == found->parent->left)
                {
                    while (found->right && found->right != last && found->left && found->left != begin)
                    {
                        if (isRoot(found) || isDeletable(found))
                            return ;
                        rightRotate(found);
                    }
                    if (isRoot(found) || isDeletable(found))
                            return ;
                    if (found == found->parent->right)
                        found->parent->right = (found->left && found->left != begin) ? found->left : found->right;
                    else
                        found->parent->left = (found->left && found->left != begin) ? found->left : found->right;
                }
                else
                {
                    while (found->right && found->right != last && found->left && found->left != begin)
                    {
                        if (isRoot(found) || isDeletable(found))
                            return ;
                        leftRotate(found);
                    }
                    if (isRoot(found) || isDeletable(found))
                            return ;
                    if (found == found->parent->right)
                        found->parent->right = (found->left && found->left != begin) ? found->left : found->right;
                    else
                        found->parent->left = (found->left && found->left != begin) ? found->left : found->right;
                }
                if (found->left && found->left != begin)
                    found->left->parent = found->parent;
                if (found->right && found->right != last)
                    found->right->parent = found->parent;
                initializeNode(found);
                alloc().destroy(found);
                alloc().deallocate(found, 1);
                NodePtr max = findMaximum(root);
                max->right = last;
                last->parent = max;
                NodePtr min = findMinimum(root);
                min->left = begin;
                begin->parent = min;
                
            }
            // void printHelper(NodePtr root, std::string indent, bool last) const
            // {
                // print the tree structure on the screen
            //     if (root != NULL)
            //     {
            //         std::cout<<indent;
            //         if (last)
            //         {
            //             std::cout<<"R----";
            //             indent += "     ";
            //         }
            //         else
            //         {
            //             std::cout<<"L----";
            //             indent += "|    ";
            //         }
            //         std::string sColor = root->color?"RED":"BLACK";
            //         std::cout<<root->first<<"("<<sColor<<")"<<std::endl;
            //         printHelper(root->left, indent, false);
            //         printHelper(root->right, indent, true);
            //     }
            // }
            // void prettyPrint() const
            // {
            //     if (root)
            //         printHelper(this->root, "", true);
	        // }
            // If a node is red, both of its children are black. This means no two nodes on a path can be red nodes.
            // Every path from a root node to a NULL node has the same number of black nodes.
    };
    template< class T1, class T2 >
    bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return lhs.first == rhs.first && lhs.second == lhs.second;
    }
    template< class T1, class T2 >
    bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return !(lhs == rhs);
    }
    template< class T1, class T2 >
    bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        if (lhs.first < rhs.first)
            return 1;
        if (rhs.first < lhs.first)
            return 0;
        if (lhs.second < rhs.second)
            return 1;
        return 0; 
    }
    template< class T1, class T2 >
    bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return !(rhs < lhs);
    }
    template< class T1, class T2 >
    bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return rhs < lhs;
    }
    template< class T1, class T2 >
    bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
    {
        return !(lhs < rhs);
    }

    template< class T1, class T2 >
    bool operator==( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return lhs.first == rhs.first && lhs.second == lhs.second;
    }
    template< class T1, class T2 >
    bool operator!=( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return !(lhs == rhs);
    }
    template< class T1, class T2 >
    bool operator<( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        if (lhs.first < rhs.first)
            return 1;
        if (rhs.first < lhs.first)
            return 0;
        if (lhs.second < rhs.second)
            return 1;
        return 0; 
    }
    template< class T1, class T2 >
    bool operator<=( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return !(rhs < lhs);
    }
    template< class T1, class T2 >
    bool operator>( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return rhs < lhs;
    }
    template< class T1, class T2 >
    bool operator>=( const ft::Leaf<T1,T2>& lhs, const ft::Leaf<T1,T2>& rhs )
    {
        return !(lhs < rhs);
    }
}

//https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/

#endif

/*T current = _it;

                if (_it->right && !_it->right->right)
                {
                    current = _it->parent;
                    while (current && current->first < _it->first)
                        current = current->parent;
                    _it = current;
                }
                else
                {
                    current = _it->right;
                    if (current->right && !current->right->right)
                        _it = current;
                    else
                    {
                        while (current->left && current->left->right && current->left->right->right)
                            current = current->left;
                    }
                    _it = current;
                }
                return _it;*/