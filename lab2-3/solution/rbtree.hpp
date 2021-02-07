#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <utility>

template <typename Key, typename Value>
class TRedBlackTree {
public:
    TRedBlackTree();
    ~TRedBlackTree();
    TRedBlackTree(const TRedBlackTree&) = default;

    TRedBlackTree& operator=(TRedBlackTree&&);

    bool Insert(const Key& key, const Value& value);
    bool Remove(const Key& key);
    Value* Search(const Key& key);
    
    static TRedBlackTree<Key, Value> Load(const char* path);
    static void Save(const char* path, const TRedBlackTree<Key, Value>& tree);

    void PrintTree() {
        PrintTree(root);
    }

private:
    struct TNode;

    void PrintTree(const TNode* node) {
        if(node == nullptr)
            return;
        std::cout << "Вершина: " << node->key << " Цвет: " << node->isBlack << "\n";
        if(node->left)
            std::cout << "l:  ";
        PrintTree(node->left);
        if(node->right)
            std::cout << "r:  ";
        PrintTree(node->right);
        std::cout << "^\n";
    }

    TNode** SearchTNode(const Key& key, TNode** parent);
    void InsertFixup(TNode* node);
    void RemoveFixup(TNode* node, TNode* father);
    void LeftRotate(TNode* parent);
    void RightRotate(TNode* parent);

private:
    TNode *root;
};

template <typename Key, typename Value>
TRedBlackTree<Key, Value> TRedBlackTree<Key, Value>::Load(const char* path) {
    std::ifstream ifs(path);
    if(!ifs) {
        throw std::runtime_error(std::strerror(errno));
    }
    
    TRedBlackTree tree;

    enum {
        FROM_PARENT,        // Пришли из родителя
        FROM_LEFT_SON,      // Пришли из левого сына 
        FROM_RIGHT_SON,     // Пришли из правого сына
    } origin = FROM_PARENT;

    auto restorePtr = [](TNode* node, TNode* parent) {
        node->parent = parent;
        if(node->left != nullptr)
            node->left = new TNode();
        if(node->right != nullptr)
            node->right = new TNode();
    };

    tree.root = new TNode();
    TNode* currNode = tree.root;
    TNode* prevNode = nullptr;


    while (currNode != nullptr) {
        TNode* currNodeTemp = currNode;
        switch (origin) {
        case FROM_PARENT:
            // Считываем вершину из файла
            ifs.read(reinterpret_cast<char*>(currNode), sizeof(*currNode));
            if(!ifs) {
                if(ifs.eof()) {
                    if(prevNode == nullptr) {
                        tree = std::move(TRedBlackTree());
                        return tree;
                    }
                    throw std::runtime_error("broken file");
                }
                else if(ifs.bad())
                    throw std::runtime_error("something terrible happened");
                else if(ifs.fail())
                    throw std::runtime_error("something not very terrible happened");
            }

            restorePtr(currNode, prevNode);

            // Переходим в левого сына
            if(currNode->left != nullptr) {
                currNode = currNode->left;
            }
            else {
                origin = FROM_LEFT_SON;
            }
            break;

        case FROM_LEFT_SON:
            // Переходим в правого сына
            if(currNode->right != nullptr) {
                origin = FROM_PARENT;
                currNode = currNode->right;
            }
            else {
                origin = FROM_RIGHT_SON;
            } 
            break;
        
        case FROM_RIGHT_SON:
            // Переходим в родителя
            if(currNode->parent)
                origin = (currNode == currNode->parent->left) ? FROM_LEFT_SON : FROM_RIGHT_SON;
            currNode = currNode->parent;
            break;
        }
        prevNode = currNodeTemp;
    }
    ifs.close();
    return tree;
}

