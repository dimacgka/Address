#include <iostream>
#include <fstream>
#include "address.h"
#include <string>


using namespace std;

const string path = "database.txt";


void addaddress()
{
    ofstream fout;
  
    fout.open(path, ofstream::app);

    cout << "Файл открыт" << endl;
    string inputs;
    Adress first;

    cout << "Введите адрес" << endl;
    getline(cin, inputs);
    first.region_search(inputs, first.region);
    first.city_search(inputs, first.city);
    first.district_search(inputs, first.district);
    first.street_search(inputs, first.street);
    first.house_search(inputs, first.house);
    first.flat_search(inputs, first.flat); 

    cout << "Введите ФИО проживающего" << endl;
    string n;
    cin >> n;
    first.writename(n);

    fout.write((char*)&first, sizeof(Adress));
    fout.close();

}


void reading()
{
  ifstream fin;
  fin.open(path);

 if (!fin.is_open())
  {
    cout << "NBVjhkjh" << endl;
  }
  else 
  {
    Adress pnt;
    while(fin.read((char*)&pnt, sizeof(Adress)))
    {
     pnt.print();
    }
  }
 
  fin.close();
}

