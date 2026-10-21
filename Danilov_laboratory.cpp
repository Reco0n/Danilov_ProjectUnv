#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "Pipe.h"
#include "KC.h"
#include "Utils.h"

using namespace std;

// ---------- Фильтры и поиск (как в лекции: указатель на функцию-фильтр) ----------

bool CheckPipeByName(const Pipe& p, string param)
{
	return p.name.find(param) != string::npos;
}
bool CheckPipeByRepair(const Pipe& p, bool param)
{
	return p.inRepair == param;
}
bool CheckKCByName(const KC& k, string param)
{
	return k.name.find(param) != string::npos;
}
bool CheckKCByUnusedMin(const KC& k, double param)
{
	return k.UnusedPercent() >= param;
}
bool CheckKCByUnusedMax(const KC& k, double param)
{
	return k.UnusedPercent() <= param;
}

// Возвращает индексы найденных объектов
template<typename T, typename P>
vector<int> FindByFilter(const vector<T>& items, bool (*f)(const T&, P), P param)
{
	vector<int> res;
	int i = 0;
	for (auto& item : items)
	{
		if (f(item, param))
			res.push_back(i);
		i++;
	}
	return res;
}

// Индекс объекта по уникальному id, -1 если не найден
template<typename T>
int FindIndexById(const vector<T>& items, int id)
{
	for (int i = 0; i < (int)items.size(); i++)
		if (items[i].GetId() == id)
			return i;
	return -1;
}

template<typename T>
void PrintByIndexes(const vector<T>& items, const vector<int>& indexes)
{
	cout << "Найдено: " << indexes.size() << endl;
	for (int i : indexes)
		cout << items[i] << endl;
}

// Запрашивает id и возвращает индекс объекта (-1 если нет)
template<typename T>
int SelectIndex(const vector<T>& items)
{
	cout << "Введите ID: ";
	int index = FindIndexById(items, GetCorrectNumber(1, 1000000));
	if (index == -1)
		cout << "Объект с таким ID не найден" << endl;
	return index;
}

vector<int> FindPipes(const vector<Pipe>& pipes)
{
	cout << "Фильтр: 1.По названию  2.По признаку \"в ремонте\": ";
	if (GetCorrectNumber(1, 2) == 1)
	{
		string name;
		cout << "Часть названия: ";
		INPUT_LINE(cin, name);
		return FindByFilter(pipes, CheckPipeByName, name);
	}
	cout << "В ремонте? (1-да, 0-нет): ";
	return FindByFilter(pipes, CheckPipeByRepair, GetCorrectNumber(0, 1) == 1);
}

vector<int> FindKCs(const vector<KC>& stations)
{
	cout << "Фильтр: 1.По названию  2.По проценту незадействованных цехов: ";
	if (GetCorrectNumber(1, 2) == 1)
	{
		string name;
		cout << "Часть названия: ";
		INPUT_LINE(cin, name);
		return FindByFilter(stations, CheckKCByName, name);
	}
	cout << "1.Не меньше  2.Не больше: ";
	int mode = GetCorrectNumber(1, 2);
	cout << "Процент (0-100): ";
	double percent = GetCorrectNumber(0.0, 100.0);
	if (mode == 1)
		return FindByFilter(stations, CheckKCByUnusedMin, percent);
	return FindByFilter(stations, CheckKCByUnusedMax, percent);
}

// ---------- Редактирование ----------

void EditKC(KC& k)
{
	cout << "1.Запуск цеха  2.Остановка цеха: ";
	bool ok = GetCorrectNumber(1, 2) == 1 ? k.StartFactory() : k.StopFactory();
	if (!ok)
		cout << "Действие невозможно" << endl;
	cout << "Цехов в работе: " << k.working << endl;
}

bool Contains(const vector<int>& v, int x)
{
	for (int a : v)
		if (a == x)
			return true;
	return false;
}

// Пакетное редактирование: все найденные трубы или выбранные пользователем
void BatchEditPipes(vector<Pipe>& pipes)
{
	vector<int> found = FindPipes(pipes);
	PrintByIndexes(pipes, found);
	if (found.empty())
		return;

	vector<int> ids;
	for (int i : found)
		ids.push_back(pipes[i].GetId());

	cout << "1.Все найденные  2.Выбрать по ID: ";
	if (GetCorrectNumber(1, 2) == 2)
	{
		vector<int> chosen;
		cout << "Вводите ID по одному, 0 - закончить" << endl;
		while (int id = GetCorrectNumber(0, 1000000))
			if (Contains(ids, id) && !Contains(chosen, id))
				chosen.push_back(id);
			else
				cout << "ID не из найденных или уже выбран" << endl;
		ids = chosen;
	}

	cout << "1.В ремонт  2.В работу  3.Удалить: ";
	int action = GetCorrectNumber(1, 3);
	for (int id : ids)
	{
		int i = FindIndexById(pipes, id);
		if (action == 3)
			pipes.erase(pipes.begin() + i);
		else if (pipes[i].inRepair != (action == 1))
			pipes[i].SwitchRepair();
	}
	cout << "Обработано труб: " << ids.size() << endl;
}

// ---------- Сохранение и загрузка ----------

void SavePipe(ofstream& fout, const Pipe& p)
{
	fout << p.name << endl << p.length << " " << p.diameter << " " << p.inRepair << endl;
}
void SaveKC(ofstream& fout, const KC& k)
{
	fout << k.name << endl << k.total << " " << k.working << " " << k.level << endl;
}