template <typename Key, typename Value>
void TRedBlackTree<Key, Value>::Save(const char* path, const TRedBlackTree<Key, Value>& tree) {
    std::ofstream ofs(path, std::ofstream::out | std::ofstream::binary);
    if(!ofs) {
        throw std::runtime_error(std::strerror(errno));
    }

    enum {
        FROM_PARENT,        // Пришли из родителя
        FROM_LEFT_SON,      // Пришли из левого сына 
        FROM_RIGHT_SON,     // Пришли из правого сына
    } origin = FROM_PARENT;
    TNode* currNode = tree.root;
    while (currNode != nullptr) {
        switch (origin) {
        case FROM_PARENT:
            // Добавляем вершину в файл
            ofs.write(reinterpret_cast<char*>(currNode), sizeof(*currNode));

            // Переходим в левого сына
            if(currNode->left != nullptr) {
                currNode = currNode->left;
            }
            else {
                origin = FROM_LEFT_SON;
            }
            break;

        case FROM_LEFT_SON:
            // Переходим в правого сына
            if(currNode->right != nullptr) {
                origin = FROM_PARENT;
                currNode = currNode->right;
            }
            else {
                origin = FROM_RIGHT_SON;
            } 
            break;
        
        case FROM_RIGHT_SON:
            // Переходим в родителя
            if(currNode->parent)
                origin = (currNode == currNode->parent->left) ? FROM_LEFT_SON : FROM_RIGHT_SON;
            currNode = currNode->parent;
            break;
        }
    }
}


template <typename Key, typename Value>
struct TRedBlackTree<Key, Value>::TNode {
    TNode* parent;
    TNode* left;
    TNode* right;
    bool isBlack;

    Key key;
    Value value;

    TNode() = default;
    TNode(const Key& key, const Value& value);
    ~TNode();
};

template <typename Key, typename Value>
TRedBlackTree<Key, Value>::TNode::TNode(const Key& key, const Value& value) 
    : parent{nullptr}, left{nullptr}, right{nullptr}, 
    isBlack{false}, key{key}, value{value}
{}

template <typename Key, typename Value>
TRedBlackTree<Key, Value>::TNode::~TNode() {
    delete left;
    delete right;
}

template <typename Key, typename Value>
TRedBlackTree<Key, Value>::TRedBlackTree()
    : root{nullptr}
{}

template <typename Key, typename Value>
TRedBlackTree<Key, Value>::~TRedBlackTree() {
    delete root;
    root = nullptr;
}

template <typename Key, typename Value>
TRedBlackTree<Key, Value>& TRedBlackTree<Key, Value>::operator=(TRedBlackTree&& tree) {
    this->~TRedBlackTree();
    root = tree.root;
    tree.root = nullptr;
    return *this;
}


template <typename Key, typename Value>
bool TRedBlackTree<Key, Value>::Insert(const Key& key, const Value& value) {
    // Поиск места
    TNode* parent = nullptr;
    TNode** foundEl = SearchTNode(key, &parent);
    // Проверка на существование элемента
    if(*foundEl != nullptr)
        return false;

    // Добавление Ноды
    TNode* newNode = new TNode();
    newNode->key = key;
    newNode->value = value;
    newNode->parent = parent;
    *foundEl = newNode;
    // Восстановление дерева
    InsertFixup(*foundEl);

    return true;
}

template <typename Key, typename Value>
void TRedBlackTree<Key, Value>::InsertFixup(TNode* node) {
    if(node == root) {
        node->isBlack = true;
        return;
    }
    
    // Пока отец красный
    while(node->parent != nullptr && node->parent->isBlack == false) {
        TNode* parent = node->parent;
        TNode* grandParent = parent->parent;
        // Если отец левый ребенок
        if(grandParent->left == parent) {
            TNode* uncle = grandParent->right;
            
            // Если дядя красный
            if (uncle != nullptr && uncle->isBlack == false) {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandParent->isBlack = false;
                node = grandParent;
            }
            // Если дядя черный
            else {
                if (parent->right == node) {
                    LeftRotate(parent);
                    // Теперь указатель на parent и указатель на node нужно поменять местами
                    TNode* temp = node;
                    node = parent;
                    parent = temp;
                }
                parent->isBlack = true;
                grandParent->isBlack = false;
                RightRotate(grandParent);
            }
        }
        // Если отец правый ребенок
        else {
            TNode* uncle = grandParent->left;

            // Если дядя красный 
            if (uncle != nullptr && uncle->isBlack == false) {
                parent->isBlack = true;
                uncle->isBlack = true;
                grandParent->isBlack = false;
                node = grandParent;
            }
            // Если дядя черный
            else {
                if (parent->left == node) {
                    RightRotate(parent);
                    // Теперь указатель на parent и указатель на node нужно поменять местами
                    TNode* temp = node;
                    node = parent;
                    parent = temp;
                }
                parent->isBlack = true;
                grandParent->isBlack = false;
                LeftRotate(grandParent);
            }
        }
    }

    root->isBlack = true;
}

