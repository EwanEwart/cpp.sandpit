#if false

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>
#include <limits>
#include <type_traits>
#include <algorithm>
using namespace std;

double stringToDouble(wchar_t* input, wchar_t* unitP = nullptr)
{
    double out = 0;
    wchar_t unit[10] = { 0 };

    int response = swscanf_s(input, L"%lf%s", &out, unit, 5);

    return out;
}

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
        // unless the result is subnormal
        || std::fabs(x - y) < std::numeric_limits<T>::min();
}

/* The precision decides about what is equality */
bool isEqual(long double d1, long double d2, long double epsilon = 0.01)
{
    long double delta{ std::fabs(d1 - d2) };
    bool rtn{ (delta <= epsilon) ? true : false };
    return rtn;
}
void printEqual(long double d1, long double d2, long double epsilon = 1E-2)
{
    std::clog << "isEqual(" << d1 << ", " << d2 << ", " << epsilon << ") " << " == "
        << std::boolalpha << isEqual(d1, d2, epsilon) << std::endl;

}

struct S7 {
    // three-bit unsigned field,
    // allowed values are 0...7
    unsigned int b : 3;
};

int main()
{
    // Converting the content of a char array or a string to a double variable
    double aDouble;
    wstring aString;
    aString = L"4.5";
    wistringstream(aString) >> aDouble;
    wcout << "\nThe value of the double variable aDouble is " << aDouble << endl;
    wistringstream(L"9.87654") >> aDouble;
    wcout << "\nNow the value of the double variable aDouble is " << aDouble << endl;



    // Converting a double to string with formatting restrictions
    //
    double D = 3.771234567;

    wostringstream Q;
    Q.fill('#');
    Q << "<<<" << setprecision(6) << setw(20) << D << ">>>";
    aString = Q.str(); // formatted converted double is now in string 

    wcout << L"\nThe value of the string variable aString is " << aString << endl;

    wchar_t  tokenstring[] = L"15 12 14...";
    wchar_t  s[81];
    wchar_t  c;
    int   i;
    float fp;

    // Input various data from tokenstring:
    // max 80 character string:
    swscanf(tokenstring, L"%80s", s); // C4996
    swscanf(tokenstring, L"%c", &c);  // C4996
    swscanf(tokenstring, L"%d", &i);  // C4996
    swscanf(tokenstring, L"%f", &fp); // C4996
    // Note: sscanf is deprecated; consider using sscanf_s instead

    // Output the data read; see 16-30 Api old
    (void)printf("String    = %ls\n", s);
    (void)printf("Character = %c\n", c);
    (void)printf("Integer:  = %ld\n", i);
    (void)printf("Real:     = %lf\n", fp);

    double d1{ stringToDouble(L"3.1415l") };
    wcout << L"\nstringToDouble(L\"3.1415l\") == " << d1 << endl;
    d1 *= 2;
    wcout << L"2 * d1 * 2 == " << d1 << L"\n" << endl;

    // epsilon
    //
    double n1{ 0.0 };
    // double n2{ 1 / std::sqrt(5) / std::sqrt(5) };
    double n2{ 0.00000001 };
    double ulp{ 0.0001 };
    std::clog << "n1 == " << n1 << " ? " << std::boolalpha << (n1 == 0.0) << std::endl;
    std::clog << "n2 == " << n2 << " ? " << std::boolalpha << (n2 == 0.0) << std::endl;
    std::clog << "almost_equal(" << n1 << ", " << n2 << ", " << ulp << ") " << " == " << std::boolalpha << almost_equal(n1, n2, ulp) << std::endl;

    printEqual(0.0, 0.000001, 1E-1);
    printEqual(0.0, 0.000001, 1E-2);
    printEqual(0.0, 0.000001, 1E-3);
    printEqual(0.0, 0.000001, 1E-4);
    printEqual(0.0, 0.000001, 1E-5);
    printEqual(0.0, 0.000001, 1E-6);
    printEqual(0.0, 0.000001, 1E-7);
    printEqual(0.0, 0.000001, 1E-8);
    printEqual(0.0, 0.000001, 1E-9);

    // bit fields
    S7 s{ 5 };
    // std::clog << "S s {7}; -> " << s.b3 << std::endl; 

    return 0;
}

#endif

#if false
// The number of bits in a bit field (width) sets the limit to the range of values it can hold:
#include <stdio.h>
struct S {
    // three-bit unsigned field,
    // allowed values are 0...7
    unsigned int b : 3;
};
int main(void)
{
    struct S s = { 5 };
    ++s.b;
    ++s.b;
    ++s.b; // unsigned overflow
    (void)printf("%d\n", ++s.b); // output: 0
}
#endif

#if false
// Multiple adjacent bit fields are permitted to be (and usually are) packed together:
#include <stdio.h>
struct S
{
    // will usually occupy 4 bytes:
    // 5 bits: value of b1
    // 11 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    // 8 bits: unused
    unsigned b1 : 5, : 11, b2 : 6, b3 : 2;
};
int main(void)
{
    (void)printf("%zu bytes\n", sizeof(struct S)); // usually prints 4
}

#endif

#if false

#include <bitset>
#include <cassert>
#include <iostream>

int main()
{
    // constructors:
    constexpr std::bitset<4> b1;          // 0000
    constexpr std::bitset<4> b2{ 0xA };  // == 0B1010
    std::bitset<4> b3{ "0011" };        // can't be constexpr yet; 0011
    std::bitset<8> b4{ "ABBA",         /*length*/4, /*0:*/'A', /*1:*/'B' }; // == 0B0000'0110
    /* https://en.cppreference.com/w/cpp/utility/bitset/bitset ctor (4) */

    // bitsets can be printed out to a stream:
    std::cout << "b1:" << b1 << "; b2:" << b2 << "; b3:" << b3 << "; b4:" << b4 << '\n';

    assert(b1 == 0b0000);
    assert(b2 == 0b1010);
    assert(b3 == 0b0011);
    assert(b4 == 0b0110);

    // bitset supports bitwise operations:
    b3 |= 0b0100; assert(b3 == 0b0111);
    b3 &= 0b0011; assert(b3 == 0b0011);
    b3 ^= std::bitset<4>{0b1100}; assert(b3 == 0b1111);

    // operations on the whole set:
    b3.reset(); assert(b3 == 0);
    b3.set(); assert(b3 == 0b1111);
    assert(b3.all() && b3.any() && !b3.none());
    b3.flip(); assert(b3 == 0);

    // operations on individual bits:
    b3.set(/* position = */ 1, true); assert(b3 == 0b0010);
    b3.set(/* position = */ 1, false); assert(b3 == 0);
    b3.flip(/* position = */ 2); assert(b3 == 0b0100);
    b3.reset(/* position = */ 2); assert(b3 == 0);

    // subscript operator[] is supported:
    b3[2] = true; assert(true == b3[2]);

    // other operations:
    assert(b3.count() == 1);
    assert(b3.size() == 4);
    assert(b3.to_ullong() == 0b0100ULL);
    assert(b3.to_string() == "0100");
}

#endif

#if false

#include <bitset>
#include <string>
#include <iostream>
#include <climits>
#include <cassert>

/* bitset ctors */

int main()
{
    // empty constructor
    std::bitset<8> b1; // [0,0,0,0,0,0,0,0]

    assert(b1 == 0b00000000);

    // unsigned long long constructor
    std::bitset<8> b2(42);          // [0,0,1,0,1,0,1,0]
    std::bitset<70> bl(ULLONG_MAX); // [0,0,0,0,0,0,1,1,1,...,1,1,1] in C++11
    std::bitset<8> bs(0xfff0);      // [1,1,1,1,0,0,0,0]

    assert(b2 == 0b00101010);
    assert(bl == 0xffffffffffffffffui64);
    assert(bs == 0b1111111111110000);

    // string constructor
    std::string bit_string = "110010";
    std::bitset<8> b3(bit_string);       // [0,0,1,1,0,0,1,0]
    std::bitset<8> b4(bit_string, 2);    // [0,0,0,0,0,0,1,0]
    std::bitset<8> b5(bit_string, 2, 3); // [0,0,0,0,0,0,0,1]

    assert(b3 == 0b110010);
    assert(b4 == 0b000010);
    assert(b5 == 0b00000001);

    // string constructor using custom zero/one digits
    std::string alpha_bit_string = "aBaaBBaB";
    std::bitset<8> b6(alpha_bit_string, 0, alpha_bit_string.size(), 'a', 'B'); // [0,1,0,0,1,1,0,1]

    assert(b6 == 0b01001101);

    // char* constructor using custom digits
    std::bitset<8> b7("XXXXYYYY", 8, 'X', 'Y'); // [0,0,0,0,1,1,1,1]

    assert(b7 == 0b00001111);

    std::cout << "b1: " << b1 << "\nb2: " << b2 << "\nbl: " << bl
        << "\nbs: " << bs << "\nb3: " << b3 << "\nb4: " << b4
        << "\nb5: " << b5 << "\nb6: " << b6 << "\nb7: " << b7 << '\n';
}

#endif

#if true

#include <boost/core/demangle.hpp>
#include <typeinfo>
#include <cstdio>
#include <string>
#include <locale.h>
#include "ParserGH263.h"

