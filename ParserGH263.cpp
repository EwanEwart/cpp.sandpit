#include "ParserGH263.h"
namespace cc
{
    namespace parser
    {
        std::array<DSATTR, 92> g_arr_dsks
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
            ,"SLK3",true
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
              {"INFO", false}
            , {"INFS", false}
            , {"PARS", false}
            , {"BEAR", true}
            , {"TXT1", false}
            , {"TXT2", false}
            , {"KOMM", true}
            , {"PAR1", true}
            , {"PARX", false}
            , {"DINE", false}
            , {"DBSV", false}
            , {"TRRL", false}
            , {"WIND", false}
            , {"ZSTA", false}
            , {"ZSTD", true}
            , {"ZSAN", false}
            , {"DWRE", false}
            , {"SLG1", true}
            , {"SLG2", true}
            , {"SLG3", true}
            , {"DTVG", false}
            , {"PHAS", false}
            , {"PHA2", false}
            , {"PHA4", false}
            , {"PHA5", false}
            , {"PSYS", false}
            , {"PZLF", false}
            , {"HTMP", false}
            , {"TPKT", false}
            , {"HTM2", false}
            , {"MAST", true}
            , {"TRAV", true}
            , {"KET1", true}
            , {"KET2", true}
            , {"ROLL", false}
            , {"WRR1", false}
            , {"WRR2", false}
            , {"SCSV", false}
            , {"PHAV", false}
            , {"DHGM", false}
            , {"EZLA", true}
            , {"NEIG", false}
            , {"ENEI", false}
            , {"ENET", false}
            , {"PATH", false}
            , {"SLK1", true}
            , {"SLK2", true}
            , {"SLK3", true}
            , {"EDHM", false}
            , {"ELST", false}
            , {"ESEH", false}
            , {"SPAN", false}
            , {"DBPD", false}
            , {"EPHA", false}
            , {"EGZU", false}
            , {"EKAP", false}
            , {"EPHF", false}
            , {"OBOP", false}
            , {"OBJ1", true}
            , {"OBJ2", true}
            , {"OBJ3", true}
            , {"OBJA", false}
            , {"OBA1", false}
            , {"OPKT", true}
            , {"OLIN", true}
            , {"OBFL", true}
            , {"OGEL", true}
            , {"OGE2", true}
            , {"OWEA", false}
            , {"OKRZ", false}
            , {"OKN2", false}
            , {"OKN3", false}
            , {"OKRV", false}
            , {"OKSE", false}
            , {"OKS2", false}
            , {"OERG", false}
            , {"OER2", false}
            , {"OEKB", false}
            , {"OMAB", false}
            , {"OMA2", false}
            , {"OEXP", false}
            , {"OEX2", false}
            , {"OPUO", false}
            , {"OPER", false}
            , {"OPIA", false}
            , {"OERI", false}
            , {"OKRA", false}
            , {"OKRK", false}
            , {"OKRS", false}
            , {"OALT", false}
            , {"SCSA", false}
            , {"STAT", false}
        };

        ParserGH263::ParserGH263
        (
            char const* const filePath
        )
            : filePath(filePath)
        {
            fp = std::fopen(filePath, "r");
            if (!fp)
            {
                std::fprintf(stderr, "%s : %d : File opening failed.\n", __FILE__, __LINE__);
                // todo: log error
            }

        }

        ParserGH263::~ParserGH263()
        {
            if (fp)
            {
                fclose(fp);
            }
        }

