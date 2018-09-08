#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct form // Структура формата
{
	string type;
	string date;
	string time;
	double lat1;
	string lat2;
	double lon1;
	string lon2;
	int speed;
	int course;
	int hight;
	int sats;
	string data;
};


string DataS(int &i,string &s);
void GetData(form *F, int N);
void ShowData(form *F, int N);

int main()
{
	SetConsoleCP(1251);  // Региональные параметры
	SetConsoleOutputCP(1251);
	int N;
	cout << "Введите кол-во строк: ";
	cin >> N;
	form *F = new form[N];
	
	GetData(F, N); //ПП ввода
	ShowData(F, N); //ПП вывести данные

	delete[]F;
	system("Pause"); // Пауза для консоли
	return 0;
}

string DataS(int &i,string &s) 
{ // Подрограмма переноса символов в нужную строку
	string str;
	int len = s.length(); // Определяем длинну строки
	while ((i < len)&&(s[i] != ';')&&(s[i]!='\r')&&(s[i]!='\n')) 
		{ // Переносим до ';' или конца файла или пока не дойдем до \r\n
			str += s[i];
			i++;
		}
	i++;
	return str;
}

void GetData(form *F, int N) 
{
	int i;
	string s;
	cin.ignore();
	for (int j = 0; j < N; j++) 
	{
		cout << "Введите строку " << j <<" : "  << endl; // Вводим строку
		getline(cin, s);
		s += '\r';  // Добавляем в конце \r\n
		s += '\n';
		cout << endl;  // Перенос строки

		int pos = 0; // Сброс позиции первого вхождения
		pos = s.find("#M#"); // Ищем совпадение
		if (pos == 0)
		{  // Первое вхождение в начале
			F[j].type = "M";
			F[j].data = s.substr(3); // Переносим данные в formM1		
		}

		pos = 0; //Сброс позиции первого вхождения
		pos = s.find("#SD#"); // Ищем совпадение
		if (pos == 0)
		{ // Первое вхождение в начале
			F[j].type = "SD";
			int i = 4; // Указатель на 4 символ
			F[j].date = DataS(i, s); // Переносим данные в нужные строки
			F[j].time = DataS(i, s);
			string slat1 = DataS(i, s);
			F[j].lat2 = DataS(i, s);
			string slon1 = DataS(i, s);
			F[j].lon2 = DataS(i, s);
			string sspeed = DataS(i, s);
			string scourse = DataS(i, s);
			string shight = DataS(i, s);
			string ssats = DataS(i, s);
			try
			{
				F[j].lat1 = round(stod(slat1) * 10000) / 10000;
			}
			catch (const std::exception&)
			{
				cerr << "Ошибка преобразования" << endl;
			}
			try
			{
				F[j].lon1 = round(stod(slon1) * 10000) / 10000;
			}
			catch (const std::exception&)
			{
				cerr << "Ошибка преобразования" << endl;
			}
			try
			{
				F[j].speed = stoi(sspeed);
			}
			catch (const std::exception&)
			{
				cerr << "Ошибка преобразования" << endl;
			}
			try
			{
				F[j].course = stoi(scourse);
			}
			catch (const std::exception&)
			{
				cerr << "Ошибка преобразования" << endl;
			}
			try
			{
				F[j].hight = stoi(shight);
			}
			catch (const std::exception&)
			{
				cerr << "Ошибка преобразования" << endl;
			}
			try
			{
				F[j].sats = stoi(ssats);
			}
			catch (const std::exception&)
			{
				cerr << "Ошибка преобразования" << endl;
			}
		}

	}
}

void ShowData(form *F, int N)
{
	for (int j = 0; j < N; j++)
	{
		cout << "Данные строки " << j << " : " << endl;
		cout << endl;
		if (F[j].type == "M")
		{
			cout << "Поле DATA: " << F[j].data << endl; //Выводим на экран
		}
		if (F[j].type == "SD")
		{
			cout << "Дата: " << F[j].date[0] << F[j].date[1]; // Выводим дату
			cout << "/";
			cout << F[j].date[2] << F[j].date[3];
			cout << "/";
			cout << F[j].date[4] << F[j].date[5] << F[j].date[6] << F[j].date[7] << endl; 
			cout << "Время: " << F[j].time[0] << F[j].time[1]; // Выводим время
			cout << ":";
			cout << F[j].time[2] << F[j].time[3];
			cout << ":";
			cout << F[j].time[4] << F[j].time[5] << endl;
			cout << "Широта: " << setprecision(4) << fixed << F[j].lat1; //Выводим широту
			cout << F[j].lat2 << endl; //N
			cout << "Долгота: " << F[j].lon1; //Выводим долготу
			cout << F[j].lon2 << endl; //E
			cout << "Скорость: " << F[j].speed << " км/ч" << endl; //Выводим скорость
			cout << "Курс: " << F[j].course << " град" << endl; //Выводим курс
			cout << "Высота: " << F[j].hight << " м" << endl; //Выводим высоту
			cout << "Кол-во спутников: " << F[j].sats << endl; //Выводим кол-во спутников
		}
		cout << endl;
	}

}