int main(int argc, char const* argv[])
{
    
    setlocale(LC_CTYPE, "German.1252");
    setlocale(LC_NUMERIC, "en_US.1252");
    // setlocale(LC_ALL, "de_DE.UTF8"); // ... fourth commit

    auto upParserGH263 {std::make_unique<ParserGH263>("E:/dev/cpp.sandpit/Muster_024A-027A.SLC")};

    // char const* const path{ "E:/dev/cpp.sandpit/Muster_024A-027A.SLC" };

    // auto fp{ std::fopen(upParserGH263->GetPath(), "r") };
    // if (!fp)
    // {
    //     std::fprintf(stderr, "%s : %d : File opening failed.\n", __FILE__, __LINE__);
    //     return -1;
    // }

#if true
    // dynamic DSKs <-- .slc
    // dynamic DSKs <-- .slc
    // dynamic DSKs <-- .slc
    // std::rewind(upParserGH263->getFP());
    // char lineBuf[1024];
    // std::queue<std::pair<std::string, std::shared_ptr<Base>>> queueDSKs;


//     for (; std::fgets(lineBuf, sizeof lineBuf, upParserGH263->getFP()) != nullptr;)
//     {
//         char aDSK[5]{};

//         int n{ sscanf(lineBuf, "%4s\n", aDSK) };

//         if (std::strcmp("INFO", aDSK) == 0 && g_dictDSKs["INFO"])
//         {
//             // struct INFO buf {};
//             auto buf{ std::make_shared<INFO>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFO", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 /*   */ lineBuf
//                 /*   */, buf->fmtDS
//                 /* 1 */, buf->DSK
//                 /* 2 */, buf->KZProgram
//                 /* 3 */, buf->LetzeAenderung
//                 /* 4 */, &buf->BerechnungsModus
//             );
//             assert(n == 4);
//         }
//         else if (std::strcmp("BEAR", aDSK) == 0 && g_dictDSKs["BEAR"])
//         {
//             // struct BEAR buf { };
//             auto buf{ std::make_shared<BEAR>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("BEAR", std::static_pointer_cast<Base>(buf)));

//             printf("\ntype : %s\n\n", boost::core::demangle(typeid(buf).name()).c_str());

//             auto n = sscanf
//             (
//                 /*    */ lineBuf
//                 /*   */, buf->fmtDS
//                 /* 1 */, buf->DSK
//                 /* 2 */, buf->Bearbeiter
//             );
//             assert(n == 2);
//         }
//         else if (std::strcmp("KOMM", aDSK) == 0 && g_dictDSKs["KOMM"])
//         {
//             // struct KOMM buf { };
//             auto buf{ std::make_shared<KOMM>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("KOMM", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 /*    */ lineBuf
//                 /*   */, buf->fmtDS
//                 /* 1 */, buf->DSK
//                 /* 2 */, buf->Kommentartext
//             );
//             assert(n == 2);
//         }
//         else if (std::strcmp("PAR1", aDSK) == 0 && g_dictDSKs["PAR1"])
//         {
//             // struct PAR1 buf { };
//             auto buf{ std::make_shared<PAR1>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("PAR1", std::static_pointer_cast<Base>(buf)));
//             auto n = sscanf
//             (
//                 /*      */ lineBuf
//                 /*     */, buf->fmtDS
//                 /*   1 */, buf->DSK
//                 /*   2 */, buf->SpezEigGewichtChar
//                 /*   3 */, buf->UmrechnungsfaktorChar
//                 /*   4 */, buf->ReckwertChar
//                 /*   5 */, buf->BerechnungEI
//                 /*   6 */, buf->Berechnungsvorschrift
//                 /*   7 */, buf->BerechnungEM
//                 /*   8 */, buf->Seilkriechen
//                 /*   9 */, buf->Seilausschwingwinkel
//                 /*  10 */, buf->Ausgangsspannung
//                 /*  11 */, buf->Reduzierung
//                 /*  12 */, buf->Hoehenausgaben
//                 /*  13 */, buf->Trassierungsrichtlinie
//                 /*  14 */, buf->Windgesetz
//                 /*  15 */, buf->Phasenabstaende
//                 /*  16 */, buf->Sprache
//                 /*  17 */, buf->Mittelzugspannung
//                 /*  18 */, buf->LogDateiYN
//             );
//             assert(n == 18);

//             n = sscanf(buf->SpezEigGewichtChar, "%f", &buf->SpezEigGewichtFloat); assert(n == 1);
//             n = sscanf(buf->UmrechnungsfaktorChar, "%f", &buf->UmrechnungsfaktorFloat); assert(n == 1);
//             n = sscanf(buf->ReckwertChar, "%f", &buf->ReckwertFloat);
//             if (n != 1)
//             {
//                 buf->ReckwertFloat = 0.0f;
//             }
//         }
//         else if (std::strcmp("ZSTD", aDSK) == 0 && g_dictDSKs["ZSTD"])
//         {
//             // struct ZSTD buf { };
//             auto buf{ std::make_shared<ZSTD>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("ZSTD", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , /*     */buf->fmtDS
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->ZustandsindexChar
//                 , /*  3 */ buf->TemperaturCChar
//                 , /*  4 */ buf->Konstante
//                 , /*  5 */ buf->Zustandsbezeichnung
//                 , /*  6 */ buf->KennungAusgangszustand
//                 , /*  7 */ buf->KennungGrenzlast
//                 , /*  8 */ buf->KennungUngleicheEislast
//                 , /*  9 */ buf->KennungKettenausschwingwinkels
//                 , /* 10 */ buf->KennungZusatzlast
//                 , /* 11 */ buf->KennungEiswalze
//                 , /* 12 */ buf->LastfaktorChar
//                 , /* 13 */ buf->WindlastfaktorChar
//                 , /* 14 */ buf->ReckwertChar
//                 , /* 15 */ buf->AusnahmelastChar
//                 , /* 16 */ buf->Temperaturzuschlag
//                 , /* 17 */ buf->GrenzlastBerechnung
//             );
//             assert(n == 17);

//             n = sscanf(buf->ZustandsindexChar, "%d", &buf->ZustandsindexInt); assert(n == 1);
//             n = sscanf(buf->TemperaturCChar, "%d", &buf->TemperaturCInt); assert(n == 1);
//             n = sscanf(buf->LastfaktorChar, "%f", &buf->LastfaktorFloat); assert(n == 1);
//             n = sscanf(buf->WindlastfaktorChar, "%f", &buf->WindlastfaktorFloat); assert(n == 1);
//             n = sscanf(buf->ReckwertChar, "%f", &buf->ReckwertFloat); assert(n == 1);
//             n = sscanf(buf->AusnahmelastChar, "%f", &buf->AusnahmelastFloat); assert(n == 1);
//         }
//         else if (std::strcmp("SLG1", aDSK) == 0 && g_dictDSKs["SLG1"])
//         {
//             // struct SLG1 buf { };
//             auto buf{ std::make_shared<SLG1>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLG1", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , /*     */buf->fmtDS
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->SeilindexChar
//                 , /*  3 */ buf->Seilbezeichnung
//                 , /*  4 */ buf->SpannungsebeneChar
//                 , /*  5 */ buf->AnzahlTeilleiterChar
//                 , /*  6 */ buf->Buendelanordnung
//                 , /*  7 */ buf->TeilleiterabstandChar
//                 , /*  8 */ buf->Seiltyp
//                 , /*  9 */ buf->TemperaturdifferenzSeilkriechenChar
//                 , /* 10 */ buf->KriechfaktorChar
//                 , /* 11 */ buf->UeberziehfaktorChar
//                 , /* 12 */ buf->KriechzeitChar
//                 , /* 13 */ buf->Kennung_EN_Seil
//                 , /* 14 */ buf->KennungSeilmanuellEingefuegt
//                 , /* 15 */ buf->Isolationsar
//                 , /* 16 */ buf->VorzeichenTemperaturdifferenz
//                 , /* 17 */ buf->VorzeichenKriechfaktor
//             );
//             assert(n == 17);

//             n = sscanf(buf->SeilindexChar, "%d", &buf->SeilindexInt); assert(n == 1);
//             n = sscanf(buf->SpannungsebeneChar, "%d", &buf->SpannungsebeneInt); assert(n == 1);
//             n = sscanf(buf->AnzahlTeilleiterChar, "%d", &buf->AnzahlTeilleiterInt); assert(n == 1);
//             n = sscanf(buf->TeilleiterabstandChar, "%f", &buf->TeilleiterabstandFloat); assert(n == 1);
//             n = sscanf(buf->TemperaturdifferenzSeilkriechenChar, "%f", &buf->TemperaturdifferenzSeilkriechenFloat); assert(n == 1);
//             n = sscanf(buf->KriechfaktorChar, "%f", &buf->KriechfaktorFloat); assert(n == 1);
//             n = sscanf(buf->UeberziehfaktorChar, "%f", &buf->UeberziehfaktorFloat); assert(n == 1);
//             n = sscanf(buf->KriechzeitChar, "%f", &buf->KriechzeitFloat); assert(n == 1);
//         }
//         else if (std::strcmp("SLG2", aDSK) == 0 && g_dictDSKs["SLG2"])
//         {
//             // struct SLG2 buf { };
//             auto buf{ std::make_shared<SLG2>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLG2", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , /*     */buf->fmtDS
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->SeilindexChar
//                 , /*  3 */ buf->SeildurchmesserChar
//                 , /*  4 */ buf->SeilquerschnittChar
//                 , /*  5 */ buf->E_ModulChar
//                 , /*  6 */ buf->AusdehnungskoeffizientChar
//                 , /*  7 */ buf->SpezSeilgewichtChar
//                 , /*  8 */ buf->NormaleZusatzlastChar
//                 , /*  9 */ buf->AerodynamischerKraftbeiwertChar
//                 , /* 10 */ buf->SeilgewichtDBChar
//                 , /* 11 */ buf->FettmasseChar
//                 , /* 12 */ buf->KennungQLK
//             );
//             assert(n == 12);

//             /* 2 */ n = sscanf(buf->SeilindexChar, "%d", &buf->SeilindexInt); assert(n == 1);
//             /* 3 */ n = sscanf(buf->SeildurchmesserChar, "%f", &buf->SeildurchmesserFloat); assert(n == 1);
//             /* 4 */ n = sscanf(buf->SeilquerschnittChar, "%f", &buf->SeilquerschnittFloat); assert(n == 1);
//             /* 5 */ n = sscanf(buf->E_ModulChar, "%f", &buf->E_ModulFloat); assert(n == 1);
//             /* 6 */ n = sscanf(buf->AusdehnungskoeffizientChar, "%f", &buf->AusdehnungskoeffizientFloat); assert(n == 1);
//             /* 7 */ n = sscanf(buf->SpezSeilgewichtChar, "%f", &buf->SpezSeilgewichtFloat); assert(n == 1);
//             /* 8 */ n = sscanf(buf->NormaleZusatzlastChar, "%f", &buf->NormaleZusatzlastFloat); assert(n == 1);
//             /* 9 */ n = sscanf(buf->AerodynamischerKraftbeiwertChar, "%f", &buf->AerodynamischerKraftbeiwertFloat); assert(n == 1);
//             /* 0 */ n = sscanf(buf->SeilgewichtDBChar, "%f", &buf->SeilgewichtDBFloat); assert(n == 1);
//             /* 1 */ n = sscanf(buf->FettmasseChar, "%f", &buf->FettmasseFloat); assert(n == 1);
//         }
//         else if (std::strcmp("SLG3", aDSK) == 0 && g_dictDSKs["SLG3"])
//         {
//             // struct SLG3 buf { };
//             auto buf{ std::make_shared<SLG3>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLG3", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->SeilindexChar
//                 , /*  3 */ buf->HoechstzugspannungChar
//                 , /*  4 */ buf->MittelzugspannungChar
//                 , /*  5 */ buf->DauerzugspannungChar
//                 , /*  6 */ buf->BruchkraftChar
//                 , /*  7 */ buf->StahlgewichtsanteilChar
//                 , /*  8 */ buf->StahlquerschnittChar
//             );
//             assert(n == 8);

//             /* 2 */ n = sscanf(buf->SeilindexChar, "%d", &buf->SeilindexInt); assert(n == 1);
//             /* 3 */ n = sscanf(buf->HoechstzugspannungChar, "%f", &buf->HoechstzugspannungFloat); assert(n == 1);
//             /* 4 */ n = sscanf(buf->MittelzugspannungChar, "%f", &buf->MittelzugspannungFloat); assert(n == 1);
//             /* 5 */ n = sscanf(buf->DauerzugspannungChar, "%f", &buf->DauerzugspannungFloat); assert(n == 1);
//             /* 6 */ n = sscanf(buf->BruchkraftChar, "%f", &buf->BruchkraftFloat); assert(n == 1);
//             /* 7 */ n = sscanf(buf->StahlgewichtsanteilChar, "%f", &buf->StahlgewichtsanteilFloat); assert(n == 1);
//             /* 8 */ n = sscanf(buf->StahlquerschnittChar, "%f", &buf->StahlquerschnittFloat); assert(n == 1);
//         }
//         else if (std::strcmp("MAST", aDSK) == 0 && g_dictDSKs["MAST"])
//         {
//             // struct MAST buf { };
//             auto buf{ std::make_shared<MAST>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("MAST", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->MastindexChar
//                 , /*   3 */ buf->MastnummerMastname_1
//                 , /*   4 */ buf->Masttyp
//                 , /*   5 */ buf->Masttypenbezeichnung_1
//                 , /*   6 */ buf->AusfuehrungChar
//                 , /*   7 */ buf->LaengenstationMaststandortChar
//                 , /*   8 */ buf->HoeheMastfusspunktChar
//                 , /*   9 */ buf->LeitungswinkelChar
//                 , /*  10 */ buf->StellwinkelChar
//                 , /*  11 */ buf->Masttypenbezeichnung_2
//                 , /*  12 */ buf->OrdinateMaststandortChar
//                 , /*  13 */ buf->MastnummerMastname_2
//             );
//             assert(n == 13);

//             /*  2 */ n = sscanf(buf->MastindexChar, "%d", &buf->MastindexInt); assert(n == 1);
//             /*  6 */ n = sscanf(buf->AusfuehrungChar, "%f", &buf->AusfuehrungFloat); assert(n == 1);
//             /*  7 */ n = sscanf(buf->LaengenstationMaststandortChar, "%f", &buf->LaengenstationMaststandortFloat); assert(n == 1);
//             /*  8 */ n = sscanf(buf->HoeheMastfusspunktChar, "%f", &buf->HoeheMastfusspunktFloat); assert(n == 1);
//             /*  9 */ n = sscanf(buf->LeitungswinkelChar, "%f", &buf->LeitungswinkelFloat); assert(n == 1);
//             /* 10 */ n = sscanf(buf->StellwinkelChar, "%f", &buf->StellwinkelFloat); assert(n == 1);
//             /* 12 */ n = sscanf(buf->OrdinateMaststandortChar, "%f", &buf->OrdinateMaststandortFloat); assert(n == 1);
//         }
//         else if (std::strcmp("TRAV", aDSK) == 0 && g_dictDSKs["TRAV"])
//         {
//             // struct TRAV buf { };
//             auto buf{ std::make_shared<TRAV>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("TRAV", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->MastindexChar
//                 , /*   3 */ buf->PhasenindexChar
//                 , /*   4 */ buf->TraversenhoeheChar
//                 , /*   5 */ buf->AusladungChar
//                 , /*   6 */ buf->StellwinkelTraverseChar
//                 , /*   7 */ buf->KettenlaengeChar
//                 , /*   8 */ buf->KettenindexChar
//                 , /*   9 */ buf->HoehenbezugStaudruckChar
//                 , /*  10 */ buf->TraversenexzentrizitaetChar
//             );
//             assert(n == 10);

//             /*  2 */ n = sscanf(buf->MastindexChar, "%d", &buf->MastindexInt); assert(n == 1);
//             /*  3 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
//             /*  4 */ n = sscanf(buf->TraversenhoeheChar, "%f", &buf->TraversenhoeheFloat); assert(n == 1);
//             /*  5 */ n = sscanf(buf->AusladungChar, "%f", &buf->AusladungFloat); assert(n == 1);
//             /*  6 */ n = sscanf(buf->StellwinkelTraverseChar, "%f", &buf->StellwinkelTraverseFloat); assert(n == 1);
//             /*  7 */ n = sscanf(buf->KettenlaengeChar, "%f", &buf->KettenlaengeFloat); assert(n == 1);
//             /*  8 */ n = sscanf(buf->KettenindexChar, "%d", &buf->KettenindexInt); assert(n == 1);
//             /*  9 */ n = sscanf(buf->HoehenbezugStaudruckChar, "%f", &buf->HoehenbezugStaudruckFloat); assert(n == 1);
//         }
//         else if (std::strcmp("KET1", aDSK) == 0 && g_dictDSKs["KET1"])
//         {
//             // struct KET1 buf { };
//             auto buf{ std::make_shared<KET1>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("KET1", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KettenindexChar
//                 , /*   3 */ buf->Kettentyp
//                 , /*   4 */ buf->AnzahlKettenstraengeChar
//                 , /*   5 */ buf->Kettentypbezeichnung
//                 , /*   6 */ buf->KettenbezeichnungIsolator
//                 , /*   7 */ buf->Schwingenbezeichnung
// #ifdef FLP
//                 , /*   8 */ buf->Kettennummer
// #endif
//             );
// #ifdef FLP
//             assert(n == 8);
// #else
//             assert(n == 7);
// #endif
//             /*  2 */ n = sscanf(buf->KettenindexChar, "%d", &buf->KettenindexInt); assert(n == 1);
//             /*  4 */ n = sscanf(buf->AnzahlKettenstraengeChar, "%d", &buf->AnzahlKettenstraengeInt); assert(n == 1);
//         }
//         else if (std::strcmp("KET2", aDSK) == 0 && g_dictDSKs["KET2"])
//         {
//             // struct KET2 buf { };
//             auto buf{ std::make_shared<KET2>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("KET2", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KettenindexChar
//                 , /*   3 */ buf->KettenlaengeChar
//                 , /*   4 */ buf->VLaengeChar
//                 , /*   5 */ buf->FesteLaengeChar
//                 , /*   6 */ buf->SchwingenlaengeChar
//                 , /*   7 */ buf->KettengewichtChar
//                 , /*   8 */ buf->EinfachesEisgewichtKetteChar
//                 , /*   9 */ buf->SchwingengewichtChar
//                 , /*  10 */ buf->GrenzausschwingwinkelInnenChar
//                 , /*  11 */ buf->GrenzausschwingwinkelAuszenChar
//                 , /*  12 */ buf->ZusatzgewichtChar
//                 , /*  13 */ buf->EinbaulaengeChar
//                 , /*  14 */ buf->SchirmdurchmesserChar
//                 , /*  15 */ buf->StrunkdurchmesserChar
//                 , /*  16 */ buf->ProjizierteFlaecheChar
//                 , /*  17 */ buf->VKetteVersatzAufhaengungMastInnenChar
//                 , /*  18 */ buf->VKetteVersatzAufhaengungMastAussenChar
//             );
//             assert(n == 18);

//             /*   2 */ n = sscanf(buf->KettenindexChar, "%d", &buf->KettenindexInt); assert(n == 1);
//             /*   3 */ n = sscanf(buf->KettenlaengeChar, "%f", &buf->KettenlaengeFloat); assert(n == 1);
//             /*   4 */ n = sscanf(buf->VLaengeChar, "%f", &buf->VLaengeFloat); assert(n == 1);
//             /*   5 */ n = sscanf(buf->FesteLaengeChar, "%f", &buf->FesteLaengeFloat); assert(n == 1);
//             /*   6 */ n = sscanf(buf->SchwingenlaengeChar, "%f", &buf->SchwingenlaengeFloat); assert(n == 1);
//             /*   7 */ n = sscanf(buf->KettengewichtChar, "%f", &buf->KettengewichtFloat); assert(n == 1);
//             /*   8 */ n = sscanf(buf->EinfachesEisgewichtKetteChar, "%f", &buf->EinfachesEisgewichtKetteFloat); assert(n == 1);
//             /*   9 */ n = sscanf(buf->SchwingengewichtChar, "%f", &buf->SchwingengewichtFloat); assert(n == 1);
//             /*  10 */ n = sscanf(buf->GrenzausschwingwinkelInnenChar, "%f", &buf->GrenzausschwingwinkelInnenFloat); assert(n == 1);
//             /*  11 */ n = sscanf(buf->GrenzausschwingwinkelAuszenChar, "%f", &buf->GrenzausschwingwinkelAuszenFloat); assert(n == 1);
//             /*  12 */ n = sscanf(buf->ZusatzgewichtChar, "%f", &buf->ZusatzgewichtFloat); assert(n == 1);
//             /*  13 */ n = sscanf(buf->EinbaulaengeChar, "%f", &buf->EinbaulaengeFloat); assert(n == 1);
//             /*  14 */ n = sscanf(buf->SchirmdurchmesserChar, "%f", &buf->SchirmdurchmesserFloat); assert(n == 1);
//             /*  15 */ n = sscanf(buf->StrunkdurchmesserChar, "%f", &buf->StrunkdurchmesserFloat); assert(n == 1);
//             /*  16 */ n = sscanf(buf->ProjizierteFlaecheChar, "%f", &buf->ProjizierteFlaecheFloat); assert(n == 1);
//             /*  17 */ n = sscanf(buf->VKetteVersatzAufhaengungMastInnenChar, "%f", &buf->VKetteVersatzAufhaengungMastInnenFloat); assert(n == 1);
//             /*  18 */ n = sscanf(buf->VKetteVersatzAufhaengungMastAussenChar, "%f", &buf->VKetteVersatzAufhaengungMastAussenFloat); assert(n == 1);
//         }
//         else if (std::strcmp("EZLA", aDSK) == 0 && g_dictDSKs["EZLA"])
//         {
//             // struct EZLA buf { };
//             auto buf{ std::make_shared<EZLA>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("EZLA", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->LastindexChar
//                 , /*   3 */ buf->PhasenindexChar
//                 , /*   4 */ buf->MastindexLinkerMastChar
//                 , /*   5 */ buf->Lasttyp
//                 , /*   6 */ buf->KennungLastEndzustand
//                 , /*   7 */ buf->KennungLastMontagezustand
//                 , /*   8 */ buf->KennungLastRollenzustand
//                 , /*   9 */ buf->ZustandsindexChar
//                 , /*  10 */ buf->AnzahlLastenInt
//                 , /*  11 */ buf->StationLinkerMastChar
//                 , /*  12 */ buf->AbstandLastenEndestationChar
//                 , /*  13 */ buf->LastChar
//                 , /*  14 */ buf->EinfacheEislastChar
//             );
//             assert(n == 14);

//             /*   2 */ n = sscanf(buf->LastindexChar, "%d", &buf->LastindexInd); assert(n == 1);
//             /*   3 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
//             /*   4 */ n = sscanf(buf->MastindexLinkerMastChar, "%d", &buf->MastindexLinkerMastInt); assert(n == 1);
//             /*   9 */ n = sscanf(buf->ZustandsindexChar, "%d", &buf->ZustandsindexInt); assert(n == 1);
//             /*  10 */ n = sscanf(buf->AnzahlLastenChar, "%d", &buf->AnzahlLastenInt); assert(n == 1);
//             /*  11 */ n = sscanf(buf->StationLinkerMastChar, "%f", &buf->StationLinkerMastFloat); assert(n == 1);
//             /*  12 */ n = sscanf(buf->AbstandLastenEndestationChar, "%f", &buf->AbstandLastenEndestationFloat); assert(n == 1);
//             /*  13 */ n = sscanf(buf->LastChar, "%f", &buf->LastFloat); assert(n == 1);
//             /*  14 */ n = sscanf(buf->EinfacheEislastChar, "%f", &buf->EinfacheEislastFloat); assert(n == 1);
//         }
//         else if (std::strcmp("SLK1", aDSK) == 0 && g_dictDSKs["SLK1"])
//         {
//             // struct SLK1 buf { };
//             auto buf{ std::make_shared<SLK1>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLK1", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->SeilkurvenindexChar
//                 , /*   3 */ buf->PhasenindexChar
//                 , /*   4 */ buf->ZustandsindexChar
//                 , /*   5 */ buf->MastindexLinkerMastChar
//                 , /*   6 */ buf->MastindexRechterMastChar
//                 , /*   7 */ buf->StationSeilaufhaengepunktLinksChar
//                 , /*   8 */ buf->HoeheSeilaufhaengepunktLinksChar
//                 , /*   9 */ buf->OrdinateSeilaufhaengepunktChar
//                 , /*  10 */ buf->StationSeilaufhaengepunktRechtsChar
//                 , /*  11 */ buf->HoeheSeilaufhaengepunktRechtsChar
//                 , /*  12 */ buf->OrdinateSeilaufhaengepunktRechtsChar
//                 , /*  13 */ buf->StationSeilaufhaengepunktLinksTransformChar
//                 , /*  14 */ buf->OrdinateSeilaufhaengepunktLinksChar
//                 , /*  15 */ buf->StationSeilaufhaengepunktRechtsTransformChar
//                 , /*  16 */ buf->OrdinateSeilaufhaengepunktRechtsTransformChar
//             );
//             assert(n == 16);

//             /*   2 */ n = sscanf(buf->SeilkurvenindexChar, "%d", &buf->SeilkurvenindexInt); assert(n == 1);
//             /*   3 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
//             /*   4 */ n = sscanf(buf->ZustandsindexChar, "%d", &buf->ZustandsindexInt); assert(n == 1);
//             /*   5 */ n = sscanf(buf->MastindexLinkerMastChar, "%d", &buf->MastindexLinkerMastInt); assert(n == 1);
//             /*   6 */ n = sscanf(buf->MastindexRechterMastChar, "%d", &buf->MastindexRechterMastInt); assert(n == 1);
//             /*   7 */ n = sscanf(buf->StationSeilaufhaengepunktLinksChar, "%f", &buf->StationSeilaufhaengepunktLinksFloat); assert(n == 1);
//             /*   8 */ n = sscanf(buf->HoeheSeilaufhaengepunktLinksChar, "%f", &buf->HoeheSeilaufhaengepunktLinksFloat); assert(n == 1);
//             /*   9 */ n = sscanf(buf->OrdinateSeilaufhaengepunktChar, "%f", &buf->OrdinateSeilaufhaengepunktFloat); assert(n == 1);
//             /*  10 */ n = sscanf(buf->StationSeilaufhaengepunktRechtsChar, "%f", &buf->StationSeilaufhaengepunktRechtsFloat); assert(n == 1);
//             /*  11 */ n = sscanf(buf->HoeheSeilaufhaengepunktRechtsChar, "%f", &buf->HoeheSeilaufhaengepunktRechtsFloat); assert(n == 1);
//             /*  12 */ n = sscanf(buf->OrdinateSeilaufhaengepunktRechtsChar, "%f", &buf->OrdinateSeilaufhaengepunktRechtsFloat); assert(n == 1);
//             /*  13 */ n = sscanf(buf->StationSeilaufhaengepunktLinksTransformChar, "%f", &buf->StationSeilaufhaengepunktLinksTransformFloat); assert(n == 1);
//             /*  14 */ n = sscanf(buf->OrdinateSeilaufhaengepunktLinksChar, "%f", &buf->OrdinateSeilaufhaengepunktLinksFloat); assert(n == 1);
//             /*  15 */ n = sscanf(buf->StationSeilaufhaengepunktRechtsTransformChar, "%f", &buf->StationSeilaufhaengepunktRechtsTransformFloat); assert(n == 1);
//             /*  16 */ n = sscanf(buf->OrdinateSeilaufhaengepunktRechtsTransformChar, "%f", &buf->OrdinateSeilaufhaengepunktRechtsTransformFloat); assert(n == 1);
//         }
//         else if (std::strcmp("SLK2", aDSK) == 0 && g_dictDSKs["SLK2"])
//         {
//             // struct SLK2 buf { };
//             auto buf{ std::make_shared<SLK2>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLK2", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->SeilkurvenindexChar
//                 , /*   3 */ buf->SeilspannungEndzustandChar
//                 , /*   4 */ buf->SeilgewichtEndzustandChar
//                 , /*   5 */ buf->SeilausschwingwinkelChar
//                 , /*   6 */ buf->DurchhangFeldmitteChar
//                 , /*   7 */ buf->StationSeilpunktFeldmitteChar
//                 , /*   8 */ buf->HoeheSeilpunktFeldmitteChar
//                 , /*   9 */ buf->OrdinateSeilpunktFeldmitteChar
//                 , /*  10 */ buf->TiefsterPunktFeldmitte
//                 , /*  11 */ buf->GroeszterDurchhangFeld
//                 , /*  12 */ buf->GewichtsspannweiteChar
//                 , /*  13 */ buf->BogenlaengeSeilChar
//                 , /*  14 */ buf->ScheitelpunktEntfernungLinkerMastChar
//                 , /*  15 */ buf->ScheitelpunktSeilhoeheChar
//                 , /*  16 */ buf->SeilspannungAbsolutAufhaengepunktLinksChar
//                 , /*  17 */ buf->SeilspannungAbsolutAufhaengepunktRechtChar
//             );
//             assert(n == 17);

//             /*   2 */ n = sscanf(buf->SeilkurvenindexChar, "%d", &buf->SeilkurvenindexInt); assert(n == 1);
//             /*   3 */ n = sscanf(buf->SeilspannungEndzustandChar, "%f", &buf->SeilspannungEndzustandFloat); assert(n == 1);
//             /*   4 */ n = sscanf(buf->SeilgewichtEndzustandChar, "%f", &buf->SeilgewichtEndzustandFloat); assert(n == 1);
//             /*   5 */ n = sscanf(buf->SeilausschwingwinkelChar, "%f", &buf->SeilausschwingwinkelFloat); assert(n == 1);
//             /*   6 */ n = sscanf(buf->DurchhangFeldmitteChar, "%f", &buf->DurchhangFeldmitteFloat); assert(n == 1);
//             /*   7 */ n = sscanf(buf->StationSeilpunktFeldmitteChar, "%f", &buf->StationSeilpunktFeldmitteFloat); assert(n == 1);
//             /*   8 */ n = sscanf(buf->HoeheSeilpunktFeldmitteChar, "%f", &buf->HoeheSeilpunktFeldmitteFloat); assert(n == 1);
//             /*   9 */ n = sscanf(buf->OrdinateSeilpunktFeldmitteChar, "%f", &buf->OrdinateSeilpunktFeldmitteFloat); assert(n == 1);
//             /*  12 */ n = sscanf(buf->GewichtsspannweiteChar, "%f", &buf->GewichtsspannweiteFloat); assert(n == 1);
//             /*  13 */ n = sscanf(buf->BogenlaengeSeilChar, "%f", &buf->BogenlaengeSeilFloat); assert(n == 1);
//             /*  14 */ n = sscanf(buf->ScheitelpunktEntfernungLinkerMastChar, "%f", &buf->ScheitelpunktEntfernungLinkerMastFloat); assert(n == 1);
//             /*  15 */ n = sscanf(buf->ScheitelpunktSeilhoeheChar, "%f", &buf->ScheitelpunktSeilhoeheFloat); assert(n == 1);
//             /*  16 */ n = sscanf(buf->SeilspannungAbsolutAufhaengepunktLinksChar, "%f", &buf->SeilspannungAbsolutAufhaengepunktLinksFloat); assert(n == 1);
//             /*  17 */ n = sscanf(buf->SeilspannungAbsolutAufhaengepunktRechtChar, "%f", &buf->SeilspannungAbsolutAufhaengepunktRechtsFloat); assert(n == 1);
//         }
//         else if (std::strcmp("SLK3", aDSK) == 0 && g_dictDSKs["SLK3"])
//         {
//             // struct SLK3 buf { };
//             auto buf{ std::make_shared<SLK3>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLK3", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->SeilkurvenindexChar
//                 , /*   3 */ buf->KettenauslenkungLinkerMastInLeitungsrichtungChar
//                 , /*   4 */ buf->KettenauslenkungLinkerMastQuerLeitungsrichtungChar
//                 , /*   5 */ buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungChar
//                 , /*   6 */ buf->KettenauslenkungRechterMastInLeitungsrichtungChar
//                 , /*   7 */ buf->KettenauslenkungRechterMastQuerLeitungsrichtungChar
//                 , /*   8 */ buf->KettenauslenkungRechterMastVertikalLeitungsrichtungChar
//                 , /*   9 */ buf->SeilzugLinksChar
//                 , /*  10 */ buf->SeilzugRechtsChar
//             );
//             assert(n == 10);

//             /*   2 */ n = sscanf(buf->SeilkurvenindexChar, "%d", &buf->SeilkurvenindexInt); assert(n == 1);
//             /*   3 */ n = sscanf(buf->KettenauslenkungLinkerMastInLeitungsrichtungChar, "%f", &buf->KettenauslenkungLinkerMastInLeitungsrichtungFloat); assert(n == 1);
//             /*   4 */ n = sscanf(buf->KettenauslenkungLinkerMastQuerLeitungsrichtungChar, "%f", &buf->KettenauslenkungLinkerMastQuerLeitungsrichtungFloat); assert(n == 1);
//             /*   5 */ n = sscanf(buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungChar, "%f", &buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungFloat); assert(n == 1);
//             /*   6 */ n = sscanf(buf->KettenauslenkungRechterMastInLeitungsrichtungChar, "%f", &buf->KettenauslenkungRechterMastInLeitungsrichtungFloat); assert(n == 1);
//             /*   7 */ n = sscanf(buf->KettenauslenkungRechterMastQuerLeitungsrichtungChar, "%f", &buf->KettenauslenkungRechterMastQuerLeitungsrichtungFloat); assert(n == 1);
//             /*   8 */ n = sscanf(buf->KettenauslenkungRechterMastVertikalLeitungsrichtungChar, "%f", &buf->KettenauslenkungRechterMastVertikalLeitungsrichtungFloat); assert(n == 1);
//             /*   9 */ n = sscanf(buf->SeilzugLinksChar, "%f", &buf->SeilzugLinksFloat); assert(n == 1);
//             /*  10 */ n = sscanf(buf->SeilzugRechtsChar, "%f", &buf->SeilzugRechtsFloat); assert(n == 1);
//         }
//         else if (std::strcmp("OBJ1", aDSK) == 0 && g_dictDSKs["OBJ1"])
//         {
//             // struct OBJ1 buf { };
//             auto buf{ std::make_shared<OBJ1>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBJ1", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KreuzungsobjektindexTeil_1_Char
//                 , /*   3 */ buf->Objektnummer
//                 , /*   4 */ buf->MindestabstandChar
//                 , /*   5 */ buf->NachweiscodeChar
//                 , /*   6 */ buf->Abstandstyp
//                 , /*   7 */ buf->Nachweiszustaende
//                 , /*   8 */ buf->MastindexChar
//                 , /*   9 */ buf->PhasenindexChar
//                 , /*  10 */ buf->Objekttyp
//                 , /*  11 */ buf->SteuerungsparameterDruckausgabe
//                 , /*  12 */ buf->ParameterLeitungskreuzungen
//                 , /*  13 */ buf->NeuerObjekttyp
//                 , /*  14 */ buf->Objektabstand
//                 , /*  15 */ buf->ObjektRechnen
//                 , /*  16 */ buf->KreuzungsobjektindexTeil_2_Char
//                 , /*  17 */ buf->Mindestabstand110kVChar
//             );
//             assert(n == 17);

//             /*   2 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
//             /*   4 */ n = sscanf(buf->MindestabstandChar, "%f", &buf->MindestabstandFloat); assert(n == 1);
//             /*   5 */ n = sscanf(buf->NachweiscodeChar, "%d", &buf->NachweiscodeInt); assert(n == 1);
//             /*   8 */ n = sscanf(buf->MastindexChar, "%d", &buf->MastindexInt); assert(n == 1);
//             /*   9 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
//             /*  16 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
//             /*  17 */ n = sscanf(buf->Mindestabstand110kVChar, "%f", &buf->Mindestabstand110kVFloat); assert(n == 1);
//         }
//         else if (std::strcmp("OBJ2", aDSK) == 0 && g_dictDSKs["OBJ2"])
//         {
//             // struct OBJ2 buf { };
//             auto buf{ std::make_shared<OBJ2>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBJ2", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KreuzungsobjektindexTeil_1_Char
//                 , /*   3 */ buf->ObjektbezeichnungZeile_1
//                 , /*   4 */ buf->ObjektbezeichnungZeile_2
//                 , /*   5 */ buf->KreuzungsobjektindexTeil_2_Char
//             );
//             assert(n == 5);

//             /*   2 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
//             /*   5 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
//         }
//         else if (std::strcmp("OBJ3", aDSK) == 0 && g_dictDSKs["OBJ3"])
//         {
//             // struct OBJ3 buf { };
//             auto buf{ std::make_shared<OBJ3>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBJ3", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KreuzungsobjektindexTeil_1_Char
//                 , /*   3 */ buf->EigentümerZeile_1
//                 , /*   4 */ buf->EigentümerZeile_2
//                 , /*   5 */ buf->KreuzungsobjektindexTeil_2_Char
//             );
//             assert(n == 5);

//             /*   2 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
//             /*   5 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
//         }
//         else if (std::strcmp("OPKT", aDSK) == 0 && g_dictDSKs["OPKT"])
//         {
//             // struct OPKT buf { };
//             auto buf{ std::make_shared<OPKT>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OPKT", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->PunktindexTeil_1_Char
//                 , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Char
//                 , /*    4 */ buf->StationChar
//                 , /*    5 */ buf->OrdinateChar
//                 , /*    6 */ buf->FuszhoeheChar
//                 , /*    7 */ buf->ObjekthoeheChar
//                 , /*    8 */ buf->PunktnummerVermessung
//                 , /*    9 */ buf->Punktindex_Teil_2_Char
// #ifdef FLP
//                 , /*   10 */ buf->MS_LinkChar
// #endif
//                 , /*   11 */ buf->KreuzungsobjektindexTeil_2_Char);
// #ifdef FLP
//             assert(n == 11);
// #else
//             assert(n == 10);
// #endif
//             /*   2 */ n = sscanf(buf->PunktindexTeil_1_Char, "%d", &buf->PunktindexTeil_1_Int); assert(n == 1);
//             /*   3 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_1_Char, "%d", &buf->Kreuzungsobjektindex_Teil_1_Int); assert(n == 1);
//             /*   4 */ n = sscanf(buf->StationChar, "%f", &buf->StationFloat); assert(n == 1);
//             /*   5 */ n = sscanf(buf->OrdinateChar, "%f", &buf->OrdinateFloat); assert(n == 1);
//             /*   6 */ n = sscanf(buf->FuszhoeheChar, "%f", &buf->FuszhoeheFloat); assert(n == 1);
//             /*   7 */ n = sscanf(buf->ObjekthoeheChar, "%f", &buf->ObjekthoeheFloat); assert(n == 1);
//             /*   9 */ n = sscanf(buf->Punktindex_Teil_2_Char, "%d", &buf->Punktindex_Teil_2_Int); assert(n == 1);
// #ifdef FLP
//             /*  10 */ n = sscanf(buf->MS_LinkChar, "%d", &buf->MS_LinkInt); assert(n == 1);
// #endif
//             /*  11 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
//         }
//         else if (std::strcmp("OLIN", aDSK) == 0 && g_dictDSKs["OLIN"])
//         {
//             // struct OLIN buf { };
//             auto buf{ std::make_shared<OLIN>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OLIN", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->LinienindexTeil_1_Char
//                 , /*    3 */ buf->KreuzungsobjektindexTeil_1_Char
//                 , /*    4 */ buf->IndexAnfangspunkt_1_Teil_1_Char
//                 , /*    5 */ buf->Index_Endpunkt_1_Teil_1_Char
//                 , /*    6 */ buf->Index_Anfangspunkt_2_Teil_2_Char
//                 , /*    7 */ buf->IndexEndpunkt_2_Teil_2_Char
// #ifdef FLP
//                 , /*    8 */ buf->MS_LinkChar
// #endif
//                 , /*    9 */ buf->Linienindex_Teil_2_Char
//                 , /*   10 */ buf->Kreuzungsobjektindex_Teil_2_Char
//             );
// #ifdef FLP
//             assert(n == 10);
// #else
//             assert(n == 9);
// #endif
//             /*   2 */ n = sscanf(buf->LinienindexTeil_1_Char, "%d", &buf->LinienindexTeil_1_Int); assert(n == 1);
//             /*   3 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
//             /*   4 */ n = sscanf(buf->IndexAnfangspunkt_1_Teil_1_Char, "%d", &buf->IndexAnfangspunkt_1_Teil_1_Int); assert(n == 1);
//             /*   5 */ n = sscanf(buf->Index_Endpunkt_1_Teil_1_Char, "%d", &buf->Index_Endpunkt_1_Teil_1_Int); assert(n == 1);
//             /*   6 */ n = sscanf(buf->Index_Anfangspunkt_2_Teil_2_Char, "%d", &buf->Index_Anfangspunkt_2_Teil_2_Int); assert(n == 1);
//             /*   7 */ n = sscanf(buf->IndexEndpunkt_2_Teil_2_Char, "%d", &buf->IndexEndpunkt_2_Teil_2_Int); assert(n == 1);
// #ifdef FLP
//             /*   8 */ n = sscanf(buf->MS_LinkChar, "%d", &buf->MS_LinkInt); assert(n == 1);
// #endif
//             /*   9 */ n = sscanf(buf->Linienindex_Teil_2_Char, "%d", &buf->Linienindex_Teil_2_Int); assert(n == 1);
//             /*  10 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_2_Char, "%d", &buf->Kreuzungsobjektindex_Teil_2_Int); assert(n == 1);
//         }
//         else if (std::strcmp("OBFL", aDSK) == 0 && g_dictDSKs["OBFL"])
//         {
//             // struct OBFL buf { };
//             auto buf{ std::make_shared<OBFL>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBFL", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->Flaechenindex_Teil_1_Char
//                 , /*    3 */ buf->KreuzungsobjektindexTeil_1_Char
//                 , /*    4 */ buf->Punktindex_1_Teil_1_Char
//                 , /*    5 */ buf->Punktindex_2_Teil_1_Char
//                 , /*    6 */ buf->Punktindex_3_Teil_1_Char
//                 , /*    7 */ buf->Punktindex_4_Teil_1_Char
//                 , /*    8 */ buf->Punktindex_1_Teil_2_Char
//                 , /*    9 */ buf->Punktindex_2_Teil_2_Char
//                 , /*   10 */ buf->Punktindex_3_Teil_2_Char
//                 , /*   11 */ buf->Punktindex_4_Teil_2_Char
// #ifdef FLP
//                 , /*   12 */ buf->MS_Link_Char
// #endif
//                 , /*   13 */ buf->Flaechenindex_Teil_2_Char, /*   14 */ buf->Kreuzungsobjektindex_Teil_2_Char);
// #ifdef FLP
//             assert(n == 14);
// #else
//             assert(n == 13);
// #endif
//             /*   2 */ n = sscanf(buf->Flaechenindex_Teil_1_Char, "%d", &buf->Flaechenindex_Teil_1_Int); assert(n == 1);
//             /*   3 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
//             /*   4 */ n = sscanf(buf->Punktindex_1_Teil_1_Char, "%d", &buf->Punktindex_1_Teil_1_Int); assert(n == 1);
//             /*   5 */ n = sscanf(buf->Punktindex_2_Teil_1_Char, "%d", &buf->Punktindex_2_Teil_1_Int); assert(n == 1);
//             /*   6 */ n = sscanf(buf->Punktindex_3_Teil_1_Char, "%d", &buf->Punktindex_3_Teil_1_Int); assert(n == 1);
//             /*   7 */ n = sscanf(buf->Punktindex_4_Teil_1_Char, "%d", &buf->Punktindex_4_Teil_1_Int); assert(n == 1);
//             /*   8 */ n = sscanf(buf->Punktindex_1_Teil_2_Char, "%d", &buf->Punktindex_1_Teil_2_Int); assert(n == 1);
//             /*   9 */ n = sscanf(buf->Punktindex_2_Teil_2_Char, "%d", &buf->Punktindex_2_Teil_2_Int); assert(n == 1);
//             /*  10 */ n = sscanf(buf->Punktindex_3_Teil_2_Char, "%d", &buf->Punktindex_3_Teil_2_Int); assert(n == 1);
//             /*  11 */ n = sscanf(buf->Punktindex_4_Teil_2_Char, "%d", &buf->Punktindex_4_Teil_2_Int); assert(n == 1);
// #ifdef FLP
//             /*  12 */ n = sscanf(buf->MS_Link_Char, "%d", &buf->MS_Link_Int); assert(n == 1);
// #endif
//             /*  13 */ n = sscanf(buf->Flaechenindex_Teil_2_Char, "%d", &buf->Flaechenindex_Teil_2_Int); assert(n == 1);
//             /*  14 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_2_Char, "%d", &buf->Kreuzungsobjektindex_Teil_2_Int); assert(n == 1);
//         }
//         else if (std::strcmp("OGEL", aDSK) == 0 && g_dictDSKs["OGEL"])
//         {
//             // struct OGEL buf { };
//             auto buf{ std::make_shared<OGEL>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OGEL", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->Gelaendepunktindex_Teil_1_Char
//                 , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Char
//                 , /*    4 */ buf->StationChar
//                 , /*    5 */ buf->GelaendehoeheTrassenmitte_Char
//                 , /*    6 */ buf->OrdinateSeitlichUeberhoehung_1_Char
//                 , /*    7 */ buf->SeitlicheUeberhoehung_1_Char
//                 , /*    8 */ buf->OrdinateSeitlicheUeberhoehung_2_Char
//                 , /*    9 */ buf->SeitlicheUeberhoehung_2_Char
//                 , /*   10 */ buf->Gelaendepunktindex_Teil_2_Char
//                 , /*   11 */ buf->KulturartCode
//                 , /*   12 */ buf->KreuzungsobjektindexTeil_2_Char
//             );
//             assert(n == 12);

//             /*   2 */ n = sscanf(buf->Gelaendepunktindex_Teil_1_Char, "%d", &buf->Gelaendepunktindex_Teil_1_Int); assert(n == 1);
//             /*   3 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_1_Char, "%d", &buf->Kreuzungsobjektindex_Teil_1_Int); assert(n == 1);
//             /*   4 */ n = sscanf(buf->StationChar, "%f", &buf->StationFloat); assert(n == 1);
//             /*   5 */ n = sscanf(buf->GelaendehoeheTrassenmitte_Char, "%f", &buf->GelaendehoeheTrassenmitteFloat); assert(n == 1);
//             /*   6 */ n = sscanf(buf->OrdinateSeitlichUeberhoehung_1_Char, "%f", &buf->OrdinateSeitlichUeberhoehung_1_Float); assert(n == 1);
//             /*   7 */ n = sscanf(buf->SeitlicheUeberhoehung_1_Char, "%f", &buf->SeitlicheUeberhoehung_1_Float); assert(n == 1);
//             /*   8 */ n = sscanf(buf->OrdinateSeitlicheUeberhoehung_2_Char, "%f", &buf->OrdinateSeitlicheUeberhoehung_2_Float); assert(n == 1);
//             /*   9 */ n = sscanf(buf->SeitlicheUeberhoehung_2_Char, "%f", &buf->SeitlicheUeberhoehung_2_Float); assert(n == 1);
//             /*  10 */ n = sscanf(buf->Gelaendepunktindex_Teil_2_Char, "%d", &buf->Gelaendepunktindex_Teil_2_Int); assert(n == 1);
//             /*  12 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
//         }
//         else if (std::strcmp("OGE2", aDSK) == 0 && g_dictDSKs["OGE2"])
//         {
//             // struct OGE2 buf { };
//             auto buf{ std::make_shared<OGE2>() };
//             queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OGE2", std::static_pointer_cast<Base>(buf)));

//             auto n = sscanf
//             (
//                 lineBuf
//                 , buf->fmtDS
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->GelaendepunktindexChar
//                 , /*    3 */ buf->KulturartReintext
//             );
//             assert(n == 12);

//             /*   2 */ n = sscanf(buf->GelaendepunktindexChar, "%d", &buf->GelaendepunktindexInt); assert(n == 1);
//         }

//     } // for scan SLC file line by line
    upParserGH263->parse();
#endif

#if true

    // statistics
    // statistics
    // statistics

    // std::rewind(upParserGH263->getFP());
    // size_t noOfLines{};
    // // char lineBuf[1024];
    // std::map<std::string, unsigned int> occurrencesDSK{};
    // for (; std::fgets(lineBuf, sizeof lineBuf, upParserGH263->getFP()) != nullptr;)
    // {
    //     char aDSK[4 + 1]{};
    //     // (void)printf("%s", lineBuf);
    //     int n{ sscanf(lineBuf, "%4s\n", aDSK) };
    //     // (void)printf("%s\n", aDSK);

    //     occurrencesDSK[aDSK]++;

    //     noOfLines++;
    // }

    // for (auto const& item : occurrencesDSK)
    // {
    //     (void)printf
    //     (
    //         "%s : %4u\n"
    //         , item.first.c_str()
    //         , item.second
    //     );
    // }
    // size_t greens{};
    // for (auto const& item : g_arr_dsks)
    // {
    //     if (item.req)
    //     {
    //         greens++;
    //     }
    // }
    // (void)printf("\nCount documented DSKs == %zd\n", g_arr_dsks.size());
    // (void)printf("\nCount green DSKs == %zd\n", greens);
    // (void)printf("\nCount different DSKs  == %zd\n", occurrencesDSK.size());
    // (void)printf("\nNo of lines .SLC      == %zd\n", noOfLines);

    // (void)printf("\n");
    upParserGH263->statistics();
#endif

    // fclose(upParserGH263->getFP());

#if true
    // Process queue
    // Process queue
    // Process queue

    // std::queue<std::pair<std::string, std::shared_ptr<Base>>> queueDSKs;
    // queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFO", std::static_pointer_cast<Base>(std::make_shared<INFO>())));
    // queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFO", std::static_pointer_cast<Base>(std::make_shared<INFO>("INFO", "A", "B", 55))));
    // queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFS", std::static_pointer_cast<Base>(std::make_shared<INFS>())));
    // queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("PARS", std::static_pointer_cast<Base>(std::make_shared<PARS>())));
    // queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("BEAR", std::static_pointer_cast<Base>(std::make_shared<BEAR>())));
//     for (;!queueDSKs.empty();)
//     {
// #if !defined(NDEBUG) // if not defined release mode, print
//         auto ds{ queueDSKs.front() };
//         auto aDSK{ ds.first.c_str() };
//         printf("==> %s\n", aDSK);
//         auto buf = std::static_pointer_cast<INFO>(ds.second);

//         if (std::strcmp("INFO", aDSK) == 0 && g_dictDSKs["INFO"])
//         {
//             auto buf = std::static_pointer_cast<INFO>(ds.second);

//             (void)printf
//             (
//                 /*    */ buf->fmtPrintf
//                 /* 1 */, buf->DSK
//                 /* 2 */, buf->KZProgram
//                 /* 3 */, buf->LetzeAenderung
//                 /* 4 */, buf->BerechnungsModus
//             );
//         }
//         else if (std::strcmp("BEAR", aDSK) == 0 && g_dictDSKs["BEAR"])
//         {
//             auto buf = std::static_pointer_cast<BEAR>(ds.second);

//             printf("\ntype : %s\n\n", boost::core::demangle(typeid(buf).name()).c_str());

//             (void)printf
//             (
//                 /*    */ buf->fmtPrintf
//                 /* 1 */, buf->DSK
//                 /* 2 */, buf->Bearbeiter
//             );
//         }
//         else if (std::strcmp("KOMM", aDSK) == 0 && g_dictDSKs["KOMM"])
//         {
//             auto buf = std::static_pointer_cast<KOMM>(ds.second);

//             (void)printf
//             (
//                 /*    */ buf->fmtPrintf
//                 /* 1 */, buf->DSK
//                 /* 2 */, buf->Kommentartext
//             );
//         }
//         else if (std::strcmp("PAR1", aDSK) == 0 && g_dictDSKs["PAR1"])
//         {
//             auto buf = std::static_pointer_cast<PAR1>(ds.second);

//             (void)printf
//             (
//                 /*      */ buf->fmtPrintf
//                 /*   1 */, buf->DSK
//                 /*   2 */, buf->SpezEigGewichtFloat
//                 /*   3 */, buf->UmrechnungsfaktorFloat
//                 /*   4 */, buf->ReckwertFloat
//                 /*   5 */, buf->BerechnungEI
//                 /*   6 */, buf->Berechnungsvorschrift
//                 /*   7 */, buf->BerechnungEM
//                 /*   8 */, buf->Seilkriechen
//                 /*   9 */, buf->Seilausschwingwinkel
//                 /*  10 */, buf->Ausgangsspannung
//                 /*  11 */, buf->Reduzierung
//                 /*  12 */, buf->Hoehenausgaben
//                 /*  13 */, buf->Trassierungsrichtlinie
//                 /*  14 */, buf->Windgesetz
//                 /*  15 */, buf->Phasenabstaende
//                 /*  16 */, buf->Sprache
//                 /*  17 */, buf->Mittelzugspannung
//                 /*  18 */, buf->LogDateiYN

//             );
//         }
//         else if (std::strcmp("ZSTD", aDSK) == 0 && g_dictDSKs["ZSTD"])
//         {
//             auto buf = std::static_pointer_cast<ZSTD>(ds.second);

//             (void)printf
//             (
//                 /*       */buf->fmtPrintf
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->ZustandsindexInt
//                 , /*  3 */ buf->TemperaturCInt
//                 , /*  4 */ buf->Konstante
//                 , /*  5 */ buf->Zustandsbezeichnung
//                 , /*  6 */ buf->KennungAusgangszustand
//                 , /*  7 */ buf->KennungGrenzlast
//                 , /*  8 */ buf->KennungUngleicheEislast
//                 , /*  9 */ buf->KennungKettenausschwingwinkels
//                 , /* 10 */ buf->KennungZusatzlast
//                 , /* 11 */ buf->KennungEiswalze
//                 , /* 12 */ buf->LastfaktorFloat
//                 , /* 13 */ buf->WindlastfaktorFloat
//                 , /* 14 */ buf->ReckwertFloat
//                 , /* 15 */ buf->AusnahmelastFloat
//                 , /* 16 */ buf->Temperaturzuschlag
//                 , /* 17 */ buf->GrenzlastBerechnung

//             );
//         }
//         else if (std::strcmp("SLG1", aDSK) == 0 && g_dictDSKs["SLG1"])
//         {
//             auto buf = std::static_pointer_cast<SLG1>(ds.second);
//             (void)printf
//             (
//                 /*       */buf->fmtPrintf
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->SeilindexInt
//                 , /*  3 */ buf->Seilbezeichnung
//                 , /*  4 */ buf->SpannungsebeneInt
//                 , /*  5 */ buf->AnzahlTeilleiterInt
//                 , /*  6 */ buf->Buendelanordnung
//                 , /*  7 */ buf->TeilleiterabstandFloat
//                 , /*  8 */ buf->Seiltyp
//                 , /*  9 */ buf->TemperaturdifferenzSeilkriechenFloat
//                 , /* 10 */ buf->KriechfaktorFloat
//                 , /* 11 */ buf->UeberziehfaktorFloat
//                 , /* 12 */ buf->KriechzeitFloat
//                 , /* 13 */ buf->Kennung_EN_Seil
//                 , /* 14 */ buf->KennungSeilmanuellEingefuegt
//                 , /* 15 */ buf->Isolationsar
//                 , /* 16 */ buf->VorzeichenTemperaturdifferenz
//                 , /* 17 */ buf->VorzeichenKriechfaktor
//             );
//         }
//         else if (std::strcmp("SLG2", aDSK) == 0 && g_dictDSKs["SLG2"])
//         {
//             auto buf = std::static_pointer_cast<SLG2>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->SeilindexInt
//                 , /*  3 */ buf->SeildurchmesserFloat
//                 , /*  4 */ buf->SeilquerschnittFloat
//                 , /*  5 */ buf->E_ModulFloat
//                 , /*  6 */ buf->AusdehnungskoeffizientFloat
//                 , /*  7 */ buf->SpezSeilgewichtFloat
//                 , /*  8 */ buf->NormaleZusatzlastFloat
//                 , /*  9 */ buf->AerodynamischerKraftbeiwertFloat
//                 , /* 10 */ buf->SeilgewichtDBFloat
//                 , /* 11 */ buf->FettmasseFloat
//                 , /* 12 */ buf->KennungQLK

//             );
//         }
//         else if (std::strcmp("SLG3", aDSK) == 0 && g_dictDSKs["SLG3"])
//         {
//             auto buf = std::static_pointer_cast<SLG3>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*  1 */ buf->DSK
//                 , /*  2 */ buf->SeilindexInt
//                 , /*  3 */ buf->HoechstzugspannungFloat
//                 , /*  4 */ buf->MittelzugspannungFloat
//                 , /*  5 */ buf->DauerzugspannungFloat
//                 , /*  6 */ buf->BruchkraftFloat
//                 , /*  7 */ buf->StahlgewichtsanteilFloat
//                 , /*  8 */ buf->StahlquerschnittFloat
//             );
//         }
//         else if (std::strcmp("MAST", aDSK) == 0 && g_dictDSKs["MAST"])
//         {
//             auto buf = std::static_pointer_cast<MAST>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->MastindexInt
//                 , /*   3 */ buf->MastnummerMastname_1
//                 , /*   4 */ buf->Masttyp
//                 , /*   5 */ buf->Masttypenbezeichnung_1
//                 , /*   6 */ buf->AusfuehrungFloat
//                 , /*   7 */ buf->LaengenstationMaststandortFloat
//                 , /*   8 */ buf->HoeheMastfusspunktFloat
//                 , /*   9 */ buf->LeitungswinkelFloat
//                 , /*  10 */ buf->StellwinkelFloat
//                 , /*  11 */ buf->Masttypenbezeichnung_2
//                 , /*  12 */ buf->OrdinateMaststandortFloat
//                 , /*  13 */ buf->MastnummerMastname_2
//             );
//         }
//         else if (std::strcmp("TRAV", aDSK) == 0 && g_dictDSKs["TRAV"])
//         {
//             auto buf = std::static_pointer_cast<TRAV>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->MastindexInt
//                 , /*   3 */ buf->PhasenindexInt
//                 , /*   4 */ buf->TraversenhoeheFloat
//                 , /*   5 */ buf->AusladungFloat
//                 , /*   6 */ buf->StellwinkelTraverseFloat
//                 , /*   7 */ buf->KettenlaengeFloat
//                 , /*   8 */ buf->KettenindexInt
//                 , /*   9 */ buf->HoehenbezugStaudruckFloat
//                 , /*  10 */ buf->TraversenexzentrizitaetFloat
//             );
//         }
//         else if (std::strcmp("KET1", aDSK) == 0 && g_dictDSKs["KET1"])
//         {
//             auto buf = std::static_pointer_cast<KET1>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KettenindexInt
//                 , /*   3 */ buf->Kettentyp
//                 , /*   4 */ buf->AnzahlKettenstraengeInt
//                 , /*   5 */ buf->Kettentypbezeichnung
//                 , /*   6 */ buf->KettenbezeichnungIsolator
//                 , /*   7 */ buf->Schwingenbezeichnung
// #ifdef FIRM_FLP
//                 , /*   8 */ buf->Kettennummer
// #endif
//             );
//         }
//         else if (std::strcmp("KET2", aDSK) == 0 && g_dictDSKs["KET2"])
//         {
//             auto buf = std::static_pointer_cast<KET2>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KettenindexInt
//                 , /*   3 */ buf->KettenlaengeFloat
//                 , /*   4 */ buf->VLaengeFloat
//                 , /*   5 */ buf->FesteLaengeFloat
//                 , /*   6 */ buf->SchwingenlaengeFloat
//                 , /*   7 */ buf->KettengewichtFloat
//                 , /*   8 */ buf->EinfachesEisgewichtKetteFloat
//                 , /*   9 */ buf->SchwingengewichtFloat
//                 , /*  10 */ buf->GrenzausschwingwinkelInnenFloat
//                 , /*  11 */ buf->GrenzausschwingwinkelAuszenFloat
//                 , /*  12 */ buf->ZusatzgewichtFloat
//                 , /*  13 */ buf->EinbaulaengeFloat
//                 , /*  14 */ buf->SchirmdurchmesserFloat
//                 , /*  15 */ buf->StrunkdurchmesserFloat
//                 , /*  16 */ buf->ProjizierteFlaecheFloat
//                 , /*  17 */ buf->VKetteVersatzAufhaengungMastInnenFloat
//                 , /*  18 */ buf->VKetteVersatzAufhaengungMastAussenFloat
//             );
//         }
//         else if (std::strcmp("EZLA", aDSK) == 0 && g_dictDSKs["EZLA"])
//         {
//             auto buf = std::static_pointer_cast<EZLA>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->LastindexInd
//                 , /*   3 */ buf->PhasenindexInt
//                 , /*   4 */ buf->MastindexLinkerMastInt
//                 , /*   5 */ buf->Lasttyp
//                 , /*   6 */ buf->KennungLastEndzustand
//                 , /*   7 */ buf->KennungLastMontagezustand
//                 , /*   8 */ buf->KennungLastRollenzustand
//                 , /*   9 */ buf->ZustandsindexInt
//                 , /*  10 */ buf->AnzahlLastenInt
//                 , /*  11 */ buf->StationLinkerMastFloat
//                 , /*  12 */ buf->AbstandLastenEndestationFloat
//                 , /*  13 */ buf->LastFloat
//                 , /*  14 */ buf->EinfacheEislastFloat
//             );
//         }
//         else if (std::strcmp("SLK1", aDSK) == 0 && g_dictDSKs["SLK1"])
//         {
//             auto buf = std::static_pointer_cast<SLK1>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->SeilkurvenindexInt
//                 , /*   3 */ buf->PhasenindexInt
//                 , /*   4 */ buf->ZustandsindexInt
//                 , /*   5 */ buf->MastindexLinkerMastInt
//                 , /*   6 */ buf->MastindexRechterMastInt
//                 , /*   7 */ buf->StationSeilaufhaengepunktLinksFloat
//                 , /*   8 */ buf->HoeheSeilaufhaengepunktLinksFloat
//                 , /*   9 */ buf->OrdinateSeilaufhaengepunktFloat
//                 , /*  10 */ buf->StationSeilaufhaengepunktRechtsFloat
//                 , /*  11 */ buf->HoeheSeilaufhaengepunktRechtsFloat
//                 , /*  12 */ buf->OrdinateSeilaufhaengepunktRechtsFloat
//                 , /*  13 */ buf->StationSeilaufhaengepunktLinksTransformFloat
//                 , /*  14 */ buf->OrdinateSeilaufhaengepunktLinksFloat
//                 , /*  15 */ buf->StationSeilaufhaengepunktRechtsTransformFloat
//                 , /*  16 */ buf->OrdinateSeilaufhaengepunktRechtsTransformFloat
//             );
//         }
//         else if (std::strcmp("SLK2", aDSK) == 0 && g_dictDSKs["SLK2"])
//         {
//             auto buf = std::static_pointer_cast<SLK2>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->SeilkurvenindexInt
//                 , /*   3 */ buf->SeilspannungEndzustandFloat
//                 , /*   4 */ buf->SeilgewichtEndzustandFloat
//                 , /*   5 */ buf->SeilausschwingwinkelFloat
//                 , /*   6 */ buf->DurchhangFeldmitteFloat
//                 , /*   7 */ buf->StationSeilpunktFeldmitteFloat
//                 , /*   8 */ buf->HoeheSeilpunktFeldmitteFloat
//                 , /*   9 */ buf->OrdinateSeilpunktFeldmitteFloat
//                 , /*  10 */ buf->TiefsterPunktFeldmitte
//                 , /*  11 */ buf->GroeszterDurchhangFeld
//                 , /*  12 */ buf->GewichtsspannweiteFloat
//                 , /*  13 */ buf->BogenlaengeSeilFloat
//                 , /*  14 */ buf->ScheitelpunktEntfernungLinkerMastFloat
//                 , /*  15 */ buf->ScheitelpunktSeilhoeheFloat
//                 , /*  16 */ buf->SeilspannungAbsolutAufhaengepunktLinksFloat
//                 , /*  17 */ buf->SeilspannungAbsolutAufhaengepunktRechtsFloat
//             );
//         }
//         else if (std::strcmp("SLK3", aDSK) == 0 && g_dictDSKs["SLK3"])
//         {
//             auto buf = std::static_pointer_cast<SLK3>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->SeilkurvenindexInt
//                 , /*   3 */ buf->KettenauslenkungLinkerMastInLeitungsrichtungFloat
//                 , /*   4 */ buf->KettenauslenkungLinkerMastQuerLeitungsrichtungFloat
//                 , /*   5 */ buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungFloat
//                 , /*   6 */ buf->KettenauslenkungRechterMastInLeitungsrichtungFloat
//                 , /*   7 */ buf->KettenauslenkungRechterMastQuerLeitungsrichtungFloat
//                 , /*   8 */ buf->KettenauslenkungRechterMastVertikalLeitungsrichtungFloat
//                 , /*   9 */ buf->SeilzugLinksFloat
//                 , /*  10 */ buf->SeilzugRechtsFloat
//             );
//         }
//         else if (std::strcmp("OBJ1", aDSK) == 0 && g_dictDSKs["OBJ1"])
//         {
//             auto buf = std::static_pointer_cast<OBJ1>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KreuzungsobjektindexTeil_1_Int
//                 , /*   3 */ buf->Objektnummer
//                 , /*   4 */ buf->MindestabstandFloat
//                 , /*   5 */ buf->NachweiscodeInt
//                 , /*   6 */ buf->Abstandstyp
//                 , /*   7 */ buf->Nachweiszustaende
//                 , /*   8 */ buf->MastindexInt
//                 , /*   9 */ buf->PhasenindexInt
//                 , /*  10 */ buf->Objekttyp
//                 , /*  11 */ buf->SteuerungsparameterDruckausgabe
//                 , /*  12 */ buf->ParameterLeitungskreuzungen
//                 , /*  13 */ buf->NeuerObjekttyp
//                 , /*  14 */ buf->Objektabstand
//                 , /*  15 */ buf->ObjektRechnen
//                 , /*  16 */ buf->KreuzungsobjektindexTeil_2_Int
//                 , /*  17 */ buf->Mindestabstand110kVFloat
//             );
//         }
//         else if (std::strcmp("OBJ2", aDSK) == 0 && g_dictDSKs["OBJ2"])
//         {
//             auto buf = std::static_pointer_cast<OBJ2>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KreuzungsobjektindexTeil_1_Int
//                 , /*   3 */ buf->ObjektbezeichnungZeile_1
//                 , /*   4 */ buf->ObjektbezeichnungZeile_2
//                 , /*   5 */ buf->KreuzungsobjektindexTeil_2_Int
//             );
//         }
//         else if (std::strcmp("OBJ3", aDSK) == 0 && g_dictDSKs["OBJ3"])
//         {
//             auto buf = std::static_pointer_cast<OBJ3>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*   1 */ buf->DSK
//                 , /*   2 */ buf->KreuzungsobjektindexTeil_1_Int
//                 , /*   3 */ buf->EigentümerZeile_1
//                 , /*   4 */ buf->EigentümerZeile_2
//                 , /*   5 */ buf->KreuzungsobjektindexTeil_2_Int
//             );
//         }
//         else if (std::strcmp("OPKT", aDSK) == 0 && g_dictDSKs["OPKT"])
//         {
//             auto buf = std::static_pointer_cast<OPKT>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->PunktindexTeil_1_Int
//                 , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Int
//                 , /*    4 */ buf->StationFloat
//                 , /*    5 */ buf->OrdinateFloat
//                 , /*    6 */ buf->FuszhoeheFloat
//                 , /*    7 */ buf->ObjekthoeheFloat
//                 , /*    8 */ buf->PunktnummerVermessung
//                 , /*    9 */ buf->Punktindex_Teil_2_Int
// #ifdef FLP
//                 , /*   10 */ buf->MS_LinkInt
// #endif
//                 , /*   11 */ buf->KreuzungsobjektindexTeil_2_Int);
//         }
//         else if (std::strcmp("OLIN", aDSK) == 0 && g_dictDSKs["OLIN"])
//         {
//             auto buf = std::static_pointer_cast<OLIN>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->LinienindexTeil_1_Int
//                 , /*    3 */ buf->KreuzungsobjektindexTeil_1_Int
//                 , /*    4 */ buf->IndexAnfangspunkt_1_Teil_1_Int
//                 , /*    5 */ buf->Index_Endpunkt_1_Teil_1_Int
//                 , /*    6 */ buf->Index_Anfangspunkt_2_Teil_2_Int
//                 , /*    7 */ buf->IndexEndpunkt_2_Teil_2_Int
// #ifdef FLP
//                 , /*    8 */ buf->MS_LinkInt
// #endif
//                 , /*    9 */ buf->Linienindex_Teil_2_Int
//                 , /*   10 */ buf->Kreuzungsobjektindex_Teil_2_Char
//             );
//         }
//         else if (std::strcmp("OBFL", aDSK) == 0 && g_dictDSKs["OBFL"])
//         {
//             auto buf = std::static_pointer_cast<OBFL>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->Flaechenindex_Teil_1_Int
//                 , /*    3 */ buf->KreuzungsobjektindexTeil_1_Int
//                 , /*    4 */ buf->Punktindex_1_Teil_1_Int
//                 , /*    5 */ buf->Punktindex_2_Teil_1_Int
//                 , /*    6 */ buf->Punktindex_3_Teil_1_Int
//                 , /*    7 */ buf->Punktindex_4_Teil_1_Int
//                 , /*    8 */ buf->Punktindex_1_Teil_2_Int
//                 , /*    9 */ buf->Punktindex_2_Teil_2_Int
//                 , /*   10 */ buf->Punktindex_3_Teil_2_Int
//                 , /*   11 */ buf->Punktindex_4_Teil_2_Int
// #ifdef FLP
//                 , /*   12 */ buf->MS_Link_Int
// #endif
//                 , /*   13 */ buf->Flaechenindex_Teil_2_Int, /*   14 */ buf->Kreuzungsobjektindex_Teil_2_Int);
//         }
//         else if (std::strcmp("OGEL", aDSK) == 0 && g_dictDSKs["OGEL"])
//         {
//             auto buf = std::static_pointer_cast<OGEL>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->Gelaendepunktindex_Teil_1_Int
//                 , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Int
//                 , /*    4 */ buf->StationFloat
//                 , /*    5 */ buf->GelaendehoeheTrassenmitteFloat
//                 , /*    6 */ buf->OrdinateSeitlichUeberhoehung_1_Float
//                 , /*    7 */ buf->SeitlicheUeberhoehung_1_Float
//                 , /*    8 */ buf->OrdinateSeitlicheUeberhoehung_2_Float
//                 , /*    9 */ buf->SeitlicheUeberhoehung_2_Float
//                 , /*   10 */ buf->Gelaendepunktindex_Teil_2_Int
//                 , /*   11 */ buf->KulturartCode, /*   12 */ buf->KreuzungsobjektindexTeil_2_Int
//             );
//         }
//         else if (std::strcmp("OGE2", aDSK) == 0 && g_dictDSKs["OGE2"])
//         {
//             auto buf = std::static_pointer_cast<OGE2>(ds.second);

//             (void)printf
//             (
//                 buf->fmtPrintf
//                 , /*    1 */ buf->DSK
//                 , /*    2 */ buf->GelaendepunktindexInt
//                 , /*    3 */ buf->KulturartReintext
//             );
//         }
// #endif

    //     queueDSKs.pop();
    // }
#endif

    upParserGH263->printRecordsOnConsole();   

    return 0;
}

#endif
