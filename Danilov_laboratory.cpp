#include <iostream>
#include <fstream>
#include <limits>
using namespace std;


void clearInput(){
    cin.clear();
    cin.ignore(100000, '\n');
}

struct Pipe{
    string Name ="";
    double length = 0;
    int diametr = 0;
    bool isRepair = false;
};
const string FILE_NAME = "pipeline_data.txt";

void inputPipe(Pipe& pipe){
    cout<<"\nНазвание: ";
    getline(cin >> ws, pipe.Name);

    cout<<"Длина(км): ";
    while (!(cin>> pipe.length)||pipe.length <= 0){
            cout<<"Длина должна быть положительна.Повторите: ";
            clearInput();
        }

    cout<<"Диаметр(мм): ";
    while (!(cin >> pipe.diametr)||pipe.diametr <= 0){
        cout<<"Диаметр должен быть положительным. Повторите: ";
        clearInput();
    }
        
    pipe.isRepair = false;
}

void displayPipe(Pipe& pipe){
    cout<<"---Труба---\n";
    cout<<"Назване: "<<pipe.Name<<"\n";
    cout<<"Длина: "<<pipe.length<<"\n";
    cout<<"Диаметр: "<<pipe.diametr<<"\n";
    cout<<"Статус: "<<(pipe.isRepair ?"в ремонте":"в работе")<<"\n";
}

void isWorking(Pipe& pipe){
    pipe.isRepair = !pipe.isRepair;
    cout<<"Статус трубы: "<<(pipe.isRepair ? "в ремонте":"в работе");
}

struct KC{
    string Name = "";
    int amountFactories = 0;
    int workingFactories = 0;
    int levelFactory = 0;
};
    
void inputKC(KC& kc){
    cout<<"\nНазвание КС: ";
    getline(cin >> ws, kc.Name);

    cout<<"Кол-во цехов: ";

    while (!(cin>>kc.amountFactories)||kc.amountFactories <= 0){
        cout<<"Кол-во должно быть положительным. Повторите: ";
        clearInput();
    }

    cout<<"Кол-во цехов в работе: ";
    while (!(cin>>kc.workingFactories) || kc.workingFactories < 0 || kc.workingFactories > kc.amountFactories){
        cout<<"Значение должно быть от 0 до "<<kc.amountFactories<<". Повторите: ";
        clearInput();
    }
    
    
    cout<<"Класс станции: ";
    while (!(cin>>kc.levelFactory)|| kc.levelFactory <= 0){
        cout<<"Класс станции должен быть положительным. Повторите: ";
        clearInput();
    }
}

void displayKC(KC& kc){
    cout<<"---KC--\n";
    cout<<"Название: "<<kc.Name<<"\n";
    cout<<"Всего цехов: "<<kc.amountFactories<<"\n";
    cout<<"Цехов в работе: "<<kc.workingFactories<<"\n";
    cout<<"Класс станции: "<<kc.levelFactory<<"\n";
}

void StartFactory(KC& kc){
    if(kc.workingFactories < kc.amountFactories){
        kc.workingFactories++;
        cout<<"Цех запущен. В работе: "<<kc.workingFactories<<"\n";
    }
    else{
        cout<<"Все цехи уже в работе\n";
    }
}
void StopFactory(KC& kc){
    if(kc.workingFactories > 0){
        kc.workingFactories --;
        cout<<"Цех остановлен. В работе: "<<kc.workingFactories<<"\n";
    }
    else{
        cout<<"Все цехи уже остановлены.\n";
    }
}

bool saveAll(const Pipe& pipe, bool pipeExists,
             const KC& kc, bool kcExists,
             const string& filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Ошибка открытия файла для записи.\n";
        return false;
    }

    if (pipeExists) {
        out << "PIPE\n"
            << pipe.Name << '\n'
            << pipe.length << '\n'
            << pipe.diametr << '\n'
            << pipe.isRepair << '\n';
    }

    if (kcExists) {
        out << "KC\n"
            << kc.Name << '\n'
            << kc.amountFactories << '\n'
            << kc.workingFactories << '\n'
            << kc.levelFactory << '\n';
    }

    cout << "Данные сохранены в " << filename << "\n";
    return true;
}

