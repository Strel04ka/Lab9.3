#include <iostream>
#include <string>
#include <ctime>
using namespace std;
struct departuretime;
struct departuretime
{
	departuretime() { HH = MM = 0; }
	departuretime(unsigned int hh, unsigned int mm)
	{
		HH = hh, MM = mm;
	}
	unsigned int HH : 5;
	unsigned int MM : 6;
};
struct Grafik
{
	string Caption;
	enum type { normal, comfortplus, speedexpres } Type;
	departuretime Deaprturetime;
};
Grafik* Add(Grafik* routes, int& sizeВ);
void AutoFill(Grafik* routes, int& size);
void StartMenu(Grafik* routes, int& size);
void Print(Grafik* routes, int& size);
Grafik* Remove(Grafik* routes, int& size);
void Change(Grafik* routes, int& size);
void SortRoutes(Grafik* routes, int& size);
void SeekByTime(Grafik* routes, int& size);

void main()
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "ukr");
	cout << "Enter the count of marchroots in the array:"; int size; cin >> size;
	Grafik* arr = new Grafik[size];
	AutoFill(arr, size);
	StartMenu(arr, size);


	system("pause");
}
Grafik* Remove(Grafik* routes, int& size)
{
	Print(routes, size);
	cout << endl << endl;
	Grafik* newroutes = new Grafik[size - 1];
	cout << "Enter the index of a marchroot which you want to remove: ";
	int index;
	cin >> index;
	bool moved = false;
	for (size_t i = 0; i < size - 1; i++)
	{

		if (i == index)  	moved = true;
		if (moved)	newroutes[i] = routes[i + 1];
		else	newroutes[i] = routes[i];
	}
	--size;
	routes = newroutes;
	return newroutes;
}
Grafik* Add(Grafik* routes, int& size)
{
	Grafik newgrafik;
	cout << "Caption:"; cin >> newgrafik.Caption;
	cout << "Type:(0.normal\t1.fastexpress\t 2.comfortplus)\n";
	int ch; cin >> ch;
	switch (ch)
	{
	case 0:
	{
		newgrafik.Type = (Grafik::type)ch;
		break;
	}
	case 1:
	{
		newgrafik.Type = (Grafik::type)ch;
		break;
	}
	case 2:
	{
		newgrafik.Type = (Grafik::type)ch;
		break;
	}
	default:
		break;
	}
	cout << "Departure time:\n";
	int hh, mm;
	cout << "Hours:"; cin >> hh;
	cout << "Minutes: "; cin >> mm;
	if (hh > 24) hh %= 24;
	if (mm > 60)mm %= 60;
	newgrafik.Deaprturetime = departuretime(hh, mm);
	Grafik* newroutes = new Grafik[size + 1];
	for (size_t i = 0; i < size; i++)
	{
		newroutes[i] = routes[i];
	}
	newroutes[size] = newgrafik;
	size++;
	return newroutes;
}
void AutoFill(Grafik* routes, int& size)
{
	for (size_t i = 0; i < size; i++)
	{
		routes[i].Caption = "Binych" + to_string(i);
		routes[i].Type = Grafik::normal;
		routes[i].Deaprturetime = departuretime((unsigned int)(rand() % 24), (unsigned int)(rand() % 60));

	}
}
void StartMenu(Grafik* routes, int& size)
{
	int choice;
	do
	{
		cout << "------------Menu------------" << endl;
		cout << "1.Додати маршрут.\n" <<
			"2.Видалити маршрут\n" <<
			"3.Редагувати маршрут\n" <<
			"4.Сортувати розклад\n" <<
			"5.Ввести час.\n" <<
			"6.Показати всі маршрути\n" <<
			"7.Exit.\n" << endl << endl;
		cout << "Your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			routes = Add(routes, size);
			break;
		}
		case 2:
		{
			routes = Remove(routes, size);
			break;
		}
		case 3:
		{
			Change(routes, size);
			break;
		}
		case 4:
		{
			SortRoutes(routes, size);
			break;
		}
		case 5:
		{
			SeekByTime(routes, size);
			break;
		}
		case 6:
		{
			Print(routes, size);
			break;
		}
		default:
			break;
		}
	} while (choice != 7);
}
void Print(Grafik* routes, int& size)
{
	cout << "№\t|Name\t|Type\t|Departure Time |" << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << i << "\t|";
		cout << routes[i].Caption << "\t|";
		switch (routes[i].Type)
		{
		case Grafik::normal: { cout << "normal\t|";			break; }
		case Grafik::speedexpres: { cout << "fastexpress\t|";	break; }
		case Grafik::comfortplus: { cout << "comfortplus\t|";	break; }
		default:
			break;
		}
		cout << routes[i].Deaprturetime.HH << ":" << routes[i].Deaprturetime.MM << "|";
		cout << endl;
	}
}
void Change(Grafik* routes, int& size)
{
	Print(routes, size);
	cout << endl << endl;
	cout << "Enter the index of the element which you want to change: ";
	int choice; cin >> choice;
	cout << "Name of route:"; cin >> routes[choice].Caption; cout << endl;
	short int ch;
	cout << "type of route:"; cin >> ch; cout << endl;
	switch (ch)
	{
	case 0: { routes[choice].Type = Grafik::normal;	  break; }
	case 1: { routes[choice].Type = Grafik::comfortplus; break; }
	case 2: { routes[choice].Type = Grafik::speedexpres; break; }
	default: {
		cout << "Invalid command.The property is defined as normal." << endl;
		routes[choice].Type = Grafik::normal;
		break;
	}
	}
	int a, b;
	cout << "Departure time: "; cin >> a >> b;
	routes[choice].Deaprturetime = departuretime(a, b);
}
void SortRoutes(Grafik* routes, int& size)
{
	int choice;
	system("cls");
	cout << "===sorting menu===" << endl << endl;
	cout << "1.Sort by name of stations.\n" <<
		"2.Sort by departure time." << endl;
	cout << "Enter the method which you want to sort the list: ";
	cin >> choice; cout << endl;
	Print(routes, size);
	switch (choice)
	{
	case 1:
	{
		for (size_t j = 1; j < size; j++)
		{
			for (size_t i = 0; i < size - i; i++)
			{
				if (routes[i].Caption > routes[i + 1].Caption)
				{
					Grafik temp = routes[i];
					routes[i] = routes[i + 1];
					routes[i + 1] = temp;
				}

			}
		}
		cout << "done." << endl;
		break;
	}
	case 2:
	{
		for (size_t j = 1; j < size; j++)
		{
			for (size_t i = 0; i < size - j; i++)
			{
				if ((routes[i].Deaprturetime.HH >= routes[i + 1].Deaprturetime.HH))/*||
				   ((routes[i].Deaprturetime.HH == routes[i + 1].Deaprturetime.HH)&&(routes[i].Deaprturetime.MM > routes[i + 1].Deaprturetime.MM)))*/
				{
					swap(routes[i], routes[i + 1]);
				}
			}
		}
		cout << "done." << endl;
		break;
	}
	default:
		break;
	}
	Print(routes, size);

}
void SeekByTime(Grafik* routes, int& size)
{
	cout << "Enter the time after which you want to see the routes: ";
	int hh, mm;
	cin >> hh, mm;
	cout << endl << endl;
	cout << "№\t|Name\t|Type\t|Departure Time |" << endl;
	for (size_t i = 0; i < size; i++)
	{
		if ((routes[i].Deaprturetime.HH > hh))
		{
			cout << i << "\t|";
			cout << routes[i].Caption << "\t|";
			switch (routes[i].Type)
			{
			case Grafik::normal: { cout << "normal\t|";			break; }
			case Grafik::speedexpres: { cout << "fastexpress\t|";	break; }
			case Grafik::comfortplus: { cout << "comfort plus\t|";	break; }
			default:break;
			}
			cout << routes[i].Deaprturetime.HH << ":" << routes[i].Deaprturetime.MM << "|" << endl;

		}
	}
}
