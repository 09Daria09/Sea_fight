#pragma once
#include <set> //Set - контейнер, который автоматически сортирует добавляемые элементы в порядке возрастания.
#include<map> //map - контейнер, который также будет содержать элементы в отсортированном порядке при добавлении, но он хранит повторяющееся элементы
#include<string>
using namespace std;

constexpr auto N = 10;
 /*constexpr — спецификатор типа, 
введённый в стандарт программирования языка C++11 для обозначения константных выражений, 
которые могут быть вычислены во время компиляции кода*/


struct ElementCell; //конкретный элемент ячейки 
typedef set<ElementCell>CellSet; //создаем контейнер для хранения элементов

struct ElementCell
{
	int col; //колонка
	int row;//ряд
	ElementCell(int row_ = 0, int col_ = 0): row(row_), col(col_){} // присваиваем ряду и колонке нули
	bool InSet(const CellSet&)const;//определяет принадлежность клетки множеству типа CellSet

	bool operator<(const ElementCell&)const; //
};
//Прямоугольная область (размещение кораблей)
struct Area
{
	ElementCell LeftTop; //левая верхняя клетка
	ElementCell RightBottom;//правая нижняя клетка
	CellSet cset; // клетки принадлежащие прямоугольнику 
	Area(){}
	Area(ElementCell It, ElementCell rb) : LeftTop(It), RightBottom(rb)	{FillCset();}
	void FillCset();// наполнить cset клетками 

	bool Cross(const CellSet& cs)const;// определение непустого пересечения прямоугольника с множеством cs 


};
class Ship
{
	friend class User;
	friend class Robot;
protected:
	Area place; //координаты размещения
	std::string name; //имя корабля
	int CountDeck; //количество палуб
	int CountLiveDeck; //количество неповрежденных палуб 
public:
	Ship(): CountDeck(0), CountLiveDeck(0){}
	Ship(int, string, Area);
};

