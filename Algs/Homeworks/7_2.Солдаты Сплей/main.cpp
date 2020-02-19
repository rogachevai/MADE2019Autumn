/*Задача 7. Использование самобалансирующихся деревьев (7 баллов)
Солдаты. В одной военной части решили построить в одну шеренгу по росту.
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность –
все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат,
а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится.
Вариант 7_2.  Требуемая скорость выполнения команды - O(log n) амортизировано. Для решения задачи реализуйте сплей дерево.*/
#include <iostream>
#include <assert.h>

using namespace std;
#define SplayTree struct splayTree

struct SplayNode {
    int key;
    int childrenCount; // Помимо роста будем сохранять количество потомков
    SplayNode* parent;
    SplayNode* Left;
    SplayNode* Right;

    SplayNode(SplayNode* par, int k) {
        key=k;
        parent=par;
        childrenCount=1;
        Left=0;
        Right=0;
    }
    ~SplayNode() {
        delete Left;
        delete Right;
    }
};

void recount_children (SplayNode* tree) { // Нам потребуется пересчитывать количество наследников после сплея
    if (tree==0){
        return;
    }
    else {
        tree->childrenCount=1;
        if (tree->Right!=0) {
            tree->childrenCount+=tree->Right->childrenCount;
        }
        if (tree->Left!=0) {
            tree->childrenCount+=tree->Left->childrenCount;
        }
    }
}
SplayNode* mkNode(SplayNode* parent, int key){
    SplayNode* node= (SplayNode*)malloc(sizeof(SplayNode));
    node->Left = node->Right = 0;
    node->parent = parent;
    node->key = key;
    node->childrenCount=1;
    return node;
}
SplayNode* addNode( SplayNode* currentrent, int key){
    if (currentrent->key==key){
        return currentrent;
    }
    SplayNode* tmp;
    if (currentrent->key>key) {
        if (currentrent->Left){
            tmp=addNode(currentrent->Left,key);}

        else {
            tmp= currentrent->Left=mkNode(currentrent,key);
        }
    } else {
        if (currentrent->Right) {
            tmp=addNode(currentrent->Right,key);
        } else {
            tmp=currentrent->Right=mkNode(currentrent,key);
        }
    }
    recount_children(tmp);
    return tmp;
}

SplayNode* findNode(SplayNode* current, SplayNode** previous, int key) { // поиск по ключу
    while (current) {
        if (current->key==key){
            return current;
        } else {
            *previous=current;
            if (current->key>key) {
                current=current->Left;
            } else {
                current=current->Right;
            }
        }
    }
    return 0;
}

SplayNode* removeNode(SplayNode** root, SplayNode* node) { // удаление
    SplayNode* previous, *higherClosest, *parent, *children, *removedNode;
    previous = higherClosest = parent = children = 0;

    if(node->Left && node->Right) { // если есть дети
        higherClosest = findNode(node, &previous, node->key+1);
        if(!higherClosest) {
            higherClosest = previous;
            parent = previous->parent;
        } else {
            parent = previous;
        }
        node->key = higherClosest->key;
        if(higherClosest == parent->Left)
            parent->Left = higherClosest->Right;
        else
            parent->Right = higherClosest->Right;

        if(higherClosest->Right)
            higherClosest->Right->parent = parent;

        removedNode = higherClosest;
    } else {
        parent = node->parent;
        children = node->Left ? node->Left : node->Right; //если есть наследники слева
        if(!parent) //если нет родителя
            *root = children;
        else {
            if(parent->Left == node)
                parent->Left = children;
            else
                parent->Right = children;
        }
        if(children)
            children->parent = parent;

        removedNode = node;
    }
    free(removedNode);
    recount_children(parent);
    return parent;
}

void chainGrandParent(SplayNode* grandparent, SplayNode* parent, SplayNode* children) {//Перекидываем внука к деду
    if(grandparent->Left == parent)//В зависимости от того, с какой стороны был отец
        grandparent->Left = children;
    else
        grandparent->Right = children;
}
//Напишем повороты, чтобы использовать из в зиг и заг'ах
SplayNode* rotateRight(SplayNode** root, SplayNode* r) {
    SplayNode* child = r->Left;
    r->Left = child->Right;
    if(child->Right)
        child->Right->parent = r;
    child->parent = r->parent;
    recount_children(r);
    recount_children(child);
    if(r->parent)
        chainGrandParent(r->parent, r, child);
    else
        *root = child;
    child->Right = r;
    r->parent = child;
    recount_children(r);
    recount_children(child);
    return child;
}

SplayNode* rotateLeft(SplayNode** root, SplayNode* r) {
    SplayNode* child = r->Right;
    r->Right = child->Left;
    if(child->Left)
        child->Left->parent = r;
    child->parent = r->parent;
    recount_children(r);
    recount_children(child);
    if(r->parent)
        chainGrandParent(r->parent, r, child);
    else
        *root = child;
    child->Left = r;
    r->parent = child;
    recount_children(r);
    recount_children(child);
    return child;
}