bool loadAll(Pipe& pipe, bool& pipeExists,
             KC& kc, bool& kcExists,
             const string& filename) {
    ifstream in(filename);
    if (!in) {
        cout << "Файл не найден.\n";
        return false;
    }

    string tag;
    while (in >> tag) {
        if (tag == "PIPE") {
            Pipe tempPipe;
            in >> ws;
            getline(in, tempPipe.Name);
            in >> tempPipe.length >> tempPipe.diametr >> tempPipe.isRepair;

            
            if (tempPipe.length <= 0 || tempPipe.diametr <= 0) {
                cout << "Ошибка: в файле некорректные данные трубы (длина или диаметр <= 0).\n";
                return false;
            }
            pipe = tempPipe;
            pipeExists = true;
        }
        else if (tag == "KC") {
            KC tempKC;
            in >> ws;
            getline(in, tempKC.Name);
            in >> tempKC.amountFactories >> tempKC.workingFactories >> tempKC.levelFactory;


            if (tempKC.amountFactories <= 0 || tempKC.levelFactory <= 0 ||tempKC.workingFactories < 0 ||tempKC.workingFactories > tempKC.amountFactories) {
                cout << "Ошибка: в файле некорректные данные КС.\n";
                return false;
            }
            kc = tempKC;
            kcExists = true;
        }
        else {
            cout << "Предупреждение: неизвестный тег в файле: " << tag << "\n";
            string dummy;
            getline(in, dummy);
        }
    }

    cout << "Данные загружены.\n";
    return true;
}
void displayManu(){
    cout<<"\n1.Труба\n";
    cout<<"2.КС\n";
    cout<<"3.Просмотр\n";
    cout<<"4.Редакт. трубы\n";
    cout<<"5.Редакт. КС\n";
    cout<<"6.Сохранить\n";
    cout<<"7.Загрузить\n";
    cout<<"0.Выход\n\n";
    cout<<"Выберетие действие: \n";
}

int main(){
    Pipe pipe;
    KC kc;
    bool pipeExists = false;
    bool kcExists = false;
    int choice;
    
    while(true){
        displayManu();
        if (!(cin>>choice)){
            cout<<"Некорректный ввод.\n";
            clearInput();
            continue;
        }

        switch (choice){
            case 0:{
                cout<<"Выход.\n";
                return 0;
            }

            case 1:{
                if (pipeExists){
                    cout<<"Труба уже есть. Перезаписать? (y/n): ";
                    char ans;
                    cin>>ans;
                    if (ans !='y'){
                        break;
                    }
                }
                inputPipe(pipe);
                pipeExists = true;
                cout<<"Труба добавлена.\n\n";
                break;
            }

            case 2:{
                if (kcExists){
                    cout<<"(y/n): ";
                    char ans;
                    cin>>ans;
                    if (ans !='y'){
                        break;
                    }
                }
                inputKC(kc);
                kcExists = true;
                cout<<"КС добавлена.\n\n";
                break;
            }

            case 3:{
                if(pipeExists) displayPipe(pipe);
                else cout<<"Трубы нет.\n";

                if (kcExists) displayKC(kc);
                else cout<<"КС нет.\n";
                break;
            }

            case 4:{
                if (!pipeExists){
                    cout<<"Сначала создайте трубу\n";
                    break;
                }
                isWorking(pipe);
                break;
            }
            case 5:{
                if (!kcExists){
                    cout<<"Сначала создайте КС.\n";
                    break;
                }
                cout<<"1.Запук цеха\n";
                cout<<"2.Остановка цеха\n";
                cout<<"Выбор: ";
                int subChoice;
                cin>>subChoice;

                switch (subChoice){
                    case 1: StartFactory(kc);
                    break;
                    case 2: StopFactory(kc);
                    break;
                    default:cout<<"Нет такого пункта.\n";
                    break; 
                }
                break;
            }
            case 6:{
                saveAll(pipe, pipeExists, kc, kcExists, FILE_NAME);
                break;
            }
 
            case 7:{
                loadAll(pipe, pipeExists, kc, kcExists, FILE_NAME);
                break;
            }
 
            default:{
                cout<<"Нет такого пункта.\n";
                break;
            }
        }
    }
}