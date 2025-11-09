#include <iostream>
#include <iomanip> // pentru setarea numarului de zecimale afisate
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

template<class T, class U>
class pereche
{
private:
    T first;
    U second;
public:
    pereche() : first(0), second(0) {}
    pereche(T first, U second) : first(first), second(second) {}
    pereche(const pereche &p)
    {
        this->first = p.first;
        this->second = p.second;
    }

    T getFirst() const { return this->first; }
    U getSecond() const { return this->second; }

    void setFirst(T first) { this->first = first; }
    void setSecond(U second) { this->second = second; }
};

string formatare_pret(int);

template<class T>
void citire_cu_validare(istream &, T &, string, float, float, bool spatii = 0);

template<>
void citire_cu_validare(istream &, string &, string, float, float, bool);

template<>
void citire_cu_validare(istream &, float &, string, float, float, bool);

// ---------- Locuinta ----------

class locuinta
{
private:
    int pret;
    int suprafata;
    int numarCamere;

public:
    locuinta();
    locuinta(int, int, int);
    locuinta(const locuinta &);
    virtual ~locuinta();
    // destructorul trebuie sa fie virtual pentru a chema destructorul corect al copiilor
    // stocati intr-un vector de pointeri de tip locuinta

    locuinta &operator=(const locuinta &);
    friend ostream &operator<<(ostream &, const locuinta &);
    friend istream &operator>>(istream &, locuinta &);

    virtual ostream &afisare(ostream &) const;
    virtual istream &citire(istream &);

    int getPret() const;
    int getSuprafata() const;
    int getNumarCamere() const;

    void setPret(int);
    void setSuprafata(int);
    void setNumarCamere(int);
};

// constructori si destructor locuinta

locuinta ::locuinta() : pret(0), suprafata(0), numarCamere(0)
{
    // cout<<"CD locuinta\n";
}

locuinta ::locuinta(int pret, int suprafata, int numarCamere)
{

    this->pret = pret;
    this->suprafata = suprafata;
    this->numarCamere = numarCamere;
    // cout<<"CP locuinta\n";
}

locuinta ::locuinta(const locuinta &l)
{

    this->pret = l.pret;
    this->suprafata = l.suprafata;
    this->numarCamere = l.numarCamere;
    // cout<<"CC locuinta\n";
}

locuinta ::~locuinta()
{
    // cout<<"D locuinta\n";
}

// operatori locuinta

locuinta &locuinta ::operator=(const locuinta &l)
{

    if (this != &l)
    {
        this->pret = l.pret;
        this->suprafata = l.suprafata;
        this->numarCamere = l.numarCamere;
    }

    return *this;
}

ostream &operator<<(ostream &out, const locuinta &l) { return l.afisare(out); }
istream &operator>>(istream &in, locuinta &l) { return l.citire(in); }

// functii locuinta

ostream &locuinta ::afisare(ostream &out) const
{

    out << formatare_pret(this->pret) << " lei" << "  ";
    out << this->suprafata << " mp" << "  ";
    out << this->numarCamere << " camere" << endl;

    return out;
}

istream &locuinta ::citire(istream &in)
{
    citire_cu_validare(in, this->pret, "Preț: ", 50000, 100000000);
    citire_cu_validare(in, this->suprafata, "Suprafață (mp): ", 100, 10000);
    citire_cu_validare(in, this->numarCamere, "Număr camere: ", 1, 100);
    return in;
}

// getteri locuinta

int locuinta ::getPret() const { return this->pret; }
int locuinta ::getSuprafata() const { return this->suprafata; }
int locuinta ::getNumarCamere() const { return this->numarCamere; }

// setteri locuinta

void locuinta ::setPret(int pret) { this->pret = pret; }
void locuinta ::setSuprafata(int suprafata) { this->suprafata = suprafata; }
void locuinta ::setNumarCamere(int numarCamere) { this->numarCamere = numarCamere; }

// ---------- Casa cu piscina ----------

class casaCuPiscina : public virtual locuinta
{

private:
    string formaPiscina;
    int suprafataPiscina;
    float adancimePiscina;

public:
    casaCuPiscina();
    casaCuPiscina(int, int, int, string, int, float);
    casaCuPiscina(const casaCuPiscina &);
    ~casaCuPiscina();

    casaCuPiscina &operator=(const casaCuPiscina &cp);

    ostream &afisare(ostream &) const;
    istream& citirePiscina(istream &);
    istream &citire(istream &);
    void filtrarePiscina(const vector<locuinta *> &) const;

    string getFormaPiscina() const;
    int getSuprafataPiscina() const;
    float getAdancimePiscina() const;

    void setFormaPiscina(string);
    void setSuprafataPiscina(int);
    void setAdancimePiscina(float);
};

