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
    ,{"SLG1",true}
    ,{"SLG2",true}
    ,{"SLG3",true}
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


//: INFO: Info Zeile
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

//: INFS: Info-Zeile slc (nur in slc-Datei enthalten)
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
//: PARS: Aufrufparameter (nur in slc-Datei enthalten)
// *** Neu ab Version 3.7.5 ***  
struct PARS : Base
{
    /* 1 -  4 */ char DSK[4 + 1];   // DatenSatzKennung PARS
    /* 7 - 26 */ char ParmAufrufBerKern[20 + 1];  // Parameter aus Aufruf Berechnungskern (z.B. KSOC)  

    virtual ~PARS() {}
};

//: BEAR: Bearbeiter   +++
struct BEAR : Base
{
    /* 1 -  4 */ char DSK[4 + 1];             // Datensatzkennung ‘BEAR’
    /* 7 - 34 */ char Bearbeiter[28 + 1];
    virtual ~BEAR() {}

};

//: "TXT1", TXT2: Leitung Allgemein, Beschreibung  
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
//: TXT1, "TXT2": Leitung Allgemein, Beschreibung  
struct TXT2 : Base
{
    /* 1 -  4 */   char DSK[4 + 1];             // Satzkennung ‘TXT2’  
    /* 7 - 34 */   char Eigentuemer1[28 + 1];   //Eigentümer (1.Zeile)  
    /*35 - 62 */   char Eigentuemer2[28 + 1];   //Eigentümer (2.Zeile)  
    virtual ~TXT2() {}

};

//: KOMM: Kommentarzeilen (nur Oberfläche)  +++
struct KOMM : Base
{
    /* 1 -    4    */   char DSK[4];  // Satzkennung ‘KOMM’  
    /* 7 - 1031(*) */   char Kommentartext[1024];  // (*) Kommentartext  
    /*
    (*): Es können mehrere (maximal 10) KOMM-Zeilen  
    (Wird in Eingabefeld der Oberfläche auch als einzelne Zeile 
    Die Gesamtlänge des Textes aller Zeilen (inklusive Zeil 
    darf aber 1024 nicht ü 
    */
    virtual ~KOMM() {}

};

//: PAR1: Berechnungseinstellungen, allgemein   +++
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

//: PARX: Erweiterte Parameter   
// *** Neu ab XX.09.05 *** (erst ab Kern Version 1.8.5 wirksam) ***  
struct PARX : Base
{

    /* 1 - 4 */ char DSK[4 + 1];      // Satzkennung ‘PARX’  
    /* 7 - 9 */ int OptionenAusgab;   // 3 Ziffern // Erweiterte Optionen für Ausgabe. '0' oder fehlend(' ') : Standard / konventionell '1': Ausgabe Spanntabellen für Sudan, unterdrückt die Info 'clamped conductor' in Protokollen (Vorgabe H.Weisse), nur sinnvoll in Verbindung mit engl. Sprachausgabe (PAR1, Spalte 36)  
    virtual ~PARX() {}
};

//: DINE: Einstellungen DIN EN50341   
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

//: DBSV: Einstellungen Trassierungsrichtlinie (früher DBE Seilverlegevorschrift)  
// *** Änderung ab Version 1.7: Erweiterung auf Trassierungsrichtlinie DBE 2004 ***  
struct DBSV : Base
{
    /*  1 -  4 */ char DSK[4 + 1];   // Satzkennung ‘DBSV’  
    /*  7 - 13 */ float Bautoleranz;        // 7.2   // Vorsorge (Bautoleranz)  
    // *** Neu ab V  3.4.4 / Win 263 V 2.8.3 ***  
    /* 14 - 14 */ char Sicherheitsabstand[1 + 1];  // Einstellung Vorsorge und Sicherheitsabstand Schutzstreifen : 'S' : Bautoleranz zu Sicherheitsabstand addieren sonst : Bautoleranz nicht zu Sicherheitsabstand addieren  
    virtual ~DBSV() {}
};

