

#if !defined(HFUNC_H)
#define HFUNC_H

#define  EXPORTFFUNC  __declspec(dllexport)

// File hfunc.c
EXPORTFFUNC void Hfunc1(int* family,int* n,double* u,double* v,double* theta,double* nu,double* out);
EXPORTFFUNC void Hfunc1_vec(int* family,int* n,double* u,double* v,double* theta,double* nu,double* out);
EXPORTFFUNC void Hfunc2(int* family,int* n,double* v,double* u,double* theta,double* nu,double* out);
EXPORTFFUNC void Hfunc2_vec(int* family,int* n,double* u,double* v,double* theta,double* nu,double* out);
EXPORTFFUNC void Hfunc(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out);

// EXPORTFFUNC void Hinv1(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out);


EXPORTFFUNC double* Hinv1(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out);
// #SUJAYGHOSH Added new function definition
//EXPORTFFUNC double getAverage(int* arr, int size);

EXPORTFFUNC void HinvNew(int family, int n, double u, double v, double theta, double nu, double out);

EXPORTFFUNC void Hinv1_vec(int* family, int* n, double* u, double* v, double*eta, double* nu, double* out);
EXPORTFFUNC void Hinv2(int* family, int* n, double* v, double* u, double* theta, double* nu, double* out);
EXPORTFFUNC void Hinv2_vec(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out);
EXPORTFFUNC void Hinv(int* family, int* n, double* u, double* v, double* theta, double* nu, double* out);
EXPORTFFUNC void HNumInv(int* family, double* u, double* v, double* theta, double* nu, double* out);
EXPORTFFUNC void pcondbb1(double* u, double* v, int* n, double* param, double* out);
EXPORTFFUNC void pcondbb6(double* u, double* v, int* n, double* param, double* out);
EXPORTFFUNC void pcondbb7(double* u, double* v, int* n, double* param, double* out);
EXPORTFFUNC void pcondbb8(double* u, double* v, int* n, double* param, double* out);
EXPORTFFUNC void qcondgum(double* q, double* u, double* de, double* out);
EXPORTFFUNC void qcondjoe(double* q, double* u, double* de, double* out);
//void qcondbb1(double* q, double* u, double* de, double* th, double* out);

#endif
