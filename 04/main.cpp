#include <iostream>

template<typename T>
class Set {
    struct Node {
        T value;
        Node *left;
        Node *right;
        Node *parent;

        Node(T value = T{} , Node* parent_ = nullptr, Node*  right_ = nullptr, Node* left_ = nullptr) : value(value), left(left_), right(right_), parent(parent_) {}
    };

    Node *root{};
    size_t size_{};

    void insert(const T &value, Node* current){

        if(value <  current->value){
            if(current->left == nullptr){
                current->left = new Node(value, current, nullptr ,nullptr);
                size_++;
                return;
            }
            insert(value, current->left);
        }
        else if(value == current->value){
            return;
        }
        else{
            if(current->right == nullptr){
                current->right = new Node(value, current);
                size_++;
                return;
            }
            insert(value, current->right);
        }
    }
    void print_inorder(const Node * current){
        if(current->left != nullptr)
            print_inorder(current->left);

        std::cout<<current->value<<" ";

        if(current-> right != nullptr)
            print_inorder(current->right);

    }

public:
    class iterator {
        Node *current;
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        iterator():current(nullptr){}
        iterator(Node *node):current(node){}
        reference operator*() const{
            return current->value;
        }

        pointer operator->() const{
            return &current->value;
        }

        iterator &operator++(){
            if (current->right) {
                current = current->right;
                while (current->left)
                    current = current->left;
                return *this;
            }

            else if (current->parent && current->parent->value > current->value) {
                current = current->parent;
                return *this;
            }

            else {
                while (current->parent && current->parent->value < current->value) {
                    current = current->parent;
                }

                if(current->parent && current->parent->value > current->value)
                    current = current->parent;

                return *this;
            }
        }

        iterator operator++(int){
            auto temp = current;

            if (current->right) {
                current = current->right;
                while (current->left)
                    current = current->left;
                return iterator(temp);
            }
            else if(current->parent->value > current->value){
                current = current->parent;
                return iterator(temp);
            }
            else{
                while(current->parent && current->parent->value < current->value){
                    current = current->parent;
                }

                if(current->parent->value > current->value)
                    current = current->parent;
                return iterator(temp);
            }
        }

        friend bool operator==(iterator lhs, iterator rhs){
           return  lhs.current == rhs.current;
        }
        friend bool operator!=(iterator lhs, iterator rhs){
            return !(lhs == rhs);
        }
    };

    iterator begin(){
        if(!size_)
            return end();

        auto x = root;
        while(x->left != nullptr)
            x = x->left;

        return x;
    }

    iterator end(){
//        auto x = root;
//        while (x!= nullptr)
//            x = x->right;
//
//        return x;
       return nullptr;
    }

    iterator find(const T &value){
        if(size_==0)
            return end();

        auto x = root;
        while(true){
            if(value == x->value) {
                return iterator(x);
            }
            if(x->left) {
                if (value <= x->left->value) {
                    x = x->left;
                    continue;
                }
            }
            if(x-> right){
                if(value >= x->right->value){
                    x = x-> left;
                    continue;
                }
            }
            break;
        }
        return end();
    }


    void insert(const T &value){
        if(root == nullptr){
            root = new Node(value);
            size_++;
            return;
        }

        insert(value ,root);
    }

    void print_inorder(){
        print_inorder(root);
    }
    void erase(iterator pos);
    ~Set(){

    }
};

int main() {
    Set<int> st;
    st.insert(10);
    st.insert(-10);
    st.insert(20);
    st.insert(10);
    st.insert(0);

//    for (auto x : st) {
//        std::cout << x << ' ';
//    } // Output: -10 0 10 20
//    std::cout << std::endl;

    auto it = st.find(10);
    std::cout << *it << std::endl; // Output: 10

   // assert(st.find(-20) == st.end());
}