template <typename Key, typename Value>
bool TRedBlackTree<Key, Value>::Remove(const Key& key) {
    // Поиск элемента
    TNode** foundEl = SearchTNode(key, nullptr);
    // Если элемент не был найден
    if (*foundEl == nullptr)
        return false;

    // Удаление элемента
    TNode* deletedNode = *foundEl;
    //Если у вершины нет детей
    if (deletedNode->left == nullptr && deletedNode->right == nullptr) {
        // Исключаем вершину из дерева
        *foundEl = nullptr;
    }
    //Если один ребенок
    else if (deletedNode->left != nullptr && deletedNode->right == nullptr) {
        *foundEl = deletedNode->left;
        deletedNode->left->parent = deletedNode->parent;
    }
    else if (deletedNode->left == nullptr && deletedNode->right != nullptr) {
        *foundEl = deletedNode->right;
        deletedNode->right->parent = deletedNode->parent;
    }
    //Если два ребенка
    else  {
        //Ищем следующий элемент
        TNode* next = deletedNode->right;
        while(next->left != nullptr) {
            next = next->left;
        }

        deletedNode->key = std::move(next->key);
        deletedNode->value = std::move(next->value);

        // Теперь мы удалеям элемент next
        foundEl = (next->parent->left == next) ? &next->parent->left : &next->parent->right;
        deletedNode = next;

        //Исключаем найденный элемент
        *foundEl = deletedNode->right;
        if(deletedNode->right != nullptr) {
            deletedNode->right->parent = deletedNode->parent;
        }
    }

    // Восстановление дерева
    if(deletedNode->isBlack == true) {
        if(*foundEl == nullptr)
            RemoveFixup(nullptr, deletedNode->parent);
        else
            RemoveFixup(*foundEl, deletedNode->parent);
    }

    deletedNode->left = nullptr;
    deletedNode->right = nullptr;
    delete deletedNode;

    return true;
}
template <typename Key, typename Value>
void TRedBlackTree<Key, Value>::RemoveFixup(TNode* node, TNode* parent) {
    while (node != root) {
        if(node != nullptr && node->isBlack == false) {
            node->isBlack = true;
            break;
        }

        if(parent->left == node) {
            // Если брат красный
            if (parent->right->isBlack == false) {
                parent->right->isBlack = true;
                parent->isBlack = false;
                LeftRotate(parent);
            }

            // Если оба сына брата черные
            if ((parent->right->left == nullptr || parent->right->left->isBlack)
             && (parent->right->right == nullptr || parent->right->right->isBlack)) {
                parent->right->isBlack = false;
                // Рассматриваем отца
                node = parent;
                parent = parent->parent;
                continue;
            }
            // Если левый сын брата красный, а правый -- черный
            if ((parent->right->left != nullptr && parent->right->left->isBlack == false)
                && (parent->right->right == nullptr || parent->right->right->isBlack)) {
                parent->right->isBlack = false;
                parent->right->left->isBlack = true;
                RightRotate(parent->right);
            }
            // Если правый сын брата красный
            if (parent->right->right != nullptr && parent->right->right->isBlack == false) {
                parent->right->right->isBlack = true;
                parent->right->isBlack = parent->isBlack;
                parent->isBlack = true;
                LeftRotate(parent);
                break;
            }
        }
        else {
            // Если брат красный
            if (parent->left->isBlack == false) {
                parent->left->isBlack = true;
                parent->isBlack = false;
                RightRotate(parent);
            }

            // Если оба сына брата черные
            if ((parent->left->right == nullptr || parent->left->right->isBlack)
             && (parent->left->left == nullptr || parent->left->left->isBlack)) {
                parent->left->isBlack = false;
                // Рассматриваем отца
                node = parent;
                parent = parent->parent;
                continue;
            }
            // Если правый сын брата красный, а левый -- черный
            if ((parent->left->right != nullptr && parent->left->right->isBlack == false)
                && (parent->left->left == nullptr || parent->left->left->isBlack)) {
                parent->left->isBlack = false;
                parent->left->right->isBlack = true;
                LeftRotate(parent->left);
            }
            // Если левый сын брата красный
            if (parent->left->left != nullptr && parent->left->left->isBlack == false) {
                parent->left->left->isBlack = true;
                parent->left->isBlack = parent->isBlack;
                parent->isBlack = true;
                RightRotate(parent);
                break;
            }
        }
    }

    if(root) {
        root->isBlack = true;
    }
}