        char const* const ParserGH263::getPath()
        {
            return filePath;
        }
        FILE* ParserGH263::getFP()
        {
            return fp;
        }
        void ParserGH263::parse()
        {
            std::rewind(fp);
            for (; std::fgets(lineBuf, sizeof lineBuf, fp) != nullptr;)
            {
                char aDSK[5]{};

                int n{ sscanf(lineBuf, "%4s\n", aDSK) };

                if (std::strcmp("INFO", aDSK) == 0 && g_dictDSKs["INFO"])
                {
                    // struct INFO buf {};
                    auto buf{ std::make_shared<INFO>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("INFO", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        /*   */ lineBuf
                        /*   */, buf->fmtDS
                        /* 1 */, buf->DSK
                        /* 2 */, buf->KZProgram
                        /* 3 */, buf->LetzeAenderung
                        /* 4 */, &buf->BerechnungsModus
                    );
                    assert(n == 4);
                }
                else if (std::strcmp("BEAR", aDSK) == 0 && g_dictDSKs["BEAR"])
                {
                    // struct BEAR buf { };
                    auto buf{ std::make_shared<BEAR>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("BEAR", std::static_pointer_cast<Base>(buf)));

                    // printf("\ntype : %s\n\n", boost::core::demangle(typeid(buf).name()).c_str());

                    auto n = sscanf
                    (
                        /*    */ lineBuf
                        /*   */, buf->fmtDS
                        /* 1 */, buf->DSK
                        /* 2 */, buf->Bearbeiter
                    );
                    assert(n == 2);
                }
                else if (std::strcmp("KOMM", aDSK) == 0 && g_dictDSKs["KOMM"])
                {
                    // struct KOMM buf { };
                    auto buf{ std::make_shared<KOMM>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("KOMM", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        /*    */ lineBuf
                        /*   */, buf->fmtDS
                        /* 1 */, buf->DSK
                        /* 2 */, buf->Kommentartext
                    );
                    assert(n == 2);
                }
                else if (std::strcmp("PAR1", aDSK) == 0 && g_dictDSKs["PAR1"])
                {
                    // struct PAR1 buf { };
                    auto buf{ std::make_shared<PAR1>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("PAR1", std::static_pointer_cast<Base>(buf)));
                    auto n = sscanf
                    (
                        /*      */ lineBuf
                        /*     */, buf->fmtDS
                        /*   1 */, buf->DSK
                        /*   2 */, buf->SpezEigGewichtChar
                        /*   3 */, buf->UmrechnungsfaktorChar
                        /*   4 */, buf->ReckwertChar
                        /*   5 */, buf->BerechnungEI
                        /*   6 */, buf->Berechnungsvorschrift
                        /*   7 */, buf->BerechnungEM
                        /*   8 */, buf->Seilkriechen
                        /*   9 */, buf->Seilausschwingwinkel
                        /*  10 */, buf->Ausgangsspannung
                        /*  11 */, buf->Reduzierung
                        /*  12 */, buf->Hoehenausgaben
                        /*  13 */, buf->Trassierungsrichtlinie
                        /*  14 */, buf->Windgesetz
                        /*  15 */, buf->Phasenabstaende
                        /*  16 */, buf->Sprache
                        /*  17 */, buf->Mittelzugspannung
                        /*  18 */, buf->LogDateiYN
                    );
                    assert(n == 18);

                    n = sscanf(buf->SpezEigGewichtChar, "%f", &buf->SpezEigGewichtFloat); assert(n == 1);
                    n = sscanf(buf->UmrechnungsfaktorChar, "%f", &buf->UmrechnungsfaktorFloat); assert(n == 1);
                    n = sscanf(buf->ReckwertChar, "%f", &buf->ReckwertFloat);
                    if (n != 1)
                    {
                        buf->ReckwertFloat = 0.0f;
                    }
                }
                else if (std::strcmp("ZSTD", aDSK) == 0 && g_dictDSKs["ZSTD"])
                {
                    // struct ZSTD buf { };
                    auto buf{ std::make_shared<ZSTD>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("ZSTD", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , /*     */buf->fmtDS
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->ZustandsindexChar
                        , /*  3 */ buf->TemperaturCChar
                        , /*  4 */ buf->Konstante
                        , /*  5 */ buf->Zustandsbezeichnung
                        , /*  6 */ buf->KennungAusgangszustand
                        , /*  7 */ buf->KennungGrenzlast
                        , /*  8 */ buf->KennungUngleicheEislast
                        , /*  9 */ buf->KennungKettenausschwingwinkels
                        , /* 10 */ buf->KennungZusatzlast
                        , /* 11 */ buf->KennungEiswalze
                        , /* 12 */ buf->LastfaktorChar
                        , /* 13 */ buf->WindlastfaktorChar
                        , /* 14 */ buf->ReckwertChar
                        , /* 15 */ buf->AusnahmelastChar
                        , /* 16 */ buf->Temperaturzuschlag
                        , /* 17 */ buf->GrenzlastBerechnung
                    );
                    assert(n == 17);

                    n = sscanf(buf->ZustandsindexChar, "%d", &buf->ZustandsindexInt); assert(n == 1);
                    n = sscanf(buf->TemperaturCChar, "%d", &buf->TemperaturCInt); assert(n == 1);
                    n = sscanf(buf->LastfaktorChar, "%f", &buf->LastfaktorFloat); assert(n == 1);
                    n = sscanf(buf->WindlastfaktorChar, "%f", &buf->WindlastfaktorFloat); assert(n == 1);
                    n = sscanf(buf->ReckwertChar, "%f", &buf->ReckwertFloat); assert(n == 1);
                    n = sscanf(buf->AusnahmelastChar, "%f", &buf->AusnahmelastFloat); assert(n == 1);
                }
                else if (std::strcmp("SLG1", aDSK) == 0 && g_dictDSKs["SLG1"])
                {
                    // struct SLG1 buf { };
                    auto buf{ std::make_shared<SLG1>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLG1", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , /*     */buf->fmtDS
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->SeilindexChar
                        , /*  3 */ buf->Seilbezeichnung
                        , /*  4 */ buf->SpannungsebeneChar
                        , /*  5 */ buf->AnzahlTeilleiterChar
                        , /*  6 */ buf->Buendelanordnung
                        , /*  7 */ buf->TeilleiterabstandChar
                        , /*  8 */ buf->Seiltyp
                        , /*  9 */ buf->TemperaturdifferenzSeilkriechenChar
                        , /* 10 */ buf->KriechfaktorChar
                        , /* 11 */ buf->UeberziehfaktorChar
                        , /* 12 */ buf->KriechzeitChar
                        , /* 13 */ buf->Kennung_EN_Seil
                        , /* 14 */ buf->KennungSeilmanuellEingefuegt
                        , /* 15 */ buf->Isolationsar
                        , /* 16 */ buf->VorzeichenTemperaturdifferenz
                        , /* 17 */ buf->VorzeichenKriechfaktor
                    );
                    assert(n == 17);

                    n = sscanf(buf->SeilindexChar, "%d", &buf->SeilindexInt); assert(n == 1);
                    n = sscanf(buf->SpannungsebeneChar, "%d", &buf->SpannungsebeneInt); assert(n == 1);
                    n = sscanf(buf->AnzahlTeilleiterChar, "%d", &buf->AnzahlTeilleiterInt); assert(n == 1);
                    n = sscanf(buf->TeilleiterabstandChar, "%f", &buf->TeilleiterabstandFloat); assert(n == 1);
                    n = sscanf(buf->TemperaturdifferenzSeilkriechenChar, "%f", &buf->TemperaturdifferenzSeilkriechenFloat); assert(n == 1);
                    n = sscanf(buf->KriechfaktorChar, "%f", &buf->KriechfaktorFloat); assert(n == 1);
                    n = sscanf(buf->UeberziehfaktorChar, "%f", &buf->UeberziehfaktorFloat); assert(n == 1);
                    n = sscanf(buf->KriechzeitChar, "%f", &buf->KriechzeitFloat); assert(n == 1);
                }
                else if (std::strcmp("SLG2", aDSK) == 0 && g_dictDSKs["SLG2"])
                {
                    // struct SLG2 buf { };
                    auto buf{ std::make_shared<SLG2>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLG2", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , /*     */buf->fmtDS
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->SeilindexChar
                        , /*  3 */ buf->SeildurchmesserChar
                        , /*  4 */ buf->SeilquerschnittChar
                        , /*  5 */ buf->E_ModulChar
                        , /*  6 */ buf->AusdehnungskoeffizientChar
                        , /*  7 */ buf->SpezSeilgewichtChar
                        , /*  8 */ buf->NormaleZusatzlastChar
                        , /*  9 */ buf->AerodynamischerKraftbeiwertChar
                        , /* 10 */ buf->SeilgewichtDBChar
                        , /* 11 */ buf->FettmasseChar
                        , /* 12 */ buf->KennungQLK
                    );
                    assert(n == 12);

                    /* 2 */ n = sscanf(buf->SeilindexChar, "%d", &buf->SeilindexInt); assert(n == 1);
                    /* 3 */ n = sscanf(buf->SeildurchmesserChar, "%f", &buf->SeildurchmesserFloat); assert(n == 1);
                    /* 4 */ n = sscanf(buf->SeilquerschnittChar, "%f", &buf->SeilquerschnittFloat); assert(n == 1);
                    /* 5 */ n = sscanf(buf->E_ModulChar, "%f", &buf->E_ModulFloat); assert(n == 1);
                    /* 6 */ n = sscanf(buf->AusdehnungskoeffizientChar, "%f", &buf->AusdehnungskoeffizientFloat); assert(n == 1);
                    /* 7 */ n = sscanf(buf->SpezSeilgewichtChar, "%f", &buf->SpezSeilgewichtFloat); assert(n == 1);
                    /* 8 */ n = sscanf(buf->NormaleZusatzlastChar, "%f", &buf->NormaleZusatzlastFloat); assert(n == 1);
                    /* 9 */ n = sscanf(buf->AerodynamischerKraftbeiwertChar, "%f", &buf->AerodynamischerKraftbeiwertFloat); assert(n == 1);
                    /* 0 */ n = sscanf(buf->SeilgewichtDBChar, "%f", &buf->SeilgewichtDBFloat); assert(n == 1);
                    /* 1 */ n = sscanf(buf->FettmasseChar, "%f", &buf->FettmasseFloat); assert(n == 1);
                }
                else if (std::strcmp("SLG3", aDSK) == 0 && g_dictDSKs["SLG3"])
                {
                    // struct SLG3 buf { };
                    auto buf{ std::make_shared<SLG3>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLG3", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->SeilindexChar
                        , /*  3 */ buf->HoechstzugspannungChar
                        , /*  4 */ buf->MittelzugspannungChar
                        , /*  5 */ buf->DauerzugspannungChar
                        , /*  6 */ buf->BruchkraftChar
                        , /*  7 */ buf->StahlgewichtsanteilChar
                        , /*  8 */ buf->StahlquerschnittChar
                    );
                    assert(n == 8);

                    /* 2 */ n = sscanf(buf->SeilindexChar, "%d", &buf->SeilindexInt); assert(n == 1);
                    /* 3 */ n = sscanf(buf->HoechstzugspannungChar, "%f", &buf->HoechstzugspannungFloat); assert(n == 1);
                    /* 4 */ n = sscanf(buf->MittelzugspannungChar, "%f", &buf->MittelzugspannungFloat); assert(n == 1);
                    /* 5 */ n = sscanf(buf->DauerzugspannungChar, "%f", &buf->DauerzugspannungFloat); assert(n == 1);
                    /* 6 */ n = sscanf(buf->BruchkraftChar, "%f", &buf->BruchkraftFloat); assert(n == 1);
                    /* 7 */ n = sscanf(buf->StahlgewichtsanteilChar, "%f", &buf->StahlgewichtsanteilFloat); assert(n == 1);
                    /* 8 */ n = sscanf(buf->StahlquerschnittChar, "%f", &buf->StahlquerschnittFloat); assert(n == 1);
                }
                else if (std::strcmp("MAST", aDSK) == 0 && g_dictDSKs["MAST"])
                {
                    // struct MAST buf { };
                    auto buf{ std::make_shared<MAST>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("MAST", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->MastindexChar
                        , /*   3 */ buf->MastnummerMastname_1
                        , /*   4 */ buf->Masttyp
                        , /*   5 */ buf->Masttypenbezeichnung_1
                        , /*   6 */ buf->AusfuehrungChar
                        , /*   7 */ buf->LaengenstationMaststandortChar
                        , /*   8 */ buf->HoeheMastfusspunktChar
                        , /*   9 */ buf->LeitungswinkelChar
                        , /*  10 */ buf->StellwinkelChar
                        , /*  11 */ buf->Masttypenbezeichnung_2
                        , /*  12 */ buf->OrdinateMaststandortChar
                        , /*  13 */ buf->MastnummerMastname_2
                    );
                    assert(n == 13);

                    /*  2 */ n = sscanf(buf->MastindexChar, "%d", &buf->MastindexInt); assert(n == 1);
                    /*  6 */ n = sscanf(buf->AusfuehrungChar, "%f", &buf->AusfuehrungFloat); assert(n == 1);
                    /*  7 */ n = sscanf(buf->LaengenstationMaststandortChar, "%f", &buf->LaengenstationMaststandortFloat); assert(n == 1);
                    /*  8 */ n = sscanf(buf->HoeheMastfusspunktChar, "%f", &buf->HoeheMastfusspunktFloat); assert(n == 1);
                    /*  9 */ n = sscanf(buf->LeitungswinkelChar, "%f", &buf->LeitungswinkelFloat); assert(n == 1);
                    /* 10 */ n = sscanf(buf->StellwinkelChar, "%f", &buf->StellwinkelFloat); assert(n == 1);
                    /* 12 */ n = sscanf(buf->OrdinateMaststandortChar, "%f", &buf->OrdinateMaststandortFloat); assert(n == 1);
                }
                else if (std::strcmp("TRAV", aDSK) == 0 && g_dictDSKs["TRAV"])
                {
                    // struct TRAV buf { };
                    auto buf{ std::make_shared<TRAV>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("TRAV", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->MastindexChar
                        , /*   3 */ buf->PhasenindexChar
                        , /*   4 */ buf->TraversenhoeheChar
                        , /*   5 */ buf->AusladungChar
                        , /*   6 */ buf->StellwinkelTraverseChar
                        , /*   7 */ buf->KettenlaengeChar
                        , /*   8 */ buf->KettenindexChar
                        , /*   9 */ buf->HoehenbezugStaudruckChar
                        , /*  10 */ buf->TraversenexzentrizitaetChar
                    );
                    assert(n == 10);

                    /*  2 */ n = sscanf(buf->MastindexChar, "%d", &buf->MastindexInt); assert(n == 1);
                    /*  3 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
                    /*  4 */ n = sscanf(buf->TraversenhoeheChar, "%f", &buf->TraversenhoeheFloat); assert(n == 1);
                    /*  5 */ n = sscanf(buf->AusladungChar, "%f", &buf->AusladungFloat); assert(n == 1);
                    /*  6 */ n = sscanf(buf->StellwinkelTraverseChar, "%f", &buf->StellwinkelTraverseFloat); assert(n == 1);
                    /*  7 */ n = sscanf(buf->KettenlaengeChar, "%f", &buf->KettenlaengeFloat); assert(n == 1);
                    /*  8 */ n = sscanf(buf->KettenindexChar, "%d", &buf->KettenindexInt); assert(n == 1);
                    /*  9 */ n = sscanf(buf->HoehenbezugStaudruckChar, "%f", &buf->HoehenbezugStaudruckFloat); assert(n == 1);
                }
                else if (std::strcmp("KET1", aDSK) == 0 && g_dictDSKs["KET1"])
                {
                    // struct KET1 buf { };
                    auto buf{ std::make_shared<KET1>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("KET1", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KettenindexChar
                        , /*   3 */ buf->Kettentyp
                        , /*   4 */ buf->AnzahlKettenstraengeChar
                        , /*   5 */ buf->Kettentypbezeichnung
                        , /*   6 */ buf->KettenbezeichnungIsolator
                        , /*   7 */ buf->Schwingenbezeichnung
#ifdef FLP
                        , /*   8 */ buf->Kettennummer
#endif
                    );
#ifdef FLP
                    assert(n == 8);
#else
                    assert(n == 7);
#endif
                    /*  2 */ n = sscanf(buf->KettenindexChar, "%d", &buf->KettenindexInt); assert(n == 1);
                    /*  4 */ n = sscanf(buf->AnzahlKettenstraengeChar, "%d", &buf->AnzahlKettenstraengeInt); assert(n == 1);
                }
                else if (std::strcmp("KET2", aDSK) == 0 && g_dictDSKs["KET2"])
                {
                    // struct KET2 buf { };
                    auto buf{ std::make_shared<KET2>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("KET2", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KettenindexChar
                        , /*   3 */ buf->KettenlaengeChar
                        , /*   4 */ buf->VLaengeChar
                        , /*   5 */ buf->FesteLaengeChar
                        , /*   6 */ buf->SchwingenlaengeChar
                        , /*   7 */ buf->KettengewichtChar
                        , /*   8 */ buf->EinfachesEisgewichtKetteChar
                        , /*   9 */ buf->SchwingengewichtChar
                        , /*  10 */ buf->GrenzausschwingwinkelInnenChar
                        , /*  11 */ buf->GrenzausschwingwinkelAuszenChar
                        , /*  12 */ buf->ZusatzgewichtChar
                        , /*  13 */ buf->EinbaulaengeChar
                        , /*  14 */ buf->SchirmdurchmesserChar
                        , /*  15 */ buf->StrunkdurchmesserChar
                        , /*  16 */ buf->ProjizierteFlaecheChar
                        , /*  17 */ buf->VKetteVersatzAufhaengungMastInnenChar
                        , /*  18 */ buf->VKetteVersatzAufhaengungMastAussenChar
                    );
                    assert(n == 18);

                    /*   2 */ n = sscanf(buf->KettenindexChar, "%d", &buf->KettenindexInt); assert(n == 1);
                    /*   3 */ n = sscanf(buf->KettenlaengeChar, "%f", &buf->KettenlaengeFloat); assert(n == 1);
                    /*   4 */ n = sscanf(buf->VLaengeChar, "%f", &buf->VLaengeFloat); assert(n == 1);
                    /*   5 */ n = sscanf(buf->FesteLaengeChar, "%f", &buf->FesteLaengeFloat); assert(n == 1);
                    /*   6 */ n = sscanf(buf->SchwingenlaengeChar, "%f", &buf->SchwingenlaengeFloat); assert(n == 1);
                    /*   7 */ n = sscanf(buf->KettengewichtChar, "%f", &buf->KettengewichtFloat); assert(n == 1);
                    /*   8 */ n = sscanf(buf->EinfachesEisgewichtKetteChar, "%f", &buf->EinfachesEisgewichtKetteFloat); assert(n == 1);
                    /*   9 */ n = sscanf(buf->SchwingengewichtChar, "%f", &buf->SchwingengewichtFloat); assert(n == 1);
                    /*  10 */ n = sscanf(buf->GrenzausschwingwinkelInnenChar, "%f", &buf->GrenzausschwingwinkelInnenFloat); assert(n == 1);
                    /*  11 */ n = sscanf(buf->GrenzausschwingwinkelAuszenChar, "%f", &buf->GrenzausschwingwinkelAuszenFloat); assert(n == 1);
                    /*  12 */ n = sscanf(buf->ZusatzgewichtChar, "%f", &buf->ZusatzgewichtFloat); assert(n == 1);
                    /*  13 */ n = sscanf(buf->EinbaulaengeChar, "%f", &buf->EinbaulaengeFloat); assert(n == 1);
                    /*  14 */ n = sscanf(buf->SchirmdurchmesserChar, "%f", &buf->SchirmdurchmesserFloat); assert(n == 1);
                    /*  15 */ n = sscanf(buf->StrunkdurchmesserChar, "%f", &buf->StrunkdurchmesserFloat); assert(n == 1);
                    /*  16 */ n = sscanf(buf->ProjizierteFlaecheChar, "%f", &buf->ProjizierteFlaecheFloat); assert(n == 1);
                    /*  17 */ n = sscanf(buf->VKetteVersatzAufhaengungMastInnenChar, "%f", &buf->VKetteVersatzAufhaengungMastInnenFloat); assert(n == 1);
                    /*  18 */ n = sscanf(buf->VKetteVersatzAufhaengungMastAussenChar, "%f", &buf->VKetteVersatzAufhaengungMastAussenFloat); assert(n == 1);
                }
                else if (std::strcmp("EZLA", aDSK) == 0 && g_dictDSKs["EZLA"])
                {
                    // struct EZLA buf { };
                    auto buf{ std::make_shared<EZLA>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("EZLA", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->LastindexChar
                        , /*   3 */ buf->PhasenindexChar
                        , /*   4 */ buf->MastindexLinkerMastChar
                        , /*   5 */ buf->Lasttyp
                        , /*   6 */ buf->KennungLastEndzustand
                        , /*   7 */ buf->KennungLastMontagezustand
                        , /*   8 */ buf->KennungLastRollenzustand
                        , /*   9 */ buf->ZustandsindexChar
                        , /*  10 */ buf->AnzahlLastenInt
                        , /*  11 */ buf->StationLinkerMastChar
                        , /*  12 */ buf->AbstandLastenEndestationChar
                        , /*  13 */ buf->LastChar
                        , /*  14 */ buf->EinfacheEislastChar
                    );
                    assert(n == 14);

                    /*   2 */ n = sscanf(buf->LastindexChar, "%d", &buf->LastindexInd); assert(n == 1);
                    /*   3 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
                    /*   4 */ n = sscanf(buf->MastindexLinkerMastChar, "%d", &buf->MastindexLinkerMastInt); assert(n == 1);
                    /*   9 */ n = sscanf(buf->ZustandsindexChar, "%d", &buf->ZustandsindexInt); assert(n == 1);
                    /*  10 */ n = sscanf(buf->AnzahlLastenChar, "%d", &buf->AnzahlLastenInt); assert(n == 1);
                    /*  11 */ n = sscanf(buf->StationLinkerMastChar, "%f", &buf->StationLinkerMastFloat); assert(n == 1);
                    /*  12 */ n = sscanf(buf->AbstandLastenEndestationChar, "%f", &buf->AbstandLastenEndestationFloat); assert(n == 1);
                    /*  13 */ n = sscanf(buf->LastChar, "%f", &buf->LastFloat); assert(n == 1);
                    /*  14 */ n = sscanf(buf->EinfacheEislastChar, "%f", &buf->EinfacheEislastFloat); assert(n == 1);
                }
                else if (std::strcmp("SLK1", aDSK) == 0 && g_dictDSKs["SLK1"])
                {
                    // struct SLK1 buf { };
                    auto buf{ std::make_shared<SLK1>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLK1", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->SeilkurvenindexChar
                        , /*   3 */ buf->PhasenindexChar
                        , /*   4 */ buf->ZustandsindexChar
                        , /*   5 */ buf->MastindexLinkerMastChar
                        , /*   6 */ buf->MastindexRechterMastChar
                        , /*   7 */ buf->StationSeilaufhaengepunktLinksChar
                        , /*   8 */ buf->HoeheSeilaufhaengepunktLinksChar
                        , /*   9 */ buf->OrdinateSeilaufhaengepunktChar
                        , /*  10 */ buf->StationSeilaufhaengepunktRechtsChar
                        , /*  11 */ buf->HoeheSeilaufhaengepunktRechtsChar
                        , /*  12 */ buf->OrdinateSeilaufhaengepunktRechtsChar
                        , /*  13 */ buf->StationSeilaufhaengepunktLinksTransformChar
                        , /*  14 */ buf->OrdinateSeilaufhaengepunktLinksChar
                        , /*  15 */ buf->StationSeilaufhaengepunktRechtsTransformChar
                        , /*  16 */ buf->OrdinateSeilaufhaengepunktRechtsTransformChar
                    );
                    assert(n == 16);

                    /*   2 */ n = sscanf(buf->SeilkurvenindexChar, "%d", &buf->SeilkurvenindexInt); assert(n == 1);
                    /*   3 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
                    /*   4 */ n = sscanf(buf->ZustandsindexChar, "%d", &buf->ZustandsindexInt); assert(n == 1);
                    /*   5 */ n = sscanf(buf->MastindexLinkerMastChar, "%d", &buf->MastindexLinkerMastInt); assert(n == 1);
                    /*   6 */ n = sscanf(buf->MastindexRechterMastChar, "%d", &buf->MastindexRechterMastInt); assert(n == 1);
                    /*   7 */ n = sscanf(buf->StationSeilaufhaengepunktLinksChar, "%f", &buf->StationSeilaufhaengepunktLinksFloat); assert(n == 1);
                    /*   8 */ n = sscanf(buf->HoeheSeilaufhaengepunktLinksChar, "%f", &buf->HoeheSeilaufhaengepunktLinksFloat); assert(n == 1);
                    /*   9 */ n = sscanf(buf->OrdinateSeilaufhaengepunktChar, "%f", &buf->OrdinateSeilaufhaengepunktFloat); assert(n == 1);
                    /*  10 */ n = sscanf(buf->StationSeilaufhaengepunktRechtsChar, "%f", &buf->StationSeilaufhaengepunktRechtsFloat); assert(n == 1);
                    /*  11 */ n = sscanf(buf->HoeheSeilaufhaengepunktRechtsChar, "%f", &buf->HoeheSeilaufhaengepunktRechtsFloat); assert(n == 1);
                    /*  12 */ n = sscanf(buf->OrdinateSeilaufhaengepunktRechtsChar, "%f", &buf->OrdinateSeilaufhaengepunktRechtsFloat); assert(n == 1);
                    /*  13 */ n = sscanf(buf->StationSeilaufhaengepunktLinksTransformChar, "%f", &buf->StationSeilaufhaengepunktLinksTransformFloat); assert(n == 1);
                    /*  14 */ n = sscanf(buf->OrdinateSeilaufhaengepunktLinksChar, "%f", &buf->OrdinateSeilaufhaengepunktLinksFloat); assert(n == 1);
                    /*  15 */ n = sscanf(buf->StationSeilaufhaengepunktRechtsTransformChar, "%f", &buf->StationSeilaufhaengepunktRechtsTransformFloat); assert(n == 1);
                    /*  16 */ n = sscanf(buf->OrdinateSeilaufhaengepunktRechtsTransformChar, "%f", &buf->OrdinateSeilaufhaengepunktRechtsTransformFloat); assert(n == 1);
                }
                else if (std::strcmp("SLK2", aDSK) == 0 && g_dictDSKs["SLK2"])
                {
                    // struct SLK2 buf { };
                    auto buf{ std::make_shared<SLK2>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLK2", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->SeilkurvenindexChar
                        , /*   3 */ buf->SeilspannungEndzustandChar
                        , /*   4 */ buf->SeilgewichtEndzustandChar
                        , /*   5 */ buf->SeilausschwingwinkelChar
                        , /*   6 */ buf->DurchhangFeldmitteChar
                        , /*   7 */ buf->StationSeilpunktFeldmitteChar
                        , /*   8 */ buf->HoeheSeilpunktFeldmitteChar
                        , /*   9 */ buf->OrdinateSeilpunktFeldmitteChar
                        , /*  10 */ buf->TiefsterPunktFeldmitte
                        , /*  11 */ buf->GroeszterDurchhangFeld
                        , /*  12 */ buf->GewichtsspannweiteChar
                        , /*  13 */ buf->BogenlaengeSeilChar
                        , /*  14 */ buf->ScheitelpunktEntfernungLinkerMastChar
                        , /*  15 */ buf->ScheitelpunktSeilhoeheChar
                        , /*  16 */ buf->SeilspannungAbsolutAufhaengepunktLinksChar
                        , /*  17 */ buf->SeilspannungAbsolutAufhaengepunktRechtChar
                    );
                    assert(n == 17);

                    /*   2 */ n = sscanf(buf->SeilkurvenindexChar, "%d", &buf->SeilkurvenindexInt); assert(n == 1);
                    /*   3 */ n = sscanf(buf->SeilspannungEndzustandChar, "%f", &buf->SeilspannungEndzustandFloat); assert(n == 1);
                    /*   4 */ n = sscanf(buf->SeilgewichtEndzustandChar, "%f", &buf->SeilgewichtEndzustandFloat); assert(n == 1);
                    /*   5 */ n = sscanf(buf->SeilausschwingwinkelChar, "%f", &buf->SeilausschwingwinkelFloat); assert(n == 1);
                    /*   6 */ n = sscanf(buf->DurchhangFeldmitteChar, "%f", &buf->DurchhangFeldmitteFloat); assert(n == 1);
                    /*   7 */ n = sscanf(buf->StationSeilpunktFeldmitteChar, "%f", &buf->StationSeilpunktFeldmitteFloat); assert(n == 1);
                    /*   8 */ n = sscanf(buf->HoeheSeilpunktFeldmitteChar, "%f", &buf->HoeheSeilpunktFeldmitteFloat); assert(n == 1);
                    /*   9 */ n = sscanf(buf->OrdinateSeilpunktFeldmitteChar, "%f", &buf->OrdinateSeilpunktFeldmitteFloat); assert(n == 1);
                    /*  12 */ n = sscanf(buf->GewichtsspannweiteChar, "%f", &buf->GewichtsspannweiteFloat); assert(n == 1);
                    /*  13 */ n = sscanf(buf->BogenlaengeSeilChar, "%f", &buf->BogenlaengeSeilFloat); assert(n == 1);
                    /*  14 */ n = sscanf(buf->ScheitelpunktEntfernungLinkerMastChar, "%f", &buf->ScheitelpunktEntfernungLinkerMastFloat); assert(n == 1);
                    /*  15 */ n = sscanf(buf->ScheitelpunktSeilhoeheChar, "%f", &buf->ScheitelpunktSeilhoeheFloat); assert(n == 1);
                    /*  16 */ n = sscanf(buf->SeilspannungAbsolutAufhaengepunktLinksChar, "%f", &buf->SeilspannungAbsolutAufhaengepunktLinksFloat); assert(n == 1);
                    /*  17 */ n = sscanf(buf->SeilspannungAbsolutAufhaengepunktRechtChar, "%f", &buf->SeilspannungAbsolutAufhaengepunktRechtsFloat); assert(n == 1);
                }
                else if (std::strcmp("SLK3", aDSK) == 0 && g_dictDSKs["SLK3"])
                {
                    // struct SLK3 buf { };
                    auto buf{ std::make_shared<SLK3>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("SLK3", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->SeilkurvenindexChar
                        , /*   3 */ buf->KettenauslenkungLinkerMastInLeitungsrichtungChar
                        , /*   4 */ buf->KettenauslenkungLinkerMastQuerLeitungsrichtungChar
                        , /*   5 */ buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungChar
                        , /*   6 */ buf->KettenauslenkungRechterMastInLeitungsrichtungChar
                        , /*   7 */ buf->KettenauslenkungRechterMastQuerLeitungsrichtungChar
                        , /*   8 */ buf->KettenauslenkungRechterMastVertikalLeitungsrichtungChar
                        , /*   9 */ buf->SeilzugLinksChar
                        , /*  10 */ buf->SeilzugRechtsChar
                    );
                    assert(n == 10);

                    /*   2 */ n = sscanf(buf->SeilkurvenindexChar, "%d", &buf->SeilkurvenindexInt); assert(n == 1);
                    /*   3 */ n = sscanf(buf->KettenauslenkungLinkerMastInLeitungsrichtungChar, "%f", &buf->KettenauslenkungLinkerMastInLeitungsrichtungFloat); assert(n == 1);
                    /*   4 */ n = sscanf(buf->KettenauslenkungLinkerMastQuerLeitungsrichtungChar, "%f", &buf->KettenauslenkungLinkerMastQuerLeitungsrichtungFloat); assert(n == 1);
                    /*   5 */ n = sscanf(buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungChar, "%f", &buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungFloat); assert(n == 1);
                    /*   6 */ n = sscanf(buf->KettenauslenkungRechterMastInLeitungsrichtungChar, "%f", &buf->KettenauslenkungRechterMastInLeitungsrichtungFloat); assert(n == 1);
                    /*   7 */ n = sscanf(buf->KettenauslenkungRechterMastQuerLeitungsrichtungChar, "%f", &buf->KettenauslenkungRechterMastQuerLeitungsrichtungFloat); assert(n == 1);
                    /*   8 */ n = sscanf(buf->KettenauslenkungRechterMastVertikalLeitungsrichtungChar, "%f", &buf->KettenauslenkungRechterMastVertikalLeitungsrichtungFloat); assert(n == 1);
                    /*   9 */ n = sscanf(buf->SeilzugLinksChar, "%f", &buf->SeilzugLinksFloat); assert(n == 1);
                    /*  10 */ n = sscanf(buf->SeilzugRechtsChar, "%f", &buf->SeilzugRechtsFloat); assert(n == 1);
                }
                else if (std::strcmp("OBJ1", aDSK) == 0 && g_dictDSKs["OBJ1"])
                {
                    // struct OBJ1 buf { };
                    auto buf{ std::make_shared<OBJ1>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBJ1", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KreuzungsobjektindexTeil_1_Char
                        , /*   3 */ buf->Objektnummer
                        , /*   4 */ buf->MindestabstandChar
                        , /*   5 */ buf->NachweiscodeChar
                        , /*   6 */ buf->Abstandstyp
                        , /*   7 */ buf->Nachweiszustaende
                        , /*   8 */ buf->MastindexChar
                        , /*   9 */ buf->PhasenindexChar
                        , /*  10 */ buf->Objekttyp
                        , /*  11 */ buf->SteuerungsparameterDruckausgabe
                        , /*  12 */ buf->ParameterLeitungskreuzungen
                        , /*  13 */ buf->NeuerObjekttyp
                        , /*  14 */ buf->Objektabstand
                        , /*  15 */ buf->ObjektRechnen
                        , /*  16 */ buf->KreuzungsobjektindexTeil_2_Char
                        , /*  17 */ buf->Mindestabstand110kVChar
                    );
                    assert(n == 17);

                    /*   2 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
                    /*   4 */ n = sscanf(buf->MindestabstandChar, "%f", &buf->MindestabstandFloat); assert(n == 1);
                    /*   5 */ n = sscanf(buf->NachweiscodeChar, "%d", &buf->NachweiscodeInt); assert(n == 1);
                    /*   8 */ n = sscanf(buf->MastindexChar, "%d", &buf->MastindexInt); assert(n == 1);
                    /*   9 */ n = sscanf(buf->PhasenindexChar, "%d", &buf->PhasenindexInt); assert(n == 1);
                    /*  16 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
                    /*  17 */ n = sscanf(buf->Mindestabstand110kVChar, "%f", &buf->Mindestabstand110kVFloat); assert(n == 1);
                }
                else if (std::strcmp("OBJ2", aDSK) == 0 && g_dictDSKs["OBJ2"])
                {
                    // struct OBJ2 buf { };
                    auto buf{ std::make_shared<OBJ2>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBJ2", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KreuzungsobjektindexTeil_1_Char
                        , /*   3 */ buf->ObjektbezeichnungZeile_1
                        , /*   4 */ buf->ObjektbezeichnungZeile_2
                        , /*   5 */ buf->KreuzungsobjektindexTeil_2_Char
                    );
                    assert(n == 5);

                    /*   2 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
                    /*   5 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
                }
                else if (std::strcmp("OBJ3", aDSK) == 0 && g_dictDSKs["OBJ3"])
                {
                    // struct OBJ3 buf { };
                    auto buf{ std::make_shared<OBJ3>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBJ3", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KreuzungsobjektindexTeil_1_Char
                        , /*   3 */ buf->EigentümerZeile_1
                        , /*   4 */ buf->EigentümerZeile_2
                        , /*   5 */ buf->KreuzungsobjektindexTeil_2_Char
                    );
                    assert(n == 5);

                    /*   2 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
                    /*   5 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
                }
                else if (std::strcmp("OPKT", aDSK) == 0 && g_dictDSKs["OPKT"])
                {
                    // struct OPKT buf { };
                    auto buf{ std::make_shared<OPKT>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OPKT", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->PunktindexTeil_1_Char
                        , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Char
                        , /*    4 */ buf->StationChar
                        , /*    5 */ buf->OrdinateChar
                        , /*    6 */ buf->FuszhoeheChar
                        , /*    7 */ buf->ObjekthoeheChar
                        , /*    8 */ buf->PunktnummerVermessung
                        , /*    9 */ buf->Punktindex_Teil_2_Char
#ifdef FLP
                        , /*   10 */ buf->MS_LinkChar
#endif
                        , /*   11 */ buf->KreuzungsobjektindexTeil_2_Char);
#ifdef FLP
                    assert(n == 11);
#else
                    assert(n == 10);
#endif
                    /*   2 */ n = sscanf(buf->PunktindexTeil_1_Char, "%d", &buf->PunktindexTeil_1_Int); assert(n == 1);
                    /*   3 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_1_Char, "%d", &buf->Kreuzungsobjektindex_Teil_1_Int); assert(n == 1);
                    /*   4 */ n = sscanf(buf->StationChar, "%f", &buf->StationFloat); assert(n == 1);
                    /*   5 */ n = sscanf(buf->OrdinateChar, "%f", &buf->OrdinateFloat); assert(n == 1);
                    /*   6 */ n = sscanf(buf->FuszhoeheChar, "%f", &buf->FuszhoeheFloat); assert(n == 1);
                    /*   7 */ n = sscanf(buf->ObjekthoeheChar, "%f", &buf->ObjekthoeheFloat); assert(n == 1);
                    /*   9 */ n = sscanf(buf->Punktindex_Teil_2_Char, "%d", &buf->Punktindex_Teil_2_Int); assert(n == 1);
#ifdef FLP
                    /*  10 */ n = sscanf(buf->MS_LinkChar, "%d", &buf->MS_LinkInt); assert(n == 1);
#endif
                    /*  11 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
                }
                else if (std::strcmp("OLIN", aDSK) == 0 && g_dictDSKs["OLIN"])
                {
                    // struct OLIN buf { };
                    auto buf{ std::make_shared<OLIN>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OLIN", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->LinienindexTeil_1_Char
                        , /*    3 */ buf->KreuzungsobjektindexTeil_1_Char
                        , /*    4 */ buf->IndexAnfangspunkt_1_Teil_1_Char
                        , /*    5 */ buf->Index_Endpunkt_1_Teil_1_Char
                        , /*    6 */ buf->Index_Anfangspunkt_2_Teil_2_Char
                        , /*    7 */ buf->IndexEndpunkt_2_Teil_2_Char
#ifdef FLP
                        , /*    8 */ buf->MS_LinkChar
#endif
                        , /*    9 */ buf->Linienindex_Teil_2_Char
                        , /*   10 */ buf->Kreuzungsobjektindex_Teil_2_Char
                    );
#ifdef FLP
                    assert(n == 10);
#else
                    assert(n == 9);
#endif
                    /*   2 */ n = sscanf(buf->LinienindexTeil_1_Char, "%d", &buf->LinienindexTeil_1_Int); assert(n == 1);
                    /*   3 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
                    /*   4 */ n = sscanf(buf->IndexAnfangspunkt_1_Teil_1_Char, "%d", &buf->IndexAnfangspunkt_1_Teil_1_Int); assert(n == 1);
                    /*   5 */ n = sscanf(buf->Index_Endpunkt_1_Teil_1_Char, "%d", &buf->Index_Endpunkt_1_Teil_1_Int); assert(n == 1);
                    /*   6 */ n = sscanf(buf->Index_Anfangspunkt_2_Teil_2_Char, "%d", &buf->Index_Anfangspunkt_2_Teil_2_Int); assert(n == 1);
                    /*   7 */ n = sscanf(buf->IndexEndpunkt_2_Teil_2_Char, "%d", &buf->IndexEndpunkt_2_Teil_2_Int); assert(n == 1);
#ifdef FLP
                    /*   8 */ n = sscanf(buf->MS_LinkChar, "%d", &buf->MS_LinkInt); assert(n == 1);
#endif
                    /*   9 */ n = sscanf(buf->Linienindex_Teil_2_Char, "%d", &buf->Linienindex_Teil_2_Int); assert(n == 1);
                    /*  10 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_2_Char, "%d", &buf->Kreuzungsobjektindex_Teil_2_Int); assert(n == 1);
                }
                else if (std::strcmp("OBFL", aDSK) == 0 && g_dictDSKs["OBFL"])
                {
                    // struct OBFL buf { };
                    auto buf{ std::make_shared<OBFL>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OBFL", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->Flaechenindex_Teil_1_Char
                        , /*    3 */ buf->KreuzungsobjektindexTeil_1_Char
                        , /*    4 */ buf->Punktindex_1_Teil_1_Char
                        , /*    5 */ buf->Punktindex_2_Teil_1_Char
                        , /*    6 */ buf->Punktindex_3_Teil_1_Char
                        , /*    7 */ buf->Punktindex_4_Teil_1_Char
                        , /*    8 */ buf->Punktindex_1_Teil_2_Char
                        , /*    9 */ buf->Punktindex_2_Teil_2_Char
                        , /*   10 */ buf->Punktindex_3_Teil_2_Char
                        , /*   11 */ buf->Punktindex_4_Teil_2_Char
#ifdef FLP
                        , /*   12 */ buf->MS_Link_Char
#endif
                        , /*   13 */ buf->Flaechenindex_Teil_2_Char, /*   14 */ buf->Kreuzungsobjektindex_Teil_2_Char);
#ifdef FLP
                    assert(n == 14);
#else
                    assert(n == 13);
#endif
                    /*   2 */ n = sscanf(buf->Flaechenindex_Teil_1_Char, "%d", &buf->Flaechenindex_Teil_1_Int); assert(n == 1);
                    /*   3 */ n = sscanf(buf->KreuzungsobjektindexTeil_1_Char, "%d", &buf->KreuzungsobjektindexTeil_1_Int); assert(n == 1);
                    /*   4 */ n = sscanf(buf->Punktindex_1_Teil_1_Char, "%d", &buf->Punktindex_1_Teil_1_Int); assert(n == 1);
                    /*   5 */ n = sscanf(buf->Punktindex_2_Teil_1_Char, "%d", &buf->Punktindex_2_Teil_1_Int); assert(n == 1);
                    /*   6 */ n = sscanf(buf->Punktindex_3_Teil_1_Char, "%d", &buf->Punktindex_3_Teil_1_Int); assert(n == 1);
                    /*   7 */ n = sscanf(buf->Punktindex_4_Teil_1_Char, "%d", &buf->Punktindex_4_Teil_1_Int); assert(n == 1);
                    /*   8 */ n = sscanf(buf->Punktindex_1_Teil_2_Char, "%d", &buf->Punktindex_1_Teil_2_Int); assert(n == 1);
                    /*   9 */ n = sscanf(buf->Punktindex_2_Teil_2_Char, "%d", &buf->Punktindex_2_Teil_2_Int); assert(n == 1);
                    /*  10 */ n = sscanf(buf->Punktindex_3_Teil_2_Char, "%d", &buf->Punktindex_3_Teil_2_Int); assert(n == 1);
                    /*  11 */ n = sscanf(buf->Punktindex_4_Teil_2_Char, "%d", &buf->Punktindex_4_Teil_2_Int); assert(n == 1);
#ifdef FLP
                    /*  12 */ n = sscanf(buf->MS_Link_Char, "%d", &buf->MS_Link_Int); assert(n == 1);
#endif
                    /*  13 */ n = sscanf(buf->Flaechenindex_Teil_2_Char, "%d", &buf->Flaechenindex_Teil_2_Int); assert(n == 1);
                    /*  14 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_2_Char, "%d", &buf->Kreuzungsobjektindex_Teil_2_Int); assert(n == 1);
                }
                else if (std::strcmp("OGEL", aDSK) == 0 && g_dictDSKs["OGEL"])
                {
                    // struct OGEL buf { };
                    auto buf{ std::make_shared<OGEL>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OGEL", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->Gelaendepunktindex_Teil_1_Char
                        , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Char
                        , /*    4 */ buf->StationChar
                        , /*    5 */ buf->GelaendehoeheTrassenmitte_Char
                        , /*    6 */ buf->OrdinateSeitlichUeberhoehung_1_Char
                        , /*    7 */ buf->SeitlicheUeberhoehung_1_Char
                        , /*    8 */ buf->OrdinateSeitlicheUeberhoehung_2_Char
                        , /*    9 */ buf->SeitlicheUeberhoehung_2_Char
                        , /*   10 */ buf->Gelaendepunktindex_Teil_2_Char
                        , /*   11 */ buf->KulturartCode
                        , /*   12 */ buf->KreuzungsobjektindexTeil_2_Char
                    );
                    assert(n == 12);

                    /*   2 */ n = sscanf(buf->Gelaendepunktindex_Teil_1_Char, "%d", &buf->Gelaendepunktindex_Teil_1_Int); assert(n == 1);
                    /*   3 */ n = sscanf(buf->Kreuzungsobjektindex_Teil_1_Char, "%d", &buf->Kreuzungsobjektindex_Teil_1_Int); assert(n == 1);
                    /*   4 */ n = sscanf(buf->StationChar, "%f", &buf->StationFloat); assert(n == 1);
                    /*   5 */ n = sscanf(buf->GelaendehoeheTrassenmitte_Char, "%f", &buf->GelaendehoeheTrassenmitteFloat); assert(n == 1);
                    /*   6 */ n = sscanf(buf->OrdinateSeitlichUeberhoehung_1_Char, "%f", &buf->OrdinateSeitlichUeberhoehung_1_Float); assert(n == 1);
                    /*   7 */ n = sscanf(buf->SeitlicheUeberhoehung_1_Char, "%f", &buf->SeitlicheUeberhoehung_1_Float); assert(n == 1);
                    /*   8 */ n = sscanf(buf->OrdinateSeitlicheUeberhoehung_2_Char, "%f", &buf->OrdinateSeitlicheUeberhoehung_2_Float); assert(n == 1);
                    /*   9 */ n = sscanf(buf->SeitlicheUeberhoehung_2_Char, "%f", &buf->SeitlicheUeberhoehung_2_Float); assert(n == 1);
                    /*  10 */ n = sscanf(buf->Gelaendepunktindex_Teil_2_Char, "%d", &buf->Gelaendepunktindex_Teil_2_Int); assert(n == 1);
                    /*  12 */ n = sscanf(buf->KreuzungsobjektindexTeil_2_Char, "%d", &buf->KreuzungsobjektindexTeil_2_Int); assert(n == 1);
                }
                else if (std::strcmp("OGE2", aDSK) == 0 && g_dictDSKs["OGE2"])
                {
                    // struct OGE2 buf { };
                    auto buf{ std::make_shared<OGE2>() };
                    queueDSKs.push(std::pair<std::string, std::shared_ptr<Base>>("OGE2", std::static_pointer_cast<Base>(buf)));

                    auto n = sscanf
                    (
                        lineBuf
                        , buf->fmtDS
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->GelaendepunktindexChar
                        , /*    3 */ buf->KulturartReintext
                    );
                    assert(n == 12);

                    /*   2 */ n = sscanf(buf->GelaendepunktindexChar, "%d", &buf->GelaendepunktindexInt); assert(n == 1);
                }

            } // for scan SLC file line by line

        }
        void ParserGH263::statistics()
        {
            std::rewind(fp);
            size_t noOfLines{};
            std::map<std::string, unsigned int> occurrencesDSK{};
            for (; std::fgets(lineBuf, sizeof lineBuf, fp) != nullptr;)
            {
                char aDSK[4 + 1]{};
                // (void)printf("%s", lineBuf);
                int n{ sscanf(lineBuf, "%4s\n", aDSK) };
                // (void)printf("%s\n", aDSK);

                occurrencesDSK[aDSK]++;

                noOfLines++;
            }

            for (auto const& item : occurrencesDSK)
            {
                (void)printf
                (
                    "%s : %4u\n"
                    , item.first.c_str()
                    , item.second
                );
            }
            size_t greens{};
            for (auto const& item : g_arr_dsks)
            {
                if (item.req)
                {
                    greens++;
                }
            }
            (void)printf("\nCount documented DSKs == %zd\n", g_arr_dsks.size());
            (void)printf("\nCount green DSKs == %zd\n", greens);
            (void)printf("\nCount different DSKs  == %zd\n", occurrencesDSK.size());
            (void)printf("\nNo of lines .SLC      == %zd\n", noOfLines);

            (void)printf("\n");
        }
        void ParserGH263::printRecordsOnConsole()
        {
            for (;!queueDSKs.empty();)
            {
                auto ds{ queueDSKs.front() };
                auto aDSK{ ds.first.c_str() };
                printf("==> %s\n", aDSK);
                auto buf = std::static_pointer_cast<INFO>(ds.second);

                if (std::strcmp("INFO", aDSK) == 0 && g_dictDSKs["INFO"])
                {
                    auto buf = std::static_pointer_cast<INFO>(ds.second);

                    (void)printf
                    (
                        /*    */ buf->fmtPrintf
                        /* 1 */, buf->DSK
                        /* 2 */, buf->KZProgram
                        /* 3 */, buf->LetzeAenderung
                        /* 4 */, buf->BerechnungsModus
                    );
                }
                else if (std::strcmp("BEAR", aDSK) == 0 && g_dictDSKs["BEAR"])
                {
                    auto buf = std::static_pointer_cast<BEAR>(ds.second);

                    // printf("\ntype : %s\n\n", boost::core::demangle(typeid(buf).name()).c_str());

                    (void)printf
                    (
                        /*    */ buf->fmtPrintf
                        /* 1 */, buf->DSK
                        /* 2 */, buf->Bearbeiter
                    );
                }
                else if (std::strcmp("KOMM", aDSK) == 0 && g_dictDSKs["KOMM"])
                {
                    auto buf = std::static_pointer_cast<KOMM>(ds.second);

                    (void)printf
                    (
                        /*    */ buf->fmtPrintf
                        /* 1 */, buf->DSK
                        /* 2 */, buf->Kommentartext
                    );
                }
                else if (std::strcmp("PAR1", aDSK) == 0 && g_dictDSKs["PAR1"])
                {
                    auto buf = std::static_pointer_cast<PAR1>(ds.second);

                    (void)printf
                    (
                        /*      */ buf->fmtPrintf
                        /*   1 */, buf->DSK
                        /*   2 */, buf->SpezEigGewichtFloat
                        /*   3 */, buf->UmrechnungsfaktorFloat
                        /*   4 */, buf->ReckwertFloat
                        /*   5 */, buf->BerechnungEI
                        /*   6 */, buf->Berechnungsvorschrift
                        /*   7 */, buf->BerechnungEM
                        /*   8 */, buf->Seilkriechen
                        /*   9 */, buf->Seilausschwingwinkel
                        /*  10 */, buf->Ausgangsspannung
                        /*  11 */, buf->Reduzierung
                        /*  12 */, buf->Hoehenausgaben
                        /*  13 */, buf->Trassierungsrichtlinie
                        /*  14 */, buf->Windgesetz
                        /*  15 */, buf->Phasenabstaende
                        /*  16 */, buf->Sprache
                        /*  17 */, buf->Mittelzugspannung
                        /*  18 */, buf->LogDateiYN

                    );
                }
                else if (std::strcmp("ZSTD", aDSK) == 0 && g_dictDSKs["ZSTD"])
                {
                    auto buf = std::static_pointer_cast<ZSTD>(ds.second);

                    (void)printf
                    (
                        /*       */buf->fmtPrintf
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->ZustandsindexInt
                        , /*  3 */ buf->TemperaturCInt
                        , /*  4 */ buf->Konstante
                        , /*  5 */ buf->Zustandsbezeichnung
                        , /*  6 */ buf->KennungAusgangszustand
                        , /*  7 */ buf->KennungGrenzlast
                        , /*  8 */ buf->KennungUngleicheEislast
                        , /*  9 */ buf->KennungKettenausschwingwinkels
                        , /* 10 */ buf->KennungZusatzlast
                        , /* 11 */ buf->KennungEiswalze
                        , /* 12 */ buf->LastfaktorFloat
                        , /* 13 */ buf->WindlastfaktorFloat
                        , /* 14 */ buf->ReckwertFloat
                        , /* 15 */ buf->AusnahmelastFloat
                        , /* 16 */ buf->Temperaturzuschlag
                        , /* 17 */ buf->GrenzlastBerechnung

                    );
                }
                else if (std::strcmp("SLG1", aDSK) == 0 && g_dictDSKs["SLG1"])
                {
                    auto buf = std::static_pointer_cast<SLG1>(ds.second);
                    (void)printf
                    (
                        /*       */buf->fmtPrintf
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->SeilindexInt
                        , /*  3 */ buf->Seilbezeichnung
                        , /*  4 */ buf->SpannungsebeneInt
                        , /*  5 */ buf->AnzahlTeilleiterInt
                        , /*  6 */ buf->Buendelanordnung
                        , /*  7 */ buf->TeilleiterabstandFloat
                        , /*  8 */ buf->Seiltyp
                        , /*  9 */ buf->TemperaturdifferenzSeilkriechenFloat
                        , /* 10 */ buf->KriechfaktorFloat
                        , /* 11 */ buf->UeberziehfaktorFloat
                        , /* 12 */ buf->KriechzeitFloat
                        , /* 13 */ buf->Kennung_EN_Seil
                        , /* 14 */ buf->KennungSeilmanuellEingefuegt
                        , /* 15 */ buf->Isolationsar
                        , /* 16 */ buf->VorzeichenTemperaturdifferenz
                        , /* 17 */ buf->VorzeichenKriechfaktor
                    );
                }
                else if (std::strcmp("SLG2", aDSK) == 0 && g_dictDSKs["SLG2"])
                {
                    auto buf = std::static_pointer_cast<SLG2>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->SeilindexInt
                        , /*  3 */ buf->SeildurchmesserFloat
                        , /*  4 */ buf->SeilquerschnittFloat
                        , /*  5 */ buf->E_ModulFloat
                        , /*  6 */ buf->AusdehnungskoeffizientFloat
                        , /*  7 */ buf->SpezSeilgewichtFloat
                        , /*  8 */ buf->NormaleZusatzlastFloat
                        , /*  9 */ buf->AerodynamischerKraftbeiwertFloat
                        , /* 10 */ buf->SeilgewichtDBFloat
                        , /* 11 */ buf->FettmasseFloat
                        , /* 12 */ buf->KennungQLK

                    );
                }
                else if (std::strcmp("SLG3", aDSK) == 0 && g_dictDSKs["SLG3"])
                {
                    auto buf = std::static_pointer_cast<SLG3>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*  1 */ buf->DSK
                        , /*  2 */ buf->SeilindexInt
                        , /*  3 */ buf->HoechstzugspannungFloat
                        , /*  4 */ buf->MittelzugspannungFloat
                        , /*  5 */ buf->DauerzugspannungFloat
                        , /*  6 */ buf->BruchkraftFloat
                        , /*  7 */ buf->StahlgewichtsanteilFloat
                        , /*  8 */ buf->StahlquerschnittFloat
                    );
                }
                else if (std::strcmp("MAST", aDSK) == 0 && g_dictDSKs["MAST"])
                {
                    auto buf = std::static_pointer_cast<MAST>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->MastindexInt
                        , /*   3 */ buf->MastnummerMastname_1
                        , /*   4 */ buf->Masttyp
                        , /*   5 */ buf->Masttypenbezeichnung_1
                        , /*   6 */ buf->AusfuehrungFloat
                        , /*   7 */ buf->LaengenstationMaststandortFloat
                        , /*   8 */ buf->HoeheMastfusspunktFloat
                        , /*   9 */ buf->LeitungswinkelFloat
                        , /*  10 */ buf->StellwinkelFloat
                        , /*  11 */ buf->Masttypenbezeichnung_2
                        , /*  12 */ buf->OrdinateMaststandortFloat
                        , /*  13 */ buf->MastnummerMastname_2
                    );
                }
                else if (std::strcmp("TRAV", aDSK) == 0 && g_dictDSKs["TRAV"])
                {
                    auto buf = std::static_pointer_cast<TRAV>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->MastindexInt
                        , /*   3 */ buf->PhasenindexInt
                        , /*   4 */ buf->TraversenhoeheFloat
                        , /*   5 */ buf->AusladungFloat
                        , /*   6 */ buf->StellwinkelTraverseFloat
                        , /*   7 */ buf->KettenlaengeFloat
                        , /*   8 */ buf->KettenindexInt
                        , /*   9 */ buf->HoehenbezugStaudruckFloat
                        , /*  10 */ buf->TraversenexzentrizitaetFloat
                    );
                }
                else if (std::strcmp("KET1", aDSK) == 0 && g_dictDSKs["KET1"])
                {
                    auto buf = std::static_pointer_cast<KET1>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KettenindexInt
                        , /*   3 */ buf->Kettentyp
                        , /*   4 */ buf->AnzahlKettenstraengeInt
                        , /*   5 */ buf->Kettentypbezeichnung
                        , /*   6 */ buf->KettenbezeichnungIsolator
                        , /*   7 */ buf->Schwingenbezeichnung
#ifdef FIRM_FLP
                        , /*   8 */ buf->Kettennummer
#endif
                    );
                }
                else if (std::strcmp("KET2", aDSK) == 0 && g_dictDSKs["KET2"])
                {
                    auto buf = std::static_pointer_cast<KET2>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KettenindexInt
                        , /*   3 */ buf->KettenlaengeFloat
                        , /*   4 */ buf->VLaengeFloat
                        , /*   5 */ buf->FesteLaengeFloat
                        , /*   6 */ buf->SchwingenlaengeFloat
                        , /*   7 */ buf->KettengewichtFloat
                        , /*   8 */ buf->EinfachesEisgewichtKetteFloat
                        , /*   9 */ buf->SchwingengewichtFloat
                        , /*  10 */ buf->GrenzausschwingwinkelInnenFloat
                        , /*  11 */ buf->GrenzausschwingwinkelAuszenFloat
                        , /*  12 */ buf->ZusatzgewichtFloat
                        , /*  13 */ buf->EinbaulaengeFloat
                        , /*  14 */ buf->SchirmdurchmesserFloat
                        , /*  15 */ buf->StrunkdurchmesserFloat
                        , /*  16 */ buf->ProjizierteFlaecheFloat
                        , /*  17 */ buf->VKetteVersatzAufhaengungMastInnenFloat
                        , /*  18 */ buf->VKetteVersatzAufhaengungMastAussenFloat
                    );
                }
                else if (std::strcmp("EZLA", aDSK) == 0 && g_dictDSKs["EZLA"])
                {
                    auto buf = std::static_pointer_cast<EZLA>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->LastindexInd
                        , /*   3 */ buf->PhasenindexInt
                        , /*   4 */ buf->MastindexLinkerMastInt
                        , /*   5 */ buf->Lasttyp
                        , /*   6 */ buf->KennungLastEndzustand
                        , /*   7 */ buf->KennungLastMontagezustand
                        , /*   8 */ buf->KennungLastRollenzustand
                        , /*   9 */ buf->ZustandsindexInt
                        , /*  10 */ buf->AnzahlLastenInt
                        , /*  11 */ buf->StationLinkerMastFloat
                        , /*  12 */ buf->AbstandLastenEndestationFloat
                        , /*  13 */ buf->LastFloat
                        , /*  14 */ buf->EinfacheEislastFloat
                    );
                }
                else if (std::strcmp("SLK1", aDSK) == 0 && g_dictDSKs["SLK1"])
                {
                    auto buf = std::static_pointer_cast<SLK1>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->SeilkurvenindexInt
                        , /*   3 */ buf->PhasenindexInt
                        , /*   4 */ buf->ZustandsindexInt
                        , /*   5 */ buf->MastindexLinkerMastInt
                        , /*   6 */ buf->MastindexRechterMastInt
                        , /*   7 */ buf->StationSeilaufhaengepunktLinksFloat
                        , /*   8 */ buf->HoeheSeilaufhaengepunktLinksFloat
                        , /*   9 */ buf->OrdinateSeilaufhaengepunktFloat
                        , /*  10 */ buf->StationSeilaufhaengepunktRechtsFloat
                        , /*  11 */ buf->HoeheSeilaufhaengepunktRechtsFloat
                        , /*  12 */ buf->OrdinateSeilaufhaengepunktRechtsFloat
                        , /*  13 */ buf->StationSeilaufhaengepunktLinksTransformFloat
                        , /*  14 */ buf->OrdinateSeilaufhaengepunktLinksFloat
                        , /*  15 */ buf->StationSeilaufhaengepunktRechtsTransformFloat
                        , /*  16 */ buf->OrdinateSeilaufhaengepunktRechtsTransformFloat
                    );
                }
                else if (std::strcmp("SLK2", aDSK) == 0 && g_dictDSKs["SLK2"])
                {
                    auto buf = std::static_pointer_cast<SLK2>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->SeilkurvenindexInt
                        , /*   3 */ buf->SeilspannungEndzustandFloat
                        , /*   4 */ buf->SeilgewichtEndzustandFloat
                        , /*   5 */ buf->SeilausschwingwinkelFloat
                        , /*   6 */ buf->DurchhangFeldmitteFloat
                        , /*   7 */ buf->StationSeilpunktFeldmitteFloat
                        , /*   8 */ buf->HoeheSeilpunktFeldmitteFloat
                        , /*   9 */ buf->OrdinateSeilpunktFeldmitteFloat
                        , /*  10 */ buf->TiefsterPunktFeldmitte
                        , /*  11 */ buf->GroeszterDurchhangFeld
                        , /*  12 */ buf->GewichtsspannweiteFloat
                        , /*  13 */ buf->BogenlaengeSeilFloat
                        , /*  14 */ buf->ScheitelpunktEntfernungLinkerMastFloat
                        , /*  15 */ buf->ScheitelpunktSeilhoeheFloat
                        , /*  16 */ buf->SeilspannungAbsolutAufhaengepunktLinksFloat
                        , /*  17 */ buf->SeilspannungAbsolutAufhaengepunktRechtsFloat
                    );
                }
                else if (std::strcmp("SLK3", aDSK) == 0 && g_dictDSKs["SLK3"])
                {
                    auto buf = std::static_pointer_cast<SLK3>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->SeilkurvenindexInt
                        , /*   3 */ buf->KettenauslenkungLinkerMastInLeitungsrichtungFloat
                        , /*   4 */ buf->KettenauslenkungLinkerMastQuerLeitungsrichtungFloat
                        , /*   5 */ buf->KettenauslenkungLinkerMastVertikalLeitungsrichtungFloat
                        , /*   6 */ buf->KettenauslenkungRechterMastInLeitungsrichtungFloat
                        , /*   7 */ buf->KettenauslenkungRechterMastQuerLeitungsrichtungFloat
                        , /*   8 */ buf->KettenauslenkungRechterMastVertikalLeitungsrichtungFloat
                        , /*   9 */ buf->SeilzugLinksFloat
                        , /*  10 */ buf->SeilzugRechtsFloat
                    );
                }
                else if (std::strcmp("OBJ1", aDSK) == 0 && g_dictDSKs["OBJ1"])
                {
                    auto buf = std::static_pointer_cast<OBJ1>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KreuzungsobjektindexTeil_1_Int
                        , /*   3 */ buf->Objektnummer
                        , /*   4 */ buf->MindestabstandFloat
                        , /*   5 */ buf->NachweiscodeInt
                        , /*   6 */ buf->Abstandstyp
                        , /*   7 */ buf->Nachweiszustaende
                        , /*   8 */ buf->MastindexInt
                        , /*   9 */ buf->PhasenindexInt
                        , /*  10 */ buf->Objekttyp
                        , /*  11 */ buf->SteuerungsparameterDruckausgabe
                        , /*  12 */ buf->ParameterLeitungskreuzungen
                        , /*  13 */ buf->NeuerObjekttyp
                        , /*  14 */ buf->Objektabstand
                        , /*  15 */ buf->ObjektRechnen
                        , /*  16 */ buf->KreuzungsobjektindexTeil_2_Int
                        , /*  17 */ buf->Mindestabstand110kVFloat
                    );
                }
                else if (std::strcmp("OBJ2", aDSK) == 0 && g_dictDSKs["OBJ2"])
                {
                    auto buf = std::static_pointer_cast<OBJ2>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KreuzungsobjektindexTeil_1_Int
                        , /*   3 */ buf->ObjektbezeichnungZeile_1
                        , /*   4 */ buf->ObjektbezeichnungZeile_2
                        , /*   5 */ buf->KreuzungsobjektindexTeil_2_Int
                    );
                }
                else if (std::strcmp("OBJ3", aDSK) == 0 && g_dictDSKs["OBJ3"])
                {
                    auto buf = std::static_pointer_cast<OBJ3>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*   1 */ buf->DSK
                        , /*   2 */ buf->KreuzungsobjektindexTeil_1_Int
                        , /*   3 */ buf->EigentümerZeile_1
                        , /*   4 */ buf->EigentümerZeile_2
                        , /*   5 */ buf->KreuzungsobjektindexTeil_2_Int
                    );
                }
                else if (std::strcmp("OPKT", aDSK) == 0 && g_dictDSKs["OPKT"])
                {
                    auto buf = std::static_pointer_cast<OPKT>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->PunktindexTeil_1_Int
                        , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Int
                        , /*    4 */ buf->StationFloat
                        , /*    5 */ buf->OrdinateFloat
                        , /*    6 */ buf->FuszhoeheFloat
                        , /*    7 */ buf->ObjekthoeheFloat
                        , /*    8 */ buf->PunktnummerVermessung
                        , /*    9 */ buf->Punktindex_Teil_2_Int
#ifdef FLP
                        , /*   10 */ buf->MS_LinkInt
#endif
                        , /*   11 */ buf->KreuzungsobjektindexTeil_2_Int);
                }
                else if (std::strcmp("OLIN", aDSK) == 0 && g_dictDSKs["OLIN"])
                {
                    auto buf = std::static_pointer_cast<OLIN>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->LinienindexTeil_1_Int
                        , /*    3 */ buf->KreuzungsobjektindexTeil_1_Int
                        , /*    4 */ buf->IndexAnfangspunkt_1_Teil_1_Int
                        , /*    5 */ buf->Index_Endpunkt_1_Teil_1_Int
                        , /*    6 */ buf->Index_Anfangspunkt_2_Teil_2_Int
                        , /*    7 */ buf->IndexEndpunkt_2_Teil_2_Int
#ifdef FLP
                        , /*    8 */ buf->MS_LinkInt
#endif
                        , /*    9 */ buf->Linienindex_Teil_2_Int
                        , /*   10 */ buf->Kreuzungsobjektindex_Teil_2_Char
                    );
                }
                else if (std::strcmp("OBFL", aDSK) == 0 && g_dictDSKs["OBFL"])
                {
                    auto buf = std::static_pointer_cast<OBFL>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->Flaechenindex_Teil_1_Int
                        , /*    3 */ buf->KreuzungsobjektindexTeil_1_Int
                        , /*    4 */ buf->Punktindex_1_Teil_1_Int
                        , /*    5 */ buf->Punktindex_2_Teil_1_Int
                        , /*    6 */ buf->Punktindex_3_Teil_1_Int
                        , /*    7 */ buf->Punktindex_4_Teil_1_Int
                        , /*    8 */ buf->Punktindex_1_Teil_2_Int
                        , /*    9 */ buf->Punktindex_2_Teil_2_Int
                        , /*   10 */ buf->Punktindex_3_Teil_2_Int
                        , /*   11 */ buf->Punktindex_4_Teil_2_Int
#ifdef FLP
                        , /*   12 */ buf->MS_Link_Int
#endif
                        , /*   13 */ buf->Flaechenindex_Teil_2_Int, /*   14 */ buf->Kreuzungsobjektindex_Teil_2_Int);
                }
                else if (std::strcmp("OGEL", aDSK) == 0 && g_dictDSKs["OGEL"])
                {
                    auto buf = std::static_pointer_cast<OGEL>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->Gelaendepunktindex_Teil_1_Int
                        , /*    3 */ buf->Kreuzungsobjektindex_Teil_1_Int
                        , /*    4 */ buf->StationFloat
                        , /*    5 */ buf->GelaendehoeheTrassenmitteFloat
                        , /*    6 */ buf->OrdinateSeitlichUeberhoehung_1_Float
                        , /*    7 */ buf->SeitlicheUeberhoehung_1_Float
                        , /*    8 */ buf->OrdinateSeitlicheUeberhoehung_2_Float
                        , /*    9 */ buf->SeitlicheUeberhoehung_2_Float
                        , /*   10 */ buf->Gelaendepunktindex_Teil_2_Int
                        , /*   11 */ buf->KulturartCode, /*   12 */ buf->KreuzungsobjektindexTeil_2_Int
                    );
                }
                else if (std::strcmp("OGE2", aDSK) == 0 && g_dictDSKs["OGE2"])
                {
                    auto buf = std::static_pointer_cast<OGE2>(ds.second);

                    (void)printf
                    (
                        buf->fmtPrintf
                        , /*    1 */ buf->DSK
                        , /*    2 */ buf->GelaendepunktindexInt
                        , /*    3 */ buf->KulturartReintext
                    );
                }
                queueDSKs.pop();
            }

        }
    } // ns parser
} // ns cc
