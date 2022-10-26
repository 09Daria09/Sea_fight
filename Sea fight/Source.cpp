#include<iostream>
#include"Navy.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
//начальная позиция 
	UserNavy userNavy;
	RobotNavy robotNavy;
	userNavy.Show();

	while (userNavy.IsLive() && robotNavy.IsLive()) {
		//выстрел пользователя
		if (Space::u_state != Miss) {
			cout << "пропускается...:  <Enter>" << endl;
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
		//выстрел робота
		if (Space::r_state != Miss)
			cout << "выстрел неприятеля пропускается..." << endl;
		else {
			robotNavy.FireOff();
			userNavy.GetFire();
			robotNavy.ResultAnalys();
		}
		userNavy.Show();
	}
	if (userNavy.IsLive())
		cout << "\n:-))) Ура победа!!! :-)))" << endl;
	else {
		cout << "\n Поражение " << endl;
	}
	cin.get();
	return 0;
}
