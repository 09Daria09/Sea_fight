#pragma once
#include "Ship.h"
#define DECK 1 //исправная клетка-палуба
#define DAMAGE 'X'//разрушенная клетка-палуба
#define MISS '#'//пустая клетка, в которую упал снаряд

typedef unsigned char Field[N][N];//--
typedef std::map<ElementCell, int>ShipMap;

enum CurrentState{Miss, Damage, Kill};

struct Space{
	public:
		static ElementCell u_fire;  //огонь от пользователя
		static ElementCell r_fire; //огонь от компьютера
		static CurrentState u_state; //состояние пользователя 
		static CurrentState r_state; //состояние робота
};

class Navy: public Space{
protected:
	Ship ship[10]; //корабли
	Field UserField; //игровое поле пользователя
	Field RobotField; //игровое поле противника
	ShipMap shipMap; //клетка - индекс корабля
	CellSet ForbiddenCells; //запрещенные клетки
	CellSet DestroyedCells; //уничтоженные клетки
	int CountLiveShip; //количество живых кораблей

public:
	Navy();
	void PlaceShip(int, int, string); //разместить корабль
	void Show()const;//показ полей 

	int GetInt(); //ввод целого числа
	bool IsLive(){
		return (CountLiveShip > 0);
	}
	Area Shell(Area)const;// возврат оболочки для заданного прямоугольника (сам прямоугольник плюс пограничные клетки
	void CellAddition(Area);// добавление клетки прямоугольника

};

class User : public Navy{
public:
	User(){Location();}
	void Location();
	void Fire(); //выстрел по врагу
	void ResultAnalys(); //результаты выстрела
	void GetFire(); //куда попал враг
	void FillDeadZone(Area r, Field&);
};

class Robot : public Navy
{
public:
	Robot();
	void Location();
	void Fire(); //выстрел по врагу
	void ResultAnalys(); //результаты выстрела
	void GetFire(); //куда попал противник
private:
	bool isCrushContinue; //если выстрел попал по врагу
	bool upEmpty; //
};