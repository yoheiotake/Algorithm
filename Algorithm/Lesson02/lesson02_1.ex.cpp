#include <iostream>
#include <new>
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

int main( )
{
  try {

    PriorityQueue q(5);

    q.Enqueue(2);
    q.Enqueue(1);
    q.Enqueue(3);
    cout << q.Min() << endl ; 
    q.DequeueMin();

    q.Enqueue(5);
    q.Enqueue(4);
    cout << q.Min() << endl ; 
    q.DequeueMin();

    q.Enqueue(0);

    while ( ! q.IsEmpty() )  {
      cout << q.Min() << endl ;
      q.DequeueMin();
    }
  }
  catch ( bad_alloc ba ) {
    cout << "Memory allocation error." << endl;
  }
  catch ( const char* msg ) {
    cout << msg << endl;
  }


  return 0;
} 
