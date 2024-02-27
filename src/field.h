#ifndef FIELD_H
#define FIELD_H

void initializeField1d(int nx, int ny, double*& arr, double* bc, double fill); 
void initializeField2d(int nx, int ny, double**& arr, double* bc, double fill);
void computeField1d   (int nx, int ny, double*& arr, double*& arrnew, double& error);
void computeField2d   (int nx, int ny, double**& arr, double**& arrnew, double& error);
void updateField1d    (int nx, int ny, double*& arr, double*& arrnew);
void updateField2d    (int nx, int ny, double**& arr, double**& arrnew);

#endif
