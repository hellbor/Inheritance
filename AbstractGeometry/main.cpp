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
		}
		virtual ~Shape() {}

		//				Encapsulation:
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
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			this->start_y = start_y;
		}
		void set_line_width(unsigned line_width)
		{
			this->line_width = line_width;
		}

		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

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
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
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
	//	double lenght;
	//	double width;
	//	double height;
	//public:
	//	Triangle(double lenght, double widht, double height, Color color) :Shape(color)
	//	{
	//		set_lenght(lenght);
	//		set_widht(widht);
	//		set_height(height);
	//	}
	//	~Triangle() {}
	//	void set_lenght(double lenght)
	//	{
	//		this->lenght = lenght;
	//	}
	//	void set_widht(double widht)
	//	{
	//		this->width = widht;
	//	}
	//	void set_height(double height)
	//	{
	//		this->height = height;
	//	}
	//	double get_lenght()const
	//	{
	//		return lenght;
	//	}
	//	double get_widht()const
	//	{
	//		return width;
	//	}
	//	double get_height()const
	//	{
	//		return height;
	//	}
	//	double get_area()const
	//	{
	//		return (width * height) / 2;
	//	}
	//	double get_perimeter()const
	//	{
	//		return lenght + width + height;
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

	//		for (int i = 0; i < lenght; i++)
	//		{
	//			for (int j = 0; j <= i; j++)
	//			{
	//				SetConsoleTextAttribute(hConsole, color);
	//				cout << "*  ";
	//				SetConsoleTextAttribute(hConsole, Color::CONSOLE_DEFAULT);
	//			}
	//			//for (int j = i; j <= lenght; j++)cout << " ";
	//			cout << endl;
	//		}
	//	}
	//	void info()const override

	//	{
	//		cout << typeid(*this).name() << endl;
	//		cout << "Длина треугольника: " << get_lenght() << endl;
	//		cout << "Ширина треугольника: " << get_widht() << endl;
	//		cout << "Высота треугольника: " << get_height() << endl;
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
			this->radius = radius;
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

			::Ellipse(hdc, start_x, start_y, start_x+get_diameter(), start_y + get_diameter());

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
}

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::CONSOLE_RED);
	Geometry::Square square(5, 100, 100, 5, Geometry::Color::RED);
	/*cout << "Длина стороны: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimeter() << endl;*/
	square.draw();
	square.info();

	Geometry::Rectangle rect(100, 50, 200, 100, 10, Geometry::Color::BLUE);
	rect.info();

	//Geometry::Triangle triangle(10, 30, 70, Geometry::Color::CONSOLE_GREEN);
	//triangle.info();

	Geometry::Circle disk(100, 500,100, 5, Geometry::Color::YELLOW);
	disk.info();
}