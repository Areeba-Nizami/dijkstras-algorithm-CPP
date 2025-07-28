#include <iostream>
#include <climits>
#include <string>

using namespace std;

#define MAX_PLACES 6

void display_city_map(int adj[MAX_PLACES][MAX_PLACES], string places[MAX_PLACES]);  // Displays the map of the city

int select_min_node(int dist[], bool visited[], int V);     // Selection of node with minimum distance to implement dijkstras algorithm

void dijkstra(int V, int adj[MAX_PLACES][MAX_PLACES], int start, int end, string places[MAX_PLACES]);   // implementation of dijkstras algorithm

int main()
{
    int V = 6;

    string places[MAX_PLACES] =
    {
        "university", "airport", "mall", "park", "hospital", "library"
    };

    int adj[MAX_PLACES][MAX_PLACES] =
    {
        {0, 10, 5, 6, INT_MAX, INT_MAX},    // INT_MAX is the largest integer in c++ (infinity)
        {10, 0, 2, 7, INT_MAX, INT_MAX},
        {5, 2, 0, 2, 3, INT_MAX},
        {6, 7, 2, 0, 4, 3},
        {INT_MAX, INT_MAX, 3, 4, 0, 6},
        {INT_MAX, INT_MAX, INT_MAX, 3, 6, 0}
    };

    display_city_map(adj, places);

    string startPlace, endPlace;
    cout << "Enter start place: ";
    cin >> startPlace;
    cout << "Enter end place: ";
    cin >> endPlace;

    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < V; i++)
    {
        if (places[i] == startPlace) startIndex = i;
        if (places[i] == endPlace) endIndex = i;
    }

    if (startIndex == -1 || endIndex == -1)
    {
        cout << "Invalid place names entered.\n";
        return 1;
    }

    dijkstra(V, adj, startIndex, endIndex, places);

    return 0;
}


void display_city_map(int adj[MAX_PLACES][MAX_PLACES], string places[MAX_PLACES]) {
    cout << "\nCity Map (Diagrammatic View):\n";
    cout << "---------------------------------------------------------\n";
    cout << "|     University---(10)---Airport   |\n";
    cout << "|           | \\        / |          |\n";
    cout << "|           |   \\    /   |          |\n";
    cout << "|         (5)    \\ /    (7)         |\n";
    cout << "|           |  (2)  (6)  |          |\n";
    cout << "|           | /        \\ |          |\n";
    cout << "|         Mall---(2)---Park         |\n";
    cout << "|           | \\       /  |          |\n";
    cout << "|           |   \\   /    |          |\n";
    cout << "|         (3)    \\/\\    (3)         |\n";
    cout << "|           |  (4)   (5) |          |\n";
    cout << "|           | /        \\ |          |\n";
    cout << "|      Hospital---(6)---Library     |\n";
    cout << "---------------------------------------------------------\n";

    cout << "\nNode List:\n";
    for (int i = 0; i < MAX_PLACES; i++) {
        cout << i + 1 << ". " << places[i] << "\n";
    }
    cout << "\n---------------------------------------------------------\n";
}


int select_min_node(int dist[], bool visited[], int V)
{
    int min_dist = INT_MAX;    // Set to maximum initially
    int min_node = -1;     // set to -1 as no node is found yet (index -1 does not exist)
    for (int i = 0; i < V; i++) {
        if (!visited[i] && dist[i] < min_dist)
        {
            min_dist = dist[i];
            min_node = i;
        }
    }
    return min_node;
}


void dijkstra(int V, int adj[MAX_PLACES][MAX_PLACES], int start, int end, string places[MAX_PLACES]) {
    int dist[MAX_PLACES];
    bool visited[MAX_PLACES] = { false };
    int prev[MAX_PLACES] = { -1 };

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        int u = select_min_node(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (adj[u][v] != INT_MAX && !visited[v] && dist[u] != INT_MAX && dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[end] == INT_MAX)
    {
        cout << "No path exists between " << places[start] << " and " << places[end] << ".\n";
    }
    else
    {
        cout << "\nShortest distance from " << places[start] << " to " << places[end] << ": " << dist[end] << " km\n";
        string path = places[end];
        int node = end;
        while (prev[node] != -1)
        {
            node = prev[node];
            path = places[node] + " -> " + path;
        }
        cout << "Shortest Path: " << path << endl;
    }
}

