#pragma once
#include "Ship.h"
#define DECK 176 //��������� ������-������
#define DAMAGE 'X'//����������� ������-������
#define MISS 'O'//������ ������, � ������� ���� ������

typedef unsigned char Field[N][N];//--
typedef std::map<Cell, int>ShipMap;

enum CurrentState{Miss, Damage, Kill};

struct Space{
	public:
		static Cell u_fire;  //����� �� ������������
		static Cell r_fire; //����� �� ����������
		static CurrentState u_state; //��������� ������������ 
		static CurrentState r_state; //��������� ������
		static int step; //
};

class Navy: public Space{
public:
	Navy();
	void AllocShip(int, int, std::string); //���������� �������
	void Show()const;//����� ����� 

	int GetInt(); //���� ������ �����
	bool IsLive(){
		return (nLiveShip > 0);
	}
	Rect Shell(Rect)const;// ������� �������� ��� ��������� �������������� (��� ������������� ���� ����������� ������
	void AddToVetoSet(Rect);// ���������� ������ ��������������

protected:
	Ship ship[10]; //�������
	Field ownField; //������� ���� ������������
	Field enemyField; //������� ���� ����������
	ShipMap shipMap; //������ - ������ �������
	CellSet vetoSet; //����������� ������
	CellSet crushSet; //������������ ������
	int nLiveShip; //���������� ����� ��������
};

class UserNavy : public Navy{
public:
	UserNavy(){Allocation();}
	void Allocation();
	void FireOff(); //������� �� �����
	void ResultAnalys(); //���������� ��������
	void GetFire(); //���� ����� ����
	void FillDeadZone(Rect r, Field&); 
};

class RobotNavy : public Navy
{
public:
	RobotNavy(); 
	void Allocation();
	void FireOff(); //������� �� �����
	void ResultAnalys(); //���������� ��������
	void GetFire(); //���� ����� ���������
private:
	bool isCrushContinue; //���� ������� ����� �� �����
	bool upEmpty; //
};