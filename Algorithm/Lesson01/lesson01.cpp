#include <iostream>
#include <string>
#include <new>
using namespace std;

class BinaryNode
{
  int         key;
  BinaryNode* left;
  BinaryNode* right;

public:
  BinaryNode( int x )
  {
    key = x;
    left = NULL;
    right = NULL;
  };

  friend class BinarySearchTree;
};


class BinarySearchTree
{

  BinaryNode* root;
public:
  BinarySearchTree( );
  ~BinarySearchTree( );
  bool Insert( int x );
  bool Find( int x ) const;
  void Show( ) const;

private:
  bool insert( int x, BinaryNode* & p );
  bool find( int x, BinaryNode* p ) const;
  void show( BinaryNode* p ) const;
  void makeEmpty( BinaryNode* p );
};

BinarySearchTree::BinarySearchTree( )
{
  root = NULL;
}

BinarySearchTree::~BinarySearchTree( )
{
  makeEmpty( root );
}

void BinarySearchTree::makeEmpty( BinaryNode* p )
{
  if ( p != NULL ) {
    makeEmpty( p -> left );
    makeEmpty( p -> right );
    delete p;
  }
}

bool BinarySearchTree::Insert( int x )
{                                     
  return insert( x, root );
}

bool BinarySearchTree::insert( int x, BinaryNode* & p )
{                                     
  if ( p == NULL ) {
    p = new BinaryNode( x );
    return true;
  }
  else if ( p->key == x )
    return false ;
  else if ( p->key > x )
    return insert( x, p->right );
  else
    return insert( x, p->left );
}

void BinarySearchTree::Show(  ) const
{                                
  show( root );
}

void BinarySearchTree::show( BinaryNode* p ) const
{
  if ( p != NULL ) {
    show( p->left );
    cout << p->key << endl;
    show( p->right );
  }
}

bool BinarySearchTree::Find( int x ) const
{                                      
  return find( x, root );
}

bool BinarySearchTree::find( int x, BinaryNode* p ) const
{
  if(p == NULL)        return false;
  else if(p->key == x) return true;
  else if(p->key > x)  return find(x,p->right);
  else                 return find(x,p->left);
}

int main( )
{ 

  BinarySearchTree bst;

  bst.Insert(2);
  bst.Insert(3);
  bst.Insert(1);
  bst.Insert(4);
  bst.Insert(0);
  bst.Show();

  int x = 0;
  cout <<"Input Number"<< endl;
  cin  >> x;

  if(!cin){
    cout <<"Invalid Number"<< endl;
    return -1;
  }

  if(bst.Find(x)) cout <<"Success"<< endl;
  else            cout <<"Error"  << endl;

  return 0;
} 
