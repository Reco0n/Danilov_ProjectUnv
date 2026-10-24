#include <iostream>
#include <fstream>
#include <ctime>
#include "Network.h"
#include "Utils.h"

using namespace std;

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
	redirect_output_wrapper cerr_out(cerr);
	char buf[64];
	time_t t = time(nullptr);
	strftime(buf, sizeof(buf), "%d_%m_%Y_%H_%M_%S", localtime(&t));
	ofstream logfile(string("log_") + buf + ".txt");
	if (logfile)
		cerr_out.redirect(logfile);

	Network network;

	while (true)
	{
		PrintMenu();
		int choice = GetCorrectNumber(0, 12);
		cerr << "Пункт меню " << choice << endl;

		switch (choice)
		{
		case 1:
			network.AddPipe();
			break;
		case 2:
			network.AddKC();
			break;
		case 3:
			network.ShowAll();
			break;
		case 4:
			network.EditPipe();
			break;
		case 5:
			network.EditKC();
			break;
		case 6:
			network.DeletePipe();
			break;
		case 7:
			network.DeleteKC();
			break;
		case 8:
			network.SearchPipes();
			break;
		case 9:
			network.SearchKCs();
			break;
		case 10:
			network.BatchEditPipes();
			break;
		case 11:
			network.Save();
			break;
		case 12:
			network.Load();
			break;
		case 0:
			return 0;
		}
	}
}
