#include<iostream>
#include<cstdlib>//
#include<time.h>
#include<algorithm>
#include "Navy.h"

using namespace std;

Cell Space::u_fire;
Cell Space::r_fire;
CurrentState Space::u_state = Miss;
CurrentState Space::r_state = Miss;
int Space::step = 1;

string gap(int n)// ���������� ������ �� n �������� 
{
	return string(n, ' ');
}

Navy::Navy() : nLiveShip(10)//��������� ������� ���� �������
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			ownField[i][j] = '.';
			enemyFiled[i][j] = '.';
		}
	}
}
Rect Navy::Shell(Rect r)const
{
	Rect sh(r);
	sh.It.row = (-sh.It.row < 0) ? 0 : sh.It.row;
	sh.It.col = (-sh.It.col < 0) ? 0 : sh.It.col;
	sh.rb.row = (++sh.rb.row > (10 - 1)) ? (10 - 1) : sh.rb.row;
	sh.rb.col = (++sh.rb.col > (10 - 1)) ? (10 - 1) : sh.rb.col;
	return sh;
}

void Navy::AddToVetoSet(Rect r)
{
	for (int i = r.It.row; i <= r.rb.row; i++)
	{
		for (int j = r.It.col; j <= r.rb.col; j++)
		{
			vetoSet.insert(Cell(i, j));
		}
	}
}

void Navy::AllocShip(int indShip, int nDeck, string name)//��������� �������� ����������� ��������� ������ ������� � ������ ������������� ����������� ������ ������� � ���������� ������ vetoSet 
{
	int i, j;
	Cell It, rb;
	while (1)
	{
		It.row = rand() % (10 + 1 - nDeck);
		It.col = rb.col = rand() % 10;
		rb.row = It.row + nDeck - 1;
		if (!Rect(It, rb).Intersect(vetoSet))break;
	}
	ship[indShip] = Ship(nDeck, name, Rect(It, rb));//��������� ������ � ����� �������

	for (i = It.row; i <= rb.row; i++)//������� ����� ������� �� ������� ���� (������ DECK). ��������� ��������������� �������� � ������� ����������
	{
		for (j = It.col; j <= rb.col; j++)
		{
			ownField[i][j] = DECK;
			shipMap[Cell(i, j)] = indShip;
		}
	}
	AddToVetoSet(Shell(Rect(It, rb)));//��������� � ��������� vetoSet ������ ������ �������, ������ � ������������ �������� 
}

void Navy::Show()const
{
	char rowName[10] = { 'A','B','C','D','E','F','G','H','I','J' };
	string colName("1 2 3 4 5 6 7 8 9 10");
	int i, j;
	cout << "_______________________________\n";
	cout << gap(3) << "��� ����" << gap(18) << "���� ����������" << endl;
	cout << gap(3) << colName << gap(6) << colName << endl;

	for (i = 0; i < 10; i++)
	{
		//Own
		string line = gap(1) + rowName[i];
		for (j = 0; j < 10; j++)
			line += gap(1) + (char)ownField[i][j];
			//Enemy
		line += gap(5) + rowName[i];
		for (j = 0; j < 10; j++)
			line += gap(1) + (char)enemyFiled[i][j];
		cout << line << endl;
	}
	cout << endl;
	cout << "========================================\n";
	cout << step << ". " << "��� �������:     ";
	step++;
}

int Navy::GetInt()
{
	int value;
	while (true)
	{
		cin >> value;
		if ('\n' == cin.peek())
		{
			cin.get();
			break;
		}
		else
		{
			cout << "��������� ���� ������� (��������� ����� �����):" << endl;
			cin.clear();
			while (cin.get() != '\n') {};
		}
	}
	return value;
}

void UserNavy::Allocation()
{
	srand((unsigned)time(NULL));
	AllocShip(0, 4, "��������� '�����'");
	AllocShip(1, 3, "������ '�������'");
	AllocShip(2, 3, "������ '�������'");
	AllocShip(3, 2, "������� '������'");
	AllocShip(4, 2, "������� '������'");
	AllocShip(5, 2, "������� '������������'");
	AllocShip(6, 1, "��������� '�������'");
	AllocShip(7, 1, "��������� '�����'");
	AllocShip(8, 1, "��������� '���������'");
	AllocShip(9, 1, "��������� '������'");
	vetoSet.clear();
}

void UserNavy::FillDeadZone(Rect r, Field& field)
{
	int i, j;
	Rect sh = Shell(r);
	for (i = sh.It.row, j = sh.It.col; j <= sh.rb.col; j++)
		if (sh.It.row < r.It.row)field[i][j] = ' ';
	for (i = sh.rb.row, j = sh.It.col; j <= sh.rb.col; j++)
		if (sh.rb.row > r.rb.row)field[i][j] = ' ';
	for (i = sh.It.col, j = sh.It.row; j <= sh.rb.row; i++)
		if (sh.It.col < r.It.col)field[i][j] = ' ';
	for (i = sh.rb.col, j = sh.It.row; j <= sh.rb.row; i++)
		if (sh.rb.col > r.rb.col)field[i][j] = ' ';
}

void UserNavy::FireOff()
{
	string capital_letter = "ABCDEFGHIJ";
	string small_letter = "abcdefghij";

	unsigned char rowName; //����������� ���� (�, �, ....., J)
	int colName; //����������� ������� (1, 2,......, 10)
	int row; // ������ ���� (0, 1,......., 9)
	int col; // ������ ������� (0, 1,...., 9)

	bool success = false;
	while (!success)
	{
		cin >> rowName;
		row = capital_letter.find(rowName);
		if (-1 == row)row = small_letter.find(rowName);
		if (-1 == row) {
			cout << "������. ��������� ����. \n"; continue;
		}
		colName = GetInt();
		col = colName - 1;
		if ((col < 0) || (col > 9)) {
			cout << "������. ��������� ����. \n"; continue;
		}
		success = true;
	}
	u_fire = Cell(row, col);
}

void UserNavy::ResultAnalus() {
	switch(r_state) {
	case Miss:
		enemyFiled[u_fire.row][u_fire.col] = MISS;
		break;
	case Damage:
		enemyFiled[u_fire.row][u_fire.col] = DAMAGE;
		crushSet.insert(u_fire);
		break;
	case Kill:
		enemyFiled[u_fire.row][u_fire.col] = DAMAGE;
		crushSet.insert(u_fire);
		Rect kill;
		kill.It = *crushSet.begin();
		kill.rb = *(--crushSet.end());
		FillDeadZone(kill, enemyFiled);
		crushSet.clear();
	}
}

void UserNavy::GetFire() {
	//������� ������ �� ������ r_fire
	string capital_letter = "ABCDEFGHIJ";
	char rowName = capital_letter[r_fire.row];
	int colName = r_fire.col + 1;
	cout << "\n������� ����������: " << rowName << colName << endl;
	if (DECK == ownField[r_fire.row][r_fire.col]) {
		cout << "*** ���� ���������! ***";
		ownField[r_fire.row][r_fire.col] = DAMAGE;
		u_state = Damage;
		//������ ������� ����������� ������ r_fire
		int ind = shipMap[r_fire];
		ship[ind].nLiveDeck--;

		if (!ship[ind].nLiveDeck) {
			u_state = Kill;
			cout << gap(6) << "� ����! �����" << ship[ind].name << " !!!";
			nLiveShip--;
			Rect kill = ship[ind].place;
			FillDeadZone(kill, ownField);
		}
	}
	else {
		u_state = Miss;
		cout << "*** ����! ***";
		ownField[r_fire.row][r_fire.col] = MISS;
	}
	cout << endl;
}

