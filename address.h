#include <iostream>
#include <string>
#include <regex>

using namespace std;


class Adress
{
private:     //приватные поля класса
    string address[6];
    string name;

public:
//конструктор класса
  Adress() : address{"region", "city", "-", "street", "house", "flat"}, name("Иванов Иван Иванович"), region("([^]\\D*) (г.|город)"), street("(Ул|ул[^]\\S*) ([^]\\S*)"), city("(Город|г.) ([^]\\S*)"), district("([^]\\S*) (р-н|район)"), house("(дом|д.) ([^]\\d*)"), flat("(кв.|квартира) ([^]\\d*)") 
{};
    regex region;
    regex city;
    regex district;
    regex street;
    regex house;
    regex flat;

//методы для поиска и записи элементов адреса
    void region_search(string const &s, regex const &r);
    void city_search(string const &s, regex const &r);
    void district_search(string const &s, regex const &r);
    void street_search(string const &s, regex const &r);
    void house_search(string const &s, regex const &r);
    void flat_search(string const &s, regex const &r);

//методы выводов на экран
    void print(){cout << name;};
    void print_rules() const;
    void showaddress();
    void writename(string const &name_){name = name_;}

    string &operator[](int j) //перегрузка []     
    {
        return address[j];
    }

    Adress& operator = ( Adress &adr2 ) //перегрузка оператора присваивания
    {
        for (int i = 0; i < 6; i++)
        {
            address[i] = adr2.address[i];
        }
        return *this;
    }

    friend bool operator ==( Adress &adr1, Adress &adr2 );

  operator string();
    
    ~Adress() { }; //деструктор класса
};

bool operator == ( Adress &adr1, Adress &adr2 )
{
//проверяем равны ли данныев в ячейках массивов     
  for (int i = 0; i < 6; i++)
  {
    if(adr1.address[i] != adr2.address[i]) {
      cout << "Значения массивов не равны\n";
      return 0;
    }              
  }  
return 1;
}

void Adress::region_search(string const &s, regex const &r) {
  smatch match;
  if (regex_search(s, match, r))
    address[0]=match[1]; 
}

//функция поиска города по регулярному выражению
void Adress::city_search(string const &s, regex const &r) {
  smatch match;
  if (regex_search(s, match, r))
    address[1]=match[2];
}

void Adress::district_search(string const &s, regex const &r) {
  smatch match;
  if (regex_search(s, match, r))
    address[2]=match[1];
}

//функция поиска улицы по регулярному выражению
void Adress::street_search(string const &s, regex const &r) {
  smatch match;
  if (regex_search(s, match, r))
    address[3]=match[2];
  else
    street = "Некорректно введено название улицы";
}

//функция поиска номера дома по регулярному выражению
void Adress::house_search(string const &s, regex const &r){
  smatch match;
  if (regex_search(s, match, r))
    address[4]=match[2];
  else
    house = "Некорректно введен номер дома";
}

//функция поиска номера квартиры по регулярному выражению
void Adress::flat_search(string const &s, regex const &r){
  smatch match;
  if (regex_search(s, match, r))
    address[5]=match[2];
  else
    flat = "Некорректно введен номер квартиры";
}

void Adress::showaddress() {
  cout << name << endl;
  for(int i=0; i<6; i++)
    cout << address[i] << endl;
}

//метод вывода правил написания почтового адреса
void Adress:: print_rules() const
{
  setlocale(LC_ALL, "Russian");
    cout << "Правила написания адреса:\n" 
      << "\tЕсли в адресе необходимо указать регион, то он приводится перед названием населенного пункта (например: Московская обл. г. Долгопрудный). Запятые НЕ ставить!!! \n\n" 
      << "\tПеред названием населенного пункта необходимо указать сокращенное      название его типа, отделив его пробелом:\n" <<
    "\t\t обл.  область		      пл.  площадь\n" <<
    "\t\t р-н  район               б-р  бульвар\n" <<
    "\t\t г.  город	              линия  линия\n" <<
    "\t\t пос.  поселок	          ш.  шоссе\n" <<
    "\t\t ул.  улица	              д.  дом\n" <<
    "\t\t пр-т  проспект	          корп.  корпус\n" <<
    "\t\t пр.  проезд	          стр.  строение\n" <<
    "\t\t пер.  переулок	          этаж  этаж\n" <<
    "\t\t наб.  набережная	      кв.  квартира\n\n";
}

