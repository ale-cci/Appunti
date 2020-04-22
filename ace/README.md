# Architettura dei calcolatori Elettronici

### Software utilizzato
Il codice assembly speiegato a lezione è quello della CPU Intel 8086. Gli esempi di codice nel pdf sono compilabili ed eseguibili su [dosbox](https://www.dosbox.com/).

Nel file [dosbox.conf](./assembly/dosbox.conf) è presente la mia configurazione.

Richiede la presenza di [NG](https://elly.dia.unipr.it/2019/pluginfile.php/22353/mod_page/content/5/Ng.zip) e [TASM](https://elly.dia.unipr.it/2019/pluginfile.php/22353/mod_page/content/5/tasm.zip) nella stessa cartella del file.

### Note DOSBOX
Prendendo come esempio il programma assembly [assembly/src/hworld.asm](assembly/src/hworld.asm);


Per compilarlo
```
C:\SRC> ass HWORLD
```

Per eseguirlo
```
C:\SRC> HWORLD
```
o anche
```
C:\SRC> HWORLD.EXE
```

##### Shortcut dosbox
| shortcut | description|
|---|---|
| `Ctrl + F9` | kill processo |
| `Ctrl + F10` | toggle mouse capture |
| `Alt + Enter` | toggle fullscreen |

Per togliere focus del mouse `Ctrl

[Comandi shell](https://www.dosbox.com/wiki/Commands)

Norton guide: dopo aver eseguito `ng`, `Shift+F1` apre la guida.

### Debugger
Richiede il file [DEBUG.exe](https://elly.dia.unipr.it/2019/pluginfile.php/22353/mod_page/content/5/DEBUG.EXE) nella stessa cartella
```
C:\SRC> debug HWORLD
```

| command | Description|
|---|---|
| ? | show help menu|
| p | step to next instruction |
| t | step into |
| u | show disassembled code |
| r | print register content |
| d | dump memoria |
| q | quit |

### Note TurboDebugger
```
C:\SRC> td HWORLD.EXE
```
| Shortcut | Description |
|---|---|
| `Alt+x` | quit |
| `F8`    | single step |
| `Ctrl+w` | add variable to watchlist |
| `F2` | add breakpoint |
| `F9` | run |
| `Alt+F5` | show screen printed characters|
