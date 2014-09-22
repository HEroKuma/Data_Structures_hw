#include<iostream>
#include<cstdlib>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<stdio.h>

//姓名：張力偉 B013040028
//撰寫日期:2013/10/10
//用途：operator overloading

using namespace std;

class Tset{
public:
    bool Set[256];

    void putin(bool*);           //處理字串
    void putout();               //輸出字串

    Tset operator+(const Tset&); //重載運算子
    Tset operator-(const Tset&);
    Tset operator*(const Tset&);
    bool operator>=(const Tset&);
};

void Tset::putin(bool arry[])
{ for(int j = 0 ;j < 256; j++) Set[j] = false; //還原到初始狀態
  for(int i = 0 ;i < 256; i++){                                  //將字元所在的位置的狀態改為存在
    Set[i] = arry[i];
  }
}

void Tset::putout()
{
  for(int i = 0 ;i < 256; i++){
    if(Set[i]>0) printf("%c",i);             //輸出字元
  }
}

Tset Tset::operator+(const Tset& Sec_set)   //重載加法運算元
{
  Tset Nset;    //宣告一個新的物件去接住相加後的結果
  for(int con = 0 ;con < 256; con++){
    Nset.Set[con] = this->Set[con] | Sec_set.Set[con];      //聯集的作法為：兩集合取or運算元"|"
  }
  return Nset;  //回傳物件
}

Tset Tset::operator-(const Tset& Sec_set)  //重載減法運算元
{
  Tset Nset;   
  for(int con = 0 ;con < 256; con++){
    Nset.Set[con] = this->Set[con] & (!Sec_set.Set[con]);  //A與B差集的作法為：A與不是B的交集->A & (!B)
  }
  return Nset;
}

Tset Tset::operator*(const Tset& Sec_set)  //重載乘法運算元
{
  Tset Nset;
  for(int con = 0 ;con < 256; con++){
    Nset.Set[con] = this->Set[con] & Sec_set.Set[con];    //A與B的交集作法為:取and運算元"&"
  }
  return Nset;
}

bool Tset:: operator>=(const Tset& Sec_set)  //重載>=運算元
{
  Tset Nset;
  bool flag = true;
  for(int con = 0 ;con < 256; con++){
    Nset.Set[con] = this->Set[con] & Sec_set.Set[con]; //A與B取完交集後放到C跟A比較,一模一樣的話A就包含於C
  }
  for(int con = 0 ;con < 256;con++){
    if(Nset.Set[con] != this->Set[con]){
      flag = false;
      break;
    }
  }
  return flag;
}

int main()
{
  Tset A;
  Tset B;
  Tset check;

  int t;
  bool inputA[256] = {false};
  bool inputB[256] = {false};
  bool inputC[256] = {false};
  unsigned char x;

  cin >> t;
  while(t--){
    memset(inputA,0,256);
    memset(inputB,0,256);
    memset(inputC,0,256);
    
    cin.ignore();
    while(scanf("%c",&x) && x != 10){
      inputA[(int)x] = true;
    }
    //for(int i = 0 ;i < 256; i++) cout << inputA[i];
    //A.putout(); cout << endl;
    while(scanf("%c",&x) && x != 10){
      inputB[(int)x] = true;
    }
    while(scanf("%c",&x) && x != 10){
      inputC[(int)x] = true;
    }
    //cin.getline(inputA,500);
    //cin.getline(inputB,500);
    //cin.getline(inputC,10);

    A.putin(inputA);
    B.putin(inputB);
    check.putin(inputC);

    cout << "A: {";
      A.putout();
    cout << "}" << endl;
    cout << "B: {";
      B.putout();
    cout << "}" << endl;
    cout << "A+B: {";
      Tset C = A + B;
      C.putout();
    cout << "}" << endl;
        //A.putout(); cout << endl;
        //B.putout(); cout << endl;
    cout << "A*B: {";
      Tset D = A * B;
      D.putout();
    cout << "}" << endl;
       //A.putout(); cout << endl;
       //B.putout(); cout << endl;
    cout << "A-B: {";
      Tset E = A - B;
      E.putout();
    cout << "}" << endl;
    cout << "B-A: {";
      Tset F = B - A;
      F.putout();
    cout << "}" << endl;
        //A.putout(); cout << endl;
        //B.putout(); cout << endl;
    bool contain = (B >= A);
    if(contain) cout << "A does not contain B" << endl;
    else cout << "A contains B" << endl;

    contain = (A >= B);
    if(contain) cout << "B does not contain A" << endl;
    else cout << "B contain A" << endl;

    contain = (check >= A);
    cout << "'";
    check.putout();
    cout << "' ";
    if(!contain) cout << "is not in A" << endl;
    else cout << "is in A" << endl;

    contain = (check >= B);
    cout << "'";
    check.putout();
    cout << "' ";
    if(!contain) cout << "is not in B" << endl;
    else cout << "is in B" << endl;
  }
  return 0;
}
