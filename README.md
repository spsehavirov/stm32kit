# SPŠE ARM kit

## Obecné informace o projektu

### Nastavení projektu

Jedna se o multi-workspace project, pri otvirani projektu nacist hlavni soubor
`STM32_project.uvmpw`

### Výběr přípravku

V levé části "WorkSpace" postačí kliknout pravé tlačítko myši a dat 
`aktivovat projekt`, veškeré další nastavení pro daný přípravek bude
provedeno automaticky v ramci hl. config_kit souboru. Nastaveni 
samotneho projektu (cast v "kouzelné hůlce") **neměnit**!

### Organizace projektu

| Adresář               | Popis                                                 |
|-----------------------|-------------------------------------------------------|
| `src/`                | Místo pro váš kód, standartně  `app.c`                |
| `docs/`               | Dokumentace k projektu (stažená zvlášť - git modul)   |
| `examples/`           | Zdrojové kódy pro jednotlivé příklady (mimo písemky)  |
| `templates/`          | Šablony pro aplikaci s i bez RTOS                     |
| `stm32/`              | Hlavní adresář se soubory pro podporu STM32 platformy |
| `stm32/arch`          | Projekty a soubory používané Keilem pro board support |
| `STM32/arch/STM32_*/` | Jednotlivý projekt pro danou desku/platformu          |
| `stm32/boards/`       | Konfigurace pinu pro jednotlivé desky (DISC a NUCLEO) |
| `stm32/config/`       | Konfigurace projektu, nastavení pro RTOS i periferie  |
| `stm32/include/`      | Drivery pro používané přípravky                       |


## Podpora

Projekt pro správnou funkci potřebuje (minimálně) následující balíčky podpory (DFP):

| Platforma (deska)        | Balíček s podporu                            |
|--------------------------|----------------------------------------------|
| F407, F401, F411         | `Keil.STM32F4xx_DFP.2.7.0.pack`              |
| L151, L152               | `Keil.STM32L1xx_DFP.1.2.0.pack`              |
| G071                     | `Keil.STM32G0xx_DFP.1.5.0.pack`              |

Testováno s `ARM Keil uVision 5.18+` (5.37 - hlavní vývojová verze pro 1.5).

## Známé problémy

- `NUCLEO G071`: nefunguje `debug` mod
