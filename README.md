# Projet C
## Simulation d'un écosystème

Se placer dans la *racine* du projet puis lancer le script
```
./run.sh
```

---

Pour tout compiler:
```
make
```

Pour compiler l'executable de la simulation:
```
make ecosys
```

Pour compiler les tests: 
```
make tests_ecosys
make tests_ecosys2
```

On peut afficher les courbes du nombre de proies et de prédateurs en fonction du nombre de générations avec le script python ```plot.py``` <br>
Avoir pandas et mathplotlib installées, puis le lancer avec python:
```
python ./plot.py
```

Des stats divers
```
python ./stats.py
```


---

FABRICI Tifenn <br>
https://github.com/tifennf