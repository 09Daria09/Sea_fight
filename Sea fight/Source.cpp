#include<iostream>
#include"Navy.h"

int main()
{
	system("color F0");
	setlocale(LC_ALL, "ru");
    //начальная позиция 
	User userNavy; //Флот пользователя
	Robot robotNavy;//Флот робота
	userNavy.Show();
	//printf("\a");

	while (userNavy.IsLive() && robotNavy.IsLive()) {
		//выстрел пользователя
		if (Space::u_state != Miss) {
			cout << "пропускается...:  <Enter>" << endl;
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
		//выстрел робота
		if (Space::r_state != Miss)
			cout << "выстрел противника пропускается..." << endl;
		else {
			robotNavy.Fire();
			userNavy.GetFire();
			robotNavy.ResultAnalys();
		}
		userNavy.Show();
	}
	if (userNavy.IsLive())
		cout << "\n Ура победа!!! :)" << endl;
	else {
		cout << "\n Поражение :( \nНичего в следующий раз повезет :) " << endl;
	}
	cin.get();
	return 0;
}
