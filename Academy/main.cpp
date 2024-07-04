﻿#include<iostream>
#include<string>
using namespace std;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
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
	~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << endl;
	}
};

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student : public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_spetiality()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	double get_rating()const
	{
		return rating;
	}
	double get_attendance()const
	{
		return attendance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(double rating)
	{
		this->rating = rating;
	}
	void set_attendance(double attendance)
	{
		this->attendance = attendance;
	}

	//				Constructors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		Human::print();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality,int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience
class Teacher :public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}

	//				Constructors:
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		Human::print();
		cout << speciality << " " << experience << " years" << endl;
	}
};

#define GRADUATE_TAKE_PARAMETERS const std::string& faculty, const std::string& speciality, int year, int grade
#define GRADUATE_GIVE_PARAMETERS faculty, speciality, year, grade

class Graduate : public Human
{
	std::string faculty;
	std::string speciality;
	int year;
	int grade;
public:
	const std::string& get_faculty()const
	{
		return faculty;
	}
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_year()const
	{
		return year;
	}
	int get_grade()const
	{
		return grade;
	}
	void set_faculty(const std::string& faculty)
	{
		this->faculty = faculty;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_year(int year)
	{
		this->year = year;
	}
	void set_grade(int grade)
	{
		this->grade = grade;
	}

	//				Constructors:
	Graduate(HUMAN_TAKE_PARAMETERS, GRADUATE_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_faculty(faculty);
		set_speciality(speciality);
		set_year(year);
		set_grade(grade);
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		Human::print();
		cout << faculty << " " << speciality << " " << year << " " << grade << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "HelloAcademy" << endl;
	Human human("Richter", "Jeffrey", 40);
	human.print();

	Student student("Pinkman", "Jessie", 20, "Chenistry", "WW_220", 95, 90);
	student.print();

	Teacher teacher("White", "Walter", 50, "Chemistry", 25);
	teacher.print();

	Graduate graduate("William", "Johns", 22, "Technical", "Robotics", 5, 95);
	graduate.print();
}