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
private:
    TreeNode<T>* root_ = nullptr;

    TreeNode<T>* insert_rec(TreeNode<T>* node, const T& value);
    TreeNode<T>* find_rec(TreeNode<T>* node, const T& value) const;
    TreeNode<T>* remove_rec(TreeNode<T>* node, const T& value);
    TreeNode<T>* find_min(TreeNode<T>* node) const;
    void preorder_rec(TreeNode<T>* node, std::vector<T>&) const;
    void postorder_rec(TreeNode<T>* node, std::vector<T>&) const;
    void inorder_rec(TreeNode<T>* node, std::vector<T>& result) const;
    TreeNode<T>* copy_rec(TreeNode<T>* node) const;
    
    template<typename U>
    friend void print(binary_tree<U>& tree);

    template<typename U>
    friend void print_rec(TreeNode<U>* node, std::size_t depth);

public:
    binary_tree(const T& value = T()) {
        root_ = new TreeNode<T>(value);
    }

    binary_tree(const binary_tree& other);
    binary_tree(binary_tree&& other) noexcept;
    binary_tree& operator=(const binary_tree& other);
    binary_tree& operator=(binary_tree&& other) noexcept;

    ~binary_tree() {
        clear(root_);
    }

    void clear(TreeNode<T>* node) noexcept;
    void insert(const T& value);
    void remove(const T& value);
    TreeNode<T>* find(const T& value);

    std::vector<T> preorder_traversal() const;
    std::vector<T> postorder_traversal() const;
    std::vector<T> inorder_traversal() const;
};

template<typename T>
binary_tree<T>::binary_tree(const binary_tree& other) {
    root_ = copy_rec(other.root_);
}

template<typename T>
TreeNode<T>* binary_tree<T>::copy_rec(TreeNode<T>* node) const {
    if (!node) return nullptr;

    TreeNode<T>* newNode = new TreeNode<T>(node->data);
    newNode->left  = copy_rec(node->left);
    newNode->right = copy_rec(node->right);

    return newNode;
}

template<typename T>
binary_tree<T>::binary_tree(binary_tree&& other) noexcept {
    root_ = other.root_;
    other.root_ = nullptr;
}

template<typename T>
binary_tree<T>& binary_tree<T>::operator=(const binary_tree& other) {
    if (this == &other) {
        return *this;
    }

    clear(root_);
    root_ = copy_rec();

    return *this;
}

template<typename T>
binary_tree<T>& binary_tree<T>::operator=(binary_tree&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    clear(root_);
    root_ = other.root_;
    other.root_ = nullptr;

    return *this;
}

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
    root_ = insert_rec(root_, value);
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
    TreeNode<T>* node = remove_rec(root_, value);
}

template<typename T>
TreeNode<T>* binary_tree<T>::remove_rec(TreeNode<T>* node, const T& value) {
    if (!node) return nullptr;

    if (value < node->data) {
        node->left = remove_rec(node->left, value);
    } 
    else if (value > node->data) {
        node->right = remove_rec(node->right, value);
    } 
    else {
        if (!node->left && !node->right) {
            // случай 1: лист
            delete node;
            return nullptr;
        } 
        else if (!node->left) {
            // случай 2: только правый потомок
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        } 
        else if (!node->right) {
            // случай 2: только левый потомок
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        } 
        else {
            // случай 3: два потомка
            TreeNode<T>* successor = find_min(node->right);
            node->data = successor->data;
            node->right = remove_rec(node->right, successor->data);
        }
    }

    return node;
}

template<typename T>
TreeNode<T>* binary_tree<T>::find_min(TreeNode<T>* node) const {
    while (node && node->left) node = node->left;
    return node;
}

template<typename T>
TreeNode<T>* binary_tree<T>::find(const T& value) {
    return find_rec(root_, value);
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
std::vector<T> binary_tree<T>::preorder_traversal() const {
    std::vector<T> result;
    preorder_rec(root_, result);

    return result;
}

template<typename T>
void binary_tree<T>::preorder_rec(TreeNode<T>* node, std::vector<T>& result) const {
    if (!node) { 
        return; 
    }

    result.push_back(node->data);

    preorder_rec(node->left, result);
    preorder_rec(node->right, result);
}

template<typename T>
std::vector<T> binary_tree<T>::postorder_traversal() const {
    std::vector<T> result;
    postorder_rec(root_, result);

    return result;
}

template<typename T>
void binary_tree<T>::postorder_rec(TreeNode<T>* node, std::vector<T>& result) const {
    if (!node) { 
        return; 
    }

    postorder_rec(node->left, result);
    postorder_rec(node->right, result);

    result.push_back(node->data);
}

template<typename T>
std::vector<T> binary_tree<T>::inorder_traversal() const {
    std::vector<T> result;
    inorder_rec(root_, result);

    return result;
}

template<typename T>
void binary_tree<T>::inorder_rec(TreeNode<T>* node, std::vector<T>& result) const {
    if (!node) { 
        return; 
    }

    inorder_rec(node->left, result);

    result.push_back(node->data);

    inorder_rec(node->right, result);
}

template<typename T>
void print(binary_tree<T>& tree) {
    print_rec(tree.root_, 0);
}

template<typename T>
void print_rec(TreeNode<T>* node, std::size_t depth) {
    if (!node) return;

    print_rec(node->right, depth + 1);

    for (int i = 0; i < depth; i++) std::cout << "    ";
        std::cout << node->data << "\n";

    print_rec(node->left, depth + 1);
}