//: TRRL: Erweiterte Daten Trassierungsrichtlinie  
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
Anstatt des wirklichen Staudruckes werden in den entsprechenden Datenfeldern die Bezugsstaudrüc 
aus denen erst der reale Staudruck im Berechnungskern ermittelt wird.
Steht hier eine '-1', so wird der Bezugsstaudruck aus der Formel '100+7*H/6' gemäß DIN EN 50341. 
Des Weiteren werden die Höhenstufen dann als Schwelle der Geländehöhe für den Mastfußpunkt ert. 
D.h. ab diesem Wert für den Mastfußpunkt gilt der zugehörige Wert fük.  
*/
//: WIND: Berechnungseinstellungen, Staudruck  
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
//: ZSTA: Allgemeine Angaben zu Zuständen  
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
    /*  12:   45 - 50    6.3  */ char LastfaktorChar[6 + 1];           // Lastfaktor (Zusatz- bzw. Eislast)  
    /*  12:   45 - 50    6.3  */ float LastfaktorFloat;           // Lastfaktor (Zusatz- bzw. Eislast)  
    /*  13:   51 - 56    6.3  */ char WindlastfaktorChar[6 + 1];           // Windlastfaktor  
    /*  13:   51 - 56    6.3  */ float WindlastfaktorFloat;           // Windlastfaktor  
    /*  14:   57 - 62    6.2  */ char ReckwertChar[6 + 1];           // Reckwert  
    /*  14:   57 - 62    6.2  */ float ReckwertFloat;           // Reckwert  
    /*  15:   63 - 68    6.2  */ char AusnahmelastChar[6 + 1];           // Ausnahmelast in N/m  
    /*  15:   63 - 68    6.2  */ float AusnahmelastFloat;           // Ausnahmelast in N/m  
    /*  16:   70 - 70      1  */ char Temperaturzuschlag[1 + 1];           // Flag, ob Zustand mit Temperaturzuschlag (aus Phasendaten) gemäss DB gerechnet wird. '+' : Mit Temperaturzschlag sonst: ohne Temperaturzuschlag  
    /* *** neu ab Version 3.6.4 *** */
    /*  17:   71 - 71      1  */ char GrenzlastBerechnung[1 + 1];           // Flag, ob Grenzlast Berechnung beeinflusst oder eine Grenzlastüberschreitung nur protokolliert wird. 'P' : nur protokollieren sonst: Einfluss auf Berechnung (Reduktion Ausgangsspannung)  
    virtual ~ZSTD() {}

};
//: ZSAN: Abstandsnachweise   
struct ZSAN
{
    /*  1 -  4   4  */ char DSK[4 + 1];   // Satzkennung ‘ZSAN’  
    /*  7 -  9   3  */ char  SatzindexChar[3 + 1];   // Satzindex (laufende Nummer)  
    /*  7 -  9   3  */ int  SatzindexInt;   // Satzindex (laufende Nummer)  
    /* 10 - 10   1  */ char Kurzbezeichnung[1 + 1];   // Kurzbezeichnung ‚Z‘ ‚A‘, ‚U‘ ‚T‘ etc.  
    /* 11 - 11   1  */ char KennungAusschwingen[1 + 1];   // Kennung für Ausschwingen: .B‘ beide Leiter schwingen aus (nach DIN/VDE 0210 12.85) ‚A‘ nur unterkreuzender schwingt aus sonst kein Ausschwingen  
    /* *** neu ab Version 4.7.2 ***  */
    /* 12 - 14   3  */ char IndexPhasensystemChar[3 + 1];    // Index Phasensystem  
    /* 12 - 14   3  */ int IndexPhasensystemInt;    // Index Phasensystem  
    /* 20 - 22   3  */ char ZustandsindexUeberkreuzendeLeitungChar[3 + 1];    // Zustandsindex überkreuzende Leitung  
    /* 20 - 22   3  */ int ZustandsindexUeberkreuzendeLeitungInt;    // Zustandsindex überkreuzende Leitung  
    /* 23 - 25   3  */ char ZustandsindexUnterkreuzendeLeitungChar[3 + 1];    // Zustandsindex unterkreuzende Leitung  
    /* 23 - 25   3  */ int ZustandsindexUnterkreuzendeLeitungInt;    // Zustandsindex unterkreuzende Leitung  
    /* *** neu ab Version 3.7.6 ***  */
    /* 26 - 28   3  */ int ZustandsindexUeberkreuzendeLeitung;   // Zustandsindex überkreuzende Leitung (Erdseile)  
    /* 29 - 31   3  */ int ZustandsindexUnterkreuzendeLeitung;   // Zustandsindex unterkreuzende Leitung (Erdseile)  
    virtual ~ZSAN() {}
};
//: DWRE: Druckausgabe Seilkurvenberechnung  
struct DWRE
{
    /*  1 -  4        4  */ char DSK[4 + 1];        // Satzkennung ‘DWRE’  
    /*  7 -  7        1  */ char Blattkennung[1 + 1];        // Blattkennung: A-Kettenaufhängepunkte (neu ab Version 3.4.12) Z-Zustandblatt H-Seilhöhentabelle L-Einzellasten (Eingabe) (neu ab Version 4.13.6) E-Einzellasten (Ergebnisse) D-Durchhänge 1 – Zusammenfassende Ausgabe 2 – ergänzende Daten  
    /* 10 - 12        3  */ char  PhasenIndexChar[3 + 1];        // PhasenIndex – 0=Alle Phasen  
    /* 10 - 12        3  */ int  PhasenIndexInt;        // PhasenIndex – 0=Alle Phasen  
    /* 13 - 22     10.2  */ char SeilhoehentabelleChar[10 + 1];       // Bei Seilhöhentabelle: Abstand der Druckausgabe  
    /* 13 - 22     10.2  */ float SeilhoehentabelleInt;       // Bei Seilhöhentabelle: Abstand der Druckausgabe  
    /* 23 - 25        3  */ char Zustandsindex_01Char[3 + 1];        // Zustandsindex 01  
    /* 23 - 25        3  */ int Zustandsindex_01Int;        // Zustandsindex 01  
    /* 26 - 28        3  */ char Zustandsindex_02Char[3 + 1];        // Zustandsindex 02  
    /* 26 - 28        3  */ int Zustandsindex_02Int;        // Zustandsindex 02  
    /* 29 - 31        3  */ char Zustandsindex_03Char[3 + 1];        // Zustandsindex 03  
    /* 29 - 31        3  */ int Zustandsindex_03Int;        // Zustandsindex 03  
    /* 32 - 34        3  */ char Zustandsindex_04Char[3 + 1];        // Zustandsindex 04  
    /* 32 - 34        3  */ int Zustandsindex_04Int;        // Zustandsindex 04  
    /* 35 - 37        3  */ char Zustandsindex_05Char[3 + 1];        // Zustandsindex 05  
    /* 35 - 37        3  */ int Zustandsindex_05Int;        // Zustandsindex 05  
    /* 38 - 40        3  */ char Zustandsindex_06Char[3 + 1];        // Zustandsindex 06  
    /* 38 - 40        3  */ int Zustandsindex_06Int;        // Zustandsindex 06  
    /* 41 - 43        3  */ char Zustandsindex_07Char[3 + 1];        // Zustandsindex 07  
    /* 41 - 43        3  */ int Zustandsindex_07Int;        // Zustandsindex 07  
    /* 44 - 46        3  */ char Zustandsindex_08Char[3 + 1];        // Zustandsindex 08  
    /* 44 - 46        3  */ int Zustandsindex_08Int;        // Zustandsindex 08  
    /* 47 - 49        3  */ char Zustandsindex_09Char[3 + 1];        // Zustandsindex 09  
    /* 47 - 49        3  */ int Zustandsindex_09Int;        // Zustandsindex 09  
    /* 50 - 52        3  */ char Zustandsindex_10Char[3 + 1];        // Zustandsindex 10  
    /* 50 - 52        3  */ int Zustandsindex_10Int;        // Zustandsindex 10  
    /* 53 - 55        3  */ char Zustandsindex_11Char[3 + 1];        // Zustandsindex 11  
    /* 53 - 55        3  */ int Zustandsindex_11Int;        // Zustandsindex 11  
    /* 56 - 58        3  */ char Zustandsindex_12Char[3 + 1];        // Zustandsindex 12  
    /* 56 - 58        3  */ int Zustandsindex_12Int;        // Zustandsindex 12  
    /* 59 - 61        3  */ char Zustandsindex_13Char[3 + 1];        // Zustandsindex 13  
    /* 59 - 61        3  */ int Zustandsindex_13Int;        // Zustandsindex 13  
    /* 62 - 64        3  */ char Zustandsindex_14Char[3 + 1];        // Zustandsindex 14  
    /* 62 - 64        3  */ int Zustandsindex_14Int;        // Zustandsindex 14  
    /* 65 - 67        3  */ char Zustandsindex_15Char[3 + 1];        // Zustandsindex 15  
    /* 65 - 67        3  */ int Zustandsindex_15Int;        // Zustandsindex 15  
    /* 68 - 70        3  */ char Zustandsindex_16Char[3 + 1];        // Zustandsindex 16  
    /* 68 - 70        3  */ int Zustandsindex_16Int;        // Zustandsindex 16  
    /* 71 - 73        3  */ char Zustandsindex_17Char[3 + 1];        // Zustandsindex 17  
    /* 71 - 73        3  */ int Zustandsindex_17Int;        // Zustandsindex 17  
    /* 74 - 76        3  */ char Zustandsindex_18Char[3 + 1];        // Zustandsindex 18  
    /* 74 - 76        3  */ int Zustandsindex_18Int;        // Zustandsindex 18  
    /* 77 - 79        3  */ char Zustandsindex_19Char[3 + 1];        // Zustandsindex 19  
    /* 77 - 79        3  */ int Zustandsindex_19Int;        // Zustandsindex 19  
    /* 80 - 82        3  */ char Zustandsindex_20Char[3 + 1];        // Zustandsindex 20  
    /* 80 - 82        3  */ int Zustandsindex_20Int;        // Zustandsindex 20  
    virtual ~DWRE() {}
};
/*
Anmerkungen zu „Druckausgabe Seilkurvenber  
•    Es können bis zu acht Datensätze je 263-Datei vorhanden sein. (Blattkennungen A/Z/H/L/E/D/1/2), wobei jede Blattkennung allerdings nur einmal vorhanden f.  
•    Die Spalten 13 – 22 werden nur bei Blattkennung ‚H‘ertet.  
•    Je nach Blattkennung können die Zustandsindize 1-20 unterschiedliche Bedeutung:  

o       Blattkennung 'A':      Ausgabe der Kettenaufhängepunkte, Zustandsindize werden ignori 
o       Blattkennung ‚Z‘:      Für jeden Zustand, welcher in den Zustandsindize auftaucht, wird ein Zustandsblatt en.  
o       Blattkennung ‚D‘:      Für jeden Zustand,welcher in den Zustandsindize auftaucht, wird ein Durchhangsblatt en.  
o       Blattkennung ‚H‘       Ausgabe der Seilhöhentabelle, für jeden Zustand,welcher in den Zustandsindize auftaucht, wird ein Blatt mit Seilhöheeben.  
o       Blattkennung ‚L‘       Ausgabe der vorhandenen Einzellasten, Zustandsindize werden t.  
o       Blattkennung ‚E‘       Ausgabe Berechnungsergebnisse Einzellasten, für jeden Zustand,welcher in den Zustandsindize auftaucht, wird ein Blatt mit Seilhöhenben.  
o       Blattkennung ‚1‘       Für Zustandsindex 1 + 2 werden Gewichtsspannweiten, für Zustandsindize 3-5 Seilspannungen und für Indize 6-8 werden Durchhänge in dem zusammenfassenden Datenblatt ausgegeben. Zustandsindize 9-20 werriert.  
o       Blattkennung ‚2‘       Für Zustandsinex  1 + 2 werden Gewichtsspannweiten auf dem ergänzenden Datenblatt ausgegeben, Zustandsindize 3-20 werdeert.  

GH263 Datenformat                                       25.01.22                                                   Seite 8
*/

