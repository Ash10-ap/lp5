#include <iostream>
#include <queue>
#include <omp.h>

// Function to perform BFS using OpenMP
void BFS_OpenMP(int** graph, int numVertices, int startVertex) {
    bool* visited = new bool[numVertices];
    for (int i = 0; i < numVertices; ++i)
        visited[i] = false;

    std::queue<int> queue;
    visited[startVertex] = true;
    queue.push(startVertex);

    #pragma omp parallel
    {
        while (!queue.empty()) {
            int currentVertex;

            #pragma omp critical
            {
                currentVertex = queue.front();
                queue.pop();
            }

            std::cout << "Visited vertex: " << currentVertex << std::endl;

            #pragma omp for
            for (int i = 0; i < numVertices; ++i) {
                if (graph[currentVertex][i] && !visited[i]) {
                    visited[i] = true;

                    #pragma omp critical
                    queue.push(i);
                }
            }
        }
    }

    delete[] visited;
}

int main() {
    int numVertices = 6;
    int** graph = new int*[numVertices];
    for (int i = 0; i < numVertices; ++i)
        graph[i] = new int[numVertices];

    // Initialize the graph
    for (int i = 0; i < numVertices; ++i)
        for (int j = 0; j < numVertices; ++j)
            graph[i][j] = 0;

    // Add edges
    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[1][4] = 1;
    graph[2][4] = 1;
    graph[3][4] = 1;
    graph[3][5] = 1;
    graph[4][5] = 1;

    int startVertex = 0;
    std::cout << "BFS traversal starting from vertex " << startVertex << ":\n";
    BFS_OpenMP(graph, numVertices, startVertex);

    for (int i = 0; i < numVertices; ++i)
        delete[] graph[i];
    delete[] graph;

    return 0;
}

