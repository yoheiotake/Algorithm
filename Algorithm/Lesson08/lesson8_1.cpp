#include<iostream>
#include<string>
#include<list>
#include<queue>
#include<map>
#include<algorithm>
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
  void PrintPath(Vertex* v);

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

void Vertex::PrintPath(Vertex* v){
  if(v -> prev != NULL) PrintPath(v -> prev);
  if(v -> prev != NULL) cout <<"->";
  cout << v -> name;
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
  void UWSP(string start);
  void PrintPath();
  bool TopoCheck(const vector<string> & v_list);
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

void Graph::UWSP(string start){
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
      itrl -> vertex -> value = itr -> second -> value + 1;
      itrl -> vertex -> prev = itr -> second;
    }
    if(q.empty()) break;
    itr = vmap.find(q.front().vertex -> name);
    q.pop();
  }
  return;
}

void Graph::PrintPath(){
  map<string,Vertex*>::const_iterator itr;
  for(itr = vmap.begin(); itr != vmap.end(); itr++){
    itr -> second -> PrintPath(itr -> second);
    cout <<":"<< itr -> second -> value << endl;
  }

  return;
}


bool Graph::TopoCheck(const vector<string> & v_list){

  map< Vertex*, int > v_order;

  for( int i = 0; i < v_list.size(); ++ i ) {
    v_order[ vmap[ v_list[ i ] ] ] = i;
  }

  list<Adjacent>::const_iterator itr;
  for(int i = 0; i < v_list.size(); ++i){
    for( itr = vmap[ v_list[i] ] -> adj_list.begin(); itr != vmap[ v_list[i] ] -> adj_list.end(); ++itr)
      if( v_order[vmap[ v_list[i] ]] > v_order[itr -> vertex]) return false;
  }
  return true;
}




int main()
{
  Graph g;

  g.AddEdge( "A", "B", 1.0 );
  g.AddEdge( "A", "C", 1.0 ); 
  g.AddEdge( "B", "D", 1.0 ); 
  g.AddEdge( "C", "D", 1.0 ); 

  vector<string>  v_list;

  v_list.push_back( "A" );
  v_list.push_back( "C" );
  v_list.push_back( "B" );
  v_list.push_back( "D" );

  cout << g.TopoCheck( v_list ) << endl;

  v_list.clear();
  v_list.push_back( "A" );
  v_list.push_back( "B" );
  v_list.push_back( "C" );
  v_list.push_back( "D" );

  cout << g.TopoCheck( v_list ) << endl;

  v_list.clear();
  v_list.push_back( "A" );
  v_list.push_back( "B" );
  v_list.push_back( "D" );
  v_list.push_back( "C" );

  cout << g.TopoCheck( v_list ) << endl;

  return 0;
} 
