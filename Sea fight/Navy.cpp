#include<iostream>
#include<time.h>
#include<algorithm>

#include<Windows.h>
#include "Navy.h"

using namespace std;

ElementCell Space::u_fire;
ElementCell Space::r_fire;
CurrentState Space::u_state = Miss;
CurrentState Space::r_state = Miss;

string gap(int n)// ���������� ������ �� n �������� 
{
	return string(n, ' ');
}

Navy::Navy() : CountLiveShip(10)//��������� ������� ���� �������
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++){
			UserField[i][j] = '.';
			RobotField[i][j] = '.';
		}
}
Area Navy::Shell(Area r)const{
	Area sh(r);
	sh.LeftTop.row = (--sh.LeftTop.row < 0) ? 0 : sh.LeftTop.row;
	sh.LeftTop.col = (--sh.LeftTop.col < 0) ? 0 : sh.LeftTop.col;
	sh.RightBottom.row = (++sh.RightBottom.row > (N - 1)) ? (N - 1) : sh.RightBottom.row;
	sh.RightBottom.col = (++sh.RightBottom.col > (N - 1)) ? (N - 1) : sh.RightBottom.col;
	return sh;
}

void Navy::CellAddition(Area r){
	for (int i = r.LeftTop.row; i <= r.RightBottom.row; i++)
		for (int j = r.LeftTop.col; j <= r.RightBottom.col; j++)
			ForbiddenCells.insert(ElementCell(i, j));
}

void Navy::PlaceShip(int indShip, int nDeck, string name)//��������� �������� ����������� ��������� ������ ������� � ������ ������������� ����������� ������ ������� � ���������� ������ DestroyColls 
{
	int i, j;
	ElementCell lt, rb;
	while (1)
	{
		lt.row = rand() % (N + 1 - nDeck);
		lt.col = rb.col = rand() % N;
		rb.row = lt.row + nDeck - 1;
		if (!Area(lt, rb).Cross(ForbiddenCells))break;
	}
	ship[indShip] = Ship(nDeck, name, Area(lt, rb));//��������� ������ � ����� �������

	for (i = lt.row; i <= rb.row; i++)//������� ����� ������� �� ������� ���� (������ DECK). ��������� ��������������� �������� � ������� ����������
		for (j = lt.col; j <= rb.col; j++){
			UserField[i][j] = DECK;
			shipMap[ElementCell(i, j)] = indShip;
		}
	CellAddition(Shell(Area(lt, rb)));//��������� � ��������� vetoSet ������ ������ �������, ������ � ������������ �������� 
}

