#include <array>
#include <map>
#include <locale>
#include <memory>
#include <queue>
#include <tuple>
#include <iostream>
#include <cassert>

// For C++ 14, because it doesn't exist here; from C++17
template <typename To, typename From>
inline std::shared_ptr<To> reinterpret_pointer_cast(
    std::shared_ptr<From> const& ptr) noexcept
{
    return std::shared_ptr<To>(ptr, reinterpret_cast<To*>(ptr.get()));
}

struct DSATTR
{
    char DSKennung[5];             // DS Kennung ‘INFO'
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
std::array<DSATTR, 92> dsks
{
     "INFO",false
    ,"INFS",false
    ,"PARS",false
    ,"BEAR",true
    ,"TXT1",false
    ,"TXT2",false
    ,"KOMM",true
    ,"PAR1",true
    ,"PARX",false
    ,"DINE",false
    ,"DBSV",false
    ,"TRRL",false
    ,"WIND",false
    ,"ZSTA",false
    ,"ZSTD",true
    ,"ZSAN",false
    ,"DWRE",false
    ,"SLG1",false
    ,"SLG2",false
    ,"SLG3",false
    ,"DTVG",false
    ,"PHAS",false
    ,"PHA2",false
    ,"PHA4",false
    ,"PHA5",false
    ,"PSYS",false
    ,"PZLF",false
    ,"HTMP",false
    ,"TPKT",false
    ,"HTM2",false
    ,"MAST",true
    ,"TRAV",true
    ,"KET1",true
    ,"KET2",true
    ,"ROLL",false
    ,"WRR1",false
    ,"WRR2",false
    ,"SCSV",false
    ,"PHAV",false
    ,"DHGM",false
    ,"EZLA",true
    ,"NEIG",false
    ,"ENEI",false
    ,"ENET",false
    ,"PATH",false
    ,"SLK1",true
    ,"SLK2",true
    ,"SLK3",false
    ,"EDHM",false
    ,"ELST",false
    ,"ESEH",false
    ,"SPAN",false
    ,"DBPD",false
    ,"EPHA",false
    ,"EGZU",false
    ,"EKAP",false
    ,"EPHF",false
    ,"OBOP",false
    ,"OBJ1",true
    ,"OBJ2",true
    ,"OBJ3",true
    ,"OBJA",false
    ,"OBA1",false
    ,"OPKT",true
    ,"OLIN",true
    ,"OBFL",true
    ,"OGEL",true
    ,"OGE2",true
    ,"OWEA",false
    ,"OKRZ",false
    ,"OKN2",false
    ,"OKN3",false
    ,"OKRV",false
    ,"OKSE",false
    ,"OKS2",false
    ,"OERG",false
    ,"OER2",false
    ,"OEKB",false
    ,"OMAB",false
    ,"OMA2",false
    ,"OEXP",false
    ,"OEX2",false
    ,"OPUO",false
    ,"OPER",false
    ,"OPIA",false
    ,"OERI",false
    ,"OKRA",false
    ,"OKRK",false
    ,"OKRS",false
    ,"OALT",false
    ,"SCSA",false
    ,"STAT",false
};
std::map<std::string, unsigned int> g_dictDSKs
{
     {"INFO",false}
    ,{"INFS",false}
    ,{"PARS",false}
    ,{"BEAR",true}
    ,{"TXT1",false}
    ,{"TXT2",false}
    ,{"KOMM",true}
    ,{"PAR1",true}
    ,{"PARX",false}
    ,{"DINE",false}
    ,{"DBSV",false}
    ,{"TRRL",false}
    ,{"WIND",false}
    ,{"ZSTA",false}
    ,{"ZSTD",true}
    ,{"ZSAN",false}
    ,{"DWRE",false}
    ,{"SLG1",false}
    ,{"SLG2",false}
    ,{"SLG3",false}
    ,{"DTVG",false}
    ,{"PHAS",false}
    ,{"PHA2",false}
    ,{"PHA4",false}
    ,{"PHA5",false}
    ,{"PSYS",false}
    ,{"PZLF",false}
    ,{"HTMP",false}
    ,{"TPKT",false}
    ,{"HTM2",false}
    ,{"MAST",true}
    ,{"TRAV",true}
    ,{"KET1",true}
    ,{"KET2",true}
    ,{"ROLL",false}
    ,{"WRR1",false}
    ,{"WRR2",false}
    ,{"SCSV",false}
    ,{"PHAV",false}
    ,{"DHGM",false}
    ,{"EZLA",true}
    ,{"NEIG",false}
    ,{"ENEI",false}
    ,{"ENET",false}
    ,{"PATH",false}
    ,{"SLK1",true}
    ,{"SLK2",true}
    ,{"SLK3",false}
    ,{"EDHM",false}
    ,{"ELST",false}
    ,{"ESEH",false}
    ,{"SPAN",false}
    ,{"DBPD",false}
    ,{"EPHA",false}
    ,{"EGZU",false}
    ,{"EKAP",false}
    ,{"EPHF",false}
    ,{"OBOP",false}
    ,{"OBJ1",true}
    ,{"OBJ2",true}
    ,{"OBJ3",true}
    ,{"OBJA",false}
    ,{"OBA1",false}
    ,{"OPKT",true}
    ,{"OLIN",true}
    ,{"OBFL",true}
    ,{"OGEL",true}
    ,{"OGE2",true}
    ,{"OWEA",false}
    ,{"OKRZ",false}
    ,{"OKN2",false}
    ,{"OKN3",false}
    ,{"OKRV",false}
    ,{"OKSE",false}
    ,{"OKS2",false}
    ,{"OERG",false}
    ,{"OER2",false}
    ,{"OEKB",false}
    ,{"OMAB",false}
    ,{"OMA2",false}
    ,{"OEXP",false}
    ,{"OEX2",false}
    ,{"OPUO",false}
    ,{"OPER",false}
    ,{"OPIA",false}
    ,{"OERI",false}
    ,{"OKRA",false}
    ,{"OKRK",false}
    ,{"OKRS",false}
    ,{"OALT",false}
    ,{"SCSA",false}
    ,{"STAT",false}
};


// INFO: Info Zeile
// Erste Zeile der Datei. Bei allen anderen Daten ist die Reihenfolge frei.
struct INFO : Base
{
    /*  1 -  4 =  4 */ std::string DSK;                // Datensatz Kennung ‘INFO'
    /*  7 - 31 = 25 */ std::string KZProgram;         // Kennung erzeugendes Programm/Version
    /* 32 - 69 = 38 */ std::string LetzeAenderung;    // Datum/Uhrzeit letzte Änderung durch Programm
    /* 70 - 73 =  4 */ int  BerechnungsModus;      // Kennung spezieller Berechnungsmodus: '0' oder fehlend(' ') : Standard / konventionell 1 : Berechnung Spanntabellen für Ausland/Export ? Braucht man noch?
    INFO()
        :DSK{ "" }
        , KZProgram{ "" }
        , LetzeAenderung{ "" }
        , BerechnungsModus{ 0 }
    {}
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
        , BerechnungsModus(BerechnungsModus)
    {}
    virtual ~INFO() {};
};

// INFS: Info-Zeile slc (nur in slc-Datei enthalten)
// *** Neu ab Version 3.7.4 ***
struct INFS : Base
{
    /*  1 -  4 =  4 */ std::string DSK;                // Datensatzkennung INFS
    /*  7 - 22 = 16 */ std::string DatZeitProgrAend;    // Datum/Uhrzeit letzte Änderung durch Programm (Format tag.monat.jahr stunde:minute)
    /* 24 - 39 = 16 */ std::string DatZeit263EingDatAend;    // Datum/Uhrzeit 263-Eingabedatei (Format tag.monat.jahr stunde:minute)
    INFS()
        : DSK{}
        , DatZeitProgrAend{}
        , DatZeit263EingDatAend{}
    {}
    virtual ~INFS() {}
};
// PARS: Aufrufparameter (nur in slc-Datei enthalten)
// *** Neu ab Version 3.7.5 ***  
struct PARS : Base
{
    /* 1 -  4 */ char DSK[4 + 1];   // DatenSatzKennung PARS
    /* 7 - 26 */ char ParmAufrufBerKern[20 + 1];  // Parameter aus Aufruf Berechnungskern (z.B. KSOC)  

