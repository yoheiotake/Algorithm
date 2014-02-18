#include<iostream>
#include<string>
#include<list>
#include<map>
using namespace std;

class Vertex;

class Adjacent {
  Vertex*  vertex;
  double   weight;

public:
  Adjacent( Vertex* v, double w ) : vertex(v), weight(w) { }; 
  Adjacent( ) : vertex(NULL), weight(0.0) { }; 

  friend class Vertex;
  friend class Graph;
};

class Vertex {

  string           name;
  list<Adjacent>   adj_list;
      
  Vertex( string n ) : name(n) { };

  void AddAdjacent( Vertex* v, double w )
  { adj_list.push_back( Adjacent( v, w ) ); };
  void PrintAdjList( );

  friend class Graph;
};


void Vertex::PrintAdjList( )
{
  list<Adjacent>::const_iterator itr;
  cout << name <<':';
  for(itr = adj_list.begin(); itr != adj_list.end(); itr++)
    cout << itr -> vertex -> name <<'('<< itr -> weight <<')';
  cout << endl;
}

class Graph {

  map  < string, Vertex* > vmap;
  int   n_vertex;
  int   n_edge;

public:
  Graph ( ) : n_vertex(0), n_edge(0) { };
  void AddEdge( string v1, string v2, double weight );
  void PrintAdjList( );

};


void Graph::AddEdge( string v1name, string v2name, double weight )
{   
  if ( vmap.find(v1name) == vmap.end() ) {
    vmap[ v1name ] = new Vertex( v1name );
    n_vertex++;
  }
  if ( vmap.find(v2name) == vmap.end() ) {
    vmap[ v2name ] = new Vertex( v2name );
    n_vertex++;
  }
  vmap[ v1name ] ->AddAdjacent( vmap[ v2name ], weight );
  n_edge++;
}

void Graph::PrintAdjList()
{
  map<string,Vertex*>::const_iterator itr;
  for(itr = vmap.begin(); itr != vmap.end(); itr++)
    itr -> second -> PrintAdjList();
}


int main()
{
  Graph g;

  g.AddEdge( "A", "B", 2.0 );
  g.AddEdge( "C", "A", 4.0 );
  g.AddEdge( "A", "D", 1.0 );
  g.AddEdge( "B", "D", 3.0 );
  g.AddEdge( "B", "E", 10.0 );
  g.AddEdge( "C", "F", 5.0 );
  g.AddEdge( "D", "C", 2.0 );
  g.AddEdge( "D", "E", 2.0 );
  g.AddEdge( "D", "F", 8.0 );
  g.AddEdge( "D", "G", 4.0 );
  g.AddEdge( "E", "G", 6.0 );
  g.AddEdge( "G", "F", 1.0 );

  g.PrintAdjList();
  cout << endl;

  return 0;
} 
