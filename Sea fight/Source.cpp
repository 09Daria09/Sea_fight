#include<iostream>
#include"Navy.h"

int main()
{
	system("color F0");
	setlocale(LC_ALL, "ru");
    //��������� ������� 
	User userNavy; //���� ������������
	Robot robotNavy;//���� ������
	userNavy.Show();
	//printf("\a");

	while (userNavy.IsLive() && robotNavy.IsLive()) {
		//������� ������������
		if (Space::u_state != Miss) {
			cout << "������������...:  <Enter>" << endl;
			cin.get();
		}
		else {
			userNavy.Fire();
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
			robotNavy.Fire();
			userNavy.GetFire();
			robotNavy.ResultAnalys();
		}
		userNavy.Show();
	}
	if (userNavy.IsLive())
		cout << "\n ��� ������!!! :)" << endl;
	else {
		cout << "\n ��������� :( \n������ � ��������� ��� ������� :) " << endl;
	}
	cin.get();
	return 0;
}
