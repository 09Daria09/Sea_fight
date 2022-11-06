#include<string>
#include<algorithm>
#include "Ship.h"
#include <iterator>
using namespace std;

bool ElementCell::InSet(const CellSet& cs)const{
	return(cs.count(ElementCell(row, col)) > 0); //count - Возвращает количество элементов с заданным значением.
}
bool ElementCell::operator<(const ElementCell& c)const{
	return ((row < c.row) || ((row == c.row) && (col < c.col)));
}

void Area::FillCset(){
	for (int i = LeftTop.row; i <= RightBottom.row; i++)
		for (int j = LeftTop.col; j <= RightBottom.col; j++)
			cset.insert(ElementCell(i, j));
	/*insert - Вставляет в середину строки несколько символов, другую строку или фрагмент другой строки.*/
}
bool Area::Cross(const CellSet& cs)const{
	CellSet common_cell;
	set_intersection(cset.begin(), cset.end(), cs.begin(), cs.end(),
		inserter(common_cell, common_cell.begin())); 
	 /*set_intersectio для получения пересечения множеств в программу
		 необходимо включить библиотеку алгоритмов, в которой есть функция
	  inserter — специальный тип итератора вывода который добавляет элементы из контейнера A в контейнер B*/ 
	return (common_cell.size() > 0);
}
Ship::Ship(int _nDeck, string _name, Area _place):
	place(_place), name(_name), CountDeck(_nDeck), CountLiveDeck(_nDeck) {}