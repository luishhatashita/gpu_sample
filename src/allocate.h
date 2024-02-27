#ifndef ALLOCATE_H
#define ALLOCATE_H

void allocate1d(int nx, int ny, double*& newarr);
void allocate2d(int nx, int ny, double**& newarr);
void deallocate1d(double*& newarr);
void deallocate2d(int nx, double**& newarr);

#endif
