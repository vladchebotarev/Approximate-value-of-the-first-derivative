// Lab_8.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

#include <Windows.h>
#include <cmath>
#include <fstream>
#include <string>
#include <typeinfo>
//#include "gnuplot-iostream-master/gnuplot-iostream.h"

using namespace std;
const long double  M_PI = 3.141592653589793238462643383279502884197169399375;
//Gnuplot gnp;
const int N = 20;	//liczba iteracji
const int M = 7;	//liczba metod

template <typename T>
T roznicaWsteczna(T x, T h)
{
	return (cos(x) - cos(x - h)) / h;
}

template <typename T>
T roznicaCentralna(T x, T h)
{
	return (cos(x + h) - cos(x - h)) / (2.0 * h);
}

template <typename T>
T roznicaProgresywna(T x, T h)
{
	return (cos(x + h) - cos(x)) / h;
}

template <typename T>
T roznicaProgresywnaTrzypunktowa(T x, T h)
{
	return (-3.0 * cos(x) + 4.0 * cos(x + h) - cos(x + (2.0 * h))) / (2.0* h);
}

template <typename T>
T roznicaWstecznaTrzypunktowa(T x, T h)
{
	return (cos(x - (2 * h)) - 4.0 * cos(x - h) + 3.0 * cos(x)) / (2.0* h);
}



template <typename T>
void obliczenia(T *kroki, T **wyniki)
{
	T x_pocz = 0.0;
	T x_sr = M_PI / 4;
	T x_kon = M_PI / 2;
	T krok = 0.1;

	for (int i = 0; i < N; i++)
	{
		kroki[i] = krok;

		wyniki[0][i] = fabs(sin(x_pocz)*(-1) - roznicaProgresywna(x_pocz, krok));
		wyniki[1][i] = fabs(sin(x_pocz)*(-1) - roznicaProgresywnaTrzypunktowa(x_pocz, krok));

		wyniki[2][i] = fabs(sin(x_sr)*(-1) - roznicaProgresywna(x_sr, krok));
		wyniki[3][i] = fabs(sin(x_sr)*(-1) - roznicaCentralna(x_sr, krok));
		wyniki[4][i] = fabs(sin(x_sr)*(-1) - roznicaWsteczna(x_sr, krok));

		wyniki[5][i] = fabs(sin(x_kon)*(-1) - roznicaWsteczna(x_kon, krok));
		wyniki[6][i] = fabs(sin(x_kon)*(-1) - roznicaWstecznaTrzypunktowa(x_kon, krok));

		krok *= 0.1;
	}
}




template <typename T> void wyswietlanie(T *kroki, T **wyniki)
{
	cout << "  h  | rozProg(x_pocz) | rozProgTrzyp(x_pocz) | rozProg(x_sr)| rozCent(x_sr) | rozWstecz(x_sr) | rozWstecz(x_kon) | roznWsteczTrzyp(x_kon) |" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout.width(5);
		cout << log10(kroki[i]) << "|";
		for (int j = 0; j < M; j++)
		{
			cout.width(15);
			cout << log10(wyniki[j][i]) << "|";
		}
		cout << endl;
	}
}

template <typename T> void zapis_danych(T *kroki, T **wyniki, string filename)
{
	fstream plik;


	cout << "Zapisuje dane do pliku." << endl;

	plik.open(filename, fstream::out);

	
	for (int i = 0; i < N; i++)
	{

		plik << log10(kroki[i]) << " ";

		for (int j = 0; j < M; j++)
		{
			plik.width(15);
			plik << log10(wyniki[j][i]);
		}
		plik << endl;
	}
	plik.close();
}


int _tmain(int argc, _TCHAR* argv[])
{

	float *krokif;
	float **wynikif;

	double *krokid;
	double **wynikid;

	krokif = new float[N];
	wynikif = new float *[M];

	krokid = new double[N];
	wynikid = new double *[M];

	for (int i = 0; i < M; i++)
	{
		wynikif[i] = new float[N];
		wynikid[i] = new double[N];
	}

	cout << "log10 BLEDY BEZWZGLEDNE:\n\nFLOAT:\n";
	obliczenia(krokif, wynikif);
	wyswietlanie(krokif, wynikif);

	cout << "\n\nDOUBLE:\n";
	obliczenia(krokid, wynikid);
	wyswietlanie(krokid, wynikid);

	zapis_danych(krokif, wynikif, "float.log");
	zapis_danych(krokid, wynikid, "double.log");
	//gnp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	
	//gnp << "plot" << gp.file1d(xy_pts_A) << "with lines title 'cubic',"<< gp.file1d(xy_pts_B) << "with points title 'circle'" << std::endl;

	delete[] krokif;
	delete[] krokid;
	delete[] wynikif;
	delete[] wynikid;

	system("pause");
	return 0;
}

