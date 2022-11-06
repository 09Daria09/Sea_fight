#pragma once
#include <set> //Set - ���������, ������� ������������� ��������� ����������� �������� � ������� �����������.
#include<map> //map - ���������, ������� ����� ����� ��������� �������� � ��������������� ������� ��� ����������, �� �� ������ ������������� ��������
#include<string>
using namespace std;

constexpr auto N = 10;
 /*constexpr � ������������ ����, 
�������� � �������� ���������������� ����� C++11 ��� ����������� ����������� ���������, 
������� ����� ���� ��������� �� ����� ���������� ����*/


struct ElementCell; //���������� ������� ������ 
typedef set<ElementCell>CellSet; //������� ��������� ��� �������� ���������

struct ElementCell
{
	int col; //�������
	int row;//���
	ElementCell(int row_ = 0, int col_ = 0): row(row_), col(col_){} // ����������� ���� � ������� ����
	bool InSet(const CellSet&)const;//���������� �������������� ������ ��������� ���� CellSet

	bool operator<(const ElementCell&)const; //
};
//������������� ������� (���������� ��������)
struct Area
{
	ElementCell LeftTop; //����� ������� ������
	ElementCell RightBottom;//������ ������ ������
	CellSet cset; // ������ ������������� �������������� 
	Area(){}
	Area(ElementCell It, ElementCell rb) : LeftTop(It), RightBottom(rb)	{FillCset();}
	void FillCset();// ��������� cset �������� 

	bool Cross(const CellSet& cs)const;// ����������� ��������� ����������� �������������� � ���������� cs 


};
class Ship
{
	friend class User;
	friend class Robot;
protected:
	Area place; //���������� ����������
	std::string name; //��� �������
	int CountDeck; //���������� �����
	int CountLiveDeck; //���������� �������������� ����� 
public:
	Ship(): CountDeck(0), CountLiveDeck(0){}
	Ship(int, string, Area);
};

