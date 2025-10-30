#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

class TreeNode {
public:
    int key; //Ключ узла
    TreeNode* left; //Указатель на левого потомка  
    TreeNode* right; //Указатель на правого потомка
    
    TreeNode(int k) : key(k), left(nullptr), right(nullptr) {
        cout << key << endl;
    }
    
    ~TreeNode() {
        cout << key << endl;
    }
};

//дерево поиска
class BinarySearchTree {
private:
    TreeNode* root; //Корень дерева
    
    //с визуализацией процесса
    TreeNode* insertRecursive(TreeNode* node, int key, int depth = 0) {
        //отступы для визуализации глубины рекурсии
        string indent(depth * 2, ' ');
        cout << indent << "Рекурсия на глубине " << depth;
        
        //если узел пустой, создаем новый
        if (node == nullptr) {
            cout << " - создаем новый узел для ключа " << key << endl;
            return new TreeNode(key);
        }
        
        cout << " - сравниваем " << key << " с текущим узлом " << node->key << endl;
        
        // рекурсивно вставляем в левое или правое поддерево
        if (key < node->key) {
            cout << indent << "Идем влево где ключ меньше" << endl;
            node->left = insertRecursive(node->left, key, depth + 1);
        } else if (key > node->key) {
            cout << indent << "Идем вправо где ключ больше" << endl;
            node->right = insertRecursive(node->right, key, depth + 1);
        } else {
            cout << indent << "Ключ уже существует - не добавляем дубликат" << endl;
        }
        
        return node;
    }
    
    // Рекурсивное удаление всех узлов поддерева (для деструктора)
    void destroyTree(TreeNode* node) {
        if (node != nullptr) {
            destroyTree(node->left);   // Удаляем левое поддерево
            destroyTree(node->right);  // Удаляем правое поддерево
            delete node;               // Удаляем текущий узел
        }
    }
    
    // Поиск узла с минимальным ключом в поддереве с визуализацией пути
    TreeNode* findMinNode(TreeNode* node, bool showPath = false) const {
        if (node == nullptr) {
            if (showPath) cout << "Поддерево пустое" << endl;
            return nullptr;
        }
        
        if (showPath) {
            cout << "Начинаем поиск минимума с узла " << node->key << endl;
        }
        
        // В BST минимальный элемент находится в самом левом узле
        while (node->left != nullptr) {
            if (showPath) {
                cout << "Переходим влево: " << node->key << " -> " << node->left->key << endl;
            }
            node = node->left;
        }
        
        if (showPath) {
            cout << "Найден минимальный элемент: " << node->key << endl;
        }
        
        return node;
    }
    
    TreeNode* findMaxNode(TreeNode* node, bool showPath = false) const {
        if (node == nullptr) {
            if (showPath) cout << "Поддерево пустое" << endl;
            return nullptr;
        }
        
        if (showPath) {
            cout << "Начинаем поиск максимума с узла " << node->key << endl;
        }
        
        while (node->right != nullptr) {
            if (showPath) {
                cout << "Переходим вправо: " << node->key << " -> " << node->right->key << endl;
            }
            node = node->right;
        }
        
        if (showPath) {
            cout << "Найден максимальный элемент: " << node->key << endl;
        }
        
        return node;
    }
    
    int calculateHeight(TreeNode* node, bool showCalculation = false, int depth = 0) const {
        string indent(depth * 2, ' ');
        
        // пустое дерево имеет высоту -1
        if (node == nullptr) {
            if (showCalculation) {
                cout << indent << "Пустой узел - высота = -1" << endl;
            }
            return -1;
        }
        
        if (showCalculation) {
            cout << indent << "Вычисляем высоту для узла " << node->key << endl;
        }
        
        // Рекурсивно находим высоту левого и правого поддеревьев
        int leftHeight = calculateHeight(node->left, showCalculation, depth + 1);
        int rightHeight = calculateHeight(node->right, showCalculation, depth + 1);
        
        // Высота узла = 1 + максимальная высота поддеревьев
        int nodeHeight = 1 + max(leftHeight, rightHeight);
        
        if (showCalculation) {
            cout << indent << "Узел " << node->key << ": левая высота=" 
                      << leftHeight << ", правая высота=" << rightHeight 
                      << ", итоговая высота=" << nodeHeight << endl;
        }
        
        return nodeHeight;
    }
    
