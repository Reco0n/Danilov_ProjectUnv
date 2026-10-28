#pragma once
#include <iostream>
#include <string>

class Pipe
{
	int id;
	static int MaxID;
	std::string name;
	double length;
	int diameter;
	bool inRepair;

public:
	Pipe();
	int GetId() const;
	std::string GetName() const;
	bool IsInRepair() const;
	void SwitchRepair();
	void SetRepair(bool value);

	static int GetMaxID();
	static void SetMaxID(int value);

	void Save(std::ostream& out) const;
	bool Load(std::istream& in);

	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
};
