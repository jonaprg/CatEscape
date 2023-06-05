<img align="right" height="420" src="https://github.com/jonaprg/CatEscape/blob/master/img/catEscapeFront.jpeg">

# CatEscape
Robot autònom amb 3 rodes que amb 3 sensors de proximitat i una càmera és capaç de detectar un gat i allunyar-se'n sense xocar-se amb els obstacles.
## taula de continguts
* [Descripció](#Descripció)
* [Requeriments](#Requeriments)
* [Contribucions sorprenents](#Contribucions_sorprenents)
* [Esquema maquinari](#Esquema_maquinari)
* [Peces 3D](#Peces_3D)
* [Arquitectura Programari](#Arquitectura_Programari)
* [Algorismes](#Algorismes)
* [Resultat final](#Resultat_final)
* [Autors](#Autors)

## Descripció
Descobreix CatEscape, la joguina perfecta per als gats domèstics que els proporcionarà hores de diversió i entreteniment! Aquest robot innovador està dissenyat per permetre als gats moure's. Per assegurar-se que els gats no es cansin d'aquesta joguina, CatEscape també està equipat amb una funció especial que permet que el robot alliberi una petita porció de pinso quan el gat l'agafa o ha estat jugant amb ell durant un temps. Això manté l'interès del gat en la joguina durant més temps i els dóna una recompensa per a la seva activitat física i mental. No deixis que el teu gat es perdi la diversió i entreteniment que CatEscape té per oferir!

## Requeriments
### Raspberry (Python)
* [Python3.11.x](https://www.python.org)
* [Opencv](https://opencv.org/) 
* [smbus2](https://pypi.org/project/smbus2/)
### Arduino (C++)
* [Servo.h] Natiu amb Arduino
* [NewPing.h](https://reference.arduino.cc/reference/en/language/functions/communication/wire/)
* [Wire.h](https://reference.arduino.cc/reference/en/libraries/newping/)
* [CapacitiveSensor.h](https://www.arduinolibraries.info/libraries/capacitive-sensor)
## Contribucions sorprenents
* Proporciona entreteniment i activitat física: Els gats són animals actius per naturalesa i necessiten estimulació i exercici per mantenir-se sans i feliços.        CatEscape proporciona una forma divertida i emocionant per als gats de jugar i mantenir-se actius, la qual cosa pot millorar el seu benestar general.
* Fomenta la interacció entre propietari i mascota: Jugar amb els gats és una excel·lent manera de desenvolupar i reforçar el llaç entre el propietari i la mascota. CatEscape pot ser una eina per ajudar els propietaris a interactuar amb els seus gats i gaudir de moments divertits junts.
* Promou l'alimentació saludable: La funció de dispensar aliments de CatEscape pot ser una forma útil per assegurar que els gats rebin la quantitat adequada d'aliment i que mengin més lentament, la qual cosa pot ser beneficiós per a la seva digestió.
* Serà probablement l'únic del curs que interactua amb un ésser que no és una persona, a la vegada que interactua amb l'entorn.
* Innovació en joguines per a mascotes: CatEscape és una joguina innovadora que combina diverses funcions en un sol dispositiu, la qual cosa pot ser un avantatge competitiu en el mercat de joguines per a mascotes.
* Fomenta la creativitat: El disseny i la fabricació de CatEscape requereixen habilitats i coneixements tècnics, la qual cosa ens permet fomentar la nostra creativitat i ampliar els nostres coneixements en el desenvolupament d'un robot apte per a mascotes.

## Esquema maquinari
A continuació es mostren els diferents components que compta el robot acompanyat de l'esquema del maquinari:
* 3x Sensors de distància/ultrasò.
* 2x Rodes per moure el robot.
* 1x Raspberry pi zero.
* 1x Sensor capacitiu.
* 1x Controlador de motors.
* 1x Servomotor per la comporta del pinso.
* 1x Porta piles amb 6 piles.
* 1x Càmera 8 MB Raspberry PI.
* 2x Motor micro metall.
* 1x Roda de transferència.
* 1x ProtoBoard. 
<img src="https://github.com/jonaprg/CatEscape/blob/master/img/HW.PNG" width="557" height="300">

## Peces 3D
Per la creació del CatEscape, s'han hagut d'imprimir una sèrie de components 3d. Aquestes peces 3d s'han imprès a l'Open Lab de la Universitat Autònoma de Barcelona (UAB).
S'ha utilitzat el programa [onshape](https://cad.onshape.com/) pel disseny de tots els diversos components i [DevoVision](https://www.3devo.com/devovision/download) per la configuració dels dissenys 3d de la base i la part superior en l'extrusora.

Les dues primeres peces impreses són les parts principals del robot, ja que formen la base i la part superior del robot per poder suportar els diferents components d'aquest. A la base se li ha retallat dos rectangles de la part lateral per tal que hi puguin cabre les rodes, i quatre orificis per poder subjectar la part d'avall amb la de dalt. En la part superior se li han realitzat dos rectangles, un per encabir el switch activador del robot, i l'altre per tal que hi passi el cable de la cámera cap a la Raspberri. 

Amb les impressores 3d s'han imprès els tres suports dels sensors d'ultrasò, i els dos rectangles situats a la part superior del robot encarregats de subjectar el switch i de fer passar el cable de la cámera. 
A continuació es mostren els resultats:
* Base de fusta tallada amb extrusora 3devo
<img name="Base de fusta tallada amb fresadora CNC" src="https://github.com/jonaprg/CatEscape/blob/master/img/parte_abajo_madera.PNG" width="250" height="250">

* Part superior de fusta tallada amb extrusora 3devo
<img name="Part superior de fusta tallada amb fresadora CNC" src="https://github.com/jonaprg/CatEscape/blob/master/img/parte_arriba_madera.PNG" width="250" height="250">

* Suport sensors d'ultra sò
<img name="Suport sensors d'ultra sò" src="https://github.com/jonaprg/CatEscape/blob/master/img/soporte_ultras.jpeg" width="250" height="250">

* Suport switch bateries
<img name="Suport switch bateries" src="https://github.com/jonaprg/CatEscape/blob/master/img/soporte_switch.jpeg" width="250" height="350">

* Encaix connector Raspberry PI
<img name="Encaix connector Raspberry PI" src="https://github.com/jonaprg/CatEscape/blob/master/img/soporte_cable_raspi.jpeg" width="350" height="250">

## Arquitectura Software
![Esquema SW](img/SW.PNG)
* CatSearch: El robot buscará un gat per la casa fins a trobar-lo. Si no troba cap s’aturarà.
* CatFound: El robot troba un gat i s’apropa cap a ell.
* FeedCat:  El robot deixa anar una mica de pinso al ser tocat per premiar-lo mentre juga.
* CatEscape: El robot fugirà del gat.
* AvoidObstacles: El robot tracta de no xocar contra cap obstacle.

### Mòduls de Software
<img src="https://github.com/jonaprg/CatEscape/blob/master/img/DiagramaSoftwareModules.png" width="500" height="250">

* Càmera: Aquest sensor s’encarrega de fer fotografies que son utilitzades per el mòdul de detecció de gats.
* Mòdul de Detecció de gat: Un cop es rep una fotografía es comprova si hi ha una cara de gat a la fotografía, si hi ha una es llança una notificació.
* Raspberry Zero: La raspberry s’encarrega de gestionar tota la operativa del mòdul de detecció de gats, quan se'n detecta un s’envia la notificació a l’arduino fent servir la comunicació I2C.
* Sensor capacitiu: Aquest sensor és el responsable de detectar quan el gat toca el robot, més concretament la part conductiva del robot.
* Dispensador pinso: Aquest actuador és el responsable de dispensar el pinso del gat, quan el mòdul de premis consideri necessari.
* Mòdul de premis: Aquest mòdul s’encarrega de consultar el sensor capacitiu i, si ho considera necessari, premiar al gat fent ús de l’actuador per dispensar pinso.
* Arduino:  L’Arduino s’encarrega de gestionar la operativa per evitar obstacles, moure motors, dispensar pinso i detectar si el gat el toca
* Mòdul de navegació: Aquest mòdul permet que el robot sigui autònom per evitar obstacles i anar avançant.
* Sensor ultrasònic: Aquest sensor ens permet determinar la distància que hi ha als obstacles que el robot té al davant.
* Motors: Aquest actuador és el responsable que el robot giri a la dreta, esquerra, o vagi cap endavant depenent de les ordres que li arribin del mòdul de navegació.

## Algorismes
### Algorisme de detecció de cares de gats
Utilitzem un model anomenat 'haarscascade_frontalcatface_extended.xml' de la llibreria OpenCV per detectar les cares de gats sense necessitat d'entrenar un algoritme específic en cada ocasió. Un cop carreguem aquest model, per cada fotograma capturat per la càmera, buscarem la presència d'una cara de gat. Si s'identifica una cara de gat,  dibuixarem un quadrat a les coordenades retornades per la funció de detecció. A continuació, enviarem una comanda a l'Arduino per indicar que s'ha detectat com a mínim un gat a la imatge, i el robot iniciarà una maniobra d'evitació, tenint en compte la presència d'obstacles al seu camí per evitar col·lisions. Aquest procés permet al robot reaccionar de manera automàtica davant de la presència de gats, permetent-li escapar d'aquests de forma segura.

### Algorisme per evitar obstacles
L'algoritme d'evitació d'obstacles utilitza 3 sensors d'ultrasons i 2 motors per permetre que un robot es mogui de manera autònoma. Els sensors d'ultrasons són col·locats en posicions estratègiques del robot per mesurar la distància als obstacles que es troben al seu voltant. En cada iteració, el robot obté les lectures dels sensors per determinar si hi ha algun obstacle a prop i a quina distància es troba. Si es detecta un obstacle a una distància perillosa, l'algoritme activa els motors perquè el robot prengui una acció evasiva. Això pot implicar girar cap a una direcció segura lliure d'obstacles o aturar-se completament per evitar una col·lisió imminent. L'algoritme es repeteix de manera cíclica, permetent al robot navegar de manera autònoma i prendre decisions en temps real per evitar obstacles i garantir un moviment segur.

### Algorisme per premiar amb pinso
L'algoritme utilitza un sensor capacitiu per detectar els tocs i un actuador del tipus servomotor per dispensar menjar quan el gat el toqui. El sensor capacitiu està connectat a dos trossos de paper de plata, un al dipòsit de pinso i un altre a la part posterior del robot, per on surt el pinso. En cada iteració, l'algoritme monitora el sensor per detectar canvis provocats per un toc del gat. Quan es detecta un toc, l'algoritme activa l'actuador del servomotor per dispensar una quantitat de menjar al gat. L'algoritme es repeteix contínuament, permetent que el gat obtingui menjar cada cop que toca el sensor capacitiu. Aquest algoritme proporciona una forma interactiva i automatitzada de dispensar menjar al gat, afavorint la seva interacció amb el dispositiu i la seva satisfacció alimentària.

## Resultat final
A continuació es mostren una sèrie d'imatges sobre la versió final del catEscape:

* <em>Vista alçada</em>
<img height="420" src="https://github.com/jonaprg/CatEscape/blob/master/img/catEscapeFront.jpeg">

* <em>Vista perfil</em>
<img  height="420" src="https://github.com/jonaprg/CatEscape/blob/master/img/catEscapeSide.jpeg">

* <em>Vista aèria</em>
<img height="420" src="https://github.com/jonaprg/CatEscape/blob/master/img/catEscapeTop.jpeg">

## Autors
* Jose Antonio Ramos Andrades
* Jonathan Rojas Granda
* Roger López Puigbò
* Mohamed El Harrak Aeuil
