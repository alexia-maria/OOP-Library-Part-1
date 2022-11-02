#include<iostream>
#include<cstring>
#include<cstdlib>
using namespace std;


class Produs {
    char *denumire = nullptr;
    int pret;

    public :

    Produs() = default;

    Produs(const char *denumire_, int pret_) {
        size_t len = strlen(denumire_);
        this->denumire = new char[len + 1];
        strcpy(this->denumire, denumire_);
        this->pret = pret_;
    }
    char *getDenumire()const{
        return this->denumire;
    }

    int getPret() const {
        return this->pret;
    }

    void setDenumire(const char *denumire_) {
        delete[] this->denumire;

        size_t len = strlen(denumire_);
        this->denumire = new char[len + 1];
        strcpy(this->denumire, denumire_);
    }

    void setPret(int pret_) {
        this->pret = pret_;
    }


        ~Produs() {
        delete[] denumire;
    }

    Produs(const Produs &prod) {
      size_t len = strlen(prod.denumire);
      denumire = new char[len + 1];
      strcpy(denumire, prod.denumire);

      pret = prod.pret;
    }

    void afisare() {
      cout<<"produsul are denumirea "<<this->denumire<<"si pretul "<<this->pret<<"\n";
    }

    Produs &operator=(const Produs &rhs) {
      if(this != &rhs) {
        delete this->denumire;
        this->denumire = new char[strlen(rhs.denumire) + 1];
        strcpy(this->denumire, rhs.denumire);
        this->pret = rhs.pret;
      }
      return *this;
    }

    friend istream &operator>>(istream &is, Produs &p) {
      char buf[255];
      is.getline(buf, 255);
      p.denumire = new char[strlen(buf) + 1];
      strcpy(p.denumire, buf);
      is>>p.pret;
      return is;
    }
    
     friend ostream &operator<<(ostream &os, const Produs &n) {
      os<<"denumirea este "<<n.denumire<<" si pretul este "<<n.pret<<"\n";
      return os;
    }

    bool operator==(const Produs &rhs) const {
      return strcmp(this->denumire, rhs.denumire) == 0 && this->pret == rhs.pret;
    }

    bool operator!=(const Produs &rhs) const {
      return !(*this == rhs);
    }

};

class Magazin {
  int nrProduse;
  Produs **produse;

  public :
  Magazin(int nrProduse_, Produs **produse_) {
    this->produse = new Produs*[nrProduse_];
    for(int i = 0; i < nrProduse_; i++) {
      this->produse[i] = produse_[i];
    }
    nrProduse = nrProduse_;
  }

  void listeaza_produse() {
    int i;
   cout<<this->nrProduse;
    for(i = 0; i < this->nrProduse; i++) {
     cout<<"produsul "<<i<<" are denumirea "<<this->produse[i]->getDenumire()<<" si pretul "<<this->produse[i]->getPret()<<"\n";
    }
  }


void adauga_Produse(Produs *prod) {
  cout<<"**";
  Produs **bkp = new Produs*[nrProduse];

  for(int i = 0; i < nrProduse; i++) {
    bkp[i] = produse[i];
  }
  delete [] produse;
  //delete [] this->produse;
  this->nrProduse++;
  this->produse = new Produs*[nrProduse];
  for(int i = 0; i < nrProduse - 1; i++) {
    this->produse[i] = bkp[i];
  }
  delete [] bkp;
  produse[nrProduse - 1] = prod;
}

  Magazin &operator+=(Produs &rhs) {
  Produs **bkp = new Produs*[nrProduse];

  for(int i = 0; i < nrProduse; i++) {
    bkp[i] = produse[i];
  }
  delete [] produse;
  this->nrProduse++;
  this->produse = new Produs*[nrProduse];
  for(int i = 0; i < nrProduse - 1; i++) {
    this->produse[i] = bkp[i];
  }
  delete [] bkp;
  produse[nrProduse - 1] = &rhs;
  return *this;
  }

  ~Magazin() {
    delete [] produse;
  }

  };


