#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <map>
using namespace std;

///// Нахождение необходимого символа в строке. Необходимо для выделения атрибутов из объекта.
///// Не считает элементы в кавычках или скобках. В случае отсутствия элемента возвращает последний элемент строки
int char_pos(string line, char char_needed, int order)
{
    if (order == 0) {
        return 0;
    }
    int char_counter = 0;
    int quotes_count = 0;
    int brackets_count = 0;
    int i = 0;
    while (line[i] != '\0')
    {
        if (((quotes_count % 2) == 0) && ((brackets_count % 2) == 0)) {
            if (line[i] == char_needed)
            {
                char_counter++;
            }
            if (char_counter == order)
            {
                return i;
            }
        }
        if (line[i] == '\"')
        {
            quotes_count++;
        }
        if ((line[i] == '(') || (line[i] == ')'))
        {
            brackets_count++;
        }
        i++;
    }
    return line.length() - 1;
}

string clean_from_date_address(string line) {
    if (line.find("T") != -1) {
        string line1 = line.substr(8, 2);
        string line2 = line.substr(5, 2);
        int linee1 = atoi(line1.c_str());
        int linee2 = atoi(line2.c_str());
        line = to_string(linee1) + "/" + to_string(linee2);
    }

    return line;
}

string clean_from_date_float(string line) {
    if (line.find("T") != -1) {
        string line1 = line.substr(8, 2);
        string line2 = line.substr(5, 2);
        int linee1 = atoi(line1.c_str());
        int linee2 = atoi(line2.c_str());
        line = to_string(linee1) + "." + to_string(linee2);
    }

    return line;

}

///// Очистка строки от лишних кавычек (все, кроме первой и последней экранируются. Необходимо для формата TTL).
string clean_quotes(string line) {
    int quotes_count_now = 0;
    int quotes_count = 0;
    int line_length = line.length();
    for (int i = 0; i < line_length; i++) {
        if (line[i] == '\"') {
            quotes_count++;
        }
    }
    for (int i = 0; i < line_length; i++) {
        if (line[i] == '\"') {
            quotes_count_now++;
            if (quotes_count_now > 1 && quotes_count_now < quotes_count) {
                line = line.substr(0, i) + '\\' + line.substr(i, line_length - i);
                line_length++;
                i++;
            }
        }
    }
    return line;
}

////////// Очистка строки от кавычек (кавычки удаляются полностью)
string clean_quotes_full(string line) {

    int line_length = line.length();
    for (int i = 0; i < line_length; i++) {
        if (line[i] == '\"') {
            line = line.substr(0, i) + line.substr(i + 1, line_length - i - 1);
            line_length--;
            i--;

        }
    }
    return line;
}

string clean_spaces_full(string line) {

    int line_length = line.length();
    for (int i = 0; i < line_length; i++) {
        if (line[i] == ' ') {
            line = line.substr(0, i) + line.substr(i + 1, line_length - i - 1);
            line_length--;
            i--;

        }
    }
    return line;
}

/////////// Очищает строку от первого слова (в нашем случае используется для очистки от id)
string clean_from_id(string line) {
    int line_length = line.length();
    int x = char_pos(line, ' ', 1);
    line = line.substr(x + 1, line_length - x - 1);
    return line;
}

/////Получение атрибута из объекта.
string atribut(int atr_num, string line)
{
    int x = (char_pos(line, ',', atr_num - 1));
    int y = char_pos(line, ',', atr_num);
    if (y == line.length() - 1) {
        y++;
    }
    if (x == 0) {
        x--;
    }
    line = line.substr((x + 1), (y - x - 1));
    if (line.length() == 0) {
        return "null";
    }
    else {
        return line;
    }
}

string atribut_mr(int atr_num, string line)
{
    int x = (char_pos(line, ';', atr_num - 1));
    int y = char_pos(line, ';', atr_num);
    if (y == line.length() - 1) {
        y++;
    }
    if (x == 0) {
        x--;
    }
    line = line.substr((x + 1), (y - x - 1));
    if (line.length() == 0) {
        return "null";
    }
    else {
        return line;
    }
}
/// Получение атрибута управляющей компании
string atribut_uk(int atr_num, string line)
{
    int x = (char_pos(line, '%', atr_num - 1));
    int y = char_pos(line, '%', atr_num);
    if (y == line.length() - 1) {
        y++;
    }
    if (x == 0) {
        x--;
    }
    line = line.substr((x + 1), (y - x - 1));
    if (line.length() == 0) {
        return "null";
    }
    else {
        return line;
    }
}
/// Подсчёт определённых символов в строке 
int counter(char c, string line) {
    int counter_c = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == c) {
            counter_c++;
        }
    }
    return counter_c;
}
///// Переводит число с точкой, в целое
string float_to_int(string line) {
    line = line.substr(0, char_pos(line, '.', 1));
    return line;
}
///// Приведение логической строки к надлежащему виду
string booleanAtribut(string atre)
{
    atre = atre.substr(0, 1);
    if (atre == "1")
    {
        return "\"true\"";
    }
    else
    {
        return "\"false\"";
    }
}

