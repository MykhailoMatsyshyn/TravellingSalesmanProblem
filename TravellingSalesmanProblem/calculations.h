#pragma once
#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#define _USE_MATH_DEFINES 
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>

// Радіус Землі в кілометрах
#define EARTH_RADIUS 6371.0

// Функція обчислення відстані за формулою Гаверсинуса
double haversine(double lat1, double lon1, double lat2, double lon2);


#endif /* CALCULATIONS_H */