#pragma once
#include "Ship.h"
#define DECK 1 //��������� ������-������
#define DAMAGE 'X'//����������� ������-������
#define MISS '#'//������ ������, � ������� ���� ������

typedef unsigned char Field[N][N];//--
typedef std::map<ElementCell, int>ShipMap;

enum CurrentState{Miss, Damage, Kill};

struct Space{
	public:
		static ElementCell u_fire;  //����� �� ������������
		static ElementCell r_fire; //����� �� ����������
		static CurrentState u_state; //��������� ������������ 
		static CurrentState r_state; //��������� ������
};

class Navy: public Space{
protected:
	Ship ship[10]; //�������
	Field UserField; //������� ���� ������������
	Field RobotField; //������� ���� ����������
	ShipMap shipMap; //������ - ������ �������
	CellSet ForbiddenCells; //����������� ������
	CellSet DestroyedCells; //������������ ������
	int CountLiveShip; //���������� ����� ��������

public:
	Navy();
	void PlaceShip(int, int, string); //���������� �������
	void Show()const;//����� ����� 

	int GetInt(); //���� ������ �����
	bool IsLive(){
		return (CountLiveShip > 0);
	}
	Area Shell(Area)const;// ������� �������� ��� ��������� �������������� (��� ������������� ���� ����������� ������
	void CellAddition(Area);// ���������� ������ ��������������

};

class User : public Navy{
public:
	User(){Location();}
	void Location();
	void Fire(); //������� �� �����
	void ResultAnalys(); //���������� ��������
	void GetFire(); //���� ����� ����
	void FillDeadZone(Area r, Field&);
};

class Robot : public Navy
{
public:
	Robot();
	void Location();
	void Fire(); //������� �� �����
	void ResultAnalys(); //���������� ��������
	void GetFire(); //���� ����� ���������
private:
	bool isCrushContinue; //���� ������� ����� �� �����
	bool upEmpty; //
};