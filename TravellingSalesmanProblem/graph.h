#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#define _USE_MATH_DEFINES 
#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// ʳ������ ������������ ��� ��� �����
#define MAX_CITIES 50

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