#include <iostream>
#include <bitset>
#include <fstream>
#include <math.h>

using namespace std;
ofstream g("generated_keys.txt");
ofstream gg("matrice_criptari.txt");
ofstream ggg("matrice_decriptari.txt");
bitset<48> final_keys[17];

//initial permutation
int IP[]= {58, 50, 42, 34, 26, 18, 10, 2,
           60, 52, 44, 36, 28, 20, 12, 4,
           62, 54, 46, 38, 30, 22, 14, 6,
           64, 56, 48, 40, 32, 24, 16, 8,
           57, 49, 41, 33, 25, 17, 9, 1,
           59, 51, 43, 35, 27, 19, 11, 3,
           61, 53, 45, 37, 29, 21, 13, 5,
           63, 55, 47, 39, 31, 23, 15, 7
          };

//initial permutation^(-1)
int IP_1[]= {40, 8, 48, 16, 56, 24, 64, 32,
             39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30,
             37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28,
             35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26,
             33, 1, 41,  9, 49, 17, 57, 25
            };

//expansion
int E[]= {32, 1, 2, 3, 4, 5,
          4, 5, 6, 7, 8, 9,
          8, 9, 10, 11, 12, 13,
          12, 13, 14, 15, 16, 17,
          16, 17, 18, 19, 20, 21,
          20, 21, 22, 23, 24, 25,
          24, 25, 26, 27, 28, 29,
          28, 29, 30, 31, 32, 1
         };

//S boxes
int S1[]= {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
           0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
           4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
           15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
          };

int S2[]= {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
           3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
           0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
           13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
          };

int S3[]= {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
           13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
           13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
           1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
          };

int S4[]= {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
           13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
           10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
           3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
          };

int S5[]= {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
           14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
           4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
           11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
          };

int S6[]= {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
           10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
           9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
           4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
          };

int S7[]= {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
           13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
           1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
           6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
          };

int S8[]= {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
           1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
           7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
           2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
          };

//permutation
int P[]= {16, 7, 20, 21,
          29, 12, 28, 17,
          1, 15, 23, 26,
          5, 18, 31, 10,
          2, 8, 24, 14,
          32, 27, 3, 9,
          19, 13, 30, 6,
          22, 11, 4, 25
         };

//permutation choice 1
int PC1[]= {57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4
           };

//permutation choice 2
int PC2[]= {14, 17, 11, 24, 1, 5,
            3, 28, 15, 6, 21, 10,
            23, 19, 12, 4, 26, 8,
            16, 7, 27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32
           };

bitset<28> circular_left_shift_one(bitset<28> sirul_de_biti)  //shiftare circulara cu o pozitie
{
    bitset<28> temporal=sirul_de_biti;
    for (int i=0; i<27; i++)
    {
        sirul_de_biti[i+1]=temporal[i];
    }
    sirul_de_biti[0]=temporal[27];
    return sirul_de_biti;
}

bitset<28> circular_left_shift_two(bitset<28> sirul_de_biti) //shiftare circulara cu 2 pozitii
{
    bitset<28> temporal=sirul_de_biti;
    for (int i=0; i<26; i++)
    {
        sirul_de_biti[i+2]=temporal[i];
    }
    sirul_de_biti[1]=temporal[27];
    sirul_de_biti[0]=temporal[26];
    return sirul_de_biti;
}


int S_box_value(int line,int column,int nr_cutie)
{
    if ((nr_cutie+1)==1)
        return (S1[line*16+column]);
    if ((nr_cutie+1)==2)
        return (S2[line*16+column]);
    if ((nr_cutie+1)==3)
        return (S3[line*16+column]);
    if ((nr_cutie+1)==4)
        return (S4[line*16+column]);
    if ((nr_cutie+1)==5)
        return (S5[line*16+column]);
    if ((nr_cutie+1)==6)
        return (S6[line*16+column]);
    if ((nr_cutie+1)==7)
        return (S7[line*16+column]);
    if ((nr_cutie+1)==8)
        return (S8[line*16+column]);
}