// constructori si destructor casa cu piscina

casaCuPiscina ::casaCuPiscina() : locuinta()
{

    this->formaPiscina = "none";
    this->suprafataPiscina = 0;
    this->adancimePiscina = 0;
    // cout<<"CD casa cu piscina\n";
}

casaCuPiscina ::casaCuPiscina(int pret, int suprafata, int numarCamere, string formaPiscina, int suprafataPiscina, float adancimePiscina) : locuinta(pret, suprafata, numarCamere)
{

    this->formaPiscina = formaPiscina;
    this->suprafataPiscina = suprafataPiscina;
    this->adancimePiscina = adancimePiscina;
    // cout<<"CC casa cu piscina\n";
}

casaCuPiscina ::casaCuPiscina(const casaCuPiscina &cp) : locuinta(cp)
{

    this->formaPiscina = cp.formaPiscina;
    this->suprafataPiscina = cp.suprafataPiscina;
    this->adancimePiscina = cp.adancimePiscina;
    // cout<<"CC casa cu piscina\n";
}

casaCuPiscina ::~casaCuPiscina()
{
    locuinta ::~locuinta();
    // cout<<"D casa cu piscina\n";
}

// operator = casa cu piscina

casaCuPiscina &casaCuPiscina ::operator=(const casaCuPiscina &cp)
{

    this->locuinta ::operator=(cp);
    this->formaPiscina = cp.formaPiscina;
    this->suprafataPiscina = cp.suprafataPiscina;
    this->adancimePiscina = cp.adancimePiscina;

    return *this;
}

// functii casa cu piscina

ostream &casaCuPiscina ::afisare(ostream &out) const
{
    this->locuinta ::afisare(out);
    out << "Piscină " << this->formaPiscina;
    out << " " << this->suprafataPiscina << " mp  ";
    out << "adâncime " << this->adancimePiscina << " m" << endl;

    return out;
}

istream& casaCuPiscina::citirePiscina(istream &in)
{
    citire_cu_validare(in, this->formaPiscina, "Formă piscină: ", 5, 25);
    citire_cu_validare(in, this->suprafataPiscina, "Suprafață piscină (mp): ", 1, 100);
    citire_cu_validare(in, this->adancimePiscina, "Adâncime piscină (m) (ex. 1.8): ", 0.5, 3);
    return in;
}

istream &casaCuPiscina ::citire(istream &in)
{

    this->locuinta::citire(in);
    this->casaCuPiscina::citirePiscina(in);
    return in;

}

void casaCuPiscina ::filtrarePiscina(const vector<locuinta *> &v) const
{

    cout << endl;
    int n = v.size();

    for (int i = 0; i < n; i++)
        if (typeid(*v[i]) == typeid(*this))
            cout << "Casă cu piscină\n" << *v[i] << endl;
}

// getteri casa cu piscina

string casaCuPiscina ::getFormaPiscina() const { return this->formaPiscina; }
int casaCuPiscina ::getSuprafataPiscina() const { return this->suprafataPiscina; }
float casaCuPiscina ::getAdancimePiscina() const { return this->adancimePiscina; }

// setteri casa cu piscina

void casaCuPiscina ::setFormaPiscina(string formaPiscina)
{
    this->formaPiscina = formaPiscina;
}

void casaCuPiscina ::setSuprafataPiscina(int suprafataPiscina)
{
    this->suprafataPiscina = suprafataPiscina;
}

void casaCuPiscina ::setAdancimePiscina(float adancimePiscina)
{
    this->adancimePiscina = adancimePiscina;
}

// ---------- Casa cu garaj ----------

class casaCuGaraj : public virtual locuinta
{

private:
    int capacitateGaraj;
    float lungimeGaraj;
    float latimeGaraj;

public:
    casaCuGaraj();
    casaCuGaraj(int, int, int, int, float, float);
    casaCuGaraj(const casaCuGaraj &);
    ~casaCuGaraj();

    casaCuGaraj &operator=(const casaCuGaraj &);

    ostream &afisare(ostream &) const;
    istream &citire(istream &);
    void filtrareGaraj(const vector<locuinta *> &) const;

    int getCapacitateGaraj() const;
    float getLungimeGaraj() const;
    float getLatimeGaraj() const;

    void setCapacitateGaraj(int);
    void setLungimeGaraj(float);
    void setLatimeGaraj(float);
};

// constructori si destructor casa cu garaj

casaCuGaraj ::casaCuGaraj() : locuinta()
{

    this->capacitateGaraj = 0;
    this->lungimeGaraj = 0;
    this->latimeGaraj = 0;
    // cout<<"CD casa cu garaj\n";
}