///// Проверка того, является ли строка числом
boolean check_number(string line) {
    int length = line.length();
    for (int i = 0; i < length; i++) {
        if ((line[i] != '1') && (line[i] != '2') && (line[i] != '3') && (line[i] != '4') && (line[i] != '5') && (line[i] != '6') && (line[i] != '7') && (line[i] != '8') && (line[i] != '9') && (line[i] != '0') && (line[i] != '.') && (line[i] != ' '))
            return 0;
    }
    return 1;
}

string street_name(string line) {
    int q;
    for (int i = line.length() - 1; i > -1; i--) {
        if ((line[i] != '1') && (line[i] != '2') && (line[i] != '3') && (line[i] != '4') && (line[i] != '5') && (line[i] != '6') && (line[i] != '7') && (line[i] != '8') && (line[i] != '9') && (line[i] != '0')) {
            q = i;
            break;
        }
    }
    line = line.substr(0, (q + 1));
    return line;
}

///////// ОСНОВНОЕ ТЕЛО ФУНКЦИИ
int main()
{
    ///////// Служебная часть, открытие файлов, установление кодировки, пропуск первой строки...
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    ///////// Переменные для составления строк

    map <string, int> street_map;
    map <string, string> uk_map;
    map <string, int> work_type_map;

    string str_b = "cg:";
    string str_2_e = " a owl:NamedIndividual,";
    string tabulation = "\t\t\t\t\t";
    string str_e_1 = " ;";
    string str_e_2 = " .";
    string str_bool = "^^xsd:boolean";
    string object_class = "CapitalConstruction";
    string object_class_2 = "MultyAptHouse";
    string object_class_3 = "MajorRenovation";
    string object_class_4 = "Address";
    string object_name = "CC_";
    string object_name_2 = "MAH_";
    string object_name_3 = "MR_";
    string object_name_4 = "Addr_number_";

    ///////// Функциональные переменные
    string object_container = "object_container";               /////// Объект который мы берём из CSV
    string uk_container;
    string street_container;
    string work_type_container;
    string atribut_container;                                   /////// Строчка в которую мы будем записывать значение атрибута 
    string atribut_container_2;


    int object_amount = 0;
    int street_amount = 0;
    int uk_amount = 0;
    int work_type_amount = 0;
    int MR_amount = 1;

    ifstream object_data("data.csv");      /////// Объекты считывания, нужно предварительно создать и заполнить.

    ofstream buildings;
    ofstream living_objects;
    ofstream major_renovation;
    ofstream addresses;
    ofstream streets;
    buildings.open("database_buildings.txt");    ///////// Объекты записи, создаются автоматически.
    major_renovation.open("database_major_renovation.txt");
    living_objects.open("database_living_objects.txt");
    addresses.open("database_addresses.txt");
    streets.open("database_streets.txt");



    getline(object_data, object_container); ///////// Пропуск первой служебной строки в файле CSV
    
    ifstream street_all("street_data.txt");
    getline(street_all, street_container);
    while (street_container != "") 
    {
        street_amount++;
        streets << "###  http://citygraph.onti.actcognitive.org/core#" << "Street_" << (street_amount) << endl;
        streets << str_b << "Street_" << (street_amount) << str_2_e << endl;
        streets << tabulation << tabulation << str_b << "Street" << str_e_1 << endl;
        streets << tabulation << str_b << "hasTitle \"" << street_name(street_container) << "\"" << str_e_2 << endl << endl << endl;
        street_map[street_name(street_container)] = street_amount;
        getline(street_all, street_container);
    }
    cout << "Street amount: " << street_amount;
    street_all.close();


    /*while (object_container != "")
    {
        getline(object_data, object_container);
        object_amount++;
    }
    cout << object_amount;
    object_data.close();
    ifstream object_data("data.csv");*/

    ifstream uk_data("uk_data.txt");
    getline(uk_data, uk_container);
    while (uk_container != "")
    {
        uk_amount++;
        int x = char_pos(uk_container, ' ', 1);
        string uk_id = uk_container.substr(0, x);
        uk_container = clean_from_id(uk_container);
        uk_container = clean_quotes_full(uk_container);
        uk_container = clean_spaces_full(uk_container);
        
        uk_map[uk_container] = uk_id;
        getline(uk_data, uk_container);
    }
    cout << "UK_amount: " << uk_amount;
    uk_data.close();

    ifstream work_type_data("work_type_data.txt");
    getline(work_type_data, work_type_container);
    while (work_type_container != "")
    {
        
        work_type_container = work_type_container.substr(0, char_pos(work_type_container, '\t', 1));
        work_type_map[work_type_container] = work_type_amount;
        getline(work_type_data, work_type_container);
        work_type_amount++;
    }
    cout << "Work type amount: " << work_type_amount;
    work_type_data.close();


    getline(object_data, object_container);
    ///////// Основная часть создания объекта
    while (object_container != "") {
        object_amount++;
        if (object_amount % 100 == 0)
        {
            cout << object_amount;
        }
        ///////////// Создаём Физический объект
        buildings << "###  http://citygraph.onti.actcognitive.org/core#" << object_name << (object_amount) << endl;
        buildings << str_b << object_name << (object_amount) << str_2_e << endl;
        buildings << tabulation << tabulation << str_b << object_class << str_e_1 << endl;
        buildings << tabulation << str_b << "hasFunction " << str_b << object_name_2 << (object_amount);
        /////////// Указываем адрес
        buildings << str_e_1 << endl << tabulation << str_b << "hasAddressObj " << str_b << object_name_4 << (object_amount) ;
        addresses << "###  http://citygraph.onti.actcognitive.org/core#" << object_name_4 << (object_amount) << endl;
        addresses << str_b << object_name_4 << (object_amount) << str_2_e << endl;
        addresses << tabulation << tabulation << str_b << object_class_4;
        addresses << str_e_1 << endl << tabulation << str_b << "hasStreet " << str_b << "Street_" << street_map[clean_quotes_full(atribut(6, object_container))];

        if (atribut(7, object_container) != "null") {
            addresses << str_e_1 << endl << tabulation << str_b << "hasHouseNumber \"" << clean_from_date_address(atribut(7, object_container)) << "\"";
        }
        if (atribut(8, object_container) != "null") {
            addresses << str_e_1 << endl << tabulation << str_b << "hasKorpus \"" << clean_quotes_full(atribut(8, object_container)) << "\"";
        }
        if (atribut(9, object_container) != "null") {
            addresses << str_e_1 << endl << tabulation << str_b << "hasLitera \"" << clean_quotes_full(atribut(9, object_container)) << "\"";
        }
        addresses << str_e_2 << endl << endl << endl;
        /////////// Указываем Управляющую компанию
        string uk_containers = clean_spaces_full(clean_quotes_full(atribut(44, object_container)));
        if (uk_containers != "null") {

            atribut_container = "null";
            string uk_containers_temp;
            for (int m = 0; m < (counter('%', uk_containers) + 1); m++) 
            {
                uk_containers_temp = atribut_uk(m + 1, uk_containers);
                atribut_container = uk_map[uk_containers_temp];
            }
            if (atribut_container != "") 
            {
            buildings << str_e_1 << endl << tabulation << str_b << "hasManagingOrganization " << str_b << atribut_container;
            }
        }
        //////////////// Указываем капитальные ремонты
        atribut_container = clean_quotes_full(atribut(46, object_container));
        atribut_container_2 = clean_quotes_full(atribut(48, object_container));
        int MR_obj_amount = atoi(atribut(47, object_container).c_str());
        for (int j = 0; j < MR_obj_amount; j++) 
        {
            string wt_temp;
            string major_data = atribut(j + 1, atribut_container);
            string major_type = atribut_mr(j + 1, atribut_container_2);
            if (j > 0) {
                major_type = major_type.substr(1, major_type.length() - 1);
            }
            if (work_type_map[major_type] > 0 && check_number(major_data) == 1) 
            {
                    major_renovation << "###  http://citygraph.onti.actcognitive.org/core#" << object_name_3 << MR_amount << endl;
                    major_renovation << str_b << object_name_3 << MR_amount << str_2_e << endl;
                    major_renovation << tabulation << tabulation << str_b << object_class_3 << str_e_1 << endl;
                    major_renovation << tabulation << str_b << "hasWorkType " << str_b << "WT_" << work_type_map[major_type] << str_e_1 << endl;
                    major_renovation << tabulation << str_b << "hasMajorRenovationDate " << major_data << str_e_2 << endl << endl << endl;

                    buildings << str_e_1 << endl << tabulation << str_b << "hasMajorRenovation " << str_b << "MR_" << MR_amount;
                    MR_amount++;
            }
        }

        ///////////////// Указываем остальные атрибуты
        ///atribut_container = atribut(4, object_container);
        ///atribut_container = clean_quotes_full(atribut_container);
        ///if (atribut_container != "null") {
        ///    buildings << str_e_1 << endl << tabulation << str_b << "hasAddress " << "\"" << atribut_container << "\"";
        ///}

        atribut_container = atribut(15, object_container);
        atribut_container = clean_quotes_full(atribut_container);
        if (atribut_container != "null") {
            buildings << str_e_1 << endl << tabulation << str_b << "hasStringSeries " << "\"" << atribut_container << "\"";
        }
        atribut_container = atribut(16, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasYearConstruct " << atribut_container;
        }

        atribut_container = atribut(17, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasYearRepair " << atribut_container;
        }

        atribut_container = atribut(18, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasAreaGeneral " << atribut_container;
        }

        atribut_container = atribut(21, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasStairsAmount " << float_to_int(atribut_container);
        }

        atribut_container = atribut(22, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasFloors " << float_to_int(atribut_container);
        }

        atribut_container = atribut(45, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasFailureStatus " << booleanAtribut(atribut_container) << str_bool;
        }

        atribut_container = atribut(53, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasLiftAmount " << float_to_int(atribut_container);
        }

        atribut_container = atribut(54, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            buildings << str_e_1 << endl << tabulation << str_b << "hasDomofonAmount " << float_to_int(atribut_container);
        }

        buildings << str_e_2 << endl << endl << endl;

        ////////////////////////////////////////// Создаём функциональный объект и указываем для него атрибуты
        living_objects << "###  http://citygraph.onti.actcognitive.org/core#" << object_name_2 << (object_amount) << endl;
        living_objects << str_b << object_name_2 << (object_amount) << str_2_e << endl;
        living_objects << tabulation << tabulation << str_b << object_class_2;
        atribut_container = atribut(19, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasInhabitableArea " << atribut_container;
        }
        atribut_container = atribut(20, object_container);
        if (atribut_container != "null") {
            living_objects << str_e_1 << endl << tabulation << str_b << "hasUninhabitableArea " << clean_from_date_float((atribut_container.c_str()));
        }
        atribut_container = atribut(23, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            living_objects << str_e_1 << endl << tabulation << str_b << "hasResidentNumber " << float_to_int(atribut_container);
        }
        atribut_container = atribut(25, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            living_objects << str_e_1 << endl << tabulation << str_b << "hasCentralHeating " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(26, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            living_objects << str_e_1 << endl << tabulation << str_b << "hasAutoBoilerRoom " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(27, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {
            living_objects << str_e_1 << endl << tabulation << str_b << "hasStoveHeating " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(28, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasCentralHotWater " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(29, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasCentralHotWaterGas " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(30, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "CentralHotWaterWoods " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(31, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasCentralElectricity " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(32, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasCentralGas " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(33, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasNotCentralGas " << booleanAtribut(atribut_container) << str_bool;
        }
        atribut_container = atribut(51, object_container);
        if (atribut_container != "null" && check_number(atribut_container) == 1) {

            living_objects << str_e_1 << endl << tabulation << str_b << "hasGarbageAmount " << float_to_int(atribut_container);
        }
        atribut_container = clean_quotes_full(atribut(11, object_container));
        atribut_container_2 = clean_quotes_full(atribut(12, object_container));
        if (atribut_container != "null") {

            int room_amount = 0;
            int set = 1;
            for (int j = 2; j < 8; j++) {
                if (char_pos(atribut_container, j + '0', 1) != atribut_container.length() - 1) {
                    room_amount = room_amount + atoi(atribut(set, atribut_container_2).c_str());
                    living_objects << str_e_1 << endl << tabulation << str_b << "hasRoomsCommunal_" << j << " " << atribut(set, atribut_container_2);
                    set++;
                }
            }
            living_objects << str_e_1 << endl << tabulation << str_b << "hasCommunalApartmentsAmount " << room_amount;
        }
        atribut_container = clean_quotes_full(atribut(35, object_container));
        atribut_container_2 = clean_quotes_full(atribut(36, object_container));
        if (atribut_container != "null") {
            int room_amount = 0;
            int set = 1;
            for (int j = 1; j < 8; j++) {
                if (char_pos(atribut_container, j + '0', 1) != atribut_container.length() - 1) {
                    room_amount = room_amount + atoi(atribut(set, atribut_container_2).c_str());
                    living_objects << str_e_1 << endl << tabulation << str_b << "hasRooms_" << j << " " << atribut(set, atribut_container_2);
                    set++;
                }
            }
            living_objects << str_e_1 << endl << tabulation << str_b << "hasApartmentsAmount " << room_amount;
        }
        living_objects << str_e_2 << endl << endl << endl;
        getline(object_data, object_container);


    }


    /////////Конец создания Объекта

    //////////Служебная часть, закрытие файла и конец кода
    addresses.close();
    buildings.close();
    living_objects.close();
    major_renovation.close();
    streets.close();

    object_data.close();
    cout << "Object_amount: " << object_amount;
    return 0;
}