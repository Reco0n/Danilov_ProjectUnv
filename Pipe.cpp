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

std::string Pipe::GetName() const
{
	return name;
}

bool Pipe::IsInRepair() const
{
	return inRepair;
}

void Pipe::SwitchRepair()
{
	inRepair = !inRepair;
}

void Pipe::SetRepair(bool value)
{
	inRepair = value;
}

int Pipe::GetMaxID()
{
	return MaxID;
}

void Pipe::SetMaxID(int value)
{
	MaxID = value;
}

void Pipe::Save(ostream& out) const
{
	out << name << endl << length << " " << diameter << " " << inRepair << endl;
}

bool Pipe::Load(istream& in)
{
	in >> ws;
	getline(in, name);
	in >> length >> diameter >> inRepair;
	return !in.fail() && length > 0 && diameter > 0;
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
