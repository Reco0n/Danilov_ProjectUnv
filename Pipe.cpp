#include "Pipe.h"
#include "Utils.h"
using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe()
{
	id = ++MaxID;
	name = "Unknown";
	length = 1;
	diameter = 1;
	inRepair = false;
}

int Pipe::GetId() const
{
	return id;
}

void Pipe::SwitchRepair()
{
	inRepair = !inRepair;
}

ostream& operator << (ostream& out, const Pipe& p)
{
	out << "---Труба #" << p.id << "---" << endl
		<< "Название: " << p.name << endl
		<< "Длина: " << p.length << endl
		<< "Диаметр: " << p.diameter << endl
		<< "Статус: " << (p.inRepair ? "в ремонте" : "в работе") << endl;
	return out;
}

istream& operator >> (istream& in, Pipe& p)
{
	cout << "Название: ";
	INPUT_LINE(in, p.name);
	cout << "Длина (км): ";
	p.length = GetCorrectNumber(0.001, 100000.0);
	cout << "Диаметр (мм): ";
	p.diameter = GetCorrectNumber(1, 100000);
	p.inRepair = false;
	return in;
}