Pipe LoadPipe(ifstream& fin)
{
	Pipe p;
	fin >> ws;
	getline(fin, p.name);
	fin >> p.length >> p.diameter >> p.inRepair;
	return p;
}
KC LoadKC(ifstream& fin)
{
	KC k;
	fin >> ws;
	getline(fin, k.name);
	fin >> k.total >> k.working >> k.level;
	return k;
}

void SaveToFile(const vector<Pipe>& pipes, const vector<KC>& stations)
{
	string filename;
	cout << "Имя файла: ";
	INPUT_LINE(cin, filename);
	ofstream fout(filename);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
		return;
	}
	fout << pipes.size() << " " << stations.size() << endl;
	for (auto& p : pipes)
		SavePipe(fout, p);
	for (auto& k : stations)
		SaveKC(fout, k);
	cout << "Сохранено" << endl;
}

void LoadFromFile(vector<Pipe>& pipes, vector<KC>& stations)
{
	string filename;
	cout << "Имя файла: ";
	INPUT_LINE(cin, filename);
	ifstream fin(filename);
	if (!fin.is_open())
	{
		cout << "Файл не найден" << endl;
		return;
	}
	// Читаем во временные списки: при ошибке в файле текущие данные не теряются
	int oldPipeId = Pipe::MaxID, oldKCId = KC::MaxID;
	Pipe::MaxID = 0;	// id после загрузки назначаются заново и остаются уникальными
	KC::MaxID = 0;
	vector<Pipe> newPipes;
	vector<KC> newStations;
	int pipeCount = 0, kcCount = 0;
	bool ok = !(fin >> pipeCount >> kcCount).fail() && pipeCount >= 0 && kcCount >= 0;
	for (int i = 0; ok && i < pipeCount; i++)
	{
		Pipe p = LoadPipe(fin);
		ok = !fin.fail() && p.length > 0 && p.diameter > 0;
		newPipes.push_back(p);
	}
	for (int i = 0; ok && i < kcCount; i++)
	{
		KC k = LoadKC(fin);
		ok = !fin.fail() && k.total > 0 && k.level > 0 && k.working >= 0 && k.working <= k.total;
		newStations.push_back(k);
	}
	if (!ok)
	{
		Pipe::MaxID = oldPipeId;
		KC::MaxID = oldKCId;
		cout << "Ошибка: неверный формат файла" << endl;
		return;
	}
	pipes = newPipes;
	stations = newStations;
	cout << "Загружено" << endl;
}

// ---------- Меню ----------

void PrintMenu()
{
	cout << endl
		<< "1. Добавить трубу" << endl
		<< "2. Добавить КС" << endl
		<< "3. Просмотр всех объектов" << endl
		<< "4. Редактировать трубу" << endl
		<< "5. Редактировать КС" << endl
		<< "6. Удалить трубу" << endl
		<< "7. Удалить КС" << endl
		<< "8. Поиск труб" << endl
		<< "9. Поиск КС" << endl
		<< "10. Пакетное редактирование труб" << endl
		<< "11. Сохранить в файл" << endl
		<< "12. Загрузить из файла" << endl
		<< "0. Выход" << endl
		<< "Выберите действие: ";
}

int main()
{
	// Лог: все вводы пользователя пишутся в cerr, который перенаправлен в файл
	redirect_output_wrapper cerr_out(cerr);
	char buf[64];
	time_t t = time(nullptr);
	strftime(buf, sizeof(buf), "%d_%m_%Y_%H_%M_%S", localtime(&t));
	ofstream logfile(string("log_") + buf + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	vector<Pipe> pipes;
	vector<KC> stations;

	while (true)
	{
		PrintMenu();
		int choice = GetCorrectNumber(0, 12);
		cerr << "Пункт меню " << choice << endl;

		switch (choice)
		{
		case 1:
		{
			Pipe p;
			cin >> p;
			pipes.push_back(p);
			cout << "Труба добавлена, ID " << p.GetId() << endl;
			break;
		}
		case 2:
		{
			KC k;
			cin >> k;
			stations.push_back(k);
			cout << "КС добавлена, ID " << k.GetId() << endl;
			break;
		}
		case 3:
		{
			if (pipes.empty())
				cout << "Труб нет" << endl;
			for (auto& p : pipes)
				cout << p << endl;
			if (stations.empty())
				cout << "КС нет" << endl;
			for (auto& k : stations)
				cout << k << endl;
			break;
		}
		case 4:
		{
			int i = SelectIndex(pipes);
			if (i != -1)
			{
				pipes[i].SwitchRepair();
				cout << "Статус: " << (pipes[i].inRepair ? "в ремонте" : "в работе") << endl;
			}
			break;
		}
		case 5:
		{
			int i = SelectIndex(stations);
			if (i != -1)
				EditKC(stations[i]);
			break;
		}
		case 6:
		{
			int i = SelectIndex(pipes);
			if (i != -1)
				pipes.erase(pipes.begin() + i);
			break;
		}
		case 7:
		{
			int i = SelectIndex(stations);
			if (i != -1)
				stations.erase(stations.begin() + i);
			break;
		}
		case 8:
		{
			PrintByIndexes(pipes, FindPipes(pipes));
			break;
		}
		case 9:
		{
			PrintByIndexes(stations, FindKCs(stations));
			break;
		}
		case 10:
		{
			BatchEditPipes(pipes);
			break;
		}
		case 11:
		{
			SaveToFile(pipes, stations);
			break;
		}
		case 12:
		{
			LoadFromFile(pipes, stations);
			break;
		}
		case 0:
		{
			return 0;
		}
		}
	}
}
