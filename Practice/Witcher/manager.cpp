#include "manager.h"
#include <iostream>
#include <functional>
using namespace std;
//***********************************************************************************************
template <typename T>
T wprowadzenie(std::string napis = "")
{
    cout << napis;
    T zmienna;
    cin >> zmienna;
    return zmienna;
}
//***********************************************************************************************
template <>
string wprowadzenie(std::string napis) 
{
    cout << napis;
    string zmienna;
    getline((cin >> ws), zmienna);
    return zmienna;
}
//***********************************************************************************************
void wypisz_wynik_rzutu(const Player& gracz)
{
    cout << "Gracz " << gracz.daj_imie() << " wyrzucil: ";
    for(auto& elem : gracz.daj_koscie())
    {
        cout << elem << ", ";
    }
    cout << endl;
}
//***********************************************************************************************
void GameManager::rozpocznij_gre()
{
    // Niech zyje losowosc!
    srand(time(NULL));

    int ilosc_graczy = wprowadzenie<int>("Wprowadz ilosc graczy: ");

    while(ilosc_graczy-- > 0)
    {
        string imie = wprowadzenie<string>("Wprowadz imie gracza: " );
        int ilosc_kosci = wprowadzenie<int>("Wprowadz ilosc kosci: ");
        bool czy_k = wprowadzenie<int>("1 - Gracz, 2 - Komputer: ");

        gracze.insert(gracze.end(), Player(imie, czy_k, ilosc_kosci));
    }

    zacznij_kolejna_runde();
}
//***********************************************************************************************
void GameManager::ruch_komputera(Player& gracz)
{
    gracz.rzucz_kosci();
}
//***********************************************************************************************
auto GameManager::daj_dzialania(Player &gracz)
{
    para_funkcjaGracza_opisFunkcji mozliwosci;

    mozliwosci.first.push_back(&Player::rzucz_kosci);
    mozliwosci.second.push_back("1 - Rzut koscmi");

    mozliwosci.first.push_back(&Player::pas);
    mozliwosci.second.push_back("2 - Pasowanie");

    return mozliwosci;
}
//***********************************************************************************************
void GameManager::wypisz_dzialania(para_funkcjaGracza_opisFunkcji para)
{
    for(const auto& elem : para.second)
    {
        cout << elem << ", ";
    }
    cout << endl;
}
//***********************************************************************************************
bool zrob_dzialanie(int odp, Player& gracz, para_funkcjaGracza_opisFunkcji& para)
{
    wskazniki_na_funkcje mozliwosci = para.first;
    auto wsk = mozliwosci.at(odp);

    (gracz.*wsk)();
    return true;
}
//***********************************************************************************************
void GameManager::ruch_gracza(Player& gracz)
{
    if(!gracz.czy_jest_komputerem())
    {
        ruch_komputera(gracz);
        return;
    }

    auto mozl = daj_dzialania(gracz);
    wypisz_dzialania(mozl);

    while(true)
    {
        int odpowiedz = wprowadzenie<int>("Wybierz dzialanie: ");
        if(zrob_dzialanie(--odpowiedz, gracz, mozl))
            break;
    }
}
//***********************************************************************************************
void GameManager::wyniki()
{
    cout << "\n\tWYNIKI: " << endl;
    for (const auto &elem : gracze)
    {
        wypisz_wynik_rzutu(elem);
    }
}
//***********************************************************************************************
void GameManager::koniec_i_zwyciezca(const Player& gracz)
{
    cout << "Wygrywa " << gracz.daj_imie() << "! Kongratulacje!" << endl;
}
//***********************************************************************************************
void GameManager::zacznij_kolejna_runde()
{
    ilosc_rund++;

    cout << "\n\n\tZaczynamy runde numer " << ilosc_rund << "!" << endl;

    for(auto& elem : gracze)
    {
        elem.rzucz_kosci();
        wypisz_wynik_rzutu(elem);
    }

    for(auto& elem : gracze)
    {
        ruch_gracza(elem);
    }

    wyniki();

    for(const auto& elem : gracze)
    {
        if(ilosc_rund == elem.daj_ilosc_wygranych())
        {
            koniec_i_zwyciezca(elem);
            return;
        }
    }

    zacznij_kolejna_runde();
}
