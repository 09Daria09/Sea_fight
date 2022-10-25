#pragma once
#include "Ship.h"
#define DECK 176 //исправная клетка-палуба
#define DAMAGE 'X'//разрушенная клетка-палуба
#define MISS 'O'//пустая клетка, в которую упал снаряд

typedef unsigned char Field[10][10];
typedef map<Cell, int>ShipMap;

enum CurrentState{Miss, Damage, Kill};

struct Space
{
	public:
		static Cell u_fire;  //огонь от пользователя
		static Cell r_fire; //огонь от компьютера
		static CurrentState u_state; //состояние пользователя 
		static CurrentState r_state; //состояние робота
		static int step; //
};

class Navy: public Space
{
protected:
	Ship ship[10]; //корабли
	Field ownField; //игровое поле пользователя
	Field enemyFiled; //игровое поле противника
	ShipMap shipMap; //клетка - индекс корабля
	CellSet vetoSet; //запрещенные клетки
	CellSet crushSet; //уничтоженные клетки
	int nLiveShip; //количество живых кораблей
public:
	Navy();
	void AllocShip(int, int, string); //разместить корабль
	void Show()const;//показ полей 
	int GetInt(); //ввод целого числа
	bool IsLive(){
		return (nLiveShip > 0);
	}
	Rect Shell(Rect)const;// возврат оболочки для заданного прямоугольника (сам прямоугольник плюс пограничные клетки
	void AddToVetoSet(Rect);// добавление клетки прямоугольника
};

class UserNavy : public Navy
{
public:
	void Allocation();
	void FireOff(); //выстрел по врагу
	void ResultAnalus(); //результаты выстрела
	void GetFire(); //куда попал враг
	void FillDeadZone(Rect r, Field&); 
	UserNavy()
	{
		Allocation();
	}
};

class RobotNavy : public Navy
{
	bool isCrushContinue; //если выстрел попал по врагу
	bool upEmpty; //
public:
	RobotNavy(); 
	void FireOff(); //выстрел по врагу
	void ResultAnalys(); //результаты выстрела
	void GetFire(); //куда попал противник
};