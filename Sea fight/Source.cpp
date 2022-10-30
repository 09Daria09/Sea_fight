#include<iostream>
#include"Navy.h"
using namespace std;

int main()
{
	system("color F0");
	setlocale(LC_ALL, "ru");
    //начальна€ позици€ 
	UserNavy userNavy; //‘лот пользовател€
	RobotNavy robotNavy;//‘лот робота
	userNavy.Show();
	//printf("\a");

	while (userNavy.IsLive() && robotNavy.IsLive()) {
		//выстрел пользовател€
		if (Space::u_state != Miss) {
			cout << "пропускаетс€...:  <Enter>" << endl;
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
			cout << "выстрел непри€тел€ пропускаетс€..." << endl;
		else {
			robotNavy.FireOff();
			userNavy.GetFire();
			robotNavy.ResultAnalys();
		}
		userNavy.Show();
	}
	if (userNavy.IsLive())
		cout << "\n:-))) ”ра победа!!! :-)))" << endl;
	else {
		cout << "\n ѕоражение " << endl;
	}
	cin.get();
	return 0;
}
