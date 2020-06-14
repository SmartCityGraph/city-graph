#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <vector>
#include <stdlib.h>
using namespace std;
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
    
        return line;
    
}
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

int main()
{
    
    ifstream object_data("data.csv");
    ofstream OKATO;
    OKATO.open("okato.txt");
    string object;
    string abr;
    for (int i = 0; i < 192389; i++) {
        if (i % 1000 == 0) {
            cout << i << " ";
        }
        getline(object_data, object);
        abr = atribut(6, object);
        string abr_atr = "";
        if (abr.find("\"с ") != (-1)) {
            abr_atr = abr_atr + "с;";
        }
        if (abr.find(" кп\"") != (-1) || abr.find("\"кп") != (-1)) {
            abr_atr = abr_atr + "кп;";
        }
        if (abr.find(" пс\"") != (-1)) {
            abr_atr = abr_atr + "пс;";
        }
        if (abr.find(" сс") != (-1)) {
            abr_atr = abr_atr + "сс;";
        }
        if (abr.find(" смн\"") != (-1)) {
            abr_atr = abr_atr + "смн;";
        }
        if (abr.find(" вл\"") != (-1)) {
            abr_atr = abr_atr + "вл;";
        }
        if (abr.find(" дп") != (-1) || abr.find("дп ") != (-1)) {
            abr_atr = abr_atr + "дп;";
        }
        if (abr.find(" п ") != (-1) || abr.find("п ") != (-1)) {
            abr_atr = abr_atr + "п;";
        }
        if (abr.find("нп ") != (-1)) {
            abr_atr = abr_atr + "нп;";
        }
        if (abr.find("п.ст") != (-1)) {
            abr_atr = abr_atr + "п.ст;";
        }
        if (abr.find("ж/д ст") != (-1)) {
            abr_atr = abr_atr + "ж/д ст;";
        }
        if (abr.find("ж/д будка") != (-1)) {
            abr_atr = abr_atr + "ж/д будка;";
        }
        if (abr.find("ж/д казарма") != (-1)) {
            abr_atr = abr_atr + "ж/д казарма;";
        }
        if (abr.find("ж/д Платформа") != (-1)) {
            abr_atr = abr_atr + "ж/д Платформа;";
        }
        if (abr.find("ж/д рзд") != (-1)) {
            abr_atr = abr_atr + "ж/д рзд;";
        }
        if (abr.find("ж/д остановочный пункт") != (-1)) {
            abr_atr = abr_atr + "ж/д остановочный пункт;";
        }
        if (abr.find("ж/д путевой пост") != (-1)) {
            abr_atr = abr_atr + "ж/д путевой пост;";
        }
        if (abr.find("ж/д блокпост") != (-1)) {
            abr_atr = abr_atr + "ж/д блокпост;";
        }
        if (abr.find("\"м ") != (-1)) {
            abr_atr = abr_atr + "м;";
        }
        if (abr.find("\"д ") != (-1)) {
            abr_atr = abr_atr + "д;";
        }
        if (abr.find("\"сл ") != (-1)) {
            abr_atr = abr_atr + "сл;";
        }
        if (abr.find("ст-ца ") != (-1)) {
            abr_atr = abr_atr + "ст-ца;";
        }
        if (abr.find("\"х") != (-1)) {
            abr_atr = abr_atr + "х;";
        }
        if (abr.find("\"у ") != (-1)) {
            abr_atr = abr_atr + "у;";
        }
        if (abr.find("\"рзд ") != (-1) || abr.find(" рзд") != (-1)) {
            abr_atr = abr_atr + "рзд;";
        }
        if (abr.find("клх") != (-1)) {
            abr_atr = abr_atr + "клх;";
        }
        if (abr.find("свх") != (-1)) {
            abr_atr = abr_atr + "свх;";
        }
        if (abr.find("\"у ") != (-1)) {
            abr_atr = abr_atr + "у;";
        }
        if (abr.find("\"ст ") != (-1) || abr.find(" ст ") != (-1) || abr.find(" ст\"") != (-1)) {
            if (abr.find("ж/д") == (-1)) {
                abr_atr = abr_atr + "ст;";
            }
        }
        OKATO << atribut(1, object) << ";" << atribut(2, object) << ";" << atribut(3, object) << ";" << atribut(4, object) << ";" << atribut(5, object) << ";\""  << abr_atr << "\";" << atribut(6, object) << ";" << atribut(7, object) << ";" << atribut(8, object) << ";" << atribut(9, object) << ";" << atribut(10, object) << ";" << atribut(11, object) << ";" << atribut(12, object) << endl;
    }

}