casaCuGaraj ::casaCuGaraj(int pret, int suprafata, int numarCamere, int capacitateGaraj, float lungimeGaraj, float latimeGaraj) : locuinta(pret, suprafata, numarCamere)
{

    this->capacitateGaraj = capacitateGaraj;
    this->lungimeGaraj = lungimeGaraj;
    this->latimeGaraj = latimeGaraj;
    // cout<<"CP casa cu garaj\n";
}

casaCuGaraj ::casaCuGaraj(const casaCuGaraj &cg) : locuinta(cg)
{

    this->capacitateGaraj = cg.capacitateGaraj;
    this->lungimeGaraj = cg.lungimeGaraj;
    this->latimeGaraj = cg.latimeGaraj;
    // cout<<"CC casa cu garaj\n";
}

casaCuGaraj ::~casaCuGaraj()
{
    locuinta ::~locuinta();
    // cout<<"D casa cu garaj\n";
}

// operator = casa cu garaj

casaCuGaraj &casaCuGaraj ::operator=(const casaCuGaraj &cg)
{

    this->locuinta ::operator=(cg);
    this->capacitateGaraj = capacitateGaraj;
    this->lungimeGaraj = cg.lungimeGaraj;
    this->latimeGaraj = cg.latimeGaraj;

    return *this;
}

// functii casa cu garaj

ostream &casaCuGaraj ::afisare(ostream &out) const
{

    this->locuinta ::afisare(out);
    out << "Garaj " << this->capacitateGaraj;

    switch (this->capacitateGaraj)
    {
    case 1:
        out << " mașină";
        break;

    default:
        out << " mașini";
    }

    out << "  " << this->lungimeGaraj << " × " << this->latimeGaraj << " m  ";
    out << this->lungimeGaraj * this->latimeGaraj << " mp\n";

    return out;
}

istream &casaCuGaraj ::citire(istream &in)
{
    this->locuinta ::citire(in);
    citire_cu_validare(in, this->capacitateGaraj, "Capacitate garaj (mașini): ", 1, 10);
    citire_cu_validare(in, this->lungimeGaraj, "Lungime garaj (m) (ex. 4.5): ", 3, 30);
    citire_cu_validare(in, this->latimeGaraj, "Lățime garaj: ", 2, 10);
    return in;
}

void casaCuGaraj ::filtrareGaraj(const vector<locuinta *> &v) const
{

    cout << endl;
    int n = v.size();

    for (int i = 0; i < n; i++)
        if (typeid(*v[i]) == typeid(*this))
        {
            cout << "Casă cu garaj\n" << *v[i] << endl;
        }
}

// getteri casa cu garaj

int casaCuGaraj ::getCapacitateGaraj() const { return this->capacitateGaraj; }
float casaCuGaraj ::getLungimeGaraj() const { return this->lungimeGaraj; }
float casaCuGaraj ::getLatimeGaraj() const { return this->latimeGaraj; }

// setteri casa cu garaj

void casaCuGaraj ::setCapacitateGaraj(int capacitateGaraj)
{
    this->capacitateGaraj = capacitateGaraj;
}

void casaCuGaraj ::setLungimeGaraj(float lungimeGaraj)
{
    this->lungimeGaraj = lungimeGaraj;
}

void casaCuGaraj ::setLatimeGaraj(float latimeGaraj)
{
    this->latimeGaraj = latimeGaraj;
}

// ---------- Teren ----------

class teren
{
private:
    float suprafata;
    string vegetatie;

public:
    teren();
    teren(float, string);
    teren(const teren &);
    ~teren();

    teren& operator=(const teren &);
    friend ostream& operator<<(ostream &, const teren &);
    friend istream& operator>>(istream &, teren &);

    float getSuprafata() const;
    string getVegetatie() const;

    void setSuprafata(float);
    void setVegetatie(string);
};

teren::teren() : suprafata(0), vegetatie("None") {}
teren::teren(float suprafata, string vegetatie) : suprafata(suprafata), vegetatie(vegetatie) {}
teren::teren(const teren &t) : suprafata(t.suprafata), vegetatie(t.vegetatie) {}
teren::~teren()
{
    // cout << "D teren\n";
}

teren& teren::operator=(const teren &t)
{
    this->suprafata = t.suprafata;
    this->vegetatie = t.vegetatie;
    return *this;
}

ostream& operator<<(ostream &out, const teren &t)
{
    out << t.suprafata << "  ";
    out << t.vegetatie << endl;
    return out;
}

istream& operator>>(istream &in, teren &t)
{
    citire_cu_validare(in, t.suprafata, "Suprafață teren (ha): ", 0, 500);
    citire_cu_validare(in, t.vegetatie, "Vegetație teren: ", 5, 25, 1);
    return in;
}

float teren::getSuprafata() const { return this->suprafata; }
string teren::getVegetatie() const { return this->vegetatie; }

