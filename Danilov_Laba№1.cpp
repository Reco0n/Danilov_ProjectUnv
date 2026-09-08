#include <iostream>
using namespace std;

class Pipe{
private:
    string KmMark;
    double length;
    int diametr;
    bool isRepair;

public:
    Pipe() : KmMark(""), length(0), diametr(0), isRepair(false){} 
    
    void inputCons(){
        cout<<"";
        cin>>KmMark;

        cout<<"";
        cin>>length;
        if (length <= 0){
            cout<<"";
            cin>>length;
        }

        cout<<"";
        cin>>diametr;
        if (diametr <= 0){
            cout<<"";
            cin>>diametr;
        }
        
        isRepair = false;
    }

    void display(){
        cout<<"";
        cout<<""<<KmMark;
        cout<<""<<length;
        cout<<""<<diametr;
        cout<<""<<(isRepair ?"":"");
    }

    void isWorking(){
        isRepair = !isRepair;
        cout<<""<<(isRepair ? "":"");
    }



};

class KC{
private:

    string Name;
    int amountFactories;
    int workingFactories;
    int levelFactory;

public:

    KC(): Name(""), amountFactories(0), workingFactories(0), levelFactory(0){}

    void inputCons(){
        cout<<"";
        cin>>Name;
    
        cout<<"";
        cin>>amountFactories;
        if (amountFactories <= 0){
            cout<<"";
            cin>>amountFactories;
        }

        cout<<"";
        cin>>workingFactories;
        if (workingFactories <= 0){
            cout<<"";
            cin>>workingFactories;
        }
        else if(workingFactories > amountFactories){
            cout<<"";
            cin>>workingFactories;
        }
        

        cout<<"";
        cin>>levelFactory;
        if (levelFactory <= 0){
            cout<<"";
            cin>>levelFactory;
        }
    }
    void display(){
        cout<<""<<Name;
        cout<<""<<amountFactories;
        cout<<""<<workingFactories;
        cout<<""<<levelFactory;
    }

    void StartFactory(){
        if(workingFactories < amountFactories){
            workingFactories++;
            cout<<""<<workingFactories;
        }
        else{
            cout<<"";
        }
    }

    void StopFactory(){
        if(workingFactories > 0){
            workingFactories --;
            cout<<""<<workingFactories;
        }
        else{
            cout<<"";
        }
    }
    
};

void displayManu(){
    cout<<"1.Труба";
    cout<<"2.КС";
    cout<<"3.Просмотр";
    cout<<"4.Редакт. трубы";
    cout<<"5.Редакт. КС";
    cout<<"0.Выход";
    cout<<"Выберетие действие: ";
}

int main(){
    Pipe pipe;
    KC kc;
    bool pipeExists = false;
    bool kcExists = false;
    int choice;
    
    while(true){
        displayManu();
        cin>>choice;

        switch (choice){
            case 0:{
                cout<<"0";
                return 0;
            }

            case 1:{
                if (pipeExists){
                    cout<<"(y/n): ";
                    char ans;
                    cin>>ans;
                    if (ans !='y'){
                        break;
                    }
                }
                pipe.inputCons();
                pipeExists = true;
                cout<<"";
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
                kc.inputCons();
                kcExists = true;
                cout<<"";
                break;
            }

            case 3:{
                if(pipeExists){
                    pipe.display();
                }
                else{
                    cout<<"";
                }

                if (kcExists){
                    kc.display();
                }
                else{
                    cout<<"";
                }
                break;
            }

            case 4:{
                if (!pipeExists){
                    cout<<"";
                    break;
                }
                pipe.isWorking();
                break;
            }
            case 5:{
                if (!kcExists){
                    cout<<"";
                    break;
                }
                cout<<"1.";
                cout<<"2.";
                cout<<"выбор: ";
                int subChoice;
                cin>>subChoice;

                switch (subChoice){
                    case 1: kc.StartFactory();
                    break;
                    case 2:kc.StopFactory();
                    break;
                    default:cout<<"";
                    break; 
                }
                break;
            }
        }

    }
}