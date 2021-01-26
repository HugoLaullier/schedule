# Projet emploi du temps

**LAULLIER Hugo 2A SDIA**
**BALZANO Antoine 2A SDIA**

## 1 Installation

Installation depuis l'archive: unzip l'archive et se placer dans le dossier schedule.

## 2 Tester le programme

 - *easena schedule.ez*
 - *make*
 - *./schedule --seed 1611279467*
Le programme peut prendre du temps à s'éxécuter car nous avons utilisé une très grande population. Il est possible de la réduire dans le fichier schedule.ez (ligne 809)

Les graines intéressantes sont données dans le fichier seed.txt

## Visualisation de l'emploi du temps

 - Se placer dans le dossier schedule et executez :
*php -S localhost:8000*

 - Toujours depuis le dossier schedule, executez :
*firefox http://localhost:8000/index.html*
ou
*chrome http://localhost:8000/index.html*