void teren::setSuprafata(float suprafata) { this->suprafata = suprafata; }
void teren::setVegetatie(string vegetatie) { this->vegetatie = vegetatie; }

// ---------- Vila ----------

class vila : public virtual casaCuPiscina, casaCuGaraj
{
private:
    string arhitectura;
    teren teren;

public:
    vila();
    vila(int, int, int, string, int, float, int, float, float, string, float, string);
    vila(const vila &);
    ~vila();

    vila &operator=(const vila &);

    ostream &afisare(ostream &) const;
    istream &citire(istream &);

    void setArhitectura(string);
    void setSuprafataTeren(float);
};

// constructori si destructor vila

vila::vila() : locuinta(), casaCuPiscina(), casaCuGaraj()
{
    // mostenirea virtuala imi permite sa chem fiecare constructor individual
    this->arhitectura = "none";
    // cout<<"CD vila\n";
}

vila ::vila(int pret, int suprafata, int numarCamere, string formaPiscina, int suprafataPiscina, float adancimePiscina, int capacitateGaraj, float lungimeGaraj, float latimeGaraj, string arhitectura, float suprafataTeren, string vegetatieTeren) : locuinta(pret, suprafata, numarCamere), casaCuPiscina(pret, suprafata, numarCamere, formaPiscina, suprafataPiscina, adancimePiscina), casaCuGaraj(pret, suprafata, numarCamere, capacitateGaraj, lungimeGaraj, latimeGaraj), teren(suprafataTeren, vegetatieTeren)
{
    this->arhitectura = arhitectura;
    // cout<<"CP vila\n";
}

vila ::vila(const vila &v) : locuinta(v), casaCuPiscina(v), casaCuGaraj(v)
{
    this->teren.setSuprafata(v.teren.getSuprafata());
    this->teren.setVegetatie(v.teren.getVegetatie());
    this->arhitectura = v.arhitectura;
    // cout<<"CC vila\n";
}

vila ::~vila()
{
    locuinta ::~locuinta();
    // cout<<"D vila\n";
}

// operator = vila

vila &vila ::operator=(const vila &v)
{

    // operatorul = din copii il cheama si pe cel de la parinte
    // operatorul = din locuinta se va chema de 2 ori, dar nu afecteaza utilizatorul
    this->casaCuPiscina ::operator=(v);
    this->casaCuGaraj ::operator=(v);
    this->arhitectura = v.arhitectura;
    this->teren = v.teren;
    return *this;
}

// functii vila

ostream &vila ::afisare(ostream &out) const
{
    // afisarea din copii va chema si afisarea din Parinte,
    // deci nu se poate folosi afisarea din ambii copii
    // se copiaza afisarile care nu au fost chemate
    out << "Arhitectură " << arhitectura << endl;

    this->casaCuGaraj ::afisare(out);

    out << "Piscină " << this->getFormaPiscina();
    out << " " << this->getSuprafataPiscina() << " mp  ";
    out << "adâncime " << this->getAdancimePiscina() << " m\n";

    out << "Teren " << this->teren.getSuprafata() << " ha  ";
    out << this->teren.getVegetatie() << endl;
    return out;
}

istream &vila ::citire(istream &in)
{
    citire_cu_validare(in, this->arhitectura, "Arhitectură: ", 5, 25);
    this->casaCuGaraj::citire(in);
    this->casaCuPiscina::citirePiscina(in);
    operator>>(in, this->teren);
    return in;
}

// setteri vila

void vila ::setArhitectura(string arhitectura)
{ this->arhitectura = arhitectura; }

void vila ::setSuprafataTeren(float suprafataTeren)
{ this->teren.setSuprafata(suprafataTeren); }

// teste

void testLocuinta()
{
    locuinta l1(3000000, 200, 5), l2(2000000, 150, 4), l3, l4(l1);
    cout << endl
         << l1 << endl
         << l2 << endl;
    l1 = l2;
    cout << l1 << endl;
    cout << endl
         << l2.getPret() << endl
         << l2.getSuprafata() << endl
         << l2.getNumarCamere() << endl;
    cin >> l3;
    cout << l3 << endl;
}

void testCasaCuPiscina()
{
    casaCuPiscina cp1, cp2(4000000, 700, 12, "rotundă", 10, 2.2), cp3(cp2), cp4, cp5 = cp1;
    cout << endl;
    cout << "\ncp1" << cp1 << endl;
    cout << "\ncp2" << cp2 << endl;
    cout << "\ncp3" << cp3 << endl;
    cin >> cp4;
    cout << "\ncp4" << cp4 << endl;
    cout << "\ncp5" << cp5 << endl;
}

