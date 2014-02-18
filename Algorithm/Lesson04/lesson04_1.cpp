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

  if ( nempty <= 1 )
    throw " Hash table is full ";

  int h = hash(k);
  while ( table[h].status == ACTIVE  )
    h = nexthash( h );

  table[h].key = k;
  table[h].value = v;
  if ( table[h].status == EMPTY )  
    nempty--; 
  table[h].status = ACTIVE;

  return true;
}

bool HashOpen::Find( string key, int & value ) const
{
  for(int h=hash(key),n=0; table[h].status != EMPTY && n < table_size; h=nexthash(h),n++){
    if(table[h].key == key){
      if(table[h].status == ERASED) continue;
      value = table[h].value;
      return true;
    }
  }
  return false;
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

    score.Insert( "mino",  10 );
    score.Insert( "yoshi",  20 );
    score.Insert( "nabe",  30 );
    score.Insert( "masaki",  40 );
    score.Insert( "ysuzuki",  50 );

    score.Insert( "tar",  10 );
    score.Insert( "target",  20 );
    score.Insert( "targ",  30 );
    score.Insert( "Max_Size",  40 );

    int i;

    if(score.Find("",i)) cout <<"Success ''"<< endl;
    if(score.Find("target",i)) cout <<"Success 'target'"<< endl;
    if(score.Find("Max_Size",i)) cout <<"Success 'Max_Size'"<< endl;

    if ( score.Find( "mino", i ) ) cout <<   i << endl;
    else cout << " not found" << endl;

    score.Erase( "mino" );

    if ( score.Find( "ysuzuki", i ) ) cout <<   i << endl;
    else cout << " not found" << endl;

    if ( score.Find( "mino", i ) ) cout <<   i << endl;
    else cout << " not found" << endl;

    score.Erase( "yoshi" );
    score.Erase( "nabe" );
    score.Erase( "masaki" );
    score.Erase( "ysuzuki" );
    score.Erase( "tar" );
    score.Erase( "targ" );
    score.Erase( "Max_Size" );

    if(score.Find( "Max_Size", i )) cout <<"Success  'Max_Size'"<< endl;
    if(score.Find( "tar", i )) cout <<"Success  'tar'"<< endl;
    if(score.Find( "targ", i )) cout <<"Success  'targ'"<< endl;
    if(score.Find( "target", i )) cout <<"Success  'target'"<< endl;
  }
  catch ( bad_alloc ba ) {
    cout << " memory allocation error." << endl;
  }
  catch ( const char* msg ) {
    cout << msg << endl;
  }

  return 0;

}
