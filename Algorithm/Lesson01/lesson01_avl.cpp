#include<iostream>
#include<new>
using namespace std;

class AVLTree
{
  class AVLNode
  {
  public:
    int      key;
    AVLNode* left;
    AVLNode* right;
    int      left_depth;
    int      right_depth;

    AVLNode( int x )
      : key(x), left(NULL), right(NULL), left_depth(0), right_depth(0) { };
  };


  AVLNode* root;

public:
  AVLTree( )         { root = NULL; };
  ~AVLTree( )        { }; // 本当は必要だが、都合により省略
  void Insert( int x )  { insert( x, root ); };
  void Show( ) const 
  { 
    cout << endl;
    if ( root != NULL ) 
      show( root, 0 ); 
    cout << endl;
  };

private:
  int  insert( int x, AVLNode* & p );
  void show( AVLNode* p, int height ) const;
  void rotate_with_left( AVLNode* & p );
  void rotate_with_right( AVLNode* & p );
};

void AVLTree::show( AVLNode* p, int depth ) const
{
  if ( p != NULL ) {
    show( p->right, depth+1 );
    cout.width(3*depth+3);
    cout << p->key << endl;
    show( p->left, depth+1 );
  }	
}

int AVLTree::insert( int x, AVLNode* & p )
{
  if ( p == NULL ) 
    p = new AVLNode( x );
  else if ( p->key == x ); 
  else if ( p->key > x ) {
    p->left_depth  = insert( x, p->left );
    if ( p->left_depth > p->right_depth + 1 )  {
      if ( p->left->right_depth > p->left->left_depth )
	rotate_with_right( p->left ); 
      rotate_with_left( p );
    }
  }
  else {
    p->right_depth = insert( x, p->right );
    if ( p->right_depth > p->left_depth + 1 )  {
      if ( p->right->left_depth > p->right->right_depth )
	rotate_with_left( p->right ); 
      rotate_with_right( p );
    }
  }

  return max( p->left_depth, p->right_depth ) + 1;
}

void AVLTree::rotate_with_left( AVLNode* & p )
{
  AVLNode* oldp = p;
  AVLNode* oldL = p->left;
  AVLNode* oldLR = p->left->right;

  p = oldL;
  p->right = oldp;
  p->right->left = oldLR;
  p->right->left_depth = oldL->right_depth;
  p->right_depth = max( p->right->right_depth, p->right->left_depth ) + 1;
}

void AVLTree::rotate_with_right( AVLNode* & p )
{
  AVLNode* oldp = p;
  AVLNode* oldR = p->right;
  AVLNode* oldRL = p->right->left;

  p = oldR;
  p->left = oldp;
  p->left->right = oldRL;
  p->left->right_depth = oldR->left_depth;
  p->left_depth = max( p->left->right_depth, p->left->left_depth ) + 1;
}

int main(void)
{ 

  AVLTree avlt;

  avlt.Insert(3); avlt.Insert(10); avlt.Insert(2); 
  avlt.Insert(4); avlt.Insert(11); 
  avlt.Show();

  avlt.Insert(12); 
  avlt.Show();

  avlt.Insert(7); avlt.Insert(6);
  avlt.Show();

  avlt.Insert(5); 
  avlt.Show();

  return 0;
}