void testCasaCuGaraj()
{
    casaCuGaraj cg1, cg2(3000000, 200, 5, 1, 7.5, 5), cg3(cg2), cg4 = cg1, cg5;

    cout << "\ncg1\n"
         << cg1;
    cout << "\ncg2\n"
         << cg2;
    cout << "\ncg3\n"
         << cg3;
    cout << "\ncg4\n"
         << cg4;
    cin >> cg5;
    cout << "\ncg5\n"
         << cg5;
}

void testVila()
{
    vila v1, v2(200000, 400, 6, "rotundă", 14, 1.8, 4, 12.5, 4, "victoriană", 400, "pădure de foioase"), v3(v2), v4 = v1, v5;

    cout << "\nv1\n"
         << v1 << endl;
    cout << "\nv2\n"
         << v2 << endl;
    cout << "\nv3\n"
         << v3 << endl;
    cout << "\nv4\n"
         << v4 << endl;
    cout << "\nv5\n";
    // cin >> v5;
    // cout << v5 << endl;
}

// functii si exceptii

class input_invalid : public exception {};

class input_invalid_cu_spatii : public exception {};

class nu_este_int : public exception {};

class numar_prea_mic : public exception {};

class numar_prea_mare : public exception {};

class string_prea_scurt : public exception {};

class string_prea_lung : public exception {};

string tip_locuinta(locuinta *l)
{
    // dynamic cast functioneaza doar cu clase abstracte
    if(dynamic_cast<vila *>(l))
        return "Vilă";

    else if(dynamic_cast<casaCuPiscina *>(l))
        return "Casă cu piscină";

    else if(dynamic_cast<casaCuGaraj *>(l))
        return "Casă cu garaj";
    return "-1";
}

void afisare_tip_locuinta(locuinta *l)
{
    cout << tip_locuinta(l);
    if(tip_locuinta(l) == "Vilă")
        cout << "  ";
    else cout << endl;
}

void afisare_sortare_raport_pret_suprafata (vector<locuinta *> v)
{
    // se creeaza o copie a vectorului de pointeri, nu se creeaza copii pentru obiecte
    int n = v.size();

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            // dereferentiez adresa de la v[i] si fac raportul pret/suprafata
            if (v[i]->getPret() / v[i]->getSuprafata() > v[j]->getPret() / v[j]->getSuprafata())
            {
                locuinta *aux = v[i]; // retin adresa de la v[i] intr-un pointer auxiliar
                v[i] = v[j];          // inversez adresele, nu obiectele din v[i] si v[j] pentru a pastra
                v[j] = aux;           // ordinea obiectelor din vectorul primit ca parametru
            }
        }
    for (int i = 0; i < n; i++)
    {
        cout << formatare_pret(v[i]->getPret() / v[i]->getSuprafata()) << " lei/mp ";
        afisare_tip_locuinta(v[i]);
        cout << *v[i] << endl;
    }
    // nu este nevoie sa eliberez memoria pentru ca nu s-au creat copii pentru obiecte
}

/* void actualizare (locuinta &l) {

int x, k = 1;

casaCuPiscina cp; casaCuGaraj cg; vila v;

int pret, suprafata, numarCamere, suprafataPiscina, capacitateGaraj, suprafataTeren;
float adancimePiscina, lungimeGaraj, latimeGaraj;
string formaPiscina, arhitectura;

while(k == 1) {

if(typeid(l) == typeid(cp)) {

cout<<"[1] Preț            [2] Suprafață           [3] Număr camere\n\n";

cout<<"[4] Formă piscină   [5] Suprafață piscină   [6] Adâncime piscină\n\n";

cout<<"[7] Toate           [8] Ieșire\n\n";

cout<<"Alege câmpul: ";
cin>>x;

switch(x) {

case 1: {
l.
}

}

}
}

}
*/

string formatare_pret(int p)
{
    string s = to_string(p), t = "";
    int n = s.length(), c = 0;
    for(int i=n-1; i>=0; i--)
    {
        c++;
        t = t + s[i];
        if(i-1 >= 0 && c%3 == 0)
            t = t + ".";
    }
    n = t.length();
    for(int i = 0; i < n/2; i++)
        swap(t[i], t[n-i-1]);
    return t;
}

void afisare_lista_preturi(const vector<pereche<string, int>> &p)
{
    int n = p.size();
    for(int i=0; i<n; i++)
    {
        int len_total = 0, len_s, len_linie;
        string pret = formatare_pret(p[i].getSecond());
        cout<<p[i].getFirst()<<" ";
        // length() nu calculeaza corect lungimea stringurilor cu diacritice
        // (fiecare diacritica se ia ca 2 caractere)
        if(p[i].getFirst() == "Casă cu piscină")
            len_s = 15;
        else if(p[i].getFirst() == "Casă cu garaj")
            len_s = 13;
        else if (p[i].getFirst() == "Vilă")
            len_s = 4;
        
        len_total = len_s + pret.length();
        len_linie = 50;
        // afisez spatii in functie de lungimea stringului si a numarului
        while(len_linie - len_total > 0)
        {
            cout<<".";
            len_total++;
        }
        cout<<" ";
        cout << formatare_pret(p[i].getSecond()) << " lei" << endl << endl;
    }
}

