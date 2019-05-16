#include "pch.h"
#include <iostream>
using namespace std;
class Diapason
{
private:
	int left;
	int right;
public:
	Diapason(int left, int right) : left(left), right(right) {}

	~Diapason() {}

    Diapason() {
        left = 0;
        right = 0;
    }

    Diapason(Diapason &other) {
        left = other.left;
        right = other.right;
    }

    Diapason(Diapason &&other) {
        left = other.left;
        right = other.right;
        other.left = other.right = 0;
    }

	void insert() {
		cout << "Insert left range of edge: ";
		cin >> left;
		cout << "\nInsert right range of edge: ";
		cin >> right;
	}

	int getLeft() {
		return left;
	}
	int getRight() {
		return right;
	}

	int findLength() {
		return right - left;
	}
	bool checkForExist(int checkValue) {
		if (checkValue >= left && checkValue <= right)
            return true;
		else 
            return false;
	}

	bool intersection(Diapason x) {
		if (x.left >= left && x.left <= right || x.right >= left && x.right <= right)
            return true;
		else 
            return false;
	}
};

int main()
{
	Diapason D1(-10, -3);
	Diapason D2(-5, 4);
	cout << "Length of diapason is " << D1.findLength() << endl;;
	cout << D1.checkForExist(-10);
	cout <<"\Intersection: "<<D1.intersection(D2) << endl;
	return 0;
}

//1.«ДИАПАЗОН НА ЧИСЛОВОЙ ПРЯМОЙ».
//ДАННЫЕ КЛАССА : ЛЕВАЯ ГРАНИЦА ДИАПАЗОНА, ПРАВАЯ ГРАНИЦА ДИАПАЗОНА.
//ФУНКЦИИ КЛАССА : СРАВНЕНИЕ ДВУХ ДИАПАЗОНОВ, НАХОЖДЕНИЕ ДЛИНЫ ДИАПАЗОНА, 
//ПРОВЕРКА, ПОПАДАЕТ ЛИ НЕКОТОРОЕ ЧИСЛО В ДИАПАЗОН, ПРОВЕРКА, ПЕРЕСЕКАЮТСЯ ЛИ ДИАПАЗОНЫ.
