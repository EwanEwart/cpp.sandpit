#if false

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cmath>
#include <limits>
#include <iostream>
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
    printf("String    = %ls\n", s);
    printf("Character = %c\n", c);
    printf("Integer:  = %ld\n", i);
    printf("Real:     = %lf\n", fp);

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
    printf("%d\n", ++s.b); // output: 0
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
    printf("%zu bytes\n", sizeof(struct S)); // usually prints 4
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

#include <cstdio>
#include <string>
#include <locale.h>
#include "GH262.h"

int main(int argc, char const* argv[])
{
    setlocale(LC_CTYPE, "German.1252");
    setlocale(LC_NUMERIC, "en_US.1252");
    // setlocale(LC_ALL, "de_DE.UTF8"); // ... fourth commit



    char* path{ "E:/dev/cpp.sandpit/Muster_024A-027A.SLC" };

    auto fp{ std::fopen(path,"r") };
    if (!fp)
    {
        std::fprintf(stderr, "%s : %d : File opening failed.\n", __FILE__, __LINE__);
        return -1;
    }

    size_t noOfLines{};
    char lineBuf[1024];
    std::map<std::string, unsigned int> occurrencesDSK{};
    for (;std::fgets(lineBuf, sizeof lineBuf, fp) != nullptr;)
    {
        char aDSK[4 + 1]{};
        // printf("%s", lineBuf);
        int n{ sscanf(lineBuf,"%4s\n",aDSK) };
        // printf("%s\n", aDSK);

        occurrencesDSK[aDSK]++;

        noOfLines++;

    }

#if true
    // dynamic DSKs <-- .slc
    // dynamic DSKs <-- .slc
    // dynamic DSKs <-- .slc
    char ruler[]{ "-234567890-234567890-234567890-234567890-234567890-234567890-234567890-234567890-234567890\n" };
    std::rewind(fp);
    for (;std::fgets(lineBuf, sizeof lineBuf, fp) != nullptr;)
    {
        char aDSK[5]{};

        int n{ sscanf(lineBuf,"%4s\n",aDSK) };

        if (std::strcmp("INFO", aDSK) == 0 && g_dictDSKs["INFO"])
        {
            struct INFO buf {};
            char const* fmt{ "%4c%*2c%25c%38c%4d" };
            auto n = sscanf
            (
                /*   */  lineBuf
                /*   */, fmt
                /* 1 */, buf.DSK
                /* 2 */, buf.KZProgram
                /* 3 */, buf.LetzeAenderung
                /* 4 */, &buf.BerechnungsModus
            );
            assert(n == 4);

            fputs(ruler, stdout);
            char const* fmt2{ "%s|\n%s|\n%s|\n%d|\n" };
            printf
            (
                /*   */  fmt2
                /* 1 */, buf.DSK
                /* 2 */, buf.KZProgram
                /* 3 */, buf.LetzeAenderung
                /* 4 */, buf.BerechnungsModus
            );
        }
        else if (std::strcmp("BEAR", aDSK) == 0 && g_dictDSKs["BEAR"])
        {
            struct BEAR buf {};
            char const* fmt{ "%4c%*2c%28c" };
            auto n = sscanf(
                /*   */  lineBuf
                /*   */, fmt
                /* 1 */, buf.DSK
                /* 2 */, buf.Bearbeiter
            );
            assert(n == 2);

            fputs(ruler, stdout);
            char const* fmt2{ "%s|\n%s|\n" };
            printf
            (
                /*   */  fmt2
                /* 1 */, buf.DSK
                /* 2 */, buf.Bearbeiter
            );
        }
        else if (std::strcmp("KOMM", aDSK) == 0 && g_dictDSKs["INFO"])
        {
            struct KOMM buf {};
            char const* fmt{ "%4s%2ss%28s%1024s" };
            auto n = sscanf(
                /*   */  lineBuf
                /*   */, fmt
                /* 1 */, buf.DSK
                /* 2 */, buf.Kommentartext
            );
            assert(n == 2);

            char const* fmt2{ "\n%4s|\n%1024s|\n" };
            printf
            (
                /*   */  fmt2
                /* 1 */, buf.DSK
                /* 2 */, buf.Kommentartext
            );
        }
        else if (std::strcmp("PAR1", aDSK) == 0 && g_dictDSKs["PAR1"])
        {
            struct PAR1 buf {};
            char const* fmt{ "%4c%*2c%6c%6c%6c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c" };
            auto n = sscanf(
                /*     */  lineBuf
                /*     */, fmt
                /*   1 */, buf.DSK
                /*   2 */, buf.SpezEigGewichtChar
                /*   3 */, buf.UmrechnungsfaktorChar
                /*   4 */, buf.ReckwertChar
                /*   5 */, buf.BerechnungEI
                /*   6 */, buf.Berechnungsvorschrift
                /*   7 */, buf.BerechnungEM
                /*   8 */, buf.Seilkriechen
                /*   9 */, buf.Seilausschwingwinkel
                /*  10 */, buf.Ausgangsspannung
                /*  11 */, buf.Reduzierung
                /*  12 */, buf.Hoehenausgaben
                /*  13 */, buf.Trassierungsrichtlinie
                /*  14 */, buf.Windgesetz
                /*  15 */, buf.Phasenabstaende
                /*  16 */, buf.Sprache
                /*  17 */, buf.Mittelzugspannung
                /*  18 */, buf.LogDateiYN
            );
            assert(n == 18);

            n = sscanf(buf.SpezEigGewichtChar, "%f", &buf.SpezEigGewichtFloat);
            assert(n == 1);
            n = sscanf(buf.UmrechnungsfaktorChar, "%f", &buf.UmrechnungsfaktorFloat);
            assert(n == 1);
            n = sscanf(buf.ReckwertChar, "%f", &buf.ReckwertFloat);
            if (n != 1)
            {
                buf.ReckwertFloat = 0.0f;
            }


            char const* fmt2{ "\n%s|\n%6.0f|\n%6.2f|\n%6.2f|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n" };
            printf
            (
                /*     */  fmt2
                /*   1 */, buf.DSK
                /*   2 */, buf.SpezEigGewichtFloat
                /*   3 */, buf.UmrechnungsfaktorFloat
                /*   4 */, buf.ReckwertFloat
                /*   5 */, buf.BerechnungEI
                /*   6 */, buf.Berechnungsvorschrift
                /*   7 */, buf.BerechnungEM
                /*   8 */, buf.Seilkriechen
                /*   9 */, buf.Seilausschwingwinkel
                /*  10 */, buf.Ausgangsspannung
                /*  11 */, buf.Reduzierung
                /*  12 */, buf.Hoehenausgaben
                /*  13 */, buf.Trassierungsrichtlinie
                /*  14 */, buf.Windgesetz
                /*  15 */, buf.Phasenabstaende
                /*  16 */, buf.Sprache
                /*  17 */, buf.Mittelzugspannung
                /*  18 */, buf.LogDateiYN

            );
        }
        else if (std::strcmp("ZSTD", aDSK) == 0 && g_dictDSKs["ZSTD"])
        {
            struct ZSTD buf {};
            char const* fmt{ "%4c%*2c%3c%3c%2c%20c%1c%1c%1c%1c%1c%1c%*4c%6c%6c%6c%6c%*1c%1c%1c" };
            auto n = sscanf(
                lineBuf
                , fmt
                , /*  1 */ buf.DSK
                , /*  2 */ buf.ZustandsindexChar
                , /*  3 */ buf.TemperaturCChar
                , /*  4 */ buf.Konstante
                , /*  5 */ buf.Zustandsbezeichnung
                , /*  6 */ buf.KennungAusgangszustand
                , /*  7 */ buf.KennungGrenzlast
                , /*  8 */ buf.KennungUngleicheEislast
                , /*  9 */ buf.KennungKettenausschwingwinkels
                , /* 10 */ buf.KennungZusatzlast
                , /* 11 */ buf.KennungEiswalze
                , /* 12 */ buf.LastfaktorChar
                , /* 13 */ buf.WindlastfaktorChar
                , /* 14 */ buf.ReckwertChar
                , /* 15 */ buf.AusnahmelastChar
                , /* 16 */ buf.Temperaturzuschlag
                , /* 17 */ buf.GrenzlastBerechnung
            );
            assert(n == 17);
            n = sscanf(buf.ZustandsindexChar, "%d", &buf.ZustandsindexInt);assert(n == 1);
            n = sscanf(buf.TemperaturCChar, "%d", &buf.TemperaturCInt);assert(n == 1);
            n = sscanf(buf.LastfaktorChar, "%f", &buf.LastfaktorFloat);assert(n == 1);
            n = sscanf(buf.WindlastfaktorChar, "%f", &buf.WindlastfaktorFloat);assert(n == 1);
            n = sscanf(buf.ReckwertChar, "%f", &buf.ReckwertFloat);assert(n == 1);
            n = sscanf(buf.AusnahmelastChar, "%f", &buf.AusnahmelastFloat);assert(n == 1);
            char const* fmt2{ "\n%s|\n%d|\n%d|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%6.3f|\n%6.3f|\n%6.2f|\n%6.2f|\n%s|\n%s|\n" };
            printf
            (
                fmt2
                , /*  1 */ buf.DSK
                , /*  2 */ buf.ZustandsindexInt
                , /*  3 */ buf.TemperaturCInt
                , /*  4 */ buf.Konstante
                , /*  5 */ buf.Zustandsbezeichnung
                , /*  6 */ buf.KennungAusgangszustand
                , /*  7 */ buf.KennungGrenzlast
                , /*  8 */ buf.KennungUngleicheEislast
                , /*  9 */ buf.KennungKettenausschwingwinkels
                , /* 10 */ buf.KennungZusatzlast
                , /* 11 */ buf.KennungEiswalze
                , /* 12 */ buf.LastfaktorFloat
                , /* 13 */ buf.WindlastfaktorFloat
                , /* 14 */ buf.ReckwertFloat
                , /* 15 */ buf.AusnahmelastFloat
                , /* 16 */ buf.Temperaturzuschlag
                , /* 17 */ buf.GrenzlastBerechnung

            );
        }

    }
#endif


    fclose(fp);

#if false

    // statistics
    // statistics
    // statistics

    for (auto const& item : occurrencesDSK)
    {
        printf
        (
            "%s : %4u\n"
            , item.first.c_str()
            , item.second
        );
    }
    size_t greens{};
    for (auto const& item : dsks)
    {
        if (item.req)
        {
            greens++;
        }
    }
    printf("\nCount documented DSKs == %zd\n", dsks.size());
    printf("\nCount green DSKs == %zd\n", greens);
    printf("\nCount different DSKs  == %zd\n", occurrencesDSK.size());
    printf("\nNo of lines .SLC      == %zd\n", noOfLines);

    printf("\n");
#endif

#if false
    // queue static DSKs 
    // queue static DSKs 
    // queue static DSKs 
    std::queue<std::pair<std::string, std::shared_ptr<Base>>> queueDSKs;
    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFO", std::static_pointer_cast<Base>(std::make_shared<INFO>())));
    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFO", std::static_pointer_cast<Base>(std::make_shared<INFO>("INFO", "A", "B", 55))));
    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFS", std::static_pointer_cast<Base>(std::make_shared<INFS>())));
    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("PARS", std::static_pointer_cast<Base>(std::make_shared<PARS>())));
    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("BEAR", std::static_pointer_cast<Base>(std::make_shared<BEAR>())));
    for (;!queueDSKs.empty();)
    {
        auto dsk{ queueDSKs.front() };
        if (std::strcmp(dsk.first.c_str(), "INFO") == 0)
        {
            auto p = std::static_pointer_cast<INFO>(dsk.second);
            std::cout
                << (dsk.first) << '|' << '\n'
                << (p->DSK) << '|' << '\n'
                << (p->KZProgram) << '|' << '\n'
                << (p->LetzeAenderung) << '|' << '\n'
                << (p->BerechnungsModus) << '|' << '\n'
                << std::endl;
        }
        queueDSKs.pop();
    }
#endif

    return 0;
}

#endif
