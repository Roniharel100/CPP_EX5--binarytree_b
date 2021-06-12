#include <iostream>
#include <vector>
using namespace std;

namespace ariel
{
    template <typename T>
    class BinaryTree
    {
    private:
        class Node
        {
        public:
            T data;
            Node *right;
            Node *left;
            Node(T val) : data(val), right(nullptr), left(nullptr) {}
        };
        Node *root;

    public:
        class iterator
        {
        private:
            unsigned int temp;
            vector<Node *> vec;

        public:
            void inorder(Node *node)
            {
                if (node != nullptr)
                {
                    inorder(node->left);
                    vec.push_back(node);
                    inorder(node->right);
                }
            }

            void preorder(Node *node)
            {
                if (node != nullptr)
                {
                    vec.push_back(node);
                    preorder(node->left);
                    preorder(node->right);
                }
            }

            void postorder(Node *node)
            {
                if (node != nullptr)
                {
                    postorder(node->left);
                    postorder(node->right);
                    vec.push_back(node);
                }
            }

            iterator(Node *root = nullptr, int c = 0)
            {
                if (root != nullptr)
                {
                    switch (c)
                    {
                    case 0:
                        inorder(root);
                        break;
                    case 1:
                        preorder(root);
                        break;
                    case 2:
                        postorder(root);
                        break;
                    default:
                        inorder(root);
                        break;
                    }
                }
                temp = 0;
            }

            T *operator->() const { return &(vec.at(temp)->data); }
            T &operator*() const { return vec.at(temp)->data; }

            iterator &operator++()
            {
                ++temp;
                if (vec.size() == temp)
                {
                    vec.clear();
                }
                return *this;
            }

            iterator operator++(int)
            {
                iterator tmp = *this;
                temp++;
                if (vec.size() == temp)
                {
                    vec.clear();
                }
                return tmp;
            }

            bool operator==(const iterator &v) const { return (vec == v.vec); }
            bool operator!=(const iterator &v) const { return (vec != v.vec); }

            Node *get_node() { return vec.at(temp); }
        };

        //--------------------------------------------------------------------------------------------------------

        BinaryTree() : root(nullptr) {}
        ~BinaryTree() { delete root; }

        void copy(Node *src, Node *dest)
        {
            if (dest->left != nullptr)
            {
                src->left = new Node(dest->left->data);
                copy(src->left, dest->left);
            }
            if (dest->right != nullptr)
            {
                src->right = new Node(dest->right->data);
                copy(src->right, dest->right);
            }
        }

        //--------------------------------------------------------------------------------------------------------

        BinaryTree(BinaryTree &n)
        {
            root = new Node(n.root->data);
            copy(root, n.root);
        }

        BinaryTree &operator=(BinaryTree n)
        {
            delete root;
            root = new Node(n.root->data);
            copy(root, n.root);
            return *this;
        }

        BinaryTree(BinaryTree &&n) noexcept
        {
            root = n.root;
            n.root = nullptr;
        }

        BinaryTree &operator=(BinaryTree &&n) noexcept
        {
            root = n.root;
            n.root = nullptr;
        }

        //--------------------------------------------------------------------------------------------------------

        BinaryTree &add_root(T r)
        {
            if (root == nullptr)
            {
                root = new Node(r);
                return *this;
            }
            root->data = r;
            return *this;
        }

        BinaryTree &add_right(T a, T b)
        {
            Node *n = nullptr;
            for (iterator it = begin(); it != end(); ++it)
            {
                if (*it == a)
                {
                    n = it.get_node();
                    if (!n->right)
                    {
                        n->right = new Node{b};
                    }
                    else
                    {
                        n->right->data = b;
                    }
                    return *this;
                }
            }
            throw std::invalid_argument("error!");
        }

        BinaryTree &add_left(T a, T b)
        {
            Node *n = nullptr;
            for (iterator it = begin(); it != end(); ++it)
            {
                if (*it == a)
                {
                    n = it.get_node();
                    if (!n->left)
                    {
                        n->left = new Node{b};
                    }
                    else
                    {
                        n->left->data = b;
                    }
                    return *this;
                }
            }
            throw std::invalid_argument("error!");
        }

        //--------------------------------------------------------------------------------------------------------

        iterator begin() { return iterator(root); }
        iterator end() { return iterator(); }
        iterator begin_preorder() { return iterator(root, 1); }
        iterator end_preorder() { return iterator(); }
        iterator begin_inorder() { return iterator(root, 0); }
        iterator end_inorder() { return iterator(); }
        iterator begin_postorder() { return iterator(root, 2); }
        iterator end_postorder() { return iterator(); }

        friend ostream &operator<<(ostream &os, BinaryTree &t)
        {
            return os;
        }
    };
}
