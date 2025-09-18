#include <iostream>

template<typename T>
struct TreeNode {
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    T data;

    TreeNode(const T& value = T()) : data(value) {};
};

template<typename T>
class binary_tree {
    TreeNode<T>* root = nullptr;

    TreeNode<T>* insert_rec(TreeNode<T>* node, const T& value);
    TreeNode<T>* find_rec(TreeNode<T>* node, const T& value) const;
    
    template<typename U>
    friend void print(binary_tree<U>& tree);

    template<typename U>
    friend void print_rec(TreeNode<U>* node, std::size_t depth);
public:
    binary_tree(const T& value = T()) {
        root = new TreeNode<T>(value);
    };

    binary_tree(const binary_tree& other);
    binary_tree(binary_tree&& other);
    binary_tree& operator=(const binary_tree& other);
    binary_tree& operator=(binary_tree&& other);

    ~binary_tree() {
        clear(root);
    }

    void clear(TreeNode<T>* node) noexcept;
    void insert(const T& value);
    void remove(const T& value);
    TreeNode<T>* find(const T& value);
};

template<typename T>
void binary_tree<T>::clear(TreeNode<T>* node) noexcept {
    if (!node) {
        return;
    }

    clear(node->right);
    clear(node->left);
    delete node;
}

template<typename T>
void binary_tree<T>::insert(const T& value) {
    root = insert_rec(root, value);
}

template<typename T>
TreeNode<T>* binary_tree<T>::insert_rec(TreeNode<T>* node, const T& value) {
    if (!node) {
        return new TreeNode<T>(value);
    }

    if (value < node->data) {
        node->left = insert_rec(node->left, value);
    } 
    else if (value > node->data) {
        node->right = insert_rec(node->right, value);
    }

    return node;
}

template<typename T>
void binary_tree<T>::remove(const T& value) {
    TreeNode<T>* node = find(value);
    if (!node) {
        return;
    }

    return;
}

template<typename T>
TreeNode<T>* binary_tree<T>::find(const T& value) {
    return find_rec(root, value);
}

template<typename T>
TreeNode<T>* binary_tree<T>::find_rec(TreeNode<T>* node, const T& value) const {
    if (!node) { 
        return nullptr; 
    }
    
    if (value < node->data) {
        return find_rec(node->left, value);
    } 
    else if (value > node->data) {
        return find_rec(node->right, value);
    }

    return node;
}

template<typename T>
void print(binary_tree<T>& tree) {
    print_rec(tree.root, 0);
}

template<typename T>
void print_rec(TreeNode<T>* node, std::size_t depth) {
    if (!node) return;

    print_rec(node->right, depth + 1);

    for (int i = 0; i < depth; i++) std::cout << "    ";
        std::cout << node->data << "\n";

    print_rec(node->left, depth + 1);
}