template <typename Key, typename Value>
void TRedBlackTree<Key, Value>::LeftRotate(TNode* parent) {
    // Устанавливаем связи у дедушки
    if(parent->parent) {
        TNode* grandParent = parent->parent;
        if(grandParent->left == parent) {
            grandParent->left = parent->right;   
        }
        else {
            grandParent->right = parent->right;
        }
    }
    
    // Устанавливаем связи для правого ребенка
    TNode* child = parent->right;
    child->parent = parent->parent;
    
    TNode* midNode = child->left;   // узел посередине;
    child->left = parent;

    // Устанавливаем связи для родителя
    parent->parent = child;
    parent->right = midNode;

    // Меняем родителя у узла посередине
    if(midNode != nullptr)
        midNode->parent = parent;

    // Если родитель был корнем, то нужно обновить корень
    if(parent == root)
        root = child;
}

template <typename Key, typename Value>
void TRedBlackTree<Key, Value>::RightRotate(TNode* parent) {
    // Устанавливаем связи у дедушки
    if(parent->parent) {
        TNode* grandParent = parent->parent;
        if(grandParent->left == parent) {
            grandParent->left = parent->left;   
        }
        else {
            grandParent->right = parent->left;
        }
    }
    
    // Устанавливаем связи для левого ребенка
    TNode* child = parent->left;
    child->parent = parent->parent;
    
    TNode* midNode = child->right;   // узел посередине;
    child->right = parent;

    // Устанавливаем связи для родителя
    parent->parent = child;
    parent->left = midNode;

    // Меняем родителя у узла посередине
    if(midNode != nullptr)
        midNode->parent = parent;

    // Если родитель был корнем, то нужно обновить корень
    if(parent == root)
        root = child;
}

template <typename Key, typename Value>
typename TRedBlackTree<Key, Value>::TNode** TRedBlackTree<Key, Value>::SearchTNode(const Key& key, TRedBlackTree<Key, Value>::TNode** parent) {
    TNode* foundEl = root;
    TNode* par = nullptr;
    while (foundEl != nullptr && foundEl->key != key) {
        par = foundEl;
        if(key < par->key)
            foundEl = par->left;
        else
            foundEl = par->right;
    }

    // Если мы указали переменную для отца, то записываем туда отца найденной вершины
    if (parent != nullptr)
        *parent = par;
    // Если искомым элементом является корень
    if (par == nullptr)
        return &root;
    // Иначе возвращаем указатель на указатель найденной ноды
    else
        return (key < par->key) ? &par->left : &par->right; 
}

template <typename Key, typename Value>
Value* TRedBlackTree<Key, Value>::Search(const Key& key) {
    TNode** foundEl = SearchTNode(key, nullptr);
    return (*foundEl == nullptr) ? nullptr : &(*foundEl)->value;
}