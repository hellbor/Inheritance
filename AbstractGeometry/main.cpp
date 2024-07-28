#define _USE_MATH_DEFINES
#include<Windows.h>
#include<iostream>
using namespace std;

namespace Geometry
{
	enum Color
	{
		RED		= 0x000000FF,
		GREEN	= 0x0000FF00,
		BLUE	= 0x00FF0000,
		YELLOW	= 0x0000FFFF,
		DARK_GREEN	= 0x0000AA00,
		CONSOLE_RED = 0xCC, //старшая 'С' - цвет фона, младшая 'C' - цвет текста
		CONSOLE_GREEN = 0xAA,
		CONSOLE_BLUE = 0x99,
		CONSOLE_DEFAULT = 0x07
	};

#define SHAPE_TAKE_PARAMETERS unsigned int start_x, unsigned int start_y, unsigned int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 50;
		static const int MAX_START_X = 1000;
		static const int MAX_START_Y = 500;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 32;
		static const int MIN_SIZE = 50;
		static const int MAX_SIZE = 500;
		static int count;
	public:
		//Чисто виртуальные функции (Pure virtual functions)
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		/////////////////////////////////////////////
		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
			count++;
		}
		virtual ~Shape() 
		{
			count--;
		}

		//				Encapsulation:
		int get_count()const
		{
			return count;
		}
		unsigned int get_start_x()const
		{
			return start_x;
		}
		unsigned int get_start_y()const
		{
			return start_y;
		}
		unsigned int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(unsigned int start_x)
		{
			if (start_x < MIN_START_X)start_x = MIN_START_X;
			if (start_x > MAX_START_X)start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y < MIN_START_Y)start_y = MIN_START_Y;
			if (start_y > MAX_START_Y)start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(unsigned line_width)
		{
			this->line_width = 
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH : 
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH : 
				line_width;
		}
		int filter_size(int size)const
		{
			return
				size < MIN_SIZE ? MIN_SIZE :
				size > MAX_SIZE ? MAX_SIZE :
				size;
		}

		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	int Shape::count = 0;

	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimeter()const override
		{
			return side * 4;
		}
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << get_side() << endl;
			Shape::info();
		}
	};*/

	class Rectangle :public Shape
	{
		double width;	//ширина прямоугольника
		double height;	//высота прямоугольника
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		~Rectangle() {}
		void set_width(double width)
		{
			this->width = filter_size(width);
		}
		void set_height(double height)
		{
			this->height = filter_size(height);
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const
		{
			return width * height;
		}
		double get_perimeter()const
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//WinGDI - Windows Graphics Device Interface
			//1) Получаем окно консоли:
			//HWND hwnd = GetConsoleWindow();	//Эта функция получает окно консоли
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			//2)Для того, чтобы рисовать, нужен контекст устройства (Device Context)б
			// который есть у каждого окна. Контекст устройства можно получить при помощи функции GetDC()
			HDC hdc = GetDC(hwnd);	//Получаем контекст окна консоли
			//Контекст устройства - это то, на чем мы будем рисовать.

			//3) Теперь нам нужно то, чем мы будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);	//hPen - рисует контур фигуры
			//SP_SOLID - сплошная линия
			//5 - толщина линии
			HBRUSH hBrush = CreateSolidBrush(color);	//hBrush - рисует заливку фигуры, SolidBrush - сплошной цвет

			//4) Выбираем чем, и на чем мы будем рисовать:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			//5) рисуем фигуру:
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + height);	//:: - Global Scope (Глобальное пространство имен)

			//6)hdBrush занимают ресурсы, и после того, как мы ими воспользовались, ресурсы нужно освободить
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина прямоугольника: " << get_width() << endl;
			cout << "Высота прямоугольника: " << get_height() << endl;
			Shape::info();
		}
	};

	//class Triangle :public Shape
	//{
	//	double length;
	//	double width;
	//	double heigth;
	//public:
	//	Triangle(double length, double width, double heigth, Color color) :Shape(color)
	//	{
	//		set_lenght(length);
	//		set_width(width);
	//		set_heigth(heigth);
	//	}
	//	~Triangle() {}
	//	void set_length(double length)
	//	{
	//		this->lenght = lenght;
	//	}
	//	void set_width(double width)
	//	{
	//		this->width = widht;
	//	}
	//	void set_heigth(double heigth)
	//	{
	//		this->heigth = heigth;
	//	}
	//	double get_length()const
	//	{
	//		return length;
	//	}
	//	double get_width()const
	//	{
	//		return width;
	//	}
	//	double get_heigth()const
	//	{
	//		return heigth;
	//	}
	//	double get_area()const
	//	{
	//		return (width * heigth) / 2;
	//	}
	//	double get_perimeter()const
	//	{
	//		return length + width + heigth;
	//	}
	//	void draw()const override
	//	{
	//		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//		//HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
	//		HWND hwnd = GetConsoleWindow();
	//		HDC hdc = GetDC(hwnd);
	//		HPEN hPen = CreatePen(PS_SOLID, 3, color);
	//		HBRUSH hBrush = CreateSolidBrush(color);
	//		SelectObject(hdc, hPen);
	//		SelectObject(hdc, hBrush);

	//		//::Triangle(hdc, 10, 30, 70);

	//		DeleteObject(hBrush);
	//		DeleteObject(hPen);

	//		ReleaseDC(hwnd, hdc);

	//		for (int i = 0; i < length; i++)
	//		{
	//			for (int j = 0; j <= i; j++)
	//			{
	//				SetConsoleTextAttribute(hConsole, color);
	//				cout << "*  ";
	//				SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
	//			}
	//			//for (int j = i; j <= length; j++)cout << " ";
	//			cout << endl;
	//		}
	//	}
	//	void info()const override

	//	{
	//		cout << typeid(*this).name() << endl;
	//		cout << "Длина треугольника: " << get_length() << endl;
	//		cout << "Ширина треугольника: " << get_width() << endl;
	//		cout << "Высота треугольника: " << get_heigth() << endl;
	//		Shape::info();
	//	}
	//};
	class Square :public Rectangle
	{
	public:
		Square(double side,SHAPE_TAKE_PARAMETERS):Rectangle(side, side, SHAPE_GIVE_PARAMETERS){}
		~Square(){}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_radius(radius);
		}
		~Circle(){}
		void set_radius(double radius)
		{
			this->radius = filter_size(radius);
		}
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return 2 * radius;
		}
		double get_area()const
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const override
		{
			return M_PI * get_diameter();
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());

			// Очищаем ресурсы:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус круга: " << get_radius() << endl;
			cout << "Диаметр круга: " << get_diameter() << endl;
			Shape::info();
		}
	};
	class Triangle :public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS){}
		~Triangle() {}
		virtual double get_height()const = 0;
		void info()const override
		{
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		EquilateralTriangle(double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		~EquilateralTriangle(){}
		void set_side(double side)
		{
			this->side = filter_size(side);
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const override
		{
			return side * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return 3 * side;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			::Polygon(hdc, vertices, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны :" << get_side() << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double base;
		double side;
	public:
		IsoscelesTriangle(double base, double side, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_base(base);
			set_side(side);
		}
		~IsoscelesTriangle(){}
		void set_base(double base)
		{
			this->base = filter_size(base);
		}
		void set_side(double side)
		{
			this->side = filter_size(side);
			if (this->side <= base / 2)
				this->side = base * 3 / 5;
		}
		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const override
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}
		double get_area()const override
		{
			return base * get_height() / 2;
		}
		double get_perimeter()const override
		{
			return base + side * 2;
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x,start_y + side},
				{start_x + base,start_y + side},
				{start_x + base / 2,start_y + side - get_height()},
			};

			::Polygon(hdc, vertices, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание треугольника: " << get_base() << endl;
			cout << "Сторона треугольника: " << get_side() << endl;
			Triangle::info();
		}
	};
	class RightTriangle :public Triangle
	{
		double catheter_1;
		double catheter_2;
	public:
		RightTriangle(double catheter_1, double catheter_2, SHAPE_TAKE_PARAMETERS) :Triangle(SHAPE_GIVE_PARAMETERS)
		{
			set_catheter_1(catheter_1);
			set_catheter_2(catheter_2);
		}
		void set_catheter_1(double catheter_1)
		{
			this->catheter_1 = filter_size(catheter_1);
		}
		void set_catheter_2(double catheter_2)
		{
			this->catheter_2 = filter_size(catheter_2);
		}
		double get_catheter_1()const
		{
			return catheter_1;
		}
		double get_catheter_2()const
		{
			return catheter_2;
		}
		double get_hypotenuse()const
		{
			return sqrt(pow(catheter_1,2)+pow(catheter_2,2));
		}
		double get_height()const override
		{
			return catheter_2;
		}
		double get_area()const override
		{
			return catheter_1 * catheter_2 / 2;
		}
		double get_perimeter()const override
		{
			return catheter_1 + catheter_2 + get_hypotenuse();
		}
		void draw()const override
		{
			HWND hwnd = FindWindow(NULL, L"Inheritance - Microsoft Visual Studio");
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertices[] =
			{
				{start_x, start_y},
				{start_x, start_y + get_height()},
				{start_x + catheter_1, start_y + get_height()},
			};
				
			::Polygon(hdc, vertices, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
			void info()const override
			{
				cout << typeid(*this).name() << endl;
				cout << "Катет треугольника 1: " << get_catheter_1() << endl;
				cout << "Катет треугольника 2: " << get_catheter_2() << endl;
				cout << "Гипотенуза треугольника : " << get_hypotenuse() << endl;
				Triangle::info();
			}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
	Geometry::Square square(50, 100, 100, 5, Geometry::Color::RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;*/
	square.draw();
	square.info();

	Geometry::Rectangle rect(150, 130, 300, 120, 1, Geometry::Color::BLUE);
	rect.info();

	//Geometry::Triangle triangle(10, 30, 70, Geometry::Color::CONSOLE_GREEN);
	//triangle.info();

	Geometry::EquilateralTriangle e_triangle(150, 300, 100, 5, Geometry::Color::DARK_GREEN);
	e_triangle.info();

	Geometry::Circle disk(10000, 500,100, 5, Geometry::Color::YELLOW);
	disk.info();

	Geometry::IsoscelesTriangle iso_triangle(200, 10, 500, 200, 5, Geometry::Color::DARK_GREEN);
	iso_triangle.info();

	Geometry::RightTriangle r_triangle(200, 100, 400, 300, 5, Geometry::Color::DARK_GREEN);
	r_triangle.info();

	cout << "Количество фигур: " << disk.get_count() << endl;
}