//: "SLG1", SLG2, SLG3: Seildaten   +++
// Maximal 30 Seile  
struct SLG1
{
    /* 1:  1 -  4      4  */ char DSK[4 + 1];             // Satzkennung ‘SLG1’  
    /* 2:  7 -  9      3  */ char  SeilindexChar[3 + 1];             // Seilindex (laufende Nummer)  
    /* 3:  7 -  9      3  */ int  SeilindexInt;             // Seilindex (laufende Nummer)  
    /* 3: 11 - 38     28  */ char Seilbezeichnung[28 + 1];             // Seilbezeichnung  
    /* 4: 39 - 42      4  */ char  SpannungsebeneChar[4 + 1];             // Spannungsebene [kV] (‘110’,’220’,’380’...)  
    /* 4: 39 - 42      4  */ int  SpannungsebeneInt;             // Spannungsebene [kV] (‘110’,’220’,’380’...)  
    /* 5: 43 - 44      2  */ char  AnzahlTeilleiterChar[2 + 1];             // Anzahl Teilleiter  
    /* 5: 43 - 44      2  */ int  AnzahlTeilleiterInt;             // Anzahl Teilleiter  
    /* 6: 45 - 45      1  */ char Buendelanordnung[1 + 1];             // Bündelanordnung (bei 2-er-Bündel:‘H’=Horizontal,’V’=Vertikal)  
    /* 7: 46 - 49    4.2  */ char TeilleiterabstandChar[4 + 1];             // Teilleiterabstand [m],(‘0.40’)  
    /* 7: 46 - 49    4.2  */ float TeilleiterabstandFloat;             // Teilleiterabstand [m],(‘0.40’)  
    /* 8: 50 - 54      5  */ char  Seiltyp[5 + 1];             // Seiltyp (‘LS’=Leiterseil,’ES’=Erdseil, ‘LWL’=Lichtwellenleiter)  
    /* 9: 55 - 59    5.1  */ char TemperaturdifferenzSeilkriechenChar[5 + 1];             // Temperaturdifferenz beim Seilkriechen [°C]  
    /* 9: 55 - 59    5.1  */ float TemperaturdifferenzSeilkriechenFloat;             // Temperaturdifferenz beim Seilkriechen [°C]  
    /* 10: 60 - 64    5.3  */ char KriechfaktorChar[5 + 1];             // Kriechfaktor [promille]  
    /* 10: 60 - 64    5.3  */ float KriechfaktorFloat;             // Kriechfaktor [promille]  
    /* 11: 65 - 70    6.2  */ char UeberziehfaktorChar[6 + 1];             // Überziehfaktor [%]  
    /* 11: 65 - 70    6.2  */ float UeberziehfaktorFloat;             // Überziehfaktor [%]  
    /* 12: 71 - 78    8.0  */ char KriechzeitChar[8 + 1];             // Kriechzeit [h] (‘262800’=30Jahre)  
    /* 12: 71 - 78    8.0  */ float KriechzeitFloat;             // Kriechzeit [h] (‘262800’=30Jahre)  
    /* 13: 80 - 80      1  */ char  Kennung_EN_Seil[1 + 1];             //  'E' = EN-Seil sonst : Seil konventionell  
    /* 14: 81 - 81      1  */ char  KennungSeilmanuellEingefuegt[1 + 1];             // Kennung Seil manuell eingefügt (zur Sperrung Gewicht in Win263) ’U’ = Seildatensatz manuell eingefügt, Gewicht editierbar sonst: Gewicht gesperrt.  
    /* *** Neu ab Version 4.12.0 ***  */
    /* 15: 82 - 82     1  */ char  Isolationsar[1 + 1];             // Isolationsart (‘K‘=kunststoffummantelter Leiter, ‘I‘=isoliertes Kabel, sonst: Blanker Leiter)  
    /* *** Neu ab Version 4.12.3 ***  */
    /* 16: 83   83     1  */ char VorzeichenTemperaturdifferenz[1 + 1];            // Vorzeichen Temperaturdifferenz : ‘-‘ = negativ , sonst: positiv  
    /* 17: 84   84     1  */ char VorzeichenKriechfaktor[1 + 1];            // Vorzeichen Kriechfaktor: ‘-‘ = negativ , sonst: positiv  

