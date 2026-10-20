#pragma once
#include <iostream>
#include <string>

class KC
{
	int id;
public:
	static int MaxID;
	std::string name;
	int total;
	int working;
	int level;

	KC();
	int GetId() const;
	double UnusedPercent() const;
	bool StartFactory();
	bool StopFactory();

	friend std::ostream& operator << (std::ostream& out, const KC& k);
	friend std::istream& operator >> (std::istream& in, KC& k);
};
