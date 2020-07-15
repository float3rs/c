#include <iostream>
#include <iomanip>

using namespace std;

class Game
{
    private:
       float price;

    public:
        string name;
        int age;

       // Constructors
       Game(): age(18), price(0.00), name("-"){ }
       Game(string n): age(18), price(0.00), name(n){ }
       Game(string n, float p): age(18), price(p), name(n){ }
       Game(string n, float p, int a): age(a), price(p), name(n){ }

       void PrintData()
       {
           cout << "GAME DATA // NAME: " << setw(16) << name << " // PRICE: " << setw(16) << setprecision(2) << fixed << price << " // AGE: " << setw(16) << age << "\n";
           return;
       }

       void ChangeAge(int newAge)
       {
           age = newAge;
           return;
       }
};

int main()
{
    Game G1, G2("doom"), G3("wolfenstein", 20.00), G4("quake", 40.00, 16);

    G1.ChangeAge(3);
    G2.ChangeAge(5);
    G3.ChangeAge(8);
    G4.ChangeAge(15);
    
    G1.PrintData();
    G2.PrintData();
    G3.PrintData();
    G4.PrintData();

    return 0;
}