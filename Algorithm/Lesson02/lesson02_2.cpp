#include <iostream>
#include <new>
#include <cassert>
#include <stdlib.h>
using namespace std;

class PriorityQueue {

  int* array;
  int  size;
  int  ndata;

public:
  PriorityQueue( int queue_size );  
  ~PriorityQueue( );  
  void Enqueue(int data); 
  void DequeueMin();   
  int  Min() const;
  bool IsEmpty() const;
};


PriorityQueue::PriorityQueue( int queue_size ) 
{
  array = new int [ queue_size ];
  size = queue_size;
  ndata = 0;
}

PriorityQueue::~PriorityQueue( ) 
{
  delete [] array;
}

void PriorityQueue::Enqueue( int data ) 
{
  if ( ndata >= size ) 
    throw " Queue overflow ";

  int parent;
  int i = ndata;

  while ( i > 0 ) {
    parent = (int) (i-1)/2;
    if ( array[ parent ] > data ) {
      array[ i ] = array[ parent ];
      i = parent; 
    }
    else
      break;
  }
  array[i] = data; 
  ndata++;
}

void PriorityQueue::DequeueMin( ) 
{
  int pos = 0;
  int tmp = array[ndata-1];
  int x = (int)(ndata-1)/2;

  while(x > pos){
    int child = 2*pos+1;
    
    if(array[child] > array[child + 1]) child++;
    if(array[child] > tmp) break;

    array[pos] = array[child];
    pos = child;
  }

  array[pos] = tmp;
  ndata--;
}

int PriorityQueue::Min( ) const
{
  return array[0];
}

bool PriorityQueue::IsEmpty( ) const
{
  return ( ndata <= 0 );
}

int main( int argc,char* argv[])
{
  int n = atoi(argv[1]);  // コマンドライン引数を読んで、整数に変換。

  cout << "The number of data : " << n << endl;

  try {
    PriorityQueue q(n);

    for ( int i = 0; i < n; i ++ ) {
      q.Enqueue(rand());
    }
    cout << n << " data were Enqueued " << endl;

    while ( ! q.IsEmpty() ) {
      q.DequeueMin();
    }
    cout << n << " data were Dequeued " << endl;
  } 

  catch ( bad_alloc ba ) {
    cout << "Memory allocation error." << endl;
  }
  catch ( const char* msg ) {
    cout << msg << endl;
  }


  return 0;
} 


/*************************************************
<実行方法>
> time ./a.out データ数

*************************************************/
