#ifndef PARSER_GH263_H
#define PARSER_GH263_H

#include <array>
#include <map>
// #include <locale>
#include <memory>
#include <queue>
#include <tuple>
#include <iostream>
#include <cassert>

namespace cc
{
    namespace parser
    {

    // For C++ 14, because it doesn't exist here; from C++17
    template <typename To, typename From>
    inline std::shared_ptr<To> reinterpret_pointer_cast(
        std::shared_ptr<From> const& ptr) noexcept
    {
        return std::shared_ptr<To>(ptr, reinterpret_cast<To*>(ptr.get()));
    }

    struct DSATTR
    {
        char DSKennung[5]; // DS Kennung ‘INFO'
        bool req;
    };

    struct Base
    {
        int a;
        virtual void f() const { std::cout << "I am base!\n"; }
        virtual ~Base() {}
    };

    // enum DSKS
    // {
    //     INFO
    //     , INFS
    //     , PARS
    //     , BEAR
    //     , TXT1
    //     , TXT2
    //     , KOMM
    //     , PAR1
    //     , PARX
    //     , DINE
    //     , DBSV
    //     , TRRL
    //     , WIND
    //     , ZSTA
    //     , ZSTD
    //     , ZSAN
    //     , DWRE
    //     , SLG1
    //     , SLG2
    //     , SLG3
    //     , DTVG
    //     , PHAS
    //     , PHA2
    //     , PHA4
    //     , PHA5
    //     , PSYS
    //     , PZLF
    //     , HTMP
    //     , TPKT
    //     , HTM2
    //     , MAST
    //     , TRAV
    //     , KET1
    //     , KET2
    //     , ROLL
    //     , WRR1
    //     , WRR2
    //     , SCSV
    //     , PHAV
    //     , DHGM
    //     , EZLA
    //     , NEIG
    //     , ENEI
    //     , ENET
    //     , PATH
    //     , SLK1
    //     , SLK2
    //     , SLK3
    //     , EDHM
    //     , ELST
    //     , ESEH
    //     , SPAN
    //     , DBPD
    //     , EPHA
    //     , EGZU
    //     , EKAP
    //     , EPHF
    //     , OBOP
    //     , OBJ1
    //     , OBJ2
    //     , OBJ3
    //     , OBJA
    //     , OBA1
    //     , OPKT
    //     , OLIN
    //     , OBFL
    //     , OGEL
    //     , OGE2
    //     , OWEA
    //     , OKRZ
    //     , OKN2
    //     , OKN3
    //     , OKRV
    //     , OKSE
    //     , OKS2
    //     , OERG
    //     , OER2
    //     , OEKB
    //     , OMAB
    //     , OMA2
    //     , OEXP
    //     , OEX2
    //     , OPUO
    //     , OPER
    //     , OPIA
    //     , OERI
    //     , OKRA
    //     , OKRK
    //     , OKRS
    //     , OALT
    //     , SCSA
    //     , STAT
    // };
    extern std::array<DSATTR, 92> g_arr_dsks;
    extern std::map<std::string, unsigned int> g_dictDSKs;

    //: INFO: Info Zeile
    // Erste Zeile der Datei. Bei allen anderen Daten ist die Reihenfolge frei.
    struct INFO : Base
    {
        char const* fmtDS{ "%4c%*2c%25c%38c%4d" };
        char const* fmtPrintf{ "%s|\n%s|\n%s|\n%d|\n" };

        /*  1 -  4 =  4 */ std::string DSK;            // Datensatz Kennung ‘INFO'
        /*  7 - 31 = 25 */ std::string KZProgram;      // Kennung erzeugendes Programm/Version
        /* 32 - 69 = 38 */ std::string LetzeAenderung; // Datum/Uhrzeit letzte Änderung durch Programm
        /* 70 - 73 =  4 */ int BerechnungsModus;       // Kennung spezieller Berechnungsmodus: '0' oder fehlend(' ') : Standard / konventionell 1 : Berechnung Spanntabellen für Ausland/Export ? Braucht man noch?
        INFO() 
        : DSK{ "" }
        , KZProgram{ "" }
        , LetzeAenderung{ "" }
        , BerechnungsModus{ 0 }
        {
        }
        INFO
        (
            std::string DSK
            , std::string KZProgram
            , std::string LetzeAenderung
            , int BerechnungsModus
        )
        : DSK(DSK)
        , KZProgram(KZProgram)
        , LetzeAenderung(LetzeAenderung)
        , BerechnungsModus(BerechnungsModus
        )
        {
        }
        virtual ~INFO() {};
    };

    //: INFS: Info-Zeile slc (nur in slc-Datei enthalten)
    // *** Neu ab Version 3.7.4 ***
    struct INFS : Base
    {
        /*  1 -  4 =  4 */ std::string DSK;                   // Datensatzkennung INFS
        /*  7 - 22 = 16 */ std::string DatZeitProgrAend;      // Datum/Uhrzeit letzte Änderung durch Programm (Format tag.monat.jahr stunde:minute)
        /* 24 - 39 = 16 */ std::string DatZeit263EingDatAend; // Datum/Uhrzeit 263-Eingabedatei (Format tag.monat.jahr stunde:minute)
        INFS() 
        : DSK{}
        , DatZeitProgrAend{}
        , DatZeit263EingDatAend{}
        {
        }
        virtual ~INFS() {}
    };
    //: PARS: Aufrufparameter (nur in slc-Datei enthalten)
    // *** Neu ab Version 3.7.5 ***
    struct PARS : Base
    {
        /* 1 -  4 */ char DSK[4 + 1];                // DatenSatzKennung PARS
        /* 7 - 26 */ char ParmAufrufBerKern[20 + 1]; // Parameter aus Aufruf Berechnungskern (z.B. KSOC)

        virtual ~PARS() {}
    };

    //: BEAR: Bearbeiter   +++
    struct BEAR : Base
    {
        char const* fmtDS{ "%4c%*2c%28c" };
        char const* fmtPrintf{ "%s|\n%s|\n" };

        /* 1 -  4 */ char DSK[4 + 1]; // Datensatzkennung ‘BEAR’
        /* 7 - 34 */ char Bearbeiter[28 + 1];

        virtual ~BEAR() {}
    };

    //: "TXT1", TXT2: Leitung Allgemein, Beschreibung
    struct TXT1 : Base
    {
        /*  1 -  4 */ char DSK[4 + 1];                      // Satzkennung ‘TXT1’
        /*  7 - 34 */ char Leitung1[28 + 1];                // Leitung (1.Zeile)
        /* 35 - 62 */ char Leitung2[28 + 1];                // Leitung (2.Zeile)
        /* 63 - 68 */ char Leitungsnummer1[6 + 1];          // Leitungsnummer
        /* 69 - 71 */ int Abschnittsnummer;                 // 3 digits, Abschnittsnummer
        //   *** Neu ab V 3.4.10 4 / Win 263 V 2.8.7 ***    //
        /* 73 - 78 */ char Leitungsnummer2[5 + 1];          // Leitungsnummer (Zeichen 7-12, falls vorhanden)
        virtual ~TXT1() {}
    };
    //: TXT1, "TXT2": Leitung Allgemein, Beschreibung
    struct TXT2 : Base
    {
        /* 1 -  4 */ char DSK[4 + 1];           // Satzkennung ‘TXT2’
        /* 7 - 34 */ char Eigentuemer1[28 + 1]; // Eigentümer (1.Zeile)
        /*35 - 62 */ char Eigentuemer2[28 + 1]; // Eigentümer (2.Zeile)
        virtual ~TXT2() {}
    };

    //: KOMM: Kommentarzeilen (nur Oberfläche)  +++
    struct KOMM : Base
    {
        char const* fmtDS{ "%4s%2ss%28s%1024s" };
        char const* fmtPrintf{ "\n%4s|\n%1024s|\n" };

        /* 1 -    4    */ char DSK[4];              // Satzkennung ‘KOMM’
        /* 7 - 1031(*) */ char Kommentartext[1024]; // (*) Kommentartext
        /*
        (*): Es können mehrere (maximal 10) KOMM
        (Wird in Eingabefeld der Oberfläche auch als einzel
        Die Gesamtlänge des Textes aller Zeilen (inklus
        darf aber 1024 nicht ü
        */
        virtual ~KOMM() {}
    };

    //: PAR1: Berechnungseinstellungen, allgemein   +++
    struct PAR1 : Base
    {
        char const* fmtDS{ "%4c%*2c%6c%6c%6c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c" };
        char const* fmtPrintf{ "\n%s|\n%6.0f|\n%6.2f|\n%6.2f|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n" };

        /*  1 -  4  */ char DSK[4 + 1];                     // Satzkennung ‘PAR1’
        /*  7 - 12  */ char SpezEigGewichtChar[6 + 1];      // 6.0   // Spezifisches Eisgewicht [N/m³], (‘7500’)
        /*  7 - 12  */ float SpezEigGewichtFloat;           // 6.0   // Spezifisches Eisgewicht [N/m³], (‘7500’)
        /* 13 - 18  */ char UmrechnungsfaktorChar[6 + 1];   // 6.2   // Umrechnungsfaktor [kg/N], (‘10.00’ bzw. ‘9.81’)
        /* 13 - 18  */ float UmrechnungsfaktorFloat;        // 6.2   // Umrechnungsfaktor [kg/N], (‘10.00’ bzw. ‘9.81’)
        /* 19 - 24  */ char ReckwertChar[6 + 1];            // 6.2   // Reckwert [m], (0=kein Reckwert)
        /* 19 - 24  */ float ReckwertFloat;                 // 6.2   // Reckwert [m], (0=kein Reckwert)
        /* 25 - 25  */ char BerechnungEI[1 + 1];            // Berechnung: E=Exakte,I=Ideell
        /* 26 - 26  */ char Berechnungsvorschrift[1 + 1];   // Berechnungsvorschrift (als Auswahlmenü) 0=Benutzerdefiniert 1= DIN VDE/0210 12.85 2= DIN VDE/0210 5.62 3= TGL (nur Eislast in Oberfläche) 4= DIN EN 50341 03.2002-01.2011 6= DIN VDE/0210 5.69 *** neu ab Version 4.5.1 *** 7= DIN EN 50341 04.2016 *** neu ab Version 4.11.1*** 8= DIN EN 50341 09.2019 *** neu ab Version 4.13.6***
        /* 27 - 27  */ char BerechnungEM[1 + 1];            // Berechnung: E=Endzustände, M=Montagezustände (default ‚E‘)
        // *** Neu ab V4.14.3 : Option „V“ ***              //
        /* 28 -  28 */ char Seilkriechen[1 + 1];            // Seilkriechen: T=Temperaturdifferenz, K=Kriechfaktor, U=Überziehen,Z=Kriechzeit, V=Temperaturdifferenz aus Zeitvorgabe, ' '=kein
        /* 29 -  29 */ char Seilausschwingwinkel[1 + 1];    // Berechnung Seilausschwingwinkel: J=Spannweitenreduktion nach DIN VDE 0210/12 85 N=Keine Spannweitenreduktion (Default ‚J‘)
        /* 30 -  30 */ char Ausgangsspannung[1 + 1];        // Ausgangsspannung : V=Spannungsvorgabe, M=aus Mittelwert der gemessenen Durchhänge U=aus Ungünstigstem gemessenem Durchhang B=aus Vorgabe Bogenlänge 69 *** neu ab Version 4.7.3 *** (Default ‚V‘)
        /* 31 -  31 */ char Reduzierung[1 + 1];             // Reduzierung des Kettenausschwingwinkels nach DIN 85 (Faktor 0.8) ‚N‘=Keine Reduzierung des Kettenausschwingwinkels Sonst= Reduzierung des Kettenausschwingwinkels (Default:‘ ')
        /* 32 -  32 */ char Hoehenausgaben[1 + 1];          // Höhenausgaben in Ergebnisprotokollen in 'NN' bzw. 'HN' 'H'= Ausgabe in 'HN' 'N'= Ausgabe in 'NHN' Sonst= Ausgabe in 'NN' (Default: ' ')
        /* 33-   33 */ char Trassierungsrichtlinie[1 + 1];  // Einschalten einer Trassierungsrichtlinie (Standard: “Seilverlegevorschrift DB 2004" (Objektabstände: Bautoleranz berücksichtigen (siehe 'DBSV'), altern. Temperaturwert bei Zuständen wird ausgewertet.) 'D'= Trassierungsrichtlinie ein, Sonst= Trassierungsrichtlinie aus
        /* 34 -  34 */ char Windgesetz[1 + 1];              // Festlegung Berechnung Windgesetz 'E' = DIN EN 50341 03.02 'T' = TGL 200-0614/20 (Stand September 1987) Sonst : DIN VDE 12.85 (Default: ' ')
        /* 35 -  35 */ char Phasenabstaende[1 + 1];         // Einstellung Berechnung Phasenabstände und Dauerzugprüfung 'E' = DIN EN 50341 03.02 Sonst : DIN VDE 12.85 (Default: ' ')
        /* 36 -  36 */ char Sprache[1 + 1];                 // Einstellung Sprache Ergebnisausgabe: 'E' = Englisch Sonst: deutsch
        // *** Neu ab V4.1.9 ***                            //
        /* 37 - 37  */ char Mittelzugspannung[1 + 1];       // Einstellung Ermittlung Mittelzugspannung bei zeitabhängigem Kriechen: ‘E‘ = Exakte Berechnung (Ausgangszustand auf Mittelzugspannungsprüfung gesetzt), sonst nach ideeller Berechnung
        // *** Neu ab V4.7.4 ***                            //
        /* 38 - 38  */ char LogDateiYN[1 + 1];              // Einstellung *.log-Datei: ‚L‘ : Datei erstellen, sonst nicht (Logdatei kann auch über Programmparameter ‚L‘ erzeugt werden.)
        virtual ~PAR1() {}
    };

    //: PARX: Erweiterte Parameter
    // *** Neu ab XX.09.05 *** (erst ab Kern Version 1.8.5 wirksam) ***
    struct PARX : Base
    {

        /* 1 - 4 */ char DSK[4 + 1];    // Satzkennung ‘PARX’
        /* 7 - 9 */ int OptionenAusgab; // 3 Ziffern // Erweiterte Optionen für Ausgabe. '0' oder fehlend(' ') : Standard / konventionell '1': Ausgabe Spanntabellen für Sudan, unterdrückt die Info 'clamped conductor' in Protokollen (Vorgabe H.Weisse), nur sinnvoll in Verbindung mit engl. Sprachausgabe (PAR1, Spalte 36)
        virtual ~PARX() {}
    };