    virtual ~SLG1() {}
};

//: SLG1, "SLG2", SLG3: Seildaten   +++
// Maximal 30 Seile  
struct SLG2
{
    /* 1  1 -  4       4  */ char DSK[4 + 1];           // Satzkennung ‘SLG2’  
    /* 2  7 -  9       3  */ char   SeilindexChar[3 + 1];           // Seilindex (laufende Nummer)  
    /* 2  7 -  9       3  */ int   SeilindexInt;           // Seilindex (laufende Nummer)  
    /* 3 10 - 15     6.2  */ char SeildurchmesserChar[6 + 1];           // Seildurchmesser [mm]  
    /* 3 10 - 15     6.2  */ float SeildurchmesserFloat;           // Seildurchmesser [mm]  
    /* 4 16 - 23     8.2  */ char SeilquerschnittChar[8 + 1];           // Seilquerschnitt [mm²]  
    /* 4 16 - 23     8.2  */ float SeilquerschnittFloat;           // Seilquerschnitt [mm²]  
    /* 5 24 - 31     8.0  */ char E_ModulChar[8 + 1];           // E-Modul [N/mm²]  
    /* 5 24 - 31     8.0  */ float E_ModulFloat;           // E-Modul [N/mm²]  
    /* 6 32 - 41    10.8  */ char AusdehnungskoeffizientChar[10 + 1];           // Ausdehnungskoeffizient [1/K]  
    /* 6 32 - 41    10.8  */ float AusdehnungskoeffizientFloat;           // Ausdehnungskoeffizient [1/K]  
    /* 7 42 - 52    11.9  */ char SpezSeilgewichtChar[11 + 1];           // Spez. Seilgewicht (QLK)[N/mm²m]  
    /* 7 42 - 52    11.9  */ float SpezSeilgewichtFloat;           // Spez. Seilgewicht (QLK)[N/mm²m]  
    /* 8 53 - 59     7.3  */ char NormaleZusatzlastChar[7 + 1];           // Normale Zusatzlast [N/m] (5+0.1d nach DIN)  
    /* 8 53 - 59     7.3  */ float NormaleZusatzlastFloat;           // Normale Zusatzlast [N/m] (5+0.1d nach DIN)  
    /* 9 60 - 63     4.2  */ char AerodynamischerKraftbeiwertChar[4 + 1];           //  (‘1.0’,’1.1’,‘1.2’ oder ‘1,05‘)  
    /* 9 60 - 63     4.2  */ float AerodynamischerKraftbeiwertFloat;           //  (‘1.0’,’1.1’,‘1.2’ oder ‘1,05‘)  
    /* 10 64 - 71     8.2  */ char SeilgewichtDBChar[8 + 1];           // Seilgewicht aus Daten/Datenbank (zum Bestimmen QLK)  
    /* 10 64 - 71     8.2  */ float SeilgewichtDBFloat;           // Seilgewicht aus Daten/Datenbank (zum Bestimmen QLK)  
    /* 11 72 - 79     8.2  */ char FettmasseChar[8 + 1];           // Fettmasse (nur EN-Seile)  
    /* 11 72 - 79     8.2  */ float FettmasseFloat;           // Fettmasse (nur EN-Seile)  
    /**** Neu ab Version 4.0.1 *** (nur als Ergebnis in slc-Datei)  */
    /* 12 80 - 80       1  */ char KennungQLK[1 + 1];             // Kennung, ob QLK vorgegeben oder aus Seilgewicht berechnet wurde. ‘V‘ = Vorgabe, ‘G‘=gerechnet  

    virtual ~SLG2() {}
};

