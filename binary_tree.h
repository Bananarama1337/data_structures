template<typename T>
struct TreeNode {
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    T data;

    TreeNode(const T& value = T()) : data(value) {};
};

template<typename T>
class binary_tree {
    TreeNode<T> root = nullptr;

public:
    binary_tree();
    binary_tree(const binary_tree& other);
    binary_tree(binary_tree&& other);
    binary_tree& operator=(const binary_tree& other);
    binary_tree& operator=(binary_tree&& other);
    binary_tree();

    ~binary_tree() {
        clear(root);
    }

    void clear(TreeNode<T>* node) noexcept {
        if (!node) {
            return;
        }

        clear(node->right);
        clear(node->left);
        delete node;
    }
};