    //: DINE: Einstellungen DIN EN50341
    // *** Änderung ab Version 1.6 ***
    struct DINE : Base
    {
        /*  1 -  4 */ char DSK[4 + 1];                  // Satzkennung ‘DINE’
        /*  7 -  7 */ int Eislastzone;                  //   1  // Eislastzone
        /*  9 -  9 */ int Windlastzone;                 //   1  // Windlastzone
        /* 11 - 15 */ float AlternativerObjektabstand;  // 5.2   // Alternativer Objektabstand (a_som), wird nur vom Kern ausgewertet, wenn mindestens bei einem Kreuzungsobjekt der Objektabstand nach DIN EN ausgewählt ist, s.u. Satzkennung "OBJ1". Für jedes Kreuzungsobjekt, für welches der Mindestabstand gemäß DIN EN eingestellt ist, wird geprüft, ob 1.1*a_som > angegebener Mindestabstand. Ist dies der Fall, wird der Mindestabstand auf 1.1*a_som gesetzt.
        // *** Neu ab V 3.4.0 / Win 263 V 2.8.0 ***     //
        /* 17 - 17 */ char ENStandEislast[1 + 1];       // EN-Stand Eislast: '0' oder ' '  : Eislast nach EN 03/2002 '1’ : Eislast ab EN 01/20 11
        /* 18 - 18 */ char ENStandWindlast[1 + 1];      // EN-Stand Windlast: ''0' oder ' ' : Windlast nach EN 03/2002 '1' : Windlast ab EN 01/20 11
        // ***Neu ab V 3.4.3 / Win 263 V 2.8.2 * **     //
        /* 19 - 19 */ char Staudruck[1 + 1];            // Modus Angabe Staudruck-Höhentabelle: '0' oder '' : Bezugsstaudruck '1' : Absoluter Staudruck
        virtual ~DINE() {}
    };

    //: DBSV: Einstellungen Trassierungsrichtlinie (früher DBE Seilverlegevorschrift)
    // *** Änderung ab Version 1.7: Erweiterung auf Trassierungsrichtlinie DBE 2004 ***
    struct DBSV : Base
    {
        /*  1 -  4 */ char DSK[4 + 1];                  // Satzkennung ‘DBSV’
        /*  7 - 13 */ float Bautoleranz;                // 7.2   // Vorsorge (Bautoleranz)
        // *** Neu ab V  3.4.4 / Win 263 V 2.8.3 ***    //
        /* 14 - 14 */ char Sicherheitsabstand[1 + 1];   // Einstellung Vorsorge und Sicherheitsabstand Schutzstreifen : 'S' : Bautoleranz zu Sicherheitsabstand addieren sonst : Bautoleranz nicht zu Sicherheitsabstand addieren
        virtual ~DBSV() {}
    };

    //: TRRL: Erweiterte Daten Trassierungsrichtlinie
    // *** Neu ab Version 4.14.2: Namen Trassierungsrichtlinie frei definierbar ***
    struct TRRL : Base
    {
        /* 1 -  4 */ char DSK[4];                     // Satzkennung ‘TRRL’
        /* 7 - 70 */ char Trassierungsrichtlinie[64]; // Name Trassierungsrichtlinie (wenn leer: nach DB Energie)
        virtual ~TRRL() {}
    };

    /*
    WIND: Berechnungseinstellungen, Staudruck

    Anmerkung: Falls in allgemeinen Einstellungen Windgesetz nach DIN EN 50341 eingestellt ist
    (siehe oben, Datenzeile PAR1, Spalte 34)
    werden die Staudruckdaten anders interpretiert.
    Anstatt des wirklichen Staudruckes werden in den entsprechenden Datenfeldern die Bezugsstaudrü
    aus denen erst der reale Staudruck im Berechnungskern ermittelt wird.
    Steht hier eine '-1', so wird der Bezugsstaudruck aus der Formel '100+7*H/6' gemäß DIN E.
    Des Weiteren werden die Höhenstufen dann als Schwelle der Geländehöhe für den Mastfußert.
    D.h. ab diesem Wert für den Mastfußpunkt gilt der zugehö.
    */
    //: WIND: Berechnungseinstellungen, Staudruck
    struct WIND : Base
    {
        /*  1 -  4   Char     4 */ std::string DSK;              // Satzkennung ‘WIND’
        /*  7 -  8   Int      2 */ int AnzahlHoehenstufen;       // Anzahl Höhenstufen (<=‘7’)
        /*  9 - 14   Float  6.0 */ float StaudruckHoehenstufe_1; // Staudruck Höhenstufe 1, [N/m²], (‘530’)
        /* 15 - 20   Float  6.0 */ float Hoehenstufe_1;          // Höhenstufe 1, [m], (‘15’)
        /* 21 - 26   Float  6.0 */ float StaudruckHoehenstufe_2; // Staudruck Höhenstufe 2, [N/m²], (‘530’)
        /* 27 - 32   Float  6.0 */ float Hoehenstufe_2;          // Höhenstufe 2, [m], (‘40’)
        /* 33 - 38   Float  6.0 */ float StaudruckHoehenstufe_3; // Staudruck Höhenstufe 3, [N/m²], (‘680’)
        /* 39 - 44   Float  6.0 */ float Hoehenstufe_3;          // Höhenstufe 3, [m], (‘100’)
        /* 45 - 50   Float  6.0 */ float StaudruckHoehenstufe_4; // Staudruck Höhenstufe 4, [N/m²], (‘860’)
        /* 51 - 56   Float  6.0 */ float Hoehenstufe_4;          // Höhenstufe 4, [m], (‘150’)
        /* 57 - 62   Float  6.0 */ float StaudruckHoehenstufe_5; // Staudruck Höhenstufe 5, [N/m²], (‘950’)
        /* 63 - 68   Float  6.0 */ float Hoehenstufe_5;          // Höhenstufe 5, [m], (‘200’)
        /* 69 - 74   Float  6.0 */ float StaudruckHoehenstufe_6; // Staudruck Höhenstufe 6, [N/m²]
        /* 75 - 80   Float  6.0 */ float Hoehenstufe_6;          // Höhenstufe 6, [m]
        /* 81 - 86   Float  6.0 */ float StaudruckHoehenstufe_7; // Staudruck Höhenstufe 7, [N/m²]
        /* 87 - 92   Float  6.0 */ float Hoehenstufe_7;          // Höhenstufe 7, [m]
        virtual ~WIND() {}
    };

    // Berechnungszustände
    //: ZSTA: Allgemeine Angaben zu Zuständen
    struct ZSTA : Base
    {
        /*  1 -  4     4  */ char DSK[4 + 1];                        // Datensatzkennung ‘ZSTA’
        /*  7 - 12   6.3  */ char FaktorZusatzlastChar[6 + 1];       // Faktor erhöhte Zusatzlast (‘1.0’)
        /*  7 - 12   6.3  */ float FaktorZusatzlastFloat;            // Faktor erhöhte Zusatzlast (‘1.0’)
        /* 13 - 18   6.3  */ char FaktorUngleicheEislastChar[6 + 1]; // Faktor ungleiche Eislast (‘0.5’)
        /* 13 - 18   6.3  */ float FaktorUngleicheEislastFloat;      // Faktor ungleiche Eislast (‘0.5’)
        /* 19 - 24   6.3  */ char WindlastfaktorChar[6 + 1];         // Windlastfaktor
        /* 19 - 24   6.3  */ float WindlastfaktorFloat;              // Windlastfaktor
        virtual ~ZSTA() {}
    };

    // ZSTD: Definition der Berechnungszustände   +++
    struct ZSTD : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%3c%2c%20c%1c%1c%1c%1c%1c%1c%*4c%6c%6c%6c%6c%*1c%1c%1c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%6.3f|\n%6.3f|\n%6.2f|\n%6.2f|\n%s|\n%s|\n" };

        /*  1:     1 -  4      4  */ char DSK[4 + 1];                           // Datensatzkennung ‘ZSTD’
        /*  2:     7 -  9      3  */ char ZustandsindexChar[3 + 1];             // Zustandsindex (laufende Nummer)
        /*  2:     7 -  9      3  */ int ZustandsindexInt;                      // Zustandsindex (laufende Nummer)
        /*  3:    10 - 12      3  */ char TemperaturCChar[3 + 1];               // Temperatur °C
        /*  3:    10 - 12      3  */ int TemperaturCInt;                        // Temperatur °C
        /*  4:    13 - 14         */ char Konstante[2 + 1];                     // '°C' Konstante
        /*  5:    15 - 34     20  */ char Zustandsbezeichnung[20 + 1];          // Zustandsbezeichnung
        /*  6:    35 - 35      1  */ char KennungAusgangszustand[1 + 1];        // Kennung ‚A‘ Für Ausgangszustand, (darf nur einmal vergeben werden)
        /*  7:    36 - 36      1  */ char KennungGrenzlast[1 + 1];              // Kennung Grenzlast (‚H‘=Höchstzug, ‚M‘=Mittelzug, 'D'=Dauerzug nach EN 2002, 'B'=Bruchkraft nach EN 2006/2009)
        /*  8:    37 - 37      1  */ char KennungUngleicheEislast[1 + 1];       // Kennung ‚U‘ für ungleiche Eislast, darf nur einmal vergeben werden.
        /*  9:    38 - 38      1  */ char KennungKettenausschwingwinkels[1 + 1];// Kennung für ‚K’ Überprüfung des Kettenausschwingwinkels (darf nur einmal vergeben werden)
        /*  10:   39 - 39      1  */ char KennungZusatzlast[1 + 1];             // Kennung ‚E‘ Berechnung mit erhöhter Zusatzlast falls diese ungleich 1 (In ZSTA)
        /*  11:   40 - 40      1  */ char KennungEiswalze[1 + 1];               // Kennung ‚X‘ Berechnung mit Eiswalze
        /*  12:   45 - 50    6.3  */ char LastfaktorChar[6 + 1];                // Lastfaktor (Zusatz- bzw. Eislast)
        /*  12:   45 - 50    6.3  */ float LastfaktorFloat;                     // Lastfaktor (Zusatz- bzw. Eislast)
        /*  13:   51 - 56    6.3  */ char WindlastfaktorChar[6 + 1];            // Windlastfaktor
        /*  13:   51 - 56    6.3  */ float WindlastfaktorFloat;                 // Windlastfaktor
        /*  14:   57 - 62    6.2  */ char ReckwertChar[6 + 1];                  // Reckwert
        /*  14:   57 - 62    6.2  */ float ReckwertFloat;                       // Reckwert
        /*  15:   63 - 68    6.2  */ char AusnahmelastChar[6 + 1];              // Ausnahmelast in N/m
        /*  15:   63 - 68    6.2  */ float AusnahmelastFloat;                   // Ausnahmelast in N/m
        /*  16:   70 - 70      1  */ char Temperaturzuschlag[1 + 1];            // Flag, ob Zustand mit Temperaturzuschlag (aus Phasendaten) gemäss DB gerechnet wird. '+' : Mit Temperaturzschlag sonst: ohne Temperaturzuschlag
        /* *** neu ab Version 3.6.4 *** */                                      //
        /*  17:   71 - 71      1  */ char GrenzlastBerechnung[1 + 1];           // Flag, ob Grenzlast Berechnung beeinflusst oder eine Grenzlastüberschreitung nur protokolliert wird. 'P' : nur protokollieren sonst: Einfluss auf Berechnung (Reduktion Ausgangsspannung)
        virtual ~ZSTD() {}
    };
    //: ZSAN: Abstandsnachweise
    struct ZSAN : Base
    {
        /*  1 -  4   4  */ char DSK[4 + 1];                                    // Satzkennung ‘ZSAN’
        /*  7 -  9   3  */ char SatzindexChar[3 + 1];                          // Satzindex (laufende Nummer)
        /*  7 -  9   3  */ int SatzindexInt;                                   // Satzindex (laufende Nummer)
        /* 10 - 10   1  */ char Kurzbezeichnung[1 + 1];                        // Kurzbezeichnung ‚Z‘ ‚A‘, ‚U‘ ‚T‘ etc.
        /* 11 - 11   1  */ char KennungAusschwingen[1 + 1];                    // Kennung für Ausschwingen: .B‘ beide Leiter schwingen aus (nach DIN/VDE 0210 12.85) ‚A‘ nur unterkreuzender schwingt aus sonst kein Ausschwingen
        /* *** neu ab Version 4.7.2 ***  */                                    //
        /* 12 - 14   3  */ char IndexPhasensystemChar[3 + 1];                  // Index Phasensystem
        /* 12 - 14   3  */ int IndexPhasensystemInt;                           // Index Phasensystem
        /* 20 - 22   3  */ char ZustandsindexUeberkreuzendeLeitungChar[3 + 1]; // Zustandsindex überkreuzende Leitung
        /* 20 - 22   3  */ int ZustandsindexUeberkreuzendeLeitungInt;          // Zustandsindex überkreuzende Leitung
        /* 23 - 25   3  */ char ZustandsindexUnterkreuzendeLeitungChar[3 + 1]; // Zustandsindex unterkreuzende Leitung
        /* 23 - 25   3  */ int ZustandsindexUnterkreuzendeLeitungInt;          // Zustandsindex unterkreuzende Leitung
        /* *** neu ab Version 3.7.6 ***  */                                    //
        /* 26 - 28   3  */ int ZustandsindexUeberkreuzendeLeitung;             // Zustandsindex überkreuzende Leitung (Erdseile)
        /* 29 - 31   3  */ int ZustandsindexUnterkreuzendeLeitung;             // Zustandsindex unterkreuzende Leitung (Erdseile)
        virtual ~ZSAN() {}
    };
    //: DWRE: Druckausgabe Seilkurvenberechnung
    struct DWRE : Base
    {
        /*  1 -  4        4  */ char DSK[4 + 1];                    // Satzkennung ‘DWRE’
        /*  7 -  7        1  */ char Blattkennung[1 + 1];           // Blattkennung: A-Kettenaufhängepunkte (neu ab Version 3.4.12) Z-Zustandblatt H-Seilhöhentabelle L-Einzellasten (Eingabe) (neu ab Version 4.13.6) E-Einzellasten (Ergebnisse) D-Durchhänge 1 – Zusammenfassende Ausgabe 2 – ergänzende Daten
        /* 10 - 12        3  */ char PhasenIndexChar[3 + 1];        // PhasenIndex – 0=Alle Phasen
        /* 10 - 12        3  */ int PhasenIndexInt;                 // PhasenIndex – 0=Alle Phasen
        /* 13 - 22     10.2  */ char SeilhoehentabelleChar[10 + 1]; // Bei Seilhöhentabelle: Abstand der Druckausgabe
        /* 13 - 22     10.2  */ float SeilhoehentabelleInt;         // Bei Seilhöhentabelle: Abstand der Druckausgabe
        /* 23 - 25        3  */ char Zustandsindex_01Char[3 + 1];   // Zustandsindex 01
        /* 23 - 25        3  */ int Zustandsindex_01Int;            // Zustandsindex 01
        /* 26 - 28        3  */ char Zustandsindex_02Char[3 + 1];   // Zustandsindex 02
        /* 26 - 28        3  */ int Zustandsindex_02Int;            // Zustandsindex 02
        /* 29 - 31        3  */ char Zustandsindex_03Char[3 + 1];   // Zustandsindex 03
        /* 29 - 31        3  */ int Zustandsindex_03Int;            // Zustandsindex 03
        /* 32 - 34        3  */ char Zustandsindex_04Char[3 + 1];   // Zustandsindex 04
        /* 32 - 34        3  */ int Zustandsindex_04Int;            // Zustandsindex 04
        /* 35 - 37        3  */ char Zustandsindex_05Char[3 + 1];   // Zustandsindex 05
        /* 35 - 37        3  */ int Zustandsindex_05Int;            // Zustandsindex 05
        /* 38 - 40        3  */ char Zustandsindex_06Char[3 + 1];   // Zustandsindex 06
        /* 38 - 40        3  */ int Zustandsindex_06Int;            // Zustandsindex 06
        /* 41 - 43        3  */ char Zustandsindex_07Char[3 + 1];   // Zustandsindex 07
        /* 41 - 43        3  */ int Zustandsindex_07Int;            // Zustandsindex 07
        /* 44 - 46        3  */ char Zustandsindex_08Char[3 + 1];   // Zustandsindex 08
        /* 44 - 46        3  */ int Zustandsindex_08Int;            // Zustandsindex 08
        /* 47 - 49        3  */ char Zustandsindex_09Char[3 + 1];   // Zustandsindex 09
        /* 47 - 49        3  */ int Zustandsindex_09Int;            // Zustandsindex 09
        /* 50 - 52        3  */ char Zustandsindex_10Char[3 + 1];   // Zustandsindex 10
        /* 50 - 52        3  */ int Zustandsindex_10Int;            // Zustandsindex 10
        /* 53 - 55        3  */ char Zustandsindex_11Char[3 + 1];   // Zustandsindex 11
        /* 53 - 55        3  */ int Zustandsindex_11Int;            // Zustandsindex 11
        /* 56 - 58        3  */ char Zustandsindex_12Char[3 + 1];   // Zustandsindex 12
        /* 56 - 58        3  */ int Zustandsindex_12Int;            // Zustandsindex 12
        /* 59 - 61        3  */ char Zustandsindex_13Char[3 + 1];   // Zustandsindex 13
        /* 59 - 61        3  */ int Zustandsindex_13Int;            // Zustandsindex 13
        /* 62 - 64        3  */ char Zustandsindex_14Char[3 + 1];   // Zustandsindex 14
        /* 62 - 64        3  */ int Zustandsindex_14Int;            // Zustandsindex 14
        /* 65 - 67        3  */ char Zustandsindex_15Char[3 + 1];   // Zustandsindex 15
        /* 65 - 67        3  */ int Zustandsindex_15Int;            // Zustandsindex 15
        /* 68 - 70        3  */ char Zustandsindex_16Char[3 + 1];   // Zustandsindex 16
        /* 68 - 70        3  */ int Zustandsindex_16Int;            // Zustandsindex 16
        /* 71 - 73        3  */ char Zustandsindex_17Char[3 + 1];   // Zustandsindex 17
        /* 71 - 73        3  */ int Zustandsindex_17Int;            // Zustandsindex 17
        /* 74 - 76        3  */ char Zustandsindex_18Char[3 + 1];   // Zustandsindex 18
        /* 74 - 76        3  */ int Zustandsindex_18Int;            // Zustandsindex 18
        /* 77 - 79        3  */ char Zustandsindex_19Char[3 + 1];   // Zustandsindex 19
        /* 77 - 79        3  */ int Zustandsindex_19Int;            // Zustandsindex 19
        /* 80 - 82        3  */ char Zustandsindex_20Char[3 + 1];   // Zustandsindex 20
        /* 80 - 82        3  */ int Zustandsindex_20Int;            // Zustandsindex 20
        virtual ~DWRE() {}
    };
    /*
    Anmerkungen zu „Druckausgabe
    •    Es können bis zu acht Datensätze je 263-Datei vorhanden sein. (Blattkennungen A/Z/H/L/E/D/1/2), wobei jede Blattkennung allerdings nur einf.
    •    Die Spalten 13 – 22 werden nur bei Blattkennung ‚H‘ertet.
    •    Je nach Blattkennung können die Zustandsindize 1-20 unterschiedl:

    o       Blattkennung 'A':      Ausgabe der Kettenaufhängepunkte, Zustandsindize werde
    o       Blattkennung ‚Z‘:      Für jeden Zustand, welcher in den Zustandsindize auftaucht, wird ein en.
    o       Blattkennung ‚D‘:      Für jeden Zustand,welcher in den Zustandsindize auftaucht, wird ein Duen.
    o       Blattkennung ‚H‘       Ausgabe der Seilhöhentabelle, für jeden Zustand,welcher in den Zustandsindize auftaucht, wird ein Blatt ben.
    o       Blattkennung ‚L‘       Ausgabe der vorhandenen Einzellasten, Zustandst.
    o       Blattkennung ‚E‘       Ausgabe Berechnungsergebnisse Einzellasten, für jeden Zustand,welcher in den Zustandsindize auftaucht, wird ein Blatt mien.
    o       Blattkennung ‚1‘       Für Zustandsindex 1 + 2 werden Gewichtsspannweiten, für Zustandsindize 3-5 Seilspannungen und für Indize 6-8 werden Durchhänge in dem zusammenfassenden Datenblatt ausgegeben. Zustandsiriert.
    o       Blattkennung ‚2‘       Für Zustandsinex  1 + 2 werden Gewichtsspannweiten auf dem ergänzenden Datenblatt ausgegeben, Zustandsindert.

    GH263 Datenformat                                       25.01.22                                                   Seite 8
    */