bitset<32> functia_feistel(bitset<32> R,int runda_de_cheie,bitset<48> final_keys[]) //f(R_i-1,K_i)
{
    bitset<48> R_expanded;
    for (int i=0; i<48; i++) //Aplicam sirului de 32 biti R functia_feistel de extensie din tabelul E
    {
        R_expanded[47-i]=R[31-(E[i]-1)];
    }
    //cout<<"R_expanded la runda"<<runda_de_cheie<<" "<<R_expanded<<endl;

    R_expanded = R_expanded ^ final_keys[runda_de_cheie];//R extins XOR cheia rundei curente

    //cout<<"E(R) XOR cheie_runda"<<" "<<R_expanded<<endl;
    bitset<6> before_S_boxes[8];
    bitset<4> after_S_boxes[8];

    for (int i=0; i<48; i++) //Reprezentam stringul de la operatia de mai sus ca concatenare a 8 siruri a cate 6 biti
        before_S_boxes[7-i/6][5-i%6]=R_expanded[47-i];

    for (int i=0; i<8; i++) //8 siruri cate 6 biti -> 8 siruri cate 4 biti cu valori din S-boxes
    {
        bitset<2> linia;
        linia[0]=before_S_boxes[7-i][0];
        linia[1]=before_S_boxes[7-i][5];
        bitset<4> coloana;
        coloana[0]=before_S_boxes[7-i][1];
        coloana[1]=before_S_boxes[7-i][2];
        coloana[2]=before_S_boxes[7-i][3];
        coloana[3]=before_S_boxes[7-i][4];
        int line = linia[0]+linia[1]*2;
        int column = coloana[0]+coloana[1]*2+coloana[2]*4+coloana[3]*8;
        int valoare_din_box;
        valoare_din_box=S_box_value(line,column,i);
        after_S_boxes[7-i]=bitset<4>(valoare_din_box);
    }

    bitset<32> before_P;
    for (int i=0; i<32; i++)
    {
        before_P[31-i]=after_S_boxes[7-i/4][3-i%4];
    }

    bitset<32> to_be_returned;

    for (int i=0; i<32; i++) //Aplicam permutarile finale din tabelul P si primim f(R_i-1,K_i)
    {
        to_be_returned[31-i]=before_P[31-(P[i]-1)];
    }
    //cout<<"f(R_i-1, K_i) este "<<to_be_returned<<endl;
    return to_be_returned;
}

bitset<32> R_i_formare(bitset<32> R_precedent,bitset<32> L_precedent,int runda,bitset<48> final_keys[]) //L_i-1 XOR f(R_i-1,K_i)
{
    return (L_precedent^functia_feistel(R_precedent,runda,final_keys));
}

bitset<64> criptare_decriptare(bitset<64> sirul_biti,bool criptare,bitset<48> final_keys[])
{
    bitset<64>text_dupa_IP;
    for (int i=0; i<64; i++)
    {
        text_dupa_IP[i]=sirul_biti[IP[i]-1];
    }
    bitset<32> L;
    bitset<32> R;

    //Impartim textul in L si R
    for (int i=0; i<32; i++)
    {
        R[i]=text_dupa_IP[i];
        L[i]=text_dupa_IP[i+32];
    }
    //Incep rundele de criptare
    if(criptare==1)
        for (int i=1; i<=16; i++)
        {
            bitset<32> L_temporar=L;
            L=R;
            R=R_i_formare(R,L_temporar,i,final_keys);
        }
    else
        for (int i=16; i>=1; i--)
        {
            bitset<32> L_temporar=L;
            L=R;
            R=R_i_formare(R,L_temporar,i,final_keys);
        }

    bitset<64> criptotext_temporal;
    for (int i=0; i<32; i++) //formam criptotext pentru IP^(-1) din doua jumatati criptate in 16 runde
    {
        criptotext_temporal[i]=L[i];
        criptotext_temporal[i+32]=R[i];
    }

    bitset<64>criptotext;
    for (int i=0; i<64; i++) //Aplicam tabelul de permutari, inversul tabelei IP
    {
        criptotext[63-i]=criptotext_temporal[63-(IP_1[i]-1)];
    }

    return criptotext;
}
//string text_initial;
//intput initial
bitset<64> text(0x4E6F772069732074);
bitset<64> key(0x0123456789ABCDEF);
//bitset<64> key(0x000000000000001);
bitset<64> auxilary(0x3FA40E8A984D4815); //rezultat corect DES input initial

//bitset<64> text(0x15D002D1722208C7);//textul criptat cu cheia de mai jos
//bitset<64> text(0x61BC764754615154);
//bitset<64> key(0x0123456789ABCD00);
//bitset<64> key(0x0123456789ABCD01);


void DES(bitset<64> key)
{
    //------------------------------------------------------generarea cheilor---------------------------------------------------------------
    //Aplicam cheii permutari din PC1 eliminad astfel si bitii de paritate
    bitset<56>key_after_PC1;
    for (int i=0; i<56; i++)
    {
        key_after_PC1[55-i]=key[63-(PC1[i]-1)];
    }

    //Impartim cheia in C_0 si D_0
    bitset<28> C_0,D_0;
    for (int i=0; i<28; i++)
    {
        C_0[i]=key_after_PC1[i];
        D_0[i]=key_after_PC1[i+28];
    }

    //Generam cheile pentru 16 runde de criptare
    for (int i=1; i<17; i++)
    {
        bitset<28> C,D;
        bitset<56> temporary_key;
        if (i==1 || i==2 || i==9 || i==16) //pentru i=1,2,9,16 siftam bitii din C si D cu o pozitie
        {
            C=circular_left_shift_one(C_0);
            D=circular_left_shift_one(D_0);
            C_0=C;
            D_0=D;
            for (int j=0; j<28; j++)
            {
                temporary_key[j]=C[j];
                temporary_key[j+28]=D[j];
            }
            for (int j=0; j<48; j++) //Aplicam permutarile din tabelul PC2 si plasam cheia in tabelul final de chei
            {
                final_keys[i][47-j]=temporary_key[55-(PC2[j]-1)];
            }
        }
        else //pentru toti ceilalti i siftam bitii din C si D cu doua pozitii
        {
            C=circular_left_shift_two(C_0);
            D=circular_left_shift_two(D_0);
            C_0=C;
            D_0=D;
            for (int j=0; j<28; j++) //concatenam partea stanga cu partea dreapta
            {
                temporary_key[j]=C[j];
                temporary_key[j+28]=D[j];
            }
            for (int j=0; j<48; j++) //Aplicam permutarile din tabelul PC2 si plasam cheia in tabelul final de chei
            {
                final_keys[i][47-j]=temporary_key[55-(PC2[j]-1)];
            }
        }
    }
    //for(int i=1; i<17; i++)
        //cout<<"RUNDA"<<i<<" "<<final_keys[i]<<endl;
    //cout<<endl<<endl;
}

