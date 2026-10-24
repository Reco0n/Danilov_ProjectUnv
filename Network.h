#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "KC.h"

class Network
{
	std::unordered_map<int, Pipe> pipes;
	std::unordered_map<int, KC> stations;
public:
	void AddPipe();
	void AddKC();
	void ShowAll() const;

	void EditPipe();
	void EditKC();
	void DeletePipe();
	void DeleteKC();

	void SearchPipes() const;
	void SearchKCs() const;
	void BatchEditPipes();

	void Save() const;
	void Load();
};