    //: "SLG1", SLG2, SLG3: Seildaten   +++
    // Maximal 30 Seile
    struct SLG1 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%28c%4c%2c%1c%4c%5c%5c%5c%6c%8c%*1c%1c%1c%1c%1c%1c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%d|\n%d|\n%s|\n%4.2f|\n%s|\n%5.1f|\n%5.3f|\n%6.2f|\n%8.0f|\n%s|\n%s|\n%s|\n%s|\n%s|\n" };

        /* 1:  1 -  4      4   */ char DSK[4 + 1];                                 // Satzkennung ‘SLG1’
        /* 2:  7 -  9      3   */ char SeilindexChar[3 + 1];                       // Seilindex (laufende Nummer)
        /* 3:  7 -  9      3   */ int SeilindexInt;                                // Seilindex (laufende Nummer)
        /* 3: 11 - 38     28   */ char Seilbezeichnung[28 + 1];                    // Seilbezeichnung
        /* 4: 39 - 42      4   */ char SpannungsebeneChar[4 + 1];                  // Spannungsebene [kV] (‘110’,’220’,’380’...)
        /* 4: 39 - 42      4   */ int SpannungsebeneInt;                           // Spannungsebene [kV] (‘110’,’220’,’380’...)
        /* 5: 43 - 44      2   */ char AnzahlTeilleiterChar[2 + 1];                // Anzahl Teilleiter
        /* 5: 43 - 44      2   */ int AnzahlTeilleiterInt;                         // Anzahl Teilleiter
        /* 6: 45 - 45      1   */ char Buendelanordnung[1 + 1];                    // Bündelanordnung (bei 2-er-Bündel:‘H’=Horizontal,’V’=Vertikal)
        /* 7: 46 - 49    4.2   */ char TeilleiterabstandChar[4 + 1];               // Teilleiterabstand [m],(‘0.40’)
        /* 7: 46 - 49    4.2   */ float TeilleiterabstandFloat;                    // Teilleiterabstand [m],(‘0.40’)
        /* 8: 50 - 54      5   */ char Seiltyp[5 + 1];                             // Seiltyp (‘LS’=Leiterseil,’ES’=Erdseil, ‘LWL’=Lichtwellenleiter)
        /* 9: 55 - 59    5.1   */ char TemperaturdifferenzSeilkriechenChar[5 + 1]; // Temperaturdifferenz beim Seilkriechen [°C]
        /* 9: 55 - 59    5.1   */ float TemperaturdifferenzSeilkriechenFloat;      // Temperaturdifferenz beim Seilkriechen [°C]
        /* 10: 60 - 64    5.3  */ char KriechfaktorChar[5 + 1];                    // Kriechfaktor [promille]
        /* 10: 60 - 64    5.3  */ float KriechfaktorFloat;                         // Kriechfaktor [promille]
        /* 11: 65 - 70    6.2  */ char UeberziehfaktorChar[6 + 1];                 // Überziehfaktor [%]
        /* 11: 65 - 70    6.2  */ float UeberziehfaktorFloat;                      // Überziehfaktor [%]
        /* 12: 71 - 78    8.0  */ char KriechzeitChar[8 + 1];                      // Kriechzeit [h] (‘262800’=30Jahre)
        /* 12: 71 - 78    8.0  */ float KriechzeitFloat;                           // Kriechzeit [h] (‘262800’=30Jahre)
        /* 13: 80 - 80      1  */ char Kennung_EN_Seil[1 + 1];                     //  'E' = EN-Seil sonst : Seil konventionell
        /* 14: 81 - 81      1  */ char KennungSeilmanuellEingefuegt[1 + 1];        // Kennung Seil manuell eingefügt (zur Sperrung Gewicht in Win263) ’U’ = Seildatensatz manuell eingefügt, Gewicht editierbar sonst: Gewicht gesperrt.
        /* *** Neu ab Version 4.12.0 ***  */                                       //
        /* 15: 82 - 82     1   */ char Isolationsar[1 + 1];                        // Isolationsart (‘K‘=kunststoffummantelter Leiter, ‘I‘=isoliertes Kabel, sonst: Blanker Leiter)
        /* *** Neu ab Version 4.12.3 ***  */                                       //
        /* 16: 83   83     1   */ char VorzeichenTemperaturdifferenz[1 + 1];       // Vorzeichen Temperaturdifferenz : ‘-‘ = negativ , sonst: positiv
        /* 17: 84   84     1   */ char VorzeichenKriechfaktor[1 + 1];              // Vorzeichen Kriechfaktor: ‘-‘ = negativ , sonst: positiv

