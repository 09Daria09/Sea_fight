#include<iostream>
#include"Navy.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
//��������� ������� 
	UserNavy userNavy;
	RobotNavy robotNavy;
	userNavy.Show();

	while (userNavy.IsLive() && robotNavy.IsLive()) {
		//������� ������������
		if (Space::u_state != Miss) {
			cout << "������������...:  <Enter>" << endl;
			cin.get();
		}
		else {
			userNavy.FireOff();
			robotNavy.GetFire();
			userNavy.ResultAnalys();
			if (!robotNavy.IsLive()) {
				userNavy.Show();
				break;
			}
		}
		//������� ������
		if (Space::r_state != Miss)
			cout << "������� ���������� ������������..." << endl;
		else {
			robotNavy.FireOff();
			userNavy.GetFire();
			robotNavy.ResultAnalys();
		}
		userNavy.Show();
	}
	if (userNavy.IsLive())
		cout << "\n:-))) ��� ������!!! :-)))" << endl;
	else {
		cout << "\n ��������� " << endl;
	}
	cin.get();
	return 0;
}