    // Поиск узла по ключу с демонстрацией пути поиска
    TreeNode* searchNode(TreeNode* node, int key, bool showPath = false) const {
        if (showPath && node != nullptr) {
            cout << "Проверяем узел " << node->key;
        }
        
        // Базовые случаи: узел не найден или найден нужный ключ
        if (node == nullptr) {
            if (showPath) cout << " - узел не найден" << endl;
            return node;
        }
        
        if (node->key == key) {
            if (showPath) cout << " - найден искомый ключ!" << endl;
            return node;
        }
        
        // Рекурсивно ищем в левом или правом поддереве
        if (key < node->key) {
            if (showPath) cout << " - идем влево (искомый ключ меньше)" << endl;
            return searchNode(node->left, key, showPath);
        } else {
            if (showPath) cout << " - идем вправо (искомый ключ больше)" << endl;
            return searchNode(node->right, key, showPath);
        }
    }
    
    // Симметричный обход дерева (in-order traversal)
    void inorderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            inorderTraversal(node->left);   // Обходим левое поддерево
            cout << node->key << " ";  // Обрабатываем текущий узел
            inorderTraversal(node->right);  // Обходим правое поддерево
        }
    }
    
    // Подсчет количества узлов в поддереве
    int countNodes(TreeNode* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
    
    // Вспомогательная функция для красивого ASCII-представления дерева
    void printTreeStructure(TreeNode* node, const string& prefix, bool isLeft, bool isRoot = false) const {
        if (node == nullptr) {
            return;
        }

        // Выводим правое поддерево сверху
        if (node->right != nullptr) {
            printTreeStructure(node->right, prefix + (isRoot ? "" : (isLeft ? "│   " : "    ")), false);
        }

        // Выводим текущий узел
        cout << prefix;
        if (isRoot) {
            cout << node->key << " (корень)" << endl;
        } else {
            cout << (isLeft ? "└── " : "┌── ") << node->key << endl;
        }

        // Выводим левое поддерево снизу
        if (node->left != nullptr) {
            printTreeStructure(node->left, prefix + (isRoot ? "" : (isLeft ? "    " : "│   ")), true);
        }
    }

public:
    // Конструктор по умолчанию - создает пустое дерево
    BinarySearchTree() : root(nullptr) {
        cout << "=== СОЗДАНИЕ ДЕРЕВА ===" << endl;
        cout << "Создано пустое бинарное дерево поиска" << endl;
        cout << "========================" << endl;
    }
    
    // Конструктор с начальным значением
    BinarySearchTree(int rootKey) {
        cout << "=== СОЗДАНИЕ ДЕРЕВА ===" << endl;
        cout << "Создаем дерево с корневым узлом: " << rootKey << endl;
        root = new TreeNode(rootKey);
        cout << "Бинарное дерево поиска успешно создано" << endl;
        cout << "========================" << endl;
    }
    
    // Деструктор - освобождает всю память, занятую деревом
    ~BinarySearchTree() {
        cout << "\n=== УНИЧТОЖЕНИЕ ДЕРЕВА ===" << endl;
        cout << "Вызван деструктор дерева. Начинаем удаление всех узлов..." << endl;
        destroyTree(root);
        cout << "Дерево полностью уничтожено" << endl;
        cout << "===========================" << endl;
    }
    
    // Публичный метод для вставки узла по ключу с полной визуализацией
    void insert(int key) {
        cout << "\n=== ВСТАВКА УЗЛА ===" << endl;
        cout << "Добавление узла с ключом: " << key << endl;
        cout << "Трассировка процесса вставки:" << endl;
        root = insertRecursive(root, key);
        cout << "Узел успешно добавлен!" << endl;
        cout << "===================" << endl;
        
        // Показываем текущую структуру дерева после вставки
        cout << "\nТекущая структура дерева:" << endl;
        printVisualTree();
    }
    
    // Поиск минимального ключа во всем дереве с демонстрацией
    int findMin() const {
        cout << "\n=== ПОИСК МИНИМУМА ===" << endl;
        TreeNode* minNode = findMinNode(root, true);
        if (minNode == nullptr) {
            cout << "======================" << endl;
            throw runtime_error("Дерево пустое - невозможно найти минимум");
        }
        cout << "======================" << endl;
        return minNode->key;
    }
    
    // Поиск максимального ключа во всем дереве с демонстрацией
    int findMax() const {
        cout << "\n=== ПОИСК МАКСИМУМА ===" << endl;
        TreeNode* maxNode = findMaxNode(root, true);
        if (maxNode == nullptr) {
            cout << "========================" << endl;
            throw runtime_error("Дерево пустое - невозможно найти максимум");
        }
        cout << "========================" << endl;
        return maxNode->key;
    }
    
    // Получение высоты дерева с детальным расчетом
    int getHeight() const {
        cout << "\n=== ВЫЧИСЛЕНИЕ ВЫСОТЫ ДЕРЕВА ===" << endl;
        int height = calculateHeight(root, true);
        cout << "Финальная высота дерева: " << height << endl;
        cout << "=================================" << endl;
        return height;
    }
    
    // Проверка, существует ли узел с заданным ключом
    bool contains(int key) const {
        cout << "\n=== ПОИСК УЗЛА ===" << endl;
        cout << "Поиск узла с ключом " << key << ":" << endl;
        bool found = searchNode(root, key, true) != nullptr;
        cout << "Результат поиска: " << (found ? "НАЙДЕН" : "НЕ НАЙДЕН") << endl;
        cout << "==================" << endl;
        return found;
    }
    
    // Вывод дерева в упорядоченном виде (симметричный обход)
    void printInOrder() const {
        cout << "\n=== СИММЕТРИЧНЫЙ ОБХОД ===" << endl;
        cout << "Содержимое дерева (в порядке возрастания): ";
        if (root == nullptr) {
            cout << "дерево пустое";
        } else {
            inorderTraversal(root);
        }
        cout << endl;
        cout << "==========================" << endl;
    }
    
    // Получение количества узлов в дереве
    int size() const {
        return countNodes(root);
    }
    
    // Проверка, является ли дерево пустым
    bool isEmpty() const {
        return root == nullptr;
    }
    
    // Поиск минимума в поддереве, начинающемся с узла с заданным ключом
    int findMinInSubtree(int subtreeRoot) const {
        cout << "\n=== ПОИСК МИНИМУМА В ПОДДЕРЕВЕ ===" << endl;
        cout << "Ищем минимум в поддереве с корнем " << subtreeRoot << endl;
        
        TreeNode* subtreeNode = searchNode(root, subtreeRoot, true);
        if (subtreeNode == nullptr) {
            cout << "===================================" << endl;
            throw runtime_error("Узел с ключом " + to_string(subtreeRoot) + " не найден");
        }
        
        cout << "Найден корень поддерева, начинаем поиск минимума:" << endl;
        TreeNode* minNode = findMinNode(subtreeNode, true);
        cout << "===================================" << endl;
        return minNode->key;
    }
    
    // Поиск максимума в поддереве, начинающемся с узла с заданным ключом
    int findMaxInSubtree(int subtreeRoot) const {
        cout << "\n=== ПОИСК МАКСИМУМА В ПОДДЕРЕВЕ ===" << endl;
        cout << "Ищем максимум в поддереве с корнем " << subtreeRoot << endl;
        
        TreeNode* subtreeNode = searchNode(root, subtreeRoot, true);
        if (subtreeNode == nullptr) {
            cout << "====================================" << endl;
            throw runtime_error("Узел с ключом " + to_string(subtreeRoot) + " не найден");
        }
        
        cout << "Найден корень поддерева, начинаем поиск максимума:" << endl;
        TreeNode* maxNode = findMaxNode(subtreeNode, true);
        cout << "====================================" << endl;
        return maxNode->key;
    }
    
    // Получение высоты поддерева, начинающегося с узла с заданным ключом
    int getSubtreeHeight(int subtreeRoot) const {
        cout << "\n=== ВЫЧИСЛЕНИЕ ВЫСОТЫ ПОДДЕРЕВА ===" << endl;
        cout << "Вычисляем высоту поддерева с корнем " << subtreeRoot << endl;
        
        TreeNode* subtreeNode = searchNode(root, subtreeRoot, true);
        if (subtreeNode == nullptr) {
            cout << "====================================" << endl;
            throw runtime_error("Узел с ключом " + to_string(subtreeRoot) + " не найден");
        }
        
        cout << "Найден корень поддерева, начинаем вычисление высоты:" << endl;
        int height = calculateHeight(subtreeNode, true);
        cout << "Высота поддерева с корнем " << subtreeRoot << ": " << height << endl;
        cout << "====================================" << endl;
        return height;
    }
    
    // Красивая визуализация структуры дерева
    void printVisualTree() const {
        cout << "\n=== ВИЗУАЛЬНАЯ СТРУКТУРА ДЕРЕВА ===" << endl;
        if (root == nullptr) {
            cout << "Дерево пустое" << endl;
        } else {
            cout << "Дерево (правое поддерево сверху, левое снизу):" << endl;
            printTreeStructure(root, "", false, true);
        }
        cout << "===================================" << endl;
    }
    
    // Вывод структуры дерева (обход в ширину) с пояснениями
    void printLevelOrder() const {
        cout << "\n=== ОБХОД ПО УРОВНЯМ ===" << endl;
        if (root == nullptr) {
            cout << "Дерево пустое" << endl;
            cout << "========================" << endl;
            return;
        }
        
        queue<TreeNode*> queue;
        queue.push(root);
        
        cout << "Структура дерева по уровням (обход в ширину):" << endl;
        int level = 0;
        
        while (!queue.empty()) {
            int levelSize = queue.size();
            cout << "Уровень " << level << " (глубина " << level << "): ";
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* current = queue.front();
                queue.pop();
                
                cout << current->key;
                if (i < levelSize - 1) cout << ", ";
                
                if (current->left) queue.push(current->left);
                if (current->right) queue.push(current->right);
            }
            
            cout << endl;
            level++;
        }
        cout << "========================" << endl;
    }
    
    // Анализ свойств дерева с подробной статистикой
    void analyzeTree() const {
        cout << "\n=== АНАЛИЗ ДЕРЕВА ===" << endl;
        
        if (isEmpty()) {
            cout << "Дерево пустое - нет данных для анализа" << endl;
            cout << "====================" << endl;
            return;
        }
        
        int treeSize = size();
        int treeHeight = calculateHeight(root);
        int minKey = findMinNode(root)->key;
        int maxKey = findMaxNode(root)->key;
        
        cout << "Основные характеристики дерева:" << endl;
        cout << "  Количество узлов: " << treeSize << endl;
        cout << "  Высота дерева: " << treeHeight << endl;
        cout << "  Минимальный ключ: " << minKey << endl;
        cout << "  Максимальный ключ: " << maxKey << endl;
        cout << "  Диапазон значений: " << (maxKey - minKey) << endl;
        
        // Оценка сбалансированности дерева
        double idealHeight = log2(treeSize);
        cout << "  Идеальная высота для " << treeSize << " узлов: " 
                  << fixed << setprecision(1) << idealHeight << endl;
        
        if (treeHeight <= idealHeight + 1) {
            cout << "  Оценка: Дерево хорошо сбалансировано" << endl;
        } else if (treeHeight <= idealHeight * 1.5) {
            cout << "  Оценка: Дерево умеренно сбалансировано" << endl;
        } else {
            cout << "  Оценка: Дерево плохо сбалансировано (вырождается в список)" << endl;
        }
        
        cout << "====================" << endl;
    }
};

