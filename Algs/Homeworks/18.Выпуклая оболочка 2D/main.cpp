/*
Дано множество точек на плоскости (x, y). Постройте выпуклую оболочку этого множества и вычислите ее периметр.
Формат ввода
Количество точек, далее на каждой строке координаты точек x, y.
Общее количество точек не превосходит 100000. Координаты точек - числа с плавающей точкой в диапазоне [-1000, 1000].
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;
struct Point{
    double x, y;
};

double dist(Point p1, Point p2){ // считаем расстояние между точками p1 и p2
    return sqrt((p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y));
}

double perimeter(vector<Point> hull){ // находим периметр оболочки
    double perimeter = 0.0;
    for (int i = 0; i < hull.size() - 1; i++) {
        perimeter += dist(hull[i], hull[i + 1]);
    } perimeter += dist(hull[0], hull[hull.size() - 1]);
    return perimeter;
}

int orientation(Point p1, Point p2, Point p3) { // определяем, лежат ли точки на одной прямой
    double val = (p2.y - p1.y)*(p3.x - p2.x)-(p2.x - p1.x)*(p3.y - p2.y);
    double eps= 0.0000000000000001;
    if (abs(val) < eps) {
        return 0; // если лежат
    }if (val>eps){ // если не лежат, то определяем ориентацию
        return 1;
    } else {
        return 2;
    }
}

vector<Point> hullJarvis(Point points[], int n) {
    vector<Point> hull;
    int p1 = 0;
    for (int i = 1; i < n; i++){ // найдем нижнюю левую точку (p1)
        if (points[i].x < points[p1].x){
            p1 = i;
        } else {
            if (points[i].x==points[p1].x && points[i].y<points[p1].y){
                p1 = i;
            }
        }
    }
    int p = p1, q;
    do{
        hull.push_back(points[p]);
        q = (p+1)%n;
        for (int i = 0; i < n; i++){ // просматриваем точки, находим наибольший угол
            if (orientation(points[p], points[i], points[q]) == 2) {// идем против часовой стрелки
                q = i;
            }
            else{ if (orientation(points[p], points[i], points[q]) == 0){
                    if  (dist(points[i], points[p]) > dist(points[q], points[p])){
                        q = i;
                    }
                }}
        }
        p = q; // нашли очередную точку, если она не начальная (p1)- закидываем ее в оболочку,
    } while (p != p1);// а если начальная- оболочка готова
    return hull;
}

int main() {
    int n;
    cin>>n;
    assert(n<100001);
    Point points[n];
    double x;
    double y;
    for (int i=0; i<n;i++){
        cin>>x>>y;
        assert(x*x<=1000.*1000.);
        assert(y*y<=1000.*1000.);
        points[i].x=x;
        points[i].y=y;
    } vector<Point> hullRes = hullJarvis(points, n);
    cout.precision(16);
    cout << perimeter(hullRes);
    return 0;
} 