void afisare_vector_pointeri(const vector<locuinta *> &v)
{
    int n = v.size();

    for (int i = 0; i < n; i++)
        cout << *v[i] << endl;
}

void afisare_toate_locuintele(const vector<locuinta *> &v)
{
    int n = v.size();

    for (int i = 0; i < n; i++)
    {
        afisare_tip_locuinta(v[i]);
        cout << *v[i] << endl;
    }
}

int validare_string(string s, bool spatii)
{
    const char *c_str = s.c_str();
    int n = s.length();
    for(int i=0; i<n; i++)
    {
        if (spatii)
        {
            if (c_str[i] < 'A' && c_str[i] != ' ')   
                return 2;
        }

        else
            if (c_str[i] < 'A')
                return 1;
            
        if (c_str[i] > 'Z' && c_str[i] < 'a')
            return 1;
                
        if (c_str[i] > 'z')
            return 1;        
    }
    return 0;
}

template<class T>
void citire_cu_validare(istream &in, T &x, string var_de_citit, float min, float max, bool spatii)
{
    char c;
    int k = 1;
    while(k == 1)
    {
        try
        {
            cout << var_de_citit;
            in >> x;

            if (!in) // daca in loc de int primeste litere (si apoi cifre) sau float
            {
                in.clear();
                throw input_invalid();
            }

            in.get(c);

            if (c == '.')
                throw nu_este_int();

            if (c != 10) // daca primeste cifre si apoi litere
                throw input_invalid();
            
            if (x < min)
                throw numar_prea_mic();
            
            if (x > max)
                throw numar_prea_mare();

            k = 2;
        }

        catch (input_invalid &e)
        {
            in.ignore(10000, '\n');
            cout << "Input invalid.\n";
        }

        catch (nu_este_int &e)
        {
            in.ignore(10000, '\n');
            cout << "Valoarea introdusă trebuie să fie un număr natural." << endl;
        }

        catch (numar_prea_mic &e)
        {
            cout << "Valoarea introdusă este prea mică." << endl;
            cout << "Valoare minimă: " << formatare_pret(min) << endl;
        }

        catch (numar_prea_mare &e)
        {
            cout << "Valoarea introdusă este prea mare." << endl;
            cout << "Valoare maximă: " << formatare_pret(max) << endl;
        }

        catch (...) {}

    }
}

template<>
void citire_cu_validare(istream &in, string &x, string var_de_citit, float min, float max, bool spatii)
{
    int k = 1;
    while (k == 1)
    {
        try
        {   
            cout << var_de_citit;
            getline(in, x);

            if (validare_string(x, spatii) == 1)
                throw input_invalid();

            if (validare_string(x, spatii) == 2)
                throw input_invalid_cu_spatii();

            if (x.length() < min)
                throw string_prea_scurt();

            if (x.length() > max)
                throw string_prea_lung();

            k = 2;
        }

        catch (input_invalid &e)
        {
            cout << "Textul introdus poate conține numai litere.\n";
        }

        catch (input_invalid_cu_spatii &e)
        {
            cout << "Textul introdus poate conține numai litere și spații.\n";
        }

        catch (string_prea_scurt &e)
        {
            cout << "Introduceți minim " << min << " caractere.\n";
        }

        catch (string_prea_lung &e)
        {
            cout << "Introduceți maxim " << max << "caractere.\n";
        }

        catch (...) {}
    }
}

template<>
void citire_cu_validare(istream &in, float &x, string var_de_citit, float min, float max, bool spatii)
{
    char c;
    int k = 1;
    while(k == 1)
    {
        try
        {
            cout << var_de_citit;
            in >> x;

            if (!in) // daca in loc de int primeste litere (si apoi cifre) sau float
            {
                in.clear();
                throw input_invalid();
            }

            in.get(c);

            if (c == '.')
                throw nu_este_int();

            if (c != 10) // daca primeste cifre si apoi litere
                throw input_invalid();
            
            if (x < min)
                throw numar_prea_mic();
            
            if (x > max)
                throw numar_prea_mare();

            k = 2;
        }

        catch (input_invalid &e)
        {
            in.ignore(10000, '\n');
            cout << "Input invalid.\n";
        }

        catch (nu_este_int &e)
        {
            in.ignore(10000, '\n');
            cout << "Valoarea introdusă trebuie să fie un număr natural." << endl;
        }

        catch (numar_prea_mic &e)
        {
            cout << "Valoarea introdusă este prea mică." << endl;
            cout << "Valoare minimă: " << min << endl;
        }

        catch (numar_prea_mare &e)
        {
            cout << "Valoarea introdusă este prea mare." << endl;
            cout << "Valoare maximă: " << max << endl;
        }

        catch (...) {}
    }
}