    virtual ~PARS() {}
};

// BEAR: Bearbeiter   +++
struct BEAR : Base
{
    /* 1 -  4 */ char DSK[4 + 1];             // Datensatzkennung ‘BEAR’
    /* 7 - 34 */ char Bearbeiter[28 + 1];
    virtual ~BEAR() {}

};

// TXT1, TXT2: Leitung Allgemein, Beschreibung  
struct TXT1 : Base
{
    /*  1 -  4 */ char DSK[4 + 1];          // Satzkennung ‘TXT1’  
    /*  7 - 34 */ char Leitung1[28 + 1];    // Leitung (1.Zeile)  
    /* 35 - 62 */ char Leitung2[28 + 1];    // Leitung (2.Zeile)  
    /* 63 - 68 */ char Leitungsnummer1[6 + 1];   // Leitungsnummer  
    /* 69 - 71 */ int  Abschnittsnummer;          // 3 digits, Abschnittsnummer  
    //   *** Neu ab V 3.4.10 4 / Win 263 V 2.8.7 ***  
    /* 73 - 78 */ char Leitungsnummer2[5 + 1];          // Leitungsnummer (Zeichen 7-12, falls vorhanden)  
    virtual ~TXT1() {}

};
struct TXT2 : Base
{
    /* 1 -  4 */   char DSK[4 + 1];             // Satzkennung ‘TXT2’  
    /* 7 - 34 */   char Eigentuemer1[28 + 1];   //Eigentümer (1.Zeile)  
    /*35 - 62 */   char Eigentuemer2[28 + 1];   //Eigentümer (2.Zeile)  
    virtual ~TXT2() {}

};

// KOMM: Kommentarzeilen (nur Oberfläche)  +++
struct KOMM : Base
{
    /* 1 -    4    */   char DSK[4];  // Satzkennung ‘KOMM’  
    /* 7 - 1031(*) */   char Kommentartext[1024];  // (*) Kommentartext  
    /*
    (*): Es können mehrere (maximal 10) KOMM-Zeilen vorhand 
    (Wird in Eingabefeld der Oberfläche auch als einzelne Zeilen darges 
    Die Gesamtlänge des Textes aller Zeilen (inklusive Zeilenendez 
    darf aber 1024 nicht übersch 
    */
    virtual ~KOMM() {}

};

// PAR1: Berechnungseinstellungen, allgemein   +++
struct PAR1 : Base
{
    /*  1 -  4 */   char DSK[4 + 1];   // Satzkennung ‘PAR1’  
    /*  7 - 12 */   char SpezEigGewichtChar[6 + 1];         // 6.0   // Spezifisches Eisgewicht [N/m³], (‘7500’)  
    /*  7 - 12 */   float SpezEigGewichtFloat;         // 6.0   // Spezifisches Eisgewicht [N/m³], (‘7500’)  
    /* 13 - 18 */   char UmrechnungsfaktorChar[6 + 1];         // 6.2   // Umrechnungsfaktor [kg/N], (‘10.00’ bzw. ‘9.81’)  
    /* 13 - 18 */   float UmrechnungsfaktorFloat;         // 6.2   // Umrechnungsfaktor [kg/N], (‘10.00’ bzw. ‘9.81’)  
    /* 19 - 24 */   char ReckwertChar[6 + 1];         // 6.2   // Reckwert [m], (0=kein Reckwert)  
    /* 19 - 24 */   float ReckwertFloat;         // 6.2   // Reckwert [m], (0=kein Reckwert)  
    /* 25 - 25 */   char BerechnungEI[1 + 1];   // Berechnung: E=Exakte,I=Ideell  
    /* 26 - 26 */   char Berechnungsvorschrift[1 + 1];   // Berechnungsvorschrift (als Auswahlmenü) 0=Benutzerdefiniert 1= DIN VDE/0210 12.85 2= DIN VDE/0210 5.62 3= TGL (nur Eislast in Oberfläche) 4= DIN EN 50341 03.2002-01.2011 6= DIN VDE/0210 5.69 *** neu ab Version 4.5.1 *** 7= DIN EN 50341 04.2016 *** neu ab Version 4.11.1*** 8= DIN EN 50341 09.2019 *** neu ab Version 4.13.6***  
    /* 27 - 27 */   char BerechnungEM[1 + 1];   // Berechnung: E=Endzustände, M=Montagezustände (default ‚E‘)  
    // *** Neu ab V4.14.3 : Option „V“ ***  
    /* 28 -  28 */   char Seilkriechen[1 + 1];   // Seilkriechen: T=Temperaturdifferenz, K=Kriechfaktor, U=Überziehen,Z=Kriechzeit, V=Temperaturdifferenz aus Zeitvorgabe, ' '=kein  
    /* 29 -  29 */   char Seilausschwingwinkel[1 + 1];   // Berechnung Seilausschwingwinkel: J=Spannweitenreduktion nach DIN VDE 0210/12 85 N=Keine Spannweitenreduktion (Default ‚J‘)  
    /* 30 -  30 */   char Ausgangsspannung[1 + 1];   // Ausgangsspannung : V=Spannungsvorgabe, M=aus Mittelwert der gemessenen Durchhänge U=aus Ungünstigstem gemessenem Durchhang B=aus Vorgabe Bogenlänge 69 *** neu ab Version 4.7.3 *** (Default ‚V‘)  
    /* 31 -  31 */   char Reduzierung[1 + 1];   // Reduzierung des Kettenausschwingwinkels nach DIN 85 (Faktor 0.8) ‚N‘=Keine Reduzierung des Kettenausschwingwinkels Sonst= Reduzierung des Kettenausschwingwinkels (Default:‘ ')  
    /* 32 -  32 */   char Hoehenausgaben[1 + 1];   // Höhenausgaben in Ergebnisprotokollen in 'NN' bzw. 'HN' 'H'= Ausgabe in 'HN' 'N'= Ausgabe in 'NHN' Sonst= Ausgabe in 'NN' (Default: ' ')  
    /* 33-   33 */   char Trassierungsrichtlinie[1 + 1];   // Einschalten einer Trassierungsrichtlinie (Standard: “Seilverlegevorschrift DB 2004" (Objektabstände: Bautoleranz berücksichtigen (siehe 'DBSV'), altern. Temperaturwert bei Zuständen wird ausgewertet.) 'D'= Trassierungsrichtlinie ein, Sonst= Trassierungsrichtlinie aus  
    /* 34 -  34 */   char Windgesetz[1 + 1];   // Festlegung Berechnung Windgesetz 'E' = DIN EN 50341 03.02 'T' = TGL 200-0614/20 (Stand September 1987) Sonst : DIN VDE 12.85 (Default: ' ')  
    /* 35 -  35 */   char Phasenabstaende[1 + 1];   // Einstellung Berechnung Phasenabstände und Dauerzugprüfung 'E' = DIN EN 50341 03.02 Sonst : DIN VDE 12.85 (Default: ' ')  
    /* 36 -  36 */   char Sprache[1 + 1];   // Einstellung Sprache Ergebnisausgabe: 'E' = Englisch Sonst: deutsch  
    // *** Neu ab V4.1.9 ***  
    /* 37 - 37 */   char Mittelzugspannung[1 + 1];   // Einstellung Ermittlung Mittelzugspannung bei zeitabhängigem Kriechen: ‘E‘ = Exakte Berechnung (Ausgangszustand auf Mittelzugspannungsprüfung gesetzt), sonst nach ideeller Berechnung  
    // *** Neu ab V4.7.4 ***  
    /* 38 - 38 */   char LogDateiYN[1 + 1];   // Einstellung *.log-Datei: ‚L‘ : Datei erstellen, sonst nicht (Logdatei kann auch über Programmparameter ‚L‘ erzeugt werden.)  
    virtual ~PAR1() {}
};

// PARX: Erweiterte Parameter   
// *** Neu ab XX.09.05 *** (erst ab Kern Version 1.8.5 wirksam) ***  
struct PARX : Base
{

