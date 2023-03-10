// Zadanie 10 - usuwacz. Posiadasz vector<char> z zawartoscia {'S','A','b','S','S','b','S','y','S'}. Usun z niego za pomoca algorytmow litere 'S' i niech vector zmieni swoj rozmiar na prawidlowy.
// Wypisz odpowiedz na ekranie.
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
//************************************************************************************************************************
int main()
{
    vector<char> litery = {'S',
                           'A',
                           'b',
                           'S',
                           'S',
                           'b',
                           'S',
                           'y',
                           'S'};

    litery.erase(remove(litery.begin(), litery.end(), 'S'), litery.end());

    for(const auto& elem : litery) {
        cout << elem;
    }
}