class Singleton
{
private:
    static Singleton *instance;
    Singleton() {}

public:
    static Singleton *getInstance()
    {
        if (Singleton::instance != NULL)
        {
            return Singleton::instance;
        }
        else
        {
            instance = new Singleton();
            return instance;
        }
    }

    void meniu()
{
    vector<locuinta *> v;
    vector<pereche<string, int>> p;
    vila v1(4650000, 544, 9, "ovală", 30, 1.8, 3, 15, 6, "victoriană", 0.17, "pădure de foioase");
    vila v2(8500000, 743, 9, "dreptunghiulară", 24, 1.8, 4, 20, 7, "victoriană", 0.86, "pădure de conifere");
    casaCuPiscina cp1(200000, 250, 4, "rotundă", 10, 1.8);
    casaCuGaraj cg1(300000, 200, 3, 1, 4.5, 4);

    int k = 1;

    v.push_back(new vila(v1));
    v.push_back(new vila(v2));
    v.push_back(new casaCuPiscina(cp1));
    v.push_back(new casaCuGaraj(cg1));

    int n = v.size();

    for(int i=0; i<n; i++)
    {
        if(typeid(*v[i]) == typeid(cp1))
            p.push_back({"Casă cu piscină", v[i]->getPret()});
        else if(typeid(*v[i]) == typeid(cg1))
            p.push_back({"Casă cu garaj", v[i]->getPret()});
        else if(typeid(*v[i]) == typeid(v1))
            p.push_back({"Vilă", v[i]->getPret()});
    }

    while (k == 1)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                       
        cout << "[1] Creează o locuință          [2] Afișează locuințele\n\n";

        cout << "[3] Actualizează o locuință     [4] Șterge o locuință\n\n";

        cout << "[5] Ieșire\n\n";

        int x, y;
        char c;

        try
        {
            cin >> x;
            if (!cin) // daca primeste litere (si apoi cifre)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                throw input_invalid();
            }
            cin.get(c);
            if (c != 10) // daca primeste cifre si apoi litere
            {
                cin.ignore(10000, '\n');
                throw input_invalid();
            }
        }
        catch (input_invalid &e)
        {
            x = -1;
        }
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        switch (x) {

        case 1: // creare locuinta
        {                
            cout << "[1] Creează o casă cu piscină   [2] Creează o casă cu garaj\n\n";

            cout << "[3] Creează o vilă              [0] Meniul principal\n\n";

            cout << "\n\n";

            try
            {
                cin >> y;
                if (!cin) // daca primeste litere (si apoi cifre)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw input_invalid();
                }
                cin.get(c);
                if (c != 10) // daca primeste cifre si apoi litere
                {
                    cin.ignore(10000, '\n');
                    throw input_invalid();
                }
            }
            catch (input_invalid &e)
            {
                y = -1;
            }
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            switch(y) {

            case 0:
                break;

            case 1:
            {
                casaCuPiscina cp;
                cin >> cp;
                v.push_back(new casaCuPiscina(cp));
                p.push_back({"Casă cu piscină", cp.getPret()});
                break;
            }

            case 2:
            {
                casaCuGaraj cg;
                cin >> cg;
                v.push_back(new casaCuGaraj(cg));
                p.push_back({"Casă cu garaj", cg.getPret()});
                break;
            }

            case 3:
            {
                vila vi;
                cin >> vi;
                v.push_back(new vila(vi));
                p.push_back({"Vilă", vi.getPret()});
                break;
            }
            }
            if (y != 0)
            {
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                cout << "Locuința a fost creată!\n\n";
                afisare_tip_locuinta(v[v.size()-1]);   
                cout << *v[v.size()-1]<<endl;
                cout << "[Enter] Meniul principal\n";
                cin.get(c);
            }
            break;
        }