//: SLG1, SLG2, "SLG3": Seildaten   +++
// Maximal 30 Seile  
struct SLG3
{
    /*  1:    1 -  4       4  */  char DSK[4 + 1];  // Satzkennung ‘SLG3’  
    /*  2:    7 -  9       3  */  char SeilindexChar[3 + 3];  // Seilindex (laufende Nummer)  
    /*  2:    7 -  9       3  */  int  SeilindexInt;  // Seilindex (laufende Nummer)  
    /*  3:   10 - 17     8.2  */  char HoechstzugspannungChar[8 + 3];  // zulässige Höchstzugspannung [N/mm²]  
    /*  3:   10 - 17     8.2  */  float HoechstzugspannungFloat;  // zulässige Höchstzugspannung [N/mm²]  
    /*  4:   18 - 25     8.2  */  char MittelzugspannungChar[8 + 3];  // zulässige Mittelzugspannung [N/mm²]  
    /*  4:   18 - 25     8.2  */  float MittelzugspannungFloat;  // zulässige Mittelzugspannung [N/mm²]  
    /*  5:   26 - 33     8.2  */  char DauerzugspannungChar[8 + 3];  // zulässige Dauerzugspannung [N/mm²]  
    /*  5:   26 - 33     8.2  */  float DauerzugspannungFloat;  // zulässige Dauerzugspannung [N/mm²]  
    /*  6:   34 - 41     8.0  */  char BruchkraftChar[8 + 3];  // rechnerische Bruchkraft [N]  
    /*  6:   34 - 41     8.0  */  float BruchkraftFloat;  // rechnerische Bruchkraft [N]  
    /*  7:   42 - 47     6.2  */  char StahlgewichtsanteilChar[6 + 3];  // Stahlgewichtsanteil [%]  
    /*  7:   42 - 47     6.2  */  float StahlgewichtsanteilFloat;  // Stahlgewichtsanteil [%]  
    /* *** Neu ab Version 4 .9.5 *** (zur Berechnung des Stahlgewichtsanteils)  */
    /*  8: 48 - 55     8.2  */  char StahlquerschnittChar[8 + 3];  // Stahlquerschnitt [mm²]  
    /*  8: 48 - 55     8.2  */  float StahlquerschnittFloat;  // Stahlquerschnitt [mm²]  

    virtual ~SLG3() {}
};
//: DTVG: Zeitabhängige Delta-T Vorgaben für Seilkriechen  
struct DTVG
{
    virtual ~DTVG() {}
};
//: "PHAS", PHA2, PHA4, PHA5: Phasen   
struct PHAS
{
    virtual ~PHAS() {}
};
//: PHAS, "PHA2", PHA4, PHA5: Phasen   
struct PHA2
{
    virtual ~PHA2() {}
};
//: PHAS, PHA2, "PHA4", PHA5: Phasen   
struct PHA4
{
    virtual ~PHA4() {}
};
//: PHAS, PHA2, PHA4, "PHA5": Phasen   
struct PHA5
{
    virtual ~PHA5() {}
};
//: PSYS: Phasensysteme   
struct PSYS
{
    virtual ~PSYS() {}
};
//: PZLF: Zusätzliche Phasenabstandsberechnungen  
struct PZLF
{
    virtual ~PZLF() {}
};
//: HTMP (oder TPKT): Daten Hochtemperaturseile / Transitionspunkte   
//: TPKT (oder HTMP): Daten Hochtemperaturseile / Transitionspunkte   
struct HTMP
{
    virtual ~HTMP() {}
};
//: HTM2: Daten Hochtemperaturseile 2  
struct HTM2
{
    virtual ~HTM2() {}
};
//: MAST: Maststandorte  +++
// Maximal 100 Maste  
struct MAST
{
    /*  1:    1 -   4       4   */ char DSK[4 + 1];          //  Satzkennung ‘MAST’  
    /*  2:    7 -   9       3   */ char  MastindexChar[3 + 1];          //  Mastindex (laufende Nummer)  
    /*  2:    7 -   9       3   */ int   MastindexInt;          //  Mastindex (laufende Nummer)  
    /*  3:   11 -  16       6   */ char  MastnummerMastname_1[6 + 1];          //  Mastnummer / Mastname, Zeichen 1-6   
    /*  4:   18 -  18       1   */ char  Masttyp[1 + 1];          //  Masttyp (‘A‘‚ ‘T‘ oder 'X' )  
    /*  5:   20 -  26       7   */ char  Masttypenbezeichnung_1[7 + 1];          //  Masttypenbezeichnung(=Masttyp aus CIT-Datei), Zeichen 1-7 !Achtung siehe auch Spalte 69-101!  
    /*  6:   27 -  32     6.2   */ char AusfuehrungChar[6 + 1];          //  Ausführung (Fußverlängerung) [m]  
    /*  6:   27 -  32     6.2   */ float AusfuehrungFloat;          //  Ausführung (Fußverlängerung) [m]  
    /*  7:   33 -  41     9.2   */ char LaengenstationMaststandortChar[9 + 1];          //  Längenstation Maststandort [m]  
    /*  7:   33 -  41     9.2   */ float LaengenstationMaststandortFloat;          //  Längenstation Maststandort [m]  
    /*  8:   42 -  49     8.2   */ char HoeheMastfusspunktChar[8 + 1];          //  Höhe Mastfußpunkt [m]  
    /*  8:   42 -  49     8.2   */ float HoeheMastfusspunktFloat;          //  Höhe Mastfußpunkt [m]  
    /*  9:   50 -  58     9.3   */ char LeitungswinkelChar[9 + 1];          //  Leitungswinkel [gon] (200=Flucht)  
    /*  9:   50 -  58     9.3   */ float LeitungswinkelFloat;          //  Leitungswinkel [gon] (200=Flucht)  
    /* 10:   59 -  67     9.3   */ char StellwinkelChar[9 + 1];          //  Stellwinkel [gon] (0=Winkelhalbierende)  
    /* 10:   59 -  67     9.3   */ float StellwinkelFloat;          //  Stellwinkel [gon] (0=Winkelhalbierende)  
    /* 11:   69 - 101      33   */ char  Masttypenbezeichnung_2[33 + 1];          //  Masttypenbezeichnung,  Zeichen 8-40  
    /* *** neu ab Version 3.6.4 (Änderung IHL) ***  */
    /* 12:  102 - 107     6.2   */ char OrdinateMaststandortChar[6 + 1];             // Ordinate Maststandort (Wert wird  als Ordinaten-Zuschlag für Kettenaufhängepunkte interpretiert. Der Wert bezieht sich rechtwinklig auf das dem Mast vorhergehenden Leitungsfeld, beim 1. Mast ist es das nachfolgende Feld. )  
    /* 12:  102 - 107     6.2   */ float OrdinateMaststandortFloat;             // Ordinate Maststandort (Wert wird  als Ordinaten-Zuschlag für Kettenaufhängepunkte interpretiert. Der Wert bezieht sich rechtwinklig auf das dem Mast vorhergehenden Leitungsfeld, beim 1. Mast ist es das nachfolgende Feld. )  
    /* *** neu ab Version 4.6.3 ***  */
    /* 13:  109 - 134     26    */ char MastnummerMastname_2[26 + 1];            // Mastnummer / Mastname, Zeichen 7-32  

