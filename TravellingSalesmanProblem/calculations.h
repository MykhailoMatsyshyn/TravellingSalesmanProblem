#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "graph.h";

// Радіус Землі в кілометрах
#define EARTH_RADIUS 6371.0

// Функція обчислення відстані за формулою Гаверсинуса
double haversine(double lat1, double lon1, double lat2, double lon2);


#endif /* CALCULATIONS_H */