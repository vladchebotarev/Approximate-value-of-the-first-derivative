// MO_Lab8v2.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <iomanip>
#include <math.h>
#include <fstream>
#include <typeinfo>
#include <string>

using namespace std;
const int iter = 16;	//liczba kroków
const int methods = 9;	//liczba wywo³añ funkcji (2 dla pocz¹tku, 3 dla œrodka i 2 koñca przedzia³u)

template <typename T>
T pochodna(T x)
{
	return -sin(x);
}

template <typename T> T roznica_progresywna(T x, T krok)
{
	return (cos(x + krok) - cos(x)) / krok;
}

template <typename T> T roznica_wsteczna(T x, T krok)
{
	return (cos(x) - cos(x - krok)) / krok;
}

template <typename T> T roznica_centralna(T x, T krok)
{
	return (cos(x + krok) - cos(x - krok)) / (2.0*krok);
}

template <typename T> T roznica_progresywna_trzypunktowa(T x, T krok)
{
	return (-3.0 / 2.0*cos(x) + 2.0*cos(x + krok) - 1.0 / 2.0*cos(x + 2.0*krok)) / krok;
}

template <typename T> T roznica_wsteczna_trzypunktowa(T x, T krok)
{
	return (1.0 / 2.0*cos(x - 2.0*krok) - 2.0*cos(x - krok) + 3.0 / 2.0*cos(x)) / krok;
}



template <typename T> void oblicz(T *krok, T **wynik)
{
	T pocz = 0.0, srodek = M_PI_4, kon = M_PI_2, h = 0.1;



	for (int i = 0; i < iter; i++)//blad odciecia
	{
		krok[i] = h;
		wynik[0][i] = fabs(pochodna(pocz) - roznica_progresywna(pocz, h));
		wynik[1][i] = fabs(pochodna(pocz) - roznica_progresywna_trzypunktowa(pocz, h));


		wynik[2][i] = fabs(pochodna(srodek) - roznica_progresywna(srodek, h));
		wynik[3][i] = fabs(pochodna(srodek) - roznica_centralna(srodek, h));
		wynik[4][i] = fabs(pochodna(srodek) - roznica_wsteczna(srodek, h));
		wynik[5][i] = fabs(pochodna(srodek) - roznica_progresywna_trzypunktowa(srodek, h));
		wynik[6][i] = fabs(pochodna(srodek) - roznica_wsteczna_trzypunktowa(srodek, h));


		wynik[7][i] = fabs(pochodna(kon) - roznica_wsteczna(kon, h));
		wynik[8][i] = fabs(pochodna(kon) - roznica_wsteczna_trzypunktowa(kon, h));



		
		h *= 0.1; // za kazdym razem zmniejszamy krok
	}
	

}

void nazwykolumn()
{
	cout << " -----------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|";
	cout.width(5);
	cout << "h|"; //numer kroku
	cout.width(12);
	cout << "x0 -PRO |"; //poczatkowy- progresywna
	cout.width(12);
	cout << "x0 - PRO3 |"; //poczatkowy- progresywna 3-punktowa
	cout.width(12);
	cout << "xs - PRO |"; //srodkowy- progresywna
	cout.width(12);
	cout << "xs - CEN |"; //srodkowy- centralna
	cout.width(12);
	cout << "xs - WST |";//srodkowy- wsteczna
	cout.width(12);
	cout << "xs - PRO3 |";//srodkowy- progresywna 3-punktowa
	cout.width(12);
	cout << "xs - WST3 |";//srodkowy- wsteczna 3-punktowa
	cout.width(12);
	cout << "xn - WST |"; //koncowy- wsteczna
	cout.width(12);
	cout << "xn - WST3 |" << endl;//konczowy- wsteczna 3-punktowa
	cout << " -----------------------------------------------------------------------------------------------------------------" << endl;
}

template <typename T> void zapisz(T *krok, T **wynik)
{

	fstream file;
	string nazwa = typeid(T).name();	//pobieranie nazwy typu danych- double float
	cout << "TYP: " << nazwa << endl;
	nazwa += ".txt"; //rozszerzenie
	file.open(nazwa, ios::out);

	if (file.good())
	{

		nazwykolumn();
		for (int i = 0; i<iter; i++)
		{
			cout.width(5);
			cout << log10(krok[i]);
			file << log10(krok[i]);
			file <<"\t";

			for (int j = 0; j< methods; j++)
			{
				cout.width(12);
				cout << log10(wynik[j][i]);
				file << log10(wynik[j][i]);//zapis do excela
				file << " ";
			}
			file << endl;
			cout << endl;
		}
		cout << endl << "\t\t\t\t---Wyniki zostaly zapisane do pliku: " << nazwa << ".---" << endl << endl;
	}
	else
		cout << "Error\n";
	file.close();
}

int main()
{
	double **wynikd;
	double *krokd;
	float **wynikf;
	float *krokf;

	krokd = new double[iter];
	krokf = new float[iter];
	wynikd = new double*[methods];
	wynikf = new float*[methods];
	for (int i = 0; i<methods; i++)
	{
		wynikd[i] = new double[iter];
		wynikf[i] = new float[iter];
	}
	oblicz(krokd, wynikd);
	oblicz(krokf, wynikf);
	zapisz(krokd, wynikd);
	zapisz(krokf, wynikf);

	system("PAUSE");
	return 0;
}