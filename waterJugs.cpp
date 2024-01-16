/*
 * Name:            Noah Nininger
 * Date Submitted:  04/25/2023
 * Lab Section:     001
 * Assignment Name: Lab 10
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
  //Implement this function
  state currentState = make_pair(0, 0);
  int jugA = 3, jugB = 4;
  state end = make_pair(jugA, jugB);

  while (currentState != end)
  {
    state next;

   // fill jug A
    next = make_pair(jugA, currentState.second);
    if (next != currentState)
    {
      pair<state, state> edge = make_pair(currentState, next);
      nbrs[currentState].push_back(next);
      edge_label[edge] = actions[0];
    }

   // fill jug B
    next = make_pair(currentState.first, jugB);
    if (next != currentState)
    {
      pair<state, state> edge = make_pair(currentState, next);
      nbrs[currentState].push_back(next);
      edge_label[edge] = actions[1];
    }

   // empty jug A
    next = make_pair(0, currentState.second);
    if (next != currentState)
    {
      pair<state, state> edge = make_pair(currentState, next);
      nbrs[currentState].push_back(next);
      edge_label[edge] = actions[2];
    }

   // empty jug B
    next = make_pair(currentState.first, 0);
    if (next != currentState)
    {
      pair<state, state> edge = make_pair(currentState, next);
      nbrs[currentState].push_back(next);
      edge_label[edge] = actions[3];
    }

   // pour jug A into jug B
    int jugA2 = currentState.first;
    int jugB2 = currentState.second;
    if(currentState.second < jugB)
    {
      while (jugA2 > 0 && jugB2 < jugB)
      {
        jugB2++;
        jugA2--;
      }

      next = make_pair(jugA2,jugB2);

      if (next != currentState)
      {
        pair<state, state> edge = make_pair(currentState, next);
        nbrs[currentState].push_back(next);
        edge_label[edge] = actions[4];
      }
    }

   // pour jug B into jug A
    jugA2 = currentState.first;
    jugB2 = currentState.second;
    if (currentState.first < jugA)
    {
      while (jugA2 < jugA && jugB2 > 0)
      {
        jugA2++;
        jugB2--;
      }

      next = make_pair(jugA2, jugB2);

      if (next != currentState)
      {
        pair<state, state> edge = make_pair(currentState, next);
        nbrs[currentState].push_back(next);
        edge_label[edge] = actions[5];
      }
    }

    if (currentState.second == jugB)
      { currentState = make_pair(currentState.first + 1, 0); }
    else
      { currentState = make_pair(currentState.first, currentState.second + 1); }
  }
}
/*
int main(void)
{
  build_graph();

  state start = make_pair(0, 0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i, 5-i)].push_back(make_pair(-1, -1));
  search (start);
  if (visited[make_pair(-1, -1)]) 
    print_path (start, pred[make_pair(-1, -1)]);
  else
    cout << "No path!\n";
  
  return 0;
}*/