        virtual ~SLG1() {}
    };

    //: SLG1, "SLG2", SLG3: Seildaten   +++
    // Maximal 30 Seile
    struct SLG2 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%6c%8c%8c%10c%11c%7c%4c%8c%8c%1c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%6.2f|\n%8.2f|\n%8.0f|\n%10.8f|\n%11.9f|\n%7.3f|\n%4.2f|\n%8.2f|\n%8.2f|\n%s|\n" };

        /* 1  1 -  4       4   */ char DSK[4 + 1];                             // Satzkennung ‘SLG2’
        /* 2  7 -  9       3   */ char SeilindexChar[3 + 1];                   // Seilindex (laufende Nummer)
        /* 2  7 -  9       3   */ int SeilindexInt;                            // Seilindex (laufende Nummer)
        /* 3 10 - 15     6.2   */ char SeildurchmesserChar[6 + 1];             // Seildurchmesser [mm]
        /* 3 10 - 15     6.2   */ float SeildurchmesserFloat;                  // Seildurchmesser [mm]
        /* 4 16 - 23     8.2   */ char SeilquerschnittChar[8 + 1];             // Seilquerschnitt [mm²]
        /* 4 16 - 23     8.2   */ float SeilquerschnittFloat;                  // Seilquerschnitt [mm²]
        /* 5 24 - 31     8.0   */ char E_ModulChar[8 + 1];                     // E-Modul [N/mm²]
        /* 5 24 - 31     8.0   */ float E_ModulFloat;                          // E-Modul [N/mm²]
        /* 6 32 - 41    10.8   */ char AusdehnungskoeffizientChar[10 + 1];     // Ausdehnungskoeffizient [1/K]
        /* 6 32 - 41    10.8   */ float AusdehnungskoeffizientFloat;           // Ausdehnungskoeffizient [1/K]
        /* 7 42 - 52    11.9   */ char SpezSeilgewichtChar[11 + 1];            // Spez. Seilgewicht (QLK)[N/mm²m]
        /* 7 42 - 52    11.9   */ float SpezSeilgewichtFloat;                  // Spez. Seilgewicht (QLK)[N/mm²m]
        /* 8 53 - 59     7.3   */ char NormaleZusatzlastChar[7 + 1];           // Normale Zusatzlast [N/m] (5+0.1d nach DIN)
        /* 8 53 - 59     7.3   */ float NormaleZusatzlastFloat;                // Normale Zusatzlast [N/m] (5+0.1d nach DIN)
        /* 9 60 - 63     4.2   */ char AerodynamischerKraftbeiwertChar[4 + 1]; //  (‘1.0’,’1.1’,‘1.2’ oder ‘1,05‘)
        /* 9 60 - 63     4.2   */ float AerodynamischerKraftbeiwertFloat;      //  (‘1.0’,’1.1’,‘1.2’ oder ‘1,05‘)
        /* 10 64 - 71     8.2  */ char SeilgewichtDBChar[8 + 1];               // Seilgewicht aus Daten/Datenbank (zum Bestimmen QLK)
        /* 10 64 - 71     8.2  */ float SeilgewichtDBFloat;                    // Seilgewicht aus Daten/Datenbank (zum Bestimmen QLK)
        /* 11 72 - 79     8.2  */ char FettmasseChar[8 + 1];                   // Fettmasse (nur EN-Seile)
        /* 11 72 - 79     8.2  */ float FettmasseFloat;                        // Fettmasse (nur EN-Seile)
        /**** Neu ab Version 4.0.1 *** (nur als Ergebnis in slc-Datei)  */     //
        /* 12 80 - 80       1  */ char KennungQLK[1 + 1];                      // Kennung, ob QLK vorgegeben oder aus Seilgewicht berechnet wurde. ‘V‘ = Vorgabe, ‘G‘=gerechnet

        virtual ~SLG2() {}
    };

    //: SLG1, SLG2, "SLG3": Seildaten   +++
    // Maximal 30 Seile
    struct SLG3 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%8c%8c%8c%8c%6c%8c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%8.2f|\n%8.2f|\n%8.2f|\n%8.0f|\n%6.2f|\n%8.2f|\n" };

        /*  1:    1 -  4       4  */ char DSK[4 + 1];                     // Satzkennung ‘SLG3’
        /*  2:    7 -  9       3  */ char SeilindexChar[3 + 3];           // Seilindex (laufende Nummer)
        /*  2:    7 -  9       3  */ int SeilindexInt;                    // Seilindex (laufende Nummer)
        /*  3:   10 - 17     8.2  */ char HoechstzugspannungChar[8 + 3];  // zulässige Höchstzugspannung [N/mm²]
        /*  3:   10 - 17     8.2  */ float HoechstzugspannungFloat;       // zulässige Höchstzugspannung [N/mm²]
        /*  4:   18 - 25     8.2  */ char MittelzugspannungChar[8 + 3];   // zulässige Mittelzugspannung [N/mm²]
        /*  4:   18 - 25     8.2  */ float MittelzugspannungFloat;        // zulässige Mittelzugspannung [N/mm²]
        /*  5:   26 - 33     8.2  */ char DauerzugspannungChar[8 + 3];    // zulässige Dauerzugspannung [N/mm²]
        /*  5:   26 - 33     8.2  */ float DauerzugspannungFloat;         // zulässige Dauerzugspannung [N/mm²]
        /*  6:   34 - 41     8.0  */ char BruchkraftChar[8 + 3];          // rechnerische Bruchkraft [N]
        /*  6:   34 - 41     8.0  */ float BruchkraftFloat;               // rechnerische Bruchkraft [N]
        /*  7:   42 - 47     6.2  */ char StahlgewichtsanteilChar[6 + 3]; // Stahlgewichtsanteil [%]
        /*  7:   42 - 47     6.2  */ float StahlgewichtsanteilFloat;      // Stahlgewichtsanteil [%]
        /* *** Neu ab Version 4 .9.5 *** (zur Berechnung des Stahlgewichtsanteils)  */
        /*  8: 48 - 55     8.2    */ char StahlquerschnittChar[8 + 3];    // Stahlquerschnitt [mm²]
        /*  8: 48 - 55     8.2    */ float StahlquerschnittFloat;         // Stahlquerschnitt [mm²]

        virtual ~SLG3() {}
    };
    //: DTVG: Zeitabhängige Delta-T Vorgaben für Seilkriechen
    struct DTVG : Base
    {
        virtual ~DTVG() {}
    };
    //: "PHAS", PHA2, PHA4, PHA5: Phasen
    struct PHAS : Base
    {
        virtual ~PHAS() {}
    };
    //: PHAS, "PHA2", PHA4, PHA5: Phasen
    struct PHA2 : Base
    {
        virtual ~PHA2() {}
    };
    //: PHAS, PHA2, "PHA4", PHA5: Phasen
    struct PHA4 : Base
    {
        virtual ~PHA4() {}
    };
    //: PHAS, PHA2, PHA4, "PHA5": Phasen
    struct PHA5 : Base
    {
        virtual ~PHA5() {}
    };
    //: PSYS: Phasensysteme
    struct PSYS : Base
    {
        virtual ~PSYS() {}
    };
    //: PZLF: Zusätzliche Phasenabstandsberechnungen
    struct PZLF : Base
    {
        virtual ~PZLF() {}
    };
    //: HTMP (oder TPKT): Daten Hochtemperaturseile / Transitionspunkte
    //: TPKT (oder HTMP): Daten Hochtemperaturseile / Transitionspunkte
    struct HTMP : Base
    {
        virtual ~HTMP() {}
    };
    //: HTM2: Daten Hochtemperaturseile 2
    struct HTM2 : Base
    {
        virtual ~HTM2() {}
    };
    //: MAST: Maststandorte  +++
    // Maximal 100 Maste
    struct MAST : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%6c%*1c%1c%*1c%7c%6c%9c%8c%9c%9c%*1c%33c%6c%*1c%26c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%s|\n%s|\n%6.2f|\n%9.2f|\n%8.2f|\n%9.3f|\n%9.3f|\n%s%6.2f|\n%s|\n" };

        /*  1:    1 -   4       4   */ char DSK[4 + 1];                            //  Satzkennung ‘MAST’
        /*  2:    7 -   9       3   */ char MastindexChar[3 + 1];                  //  Mastindex (laufende Nummer)
        /*  2:    7 -   9       3   */ int MastindexInt;                           //  Mastindex (laufende Nummer)
        /*  3:   11 -  16       6   */ char MastnummerMastname_1[6 + 1];           //  Mastnummer / Mastname, Zeichen 1-6
        /*  4:   18 -  18       1   */ char Masttyp[1 + 1];                        //  Masttyp (‘A‘‚ ‘T‘ oder 'X' )
        /*  5:   20 -  26       7   */ char Masttypenbezeichnung_1[7 + 1];         //  Masttypenbezeichnung(=Masttyp aus CIT-Datei), Zeichen 1-7 !Achtung siehe auch Spalte 69-101!
        /*  6:   27 -  32     6.2   */ char AusfuehrungChar[6 + 1];                //  Ausführung (Fußverlängerung) [m]
        /*  6:   27 -  32     6.2   */ float AusfuehrungFloat;                     //  Ausführung (Fußverlängerung) [m]
        /*  7:   33 -  41     9.2   */ char LaengenstationMaststandortChar[9 + 1]; //  Längenstation Maststandort [m]
        /*  7:   33 -  41     9.2   */ float LaengenstationMaststandortFloat;      //  Längenstation Maststandort [m]
        /*  8:   42 -  49     8.2   */ char HoeheMastfusspunktChar[8 + 1];         //  Höhe Mastfußpunkt [m]
        /*  8:   42 -  49     8.2   */ float HoeheMastfusspunktFloat;              //  Höhe Mastfußpunkt [m]
        /*  9:   50 -  58     9.3   */ char LeitungswinkelChar[9 + 1];             //  Leitungswinkel [gon] (200=Flucht)
        /*  9:   50 -  58     9.3   */ float LeitungswinkelFloat;                  //  Leitungswinkel [gon] (200=Flucht)
        /* 10:   59 -  67     9.3   */ char StellwinkelChar[9 + 1];                //  Stellwinkel [gon] (0=Winkelhalbierende)
        /* 10:   59 -  67     9.3   */ float StellwinkelFloat;                     //  Stellwinkel [gon] (0=Winkelhalbierende)
        /* 11:   69 - 101      33   */ char Masttypenbezeichnung_2[33 + 1];        //  Masttypenbezeichnung,  Zeichen 8-40
        /* *** neu ab Version 3.6.4 (Änderung IHL) ***  */                         //
        /* 12:  102 - 107     6.2   */ char OrdinateMaststandortChar[6 + 1];       // Ordinate Maststandort (Wert wird  als Ordinaten-Zuschlag für Kettenaufhängepunkte interpretiert. Der Wert bezieht sich rechtwinklig auf das dem Mast vorhergehenden Leitungsfeld, beim 1. Mast ist es das nachfolgende Feld. )
        /* 12:  102 - 107     6.2   */ float OrdinateMaststandortFloat;            // Ordinate Maststandort (Wert wird  als Ordinaten-Zuschlag für Kettenaufhängepunkte interpretiert. Der Wert bezieht sich rechtwinklig auf das dem Mast vorhergehenden Leitungsfeld, beim 1. Mast ist es das nachfolgende Feld. )
        /* *** neu ab Version 4.6.3 ***  */                                        //
        /* 13:  109 - 134     26    */ char MastnummerMastname_2[26 + 1];          // Mastnummer / Mastname, Zeichen 7-32

        virtual ~MAST() {}
    };
    //: TRAV: Aufhängepunkte (Traversen) +++
    struct TRAV : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%3c%7c%7c%8c%*6c%6c%3c%*1c%7c%7c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%7.2f|\n%7.2f|\n%8.2f|\n%6.2f|\n%d|\n%7.2f|\n%7.2f|\n" };

        /* *** Änderung ab Version 4.5.1 Satzkennung auch anders ***  */
        /*  1:  1  -  4      4  */ char DSK[4 + 1];                         // Satzkennung ‘TRAV’ (auch ‘AUFH‘ erlaubt, bitte als Standard ‘TRAV‘ verwenden)
        /*  2:  7  -  9      3  */ char MastindexChar[3 + 1];               // Mastindex
        /*  2:  7  -  9      3  */ int MastindexInt;                        // Mastindex
        /*  3:  10 - 12      3  */ char PhasenindexChar[3 + 1];             // Phasenindex
        /*  3:  10 - 12      3  */ int PhasenindexInt;                      // Phasenindex
        /*  4:  13 - 19    7.2  */ char TraversenhoeheChar[7 + 1];          // Traversenhöhe [m]
        /*  4:  13 - 19    7.2  */ float TraversenhoeheFloat;               // Traversenhöhe [m]
        /*  5:  20 - 26    7.2  */ char AusladungChar[7 + 1];               // Ausladung (links positiv)
        /*  5:  20 - 26    7.2  */ float AusladungFloat;                    // Ausladung (links positiv)
        /*  6:  27 - 34    8.2  */ char StellwinkelTraverseChar[8 + 1];     // Stellwinkel der Traverse (0=Maststellwinkel) [gon]
        /*  6:  27 - 34    8.2  */ float StellwinkelTraverseFloat;          // Stellwinkel der Traverse (0=Maststellwinkel) [gon]
        /*  7:  41 - 46    6.2  */ char KettenlaengeChar[6 + 2];            // gemessene Kettenlänge [m]
        /*  7:  41 - 46    6.2  */ float KettenlaengeFloat;                 // gemessene Kettenlänge [m]
        /*  8:  47 - 49      3  */ char KettenindexChar[3 + 1];             // Kettenindex
        /*  8:  47 - 49      3  */ int KettenindexInt;                      // Kettenindex
        /*  9:  51 - 57    7.2  */ char HoehenbezugStaudruckChar[7 + 1];    // Höhenbezug Staudruck (EN-Norm) 0: Höhenbezug ist Traversenhöhe >0 : Direkte Angabe Höhenbezug für Berechnung Staudruck
        /*  9:  51 - 57    7.2  */ float HoehenbezugStaudruckFloat;         // Höhenbezug Staudruck (EN-Norm) 0: Höhenbezug ist Traversenhöhe >0 : Direkte Angabe Höhenbezug für Berechnung Staudruck
        /* *** Neu ab V 3.4.12 / Win 263 V 2.8.8 ***  */                    //
        /* 10:  58 - 64    7.2  */ char TraversenexzentrizitaetChar[7 + 1]; // Traversenexzentrizität. Positiv: In Leitungsrichtung, negativ: entgegen Leitungsrichtung.
        /* 10:  58 - 64    7.2  */ float TraversenexzentrizitaetFloat;      // Traversenexzentrizität. Positiv: In Leitungsrichtung, negativ: entgegen Leitungsrichtung.

        virtual ~TRAV() {}
    };
    //: "KET1", KET2: Ketten   +++
    // Maximal 1000 Ketten
    struct KET1 : Base
    {
#ifdef FLP
        char const* fmtDS{ "%4c%*2c%3c%*1c%1c%3c%*1c%2c%*1c%28c%*1c%9c%*1c%5c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%d|\n%s|\n%s|\n%s|\n%s|\n" };
#else
        char const* fmtDS{ "%4c%*2c%3c%*1c%1c%3c%*1c%2c%*1c%28c%*1c%9c%*1c%*5c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%d|\n%s|\n%s|\n%s|\n" };
#endif

        /*  1:  1  -  4     4  */ char DSK[4 + 1];                        // Satzkennung ‘KET1’
        /*  2:  7  -  9     3  */ char KettenindexChar[3 + 1];            // Kettenindex (laufende Nummer)
        /*  2:  7  -  9     3  */ int KettenindexInt;                     // Kettenindex (laufende Nummer)
        /*  3:  11 - 11     1  */ char Kettentyp[1 + 1];                  // Kettentyp (‘A’=Abspann-, ‘H’=Hänge-,’V’=V-Kette, ’S’=Stützer)
        /*  4:  12 - 14     3  */ char AnzahlKettenstraengeChar[3 + 1];   // Anzahl Kettenstränge
        /*  4:  12 - 14     3  */ int AnzahlKettenstraengeInt;            // Anzahl Kettenstränge
        /*  5:  16 - 17     2  */ char Kettentypbezeichnung[2 + 1];       // Kettentypbezeichnung (‘DA’,’DH’,’EH’ etc.)
        /*  6:  19 - 46    28  */ char KettenbezeichnungIsolator[28 + 1]; // Kettenbezeichnung/Isolator
        /*  7:  48 - 56     9  */ char Schwingenbezeichnung[9 + 1];       // Schwingenbezeichnung
#ifdef FLP
        /*  8:  58 - 62     5  */ char Kettennummer[5 + 1]; // Kettennummer (nur von FLP verwendet)
#endif
        virtual ~KET1()
        {
        }
    };

    //: KET1, "KET2": Ketten   +++
    // Maximal 1000 Ketten
    struct KET2 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%5c%5c%5c%5c%6c%6c%6c%7c%7c%6c%6c%6c%6c%6c%5c%5c" };
        char const* fmtPrintf{ "\n%4s|\n%d|\n%5.2f|\n%5.2f|\n%5.2f|\n%5.2f|\n%6.0f|\n%6.0f|\n%6.0f|\n%7.2f|\n%7.2f|\n%6.0f|\n%6.3f|\n%6.3f|\n%6.3f|\n%6.3f|\n%5.2f|\n%5.2f|\n" };

        /*    1   1 -  4       4    */ char DSK[4 + 1];                                    // Satzkennung ‘KET2’
        /*        5 -  6       1                                                           //
        /*    2   7 -  9       3    */ char KettenindexChar[3 + 1];                        // Kettenindex (laufende Nummer)
        /*    2   7 -  9       3    */ int KettenindexInt;                                 // Kettenindex (laufende Nummer)
        /*    3  10 - 14     5.2    */ char KettenlaengeChar[5 + 1];                       // Kettenlänge bis UK Bündel [m]
        /*    3  10 - 14     5.2    */ float KettenlaengeFloat;                            // Kettenlänge bis UK Bündel [m]
        /*    4  15 - 19     5.2    */ char VLaengeChar[5 + 1];                            // V-Länge (nur bei V-Ketten) [m]
        /*    4  15 - 19     5.2    */ float VLaengeFloat;                                 // V-Länge (nur bei V-Ketten) [m]
        /*    5  20 - 24     5.2    */ char FesteLaengeChar[5 + 1];                        // Feste Länge ab Traverse [m]
        /*    5  20 - 24     5.2    */ float FesteLaengeFloat;                             // Feste Länge ab Traverse [m]
        /*    6  25 - 29     5.2    */ char SchwingenlaengeChar[5 + 1];                    // Schwingenlänge [m]
        /*    6  25 - 29     5.2    */ float SchwingenlaengeFloat;                         // Schwingenlänge [m]
        /*    7  30 - 35     6.0    */ char KettengewichtChar[6 + 1];                      // Kettengewicht [N]
        /*    7  30 - 35     6.0    */ float KettengewichtFloat;                           // Kettengewicht [N]
        /*    8  36 - 41     6.0    */ char EinfachesEisgewichtKetteChar[6 + 1];           // Einfaches Eisgewicht auf Kette [N]
        /*    8  36 - 41     6.0    */ float EinfachesEisgewichtKetteFloat;                // Einfaches Eisgewicht auf Kette [N]
        /*    9  42 - 47     6.0    */ char SchwingengewichtChar[6 + 1];                   // Schwingengewicht [N]
        /*    9  42 - 47     6.0    */ float SchwingengewichtFloat;                        // Schwingengewicht [N]
        /*   10  48 - 54     7.2    */ char GrenzausschwingwinkelInnenChar[7 + 1];         // Grenzausschwingwinkel innen [grad]
        /*   10  48 - 54     7.2    */ float GrenzausschwingwinkelInnenFloat;              // Grenzausschwingwinkel innen [grad]
        /*   11  55 - 61     7.2    */ char GrenzausschwingwinkelAuszenChar[7 + 1];        // Grenzausschwingwinkel außen [grad]
        /*   11  55 - 61     7.2    */ float GrenzausschwingwinkelAuszenFloat;             // Grenzausschwingwinkel außen [grad]
        /*   12  62 - 67     6.0    */ char ZusatzgewichtChar[6 + 1];                      // Zusatzgewicht [N]
        /*   12  62 - 67     6.0    */ float ZusatzgewichtFloat;                           // Zusatzgewicht [N]
        /*   13  68 - 73     6.3    */ char EinbaulaengeChar[6 + 1];                       // Einbaulänge [m]
        /*   13  68 - 73     6.3    */ float EinbaulaengeFloat;                            // Einbaulänge [m]
        /*   14  74 - 79     6.3    */ char SchirmdurchmesserChar[6 + 1];                  // Schirmdurchmesser [m]
        /*   14  74 - 79     6.3    */ float SchirmdurchmesserFloat;                       // Schirmdurchmesser [m]
        /*   15  80 - 85     6.3    */ char StrunkdurchmesserChar[6 + 1];                  // Strunkdurchmesser [m]
        /*   15  80 - 85     6.3    */ float StrunkdurchmesserFloat;                       // Strunkdurchmesser [m]
        /*   16  86 - 91     6.3    */ char ProjizierteFlaecheChar[6 + 1];                 // Projizierte Fläche [m²]
        /*   16  86 - 91     6.3    */ float ProjizierteFlaecheFloat;                      // Projizierte Fläche [m²]
        /* *** Neu ab Version 4.10.0 *** (V-Kettenstrangbruch)  */                         //
        /*   17  92 -  96    5.2    */ char VKetteVersatzAufhaengungMastInnenChar[5 + 1];  //  V-Kette Versatz Aufhängung zum Mast hin (innen)
        /*   17  92 -  96    5.2    */ float VKetteVersatzAufhaengungMastInnenFloat;       //  V-Kette Versatz Aufhängung zum Mast hin (innen)
        /*   18  97 - 101    5.2    */ char VKetteVersatzAufhaengungMastAussenChar[5 + 1]; //  V-Kette Versatz Aufhängung vom Mast weg (außen)
        /*   18  97 - 101    5.2    */ float VKetteVersatzAufhaengungMastAussenFloat;      //  V-Kette Versatz Aufhängung vom Mast weg (außen)

        virtual ~KET2() {}
    };
    //: ROLL: Rollen (bei Berechnung Seile in Rollen)
    struct ROLL : Base
    {
        virtual ~ROLL() {}
    };
    //: "WRR1", WRR2: Einstellungen Spanntabellen
    struct WRR1 : Base
    {
        virtual ~WRR1() {}
    };
    //: WRR1, "WRR2": Einstellungen Spanntabellen
    struct WRR2 : Base
    {
        virtual ~WRR2() {}
    };
    //: SCSV: Einstellungen Schutzstreifen
    struct SCSV : Base
    {
        virtual ~SCSV() {}
    };
    //: PHAV: Einstellungen Phasenabstandsberechnung
    struct PHAV : Base
    {
        virtual ~PHAV() {}
    };
    //: DHGM: Durchhangsmessungen
    struct DHGM : Base
    {
        virtual ~DHGM() {}
    };
    //: EZLA: Einzel- und Streckenlasten  +++
    struct EZLA : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%3c%3c%*1c%1c%*1c%1c%1c%1c%3c%3c%9c%9c%9c%9c" };
        char const* fmtPrintf{ "\n%4s|\n%3d|\n%3d|\n%3d|\n%1s|\n%1s|\n%1s|\n%1s|\n%3d|\n%3d|\n%99.2f|\n%9.2f|\n%9.2f|\n%99.2f|\n" };

        /*    1  1 -  4      4  */ char DSK[4 + 1];                          // Satzkennung ‘EZLA’
        /*       5 -  6      2                                               //
        /*    2  7 -  9      3  */ char LastindexChar[1 + 1];                // Lastindex (laufende Nummer)
        /*    2  7 -  9      3  */ int LastindexInd;                         // Lastindex (laufende Nummer)
        /*    3 10 - 12      3  */ char PhasenindexChar[3 + 1];              // Phasenindex
        /*    3 10 - 12      3  */ int PhasenindexInt;                       // Phasenindex
        /*    4 13 - 15      3  */ char MastindexLinkerMastChar[3 + 1];      // Mastindex linker Mast
        /*    4 13 - 15      3  */ int MastindexLinkerMastInt;               // Mastindex linker Mast
        /*      16 - 16      1                                               //
        /*    5 17 - 17      1  */ char Lasttyp[1 + 1];                      // Lasttyp (‘F’=Feldlast, ‘S’=Streckenlast, ‘P’=Punktlast)
        /*      18 - 18      1                                               //
        /*    6 19 - 19      1  */ char KennungLastEndzustand[1 + 1];        // Kennung ‘X’ - Last auf Endzustand
        /*    7 20 - 20      1  */ char KennungLastMontagezustand[1 + 1];    // Kennung ‘X’ - Last auf Montagezustand
        /*    8 21 - 21      1  */ char KennungLastRollenzustand[1 + 1];     // Kennung ‘X’ - Last auf Rollenzustand
        /*    9 22 - 24      3  */ char ZustandsindexChar[3 + 1];            // Zustandsindex, 0-Last auf alle Berechnungszustände, sonst nur auf einzelnen Berechnungszustand
        /*    9 22 - 24      3  */ int ZustandsindexInt;                     // Zustandsindex, 0-Last auf alle Berechnungszustände, sonst nur auf einzelnen Berechnungszustand
        /*   10 25 - 27      3  */ char AnzahlLastenChar[3 + 1];             // Anzahl Lasten bei Einzel– oder Feldlast (Bei Feldlast: Anzahl der Felder beginnend ab Startfeld, Werte von <= 0 entsprechen dabei 1)
        /*   10 25 - 27      3  */ int AnzahlLastenInt;                      // Anzahl Lasten bei Einzel– oder Feldlast (Bei Feldlast: Anzahl der Felder beginnend ab Startfeld, Werte von <= 0 entsprechen dabei 1)
        /*   11 28 - 36    9.2  */ char StationLinkerMastChar[9 + 1];        // Station bzgl. linken Mast  [m]
        /*   11 28 - 36    9.2  */ float StationLinkerMastFloat;             // Station bzgl. linken Mast  [m]
        /*   12 37 - 45    9.2  */ char AbstandLastenEndestationChar[9 + 1]; // Abstand zwischen Lasten bzw. Endestation
        /*   12 37 - 45    9.2  */ float AbstandLastenEndestationFloat;      // Abstand zwischen Lasten bzw. Endestation
        /*   13 46 - 54    9.2  */ char LastChar[9 + 1];                     // Last [N] bzw [N/m]
        /*   13 46 - 54    9.2  */ float LastFloat;                          // Last [N] bzw [N/m]
        /*   14 55 - 63    9.2  */ char EinfacheEislastChar[9 + 1];          // Einfache Eislast [N] bzw. [N/m]
        /*   14 55 - 63    9.2  */ float EinfacheEislastFloat;               // Einfache Eislast [N] bzw. [N/m]
        virtual ~EZLA() {}
    };
    //: NEIG: Eingabe Seilneigung
    struct NEIG : Base
    {
        virtual ~NEIG() {}
    };
    struct ENEI : Base
    {
        virtual ~ENEI() {}
    };
    //: ENEI: Ergebnisse Seilneigung (slc)
    struct ENET : Base
    {
        virtual ~ENET() {}
    };
    //: PATH: Dateipfad Berechnungsprogramm (slc)
    struct PATH : Base
    {
        virtual ~PATH() {}
    };
    //: "SLK1", SLK2, SLK3: Ergebnis Seilkurvenberechnung (slc)  +++
    struct SLK1 : Base
    {
        char const* fmtDS{ "%4c%*3c%4c%4c%3c%3c%3c%9c%9c%9c%9c%9c%9c%9c%9c%9c%9c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%d|\n%d|\n%d|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n" };

        /*   1:    1    1 -   4    4     */ char DSK[4 + 1];                                            // Satzkennung ‘SLK1’
        /*    :    2    5 -   7    3     */                                                             //
        /*   2:    3    8 -  11    4     */ char SeilkurvenindexChar[4 + 1];                            // Seilkurvenindex (laufende Nummer)
        /*   2:    3    8 -  11    4     */ int SeilkurvenindexInt;                                     // Seilkurvenindex (laufende Nummer)
        /*   3:    4   12 -  15    3     */ char PhasenindexChar[4 + 1];                                // Phasenindex
        /*   3:    4   12 -  15    3     */ int PhasenindexInt;                                         // Phasenindex
        /*   4:    5   16 -  18    3     */ char ZustandsindexChar[3 + 1];                              // Zustandsindex
        /*   4:    5   16 -  18    3     */ int ZustandsindexInt;                                       // Zustandsindex
        /*   5:    6   19 -  21    3     */ char MastindexLinkerMastChar[3 + 1];                        // Mastindex linker Mast
        /*   5:    6   19 -  21    3     */ int MastindexLinkerMastInt;                                 // Mastindex linker Mast
        /*   6:    7   22 -  24    3     */ char MastindexRechterMastChar[3 + 1];                       // Mastindex rechter Mast
        /*   6:    7   22 -  24    3     */ int MastindexRechterMastInt;                                // Mastindex rechter Mast
        /*   7:    8   25 -  33    9.2   */ char StationSeilaufhaengepunktLinksChar[9 + 1];             // Station Seilaufhängepunkt (links) [m]
        /*   7:    8   25 -  33    9.2   */ float StationSeilaufhaengepunktLinksFloat;                  // Station Seilaufhängepunkt (links) [m]
        /*   8:    9   34 -  42    9.2   */ char HoeheSeilaufhaengepunktLinksChar[9 + 1];               // Höhe Seilaufhängepunkt (links) [m]
        /*   8:    9   34 -  42    9.2   */ float HoeheSeilaufhaengepunktLinksFloat;                    // Höhe Seilaufhängepunkt (links) [m]
        /*   9:   10   43 -  51    9.2   */ char OrdinateSeilaufhaengepunktChar[9 + 1];                 // Ordinate Seilaufhängepunkt (links) [m]
        /*   9:   10   43 -  51    9.2   */ float OrdinateSeilaufhaengepunktFloat;                      // Ordinate Seilaufhängepunkt (links) [m]
        /*  10:   11   52 -  60    9.2   */ char StationSeilaufhaengepunktRechtsChar[9 + 1];            // Station Seilaufhängepunkt (rechts) [m]
        /*  10:   11   52 -  60    9.2   */ float StationSeilaufhaengepunktRechtsFloat;                 // Station Seilaufhängepunkt (rechts) [m]
        /*  11:   12   61 -  69    9.2   */ char HoeheSeilaufhaengepunktRechtsChar[9 + 1];              // Höhe Seilaufhängepunkt (rechts) [m]
        /*  11:   12   61 -  69    9.2   */ float HoeheSeilaufhaengepunktRechtsFloat;                   // Höhe Seilaufhängepunkt (rechts) [m]
        /*  12:   13   70 -  78    9.2   */ char OrdinateSeilaufhaengepunktRechtsChar[9 + 1];           // Ordinate Seilaufhängepunkt (rechts) [m]
        /*  12:   13   70 -  78    9.2   */ float OrdinateSeilaufhaengepunktRechtsFloat;                // Ordinate Seilaufhängepunkt (rechts) [m]
        /*  13:   14   79 -  87    9.2   */ char StationSeilaufhaengepunktLinksTransformChar[9 + 1];    // Station Seilaufhängepunkt (links) [m] (transformiert auf Feld)
        /*  13:   14   79 -  87    9.2   */ float StationSeilaufhaengepunktLinksTransformFloat;         // Station Seilaufhängepunkt (links) [m] (transformiert auf Feld)
        /*  14:   15   88 -  96    9.2   */ char OrdinateSeilaufhaengepunktLinksChar[9 + 1];            // Ordinate Seilaufhängepunkt (links) [m] (transformiert auf Feld)
        /*  14:   15   88 -  96    9.2   */ float OrdinateSeilaufhaengepunktLinksFloat;                 // Ordinate Seilaufhängepunkt (links) [m] (transformiert auf Feld)
        /*  15:   16   97 - 105    9.2   */ char StationSeilaufhaengepunktRechtsTransformChar[9 + 1];   // Station Seilaufhängepunkt (rechts) [m] (transformiert auf Feld)
        /*  15:   16   97 - 105    9.2   */ float StationSeilaufhaengepunktRechtsTransformFloat;        // Station Seilaufhängepunkt (rechts) [m] (transformiert auf Feld)
        /*  16:   17  106 - 114    9.2   */ char OrdinateSeilaufhaengepunktRechtsTransformChar[9 + 1];  // Ordinate Seilaufhängepunkt (rechts) [m] (transformiert auf Feld)
        /*  16:   17  106 - 114    9.2   */ float OrdinateSeilaufhaengepunktRechtsTransformFloat;       // Ordinate Seilaufhängepunkt (rechts) [m] (transformiert auf Feld)

        virtual ~SLK1() {}
    };
    //: SLK1, "SLK2", SLK3: Ergebnis Seilkurvenberechnung (slc)  +++
    struct SLK2 : Base
    {
        char const* fmtDS{ "%4c%*3c%4c%7c%11c%7c%7c%9c%9c%9c%1c%1c%9c%9c%9c%9c%8c%8c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%7.2f|\n%11.9f|\n%7.2f|\n%7.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%s|\n%s|\n%9.2f|\n%9.2f|\n%9.2f|\n%9.2f|\n%8.2f|\n%8.2f|\n" };

        /*   1:     1     1 -   4         4     */ char DSK[4 + 1];                                         // Satzkennung ‘SLK2’
        /*          2     5 -   7         3                                                                 //
        /*   2:     3     8 -  11         4     */ char SeilkurvenindexChar[4 + 1];                         // Seilkurvenindex (laufende Nummer)
        /*   2:     3     8 -  11         4     */ int SeilkurvenindexInt;                                  // Seilkurvenindex (laufende Nummer)
        /*   3:     4    12 -  18         7.2   */ char SeilspannungEndzustandChar[7 + 1];                  // Seilspannung Endzustand [N/mm²]
        /*   3:     4    12 -  18         7.2   */ float SeilspannungEndzustandFloat;                       // Seilspannung Endzustand [N/mm²]
        /*   4:     5    19 -  29        11.9   */ char SeilgewichtEndzustandChar[11 + 1];                  // Seilgewicht Endzustand [N/mm²m]
        /*   4:     5    19 -  29        11.9   */ float SeilgewichtEndzustandFloat;                        // Seilgewicht Endzustand [N/mm²m]
        /*   5:     6    30 -  36         7.2   */ char SeilausschwingwinkelChar[7 + 1];                    // Seilausschwingwinkel
        /*   5:     6    30 -  36         7.2   */ float SeilausschwingwinkelFloat;                         // Seilausschwingwinkel
        /*   6:     7    37 -  43         7.2   */ char DurchhangFeldmitteChar[7 + 1];                      // Durchhang in Feldmitte
        /*   6:     7    37 -  43         7.2   */ float DurchhangFeldmitteFloat;                           // Durchhang in Feldmitte
        /*   7:     8    44 -  52         9.2   */ char StationSeilpunktFeldmitteChar[9 + 2];               // Station Seilpunkt (Feldmitte) [m]
        /*   7:     8    44 -  52         9.2   */ float StationSeilpunktFeldmitteFloat;                    // Station Seilpunkt (Feldmitte) [m]
        /*   8:     9    53 -  61         9.2   */ char HoeheSeilpunktFeldmitteChar[9 + 2];                 // Höhe Seilpunkt (Feldmitte) [m]
        /*   8:     9    53 -  61         9.2   */ float HoeheSeilpunktFeldmitteFloat;                      // Höhe Seilpunkt (Feldmitte) [m]
        /*   9:    10    62 -  70         9.2   */ char OrdinateSeilpunktFeldmitteChar[9 + 2];              // Ordinate Seilpunkt (Feldmitte) [m]
        /*   9:    10    62 -  70         9.2   */ float OrdinateSeilpunktFeldmitteFloat;                   // Ordinate Seilpunkt (Feldmitte) [m]
        /*  10:    11    71 -  71         1     */ char TiefsterPunktFeldmitte[1 + 1];                      // ' * ' falls tiefster Punkt in Feldmitte des Feldes, sonst nichts
        /*  11:    12    72 -  72         1     */ char GroeszterDurchhangFeld[1 + 1];                      // '#' falls größter Durchhang des Feldes, sonst nichts
        /* *** Neu ab Version 4.0.1 ***  */                                                                 //
        /*  12:    13     73 -  81        9.2   */ char GewichtsspannweiteChar[9 + 1];                      // Gewichtsspannweite
        /*  12:    13     73 -  81        9.2   */ float GewichtsspannweiteFloat;                           // Gewichtsspannweite
        /*  13:    14     82 -  90        9.2   */ char BogenlaengeSeilChar[9 + 1];                         // Bogenlänge des Seils
        /*  13:    14     82 -  90        9.2   */ float BogenlaengeSeilFloat;                              // Bogenlänge des Seils
        /*  14:    15     91 -  99        9.2   */ char ScheitelpunktEntfernungLinkerMastChar[9 + 1];       // Scheitelpunkt, Entfernung vom linken Mast
        /*  14:    15     91 -  99        9.2   */ float ScheitelpunktEntfernungLinkerMastFloat;            // Scheitelpunkt, Entfernung vom linken Mast
        /*  15:    16    100 - 108        9.2   */ char ScheitelpunktSeilhoeheChar[9 + 1];                  // Scheitelpunkt, Seilhöhe
        /*  15:    16    100 - 108        9.2   */ float ScheitelpunktSeilhoeheFloat;                       // Scheitelpunkt, Seilhöhe
        /*  16:    17    109 - 116        8.2   */ char SeilspannungAbsolutAufhaengepunktLinksChar[8 + 1];  // Seilspannung absolut Aufhängepunkt links
        /*  16:    17    109 - 116        8.2   */ float SeilspannungAbsolutAufhaengepunktLinksFloat;       // Seilspannung absolut Aufhängepunkt links
        /*  17:    18    117 - 124        8.2   */ char SeilspannungAbsolutAufhaengepunktRechtChar[8 + 1];  // Seilspannung absolut Aufhängepunkt rechts
        /*  17:    18    117 - 124        8.2   */ float SeilspannungAbsolutAufhaengepunktRechtsFloat;      // Seilspannung absolut Aufhängepunkt rechts

        virtual ~SLK2() {}
    };
    //: SLK1, SLK2, "SLK3": Ergebnis Seilkurvenberechnung (slc)
    struct SLK3 : Base
    {
        char const* fmtDS{ "%4c%*3c%4c%7c%7c%7c%7c%7c%7c%10c%10c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%7.3f|\n%7.3f|\n%7.3f|\n%7.3f|\n%7.3f|\n%7.3f|\n%10.2f|\n%10.2f|\n" };

        /*   1:    1 -  4        4     */ char DSK[4 + 1];                                                      // Satzkennung ‘SLK3’
        /*         5 -  7        3     */                                                                       //
        /*   2:    8 - 11        4     */ char SeilkurvenindexChar[4 + 1];                                      // Seilkurvenindex (laufende Nummer)
        /*   2:    8 - 11        4     */ int SeilkurvenindexInt;                                               // Seilkurvenindex (laufende Nummer)
        /*   3:   12 - 18        7.3   */ char KettenauslenkungLinkerMastInLeitungsrichtungChar[7 + 1];         // Kettenauslenkung linker Mast in Leitungsrichtung
        /*   3:   12 - 18        7.3   */ float KettenauslenkungLinkerMastInLeitungsrichtungFloat;              // Kettenauslenkung linker Mast in Leitungsrichtung
        /*   4:   19 - 25        7.3   */ char KettenauslenkungLinkerMastQuerLeitungsrichtungChar[7 + 1];       // Kettenauslenkung linker Mast quer zu Leitungsrichtung (positiv entspr. nach links)
        /*   4:   19 - 25        7.3   */ float KettenauslenkungLinkerMastQuerLeitungsrichtungFloat;            // Kettenauslenkung linker Mast quer zu Leitungsrichtung (positiv entspr. nach links)
        /*   5:   26 - 32        7.3   */ char KettenauslenkungLinkerMastVertikalLeitungsrichtungChar[7 + 1];   // Kettenauslenkung linker Mast vertikal (Höhe, negativ entspr. nach unten)
        /*   5:   26 - 32        7.3   */ float KettenauslenkungLinkerMastVertikalLeitungsrichtungFloat;        // Kettenauslenkung linker Mast vertikal (Höhe, negativ entspr. nach unten)
        /*   6:   33 - 39        7.3   */ char KettenauslenkungRechterMastInLeitungsrichtungChar[7 + 1];        // Kettenauslenkung rechter Mast in Leitungsrichtung
        /*   6:   33 - 39        7.3   */ float KettenauslenkungRechterMastInLeitungsrichtungFloat;             // Kettenauslenkung rechter Mast in Leitungsrichtung
        /*   7:   40 - 46        7.3   */ char KettenauslenkungRechterMastQuerLeitungsrichtungChar[7 + 1];      // Kettenauslenkung rechter Mast quer zu Leitungsrichtung (positiv entspr. nach links)
        /*   7:   40 - 46        7.3   */ float KettenauslenkungRechterMastQuerLeitungsrichtungFloat;           // Kettenauslenkung rechter Mast quer zu Leitungsrichtung (positiv entspr. nach links)
        /*   8:   47 - 53        7.3   */ char KettenauslenkungRechterMastVertikalLeitungsrichtungChar[7 + 1];  // Kettenauslenkung rechter Mast vertikal (Höhe, negativ entspr. nach unten)
        /*   8:   47 - 53        7.3   */ float KettenauslenkungRechterMastVertikalLeitungsrichtungFloat;       // Kettenauslenkung rechter Mast vertikal (Höhe, negativ entspr. nach unten)
        /*   9:   54 - 63       10.2   */ char SeilzugLinksChar[10 + 1];                                        // Seilzug links
        /*   9:   54 - 63       10.2   */ float SeilzugLinksFloat;                                              // Seilzug links
        /*  10:   64 - 73       10.2   */ char SeilzugRechtsChar[10 + 1];                                       // Seilzug rechts
        /*  10:   64 - 73       10.2   */ float SeilzugRechtsFloat;                                             // Seilzug rechts

        virtual ~SLK3() {}
    };
    //: EDHM: Ergebnisse Durchhangsmessungen (slc)
    struct EDHM : Base
    {
        virtual ~EDHM() {}
    };
    //: ELST: Ergebnis Einzellasten (slc)
    struct ELST : Base
    {
        virtual ~ELST() {}
    };
    //: ESEH: Ergebnis Seilhöhentabellen (slc)
    struct ESEH : Base
    {
        virtual ~ESEH() {}
    };
    //: SPAN: Ergebnisse Spannweiten an Maste (slc)
    struct SPAN : Base
    {
        virtual ~SPAN() {}
    };
    //: DBPD: Ergebnisse Phasendaten DB Energie (slc)
    struct DBPD : Base
    {
        virtual ~DBPD() {}
    };
    //: EPHA: Ergebnisse Ausgabe Phasen (slc)
    struct EPHA : Base
    {
        virtual ~EPHA() {}
    };
    //: EGZU: Ergebnisse Grenzspannungen überschritten (slc)
    struct EGZU : Base
    {
        virtual ~EGZU() {}
    };
    //: EKAP: Ergebnisse Kettenaufhängepunkte (slc)
    struct EKAP : Base
    {
        virtual ~EKAP() {}
    };
    //: EPHF: Ergebnisse feldbezogene Phasendaten (slc)
    struct EPHF : Base
    {
        virtual ~EPHF() {}
    };
    //: OBOP: Einstellungen Berechnung Kreuzungsobjekte
    struct OBOP : Base
    {
        virtual ~OBOP() {}
    };
    //: "OBJ1", OBJ2, OBJ3: Kreuzungsobjekte  +++
    struct OBJ1 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%10c%6c%3c%1c%*3c%4c%3c%3c%*1c%1c%1c%1c%1c%1c%1c%3c%6c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%6.2f|\n%d|\n%s|\n%s|\n%d|\n%d|\n%s|\n%s|\n%s|\n%s|\n%s|\n%s|\n%d|\n%6.2f|\n" };

        /*   1:  1  -  4      4           */ char DSK[4 + 1];                             //  Satzkennung ‘OBJ1’
        /*   2:  7  -  9      3           */ char KreuzungsobjektindexTeil_1_Char[3 + 1] ; //  Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*   2:  7  -  9      3           */ int KreuzungsobjektindexTeil_1_Int;          //  Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*   3:  11 - 20     10           */ char Objektnummer[10 + 1];                   //  Objektnummer (Bezeichnung)
        /*   4:  21 - 26    6.2           */ char MindestabstandChar[6 + 1];              //  Mindestabstand [m]
        /*   4:  21 - 26    6.2           */ float MindestabstandFloat;                   //  Mindestabstand [m]
        /*   5:  27 - 29      3           */ char NachweiscodeChar[3 + 1];                //  Nachweiscode (gemäß Abstandstabelle)
        /*   5:  27 - 29      3           */ int NachweiscodeInt;                         //  Nachweiscode (gemäß Abstandstabelle)
        /*   6:  30 - 30      1           */ char Abstandstyp[1 + 1];                     //  Abstandstyp: ‘L’=lotrecht,’D’=direkt,’W’=waagrecht,’P’=profilprojiziert
        /*   7:  34 - 37      4           */ char Nachweiszustaende[4 + 1];               //  Nachweiszustände (‘TZUA’)
        /*   8:  38 - 40      3           */ char MastindexChar[3 + 1];                   //  Mastindex, wenn 0 automatisch
        /*   8:  38 - 40      3           */ int MastindexInt;                            //  Mastindex, wenn 0 automatisch
        /*   9:  41 - 43      3           */ char PhasenindexChar[3 + 1];                 //  Phasenindex, wenn 0 kleinster Abstand aus allen Phasen
        /*   9:  41 - 43      3           */ int PhasenindexInt;                          //  Phasenindex, wenn 0 kleinster Abstand aus allen Phasen
        /*  10:  45 - 45      1           */ char Objekttyp[1 + 1];                       //  Objekttyp (alter Objekttyp bzw. Typ der Kreuzungsberechnung)
        /*  11:  46 - 46      1           */ char SteuerungsparameterDruckausgabe[1 + 1]; //  Steuerungsparameter für Druckausgabe
        /*  12:  47 - 47      1           */ char ParameterLeitungskreuzungen[1 + 1];     //  Parameter für Leitungskreuzungen
        /*  13:  48 - 48      1           */ char NeuerObjekttyp[1 + 1];                  //  Neuer Objekttyp (’P’=Punkt, ’L’=Linie, ’F’=Fläche, ’G’=Gelände, ’X’=Leitungskreuzung, ‘W‘=Windenergieanlage, sonstiges Zeichen=Benutzerdefiniert)
        /* *** Neu ab XX.03.04 ***        */                                              //
        /*  14:  49 - 49      1           */ char Objektabstand[1 + 1];                   // Festlegung Objektabstand '0' = Freie Eingabe '1' = DIN VDE 5.62 ‘2‘ = DIN VDE 5.69 *** neu ab Version 4.5.1 *** '3' = DIN VDE 12.85 '4' = DIN EN 50341 (2002-2011) '5' = DIN EN 50341 (2016-2019) *** neu ab Version 4.11.2 *** Sonst : Freie Eingabe (Default: '0')
        /* *** Neu ab Version 3.3.0x ***  */                                              //
        /*  15:  50 - 50      1           */ char ObjektRechnen[1 + 1];                   // Objekt rechnen: ‚N’ : Nicht rechnen Sonst: Rechnen
        /* *** Neu ab Version 4.2.1 ***   */                                              //
        /*  16:  51 - 53      3           */ char KreuzungsobjektindexTeil_2_Char[3 + 1]; // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /*  16:  51 - 53      3           */ int KreuzungsobjektindexTeil_2_Int;          // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /* *** Neu ab Version 4.7.2 ***   */                                              //
        /*  17:  54 - 59      6.2         */ char Mindestabstand110kVChar[6 + 1];         // Mindestabstand 110 kV (wenn angegeben wird Mindestabstand aus Spannungsebene Phase und Zuschlag bei Laufzeit ermittelt)
        /*  17:  54 - 59      6.2         */ float Mindestabstand110kVFloat;              // Mindestabstand 110 kV (wenn angegeben wird Mindestabstand aus Spannungsebene Phase und Zuschlag bei Laufzeit ermittelt)

        virtual ~OBJ1() {}
    };
    //: OBJ1, "OBJ2", OBJ3: Kreuzungsobjekte  +++
    struct OBJ2 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%28c%28c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%s|\n%d|\n" };

        /*  1:   1 -  4      4           */ char DSK[4 + 1];                             // Satzkennung ‘OBJ2’
        /*       5 -  6      2           */                                              //
        /*  2:   7 -  9      3           */ char KreuzungsobjektindexTeil_1_Char[3 + 1]; // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*  2:   7 -  9      3           */ int KreuzungsobjektindexTeil_1_Int;          // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*      10 - 10      1           */                                              //
        /*  3:  11 - 38     28           */ char ObjektbezeichnungZeile_1[28 + 1];       // Objektbezeichnung (1.Zeile)
        /*  4:  39 - 66     28           */ char ObjektbezeichnungZeile_2[28 + 1];       // Objektbezeichnung (2.Zeile)
        /* *** Neu ab Version 4.2.1 ***  */                                              //
        /*  5:  67 - 69      3           */ char KreuzungsobjektindexTeil_2_Char[3 + 1]; // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /*  5:  67 - 69      3           */ int KreuzungsobjektindexTeil_2_Int;          // Kreuzungsobjektindex Teil 2 (Tausenderstellen)

        virtual ~OBJ2() {}
    };
    //: OBJ1, OBJ2, "OBJ3": Kreuzungsobjekte  +++
    struct OBJ3 : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%28c%28c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%s|\n%d|\n" };

        /*  1:  1 -  4      4            %4c   %s    */ char DSK[4 + 1];                             // Satzkennung ‘OBJ3’
        /*      5 -  6      2            %*2c        */                                              //
        /*  2:  7 -  9      3            %3c   %d    */ char KreuzungsobjektindexTeil_1_Char[3 + 1]; // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*  2:  7 -  9      3            %3c   %d    */ int KreuzungsobjektindexTeil_1_Int;          // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*     10 - 10      1            %*1c        */                                              //
        /*  3: 11 - 38     28            %28c  %s    */ char EigentümerZeile_1[28 + 1];              // Eigentümer (1.Zeile)
        /*  4: 39 - 66     28            %28c  %s    */ char EigentümerZeile_2[28 + 1];              // Eigentümer (2.Zeile)
        /* *** Neu ab Version 4.2.1 ***              */                                              //
        /*  5: 67 - 69      3            %3c   %d    */ char KreuzungsobjektindexTeil_2_Char[3 + 1]; // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /*  5: 67 - 69      3            %3c   %d    */ int KreuzungsobjektindexTeil_2_Int;          // Kreuzungsobjektindex Teil 2 (Tausenderstellen)

        virtual ~OBJ3() {}
    };
    //: OBJA: Erweiterung unterschiedliche Mindestabstände für Nachweiszustände
    struct OBJA : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%d|\n" };

        /*   1:  1 -  4      4  %4c      %s     */ char  DSK[4+1]                               ;   // Satzkennung ‘OBJA’  
        /*       5 -  6      2  %*2c            */                                                  //
        /*   2:  7 -  9      3  %3c      %d     */ char  Kreuzungsobjektindex_Teil_1_Char[3+1]  ;   // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen) 
        /*   2:  7 -  9      3  %3c      %d     */ int   Kreuzungsobjektindex_Teil_1_Int        ;   // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen) 
        /*      10 - 10      1  %*1c            */                                                  //
        /*   3: 11 - 11      1  %1c      %s     */ char  Kennung_Nr_1[1+1]                      ;   // Kennung Nr. 1 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert).  
        /*   4: 12 - 17    6.2  %6c      %6.2f  */ char  Mindestabstand_1_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*   4: 12 - 17    6.2  %6c      %6.2f  */ float Mindestabstand_1_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      18 - 18      1  %*1c            */                                                  //
        /*   5: 19 - 19      1  %1c      %s     */ char  Kennung_Nr_2[1+1]                      ;   // Kennung Nr. 2 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert)           
        /*   6: 20 - 25    6.2  %6c      %6.2f  */ char  Mindestabstand_2_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*   6: 20 - 25    6.2  %6c      %6.2f  */ float Mindestabstand_2_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      26 - 26      1  %*1c            */                                                  //
        /*   7: 27 - 27      1  %1c      %s     */ char  Kennung_Nr_3[1+1]                      ;   // Kennung Nr. 3 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert).  
        /*   8: 28 - 33    6.2  %6c      %6.2f  */ char  Mindestabstand_3_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*   8: 28 - 33    6.2  %6c      %6.2f  */ float Mindestabstand_3_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      34 - 34      1  %*1c            */                                                  //
        /*   9: 35 - 35      1  %1c      %s     */ char  Kennung_Nr_4[1+1]                      ;   // Kennung Nr. 4 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert).  
        /*  10: 36 - 41    6.2  %6c      %f     */ char  Mindestabstand_4_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  10: 36 - 41    6.2  %6c      %f     */ float Mindestabstand_4_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      42 - 42      1  %*1c            */                                                  //
        /*  11: 43 - 43      1  %1c      %s     */ char  Kennung_Nr_5[1+1]                      ;   // Kennung Nr. 5 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für  
        /*  12: 44 - 49    6.2  %6c      %6.2f  */ char  Mindestabstand_5_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  12: 44 - 49    6.2  %6c      %6.2f  */ float Mindestabstand_5_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      50 - 50      1  %*1c            */                                                  //
        /*  13: 51 - 51      1  %1c      %s     */ char  Kennung_Nr_6[1+1]                      ;   // Kennung Nr. 6 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert).  
        /*  14: 52 - 57    6.2  %6c      %6.2f  */ char  Mindestabstand_6_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  14: 52 - 57    6.2  %6c      %6.2f  */ float Mindestabstand_6_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      58 - 58      1  %*1c            */                                                  //
        /*  15: 59 - 59      1  %1c      %s     */ char  Kennung_Nr_7[1+1]                      ;   // Kennung Nr. 7 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert).  
        /*  16: 60 - 65    6.2  %6c      %6.2f  */ char  Mindestabstand_7_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  16: 60 - 65    6.2  %6c      %6.2f  */ float Mindestabstand_7_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      66 - 66      1  %*1c            */                                                  //
        /*  17: 67 - 67      1  %1c      %s     */ char  Kennung_Nr_8[1+1]                      ;   // Kennung Nr. 8 ('TZUA1234') auf Nachweiszustand ('ZSAN'-Satz), für den ein anderer Mindestabstand als der Wert aus 'OBJ1' verwendet werden soll (falls ' ' wird nachfolgender Abstand ignoriert).  
        /*  18: 68 - 73    6.2  %6c      %6.2f  */ char  Mindestabstand_8_Char[6+1]             ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  18: 68 - 73    6.2  %6c      %6.2f  */ float Mindestabstand_8_Float                 ;   // Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      74 - 74      1  %*1c            */                                                  //
        /* *** Neu ab Version 4.2.1 ***         */                                                  //
        /*  19: 75 - 77      3  %3c      %d     */ char  Kreuzungsobjektindex_Teil_2_Char[3+1]  ;    // Kreuzungsobjektindex Teil 2 (Tausenderstellen)  
        /*  19: 75 - 77      3  %3c      %d     */ int   Kreuzungsobjektindex_Teil_2_Int        ;    // Kreuzungsobjektindex Teil 2 (Tausenderstellen)  
        virtual ~OBJA() {}
    };
    //: OBA1: Erweiterung unterschiedliche Mindestabstände 110kV für
    struct OBA1 : Base
    {
        char const* fmtDS{ "%4c%*2c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c%*1c%1c%6c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n%s|\n%6.2f|\n" };
        /*   1:  1 -  4      4      %4c     %s      */  char DSK[4+1]                           ;   // Satzkennung "OBA1"  
        /*       5 -  6      2      %*2c            */                                              //
        /*   2:  7 - 12      6      %6c     %d      */  char  Kreuzungsobjektindex_Char[6+1]    ;   // Kreuzungsobjektindex  
        /*   2:  7 - 12      6      %6c     %d      */  int   Kreuzungsobjektindex_Int          ;   // Kreuzungsobjektindex  
        /*      13 - 13      1      %*1c            */                                              // 
        /*   3: 14 - 14      1      %1c     %s      */  char  Kennung_Nr_1[1+1]                 ;   // Kennung Nr. 1 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*   4: 15 - 20    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_1_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*   4: 15 - 20    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_1_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      21 - 21      1      %*1c            */                                          ;   //
        /*   5: 22 - 22      1      %1c     %s      */  char  Kennung_Nr_2[1+1]                 ;   // Kennung Nr. 2 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*   6: 23 - 28    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_2_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*   6: 23 - 28    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_2_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      29 - 29      1      %*1c            */                                              //
        /*   7: 30 - 30      1      %1c     %s      */  char  Kennung_Nr_3[1+1]                 ;   // Kennung Nr. 3 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*   8: 31 - 36    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_3_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*   8: 31 - 36    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_3_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      37 - 37      1      %*1c            */                                              //
        /*   9: 38 - 38      1      %1c     %s      */  char  Kennung_Nr_4[1+1]                 ;   // Kennung Nr. 4 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*  10: 39 - 44    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_4_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  10: 39 - 44    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_4_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      45 - 45      1      %*1c            */                                              //
        /*  11: 46 - 46      1      %1c     %s      */  char  Kennung_Nr_5[1+1]                 ;   // Kennung Nr. 5 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*  12: 47 - 52    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_5_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  12: 47 - 52    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_5_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      53 - 53      1      %*1c            */                                              //
        /*  13: 54 - 54      1      %1c     %s      */  char  Kennung_Nr_6[1+1]                 ;   // Kennung Nr. 6 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*  14: 55 - 60    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_6_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  14: 55 - 60    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_6_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      61 - 61      1      %*1c            */                                              //
        /*  15: 62 - 62      1      %1c     %s      */  char  Kennung_Nr_7[1+1]                 ;   // Kennung Nr. 7 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*  16: 63 - 68    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_7_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  16: 63 - 68    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_7_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*      69 - 69      1      %*1c            */                                              //
        /*  17: 70 - 70      1      %1c     %s      */  char  Kennung_Nr_8[1+1]                 ;   // Kennung Nr. 8 ("TZUA1234") auf Nachweiszustand ("ZSAN"-Satz), für den ein anderer 110kV-Mindestabstand als der Wert aus "OBJ1" verwendet werden soll (falls " " wird nachfolgender Abstand ignoriert).  
        /*  18: 71 - 76    6.2      %6c     %6.2f   */  char  Mindestabstand_110kV_8_Char[6+1]  ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        /*  18: 71 - 76    6.2      %6c     %6.2f   */  float Mindestabstand_110kV_8_Float      ;   // 110kV-Mindestabstand für vorausgehend angegebenen Nachweiszustand [m]  
        virtual ~OBA1() {}
    };
    //: OPKT: Punktobjekte  +++
    struct OPKT : Base
    {
#ifdef FLP
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%9c%7c%8c%7c%8c%*1c%3c%10c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%9.2f|\n%7.2f|\n%8.2f|\n%7.2f|\n%s|\n%d|\n%d|\n%d|\n" };
#else
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%9c%7c%8c%7c%8c%*1c%3c%*10c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%9.2f|\n%7.2f|\n%8.2f|\n%7.2f|\n%s|\n%d|\n%d|\n" };
#endif
        /*   1:   1 -  4   4              %4c   %s     */ char DSK[4 + 1];                              // Satzkennung ‘OPKT’
        /*        5 -  6   2              %*2c         */                                               //
        /*   2:   7 -  9   3              %3c   %d     */ char PunktindexTeil_1_Char[3 + 1];            // Punktindex Teil 1 (Einer- bis Hunderterstellen)
        /*   2:   7 -  9   3              %3c   %d     */ int PunktindexTeil_1_Int;                     // Punktindex Teil 1 (Einer- bis Hunderterstellen)
        /*       10 - 10   1              %*1c         */                                               //
        /*   3:  11 - 13   3              %3c   %d     */ char Kreuzungsobjektindex_Teil_1_Char[3 + 1]; // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*   3:  11 - 13   3              %3c   %d     */ int Kreuzungsobjektindex_Teil_1_Int;          // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*   4:  14 - 22   9.2            %9c   %9.2f  */ char StationChar[9 + 1];                      // Station [m]
        /*   4:  14 - 22   9.2            %9c   %9.2f  */ float StationFloat;                           // Station [m]
        /*   5:  23 - 29   7.2            %7c   %7.2f  */ char OrdinateChar[7 + 1];                     // Ordinate [m]
        /*   5:  23 - 29   7.2            %7c   %7.2f  */ float OrdinateFloat;                          // Ordinate [m]
        /*   6:  30 - 37   8.2            %8c   %8.2f  */ char FuszhoeheChar[8 + 2];                    // Fußhöhe [m]
        /*   6:  30 - 37   8.2            %8c   %8.2f  */ float FuszhoeheFloat;                         // Fußhöhe [m]
        /*   7:  38 - 44   7.2            %7c   %7.2f  */ char ObjekthoeheChar[7 + 2];                  // Objekthöhe [m]
        /*   7:  38 - 44   7.2            %7c   %7.2f  */ float ObjekthoeheFloat;                       // Objekthöhe [m]
        /*   8:  45 - 52   8              %8c   %s     */ char PunktnummerVermessung[8 + 1];            // Punktnummer (aus Vermessung)
        /*       53 - 53   1              %*1c         */                                               //
        /*   9:  54 - 56   3              %3c   %d     */ char Punktindex_Teil_2_Char[3 + 1];           // Punktindex Teil 2 (Tausenderstellen)
        /*   9:  54 - 56   3              %3c   %d     */ int Punktindex_Teil_2_Int;                    // Punktindex Teil 2 (Tausenderstellen)
        /* *** Neu ab XX.09.04 ***                     */                                               //
#ifdef FLP                                                                                              //
        /*  10:  57 - 66  10              %10c  %d     */ char MS_LinkChar[10 + 1];                     // MS-Link (nur von FLP verwendet, irrelevant für Berech- nungsverhalten)
        /*  10:  57 - 66  10              %10c  %d     */ int MS_LinkInt;                               // MS-Link (nur von FLP verwendet, irrelevant für Berech- nungsverhalten)
#endif                                                                                                  //
        /* *** Neu ab Version 4.2.1 ***                */                                               //
        /*  11:  67 - 69   3              %3c   %d     */ char KreuzungsobjektindexTeil_2_Char[3 + 1];  // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /*  11:  67 - 69   3              %3c   %d     */ int KreuzungsobjektindexTeil_2_Int;           // Kreuzungsobjektindex Teil 2 (Tausenderstellen)

        virtual ~OPKT() {}
    };
    //: OLIN: Linienobjekte  +++
    struct OLIN : Base
    {
#ifdef FLP
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%3c%3c%3c%3c%10c%3c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n" };
#else
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%3c%3c%3c%3c%*10c%3c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n" };
#endif
        /*  1:   1 -  4    4               %4c  %s */ char DSK[4 + 1];                              // Satzkennung ‘OLIN’
        /*       5 -  6    2               %*2c    */                                               //
        /*  2:   7 -  9    3               %3c  %d */ char LinienindexTeil_1_Char[3 + 1];           // Linienindex Teil1 (Einer- bis Hunderterstellen)
        /*  2:   7 -  9    3               %3c  %d */ int LinienindexTeil_1_Int;                    // Linienindex Teil1 (Einer- bis Hunderterstellen)
        /*      10 - 10    1               %*1c    */                                               //
        /*  3:  11 - 13    3               %3c  %d */ char KreuzungsobjektindexTeil_1_Char[3 + 1];  // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*  3:  11 - 13    3               %3c  %d */ int KreuzungsobjektindexTeil_1_Int;           // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*  4:  14 - 16    3               %3c  %d */ char IndexAnfangspunkt_1_Teil_1_Char[3 + 1];  // Index Anfangspunkt 1 Teil 1 (Einer- bis Hunderterstellen)
        /*  4:  14 - 16    3               %3c  %d */ int IndexAnfangspunkt_1_Teil_1_Int;           // Index Anfangspunkt 1 Teil 1 (Einer- bis Hunderterstellen)
        /*  5:  17 - 19    3               %3c  %d */ char Index_Endpunkt_1_Teil_1_Char[3 + 1];     // Index Endpunkt 1 Teil 1 (Einer- bis Hunderterstellen)
        /*  5:  17 - 19    3               %3c  %d */ int Index_Endpunkt_1_Teil_1_Int;              // Index Endpunkt 1 Teil 1 (Einer- bis Hunderterstellen)
        /*  6:  20 - 22    3               %3c  %d */ char Index_Anfangspunkt_2_Teil_2_Char[3 + 1]; // Index Anfangspunkt 2 Teil 2 (Tausenderstellen)
        /*  6:  20 - 22    3               %3c  %d */ int Index_Anfangspunkt_2_Teil_2_Int;          // Index Anfangspunkt 2 Teil 2 (Tausenderstellen)
        /*  7:  23 - 25    3               %3c  %d */ char IndexEndpunkt_2_Teil_2_Char[3 + 1];      // Index Endpunkt 2 Teil 2 (Tausenderstellen)
        /*  7:  23 - 25    3               %3c  %d */ int IndexEndpunkt_2_Teil_2_Int;               // Index Endpunkt 2 Teil 2 (Tausenderstellen)
        /*  *** Neu ab XX.09.04 ***                */                                               //
#ifdef FLP                                                                                          //
        /*  8:  26 - 35   10               %10c %d */ char MS_LinkChar[10 + 1];                     // MS-Link (nur von FLP verwendet, irrelevant für Berech- nungsverhalten)
        /*  8:  26 - 35   10               %10c %d */ int MS_LinkInt;                               // MS-Link (nur von FLP verwendet, irrelevant für Berech- nungsverhalten)
#endif                                                                                              //
        /*  *** Neu ab Version 4.2.1 ***           */                                               //
        /*  9:  36 - 38    3               %3c  %d */ char Linienindex_Teil_2_Char[3 + 1];          //  Linienindex Teil 2 (Tausenderstellen)
        /*  9:  36 - 38    3               %3c  %d */ int Linienindex_Teil_2_Int;                   //  Linienindex Teil 2 (Tausenderstellen)
        /* 10:  39 - 41    3               %3c  %d */ char Kreuzungsobjektindex_Teil_2_Char[3 + 1]; //  Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /* 10:  39 - 41    3               %3c  %d */ int Kreuzungsobjektindex_Teil_2_Int;          //  Kreuzungsobjektindex Teil 2 (Tausenderstellen)

        virtual ~OLIN() {}
    };
    //: OBFL: Flächenobjekte  +++
    struct OBFL : Base
    {
#ifdef FLP
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%3c%3c%3c%3c%3c%3c%3c%3c%10c%3c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n" };
#else
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%3c%3c%3c%3c%3c%3c%3c%3c%*10c%3c%3c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n%d|\n" };
#endif
        /*   1 :   1 -  4   4                 %4c   %s   */ char DSK[4 + 1];                                // Satzkennung ‘OBFL’
        /*         5 -  6   1                 %*1c                                                          //
        /*   2 :   7 -  9   3                 %3c   %d   */ char Flaechenindex_Teil_1_Char[3 + 1];          // Flächenindex Teil 1 (Einer- bis Hunderterstellen)
        /*   2 :   7 -  9   3                 %3c   %d   */ int Flaechenindex_Teil_1_Int;                   // Flächenindex Teil 1 (Einer- bis Hunderterstellen)
        /*        10 - 10   1                 %*1c                                                          //
        /*   3 :  11 - 13   3                 %3c   %d   */ char KreuzungsobjektindexTeil_1_Char[3 + 1];    // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*   3 :  11 - 13   3                 %3c   %d   */ int KreuzungsobjektindexTeil_1_Int;             // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*   4 :  14 - 16   3                 %3c   %d   */ char Punktindex_1_Teil_1_Char[3 + 1];           // Punktindex 1 Teil 1 (Einer- bis Hunderterstellen)
        /*   4 :  14 - 16   3                 %3c   %d   */ int Punktindex_1_Teil_1_Int;                    // Punktindex 1 Teil 1 (Einer- bis Hunderterstellen)
        /*   5 :  17 - 19   3                 %3c   %d   */ char Punktindex_2_Teil_1_Char[3 + 1];           // Punktindex 2 Teil 1 (Einer- bis Hunderterstellen)
        /*   5 :  17 - 19   3                 %3c   %d   */ int Punktindex_2_Teil_1_Int;                    // Punktindex 2 Teil 1 (Einer- bis Hunderterstellen)
        /*   6 :  20 - 22   3                 %3c   %d   */ char Punktindex_3_Teil_1_Char[3 + 1];           // Punktindex 3 Teil 1 (Einer- bis Hunderterstellen)
        /*   6 :  20 - 22   3                 %3c   %d   */ int Punktindex_3_Teil_1_Int;                    // Punktindex 3 Teil 1 (Einer- bis Hunderterstellen)
        /*   7 :  23 - 25   3                 %3c   %d   */ char Punktindex_4_Teil_1_Char[3 + 1];           // Punktindex 4 Teil 1 (Einer- bis Hunderterstellen)
        /*   7 :  23 - 25   3                 %3c   %d   */ int Punktindex_4_Teil_1_Int;                    // Punktindex 4 Teil 1 (Einer- bis Hunderterstellen)
        /*   8 :  26 - 28   3                 %3c   %d   */ char Punktindex_1_Teil_2_Char[3 + 1];           // Punktindex 1 Teil 2 (Tausenderstelle)
        /*   8 :  26 - 28   3                 %3c   %d   */ int Punktindex_1_Teil_2_Int;                    // Punktindex 1 Teil 2 (Tausenderstelle)
        /*   9 :  29 - 31   3                 %3c   %d   */ char Punktindex_2_Teil_2_Char[3 + 1];           // Punktindex 2 Teil 2 (Tausenderstelle)
        /*   9 :  29 - 31   3                 %3c   %d   */ int Punktindex_2_Teil_2_Int;                    // Punktindex 2 Teil 2 (Tausenderstelle)
        /*  10 :  32 - 34   3                 %3c   %d   */ char Punktindex_3_Teil_2_Char[3 + 1];           // Punktindex 3 Teil 2 (Tausenderstelle)
        /*  10 :  32 - 34   3                 %3c   %d   */ int Punktindex_3_Teil_2_Int;                    // Punktindex 3 Teil 2 (Tausenderstelle)
        /*  11 :  35 - 37   3                 %3c   %d   */ char Punktindex_4_Teil_2_Char[3 + 1];           // Punktindex 4 Teil 2 (Tausenderstelle)
        /*  11 :  35 - 37   3                 %3c   %d   */ int Punktindex_4_Teil_2_Int;                    // Punktindex 4 Teil 2 (Tausenderstelle)
#ifdef FLP                                                                                                  //
        /*   :  *** Neu ab XX.09.04 ***                  */                                                 //
        /*  12 :  38 - 47  10                 %10c   %d  */ char MS_Link_Char[10 + 1];                      // MS-Link (nur von FLP verwendet, irrelevant für Berech- nungsverhalten)
        /*  12 :  38 - 47  10                 %10c   %d  */ int MS_Link_Int;                                // MS-Link (nur von FLP verwendet, irrelevant für Berech- nungsverhalten)
#endif                                                                                                      //
        /*   :  *** Neu ab Version 4.2.1 ***             */                                                 //
        /*  13 :  48 - 50   3                 %3c   %d   */ char Flaechenindex_Teil_2_Char[3 + 1];          // Flächenindex Teil 2 (Tausenderstellen)
        /*  13 :  48 - 50   3                 %3c   %d   */ int Flaechenindex_Teil_2_Int;                   // Flächenindex Teil 2 (Tausenderstellen)
        /*  14 :  51 - 53   3                 %3c   %d   */ char Kreuzungsobjektindex_Teil_2_Char[3 + 1];   // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /*  14 :  51 - 53   3                 %3c   %d   */ int Kreuzungsobjektindex_Teil_2_Int;            // Kreuzungsobjektindex Teil 2 (Tausenderstellen)

        virtual ~OBFL() {}
    };
    //: "OGEL", OGE2: Geländepunkte  +++
    // Wenn vorhanden mindestens zwei Punkte pro Kreuzungsobjekt sortiert nach Station.
    // *** Änderung ab Version 1.5.1: Erweiterung der Punktindize auf 6 Stellen, abgelegt in zwei 3 stelligen Werten, um abwärtskompatibel zu bleiben. ***
    struct OGEL : Base
    {
        char const* fmtDS{ "%4c%*2c%3c%*1c%3c%9c%8c%6c%6c%6c%6c%*1c%3c%3c%3c" };
        char const* fmtPrintf{ "\n%4s|\n%3d|\n%3d|\n%9.2f|\n%8.2f|\n%6.2f|\n%6.2f|\n%6.2f|\n%6.2f|\n%3d|\n%3s|\n%3d|\n" };

        /*  1:  1 -  4  4     %4c   %4s    */ char DSK[4 + 1];                                  // Satzkennung ‘OGEL’
        /*      5 -  6  2     %*2c         */                                                   //
        /*  2:  7 -  9  3     %3c   %3d    */ char Gelaendepunktindex_Teil_1_Char[3 + 1];       // Geländepunktindex Teil 1 (Einer- bis Hunderterstellen)
        /*  2:  7 -  9  3     %3c   %3d    */ int Gelaendepunktindex_Teil_1_Int;                // Geländepunktindex Teil 1 (Einer- bis Hunderterstellen)
        /*     10 - 10  1     %*1c         */                                                   //
        /*  3: 11 - 13  3     %3c   %3d    */ char Kreuzungsobjektindex_Teil_1_Char[3 + 1];     // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*  3: 11 - 13  3     %3c   %3d    */ int Kreuzungsobjektindex_Teil_1_Int;              // Kreuzungsobjektindex Teil 1 (Einer- bis Hunderterstellen)
        /*  4: 14 - 22  9.2   %9c   %9.2f  */ char StationChar[9 + 1];                          // Station
        /*  4: 14 - 22  9.2   %9c   %9.2f  */ float StationFloat;                               // Station
        /*  5: 23 - 30  8.2   %8c   %8.2f  */ char GelaendehoeheTrassenmitte_Char[8 + 1];       // Geländehöhe in Trassenmitte
        /*  5: 23 - 30  8.2   %8c   %8.2f  */ float GelaendehoeheTrassenmitteFloat;             // Geländehöhe in Trassenmitte
        /*  6: 31 - 36  6.2   %6c   %6.2f  */ char OrdinateSeitlichUeberhoehung_1_Char[6 + 1];  // Ordinate seitliche Überhöhung1 (links)
        /*  6: 31 - 36  6.2   %6c   %6.2f  */ float OrdinateSeitlichUeberhoehung_1_Float;       // Ordinate seitliche Überhöhung1 (links)
        /*  7: 37 - 42  6.2   %6c   %6.2f  */ char SeitlicheUeberhoehung_1_Char[6 + 1];         // Seitliche Überhöhung 1 (relativ zur Höhe in Trassenmitte, d.h. bei ‚0.00‘ auf Seite gleiche Höhe wie in Trassenmitte)
        /*  7: 37 - 42  6.2   %6c   %6.2f  */ float SeitlicheUeberhoehung_1_Float;              // Seitliche Überhöhung 1 (relativ zur Höhe in Trassenmitte, d.h. bei ‚0.00‘ auf Seite gleiche Höhe wie in Trassenmitte)
        /*  8: 43 - 48  6.2   %6c   %6.2f  */ char OrdinateSeitlicheUeberhoehung_2_Char[6 + 1]; // Ordinate seitliche Überhöhung2 (rechts)
        /*  8: 43 - 48  6.2   %6c   %6.2f  */ float OrdinateSeitlicheUeberhoehung_2_Float;      // Ordinate seitliche Überhöhung2 (rechts)
        /*  9: 49 - 54  6.2   %6c   %6.2f  */ char SeitlicheUeberhoehung_2_Char[6 + 1];         // seitliche Überhöhung 2 (relativ zur Höhe in Trassenmitte)
        /*  9: 49 - 54  6.2   %6c   %6.2f  */ float SeitlicheUeberhoehung_2_Float;              // seitliche Überhöhung 2 (relativ zur Höhe in Trassenmitte)
        /*     55 - 55  1     %*1c         */                                                   //
        /*  10: 56 - 58  3     %3c   %3d   */ char Gelaendepunktindex_Teil_2_Char[3 + 1];       // Geländepunktindex Teil 2 (Tausenderstellen)
        /*  10: 56 - 58  3     %3c   %3d   */ int Gelaendepunktindex_Teil_2_Int;                // Geländepunktindex Teil 2 (Tausenderstellen)
        /*  *** Neu ab Version 4.1.3 ***   */                                                   //
        /*  11: 59 - 61  3     %3c   %3s   */ char KulturartCode[3 + 1];                        // Kulturart Code
        /*  *** Neu ab Version 4.2.1 ***   */                                                   //
        /*  12: 62 - 64  3     %3c   %3d   */ char KreuzungsobjektindexTeil_2_Char[3 + 1];      // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        /*  12: 62 - 64  3     %3c   %3d   */ int KreuzungsobjektindexTeil_2_Int;               // Kreuzungsobjektindex Teil 2 (Tausenderstellen)
        virtual ~OGEL() {}
    };
    //: OGEL, "OGE2": Geländepunkte  +++
    struct OGE2 : Base
    {
        char const* fmtDS{ "%4c%*2c%6c%30c" };
        char const* fmtPrintf{ "\n%s|\n%d|\n%s|\n" };
        /*   1:   1 -  4     4   %4c   %s   */ char DSK[4 + 1];                     // Satzkennung ‘OGE2’
        /*        5 -  6     2   %*2c       */                                      //
        /*   2:   7 - 12     6   %6c   %d   */ char GelaendepunktindexChar[6 + 1];  // Geländepunktindex
        /*   2:   7 - 12     6   %6c   %d   */ int GelaendepunktindexInt;           // Geländepunktindex
        /*   3:  14 - 43    30   %30c  %s   */ char KulturartReintext[30 + 1];      // Kulturart Reintext
        virtual ~OGE2() {}
    };
    //: OWEA: Windenergieanlagen
    struct OWEA : Base
    {
        virtual ~OWEA() {}
    };
    //: "OKRZ", OKN2, OKN3: Leitungskreuzungen
    struct OKRZ : Base
    {
        virtual ~OKRZ() {}
    };
    //: OKRZ, "OKN2", OKN3: Leitungskreuzungen
    struct OKN2 : Base
    {
        virtual ~OKN2() {}
    };
    //: OKRZ, OKN2, "OKN3": Leitungskreuzungen
    struct OKN3 : Base
    {
        virtual ~OKN3() {}
    };
    //: OKRV: Einstellungen Berechnung mit vorgegebenen kreuzenden Seilen
    struct OKRV : Base
    {
        virtual ~OKRV() {}
    };
    //: "OKSE", OKS2: Kreuzende Seile
    struct OKSE : Base
    {
        virtual ~OKSE() {}
    };
    //: OKSE, "OKS2": Kreuzende Seile
    struct OKS2 : Base
    {
        virtual ~OKS2() {}
    };
    //: OERG: Kreuzungsobjekte Ergebnis (kleinster Abstand je Nachweis, slc)
    struct OERG : Base
    {
        virtual ~OERG() {}
    };
    //: OER2: Bei Leitungskreuzungen zusätzlich zweiter Ergebnisdatensatz (slc)
    struct OER2 : Base
    {
        virtual ~OER2() {}
    };
    //: OEKB: Daten Kettenstrangbruch bei Abstandsberechnung (slc)
    struct OEKB : Base
    {
        virtual ~OEKB() {}
    };
    //: OMAB: Ausgabe alle Minderabstände (slc)
    struct OMAB : Base
    {
        virtual ~OMAB() {}
    };
    //: OMA2: Bei Leitungskreuzungen zusätzlich zweiter Ergebnisdatensatz (slc)
    struct OMA2 : Base
    {
        virtual ~OMA2() {}
    };
    //: OEXP: Kreuzungsobjekte, weitere Ergebnisse (slc)
    struct OEXP : Base
    {
        virtual ~OEXP() {}
    };
    //: OEX2: Bei Leitungskreuzungen zusätzlich zweiter Ergebnisdatensatz (slc)
    struct OEX2 : Base
    {
        virtual ~OEX2() {}
    };
    //: OPUO: Kritischer Punkt auf Phase unterhalb des kritischen Punkt auf Objekt
    struct OPUO : Base
    {
        virtual ~OPUO() {}
    };
    //: OPER: Berechnungsfehler (kein Ergebnis ermittelt, slc)
    struct OPER : Base
    {
        virtual ~OPER() {}
    };
    //: OPIA: Leitungskreuzungen: Phasenkombinationen mit identischen
    struct OPIA : Base
    {
        virtual ~OPIA() {}
    };
    //: OERI: Allgemeine Informationen zu Kreuzungsobjektberechnungen (slc)
    struct OERI : Base
    {
        virtual ~OERI() {}
    };
    //: OKRA: Ergebnisse Leitungskreuzungsachse (slc)
    struct OKRA : Base
    {
        virtual ~OKRA() {}
    };
    //: OKRK: Ergebnisse Leitungskreuzungsschnitt (slc)
    struct OKRK : Base
    {
        virtual ~OKRK() {}
    };
    //: OKRS: Ergebnisse Kreuzungsseile(slc)
    struct OKRS : Base
    {
        virtual ~OKRS() {}
    };
    //: OALT: Ergebnisse Auslegungstemperaturen
    struct OALT : Base
    {
        virtual ~OALT() {}
    };
    //: SCSA: Ergebnisse Schutzstreifenberechnung(slc)
    struct SCSA : Base
    {
        virtual ~SCSA() {}
    };
    //: STAT: Statuscode der Berechnung (slc)
    struct STAT : Base
    {
        virtual ~STAT() {}
    };

    class ParserGH263
    {
    private:
        char const* const filePath{};
        FILE* fp{};
        char lineBuf[1024];
        std::queue<std::pair<std::string, std::shared_ptr<Base>>> queueDSKs;

    public:
        ParserGH263(char const* const);
        ~ParserGH263();
    public:
        char const* const getPath();
        FILE* getFP();
        void parse();
        void statistics();
        void logRecords();
    };
    } // ns parser
} // ns cc

#endif // PARSER_GH263_H
