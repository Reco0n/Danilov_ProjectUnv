#include <iostream>
using namespace std;

class Pipe{
private:
    string KmMark;
    double length;
    int diametr;
    bool isRepair;

public:
    Pipe() : KmMark(""), length(0), diametr(0), isRepair(false){} //Настройки по умолцанию
    
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