#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <vector>
#include <stdlib.h>
using namespace std;

ofstream OKATO;
string str_1 = "###  http://www.w3id.org/citygraph-core#";
string str_b = "cg:";
string str_2_e = " rdf:type owl:NamedIndividual,";
string tabulation = "\t\t\t\t\t";
string str_e_1 = " ;";
string str_e_2 = " .";
string object_class = "Region";
string object_name = "Region_";
string OKATO_name = "OKATO_";


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
    return line.length()-1;
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
                line = line.substr(0, i) + line.substr(i+1, line_length - i - 1);
                line_length--;
                i--;
            
        }
    }
    return line;
}

/////Получение атрибута из объекта.
string atribut(int atr_num, string line)
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

string atribut_abr(int atr_num, string line)
{
    int x = (char_pos(line, ';', atr_num - 1));
    int y = char_pos(line, ';', atr_num);
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

string OKATO_create_code(string object) {
    object = clean_quotes_full(atribut(1, object)) + clean_quotes_full(atribut(2, object)) + clean_quotes_full(atribut(3, object)) + clean_quotes_full(atribut(4, object));
    return object;
}

void OKATO_create(string object) {
    OKATO << str_1 << OKATO_name << OKATO_create_code(object) << str_e_1 << endl;
    OKATO << str_b << OKATO_name << OKATO_create_code(object) << str_2_e << endl;
    OKATO << tabulation << tabulation << str_b << "OKATO ;" << endl;
    OKATO << tabulation << str_b << "hasLevel1 \"" << clean_quotes_full(atribut(1,object)) << "\"" << str_e_1 << endl;
    OKATO << tabulation << str_b << "hasLevel2 \"" << clean_quotes_full(atribut(2, object)) << "\"" << str_e_1 << endl;
    OKATO << tabulation << str_b << "hasLevel3 \"" << clean_quotes_full(atribut(3, object)) << "\"" << str_e_1 << endl;
    OKATO << tabulation << str_b << "hasLevel4 \"" << clean_quotes_full(atribut(4, object)) << "\"" << str_e_1 << endl;
    OKATO << tabulation << str_b << "hasStringValue \"" << OKATO_create_code(object) << "\"" << str_e_1 << endl;
    OKATO << tabulation << str_b << "hasInitiationDate \"" << atribut(13, object) << "\" ." << endl << endl << endl;
}



string classification(int l, string object) {
    object = clean_quotes_full(atribut(l, object));
    object = object.substr(0, 1);
    return object;
}

string level_name(int l, string object) {
    object = classification(l, object);
    if (object == "2") {
        return "Region_District";
    }
    if (object == "4") {
        return "Region_City";
    }
    if (object == "3") {
        return "Intracity_District";
    }
    if (object == "5" || object == "6") {
        return "District_City";
    }
    if (object == "8" || object == "9") {
        return "VillageCouncil";
    }
}

///////// ОСНОВНОЕ ТЕЛО ФУНКЦИИ
int main() {
    ///////// Служебная часть, открытие файлов, установление кодировки, пропуск первой строки...
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    ///////// Переменные для составления строк


    ///////// Функциональные переменные
    string object_container;

    string region_check;
    string first_level_check;
    string second_level_check;
    string atribut_container;              /////// Строчка в которую мы будем записывать значение атрибута 


    int object_amount = 82;

    ifstream object_data("data.csv");      /////// Объекты считывания, нужно предварительно создать и заполнить.

    ofstream region;
    ofstream first_level;
    ofstream second_level;
    ofstream third_level;

    region.open("region.txt");
    first_level.open("first_level.txt");
    second_level.open("second_level.txt");
    third_level.open("third_level.txt");
    OKATO.open("OKATO.txt");

    getline(object_data, object_container); ///////// Пропуск первой служебной строки в файле CSV
    getline(object_data, object_container);
    getline(object_data, object_container);
    for (int i = 0; i < 82; i++) {
        cout << i;
        region_check = atribut(1, object_container);
        region << str_1 << object_name << OKATO_create_code(object_container) << endl;
        region << str_b << object_name << OKATO_create_code(object_container) << str_2_e << endl;
        region << tabulation << tabulation << str_b << "Region ;" << endl;
        region << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
        if (atribut(8, object_container) != "null") {
            region << tabulation << str_b << "hasAdministrativeCenter " << clean_quotes(atribut(8, object_container)) << str_e_1 << endl;
        }
        region << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container);
        OKATO_create(object_container);
        getline(object_data, object_container);
        while (atribut(1, object_container) == region_check) {
            if (atribut(1, object_container) == region_check) {
                string pars = atribut(7, object_container);
                int parsi = pars.length();
                if (pars[parsi - 2] != '/') {
                    if (atribut(2, object_container) != "\"000\"") {
                        first_level_check = atribut(2, object_container);
                        first_level << str_1 << level_name(2, object_container) << "_" << OKATO_create_code(object_container) << endl;
                        first_level << str_b << level_name(2, object_container) << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                        first_level << tabulation << tabulation << str_b << level_name(2, object_container) << str_e_1 << endl;
                        first_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                        if (atribut(8, object_container) != "null") {
                            first_level << tabulation << str_b << "hasAdministrativeCenter " << clean_quotes(atribut(8, object_container)) << str_e_1 << endl;
                        }
                        first_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container);
                        first_level << str_e_1 << endl << tabulation << str_b << "includedIn " << str_b << "Region_" << clean_quotes_full(atribut(1, object_container)) << "000000000";
                        if (clean_quotes_full(atribut(6, object_container)) != "") {
                            atribut_container = clean_quotes_full(atribut(6, object_container));
                            for (int j = 0; j < counter(';', atribut_container); j++) {
                                first_level << str_e_1 << endl << tabulation << str_b << "hasAbbr \"" << atribut_abr(j+1, atribut_container) << "\"";
                            }
                        }
                        OKATO_create(object_container);
                        region << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << level_name(2, object_container) << "_" << OKATO_create_code(object_container);
                        getline(object_data, object_container);
                        while (atribut(2, object_container) == first_level_check) {
                            if (atribut(2, object_container) == first_level_check) {

                                string pars_2 = atribut(7, object_container);
                                int parsi_2 = pars_2.length();
                                if (pars_2[parsi_2 - 2] != '/') {
                                    if (atribut(3, object_container) != "\"000\"") {
                                        second_level_check = atribut(3, object_container);
                                        second_level << str_1 << level_name(3, object_container) << "_" << OKATO_create_code(object_container) << endl;
                                        second_level << str_b << level_name(3, object_container) << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                                        second_level << tabulation << tabulation << str_b << level_name(3, object_container) << str_e_1 << endl;
                                        second_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                                        if (clean_quotes_full(atribut(6, object_container)) != "") {
                                            atribut_container = clean_quotes_full(atribut(6, object_container));
                                            for (int j = 0; j < counter(';', atribut_container); j++) {
                                                second_level << tabulation << str_b << "hasAbbr \"" << atribut_abr(j + 1, atribut_container) << "\"" << str_e_1 << endl;
                                            }
                                        }
                                        if (atribut(8, object_container) != "null") {
                                            second_level << tabulation << str_b << "hasAdministrativeCenter " << clean_quotes(atribut(8, object_container)) << str_e_1 << endl;
                                        }
                                        second_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container);
                                        second_level << str_e_1 << endl << tabulation << str_b << "includedIn " << str_b << level_name(2, object_container) << "_" << clean_quotes_full(atribut(1, object_container)) << clean_quotes_full(atribut(2, object_container)) << "000000";
                                        OKATO_create(object_container);
                                        first_level << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << level_name(3, object_container) << "_" << OKATO_create_code(object_container);
                                        getline(object_data, object_container);
                                        while (atribut(3, object_container) == second_level_check) {


                                            if (atribut(3, object_container) == second_level_check) {
                                                if (atribut(4, object_container) != "\"000\"") {
                                                    third_level << str_1 << "District" << "_" << OKATO_create_code(object_container) << endl;
                                                    third_level << str_b << "District" << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                                                    third_level << tabulation << tabulation << str_b << "District" << str_e_1 << endl;
                                                    third_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                                                    if (clean_quotes_full(atribut(6, object_container)) != "") {
                                                        atribut_container = clean_quotes_full(atribut(6, object_container));
                                                        for (int j = 0; j < counter(';', atribut_container); j++) {
                                                            third_level << tabulation << str_b << "hasAbbr \"" << atribut_abr(j + 1, atribut_container) << "\"" << str_e_1 << endl;
                                                        }
                                                    }
                                                    third_level << tabulation << str_b << "includedIn " << str_b << level_name(3, object_container) << "_" << clean_quotes_full(atribut(1, object_container)) << clean_quotes_full(atribut(2, object_container)) << clean_quotes_full(atribut(3, object_container)) << "000" << str_e_1 << endl;
                                                    third_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container) << str_e_2 << endl << endl << endl;
                                                    OKATO_create(object_container);
                                                    second_level << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << "District" << "_" << OKATO_create_code(object_container);
                                                    getline(object_data, object_container);
                                                }
                                                else {
                                                    getline(object_data, object_container);
                                                }
                                            }
                                        }
                                        second_level << str_e_2 << endl << endl << endl;
                                    }
                                    else {
                                        third_level << str_1 << "District" << "_" << OKATO_create_code(object_container) << endl;
                                        third_level << str_b << "District" << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                                        third_level << tabulation << tabulation << str_b << "District" << str_e_1 << endl;
                                        third_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                                        if (clean_quotes_full(atribut(6, object_container)) != "") {
                                            atribut_container = clean_quotes_full(atribut(6, object_container));
                                            for (int j = 0; j < counter(';', atribut_container); j++) {
                                                third_level << tabulation << str_b << "hasAbbr \"" << atribut_abr(j + 1, atribut_container) << "\"" << str_e_1 << endl;
                                            }
                                        }
                                        third_level << tabulation << str_b << "includedIn " << str_b << level_name(2, object_container) << "_" << clean_quotes_full(atribut(1, object_container)) << clean_quotes_full(atribut(2, object_container)) << "000000" << str_e_1 << endl;
                                        third_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container) << str_e_2 << endl << endl << endl;
                                        OKATO_create(object_container);
                                        first_level << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << "District" << "_" << OKATO_create_code(object_container);
                                        getline(object_data, object_container);
                                    }
                                }

                                else {
                                    getline(object_data, object_container);
                                }
                            }
                        }
                        first_level << str_e_2 << endl << endl << endl;
                    }
                    else {
                        if (atribut(3, object_container) != "\"000\"") {
                            second_level_check = atribut(3, object_container);
                            second_level << str_1 << level_name(3, object_container) << "_" << OKATO_create_code(object_container) << endl;
                            second_level << str_b << level_name(3, object_container) << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                            second_level << tabulation << tabulation << str_b << level_name(3, object_container) << str_e_1 << endl;
                            second_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                            if (clean_quotes_full(atribut(6, object_container)) != "") {
                                atribut_container = clean_quotes_full(atribut(6, object_container));
                                for (int j = 0; j < counter(';', atribut_container); j++) {
                                    second_level << tabulation << str_b << "hasAbbr \"" << atribut_abr(j + 1, atribut_container) << "\"" << str_e_1 << endl;
                                }
                            }
                            if (atribut(8, object_container) != "null") {
                                second_level << tabulation << str_b << "hasAdministrativeCenter " << clean_quotes(atribut(8, object_container)) << str_e_1 << endl;
                            }
                            second_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container);
                            second_level << str_e_1 << endl << tabulation << str_b << "includedIn " << str_b << "Region" << "_" << clean_quotes_full(atribut(1, object_container)) << "000000000";
                            OKATO_create(object_container);
                            region << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << level_name(3, object_container) << "_" << OKATO_create_code(object_container);
                            getline(object_data, object_container);
                            while (atribut(3, object_container) == second_level_check) {


                                if (atribut(3, object_container) == second_level_check) {
                                    if (atribut(4, object_container) != "\"000\"") {
                                        third_level << str_1 << "District" << "_" << OKATO_create_code(object_container) << endl;
                                        third_level << str_b << "District" << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                                        third_level << tabulation << tabulation << str_b << "District" << str_e_1 << endl;
                                        third_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                                        if (clean_quotes_full(atribut(6, object_container)) != "") {
                                            atribut_container = clean_quotes_full(atribut(6, object_container));
                                            for (int j = 0; j < counter(';', atribut_container); j++) {
                                                third_level << tabulation << str_b << "hasAbbr \"" << atribut_abr(j + 1, atribut_container) << "\"" << str_e_1 << endl;
                                            }
                                        }
                                        third_level << tabulation << str_b << "includedIn " << str_b << level_name(3, object_container) << "_" << clean_quotes_full(atribut(1, object_container)) << clean_quotes_full(atribut(2, object_container)) << clean_quotes_full(atribut(3, object_container)) << "000" << str_e_1 << endl;
                                        third_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container) << str_e_2 << endl << endl << endl;
                                        OKATO_create(object_container);
                                        second_level << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << "District" << "_" << OKATO_create_code(object_container);
                                        getline(object_data, object_container);
                                    }
                                    else {
                                        getline(object_data, object_container);
                                    }
                                }
                            }
                            second_level << str_e_2 << endl << endl << endl;
                        }
                        else {
                            third_level << str_1 << "District" << "_" << OKATO_create_code(object_container) << endl;
                            third_level << str_b << "District" << "_" << OKATO_create_code(object_container) << str_2_e << endl;
                            third_level << tabulation << tabulation << str_b << "District" << str_e_1 << endl;
                            third_level << tabulation << str_b << "hasTitle " << clean_quotes(atribut(7, object_container)) << str_e_1 << endl;
                            if (clean_quotes_full(atribut(6, object_container)) != "") {
                                atribut_container = clean_quotes_full(atribut(6, object_container));
                                for (int j = 0; j < counter(';', atribut_container); j++) {
                                    third_level << tabulation << str_b << "hasAbbr \"" << atribut_abr(j + 1, atribut_container) << "\"" << str_e_1 << endl;
                                }
                            }
                            third_level << tabulation << str_b << "includedIn " << str_b << "Region" << "_" << clean_quotes_full(atribut(1, object_container)) << "000000000" << str_e_1 << endl;
                            third_level << tabulation << str_b << "hasOKATO " << str_b << OKATO_name << OKATO_create_code(object_container) << str_e_2 << endl << endl << endl;
                            OKATO_create(object_container);
                            region << str_e_1 << endl << tabulation << str_b << "hasNestedObject " << str_b << "District" << "_" << OKATO_create_code(object_container);
                            getline(object_data, object_container);
                        }
                    }
                }
                else {
                    getline(object_data, object_container);
                }
            }
        }
    
    region << str_e_2 << endl << endl << endl;

        }
        object_data.close();
        region.close();
        first_level.close();
        second_level.close();
        third_level.close();
        OKATO.close();
        return 0;
    
}