void Navy::Show()const{
	char rowName[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	string colName("1 2 3 4 5 6 7 8 9 10");
	int i, j;
	cout << "____________________________________________________\n";
	cout << gap(7) << "��� ����" << gap(16) << "���� ����������" << endl;
	cout << gap(3) << colName << gap(6) << colName << endl;

	for (i = 0; i < 10; i++){
		//Own
		string line = gap(1) + rowName[i];
		for (j = 0; j < N; j++)
			line += gap(1) + (char)UserField[i][j];
			//Enemy
		line += gap(5) + rowName[i];
		for (j = 0; j < N; j++)
			line += gap(1) + (char)RobotField[i][j];
		cout << line << endl;
	}
	cout << "____________________________________________________\n";
	cout << "��� �������:     ";
}

int Navy::GetInt(){
	int value;
	while (true){
		cin >> value;
		if ('\n' == cin.peek()){cin.get();break;}//������� peek() ���������� ��������� ������ � ������ 
		else{
			cout << "��������� ���� ������� (��������� ����� �����):" << endl;
			cin.clear();
			while (cin.get() != '\n') {};
		}
	}
	return value;
}

void User::Location(){
	srand((unsigned)time(NULL));
	PlaceShip(0, 4, " ��������������� �������� ");
	PlaceShip(1, 3, " ������������ �������� ");
	PlaceShip(2, 3, " ������������ �������� ");
	PlaceShip(3, 2, " ������������ �������� ");
	PlaceShip(4, 2, " ������������ �������� ");
	PlaceShip(5, 2, " ������������ �������� ");
	PlaceShip(6, 1, " ������������ �������� ");
	PlaceShip(7, 1, " ������������ �������� ");
	PlaceShip(8, 1, " ������������ ��������");
	PlaceShip(9, 1, " ������������ ��������");
	ForbiddenCells.clear();
}

void User::FillDeadZone(Area r, Field& field)
{
	int i, j;
	Area sh = Shell(r);
	for (i = sh.LeftTop.row, j = sh.LeftTop.col; j <= sh.RightBottom.col; j++)
		if (sh.LeftTop.row < r.LeftTop.row)field[i][j] = ' ';
	for (i = sh.RightBottom.row, j = sh.LeftTop.col; j <= sh.RightBottom.col; j++)
		if (sh.RightBottom.row > r.RightBottom.row)field[i][j] = ' ';
	for (j = sh.LeftTop.col, i = sh.LeftTop.row; i <= sh.RightBottom.row; i++)
		if (sh.LeftTop.col < r.LeftTop.col)field[i][j] = ' ';
	for (j = sh.RightBottom.col, i = sh.LeftTop.row; i <= sh.RightBottom.row; i++)
		if (sh.RightBottom.col > r.RightBottom.col)field[i][j] = ' ';
}

void User::Fire()
{
	string capital_letter = "ABCDEFGHIJ";
	string small_letter = "abcdefghij";

	unsigned char rowName; //����������� ���� (�, �, ....., J)
	int colName; //����������� ������� (1, 2,......, 10)
	int row; // ������ ���� (0, 1,......., 9)
	int col; // ������ ������� (0, 1,...., 9)

	bool success = false;
	while (!success){
		cin >> rowName;
		row = capital_letter.find(rowName);
		if (-1 == row)row = small_letter.find(rowName);
		if (-1 == row) {
			cout << "!������. ��������� ����.! \n"; continue;
		}
		colName = GetInt();//�������, ������� ���������� ��������� �������� �� ���������
		col = colName - 1;
		if ((col < 0) || (col > 9)) {
			cout << "!������. ��������� ����.! \n"; continue;
		}
		success = true;
	}
	u_fire = ElementCell(row, col);
}

void User::ResultAnalys() {
	switch(r_state) {
	case Miss:
		RobotField[u_fire.row][u_fire.col] = MISS;
		break;
	case Damage:
		RobotField[u_fire.row][u_fire.col] = DAMAGE;
		DestroyedCells.insert(u_fire);
		break;
	case Kill:
		RobotField[u_fire.row][u_fire.col] = DAMAGE;
		DestroyedCells.insert(u_fire);
		Area kill;
		kill.LeftTop = *DestroyedCells.begin();
		kill.RightBottom = *(--DestroyedCells.end());
		FillDeadZone(kill, RobotField);
		DestroyedCells.clear();
	}
}

void User::GetFire() {
	//������� ������ �� ������ r_fire
	string capital_letter = "ABCDEFGHIJ";
	char rowName = capital_letter[r_fire.row];
	int colName = r_fire.col + 1;
	cout << "\n������� ����������: " << rowName << colName << endl;
	if (DECK == UserField[r_fire.row][r_fire.col]) {
		cout << "*** ���� ���������! ***";
		UserField[r_fire.row][r_fire.col] = DAMAGE;
		u_state = Damage;
		//������ ������� ����������� ������ r_fire
		int ind = shipMap[r_fire];
		ship[ind].CountLiveDeck--;

		if (!ship[ind].CountLiveDeck) {
			u_state = Kill;
			cout << gap(6) << "� ����! �����" << ship[ind].name << " !!!";
			CountLiveShip--;
			Area kill = ship[ind].place;
			FillDeadZone(kill, UserField);
		}
	}
	else {
		u_state = Miss;
		cout << "*** ����! ***";
		UserField[r_fire.row][r_fire.col] = MISS;
	}
	cout << endl;
}

Robot::Robot() {
	Location();
	isCrushContinue = false;
	upEmpty = false;
}

void Robot::Location() {
	PlaceShip(0, 4, " ��������������� �������� ");
	PlaceShip(1, 3, " ������������ �������� ");
	PlaceShip(2, 3, " ������������ �������� ");
	PlaceShip(3, 2, " ������������ �������� ");
	PlaceShip(4, 2, " ������������ �������� ");
	PlaceShip(5, 2, " ������������ �������� ");
	PlaceShip(6, 1, " ������������ �������� ");
	PlaceShip(7, 1, " ������������ �������� ");
	PlaceShip(8, 1, " ������������ ��������");
	PlaceShip(9, 1, " ������������ ��������");
	ForbiddenCells.clear();
}
 
void Robot::Fire() {
	ElementCell c, cUp;
	if (!isCrushContinue) {
		//��������� ����� ��������� ��������
		while(1) {
			c.row = rand() % N;
			c.col = rand() % N;
			if (!c.InSet(ForbiddenCells))break;
		}
	}
	else {
		//������ �� ����������� ��������� 
		c = cUp = r_fire;
		cUp.row--;
		if ((!upEmpty) && c.row && (!cUp.InSet(ForbiddenCells)))
			c.row--;
		else {
			c = *(--DestroyedCells.end());
			c.row++;
		}
	}
	r_fire = c;
	ForbiddenCells.insert(r_fire);
}

void Robot::ResultAnalys() {
	//u_state - ��������� ������������ � ����������
	//������� ������ �� ������ r_fire
	switch(u_state){
	case Miss:
		if (isCrushContinue) upEmpty = true;
		break;
	case Damage:
		isCrushContinue = true;
		DestroyedCells.insert(r_fire);
		break;
	case Kill:
		isCrushContinue = false;
		upEmpty = false;
		DestroyedCells.insert(r_fire);
		Area kill;
		kill.LeftTop = *DestroyedCells.begin();
		kill.RightBottom = *(--DestroyedCells.end());

		CellAddition(Shell(kill));
		DestroyedCells.clear();
    }
}

void Robot::GetFire() {
	//������� ������������ �� ������ u_fire
	if (DECK == UserField[u_fire.row][u_fire.col]) {
		cout << "*** ���� ���������! ***";
		r_state = Damage;
		//������ �������, ����������� ������ u_fire
		int ind = shipMap[u_fire];
		ship[ind].CountLiveDeck--;

		if (!ship[ind].CountLiveDeck) {
			r_state = Kill;
			cout << gap(6) << "��������� " << ship[ind].name << " !!!";
			CountLiveShip--;
		}
	}
	else {
		r_state = Miss;
		cout << "*** ����! ***";
	}
	cout << endl;
}