    virtual ~MAST() {}
};
//: TRAV: Aufhängepunkte (Traversen) +++ 
struct TRAV
{
    /* *** Änderung ab Version 4.5.1 Satzkennung auch anders ***  */
    /*  1:  1  -  4      4  */ char DSK[4 + 1];             // Satzkennung ‘TRAV’ (auch ‘AUFH‘ erlaubt, bitte als Standard ‘TRAV‘ verwenden)  
    /*  2:  7  -  9      3  */ char  MastindexChar[3 + 1];             // Mastindex  
    /*  2:  7  -  9      3  */ int  MastindexInt;             // Mastindex  
    /*  3:  10 - 12      3  */ char   PhasenindexChar[3 + 1];             // Phasenindex  
    /*  3:  10 - 12      3  */ int   PhasenindexInt;             // Phasenindex  
    /*  4:  13 - 19    7.2  */ char TraversenhoeheChar[7 + 1];             // Traversenhöhe [m]   
    /*  4:  13 - 19    7.2  */ float TraversenhoeheFloat;             // Traversenhöhe [m]   
    /*  5:  20 - 26    7.2  */ char AusladungChar[7 + 1];             // Ausladung (links positiv)  
    /*  5:  20 - 26    7.2  */ float AusladungFloat;             // Ausladung (links positiv)  
    /*  6:  27 - 34    8.2  */ char StellwinkelTraverseChar[8 + 1];             // Stellwinkel der Traverse (0=Maststellwinkel) [gon]  
    /*  6:  27 - 34    8.2  */ float StellwinkelTraverseFloat;             // Stellwinkel der Traverse (0=Maststellwinkel) [gon]  
    /*  7:  41 - 46    6.2  */ char  KettenlaengeChar[6 + 2];             // gemessene Kettenlänge [m]  
    /*  7:  41 - 46    6.2  */ float  KettenlaengeFloat;             // gemessene Kettenlänge [m]  
    /*  8:  47 - 49      3  */ char    KettenindexChar[3 + 1];             // Kettenindex  
    /*  8:  47 - 49      3  */ int    KettenindexInt;             // Kettenindex  
    /*  9:  51 - 57    7.2  */ char HoehenbezugStaudruckChar[7 + 1];             // Höhenbezug Staudruck (EN-Norm) 0: Höhenbezug ist Traversenhöhe >0 : Direkte Angabe Höhenbezug für Berechnung Staudruck  
    /*  9:  51 - 57    7.2  */ float HoehenbezugStaudruckFloat;             // Höhenbezug Staudruck (EN-Norm) 0: Höhenbezug ist Traversenhöhe >0 : Direkte Angabe Höhenbezug für Berechnung Staudruck  
    /* *** Neu ab V 3.4.12 / Win 263 V 2.8.8 ***  */
    /* 10:  58 - 64    7.2  */ char TraversenexzentrizitaetChar[7 + 1];             // Traversenexzentrizität. Positiv: In Leitungsrichtung, negativ: entgegen Leitungsrichtung.  
    /* 10:  58 - 64    7.2  */ float TraversenexzentrizitaetFloat;             // Traversenexzentrizität. Positiv: In Leitungsrichtung, negativ: entgegen Leitungsrichtung.  

    virtual ~TRAV() {}
};
//: "KET1", KET2: Ketten   +++
// Maximal 1000 Ketten  
struct KET1
{
    /*  1:  1  -  4     4  */  char DSK[4 + 1];  // Satzkennung ‘KET1’  
    /*  2:  7  -  9     3  */  char  KettenindexChar[3 + 1];  // Kettenindex (laufende Nummer)  
    /*  2:  7  -  9     3  */  int  KettenindexInt;  // Kettenindex (laufende Nummer)  
    /*  3:  11 - 11     1  */  char Kettentyp[1 + 1];  // Kettentyp (‘A’=Abspann-, ‘H’=Hänge-,’V’=V-Kette, ’S’=Stützer)  
    /*  4:  12 - 14     3  */  char AnzahlKettenstraengeChar[3 + 1];  // Anzahl Kettenstränge  
    /*  4:  12 - 14     3  */  int  AnzahlKettenstraengeInt;  // Anzahl Kettenstränge  
    /*  5:  16 - 17     2  */  char Kettentypbezeichnung[2 + 1];  // Kettentypbezeichnung (‘DA’,’DH’,’EH’ etc.)  
    /*  6:  19 - 46    28  */  char KettenbezeichnungIsolator[28 + 1];  // Kettenbezeichnung/Isolator  
    /*  7:  48 - 56     9  */  char Schwingenbezeichnung[9 + 1];  // Schwingenbezeichnung  
    /*  8:  58 - 62     5  */  char Kettennummer[5 + 1];  // Kettennummer (nur von FLP verwendet)  

    virtual ~KET1() {}
};

