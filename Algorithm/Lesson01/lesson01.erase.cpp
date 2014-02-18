#include <iostream>
#include <cassert>
#include <string>
#include <new>
using namespace std;

class BinarySearchTree
{
    class BinaryNode
    {
        int         key;
        BinaryNode* left;
        BinaryNode* right;

      public:
        BinaryNode( int x ): key(x), left(NULL), right(NULL) { };

      friend class BinarySearchTree;
    };

    BinaryNode* root;

  public:
    BinarySearchTree( );
    ~BinarySearchTree( );
    bool Insert( int x );
    void Show( ) const;
    bool Find(int x)const;
    int Max()const;
    int Min()const;
    bool Erase(int x);
  private:
    bool insert( int x, BinaryNode* & p );
    void show( BinaryNode* p ) const;
    void makeEmpty( BinaryNode* p );
    bool find(int x,BinaryNode* p )const;
    int max(BinaryNode* p)const;
    int min(BinaryNode* p)const;
    bool erase(int x,BinaryNode* & p );

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
      p = new BinaryNode(x);
        return true;
    }
    else if ( p->key == x )
        return false ;
    else if ( p->key > x )
        return insert(x,p->left);
    else
        return insert(x,p->right);
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

bool BinarySearchTree::Find(int x)const
{
  return find(x,root);
}

bool BinarySearchTree::find(int x,BinaryNode* p)const
{
  if(p==NULL)
    return false;
  else if(p->key==x)
    return true;
  else if(x>p->key)
    return find(x,p->right);
  else
    return find(x,p->left);
}

int BinarySearchTree::Max()const
{
  assert(root!=NULL);
  return max(root);
}

int BinarySearchTree::max(BinaryNode* p)const
{
  if(p->right==NULL)
   return p->key;
  else
    return max(p->right);
}

int BinarySearchTree::Min()const
{
  assert(root!=NULL);
  return min(root);
}

int BinarySearchTree::min(BinaryNode* p)const
{
  if(p->left==NULL)
    return p->key;
  else
    return min(p->left);
}

bool BinarySearchTree::Erase(int x)
{
  return erase(x,root);
}

bool BinarySearchTree::erase(int x,BinaryNode* & p)
{
  if(p == NULL) return false;
  else if(p->key > x) return erase(x, p->left);
  else if(p->key < x) return erase(x, p->right);
  else{
    if(p->right != NULL){
      p->key = min(p->right);
      return erase(p->key,p->right);
    }
    else{
      BinaryNode* np = p;
      p = p->left;
      delete np;
      return true;
    }
  }
}

int main( )
{

  try {
      BinarySearchTree bst;

      bst.Insert(20);
      bst.Insert(30);
      bst.Insert(10);
      bst.Insert(40);
      bst.Insert(15);
      bst.Insert(12);
      bst.Show();

      cout << bst.Find(5)<<endl;
      cout << bst.Find(3)<<endl;

      cout << bst.Max()<<endl;
      cout << bst.Min()<<endl;

      cout <<"Input Delete Number"<< endl;
      int d;
      cin >> d;

      if(bst.Erase(d)){
	cout <<"Success"<< endl;
	}
      else{
	cout <<"False"<< endl;
      }

      cout <<"Input Search Number"<< endl;
      int f;
      cin >> f;
      
      if(bst.Find(f)) cout <<"Serch Success"<< endl;

  } catch ( bad_alloc ba ) {
      cout << "Memory Allocation Error !" << endl;
  } catch ( const char* msg ) {
      cout << msg << endl;
  }

  return 0;
}