    /* 1 - 4 */ char DSK[4 + 1];      // Satzkennung ‘PARX’  
    /* 7 - 9 */ int OptionenAusgab;   // 3 Ziffern // Erweiterte Optionen für Ausgabe. '0' oder fehlend(' ') : Standard / konventionell '1': Ausgabe Spanntabellen für Sudan, unterdrückt die Info 'clamped conductor' in Protokollen (Vorgabe H.Weisse), nur sinnvoll in Verbindung mit engl. Sprachausgabe (PAR1, Spalte 36)  
    virtual ~PARX() {}
};

// DINE: Einstellungen DIN EN50341   
// *** Änderung ab Version 1.6 ***  
struct DINE : Base
{
    /*  1 -  4 */   char DSK[4 + 1];   // Satzkennung ‘DINE’  
    /*  7 -  7 */   int Eislastzone;               //   1  // Eislastzone  
    /*  9 -  9 */   int Windlastzone;               //   1  // Windlastzone  
    /* 11 - 15 */   float AlternativerObjektabstand;             // 5.2   // Alternativer Objektabstand (a_som), wird nur vom Kern ausgewertet, wenn mindestens bei einem Kreuzungsobjekt der Objektabstand nach DIN EN ausgewählt ist, s.u. Satzkennung "OBJ1". Für jedes Kreuzungsobjekt, für welches der Mindestabstand gemäß DIN EN eingestellt ist, wird geprüft, ob 1.1*a_som > angegebener Mindestabstand. Ist dies der Fall, wird der Mindestabstand auf 1.1*a_som gesetzt.  
    // *** Neu ab V 3.4.0 / Win 263 V 2.8.0 ***  
    /* 17 - 17 */ char ENStandEislast[1 + 1];       // EN-Stand Eislast: '0' oder ' '  : Eislast nach EN 03/2002 '1’ : Eislast ab EN 01/20 11  
    /* 18 - 18 */ char ENStandWindlast[1 + 1];       // EN-Stand Windlast: ''0' oder ' ' : Windlast nach EN 03/2002 '1' : Windlast ab EN 01/20 11  
    // ***Neu ab V 3.4.3 / Win 263 V 2.8.2 * **
    /* 19 - 19 */ char Staudruck[1 + 1];       // Modus Angabe Staudruck-Höhentabelle: '0' oder '' : Bezugsstaudruck '1' : Absoluter Staudruck  
    virtual ~DINE() {}
};

// DBSV: Einstellungen Trassierungsrichtlinie (früher DBE Seilverlegevorschrift)  
// *** Änderung ab Version 1.7: Erweiterung auf Trassierungsrichtlinie DBE 2004 ***  
struct DBSV : Base
{
    /*  1 -  4 */ char DSK[4 + 1];   // Satzkennung ‘DBSV’  
    /*  7 - 13 */ float Bautoleranz;        // 7.2   // Vorsorge (Bautoleranz)  
    // *** Neu ab V  3.4.4 / Win 263 V 2.8.3 ***  
    /* 14 - 14 */ char Sicherheitsabstand[1 + 1];  // Einstellung Vorsorge und Sicherheitsabstand Schutzstreifen : 'S' : Bautoleranz zu Sicherheitsabstand addieren sonst : Bautoleranz nicht zu Sicherheitsabstand addieren  
    virtual ~DBSV() {}
};

// TRRL: Erweiterte Daten Trassierungsrichtlinie  
// *** Neu ab Version 4.14.2: Namen Trassierungsrichtlinie frei definierbar ***  
struct TRRL : Base
{
    /* 1 -  4 */ char DSK[4];  // Satzkennung ‘TRRL’  
    /* 7 - 70 */ char Trassierungsrichtlinie[64];  // Name Trassierungsrichtlinie (wenn leer: nach DB Energie)  
    virtual ~TRRL() {}
};

/*
WIND: Berechnungseinstellungen, Staudruck

Anmerkung: Falls in allgemeinen Einstellungen Windgesetz nach DIN EN 50341 eingestellt ist
(siehe oben, Datenzeile PAR1, Spalte 34)
werden die Staudruckdaten anders interpretiert.
Anstatt des wirklichen Staudruckes werden in den entsprechenden Datenfeldern die Bezugsstaudrücke geles 
aus denen erst der reale Staudruck im Berechnungskern ermittelt wird.
Steht hier eine '-1', so wird der Bezugsstaudruck aus der Formel '100+7*H/6' gemäß DIN EN 50341 ermitt. 
Des Weiteren werden die Höhenstufen dann als Schwelle der Geländehöhe für den Mastfußpunkt interprert. 
D.h. ab diesem Wert für den Mastfußpunkt gilt der zugehörige Wert für den Bezugsstk.  
*/
struct WIND : Base
{
    /*  1 -  4   Char     4 */ std::string DSK;  // Satzkennung ‘WIND’  
    /*  7 -  8   Int      2 */ int AnzahlHoehenstufen;  // Anzahl Höhenstufen (<=‘7’)  
    /*  9 - 14   Float  6.0 */ float StaudruckHoehenstufe_1;  // Staudruck Höhenstufe 1, [N/m²], (‘530’)  
    /* 15 - 20   Float  6.0 */ float Hoehenstufe_1;  // Höhenstufe 1, [m], (‘15’)  
    /* 21 - 26   Float  6.0 */ float StaudruckHoehenstufe_2;  // Staudruck Höhenstufe 2, [N/m²], (‘530’)  
    /* 27 - 32   Float  6.0 */ float Hoehenstufe_2;  // Höhenstufe 2, [m], (‘40’)  
    /* 33 - 38   Float  6.0 */ float StaudruckHoehenstufe_3;  // Staudruck Höhenstufe 3, [N/m²], (‘680’)  
    /* 39 - 44   Float  6.0 */ float Hoehenstufe_3;  // Höhenstufe 3, [m], (‘100’)  
    /* 45 - 50   Float  6.0 */ float StaudruckHoehenstufe_4;  // Staudruck Höhenstufe 4, [N/m²], (‘860’)  
    /* 51 - 56   Float  6.0 */ float Hoehenstufe_4;  // Höhenstufe 4, [m], (‘150’)  
    /* 57 - 62   Float  6.0 */ float StaudruckHoehenstufe_5;  // Staudruck Höhenstufe 5, [N/m²], (‘950’)  
    /* 63 - 68   Float  6.0 */ float Hoehenstufe_5;  // Höhenstufe 5, [m], (‘200’)  
    /* 69 - 74   Float  6.0 */ float StaudruckHoehenstufe_6;  // Staudruck Höhenstufe 6, [N/m²]  
    /* 75 - 80   Float  6.0 */ float Hoehenstufe_6;  // Höhenstufe 6, [m]  
    /* 81 - 86   Float  6.0 */ float StaudruckHoehenstufe_7;  // Staudruck Höhenstufe 7, [N/m²]  
    /* 87 - 92   Float  6.0 */ float Hoehenstufe_7;  // Höhenstufe 7, [m]  
    virtual ~WIND() {}

};

// Berechnungszustände  
// ZSTA: Allgemeine Angaben zu Zuständen  
struct ZSTA : Base
{
    /*  1 -  4     4  */  char DSK[4 + 1];                        // Datensatzkennung ‘ZSTA’  
    /*  7 - 12   6.3  */  char FaktorZusatzlastChar[6 + 1];       // Faktor erhöhte Zusatzlast (‘1.0’)  
    /*  7 - 12   6.3  */  float FaktorZusatzlastFloat;          // Faktor erhöhte Zusatzlast (‘1.0’)  
    /* 13 - 18   6.3  */  char FaktorUngleicheEislastChar[6 + 1]; // Faktor ungleiche Eislast (‘0.5’)  
    /* 13 - 18   6.3  */  float FaktorUngleicheEislastFloat;    // Faktor ungleiche Eislast (‘0.5’)  
    /* 19 - 24   6.3  */  char WindlastfaktorChar[6 + 1];         // Windlastfaktor  
    /* 19 - 24   6.3  */  float WindlastfaktorFloat;            // Windlastfaktor  
    virtual ~ZSTA() {}

};

// ZSTD: Definition der Berechnungszustände   +++
struct ZSTD : Base
{
    /*  1:     1 -  4      4  */ char DSK[4 + 1];              // Datensatzkennung ‘ZSTD’  
    /*  2:     7 -  9      3  */ char ZustandsindexChar[3 + 1];           // Zustandsindex (laufende Nummer)  
    /*  2:     7 -  9      3  */ int  ZustandsindexInt;           // Zustandsindex (laufende Nummer)  
    /*  3:    10 - 12      3  */ char TemperaturCChar[3 + 1];             // Temperatur °C  
    /*  3:    10 - 12      3  */ int  TemperaturCInt;             // Temperatur °C  
    /*  4:    13 - 14         */ char Konstante[2 + 1];           // '°C' Konstante  
    /*  5:    15 - 34     20  */ char Zustandsbezeichnung[20 + 1];           // Zustandsbezeichnung   
    /*  6:    35 - 35      1  */ char KennungAusgangszustand[1 + 1];           // Kennung ‚A‘ Für Ausgangszustand, (darf nur einmal vergeben werden)  
    /*  7:    36 - 36      1  */ char KennungGrenzlast[1 + 1];           // Kennung Grenzlast (‚H‘=Höchstzug, ‚M‘=Mittelzug, 'D'=Dauerzug nach EN 2002, 'B'=Bruchkraft nach EN 2006/2009)  
    /*  8:    37 - 37      1  */ char KennungUngleicheEislast[1 + 1];           // Kennung ‚U‘ für ungleiche Eislast, darf nur einmal vergeben werden.  
    /*  9:    38 - 38      1  */ char KennungKettenausschwingwinkels[1 + 1];           // Kennung für ‚K’ Überprüfung des Kettenausschwingwinkels (darf nur einmal vergeben werden)  
    /*  10:   39 - 39      1  */ char KennungZusatzlast[1 + 1];           // Kennung ‚E‘ Berechnung mit erhöhter Zusatzlast falls diese ungleich 1 (In ZSTA)  
    /*  11:   40 - 40      1  */ char KennungEiswalze[1 + 1];           // Kennung ‚X‘ Berechnung mit Eiswalze  
    /*  12:   45 - 50    6.3  */ char LastfaktorChar[6+1];           // Lastfaktor (Zusatz- bzw. Eislast)  
    /*  12:   45 - 50    6.3  */ float LastfaktorFloat;           // Lastfaktor (Zusatz- bzw. Eislast)  
    /*  13:   51 - 56    6.3  */ char WindlastfaktorChar[6+1];           // Windlastfaktor  
    /*  13:   51 - 56    6.3  */ float WindlastfaktorFloat;           // Windlastfaktor  
    /*  14:   57 - 62    6.2  */ char ReckwertChar[6+1];           // Reckwert  
    /*  14:   57 - 62    6.2  */ float ReckwertFloat;           // Reckwert  
    /*  15:   63 - 68    6.2  */ char AusnahmelastChar[6+1];           // Ausnahmelast in N/m  
    /*  15:   63 - 68    6.2  */ float AusnahmelastFloat;           // Ausnahmelast in N/m  
    /*  16:   70 - 70      1  */ char Temperaturzuschlag[1 + 1];           // Flag, ob Zustand mit Temperaturzuschlag (aus Phasendaten) gemäss DB gerechnet wird. '+' : Mit Temperaturzschlag sonst: ohne Temperaturzuschlag  
    /* *** neu ab Version 3.6.4 *** */
    /*  17:   71 - 71      1  */ char GrenzlastBerechnung[1 + 1];           // Flag, ob Grenzlast Berechnung beeinflusst oder eine Grenzlastüberschreitung nur protokolliert wird. 'P' : nur protokollieren sonst: Einfluss auf Berechnung (Reduktion Ausgangsspannung)  
    virtual ~ZSTD() {}

};
