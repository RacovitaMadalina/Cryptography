// RSA cript+ decript.cpp : Defines the entry point for the console application.

#include<iostream>
#include<fstream>
#include<math.h>
#include<NTL/ZZ.h> // I used the library WinNTL

using namespace std;
using namespace NTL;

ZZ p, q, n, phi, key_private, key_public, e, d, m, x, y;

void criptare(ZZ m, ZZ key_public, ZZ n)
{
    y = PowerMod(m, key_public, n);
    cout << y << endl << endl;
}

void decriptare(ZZ y, ZZ key_private, ZZ n)
{
    x = PowerMod(y, key_private, n);
    cout << "Decriptare:" << x << endl << endl;
}

void decriptareTCR(ZZ y, ZZ key_private, ZZ n)
{
    ZZ xp, xq, m1, m2, x1, x2;
    xp = PowerMod(y % p, key_private % (p - 1), p);
    xq = PowerMod(y % q, key_private % (q - 1), q);

    m1 = q;
    m2 = p;

    x1 = InvMod(m1 % p, p);
    x1 = x1 * xp % p;
    x2 = InvMod(m2 % q, q);
    x2 = x2 * xq % q;

    x = (m1 * x1 + m2 * x2) % n;

    cout << x << endl << endl;
}

void RSA(ZZ m)
{

    p = GenPrime_ZZ(512, 80);

    //p=47; q=61;
    q = GenPrime_ZZ(512, 80);
    cout << "p : " << p << endl << endl;

    cout << "q : " << q << endl << endl;

    n = p*q; //1024 biti
    cout << "n : " << n << endl << endl;

    phi = (p - 1)*(q - 1);
    cout << "phi(n) : " << phi << endl << endl;

    //key_public = RandomBnd(phi); //e

    key_public = 41;
    while (GCD(key_public, phi) != 1)
        key_public = RandomBnd(phi);

    cout << "Cheia publica:" << key_public << endl << endl;

    key_private = InvMod(key_public, phi); //d-ul
    cout << "Cheia privata:" << key_private << endl << endl;

    //key_public=(e)
    //key_private=(d)

    //CRIPTARE
    cout << "Criptare:";
    criptare(m, key_public, n);

    //DECRIPTARE
    decriptare(y, key_private, n);

    //DECRIPTARE CU TEOREMA CHINEZA A RESTURILOR - mult mai optima
    cout << "Decriptare folosind Teorema Chieza a Resturilor: ";
    decriptareTCR(y, key_private, n);

}

ZZ p_wiener, q_wiener;
bool verificareConditieWiener(ZZ k, ZZ ed, ZZ n)
{
    //ZZ p,q;
    ZZ x1, x2, a, b, c, delta, aux;
    a = 1;

    if(k == 0) return false;
    b = -(n - (ed - 1) / k + 1);
    c = n;
    cout<<a<<" "<<b<<" "<<c<<endl;
    delta = (b * b) - (4 * a * c);
    cout<<"Delta este:"<<delta<<endl;
    if (delta < 0) return false;
    else if (delta == 0) x1 = x2 = -b / (2 * a);
    else if (delta > 0)
    {
        aux = SqrRoot(delta);
        x1 = (-b - aux) / (2 * a);
        x2 = (-b + aux) / (2 * a);
    }
    cout<<x1<<" "<<x2<<" "<<x1 * x2<<endl;
    if (x1 * x2 == n)
        //(n / x1 * x1 == n) && (a * x1 * x1 + b * x1 + n == 0) && (n / x2 * x2 == n) && (a * x2 * x2 + b * x2 + n == 0)
    {
        p_wiener = x1;
        q_wiener= x2;
        return true;
    }
    else return false;
}

void WeinersAttack()
{
    cout<<" -------- Weiner's Attack -----------"<<endl;
    // se da cheia publica formata din <N,e>, se doreste gasirea lui d (d - mic; d<1/3*n^(1/4) )

    n = 160523347;
    e = 60728973;
    cout<<"n= "<<n<<" e= "<<e<<endl;

    ZZ a = n, b = e, cat, rest, descompunere_factori[1000],pc,qc;
    int i = 0;
    descompunere_factori[i] = 0;
    i++;
    do
    {
        cat = a / b;
        rest = a % b;
        descompunere_factori[i] = cat;
        i++;
        a = b;
        b = rest;

    }
    while (b != 0);
    int descompunere_factoriLength = i;
    ZZ numitor_curent, numitor_prev, numitor_prev_prev, numarator_curent, numarator_prev, numarator_prev_prev;

    cout<<"Descompunerea in factori pentru a folosi dupa fractiile continue este:"<<endl;
    for(int i = 0; i<descompunere_factoriLength ; i++)
        cout<<descompunere_factori[i]<<" ";
    cout<<endl;

    i = 0;
    do
    {
        switch (i)
        {
        case 1:
            i++;
            numitor_curent = descompunere_factori[i];
            numarator_curent = 1;
            break;
        case 2:
            numitor_prev = numitor_curent;
            numitor_curent = descompunere_factori[i] * numitor_prev + 1;
            numarator_prev = numarator_curent;
            numarator_curent = numarator_prev * descompunere_factori[i];
            i++;
            break;
        default:
            numitor_prev_prev = numitor_prev;
            numitor_prev = numitor_curent;
            numitor_curent = descompunere_factori[i] * numitor_prev + numitor_prev_prev;
            numarator_prev_prev = numarator_prev;
            numarator_prev = numarator_curent;
            numarator_curent = descompunere_factori[i] * numarator_prev + numarator_prev_prev;
            i++;
            break;
        }
        cout<<numitor_curent<<" "<<numarator_curent<<endl;
    }
    while (verificareConditieWiener(numarator_curent, e*numitor_curent, n) == false && i < descompunere_factoriLength);
    cout<<p_wiener<<" "<<q_wiener<<endl;
    ZZ fi_prime = (p_wiener - 1) * (q_wiener - 1);
    ZZ d_prime = InvMod(e%fi_prime, fi_prime);
    cout<<"D dupa Wiener este: "<<d_prime<<endl;
}

int main()
{
    m = 111;
    RSA(m);
    //WeinersAttack();
}