// опишем все для дерева
// единственное что- не совсем понимаю, нужно ли все эти функции сначала задавать в классе,
// а потом уже описывать отдельно. Есть ли тут какие-то правила или это чисто эстетический момент?
SplayTree {
    SplayNode* root;
};

SplayTree* initSplayTree() {
    SplayTree* stree = (SplayTree*)malloc(sizeof(SplayTree));
    stree->root = 0;
    return stree;
}

int isZigZag(SplayNode* current) {
    SplayNode* p = current->parent; // Папа
    SplayNode*  gp = p->parent; // дед
    return (p->Right == current && gp->Left == p) ||
           (p->Left == current && gp->Right == p);
}

void zigZag(SplayNode** treeRoot, SplayNode* current) {
    SplayNode* p = current->parent;
    if(p->Right == current && p->parent->Left == p) // если мы справа, а папа у деда слева
        rotateRight(treeRoot, rotateLeft(treeRoot, p) -> parent);
    else
        rotateLeft(treeRoot, rotateRight(treeRoot, p) -> parent);
}
void zigZig(SplayNode** treeRoot, SplayNode* current) {
    SplayNode* p = current->parent;
    if(p->Left == current && p->parent->Left == p) // если мы слева, а папа у деда слева
        rotateRight(treeRoot, rotateRight(treeRoot, p->parent));
    else
        rotateLeft(treeRoot, rotateLeft(treeRoot, p->parent));
}
void zig(SplayNode** treeRoot, SplayNode* current) {
    SplayNode* p = current->parent;
    if(p->Left == current) // если мы слева от папы
        rotateRight(treeRoot, p);
    else
        rotateLeft(treeRoot, p);
}

SplayNode* splay(SplayNode** root, SplayNode* current) {
    if(!current)
        return 0;
    while(current->parent) {
        if(current->parent->parent)
            if(isZigZag(current))
                zigZag(root, current);
            else
                zigZig(root, current);
        else
            zig(root, current);
    }
    return current;
}

SplayNode* insertKey(SplayTree* tree, int key) {
    if(!tree->root)
        tree->root = mkNode(0, key);
    return splay(&tree->root, addNode(tree->root, key));
}

int removeKey(SplayTree* tree, int key) {
    SplayNode* prev = 0;
    SplayNode* res = findNode(tree->root, &prev, key);
    if(res)
        splay(&tree->root, removeNode(&tree->root, res));
    else if(prev)
        splay(&tree->root, prev);
    return res ? 1 : 0; // для себя, так проще проверять, все ли работает
}


// для первого действия нам нужно находить позицию по росту
//сделать это мы сможем как раз с помощью хранимой нами переменной childrenCount
void PositionOfSoldier( SplayNode* root, int height, int& counter )
{
    if( height == root->key ) {
        if( root->Right != 0 ) {
            counter = counter + root->Right->childrenCount;
        }
    }
    if( height > root->key ) {
        PositionOfSoldier( root->Right, height, counter );
    }
    if( height < root->key ) {
        if( root->Right != 0 ) {
            counter = counter + root->Right->childrenCount + 1;
            PositionOfSoldier( root->Left, height, counter );
        } else {
            counter = counter + 1;
            PositionOfSoldier( root->Left, height, counter );
        }
    }
}
// функция для второй операции, которая позволит определить рост по позиции
// чтобы потом удалить его из строя по росту
void HeightOfSoldier( SplayNode* root, int position, int& height )
{
    int RootRightChildren = 0;
    if( root->Right != 0) {
        RootRightChildren = root->Right->childrenCount;
    }
    if( position == RootRightChildren ) {
        height = root->key;
    }
    if( position > RootRightChildren ) {
        HeightOfSoldier( root->Left, position - RootRightChildren - 1, height );
    }
    if( position < RootRightChildren ) {
        HeightOfSoldier( root->Right, position, height );
    }
}


int main() {
    int n;
    cin >> n;
    assert((n>=1)&&(n<=90000));
    SplayTree* tree = initSplayTree();
    for( int i = 0; i < n; i++ ) {
        int operation;
        cin >> operation;
        if( operation == 1 ) {
            int height;
            cin >> height;
            assert((n>-1)&&(n<100001));
            SplayNode* tmp = insertKey(tree, height); // добавляем
            int position = 0;
            PositionOfSoldier( tmp, height, position ); // а потом считаем позицию
            cout << position << endl;
        }
        if( operation == 2 ) {
            int position;
            cin >> position;
            int height;
            HeightOfSoldier( tree->root, position, height ); // по позиции находим, кого нужно удалить
            int res = removeKey(tree, height); // удаляем, ничего не выводим
        }
    }
}
