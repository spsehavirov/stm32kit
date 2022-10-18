/**
  ********************************************************************************************************************************************
  * @file     README.txt
  * @author   SPSE Havirov
  * @version  1.5
  * @date     28-April-2022 [v1.0]
  * @brief    Obecne informace o projektu.
  *
  ********************************************************************************************************************************************
  * @attention
  *
  *   Nasteni projektu:                   Jedna se o multi-workspace project, pri otvirani projektu nacist hlavni soubor "STM32_project.uvmpw"
  *
  *   Vyber pripravku:                    V leve casti "WorkSpace" postaci kliknout pr. tl. mysi a dat aktivovat projekt, veskere dalsi
  *                                         nastaveni pro dany pripravek bude provedeno automaticky v ramci hl. config_kit souboru.
  *                                       Nastaveni samotneho projektu (cast v "kouzelne hulce") nemenit!
  *
  *   Zname problemy:                     Pro NUCLEO G071 nefunguje debuge mod.
  *
  *   Cleneni projektu v adresarich:
  *       STM32_project/STM32/data/       Materialy pro jednotlive pripravky (referencni a uzivatelske manualy)
  *                                       Informace o pouzite verzi programu uKeil
  *       STM32_project/STM32/include/    Drivery pro pouzivane pripravky
  *       STM32_project/STM32/src/        Zdrojove kody pro jednotlive ulohy
  *       STM32_xxxxxx/                   Misto "xxxxxx" nasleduje nazev desky/pripravku. Pozor, ne vsechny jsou zahrnuty v projektu,
  *                                         ale nachystany do budoucna pro rozsireni
  *
  *   Verze Keil:                         uVision5.18.0.0
  *
  *   Package pro pouzitou verzi Keil:
  *     F407, F401, F411                  Keil.STM32F4xx_DFP.2.7.0.pack
  *     L152                              Keil.STM32L1xx_DFP.1.2.0.pack
  *     G071                              Keil.STM32G0xx_DFP.1.1.0.pack
  *
  ********************************************************************************************************************************************
  * @history
  *
  *   v1.5  [30-June-2022]
  *         - Docasne pozastaven vyvoj pro F401 u programu pro KeyPad (vcetne)
  *         - Celkova revize vsech zdrojovych kodu
  *         - Doplnena inforace o znamych problemech
  *
  *   v1.4  [13-June-2022]
  *         - Pridani zdrojovych kodu pro pouziti zakladnich casovacu:
  *             STM32_00_HelloWorld_06-blinkLED_TIMx.c
  *             STM32_00_HelloWorld_07-blinkLED_TIMx-2.c
  *         - Doplneni informace o puvodnich zdrojovych kodech obsazenych od v1.0 (viz zminena verze)
  *         - Zakomponovani "include path" v nastaveni projektu, pro include soubory neni nutno zadavat cestu,
  *             postaci jen nazev souboru napr. "STM32_config_kit.h"
  *         - Odebrani hlavniho makra "STM32_TYPE" ze vsech zdrojovych kodu (i do budoucna), nyni postaci pouze
  *             aktivovat prislusny projekt (nazev desky) a hl. config_kit se postara o nastaveni pro konkretni pripravek
  *
  *   v1.3  [28-April-2022]
  *         - Presun a prejmenovani dilcich adresaru s materialy, drivery a zdrojovymi kody do adresare STM32
  *         - Zmena relativnich adres pro zdrojove kody a drivery
  *
  *   v1.2  [18-April-2022]
  *         - Prejmenovani vsech slozek a projektu, pro zprehledneni. Zmena nazvu zanesena i do zdrojovych kodu.
  *         - V ramci "Multi-Project Workspace" pridany jen otestovane pripravky, respektive projekty (F407, F401 a G071).
  *           Dalsi pripravky (F411 a L152), maji projekty pouze nachystany.
  *         - Odebrani popisu "nastaveni projektu pri zmene pripravku v ramci zachovani rady" -> dale jiz neni potreba,
  *             kazdy pripravek bude mit svuj vlastni projekt -> jednodussi a rychlejsi pri zmene pripravku
  *
  *   v1.1  [10-April-2022]
  *         - Pridan  adresar s datasheety jednotlivych pripravku a informace o pouzite verzi Keil (vzostla celkova velikost!)
  *         - Zmena obycejneho projektu na "Multi-Project Workspace..", vsechny projekty v ramci jednoho WorkSpace a je mozno mezi nimi
  *             prepinat pomoci jejich aktivace (prave tlacitko mysi na dany projekt) - projekty uz neni nutno zavirat
  *         - Rozsireni @attention o "nastaveni projektu" a "vyber pripravku"
  *
  *   v1.0  [11-March-2022]
  *         - Vytvoreni dilcich projektu pojmenovanych podle typu desky/pripravku
  *         - Prepinani mezi projekty pomoci: "Close Project" -> "Open Proeject"
  *         - Zdrojove kody:
  *             STM32_00_HelloWorld_01-blinkLED.c
  *             STM32_00_HelloWorld_02-extLED.c
  *             STM32_00_HelloWorld_03-userButton.c
  *             STM32_00_HelloWorld_04-LCD.c
  *             STM32_00_HelloWorld_05-KeyPad.c
  *
  ********************************************************************************************************************************************
*/