int main()
{

    cout<<"Textul initial in binar este : "<<text<<endl;
    cout<<"Cheia este: "<<key<<endl;

    DES(key);

    /* ************CRIPTAREA************ */

    //pasul cu aplicarea tabelului de permutari IP pentru sirul de text de 64 de biti
    bitset<64>criptotext=criptare_decriptare(text,1,final_keys);
    cout<<endl<<endl;
    cout<<"Criptotextul este : "<<criptotext<<endl;
    /*key=0x000000000000001;
    bitset<64>criptotext2=criptare_decriptare(criptotext,1,final_keys);
    cout<<endl<<endl;
    cout<<"Criptotextul este : "<<criptotext2<<endl;*/
    /*for(int i=63; i>=0;i--)
    {
        cout<<criptotext[i];
        if(i%4==0)
            cout<<endl;
    }*/
    cout<<"Verificare:::       "<<auxilary<<endl;
    cout<<endl<<endl;


    /* ************DECRIPTAREA************ */

    //pasul cu aplicarea tabelului de permutari IP pentru sirul de criptotext de 64 de biti
    bitset<64>text_decriptat=criptare_decriptare(criptotext,0,final_keys);

    cout<<"Textul decriptat in binar este : "<<text_decriptat<<endl;

    /* --------------------MEET-IN-THE-MIDDLE-ATTACK------------------ */

    bitset<56> MITM_key(0x0000000000000);
    cout<<"cheia penttu meet in the middle de 56 de biti este:"<<MITM_key<<endl;
    int number;
    bitset<64> array_keys[256];

    for (int i = 0; i<256; i++)
	{
		number = i;
		g<<"Cheia cu numarul "<<number<<endl;

		int poz = 0;
		bitset<8> byte_generated(0x00);//byte-ul pe care trebuie sa il gasim cu MITM attack va fi scrierea binara a numarului cheii
		while (number != 0)
		{
			byte_generated[poz] = number % 2;
			poz++;
			number = number / 2;
		}

		bitset<64> key_generated;

		for (int j = 0; j<8; j++){
			key_generated[j] = byte_generated[j];
		}
		int k=0;
        for (int j = 8; j<64; j++){
             key_generated[j] = MITM_key[k];
             k++;
        }

		array_keys[i] = key_generated;
		g<<array_keys[i]<<endl;
	}

	bitset<64> temporary_key, temporary_key1;
	bitset<64> array_ciphertexts[256];
	bitset<64> array_decryptedtexts[256];
    /*for (int i = 0; i<256; i++)
	{
        temporary_key = array_keys[i];
		DES(temporary_key); //generam 16 chei pentru runde
        array_ciphertexts[i] = criptare_decriptare(0100111001101111011101110010000001101001011100110010000001110100,1,final_keys);
        gg<<"Criptotextul criptat cu cheia "<<i<<endl<<array_ciphertexts[i]<<endl;
        array_decryptedtexts[i] = criptare_decriptare(0100111001101111011101110010000001101001011100110010000001110100,0,final_keys);
	}*/

    bool flag = 0;
	for (int i = 0; i<256 && flag == 0 ; i++)
	{
	    temporary_key = array_keys[i];
		DES(temporary_key); //generam 16 chei pentru runde
        array_ciphertexts[i] = criptare_decriptare(0100111001101111011101110010000001101001011100110010000001110100,1,final_keys);
		for (int j = 0; j<256 && flag==0; j++)
		{
		    temporary_key1 = array_keys[j];
		    DES(temporary_key1);
			if(array_ciphertexts[i]==criptare_decriptare(0100111001101111011101110010000001101001011100110010000001110100,0,final_keys)){
                flag = 1;
				cout<<"Am gasit cheile pentru meet in the middle!" << endl;
                cout<<"Prima cheie este: "<<array_keys[i]<<endl;  //prima cheie de criptare
                cout<<"A doua cheie este: "<<array_keys[j]<<endl;  //a doua cheie de criptare
				cout<<endl<<endl;
                cout<<"Criptotextul este: "<<array_ciphertexts[i]<<endl;
                cout<<"Textul decriptat este:"<<criptare_decriptare(0100111001101111011101110010000001101001011100110010000001110100,0,final_keys)<<endl;
			}
		}
	}
    return 0;
}