//: KET1, "KET2": Ketten   +++
// Maximal 1000 Ketten  
struct KET2
{
/*    1   1 -  4       4    */  char DSK[4+1]  ;  // Satzkennung ‘KET2’  
/*        5 -  6       1
/*    2   7 -  9       3    */  char   KettenindexChar[3+1] ;  // Kettenindex (laufende Nummer)  
/*    2   7 -  9       3    */  int   KettenindexInt ;  // Kettenindex (laufende Nummer)  
/*    3  10 - 14     5.2    */  char KettenlaengeChar[5+1] ;  // Kettenlänge bis UK Bündel [m]  
/*    3  10 - 14     5.2    */  float KettenlaengeFloat ;  // Kettenlänge bis UK Bündel [m]  
/*    4  15 - 19     5.2    */  char VLaengeChar[5+1] ;  // V-Länge (nur bei V-Ketten) [m]  
/*    4  15 - 19     5.2    */  float VLaengeFloat ;  // V-Länge (nur bei V-Ketten) [m]  
/*    5  20 - 24     5.2    */  char FesteLaengeChar[5+1] ;  // Feste Länge ab Traverse [m]  
/*    5  20 - 24     5.2    */  float FesteLaengeFloat ;  // Feste Länge ab Traverse [m]  
/*    6  25 - 29     5.2    */  char  SchwingenlaengeChar[5+1];  // Schwingenlänge [m]  
/*    6  25 - 29     5.2    */  float  SchwingenlaengeFloat;  // Schwingenlänge [m]  
/*    7  30 - 35     6.0    */  char KettengewichtChar[6+1] ;  // Kettengewicht [N]  
/*    7  30 - 35     6.0    */  float KettengewichtFloat ;  // Kettengewicht [N]  
/*    8  36 - 41     6.0    */  char EinfachesEisgewichtKetteChar[6+1] ;  // Einfaches Eisgewicht auf Kette [N]  
/*    8  36 - 41     6.0    */  float EinfachesEisgewichtKetteFloat ;  // Einfaches Eisgewicht auf Kette [N]  
/*    9  42 - 47     6.0    */  char SchwingengewichtChar[6+1] ;  // Schwingengewicht [N]  
/*    9  42 - 47     6.0    */  float SchwingengewichtFloat ;  // Schwingengewicht [N]  
/*   10  48 - 54     7.2    */  char GrenzausschwingwinkelInnenChar[7+1] ;  // Grenzausschwingwinkel innen [grad]  
/*   10  48 - 54     7.2    */  float GrenzausschwingwinkelInnenFloat ;  // Grenzausschwingwinkel innen [grad]  
/*   11  55 - 61     7.2    */  char GrenzausschwingwinkelAußenChar[7+1] ;  // Grenzausschwingwinkel außen [grad]  
/*   11  55 - 61     7.2    */  float GrenzausschwingwinkelAußenFloat ;  // Grenzausschwingwinkel außen [grad]  
/*   12  62 - 67     6.0    */  char ZusatzgewichtChar[6+1] ;  // Zusatzgewicht [N]  
/*   12  62 - 67     6.0    */  float ZusatzgewichtFloat ;  // Zusatzgewicht [N]  
/*   13  68 - 73     6.3    */  char EinbaulaengeChar[6+1] ;  // Einbaulänge [m]  
/*   13  68 - 73     6.3    */  float EinbaulaengeFloat ;  // Einbaulänge [m]  
/*   14  74 - 79     6.3    */  char SchirmdurchmesserChar[6+1] ;  // Schirmdurchmesser [m]  
/*   14  74 - 79     6.3    */  float SchirmdurchmesserFloat ;  // Schirmdurchmesser [m]  
/*   15  80 - 85     6.3    */  char StrunkdurchmesserChar[6+1] ;  // Strunkdurchmesser [m]  
/*   15  80 - 85     6.3    */  float StrunkdurchmesserFloat ;  // Strunkdurchmesser [m]  
/*   16  86 - 91     6.3    */  char ProjizierteFlaecheChar[6+1] ;  // Projizierte Fläche [m²]  
/*   16  86 - 91     6.3    */  float ProjizierteFlaecheFloat ;  // Projizierte Fläche [m²]  
/* *** Neu ab Version 4.10.0 *** (V-Kettenstrangbruch)  */
/*   17  92 -  96    5.2    */  char VKetteVersatzAufhaengungMastInnenChar[5+1] ;  //  V-Kette Versatz Aufhängung zum Mast hin (innen)  
/*   17  92 -  96    5.2    */  float VKetteVersatzAufhaengungMastInnenFloat ;  //  V-Kette Versatz Aufhängung zum Mast hin (innen)  
/*   18  97 - 101    5.2    */  char VKetteVersatzAufhaengungMastAussenChar[5+1] ;  //  V-Kette Versatz Aufhängung vom Mast weg (außen)  
/*   18  97 - 101    5.2    */  float VKetteVersatzAufhaengungMastAussenFloat ;  //  V-Kette Versatz Aufhängung vom Mast weg (außen)  

