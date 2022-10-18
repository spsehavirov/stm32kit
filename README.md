# SPŠE ARM kit

## Obecné informace o projektu

### Nastavení projektu

Jedna se o multi-workspace project, pri otvirani projektu nacist hlavni soubor `STM32_project.uvmpw`

### Výběr přípravku

V levé části "WorkSpace" postačí kliknout pravé tlačítko myši a dat `aktivovat projekt`, veškeré další nastavení pro daný přípravek bude
provedeno automaticky v ramci hl. config_kit souboru. Nastaveni samotneho projektu (cast v "kouzelné hůlce") **neměnit**!

### Organizace projektu

| Adresář                    | Popis                                                  |
|----------------------------|--------------------------------------------------------|
| `STM32/`                   | Hlavní adresář se soubory pro podportu STM32 platformy |
| `docs`                     | Dokumentace k projektu (stažená zvlášť - git modul)    |
| `STM32/arch`               | Projekty a soubory používané Keilem pro board support  |
| `STM32/arch/STM32_xxxxxx/` | Jednotlivý projekt pro danou desku/platformu           |
| `STM32/include`            | Drivery pro používané přípravky                        |
| `STM32/src`                | Zdrojové kódy pro jednotlivé úlohy                     |

## Podpora

Projekt pro správnou funkci potřebuje (minimálně) následující balíčky podpory (DFP):

| Platforma (deska)        | Balíček s podporu                            |
|--------------------------|----------------------------------------------|
| F407, F401, F411         | `Keil.STM32F4xx_DFP.2.7.0.pack`              |
| L151, L152               | `Keil.STM32L1xx_DFP.1.2.0.pack`              |
| G071                     | `Keil.STM32G0xx_DFP.1.1.0.pack`              |

Testováno s `ARM Keil uVision 5.18+` (5.37 - hlavní vývojová verze pro 1.5).

## Známé problémy

- `NUCLEO G071`: nefunguje `debug` mod