        case 2: // afisare locuinte
        {                
            cout << "[1] Listă prețuri               [2] Toate locuințele\n\n";

            cout << "[3] Toate locuințele            [4] Locuințe cu piscină\n";
            cout << "    ( ^ preț/suprafață)\n\n";

            cout << "[5] Locuințe cu garaj           [0] Meniul principal\n\n";

            try
            {
                cin >> y;
                if (!cin) // daca primeste litere (si apoi cifre)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    throw input_invalid();
                }
                cin.get(c);
                if (c != 10) // daca primeste cifre si apoi litere
                {
                    cin.ignore(10000, '\n');
                    throw input_invalid();
                }
            }
            catch (input_invalid &e)
            {
                y = -1;
            }
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            switch(y) {

            case 0:
                break;
            
            case 1:
            {
                afisare_lista_preturi(p);
                cout << "[Enter] Meniul principal\n";
                cin.get(c);
                break;
            }

            case 2:
            {
                afisare_toate_locuintele(v);
                cout << "[Enter] Meniul principal\n";
                cin.get(c);
                break;
            }

            case 3:
            {
                afisare_sortare_raport_pret_suprafata(v);
                cout << "[Enter] Meniul principal\n";
                cin.get(c);
                break;
            }

            case 4:
            {
                casaCuPiscina cp;
                cp.filtrarePiscina(v);
                cout << "[Enter] Meniul principal\n";
                cin.get(c);
                break;
            }

            case 5:
            {
                casaCuGaraj cg;
                cg.filtrareGaraj(v);
                cout << "[Enter] Meniul principal\n";
                cin.get(c);
                break;
            }
            }
            break;
        }

        case 3: // actualizare locuinta
        {
            int n = v.size();
            int i;
            for (i = 0; i < n; i++)
            {
                cout << i + 1 << ".\n";
                afisare_tip_locuinta(v[i]);
                cout << *v[i] << endl;
            }
            cout << "[0] Anulare\n\n";
            citire_cu_validare(cin, y, "Alege locuința: ", 0, i);
            if (y == 0)
                break;
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cin >> *v[y-1];
            p[y-1].setSecond(v[y-1]->getPret());
            cout << "Locuința a fost actualizată!\n\n";
            cout << *v[y-1];
            cout << endl;
            cout << "[Enter] Meniul principal\n";
            cin.get(c);
            break;
        }

        case 4: // stergere locuinta
        {
            // pentru a sterge obiectul de la o adresa din vectorul de pointeri
            // trebuie sa folosesc iteratorul
            vector<locuinta *>::iterator it;
            int n = v.size();
            it = v.begin();
            int i;
            for (i = 0; i < n; i++)
            {
                cout << i + 1 << ". ";
                afisare_tip_locuinta(v[i]);
                cout << *v[i] << endl;
            }
            cout << "[0] Anulare\n\n";
            citire_cu_validare(cin, y, "Alege locuința: ", 0, i);
            if (y == 0)
                break;
            delete *(it + y - 1); // sterg obiectul de la adresa din vector
            v.erase(it + y - 1);  // sterg adresa din vector
            vector<pereche<string, int>>::iterator it_p;
            it_p = p.begin();
            p.erase(it_p + y - 1);
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            cout << "Locuința a fost ștearsă!\n\n";
            cout << "[Enter] Meniul principal\n";
            cin.get(c);
            break;
        }

        case 5:
        {
            k = 2;
            break;
        }
        }
    }
}
};

Singleton *Singleton::instance = NULL;

void test()
{
    vector<locuinta *> v;
    vector<pereche<string, int>> p;
    int n = v.size();
    locuinta l1(225000, 540, 6), l2(100000, 200, 4);
    casaCuPiscina cp1(600000, 700, 8, "rotundă", 12, 1.8), cp2(320000, 300, 5, "rotundă", 12, 1.8);
    casaCuGaraj cg1(360000, 235, 4, 1, 5.2, 4.3), cg2(900000, 300, 3, 3, 5, 8);

    v.push_back(new locuinta(l1));
    v.push_back(new casaCuPiscina(cp1));
    v.push_back(new locuinta(l2));
    v.push_back(new casaCuPiscina(cp2));
    v.push_back(new casaCuGaraj(cg1));
    v.push_back(new casaCuGaraj(cg2));

    // p.push_back({"Casă cu piscină", v[1]->getPret()});

    // cout<<p[0].getFirst()<<endl<<p[0].getSecond()<<endl;

    // afisare_lista_preturi(p);

    if(typeid(*v[1]) == typeid(cp1))
        p.push_back({"cp", 100});

    cout<<p[0].getFirst()<<endl<<p[0].getSecond()<<endl;

    // for(int i = 0; i < v.size(); i++) cout<<*v[i]<<endl;
    // l1.sortare(v);
    // cp1.filtrare(v);
    // cg1.(v);

    // vector<locuinta *>::iterator it;

    // for(it = v.begin(); it < v.end(); it++)
    // delete *it;

    // it = v.begin();

    // delete *(it+1);
}

int main()
{
    // test();
    // testLocuinta();
    // testCasaCuPiscina();
    // testCasaCuGaraj();
    // testVila();
    // meniu();
    Singleton *s = Singleton::getInstance();
    s->meniu();
    return 0;
}
