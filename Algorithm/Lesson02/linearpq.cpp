#include <iostream>
#include <new>
#include <cassert>
#include <stdlib.h>
using namespace std;

class PriorityQueue {

  class Cell {
      
  public:
    int  data;
    Cell* next;

    Cell( int x, Cell* p ) : data(x), next(p) {} ;
  };

  Cell* top;

public:
  PriorityQueue(  );  
  ~PriorityQueue(  );  
  void Enqueue(int x); 
  void DequeueMin( );   
  void Dump( );
  int Min( ) const;
  bool IsEmpty( ) const;
};


PriorityQueue::PriorityQueue(  ) 
{
  top = NULL;
}

PriorityQueue::~PriorityQueue( ) 
{
  while ( ! IsEmpty() )
    DequeueMin( );
}

void PriorityQueue::Enqueue( int x ) 
{
  // データは値の小さい順に並べておく。
  if ( top == NULL || top->data >= x ) {
    top = new Cell( x, top );
  }
  else {
    Cell* p = top;
    // データを挿入すべき場所を探す。
    while ( p->next != NULL && p->next->data < x ) {
      p = p->next;
    }
    p->next = new Cell( x, p->next );
  }
}

void PriorityQueue::DequeueMin( void ) {

  assert ( top != NULL );  // キューが空では Dequeue できない。

  Cell* oldtop = top;
  top = top->next;
  delete oldtop;
  return;
}

void PriorityQueue::Dump( )
{
  for ( Cell* p = top; p != NULL; p = p->next )
    cout << p->data << endl;
  return;
}

int PriorityQueue::Min( ) const {

  return top->data;
}

bool PriorityQueue::IsEmpty( ) const
{
  return ( top == NULL  );
}

int main( int argc, char* argv[])
{

  int n = atoi(argv[1]);  // コマンドライン引数を読んで、整数に変換。

  cout << "The number of data : " << n << endl;

  try {
    PriorityQueue q;

    for ( int i = 0; i < n; i ++ ) {
      q.Enqueue(rand());  // ランダムな数を Enqueue する。
    }
    cout << n << " data were Enqueued " << endl;

    while ( ! q.IsEmpty() ) {
      q.DequeueMin();      // 最小値を Dequeue する。
    }
    cout << n << " data were Dequeued " << endl;
  } 
  catch ( bad_alloc ba ) {
    cout << "memory allocation error." << endl;
  }
  catch ( const char* msg ) {
    cout << msg << endl;
  }

  return 0;
}
