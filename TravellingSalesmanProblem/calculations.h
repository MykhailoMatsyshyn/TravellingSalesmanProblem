#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "graph.h";

// ����� ���� � ���������
#define EARTH_RADIUS 6371.0

// ������� ���������� ������ �� �������� �����������
double haversine(double lat1, double lon1, double lat2, double lon2);


#endif /* CALCULATIONS_H */