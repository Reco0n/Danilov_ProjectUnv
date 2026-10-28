#include "Network.h"
#include "Utils.h"
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool CheckPipeByName(const Pipe& p, string param)
{
	return p.GetName().find(param) != string::npos;
}
bool CheckPipeByRepair(const Pipe& p, bool param)
{
	return p.IsInRepair() == param;
}
bool CheckKCByName(const KC& k, string param)
{
	return k.GetName().find(param) != string::npos;
}
bool CheckKCByUnusedMin(const KC& k, double param)
{
	return k.UnusedPercent() >= param;
}
bool CheckKCByUnusedMax(const KC& k, double param)
{
	return k.UnusedPercent() <= param;
}

template<typename T>
vector<int> SortedIds(const unordered_map<int, T>& items)
{
	vector<int> ids;
	for (auto& kv : items)
		ids.push_back(kv.first);
	sort(ids.begin(), ids.end());
	return ids;
}

template<typename T, typename P>
vector<int> FindByFilter(const unordered_map<int, T>& items, bool (*f)(const T&, P), P param)
{
	vector<int> res;
	for (auto& kv : items)
		if (f(kv.second, param))
			res.push_back(kv.first);
	sort(res.begin(), res.end());
	return res;
}

template<typename T>
void PrintByIds(const unordered_map<int, T>& items, const vector<int>& ids)
{
	cout << "Найдено: " << ids.size() << endl;
	for (int id : ids)
		cout << items.at(id) << endl;
}

template<typename T>
int SelectId(const unordered_map<int, T>& items)
{
	cout << "Введите ID: ";
	int id = GetCorrectNumber(1, 1000000);
	if (items.count(id) == 0)
	{
		cout << "Объект с таким ID не найден" << endl;
		return 0;
	}
	return id;
}

template<typename T>
void DeleteObject(unordered_map<int, T>& items)
{
	int id = SelectId(items);
	if (id != 0)
	{
		items.erase(id);
		cout << "Удалено" << endl;
	}
}

vector<int> FindPipes(const unordered_map<int, Pipe>& pipes)
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

vector<int> FindKCs(const unordered_map<int, KC>& stations)
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

bool Contains(const vector<int>& v, int x)
{
	for (int a : v)
		if (a == x)
			return true;
	return false;
}

void Network::AddPipe()
{
	Pipe p;
	cin >> p;
	pipes.emplace(p.GetId(), p);
	cout << "Труба добавлена, ID " << p.GetId() << endl;
}

void Network::AddKC()
{
	KC k;
	cin >> k;
	stations.emplace(k.GetId(), k);
	cout << "КС добавлена, ID " << k.GetId() << endl;
}

void Network::ShowAll() const
{
	if (pipes.empty())
		cout << "Труб нет" << endl;
	for (int id : SortedIds(pipes))
		cout << pipes.at(id) << endl;
	if (stations.empty())
		cout << "КС нет" << endl;
	for (int id : SortedIds(stations))
		cout << stations.at(id) << endl;
}

void Network::EditPipe()
{
	int id = SelectId(pipes);
	if (id == 0)
		return;
	Pipe& p = pipes.at(id);
	p.SwitchRepair();
	cout << "Статус: " << (p.IsInRepair() ? "в ремонте" : "в работе") << endl;
}

void Network::EditKC()
{
	int id = SelectId(stations);
	if (id == 0)
		return;
	KC& k = stations.at(id);
	cout << "1.Запуск цеха  2.Остановка цеха: ";
	bool ok = GetCorrectNumber(1, 2) == 1 ? k.StartFactory() : k.StopFactory();
	if (!ok)
		cout << "Действие невозможно" << endl;
	cout << "Цехов в работе: " << k.GetWorking() << endl;
}

void Network::DeletePipe()
{
	DeleteObject(pipes);
}

void Network::DeleteKC()
{
	DeleteObject(stations);
}

void Network::SearchPipes() const
{
	PrintByIds(pipes, FindPipes(pipes));
}

void Network::SearchKCs() const
{
	PrintByIds(stations, FindKCs(stations));
}

void Network::BatchEditPipes()
{
	vector<int> ids = FindPipes(pipes);
	PrintByIds(pipes, ids);
	if (ids.empty())
		return;

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
		if (action == 3)
			pipes.erase(id);
		else
			pipes.at(id).SetRepair(action == 1);
	}
	cout << "Обработано труб: " << ids.size() << endl;
}

void Network::Save() const
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
	for (int id : SortedIds(pipes))
		pipes.at(id).Save(fout);
	for (int id : SortedIds(stations))
		stations.at(id).Save(fout);
	cout << "Сохранено" << endl;
}

void Network::Load()
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

	int oldPipeId = Pipe::GetMaxID(), oldKCId = KC::GetMaxID();
	Pipe::SetMaxID(0);
	KC::SetMaxID(0);
	unordered_map<int, Pipe> newPipes;
	unordered_map<int, KC> newStations;
	int pipeCount = 0, kcCount = 0;
	bool ok = !(fin >> pipeCount >> kcCount).fail() && pipeCount >= 0 && kcCount >= 0;
	for (int i = 0; ok && i < pipeCount; i++)
	{
		Pipe p;
		ok = p.Load(fin);
		newPipes.emplace(p.GetId(), p);
	}
	for (int i = 0; ok && i < kcCount; i++)
	{
		KC k;
		ok = k.Load(fin);
		newStations.emplace(k.GetId(), k);
	}
	if (!ok)
	{
		Pipe::SetMaxID(oldPipeId);
		KC::SetMaxID(oldKCId);
		cout << "Ошибка: неверный формат файла" << endl;
		return;
	}
	pipes = newPipes;
	stations = newStations;
	cout << "Загружено" << endl;
}
