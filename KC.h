#pragma once
#include <iostream>
#include <string>

class KC
{
	int id;
	static int MaxID;
	std::string name;
	int total;
	int working;
	int level;

public:
	KC();
	int GetId() const;
	std::string GetName() const;
	int GetWorking() const;
	double UnusedPercent() const;
	bool StartFactory();
	bool StopFactory();

	static int GetMaxID();
	static void SetMaxID(int value);

	void Save(std::ostream& out) const;
	bool Load(std::istream& in);

	friend std::ostream& operator << (std::ostream& out, const KC& k);
	friend std::istream& operator >> (std::istream& in, KC& k);
};
