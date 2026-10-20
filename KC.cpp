#include "KC.h"
#include "Utils.h"
using namespace std;

int KC::MaxID = 0;

KC::KC()
{
	id = ++MaxID;
	name = "Unknown";
	total = 1;
	working = 0;
	level = 1;
}

int KC::GetId() const
{
	return id;
}

double KC::UnusedPercent() const
{
	return 100.0 * (total - working) / total;
}

bool KC::StartFactory()
{
	if (working >= total)
		return false;
	working++;
	return true;
}

bool KC::StopFactory()
{
	if (working <= 0)
		return false;
	working--;
	return true;
}

ostream& operator << (ostream& out, const KC& k)
{
	out << "---КС #" << k.id << "---" << endl
		<< "Название: " << k.name << endl
		<< "Всего цехов: " << k.total << endl
		<< "Цехов в работе: " << k.working << endl
		<< "Незадействовано: " << k.UnusedPercent() << "%" << endl
		<< "Класс станции: " << k.level << endl;
	return out;
}

istream& operator >> (istream& in, KC& k)
{
	cout << "Название КС: ";
	INPUT_LINE(in, k.name);
	cout << "Кол-во цехов: ";
	k.total = GetCorrectNumber(1, 100000);
	cout << "Кол-во цехов в работе: ";
	k.working = GetCorrectNumber(0, k.total);
	cout << "Класс станции: ";
	k.level = GetCorrectNumber(1, 100000);
	return in;
}
