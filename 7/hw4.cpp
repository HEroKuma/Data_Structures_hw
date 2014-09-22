#include<iostream>
using namespace std;
class vector2D{
public:
    vector2D();
    vector2D(int,int);
    int x() {return _x;}
    int y() {return _y;}
    int operator*(const vector2D&);
    int _x;
    int _y;
};
vector2D::vector2D(){
    _x = 0;
    _y = 0;
}
vector2D::vector2D(int x,int y){
    _x = x;
    _y = y;
}
int vector2D::operator*(const vector2D &p){
    return _x*(p._x) + _y*(p._y);
}

int main()
{
  int x1,y1;
  int x2,y2;
  cin >> x1 >> y1;
  cin >> x2 >> y2;
  vector2D p1(x1,y1);
  vector2D p2(x2,y2);
  cout << p1*p2 << endl;
  return 0;
}
