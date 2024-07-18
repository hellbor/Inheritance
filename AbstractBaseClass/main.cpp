#include<iostream>
using namespace std;

class Vehicle
{
public:
	virtual void move() = 0;
};
class GroundVehicle :public Vehicle{};	//Абстрактный класс
class AirVehicle:public Vehicle
{
public:
	virtual void take_off() = 0;
	virtual void land() = 0;
};

class Bike :public GroundVehicle		//Конкретный класс
{
public:
	void move()override
	{
		cout << "Harley Davidson Едет на двух колесах" << endl;
	}
};
class Car :public GroundVehicle
{
public:
	void move()override
	{
		cout << "BMW едет на четырех колесах" << endl;
	}
};

class AirPlane:public AirVehicle
{
public:
	void move()override
	{
		cout << "Полет нормальный" << endl;
	}
	void take_off()override
	{
		take_off();
		cout << "Нужна взлетная полеса" << endl;
		land();
	}
	void land()override
	{
		cout << "Садимся на взлетку" << endl;
	}
};
class Helicopter:public AirVehicle
{
public:
	void move()override
	{
		cout << "Летим по-тихоньку" << endl;
	}
	void take_off()override
	{
		cout << "Могу взлететь с любого огорода" << endl;
	}
	void land()override
	{
		cout << "Где захочу, там и сяду" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Vehicle vehicle;
	//GroundVehicle gv;
	Bike harley_davidson;
	harley_davidson.move();

	Car bmw;
	bmw.move();

	AirPlane boeing;
	boeing.move();

	Helicopter blackHawk;
	blackHawk.move();
}