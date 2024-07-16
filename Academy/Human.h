#pragma once
#include<iostream>
#include<fstream>
#include<string>	//�������� ����� std::string
#include<string.h>	//��������� ������� ��� ������ � NULL Terminated Line
using std::cout;
using std::cin;
using std::endl;

#define delimiter "\n--------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int TYPE_WIDTH = 12;
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 5;
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(int age)
	{
		this->age = age;
	}

	//				Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual std::ostream& print(std::ostream& os)const
	{
		//os << strchr(typeid(*this).name(), ' ') + 1 << ":\t";	//�������� typeid(type | value) ���������� ��� �������� �� ����� ���������� ���������
												//����� name() ���������� C_string() ���������� ��� ����
		return os << " " << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs.width(TYPE_WIDTH);	//����� width() ������ ������ ������.
		//��� ������ ������ ����� width() �������� ������������ �� ������� ����
		ofs << std::left;	//���������� ������������ �� ������ ����.
		//���� ����� width() ������ �� ���� �������� ��������
		ofs << std::string(strchr(typeid(*this).name(), ' ') + 1) << ":";
		ofs.width(LAST_NAME_WIDTH);
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs << age;
		return ofs;
	}
};