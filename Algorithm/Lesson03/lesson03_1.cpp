#include<iostream>
#include<string>
#include<list>
#include<algorithm>
using namespace std;

class HashSeparate
{
  list<int>* table;
  int  table_size;
  int  ndata;

public:
  HashSeparate( int size );
  ~HashSeparate( );
  bool Insert( int key );
  bool Find( int key ) const;
  bool Erase( int key );

private:
  int hash( int key ) const { return key % table_size; };
};

HashSeparate::HashSeparate( int size )
{
  table = new list<int>[size];
  table_size = size;
  ndata = 0;
}

HashSeparate::~HashSeparate( )
{
  delete[]table;
}

bool HashSeparate::Insert( int key )
{
  if(Find(key)) return false;
  else{
    table[hash(key)].push_front(key);
    ndata++;
    }
  return true;
}

bool HashSeparate::Find( int key ) const
{
  list<int>::iterator pos;
  pos = find(table[hash(key)].begin(),table[hash(key)].end(),key);
  if(pos == table[hash(key)].end()) return false;
  else return true;
}

bool HashSeparate::Erase( int key ){
  list<int>::iterator pos;
  for(pos = table[hash(key)].begin(); pos != table[hash(key)].end();pos++){
    if((*pos) == key){
      table[hash(key)].erase(pos);
      return true;
    }
  }
  return false;
}

int main()
{
  HashSeparate score(100);

  if(score.Insert(100)) cout<<"Success"<<endl;;
  if(!score.Insert(100)) cout<<"Error"<<endl;;

  if(score.Insert( 120) && score.Insert(4501) && score.Insert( 200) && score.Insert(1000)) cout<<"Success"<<endl;
  
  cout << score.Find( 200) << endl;
  cout << score.Find(  10) << endl;
  cout << score.Find(   0) << endl;
  cout << score.Find( 100) << endl;
  cout << score.Find(4501) << endl;
  cout << score.Find(4500) << endl;
  cout << score.Find(1000) << endl;

  cout <<"Erase key=100"<< endl;
  if(score.Erase(100)) cout<<"Success"<<endl;

  cout << score.Find( 200) << endl;
  cout << score.Find(  10) << endl;
  cout << score.Find(   0) << endl;
  cout << score.Find( 100) << endl;
  cout << score.Find(4501) << endl;
  cout << score.Find(4500) << endl;
  cout << score.Find(1000) << endl;

  return 0;
}