// Демонстрационная функция для тестирования функциональности дерева
void demonstrateTreeOperations() {
    
    // Создаем дерево с начальным значением
    BinarySearchTree tree(50);
    
    // Показываем начальное состояние
    tree.printVisualTree();
    tree.analyzeTree();
    
    // Добавляем узлы в дерево с пошаговой демонстрацией
    vector<int> values = {30, 70, 20, 40, 60, 80, 10, 25, 35, 45};
    
    cout << "\n ПОШАГОВОЕ ДОБАВЛЕНИЕ УЗЛОВ:" << endl;
    for (int i = 0; i < values.size(); i++) {
        cout << "\n--- Добавляем узел " << (i + 1) << " из " << values.size() << " ---" << endl;
        tree.insert(values[i]);
        
        // Показываем промежуточный анализ для первых нескольких узлов
        if (i < 3) {
            tree.analyzeTree();
        }
        
        // Небольшая пауза для лучшего восприятия
        if (i < values.size() - 1) {
            cout << "\nНажмите Enter для продолжения...";
            cin.get();
        }
    }
    
    // Финальный анализ дерева
    cout << "\n ФИНАЛЬНОЕ СОСТОЯНИЕ ДЕРЕВА:" << endl;
    tree.printVisualTree();
    tree.analyzeTree();
    tree.printInOrder();
    tree.printLevelOrder();
    
    // Демонстрация операций поиска
    cout << "\n🔍 ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ ПОИСКА:" << endl;
    
    // Поиск минимума и максимума
    try {
        int minValue = tree.findMin();
        int maxValue = tree.findMax();
        cout << "\nГлобальные экстремумы найдены успешно!" << endl;
    } catch (const exception& e) {
        cout << "Ошибка при поиске экстремумов: " << e.what() << endl;
    }
    
    // Вычисление высоты дерева
    try {
        int height = tree.getHeight();
        cout << "\nВысота дерева вычислена успешно!" << endl;
    } catch (const exception& e) {
        cout << "Ошибка при вычислении высоты: " << e.what() << endl;
    }
    
    // Тестирование поиска узлов
    cout << "\n ТЕСТИРОВАНИЕ ПОИСКА КОНКРЕТНЫХ УЗЛОВ:" << endl;
    vector<int> searchKeys = {25, 55, 80, 100};
    for (int key : searchKeys) {
        tree.contains(key);
    }
    
    // Тестирование операций с поддеревьями
    cout << "\n ДЕМОНСТРАЦИЯ ОПЕРАЦИЙ С ПОДДЕРЕВЬЯМИ:" << endl;
    vector<int> subtreeRoots = {30, 70, 20};
    
    for (int subtreeRoot : subtreeRoots) {
        cout << "\n--- Анализ поддерева с корнем " << subtreeRoot << " ---" << endl;
        try {
            int minInSubtree = tree.findMinInSubtree(subtreeRoot);
            int maxInSubtree = tree.findMaxInSubtree(subtreeRoot);
            int subtreeHeight = tree.getSubtreeHeight(subtreeRoot);
            
            cout << "Результаты для поддерева " << subtreeRoot << ":" << endl;
            cout << "   Минимум: " << minInSubtree << endl;
            cout << "   Максимум: " << maxInSubtree << endl;
            cout << "   Высота: " << subtreeHeight << endl;
            
        } catch (const exception& e) {
            cout << "Ошибка при работе с поддеревом: " << e.what() << endl;
        }
    }
    
    cout << "\n  ВНИМАНИЕ: Дерево будет автоматически уничтожено при завершении функции..." << endl;
    cout << "Наблюдайте за процессом вызова деструкторов:" << endl;
}

// Главная функция программы
int main() {
    cout << "\n Эта программа демонстрирует:" << endl;
    cout << "• Создание и уничтожение узлов дерева (конструкторы/деструкторы)" << endl;
    cout << "• Добавление узлов по ключу с визуализацией процесса" << endl;
    cout << "• Поиск минимума и максимума в дереве и поддеревьях" << endl;
    cout << "• Вычисление высоты дерева с пошаговым объяснением" << endl;
    cout << "• Визуальное представление структуры дерева" << endl;
    cout << "• Анализ свойств и характеристик дерева" << endl;
    
    cout << "\n Нажмите Enter для начала демонстрации...";
    cin.get();
    
    try {
        // Запускаем полную демонстрацию с интерактивностью
        demonstrateTreeOperations();
        
    } catch (const exception& e) {
        cerr << "\n Произошла критическая ошибка: " << e.what() << endl;
        return 1;
    }
    
    cout << "\n Программа завершена успешно!" << endl;
    cout << "Все операции с бинарным деревом поиска выполнены корректно." << endl;
    
    return 0;
}
