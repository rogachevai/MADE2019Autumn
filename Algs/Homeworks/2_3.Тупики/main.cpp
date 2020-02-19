/* На вокзале есть некоторое количество тупиков, куда прибывают электрички.
Этот вокзал является их конечной станцией. Дано расписание движения электричек,
в котором для каждой электрички указано время ее прибытия, а также время отправления
в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
При этом если электричка из какого-то тупика отправилась в момент времени X,
то электричку, которая прибывает в момент времени X, в этот тупик ставить нельзя,
а электричку, прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное
количество тупиков для работы по расписанию. Напишите программу, которая по данному
расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.

Формат ввода
Вначале вводится n - количество электричек в расписании.
Затем вводится n строк для каждой электрички, в строке - время прибытия
и время отправления. Время - натуральное число от 0 до 1 000 000 000.
Строки в расписании упорядочены по времени прибытия.

Формат вывода
Натуральное число - минимальное количеством тупиков.
*/
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

template <class T>
class Heap {
public:
    Heap(){
        size =0;
        createHeap();
    };
    //~Heap();

    bool empty();
    int top();
    int pop(); //extract
    void push(int value);

    int size;
    //int getSize(); Можем ли закидывать размер в паблик, или лучше сделать размер в привате,
    // а потом просто добавить метод для его получения?

private:

    void createHeap();
    void siftUp(int index);
    void siftDown(int index);

    vector<T> buffer; //Cогласно слаку, можем использовать вектор.
};

// Восстановление свойств
template <class T>
void Heap<T>::siftUp(int index) {
    int parentIndex = 0;
    while (index>0){ // пока не дошли до самого верха
        parentIndex=(index-1)/2;
        if (buffer[index]>buffer[parentIndex]) {
            swap(buffer[index],buffer[parentIndex]); // меняем местами, чтобы сохранить условия кучи
        }
        index=parentIndex;
    }
}

template <class T>
void Heap<T>::siftDown(int index) {
    int i=0;// Не уверен, можно ли объявить в условии цикла,
    // если потом буду использовать после цикла? Поэтому объеявил до
    for (i; i*2+2<buffer.size();){ // Пока есть потомки справа
        if (buffer[i*2+2]<buffer[i*2+1]){
            if(buffer[i]<buffer[i*2+1]){
                swap(buffer[i],buffer[i*2+1]);
                i=i*2+1;
            } else
                break;
        }
        else {
            if (buffer[i]<buffer[i*2+2]){
                swap(buffer[i],buffer[i*2+2]);
                i=i*2+2;
            }
            else
                break;
        }
    }
    if (i*2+1<buffer.size()) { // Если справа все закончились
        if (buffer[i] < buffer[i * 2 + 1]) {
            swap(buffer[i], buffer[i * 2 + 1]);
        }
    }
}

template <class T>
void Heap<T>::createHeap() { // Из лекции
    for(int i=buffer.size()/2-1; i>=0;--i){ // Следует ли нам указыавть это прямо в конструкторе?
        // или это отдельная функция, вызываемая в конструкторе?
        siftDown(i);
    }

}


template <class T>
bool Heap<T>::empty() {
    return (size==0);
}

template <class T>
int Heap<T>::top() {
    return buffer[0];
}

template <class T>
int Heap<T>::pop() {
    assert(!buffer.empty());
    int top=buffer[0];
    buffer[0]=buffer[size-1];// Берем последний, делаем первым и просеиваем
    buffer.pop_back(); // выкидываем последний из конца
    siftDown(0);
    --size;
    return top; // Если правильно понял- этим методом мы должны и удалять элемент,
    // и возвращать
}

template <class T>
void Heap<T>::push(int value) {
    buffer.push_back(value); //Добавляем в конец и просеиваем вверх
    siftUp(size);
    ++size;

}



//template <class T>
//int Heap<T>::getSize() {
//    return size;
//}

struct time_struct {
    int arrival;
    int departure;

    time_struct(){
        arrival=0;
        departure=0;
    }
};

int main() {
    Heap<int> heap;
    vector<int> heap_buffer;
    time_struct schedule;

    int commands_count = 0;
    cin >> commands_count;
    assert(commands_count > 0);
    for (int i = 0; i < commands_count; ++i) {
        cin >> schedule.arrival >> schedule.departure;
        assert(schedule.arrival >= 0 && schedule.arrival <= 1000000000 && schedule.departure >= 0 &&
               schedule.departure <= 1000000000); // по условию
        if (!(heap.empty())) {
            while (!(heap.empty()) && schedule.arrival <= heap.top()) { // Если куча непуста, и временя прибытия меньше максимального, то засовываем в буфер
                heap_buffer.push_back(heap.pop());
            }
            if (!(heap.empty()) && schedule.arrival > heap.top()) { // если непуста, но время уже больше максимального- достаем максимальный ,
                // берем последний в буфере и добавляем в кучу, убираем его из буфера
                heap.pop();
                int k = heap_buffer.size() - 1;
                for (k; k >= 0; --k) {
                    heap.push(heap_buffer[k]);
                    heap_buffer.pop_back();
                }
            }
            if (heap.empty()) {
                int k = heap_buffer.size() - 1;
                for (k; k >= 0; --k) {
                    heap.push(heap_buffer[k]);
                    heap_buffer.pop_back();
                }
            }
        }
        heap.push(schedule.departure); // засовываем время отправления в кучу
    }
    cout << heap.size;
    return 0;
}