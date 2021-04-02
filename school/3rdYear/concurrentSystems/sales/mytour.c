#include "mytour.h"

void standard_my_tour(const point cities[], int tour[], int ncities) {
  simple_find_tour(cities, tour, ncities);
}

void my_tour(const point cities[], int tour[], int ncities) {
  simple_find_tour(cities, tour, ncities);
}

/* Flow:
 *  basic flow of the simple_find_tour is 
*/

float sqr(float x) {
  return x * x;
}

float dist(const point cities[], int i, int j) {
  return sqrt(sqr(cities[i].x - cities[j].x) + sqr(cities[i].y - cities[j].y));
}

void find_tour(const point cities[], int tour[], int ncities) {
  int i , j;
  char *visited = alloca(ncities);
  int ThisPt, ClosePt = 0;
  float CloseDist;
  int endtour = 0;

  for(i = 0; i < ncities; i++) {
    visited[i] = 0;
  }
  ThisPt = ncities - 1;
  visited[ncities-1] = 1;
  tour[endtour++] = ncities - 1;

  for(i = 1; i < ncities; i++) {
    CloseDist = DBL_MAX;
    for(j = 0; j < ncities - 1; j++) {
      if(!visited[j]) {
        if(dist(cities, ThisPt, j) < CloseDist) {
          CloseDist = dist(cities, ThisPt, j);
          ClosePt = j;
        }
      }
    }
    tour[endtour++] = ClosePt;
    visited[ClosePt] = 1;
    ThisPt = ClosePt;
  }
}