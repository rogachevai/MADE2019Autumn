/* Реализовать очередь с динамическим зацикленным буфером.
Формат входных данных.
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
Если дана команда pop*, то число b - ожидаемое значение.Если команда pop вызвана для пустой структуры данных, то ожидается “-1”. 
Формат выходных данных.
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.*/
#include <iostream>
using namespace std;
class Queue {
public:
    Queue() {
        size = 2; // задаем размер по умолчанию
        head = 0; // можно было сделать 0 и увеличивать сразу при создании
        tail = 0; // так делал в предыдущих версиях, но решил убрать
        realSize = 0;
        {
            data=new int[size];}


    }

    ~Queue() {
        if (data != NULL) {
            delete[] data;
        }
    };

    bool empty() const;
    void push(int value);
    int pop();
    void increaseSize();



private:
    int *data; // Сами числа
    int head; // Номер первого элемента
    int tail; // Номер последнего элемента
    int size; // Размер буфера
    int realSize; // Количество элементов в буфере в текущий момент
    // Пробовал сделать без данной переменной, но не получалось пройти тест
};



bool Queue::empty() const {
    return (realSize == 0);
}


void Queue::increaseSize() {
    int newSize= size*2; // вместо 2 можем выбрать и другой множитель
    int *newData= new int [newSize];
    for (int i=0;i<size;i++){
        newData[i]=pop();
    } delete[] data;
    head=0;
    tail=realSize=size;
    data=newData;
    size=newSize;
}
int Queue::pop() {
    if (realSize!=0){
        int reqValue=data[head];
        head= (head+1) % size;
        --realSize;
        return reqValue;
    }
}


void Queue::push(int value) {
    if (size==realSize){
        increaseSize();
    }
    data[tail]=value;
    tail=(tail+1)% size;
    realSize++;
}

int main(){

    int commands_count = 0;
    cin >> commands_count;
    Queue queue;	// по аналогии с семинаром
    if (commands_count>1000000){ // сначала делал с ассертами, но потом переписал с if
        cout<<"NO";
        return 0;
    }
    else {
        for (int i=0; i<commands_count; i++) {
            int command = 0;
            int val = 0;
            cin >> command >> val;
            if (command==3){
                queue.push(val);
            } else if (command ==2) {
                if (queue.empty()) {
                    if (val != -1) {
                        cout<<"NO";
                        return 0;
                    }
                } else if (queue.pop() != val) {
                    cout << "NO";
                    return 0;
                }
            }
        }
        cout <<"YES";
        return 0;}
}
