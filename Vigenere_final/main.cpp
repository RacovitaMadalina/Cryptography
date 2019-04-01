/* ****************************************************************

In urmatorul program vom implementa algoritmul de criptare Vigenere 26

Autori: Racovita Madalina

Data realizarii: 20.02.2018


******************************************************************* */

#include <iostream>
#include <string.h>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<stdlib.h>
#define MAX_LENGTH 10000

using namespace std;

float frecv_engl[] =
{
	7.81, 1.28, 2.93, 4.11, 13.05, 2.88, 1.39,

	5.85, 6.77, 0.23, 0.42, 3.60, 2.62, 7.28,

	8.21, 2.15, 0.14, 6.64, 6.46, 9.02, 2.77,

	1.00, 1.49, 0.30, 1.51, 0.09
}; //frencventele literelor din limba engleza

char alpha[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //alfabetul scris in ordine lexicografica

float IC(char criptotext[MAX_LENGTH], int jump, int start) //functie pentru calculul indicelui de coincidenta
{
    float IC = 0;
    int lettersFreq[26] = {0};
    char criptotext2[MAX_LENGTH];
    int dimension = 0;

    for(int i = start; i < strlen(criptotext); i += jump)
    {
        criptotext2[dimension] = criptotext[i];
        dimension++;
    }
    criptotext2[dimension] = '\0';
    //cout<<criptotext2;
    for(int i = 0; i < strlen(criptotext2); i++)
    {
        lettersFreq[(int)criptotext2[i] - 65]++;
    }

    for(int i = 0; i < 26; i++)
    {
        IC += ((lettersFreq[i] / (float) dimension) * ((lettersFreq[i] - 1) / ((float)dimension - 1)));
        //cout<<(lettersFreq[i] / (float) dimension)<<" "<<(lettersFreq[i] - 1) / ((float)dimension - 1)<<endl;
    }
    return IC;
}

float MutualIC(float freq1[26], float freq2[26], int k1, int k2) //calculez indicele de coincidenta mutuala
{
	float MIC = 0;
	for (int i = 0; i < 26; i++)
		MIC = MIC + ((float)freq1[i] / k1)*((float)freq2[i] / k2);
	return MIC;
}

char modifiedText[MAX_LENGTH];

/* functie ce imi returneaza sirul obinut prin inlocuirea fiecarui simbol din sir
cu simbolul aflat cu s pozitii mai la dreapta in alfabet*/

void SHIFT(char text[MAX_LENGTH], int s)
{
	for (int j = 0; j < strlen(modifiedText - 1); j++)
		modifiedText[j] = '\0';

	for (int i = 0; i < strlen(text); i++)
			modifiedText[i] = alpha[(text[i] - 'A' + s)%26]; //sirul nou primeste litera de peste s pozitii din alfabet
}

int main()
{
    // ********** FILTRAREA**************** //

    char x[MAX_LENGTH]; // x = plaintext-ul pe care urmeaza sa il modificam
    char key[MAX_LENGTH]; // cheia de criptare

    cout<<"Dati plaintext-ul: ";
    gets(x);
    cout<<"Da-ti cheia: ";
    gets(key);
    int length;
    length = strlen(x);

    for(int i=0; i<length; i++)
    {
        length = strlen(x);
        if((x[i] >= 'a') && (x[i] <= 'z'))
            x[i] = x[i] - 32;
        else if((x[i] >= 'A') && (x[i] <= 'Z'))
            continue;
        else
        {
            for (int j = i; j < length - 1; j++)
                x[j] = x[j + 1];

            length--;
            i--;
            x[length]='\0';
        }
    }
    cout<<"Plaintext-ul dupa modificari(transformare majuscule, eliminare caractere necorespunzatoare) va fi: "<<x<<endl;

    int keyLength;
    keyLength = strlen(key);

    for(int i=0; i<keyLength; i++)
    {
        keyLength = strlen(key);
        if((key[i] >= 'a') && (key[i] <= 'z'))
            key[i] = key[i] - 32;
        else if((key[i] >= 'A') && (key[i] <= 'Z'))
            continue;
        else
        {
            for (int j = i; j < keyLength - 1; j++)
                key[j] = key[j + 1];

            keyLength--;
            i--;
            key[keyLength]='\0';
        }
    }

    cout<<"Cheia dupa modificari(transformare majuscule, eliminare caractere necorespunzatoare) va fi: "<<key<<endl;

    // ********** CRIPTAREA **************** //
    char auxilary[MAX_LENGTH];
    for(int i = 0; i < length; i++)
    {
        auxilary[i] = key[i % keyLength];
    }

    auxilary[length] = '\0'; // in auxilary avem sirul KEYKEYKEY...
    keyLength = strlen(key);
    length = strlen(x);
    //cout<<auxilary<<endl;

    char encryptedText[MAX_LENGTH];
    int indexAlphaKey[MAX_LENGTH];

    for(int i = 0; i < length; i++)
    {
        int j; //variabila ce memoreaza indexul din alfabet a lui x[i]
        for(j = 0; j < 26; j++)
            if(x[i] == alpha[j])
                break;
        encryptedText[i] = alpha[(j + (int)auxilary[i] - 65) % 26];
    }

    cout<<"Textul criptat prin Vigenere cipher va fi: "<<encryptedText<<endl;

    // ********** CRIPTANALIZA **************** //

    int freq[26]={0}; //vector ce memoreaza frecventele literelor din criptotext

    //vedem frecventele literelor in criptotext
    for(int i = 0; i < length; i++)
        for(int j = 0; j <= 25; j++)
            if(alpha[j] == encryptedText[i])
                freq[j]++;

    // ------------------------- AFLAREA LUNGIMII CHEII ------------------------- //

    float IC_proper = 0;
    int keyLength_found;
    float difference_min = 0;
    float IC_average;

    for(int i = 1; i <= 10; i++) //presupunem ca lungimea maxima a cheii este 15
    {
        float sum = 0;
        int nrSubstrings;
        for(int j = 0; j < i; j++)
            sum += IC(encryptedText, i, j);
        IC_average = sum / i;
        if(IC_proper == 0)
        {
            IC_proper = IC_average;
            keyLength_found = i;
            difference_min = abs(0.065 - IC_proper);
        }
        else if(abs(0.065 - IC_average)<difference_min)
        {
            IC_proper = IC_average;
            keyLength_found = i;
            difference_min = abs(0.065 - IC_proper);
        }
        cout<<"IC_average for a key with the length "<<i<<" will be "<<IC_average<<endl;
    }
    cout<<"IC proper:"<<IC_proper<<endl;
    cout<<"The length of the key="<<keyLength_found<<endl;

	// ------------------------- AFLAREA CHEII ------------------------- //

    int s;
	float MIC;
	keyLength_found = strlen(key);
	float freq_mTOm[26] = {0};
	int length_mTOm = 0;
	string key_found;


	for (int i = 0; i < keyLength_found; i++)
	{
		length_mTOm = 0;
		for (int j = 0; j <= 'Z' - 'A'; j++)
			freq_mTOm[j] = 0;
		for (int j = i; j < strlen(encryptedText); j += keyLength_found)//FAC vector de frecvente pt fiecare sir pe care in iau din m in m unde m=keyLength_found
		{
			freq_mTOm[encryptedText[j] - 65]++;
			length_mTOm++;
		}
        s = -1;
        double MIC= 0;
		do {
			s++;
			MIC = 0;

			for (int j = 0; j < 26; j++)//parcurg tabelul de frecevta din engleza
			{
				MIC = MIC + (double)(frecv_engl[j]/100)*(double)(freq_mTOm[(j + s) % 26] / length_mTOm); //freq_mTOm[(j + s) % 26] il folosesc pt  a identifica fiecare litera

			}
		} while (!(MIC>0.050 && MIC <0.073));
		key_found += 65 + s;//fac cheie2+65 ca sa o transform in litera efeciv, pt ca am retinut ascii mai sus
	}
	cout <<key_found<<endl;

    // ********** DECRIPTAREA **************** //

    char decryptedMsg[MAX_LENGTH];
    int i;
    for(i = 0; i < strlen(encryptedText); ++i)
        decryptedMsg[i] = (((encryptedText[i] - auxilary[i]) + 26) % 26) + 'A';

    decryptedMsg[i] = '\0';
    cout<<decryptedMsg;
    return 0;
}
