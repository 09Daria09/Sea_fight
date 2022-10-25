#pragma once
#include "Ship.h"
#define DECK 176 //��������� ������-������
#define DAMAGE 'X'//����������� ������-������
#define MISS 'O'//������ ������, � ������� ���� ������

typedef unsigned char Field[10][10];
typedef map<Cell, int>ShipMap;

enum CurrentState{Miss, Damage, Kill};

struct Space
{
	public:
		static Cell u_fire;  //����� �� ������������
		static Cell r_fire; //����� �� ����������
		static CurrentState u_state; //��������� ������������ 
		static CurrentState r_state; //��������� ������
		static int step; //
};

class Navy: public Space
{
protected:
	Ship ship[10]; //�������
	Field ownField; //������� ���� ������������
	Field enemyFiled; //������� ���� ����������
	ShipMap shipMap; //������ - ������ �������
	CellSet vetoSet; //����������� ������
	CellSet crushSet; //������������ ������
	int nLiveShip; //���������� ����� ��������
public:
	Navy();
	void AllocShip(int, int, string); //���������� �������
	void Show()const;//����� ����� 
	int GetInt(); //���� ������ �����
	bool IsLive(){
		return (nLiveShip > 0);
	}
	Rect Shell(Rect)const;// ������� �������� ��� ��������� �������������� (��� ������������� ���� ����������� ������
	void AddToVetoSet(Rect);// ���������� ������ ��������������
};

class UserNavy : public Navy
{
public:
	void Allocation();
	void FireOff(); //������� �� �����
	void ResultAnalus(); //���������� ��������
	void GetFire(); //���� ����� ����
	void FillDeadZone(Rect r, Field&); 
	UserNavy()
	{
		Allocation();
	}
};

class RobotNavy : public Navy
{
	bool isCrushContinue; //���� ������� ����� �� �����
	bool upEmpty; //
public:
	RobotNavy(); 
	void FireOff(); //������� �� �����
	void ResultAnalys(); //���������� ��������
	void GetFire(); //���� ����� ���������
};