    virtual ~KET2() {}
};
//: ROLL: Rollen (bei Berechnung Seile in Rollen)  
struct ROLL
{
    virtual ~ROLL() {}
};
//: "WRR1", WRR2: Einstellungen Spanntabellen  
struct WRR1
{
    virtual ~WRR1() {}
};
//: WRR1, "WRR2": Einstellungen Spanntabellen  
struct WRR2
{
    virtual ~WRR2() {}
};
//: SCSV: Einstellungen Schutzstreifen  
struct SCSV
{
    virtual ~SCSV() {}
};
//: PHAV: Einstellungen Phasenabstandsberechnung  
struct PHAV
{
    virtual ~PHAV() {}
};
//: DHGM: Durchhangsmessungen  
struct DHGM
{
    virtual ~DHGM() {}
};
//: EZLA: Einzel- und Streckenlasten  +++
struct EZLA
{
    virtual ~EZLA() {}
};
//: NEIG: Eingabe Seilneigung  
struct NEIG
{
    virtual ~NEIG() {}
};
struct ENEI
{
    virtual ~ENEI() {}
};
//: ENEI: Ergebnisse Seilneigung (slc)  
struct ENET
{
    virtual ~ENET() {}
};
//: PATH: Dateipfad Berechnungsprogramm (slc)  
struct PATH
{
    virtual ~PATH() {}
};
//: "SLK1", SLK2, SLK3: Ergebnis Seilkurvenberechnung (slc)  +++
struct SLK1
{
    virtual ~SLK1() {}
};
//: SLK1, "SLK2", SLK3: Ergebnis Seilkurvenberechnung (slc)  +++
struct SLK2
{
    virtual ~SLK2() {}
};
//: SLK1, SLK2, "SLK3": Ergebnis Seilkurvenberechnung (slc)  
struct SLK3
{
    virtual ~SLK3() {}
};
//: EDHM: Ergebnisse Durchhangsmessungen (slc)  
struct EDHM
{
    virtual ~EDHM() {}
};
//: ELST: Ergebnis Einzellasten (slc)  
struct ELST
{
    virtual ~ELST() {}
};
//: ESEH: Ergebnis Seilhöhentabellen (slc)  
struct ESEH
{
    virtual ~ESEH() {}
};
//: SPAN: Ergebnisse Spannweiten an Maste (slc)  
struct SPAN
{
    virtual ~SPAN() {}
};
//: DBPD: Ergebnisse Phasendaten DB Energie (slc)  
struct DBPD
{
    virtual ~DBPD() {}
};
//: EPHA: Ergebnisse Ausgabe Phasen (slc)  
struct EPHA
{
    virtual ~EPHA() {}
};
//: EGZU: Ergebnisse Grenzspannungen überschritten (slc)  
struct EGZU
{
    virtual ~EGZU() {}
};
//: EKAP: Ergebnisse Kettenaufhängepunkte (slc)  
struct EKAP
{
    virtual ~EKAP() {}
};
//: EPHF: Ergebnisse feldbezogene Phasendaten (slc)  
struct EPHF
{
    virtual ~EPHF() {}
};
//: OBOP: Einstellungen Berechnung Kreuzungsobjekte  
struct OBOP
{
    virtual ~OBOP() {}
};
//: "OBJ1", OBJ2, OBJ3: Kreuzungsobjekte  +++
struct OBJ1
{
    virtual ~OBJ1() {}
};
//: OBJ1, "OBJ2", OBJ3: Kreuzungsobjekte  +++
struct OBJ2
{
    virtual ~OBJ2() {}
};
//: OBJ1, OBJ2, "OBJ3": Kreuzungsobjekte  +++
struct OBJ3
{
    virtual ~OBJ3() {}
};
//: OBJA: Erweiterung unterschiedliche Mindestabstände für Nachweiszustände  
struct OBJA
{
    virtual ~OBJA() {}
};
//: OBA1: Erweiterung unterschiedliche Mindestabstände 110kV für  
struct OBA1
{
    virtual ~OBA1() {}
};
//: OPKT: Punktobjekte  +++
struct OPKT
{
    virtual ~OPKT() {}
};
//: OLIN: Linienobjekte  +++
struct OLIN
{
    virtual ~OLIN() {}
};
//: OBFL: Flächenobjekte  +++
struct OBFL
{
    virtual ~OBFL() {}
};
//: "OGEL", OGE2: Geländepunkte  +++
struct OGEL
{
    virtual ~OGEL() {}
};
//: OGEL, "OGE2": Geländepunkte  +++
struct OGE2
{
    virtual ~OGE2() {}
};
//: OWEA: Windenergieanlagen  
struct OWEA
{
    virtual ~OWEA() {}
};
//: "OKRZ", OKN2, OKN3: Leitungskreuzungen  
struct OKRZ
{
    virtual ~OKRZ() {}
};
//: OKRZ, "OKN2", OKN3: Leitungskreuzungen  
struct OKN2
{
    virtual ~OKN2() {}
};
//: OKRZ, OKN2, "OKN3": Leitungskreuzungen  
struct OKN3
{
    virtual ~OKN3() {}
};
//: OKRV: Einstellungen Berechnung mit vorgegebenen kreuzenden Seilen  
struct OKRV
{
    virtual ~OKRV() {}
};
//: "OKSE", OKS2: Kreuzende Seile  
struct OKSE
{
    virtual ~OKSE() {}
};
//: OKSE, "OKS2": Kreuzende Seile  
struct OKS2
{
    virtual ~OKS2() {}
};
//: OERG: Kreuzungsobjekte Ergebnis (kleinster Abstand je Nachweis, slc)  
struct OERG
{
    virtual ~OERG() {}
};
//: OER2: Bei Leitungskreuzungen zusätzlich zweiter Ergebnisdatensatz (slc)  
struct OER2
{
    virtual ~OER2() {}
};
//: OEKB: Daten Kettenstrangbruch bei Abstandsberechnung (slc)  
struct OEKB
{
    virtual ~OEKB() {}
};
//: OMAB: Ausgabe alle Minderabstände (slc)  
struct OMAB
{
    virtual ~OMAB() {}
};
//: OMA2: Bei Leitungskreuzungen zusätzlich zweiter Ergebnisdatensatz (slc)  
struct OMA2
{
    virtual ~OMA2() {}
};
//: OEXP: Kreuzungsobjekte, weitere Ergebnisse (slc)  
struct OEXP
{
    virtual ~OEXP() {}
};
//: OEX2: Bei Leitungskreuzungen zusätzlich zweiter Ergebnisdatensatz (slc)  
struct OEX2
{
    virtual ~OEX2() {}
};
//: OPUO: Kritischer Punkt auf Phase unterhalb des kritischen Punkt auf Objekt  
struct OPUO
{
    virtual ~OPUO() {}
};
//: OPER: Berechnungsfehler (kein Ergebnis ermittelt, slc)  
struct OPER
{
    virtual ~OPER() {}
};
//: OPIA: Leitungskreuzungen: Phasenkombinationen mit identischen  
struct OPIA
{
    virtual ~OPIA() {}
};
//: OERI: Allgemeine Informationen zu Kreuzungsobjektberechnungen (slc)  
struct OERI
{
    virtual ~OERI() {}
};
//: OKRA: Ergebnisse Leitungskreuzungsachse (slc)  
struct OKRA
{
    virtual ~OKRA() {}
};
//: OKRK: Ergebnisse Leitungskreuzungsschnitt (slc)  
struct OKRK
{
    virtual ~OKRK() {}
};
//: OKRS: Ergebnisse Kreuzungsseile(slc)  
struct OKRS
{
    virtual ~OKRS() {}
};
//: OALT: Ergebnisse Auslegungstemperaturen  
struct OALT
{
    virtual ~OALT() {}
};
//: SCSA: Ergebnisse Schutzstreifenberechnung(slc)  
struct SCSA
{
    virtual ~SCSA() {}
};
//: STAT: Statuscode der Berechnung (slc)  
struct STAT
{
    virtual ~STAT() {}
};
