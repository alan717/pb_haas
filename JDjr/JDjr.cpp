// JDjr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "defs.h"
int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file




int __fastcall sub_54CC(_BYTE* a1, unsigned int a2, unsigned int* a3, unsigned __int8* a4, unsigned int a5)
{
    unsigned int v5; // r2
    unsigned int v6; // r11
    unsigned int v7; // r2
    _BYTE* v8; // r2
    unsigned __int8* v9; // r4
    unsigned int v10; // r1
    int v11; // r12
    int v12; // r7
    int v13; // r6
    char* v14; // r9
    char v15; // r8
    _BYTE* v16; // r1
    int result; // r0
    int v18; // r3
    int v19; // r6
    int v20; // r5
    _BYTE* v21; // r3
    char v22; // r1
    char v23; // r4
    int v24; // r1
    int v25; // r7
    int v26; // r6
    int v27; // r5
    char v28; // r4

    if (a5)
    {
        v5 = a5 / 3;
        v6 = 3 * (a5 / 3);
        if (a5 != v6)
            ++v5;
        if (v5 >= 0x40000000)
        {
            result = -42;
            *a3 = -1;
        }
        else
        {
            v7 = 4 * v5 + 1;
            if (v7 <= a2 && a1)
            {
                if (v6)
                {
                    v8 = a1;
                    v9 = a4;
                    v10 = 0;
                    do
                    {
                        v11 = v9[1];
                        v9 += 3;
                        v12 = a4[v10];
                        v10 += 3;
                        v8 += 4;
                        v13 = *(v9 - 1);
                        v14 = &aAbcdefghijklmn[16 * (v12 & 3)];
                        LOBYTE(v12) = aAbcdefghijklmn[v12 >> 2];
                        v15 = aAbcdefghijklmn[4 * (v11 & 0xF) + (v13 >> 6)];
                        LOBYTE(v11) = v14[v11 >> 4];
                        LOBYTE(v13) = aAbcdefghijklmn[v13 & 0x3F];
                        *(v8 - 2) = v15;
                        *(v8 - 3) = v11;
                        *(v8 - 4) = v12;
                        *(v8 - 1) = v13;
                    }           while (v6 > v10);
                }
                else
                {
                    v9 = a4;
                    v10 = 0;
                    v8 = a1;
                }
                if (a5 > v10)
                {
                    v18 = *v9;
                    if (a5 > v10 + 1)
                    {
                        v24 = v9[1];
                        v25 = v18 & 3;
                        v26 = v18 >> 2;
                        v21 = v8 + 3;
                        v27 = v24 >> 4;
                        v22 = aAbcdefghijklmn[4 * (v24 & 0xF)];
                        v28 = aAbcdefghijklmn[v26];
                        v8[1] = aAbcdefghijklmn[16 * v25 + v27];
                        *v8 = v28;
                    }
                    else
                    {
                        v19 = v18 & 3;
                        v20 = v18 >> 2;
                        v21 = v8 + 3;
                        v22 = 61;
                        v23 = aAbcdefghijklmn[16 * v19];
                        *v8 = aAbcdefghijklmn[v20];
                        v8[1] = v23;
                    }
                    v8[2] = v22;
                    v8 = v21 + 1;
                    *v21 = 61;
                }
                v16 = (v8 - a1);
                result = 0;
                *a3 = v16;
                *v8 = 0;
            }
            else
            {
                result = -42;
                *a3 = v7;
            }
        }
    }
    else
    {
        result = 0;
        *a3 = 0;
    }
    return result;
}
