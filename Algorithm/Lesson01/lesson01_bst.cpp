#include<iostream>
#include<new>
using namespace std;

class BinarySearchTree
{
  class BinaryNode
  {
  public:
    int      key;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode( int x ) : key(x), left(NULL), right(NULL) { };
  };


  BinaryNode* root;

public:
  BinarySearchTree( )   { root = NULL; };
  ~BinarySearchTree( )  { }; // 本当は必要だが、都合により省略
  void Insert( int x )  { insert( x, root ); };
  void Show( ) const 
  { 
    cout << endl;
    if ( root != NULL ) 
      show( root, 0 ); 
    cout << endl;
  };

private:
  void insert( int x, BinaryNode* & p );
  void show( BinaryNode* p, int height ) const;
};

void BinarySearchTree::show( BinaryNode* p, int depth ) const
{
  if ( p != NULL ) {
    show( p->right, depth+1 );
    cout.width(3*depth+3);
    cout << p->key << endl;
    show( p->left, depth+1 );
  }	
}

void BinarySearchTree::insert( int x, BinaryNode* & p )
{
  if ( p == NULL ) 
    p = new BinaryNode( x );
  else if ( p->key == x ); 
  else if ( p->key > x ) {
    insert( x, p->left );
  }
  else {
    insert( x, p->right );
  }
}

int main(void)
{ 

  BinarySearchTree bst;

  bst.Insert(3); bst.Insert(10); bst.Insert(2); 
  bst.Insert(4); bst.Insert(11); 
  bst.Show();

  bst.Insert(12); 
  bst.Show();

  bst.Insert(7); bst.Insert(6); bst.Insert(5); 
  bst.Show();

  return 0;
}
