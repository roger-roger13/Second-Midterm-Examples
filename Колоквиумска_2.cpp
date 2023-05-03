#include <iostream>
#include <cstring>

using namespace std;

// vashiot kod ovde

class Vozac {
protected:
    char ime[101];
    int vozrast;
    int brojNaTrki;
    bool eVeteran;

public:
    Vozac(const char* ime = "", int vozrast = 0, int brojNaTrki = 0, bool eVeteran = false)
            : vozrast(vozrast), brojNaTrki(brojNaTrki), eVeteran(eVeteran) {
        strcpy(this->ime, ime);
    }

    friend ostream& operator<<(ostream& out, const Vozac& v) {
        out << v.ime << endl;
        out << v.vozrast << endl;
        out << v.brojNaTrki << endl;
        if (v.eVeteran)
            out << "VETERAN" << endl;
        return out;
    }

    bool operator==(const Vozac& v) const {
        return zarabotuvachka() == v.zarabotuvachka();
    }

    virtual double zarabotuvachka() const = 0;

    virtual double danok() const = 0;
};

class Avtomobilist : public Vozac {
private:
    double cenaNaAvtomobil;

public:
    Avtomobilist(const char* ime = "", int vozrast = 0, int brojNaTrki = 0, bool eVeteran = false, double cenaNaAvtomobil = 0.0)
            : Vozac(ime, vozrast, brojNaTrki, eVeteran), cenaNaAvtomobil(cenaNaAvtomobil) {}

    double zarabotuvachka() const override {
        return cenaNaAvtomobil / 5;
    }

    double danok() const override {
        if (brojNaTrki > 10)
            return 0.15 * zarabotuvachka();
        return 0.1 * zarabotuvachka();
    }
};

class Motociklist : public Vozac {
private:
    int mokjnostNaMotor;

public:
    Motociklist(const char* ime = "", int vozrast = 0, int brojNaTrki = 0, bool eVeteran = false, int mokjnostNaMotor = 0)
            : Vozac(ime, vozrast, brojNaTrki, eVeteran), mokjnostNaMotor(mokjnostNaMotor) {}

    double zarabotuvachka() const override {
        return mokjnostNaMotor * 20;
    }

    double danok() const override {
        if (eVeteran)
            return 0.25 * zarabotuvachka();
        return 0.2 * zarabotuvachka();
    }
};

int soIstaZarabotuvachka(Vozac** niza, int n, Vozac* v) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (*niza[i] == *v)
            count++;
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}