/*3_2. Сортировка почти упорядоченной последовательности.
Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j:
 если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность.
 Последовательность может быть очень длинной. Время работы O(n * log(k)). Память O(k).
 Использовать слияние.*/

#include <iostream>


using namespace std;

void Merge( int* firstArr, int* secondArr, int firstLen,int secondLen, int* resultArr){
    int i=0; // счетчики для двух кусков
    int j=0;
    while (i<firstLen && j<secondLen){ // Сливаем куски
        if(firstArr[i]<=secondArr[j]){ // Если меньше или равен элемент в первом куске- кладем его
            resultArr[i+j]=firstArr[i];
            ++i;
        }
        else{
            resultArr[i+j]=secondArr[j]; // Если меньше во втором- то его
            ++j;
        }
    }
    if (i==firstLen){
        for(;j<secondLen;++j){
            resultArr[i+j]=secondArr[j]; // если закончился один из кусков- закидывам другой полностью
        }
    }
    else if (j==secondLen) {
        for (; i < firstLen; ++i) {
            resultArr[i + j] = firstArr[i];
        }
    }
}




void MergeSort( int* a, int aLen ) { // Из лекции
    if( aLen <= 1 ) {
        return;
    }
    int firstLen = aLen / 2;
    int secondLen = aLen - firstLen;
    MergeSort( a, firstLen );
    MergeSort( a + firstLen, secondLen );
    int* c = new int[aLen];
    Merge( a, a + firstLen, firstLen, secondLen, c );
    for (int i(0);i<aLen;++i) {
        a[i]=c[i];
    }
    delete[] c;
}

void KSorter (int n, int k){
    int temp_array[2*k];
    int size=0; // для подсчета введеных и оставшихся
    int mergeSize=0;
    for (int i=0;i<k;++i){
        cin>>temp_array[i];
        size++;
    }

    while(size<n){
        mergeSize=0;
        for (int i=k;i<2*k && size<n;++i){

            cin>>temp_array[i];
            size++;
            mergeSize++;
        }
        MergeSort(temp_array,mergeSize+k);
        for (int j=0;j<k;++j){
            cout<<temp_array[j]<<" ";
        }
        for (int o=0; o<k;++o) {
            temp_array[o] = temp_array[o + k]; // не забиваем память,
        }   // рассматриваем следующие после сортировки предыдущих

    }
    for (int i=k;i<mergeSize+k;++i){
        cout<<temp_array[i]<<" ";
    }
}


int main() {
    int n=0;
    int k=0;
    cin>>n>>k;
    KSorter(n,k);
    return 0;
}

