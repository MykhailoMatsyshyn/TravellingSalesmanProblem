// greedy.c

#include "graph.h"
#include "edge.h"

// ������� ��� ��������� ���� ����� (��� qsort)
int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return (edgeA->weight > edgeB->weight) - (edgeA->weight < edgeB->weight);
}

int findParent(int* parent, int vertex) {
    if (parent[vertex] == vertex) {
        return vertex;
    }
    return findParent(parent, parent[vertex]);
}

void unionVertices(int* parent, int vertex1, int vertex2) {
    int root1 = findParent(parent, vertex1);
    int root2 = findParent(parent, vertex2);
    parent[root1] = root2;
}

int createsCycle(int* parent, int vertex1, int vertex2) {
    int root1 = findParent(parent, vertex1);
    int root2 = findParent(parent, vertex2);

    if (root1 == root2) {
        return 1; // ���� �����������
    }

    unionVertices(parent, vertex1, vertex2);
    return 0; // ���� �� �����������
}


void greedyTSP(Graph* graph) {
    int numEdges = graph->numCities * (graph->numCities - 1) / 2;
    Edge* edges = malloc(numEdges * sizeof(Edge));
    int* parent = malloc(graph->numCities * sizeof(int));
    int* mstSet = calloc(graph->numCities, sizeof(int));

    // ����������� ������ ������
    for (int i = 0; i < graph->numCities; ++i) {
        parent[i] = i;
    }

    // ��������� ��� �������� �����
    int edgeIndex = 0;
    for (int i = 0; i < graph->numCities; ++i) {
        for (int j = i + 1; j < graph->numCities; ++j) {
            edges[edgeIndex].vertex1 = i;
            edges[edgeIndex].vertex2 = j;
            edges[edgeIndex].weight = graph->adjacency_matrix[i][j];
            edgeIndex++;
        }
    }

    // ���������� ����� �� �����
    qsort(edges, numEdges, sizeof(Edge), compareEdges);

    // ���� ����� ��� ��������
    int edgesInMST = 0;
    Edge* mstEdges = malloc((graph->numCities - 1) * sizeof(Edge)); // ����� ��� ��������� �������� �����

    for (int i = 0; edgesInMST < graph->numCities - 1 && i < numEdges; ++i) {
        if (!createsCycle(parent, edges[i].vertex1, edges[i].vertex2)) {
            mstEdges[edgesInMST++] = edges[i]; // ���������� ��������� �����
        }
    }

    // ��������� ��������
    printf("������� �������� ���������:\n");
    for (int i = 0; i < edgesInMST; ++i) {
        printf("(%d, %d) - %.2f\n", mstEdges[i].vertex1, mstEdges[i].vertex2, mstEdges[i].weight);
    }

    free(edges);
    free(parent);
    free(mstSet);
    free(mstEdges);
}

// ��� ����� ������ �������� ������� �� ����������
