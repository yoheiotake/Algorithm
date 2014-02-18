#include<iostream>
#include<map>
#include<string>
using namespace std;

int main()
{

  map<string,int> months;
  // string をキーとし、int を値とするマップを宣言

  // マップへのデータの登録
  months["July"] = 7;
  months["October"] = 10;
  months["March"] = 3;

  map<string,int>::const_iterator itr;
  // map にもイタレータが使える。

  // マップの中身を全部たどる。
  for( itr = months.begin(); itr != months.end(); itr ++ )
    cout << itr->first << " " << itr->second << endl;
  cout << endl;
  // キーは itr->first で、値は itr->second で参照できる。


  // あるキーをもつデータがあるかどうかの判定。
  if ( months.find("July") != months.end() )
    cout << "July " << months["July"] << endl;
  else
    cout << "July is not found. " << endl;

  cout << endl;

  if ( months.find("April") != months.end() )
    cout << "April " << months["April"] << endl;
  else
    cout << "April is not found. " << endl;

  cout << endl;

  months["April"] = 4;

  for( itr = months.begin(); itr != months.end(); itr ++ )
    cout << itr->first << " " << itr->second << endl;
  cout << endl;

     
  return 0;
}
