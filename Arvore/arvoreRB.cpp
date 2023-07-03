#include <iostream>
#include <chrono>

enum class Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k, Color c = Color::RED)
        : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (node->parent == nullptr)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (node->parent == nullptr)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    void insertFixup(Node* node) {
        while (node != root && node->parent->color == Color::RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                if (uncle != nullptr && uncle->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;

                if (uncle != nullptr && uncle->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    leftRotate(node->parent->parent);
                }
            }
        }

        root->color = Color::BLACK;
    }

    Node* insertHelper(Node* root, Node* newNode) {
        if (root == nullptr)
            return newNode;

        if (newNode->key < root->key) {
            root->left = insertHelper(root->left, newNode);
            root->left->parent = root;
        } else if (newNode->key > root->key) {
            root->right = insertHelper(root->right, newNode);
            root->right->parent = root;
        }

        return root;
    }

    Node* searchHelper(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (key < root->key)
            return searchHelper(root->left, key);

        return searchHelper(root->right, key);
    }

    void inorderTraversalHelper(Node* root) {
        if (root != nullptr) {
            inorderTraversalHelper(root->left);
            std::cout << root->key << " ";
            inorderTraversalHelper(root->right);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int key) {
        Node* newNode = new Node(key);
        newNode->color = Color::RED;

        root = insertHelper(root, newNode);

        insertFixup(newNode);
    }

    Node* search(int key) {
        auto startTime = std::chrono::high_resolution_clock::now();
        Node* result = searchHelper(root, key);
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
        std::cout << "Tempo de busca na Arvore: " << duration.count() << " nanossegundos" << std::endl;

        return result;
    }

    void inorderTraversal() {
        inorderTraversalHelper(root);
        std::cout << std::endl;
    }
};

// int main() {
//     RedBlackTree tree;
//     auto startTime = std::chrono::high_resolution_clock::now();

//     // Inserindo valores de 1 a 100 na árvore
//     for (int i = 1; i <= 100000; i++) {
//         tree.insert(i);
//     }

//     //tree.insert(-1);
//     std::cout << "Elementos da Árvore: " <<std::endl;
//     tree.inorderTraversal();

//     Node* result = tree.search(614);
//     auto endTime = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
//     std::cout << "Tempo total: " << duration.count() << " segundos" << std::endl;

//     if (result != nullptr)
//         std::cout << "Valor encontrado na árvore binária rubro-negra: " << result->key << std::endl;
//     else
//         std::cout << "Valor não encontrado na árvore binária rubro-negra." << std::endl;

//     return 0;
// }