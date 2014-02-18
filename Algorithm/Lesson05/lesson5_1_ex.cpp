#include <iostream>
#include <string>
#include <new>
using namespace std;

class HashOpen
{
  enum EntryType { ACTIVE, EMPTY, ERASED }; //ACTIVE : 有効なデータ、EMPTY : 空、ERASED : 削除されたデータ

  class HashEntry
  {
    string key;
    int value;
    EntryType status;

  public:
    HashEntry(  ){ status = EMPTY; };

    friend class HashOpen;
  };

  HashEntry* table;

  int        table_size;
  int        nempty;    // EMPTY 状態 HashEntry の数

public:
  HashOpen( int n );
  ~HashOpen( );
  bool Insert( string key, int value );
  bool Find( string key, int & value ) const;
  bool Erase( string key );

private:
  int hash( int i ) const { return i % table_size; };
  int hash( const string & s ) const ; 
  int nexthash ( int h ) const { return (h+1) % table_size; };
  void expand_table(int new_size);            
};

HashOpen::HashOpen( int size )
{ 
  table_size = size;

  table  =  new HashEntry[table_size];
  nempty = table_size;
}

int HashOpen::hash( const string & key ) const 
{
  int x = 0;
  for( int i=0; i < key.length(); i ++ )
    x = ( x * 64 + key[i] ) % table_size;
  return x;    
}

HashOpen::~HashOpen( )
{
  delete [] table;
}

bool HashOpen::Insert( string k, int v )
{

  if ( Find( k, v ) )
    return false;

  if( nempty * 3 < table_size ) {
    expand_table( table_size * 4 - 1 );
  }

  int h = hash(k);
  while ( table[h].status == ACTIVE  )
    h = nexthash( h );

  table[h].key = k;
  table[h].value = v;
  table[h].status = ACTIVE;

  nempty--;
  return true;
}

bool HashOpen::Find( string key, int & value ) const
{
  int h = hash(key);
  while(table[h].status != EMPTY ){
    if(table[h].key == key && table[h].status != ERASED){
      value = table[h].value;
      return true;
    }
    h = nexthash(h);
  }
  return false;
}


void HashOpen::expand_table( int new_size ) {

  int old_table_size = table_size;
  HashEntry* old_table = table;
  table = new HashEntry[new_size];
  table_size = new_size;
  nempty = table_size;

  for(int n=0; n < old_table_size; n++)
    if(old_table[n].status == ACTIVE) Insert(old_table[n].key,old_table[n].value);

  delete []old_table;
}

bool HashOpen::Erase( string key )
{
  for(int h=hash(key),n=0; table[h].status != EMPTY && n < table_size; h=nexthash(h),n++){
    if(table[h].key == key){
      table[h].status = ERASED;
      return true;
    }
  }
  return false;
}

int main()
{

  try {

    HashOpen score(10);

    char s[3];
    s[2] = (char)0; //文字列の終端記号

    for(int x=0; x<=25; x++){
      s[0] = (char)97 + x;
      for(int y=0; y<=25; y++){
	s[1] = (char)97 + y;
	score.Insert(s,0);
      }
    }

    int i;

    if(score.Find("a",i))  cout <<"Find 'a'" << endl;
    if(score.Find("aa",i)) cout <<"Find 'aa'"<< endl;
    if(score.Find("ab",i)) cout <<"Find 'ab'"<< endl;
    if(score.Find("zz",i)) cout <<"Find 'zz'"<< endl;
    
    cout << endl;
    if(score.Erase( "aa" )) cout<<"Erase 'aa'"<< endl;
    if(score.Erase( "zz" )) cout<<"Erase 'zz'"<< endl;

    cout << endl;
    if(score.Find("aa",i)) cout <<"Find  'aa'"<< endl;
    if(score.Find("ab",i)) cout <<"Find  'ab'"<< endl;
    if(score.Find("zz",i)) cout <<"Find  'zz'"<< endl;

    cout << endl;
    if(score.Insert("aa",0)) cout <<"Success 'aa'" << endl;
    if(score.Find("aa",i))   cout <<"Find    'aa'" << endl;

  }
  catch ( bad_alloc ba ) {
    cout << " memory allocation error." << endl;
  }
  catch ( const char* msg ) {
    cout << msg << endl;
  }

  return 0;

}


/************************************************ 
   <a=97,z=122>
   char s[4];
   s[0] = (char) 97; a
   s[1] = (char) 98; b
   s[2] = (char) 99; c
   s[3] = (char) 0 ; 文字列の最後に終端記号を入れる
   cout <<"string test = "<< s << endl;
   string ss = s;
************************************************/
