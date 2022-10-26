#pragma once
//&
#ifndef SHIP_H
#endif SHIP_H

#include <set>
#include<map>
#include<string>

constexpr auto N = 10;


struct Cell;
typedef std::set<Cell>CellSet;

struct Cell
{
	Cell(int _r = 0, int _c = 0): row(_r), col(_c){}
	bool InSet(const CellSet&)const;//���������� �������������� ������ ��������� ���� CellSet

	bool operator<(const Cell&)const;
	int row;//���
	int col; //�������
};
//������������� ������� (���������� ��������)
struct Rect
{
	Rect(){}
	Rect(Cell _It, Cell _rb) : It(_It), rb(_rb)	{FillCset();}
	void FillCset();

	bool Intersect(const CellSet& cs)const;

	Cell It;
	Cell rb;
	CellSet cset;

};
class Ship
{
	friend class UserNavy;
	friend class RobotNavy;
public:
	Ship(): nDeck(0), nLiveDeck(0){}
	Ship(int, std::string, Rect);
protected:
	Rect place; //���������� ����������
	std::string name; //��� �������
	int nDeck; //���������� �����
	int nLiveDeck; //���������� �������������� ����� 
};

