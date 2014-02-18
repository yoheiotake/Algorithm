#include<iostream>
#include<string>
#include<list>
#include<queue>
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
  bool flag;
  double value;
  Vertex* prev;
      
  Vertex( string n );

  void AddAdjacent( Vertex* v, double w )
  { adj_list.push_back( Adjacent( v, w ) ); };
  void PrintAdjList( );
  void Reset();

  friend class Graph;
};


Vertex::Vertex(string n){
  name = n;
  flag = false;
  value = 0;
  prev = NULL;
}

void Vertex::Reset(){
  flag = false;
  value = 0;
  prev = NULL;
}

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
  void dfs(Vertex* v);

public:
  Graph ( ) : n_vertex(0), n_edge(0) { };
  void AddEdge( string v1, string v2, double weight );
  void PrintAdjList( );
  void Reset();
  void DFS(string start);
  void PrintSpanTree();
  void BFS(string start);
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

void Graph::Reset(){
  map<string,Vertex*>::const_iterator itr;
  for(itr = vmap.begin(); itr != vmap.end(); itr++){
    itr -> second -> Reset();
  }
}

void Graph::dfs(Vertex* v){
  list<Adjacent>::iterator itr;
  for(itr = v -> adj_list.begin(); itr != v -> adj_list.end(); itr++){
    if(itr -> vertex -> flag) continue;
    itr -> vertex -> value = itr -> weight;
    itr -> vertex -> prev = v;
    itr -> vertex -> flag = true;
    dfs(itr -> vertex);
  }
}

void Graph::DFS(string start){
  map<string,Vertex*>::iterator itr;
  itr = vmap.find(start);
  if(itr == vmap.end() || itr -> second -> flag) return;
  itr -> second -> flag = true;
  dfs(itr -> second);
}

void Graph::PrintSpanTree(){
  map<string,Vertex*>::iterator itr;
  for(itr = vmap.begin(); itr != vmap.end(); itr++){
    if(itr -> second -> prev == NULL) continue;
    cout << itr -> second -> prev -> name <<"-("
         << itr -> second -> value <<")-"
         << itr -> second -> name << endl;
  }
}

void Graph::BFS(string start){
  queue<Adjacent> q;
  map<string,Vertex*>::iterator itr;
  list<Adjacent>::iterator itrl;
  itr = vmap.find(start);
  itr -> second -> flag = true;

  while(true){
    itrl = itr -> second -> adj_list.begin();
    for(; itrl != itr -> second -> adj_list.end(); itrl++){
      if(itrl -> vertex -> flag) continue;
      q.push(*itrl);
      itrl -> vertex -> flag = true;
      itrl -> vertex -> value = itrl -> weight;
      itrl -> vertex -> prev = itr -> second;
    }
    if(q.empty()) break;
    itr = vmap.find(q.front().vertex -> name);
    q.pop();
  }
  return;
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

  g.Reset();
  g.DFS( "A" );       // 深さ優先探索
  g.PrintSpanTree();
  cout << endl;

  g.Reset();
  g.BFS( "A" );      // 課題２ 幅優先探索ではここを実行する。
  g.PrintSpanTree();
  cout << endl;

  //g.Reset();
  //g.UWSP( "A" );     // 課題３ 重みなし最短経路ではここを実行する。
  //g.PrintPath();
  //cout << endl;

  return 0;
} 
