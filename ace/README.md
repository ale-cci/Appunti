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

