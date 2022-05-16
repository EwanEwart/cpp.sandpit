#include <array>

struct DSATTR
{
    char DSKennung[5];             // DS Kennung ‘INFO'
    bool req;
};

enum DSKS
{
    INFO
    , INFS
    , PARS
    , BEAR
    , TXT1
    , TXT2
    , KOMM
    , PAR1
    , PARX
    , DINE
    , DBSV
    , TRRL
    , WIND
    , ZSTA
    , ZSTD
    , ZSAN
    , DWRE
    , SLG1
    , SLG2
    , SLG3
    , DTVG
    , PHAS
    , PHA2
    , PHA4
    , PHA5
    , PSYS
    , PZLF
    , HTMP
    , TPKT
    , HTM2
    , MAST
    , TRAV
    , KET1
    , KET2
    , ROLL
    , WRR1
    , WRR2
    , SCSV
    , PHAV
    , DHGM
    , EZLA
    , NEIG
    , ENEI
    , ENET
    , PATH
    , SLK1
    , SLK2
    , SLK3
    , EDHM
    , ELST
    , ESEH
    , SPAN
    , DBPD
    , EPHA
    , EGZU
    , EKAP
    , EPHF
    , OBOP
    , OBJ1
    , OBJ2
    , OBJ3
    , OBJA
    , OBA1
    , OPKT
    , OLIN
    , OBFL
    , OGEL
    , OGE2
    , OWEA
    , OKRZ
    , OKN2
    , OKN3
    , OKRV
    , OKSE
    , OKS2
    , OERG
    , OER2
    , OEKB
    , OMAB
    , OMA2
    , OEXP
    , OEX2
    , OPUO
    , OPER
    , OPIA
    , OERI
    , OKRA
    , OKRK
    , OKRS
    , OALT
    , SCSA
    , STAT
};
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


struct INFO
{
    char DSKennung[4];          // Datensatz Kennung ‘INFO'
    char notUsed[2];            // two spaces
    char KZProgram[25];         // Kennung erzeugendes Programm/Version
    char LetzeAenderung[38];    // Datum/Uhrzeit letzte Änderung durch Programm
    int  BerechnungsModus;      // Kennung spezieller Berechnungsmodus: '0' oder fehlend(' ') : Standard / konventionell 1 : Berechnung Spanntabellen für Ausland/Export ? Braucht man noch?
};


struct BEAR
{
    char KZSatz[4];             // Datensatzkennung ‘BEAR’
    char notUsed[2];            // two spaces
    char Bearbeiter[28];
};
struct KOMM
{
    char KZSatz[4];             // Datensatzkennung ‘BEAR’
    char notUsed[2];            // two spaces
    char Eigentuemer[28];        // Eigentümer (1.Zeile)
    char Kommentartext[1024];
    /*
    Kommentartext:
    Es können mehrere (maximal 10) KOMM-Zeil 
    (Wird in Eingabefeld der Oberfläche auch als einzelne Zei 
    Die Gesamtlänge des Textes aller Zeilen
    (inklusive Zeilenendezeichen)
    darf 1024 aber nicht überschreiten.
    */
};
struct PAR1
{
    char KZSatz[4];                 // Datensatzkennung ‘BEAR’
    char notUsed[2];                // two spaces for readability
    float SpezifischesEisgewicht; //  [N/m³], (‘7500’)
    float Umrechnungsfaktor;    // Umrechnungsfaktor [kg/N], (‘10.00’ bzw. ‘9.81’)
    float Reckwert;             // Reckwert [m], (0=kein Reckwert)
    /*
    Berechnungsvorschrift (als Auswahlmenü)
    0=Benutzerdefiniert
    1= DIN VDE/0210 12.85
    2= DIN VDE/0210 5.62
    3= TGL (nur Eislast in Oberfläche)
    4= DIN EN 50341 03.2002-01.2011
    6= DIN VDE/0210 5.69 *** neu ab Version 4.5.1 ***
    7= DIN EN 50341 04.2016 *** neu ab Version 4.11.1***
    8= DIN EN 50341 09.2019 *** neu ab Version 4.13.6***
    */
    char BerechnungsTyp;          // Berechnung: E=Exakte,I=Ideell
    char Berechnungsvorschrift;
    char BerechnungEM; // Berechnung: E=Endzustände, M=Montagezustände (default ‚E‘)

    /* *** Neu ab V4.14.3 : Option „V“ ****/
    /* Seilkriechen:
    T=Temperaturdifferenz,
    K=Kriechfaktor,
    U=Überziehen,
    Z=Kriechzeit,
    V=Temperaturdifferenz aus Zeitvorgabe,
    ' '=kein
    */
    char Seilkriechen;
    /*
    Berechnung Seilausschwingwinkel:
    J=Spannweitenreduktion nach DIN VDE 0210/12 85
    N=Keine Spannweitenreduktion
    (Default ‚J‘)
    */
    char Seilausschwingwinkel;
    /*
    Ausgangsspannung:
    V=Spannungsvorgabe,
    M=aus Mittelwert der gemessenen Durchhä 
    U=aus Ungünstigstem gemes 
    B=aus Vorgabe Bogenlänge 69 *** neu ab Version 4.7.3 *** (Default ‚V‘)
    */
    char Ausgangsspannung;
    /*
    Reduzierung des Kettenausschwingwinkels nach DIN 85 (Faktor 0.8)
    ‚N‘=Keine Reduzierung des Kettenausschwingwinkels
    Sonst= Reduzierung des Kettenausschwingwinkels
    (Default:‘ ')
    */
    char Kettenausschwingwinkels;
    /*
    Höhenausgaben in Ergebnisprotokollen in 'NN' bzw. 'HN'
    'H'= Ausgabe in 'HN'
    'N'= Ausgabe in 'NHN'
    Sonst= Ausgabe in 'NN'
    (Default: ' ')
    */
    char Hoehenausgabe;
    /*
    Einschalten einer Trassierungsrichtlinie (Standard: “Seilverlegevorsc" 
    (Objektabstände: Bautoleranz berücksichtigen (siehe 'D. 
    Temperaturwert bei Zuständen wird  
    'D'= Trassierungsrichtlinie ein, Sonst= Trassierungsrichtlinie aus
    */
    char Trassierungsrichtlinie;
    /*
    Festlegung Berechnung Windgesetz
    'E' = DIN EN 50341 03.02
    'T' = TGL 200-0614/20 (Stand September 1987)
    Sonst : DIN VDE 12.85
    (Default: ' ')
    */
    char Windgesetz;
    /*
    Einstellung Berechnung Phasenabstände und Dauerzugprüfung
    'E' = DIN EN 50341 03.02
    Sonst : DIN VDE 12.85
    (Default: ' ')
    */
    char Phasenabstaende;
    /*
    Einstellung Sprache Ergebnisausgabe:
    'E' = Englisch
    Sonst: deutsch
    */
    char Sprache;

    /* *** Neu ab V4.1.9 *** */

    /*
    Einstellung Ermittlung  bei zeitabhängigem Kriechen: ‘E‘ =
    Exakte Berechnung (Ausgangszustand auf Mittelzugspannungsprüfung gesetzt),
    sonst nach ideeller Berechnung
    */
    char Mittelzugspannung;

    /*
    Einstellung *.log-Datei:
    ‚L‘ : Datei erstellen, cht 
    (Logdatei kann auch über Programmparameter ‚L‘ erzeugt werden.)
    */
    char Logdatei;
};

