#include "stdafx.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>

using namespace std;

struct form // ��������� �������
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
	SetConsoleCP(1251);  // ������������ ���������
	SetConsoleOutputCP(1251);
	int N;
	cout << "������� ���-�� �����: ";
	cin >> N;
	form *F = new form[N];
	
	GetData(F, N); //�� �����
	ShowData(F, N); //�� ������� ������

	delete[]F;
	system("Pause"); // ����� ��� �������
	return 0;
}

string DataS(int &i,string &s) 
{ // ����������� �������� �������� � ������ ������
	string str;
	int len = s.length(); // ���������� ������ ������
	while ((i < len)&&(s[i] != ';')&&(s[i]!='\r')&&(s[i]!='\n')) 
		{ // ��������� �� ';' ��� ����� ����� ��� ���� �� ������ �� \r\n
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
		cout << "������� ������ " << j <<" : "  << endl; // ������ ������
		getline(cin, s);
		s += '\r';  // ��������� � ����� \r\n
		s += '\n';
		cout << endl;  // ������� ������

		int pos = 0; // ����� ������� ������� ���������
		pos = s.find("#M#"); // ���� ����������
		if (pos == 0)
		{  // ������ ��������� � ������
			F[j].type = "M";
			F[j].data = s.substr(3); // ��������� ������ � formM1		
		}

		pos = 0; //����� ������� ������� ���������
		pos = s.find("#SD#"); // ���� ����������
		if (pos == 0)
		{ // ������ ��������� � ������
			F[j].type = "SD";
			int i = 4; // ��������� �� 4 ������
			F[j].date = DataS(i, s); // ��������� ������ � ������ ������
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
				cerr << "������ ��������������" << endl;
			}
			try
			{
				F[j].lon1 = round(stod(slon1) * 10000) / 10000;
			}
			catch (const std::exception&)
			{
				cerr << "������ ��������������" << endl;
			}
			try
			{
				F[j].speed = stoi(sspeed);
			}
			catch (const std::exception&)
			{
				cerr << "������ ��������������" << endl;
			}
			try
			{
				F[j].course = stoi(scourse);
			}
			catch (const std::exception&)
			{
				cerr << "������ ��������������" << endl;
			}
			try
			{
				F[j].hight = stoi(shight);
			}
			catch (const std::exception&)
			{
				cerr << "������ ��������������" << endl;
			}
			try
			{
				F[j].sats = stoi(ssats);
			}
			catch (const std::exception&)
			{
				cerr << "������ ��������������" << endl;
			}
		}

	}
}

void ShowData(form *F, int N)
{
	for (int j = 0; j < N; j++)
	{
		cout << "������ ������ " << j << " : " << endl;
		cout << endl;
		if (F[j].type == "M")
		{
			cout << "���� DATA: " << F[j].data << endl; //������� �� �����
		}
		if (F[j].type == "SD")
		{
			cout << "����: " << F[j].date[0] << F[j].date[1]; // ������� ����
			cout << "/";
			cout << F[j].date[2] << F[j].date[3];
			cout << "/";
			cout << F[j].date[4] << F[j].date[5] << F[j].date[6] << F[j].date[7] << endl; 
			cout << "�����: " << F[j].time[0] << F[j].time[1]; // ������� �����
			cout << ":";
			cout << F[j].time[2] << F[j].time[3];
			cout << ":";
			cout << F[j].time[4] << F[j].time[5] << endl;
			cout << "������: " << setprecision(4) << fixed << F[j].lat1; //������� ������
			cout << F[j].lat2 << endl; //N
			cout << "�������: " << F[j].lon1; //������� �������
			cout << F[j].lon2 << endl; //E
			cout << "��������: " << F[j].speed << " ��/�" << endl; //������� ��������
			cout << "����: " << F[j].course << " ����" << endl; //������� ����
			cout << "������: " << F[j].hight << " �" << endl; //������� ������
			cout << "���-�� ���������: " << F[j].sats << endl; //������� ���-�� ���������
		}
		cout << endl;
	}

}