int main() {
int n, val;
char *buf = new char[100];

cout<<"Specificati cate produse doriti sa introduceti in baza de date ";
cin>>n; 
Produs** arr = new Produs*[n];

for(int i = 0; i < n; i++) {
    cout<<"\n Precizati denumirea produsului ";
    cin>>buf;

    cout<<"\n Precizati pretul produsului ";
    cin>>val;

    arr[i] = new Produs(buf, val);    
}

Produs p1("carne", 15);
Produs p2("lapte", 10);
Produs p3("apa", 2);

Produs *sir[] = {&p1, &p2, &p3};
Magazin *M = new Magazin(3, sir);

int key;
cout<<"Pentru a afisa cele n produse, apasati tasta 1\n";
cout<<"pentru a modifica denumirea si pretul unui produs, apasati tasta 2\n";
cout<<"Pentru a copia datele unui produs, apasati tasta 3\n";
cout<<"Pentru a vedea lista cu produsele magazinului, apasati tasta 4\n";
cout<<"Pentru a adauga un nou produs in baza de date a magazinului, apasati tasta 5\n";
cout<<"Pentru a adauga un nou produs cu operatorul +=, apasati tasta 6\n";
cout<<"Pentru a vedea implementarea operatorului >>(supraincarcarea opeartorilor) apasati tasta 7.\n"; 
cout<<"In acest caz, Adaugati denumirea imediat dupa ce ati apasat tasta, iar pretul pe randul urmator : \n";
cout<<"Pentru a vedea implementarea operatorilor == si !=, apasati tasta 8\n";

cin>>key;
switch(key) {
  case 1 : {
    for(int i = 0; i < n; i++) {
      cout<<"\nDenumirea produsului este "<<arr[i]->getDenumire();     
      cout<<"\n Pretul produsului este "<<arr[i]->getPret();
  }
  break;
  }

  case 2 : {
    int j;
    cout<<"\n specificati indicele produsului pe care doriti sa il modificati ";
    cin>>j;

    char *buf2 = new char[100];
    cout<<"\n noua denumire este ";
    cin>>buf2;

    int val2;
    cout<<"noul pret este ";
    cin>>val2;

    arr[j]->setDenumire(buf2);
    arr[j]->setPret(val2);

    cout<<"denumirea setata este "<<arr[j]->getDenumire();
    cout<<"\n pretul setat este"<<arr[j]->getPret();
    delete [] buf2;

    break;
  }

  case 3 : {
    int k;
    cout<<"\n indicele produsului pe care doriti sa il copiati ";
    cin>>k;

    Produs p = *(arr[k]);
    cout<<"denumirea este "<<p.getDenumire();
    cout<<"\n pretul este "<<p.getPret();

    break;
  }

  case 4 : {
    M->listeaza_produse();
    break;
  }

  case 5 : {
    cout<<"Denumirea este \n";
    char *buf3 = new char[100];
    cin>>buf3;
    int val3;
    cout<<"Pretul este \n";
    cin>>val3;
    Produs *p4 = new Produs(buf3, val3);
    M->adauga_Produse(p4);

    M->listeaza_produse();
    delete [] buf3;
    delete p4;
      break;
  }

  case 6 : {
    char *buf4 = new char[255];
    cout<<"precizati denumirea produsului ";
    cin>>buf4;

    int val4;
    cout<<"\nPrecizati opretul produsului ";
    cin>>val4;

    Produs prod(buf4, val4);
    (*M)+=prod;
    M->listeaza_produse();

    delete [] buf4;
    break;
  }

  case 7 : {
    Produs p0;
    cin>>p0;
    cout<<p0;
    break;
  }
        
   case 8 : {
    Produs a, b, c;
    a.setDenumire("paine");
    a.setPret(4);

    b.setDenumire("paine");
    b.setPret(4);

    c.setDenumire("paine");
    c.setPret(5);

    if(a == b) {
      cout<<"a si b sunt egale\n";
    } else {
      cout<<"a si b nu sunt egale\n";
    }

    if(a != c) {
      cout<<"a si c sunt diferite\n";
    } else {
      cout<<"a si c nu sunt diferite\n";
    }

    break;
  }
}

for(int i = 0; i < n; i++) {
  delete arr[i];
}
delete [] arr;
delete [] buf; 
delete M;

return 0;
}
