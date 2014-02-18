#include<iostream>
#include<list>
#include<string>
using namespace std;

int main()
{

  list<int> ilist;

  ilist.push_back( 3 );  // リストの末尾に追加
  ilist.push_back( 1 );
  ilist.push_back( 2 );

  list<int>::const_iterator itr; 
  // イタレータ(iterator)とは、リストの中のデータを指すポインタみたいなもの

  // イタレータを使ってリストの中身を洩れなくたどる方法。
  for ( itr = ilist.begin(); itr != ilist.end(); itr ++ ) 
    cout << *itr << endl;
  cout << endl;

  ilist.push_back( 4 );

  for ( itr = ilist.begin(); itr != ilist.end(); itr ++ )
    cout << *itr << endl;
  cout << endl;


  return 0;
}
