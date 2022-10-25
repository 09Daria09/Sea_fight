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
	int row;//���
	int col; //�������
	Cell(int _r = 0, int _c = 0): row(_r), col(_c){}
	bool InSet(const CellSet&)const;//���������� �������������� ������ ��������� ���� CellSet
	bool operator<(const Cell&)const;
};
//������������� ������� (���������� ��������)
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
	Rect place; //���������� ����������
	string name; //��� �������
	int nDeck; //���������� �����
	int nLiveDeck; //���������� �������������� ����� 
};

