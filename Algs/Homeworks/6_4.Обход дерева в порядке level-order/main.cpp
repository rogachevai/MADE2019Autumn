/* Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”). */

#include <iostream>
#include <queue>
#include <assert.h>

using namespace std;

// Хотел отметить, что в задании в облаке говорится о запрете рекурсии, в контесте это не оговорено.
// Рекурсию не использовал. Не уверен, на сколько легитимно использовать очередь для level-order,
// но об этом ниде не говорится.

struct Node{ // Узел
    int data;
    Node* Left;
    Node* Right;

    Node(int k){
        data=k;
        Left=0;
        Right=0;
    }
    ~Node(){
        delete Left;
        delete Right;
    }
};

class BTree{ // Само дерево
private:
    Node* root;
    void LevelOrder(Node * root);
public:
    BTree(){
        root=0;
    }
    ~BTree(){
        delete root;
    }
    void Add(int Data);
    void LevelOrder() { // Вывод элементов в порядке level-order.
        LevelOrder(root);
    };
};

void BTree::Add(int Data) {
    Node* newNode = new Node(Data);
    if (root==0){ // Если дерево пустое
        root=newNode;
    }
    else {
        Node* nearestNode=root;
        while (true){
            if (Data<nearestNode->data) { // Если новое число меньше корня, то идем в левое поддерево
                if (nearestNode->Left != 0) {
                    nearestNode=nearestNode->Left;
                }
                else{
                    nearestNode->Left=newNode; // Если больше идти некуда - подвешиваем
                    return;
                }
            }
            else { // Аналогично для правого поддерева
                if (nearestNode->Right !=0){
                    nearestNode=nearestNode->Right;
                }
                else{
                    nearestNode->Right=newNode;
                    return;
                }
            }
        }

    }
}

void BTree::LevelOrder(Node* root) {
    if(root == 0){
        return;
    }
    std::queue<Node*> Q;
    Q.push(root);
    while(!Q.empty())
    {
        Node* current = Q.front();
        cout<< current->data << " ";
        if(current->Left != 0) Q.push(current->Left);
        if(current->Right != 0) Q.push(current->Right);
        Q.pop();
    }
}




int main() {
    int n=0;
    int m=0;
    cin>>n;
    assert(n<10^6);
    BTree tree;

    for (int i=0;i<n;++i){
        cin>>m;
        assert((m<=2^31)&(m>=-2^31));
        tree.Add(m);
    }
    tree.LevelOrder();
    return 0;
}