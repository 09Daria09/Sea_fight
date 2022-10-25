#pragma once
//&
#ifndef SHIP_H
#endif SHIP_H

#include <set>
#include<map>
#include<string>
#include<iostream>
using namespace std;


struct Cell;
typedef set<Cell>CellSet;

struct Cell
{
	int row;//ряд
	int col; //колонка
	Cell(int _r = 0, int _c = 0): row(_r), col(_c){}
	bool InSet(const CellSet&)const;//определяет принадлежность клетки множеству типа CellSet
	bool operator<(const Cell&)const;
};
//Прямоугольная область (размещение кораблей)
struct Rect
{
	Cell It;
	Cell rb;
	CellSet cset;
	void FillCset();
	Rect(){}
	Rect(Cell _It, Cell _rb) : It(_It), rb(_rb)	{FillCset();}
	bool Intersect(const CellSet& cs)const;

};
class Ship
{
	friend class UserNavy;
	friend class RobotNavay;
public:
	Ship(): nDeck(0), nLiveDeck(0){}
	Ship(int, string, Rect);
protected:
	Rect place; //координаты размещения
	string name; //имя корабля
	int nDeck; //количество палуб
	int nLiveDeck; //количество неповрежденных палуб 
};

