#pragma once
#ifndef GRAPH_H
#define GRAPH_H 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "calculations.h"

// ʳ������ ������������ ��� ��� �����
#define MAX_CITIES 120
#define N_TO_PRINT 15

// ��������� ��� ��������� ��������� ���
typedef struct {
    int num;
    char name[50];
    double latitude;
    double longitude;
} City;

// ��������� ��� ��������� �����
typedef struct {
    int numCities;
    City cities[MAX_CITIES];
    double adjacency_matrix[MAX_CITIES][MAX_CITIES];
} Graph;

void initializeGraph(Graph* graph);
void addCity(Graph* graph, char* name, double latitude, double longitude);
void addEdge(Graph* graph, int city1, int city2, double distance);
void calculateDistances(Graph* graph);

void printGraph(Graph* graph);


#endif /* GRAPH_H */