# Změny a vývoj projektu

## [next]:


## [2.2.0] 2023-10-04:
- `Fix`: Keypad modes not reacting correctly with 3x4 or 4x3

## [2.1.0] 2023-09-21:
- `Add`: Adding `pin.h` to simplify the pin setup
- `Mod`: Editing the drivers to support new pin.h header
- `Mod`: Renaming `KeyPad_*` functions to `KBD_*` to match the style
- `Mod`: Examples to use config header
- `Add`: Typealias for `enum pin` as `pin_t` (POSIX naming)

## [2.0.0] 2023-03-29:
- Facelift of the project to clean up the process

## [1.5.9][18-November-2022]:

- `Mod`: Reorganising the structure to better support the Git repository
- `Add`: Adding git repository and pushing it to github.com
- `Add`: Adding basic support for `RTOS`

## [1.5][30-June-2022]:

- Docasně pozastaven vývoj pro F401 u programu pro KeyPad (včetně)
- Celková revize všech zdrojových kodu
- Doplněná inforace o znamých problémech
- `gpio.h`
  - Vycleneni funkci pro praci s casem do solo knihovny (pro budouci podporu RTX)
- `keypad.h`:
  - Uprava funkce `KeyPad_getKey()`, odstraneni nepouzivane promenne key (nahrazeni pevnou hodnotou pro return)
- `lcd.h`:
  - Odebrani zakomentovane funkce pro kontrolu zaneprazdnenosti LCD, vcetne odebrani dalsich nepotrebnych radku (vsechny drive zakomentovany)
- `platform.h`:
  - Vytvoreni solo hlavickoveho souboru pro praci s I/O
  - pridani auto-detekce compiler-u pro vetsi granularitu nastaveni
  - umozneni pouzivani pinoutu pomoci `enum pin`

## [1.4.3][30-June-2022]:

- `Add`: zjednodušení pinout nastavením (`enum pin`)
- `Add`: Uprava definu pro praci s *_platform.h a vyuzivani jejich maker
- `timers.h`:
  - Vytvoreni maker pro nastaveni PSC, ARR a CNT registru u casovace
  - Prepsani funkce pro konfigurace casovace (odebrani vstupnich parametru) pro vyuziti vytvorenych maker
  - Otestovano pro pripravek G071
  - Uprava dilcich komentaru, sjednoceni zapisu


## [1.4][13-June-2022]:

- Pridani zdrojovych kodu pro pouziti zakladnich casovacu:
            STM32_00_HelloWorld_06-blinkLED_TIMx.c
            STM32_00_HelloWorld_07-blinkLED_TIMx-2.c
- Doplneni informace o puvodnich zdrojovych kodech obsazenych od v1.0 (viz zminena verze)
- Zakomponovani "include path" v nastaveni projektu, pro include soubory neni nutno zadavat cestu, postaci jen nazev souboru napr. "STM32_config_kit.h"
- Odebrani hlavniho makra "STM32_TYPE" ze vsech zdrojovych kodu (i do budoucna), nyni postaci pouze aktivovat prislusny projekt (nazev desky) a hl. config_kit se postara o nastaveni pro konkretni pripravek

## [1.3][28-April-2022]:

- Presun a prejmenovani dilcich adresaru s materialy, drivery a zdrojovymi kody do adresare STM32
- Zmena relativnich adres pro zdrojove kody a drivery

## [1.2][18-April-2022]:

- Prejmenovani vsech slozek a projektu, pro zprehledneni. Zmena nazvu zanesena i do zdrojovych kodu.
- V ramci "Multi-Project Workspace" pridany jen otestovane pripravky, respektive projekty (F407, F401 a G071). Dalsi pripravky (F411 a L152), maji projekty pouze nachystany.
- Odebrani popisu "nastaveni projektu pri zmene pripravku v ramci zachovani rady" -> dale jiz neni potreba, kazdy pripravek bude mit svuj vlastni projekt -> jednodussi a rychlejsi pri zmene pripravku

## [1.1][10-April-2022]:

- Pridan  adresar s datasheety jednotlivych pripravku a informace o pouzite verzi Keil (vzostla celkova velikost!)
- Zmena obycejneho projektu na "Multi-Project Workspace..", vsechny projekty v ramci jednoho WorkSpace a je mozno mezi nimi prepinat pomoci jejich aktivace (prave tlacitko mysi na dany projekt) - projekty uz neni nutno zavirat
- Rozsireni @attention o "nastaveni projektu" a "vyber pripravku"
- Uprava hl. komentare v casti kodu pro pripravky
- Uprava dilcich komentaru, sjednoceni zapisu
- Zmena vyberu desky a linkovani device header pro pouzity pripravek
- Uprava hl. komentare v casti kodu pro pripravky

## [1.0][11-March-2022]:

- Vytvoreni dilcich projektu pojmenovanych podle typu desky/pripravku
- Prepinani mezi projekty pomoci: "Close Project" -> "Open Proeject"
- Zdrojove kody:
  - STM32_00_HelloWorld_01-blinkLED.c
  - STM32_00_HelloWorld_02-extLED.c
  - STM32_00_HelloWorld_03-userButton.c
  - STM32_00_HelloWorld_04-LCD.c
  - STM32_00_HelloWorld_05-KeyPad.c
- Pro pripravek G071 zmena portu a pinu pro vestavene LED a zmena pinu pro externi LED (odseparovani od F401, F411 a L152 v ramci pouzitych maker), vyuziti volnych pinu (ty jez jsou urceny jen jako I/O)
- Drobne upravy komentaru

## [0.9][27-February-2022]:

- Prvni verze driveru pro sirsi pouziti
- Otestovano pro pripravek F407 a F401
