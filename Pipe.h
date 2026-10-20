#pragma once
#include <iostream>
#include <string>

class Pipe
{
	int id;
public:
	static int MaxID;
	std::string name;
	double length;
	int diameter;
	bool inRepair;

	Pipe();
	int GetId() const;
	void SwitchRepair();

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
};
