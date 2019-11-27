<div align = "center">

# intelliPhoto

</div>

## Index
<!-- TOC -->

- [intelliPhoto](#intelliphoto)
  - [Index](#index)
    - [Einleitung](#einleitung)
    - [Projektentwicklungsplan](#projektentwicklungsplan)
    - [Spezifikation der Softwareanforderungen](#spezifikation-der-softwareanforderungen)
    - [Detaillierte Designspezifikation](#detaillierte-designspezifikation)
      - [Responsibility Driven Design](#responsibility-driven-design)
      - [Spezifikation des UML-Klassendiagramm und Use-Case Diagramm](#spezifikation-des-uml-klassendiagramm-und-use-case-diagramm)
        - [UML-Klassendiagramm](#uml-klassendiagramm)
      - [Spezifikation der UML-Squenz Diagramme und UML-Zustandsdiagramme](#spezifikation-der-uml-squenz-diagramme-und-uml-zustandsdiagramme)
    - [Testplan](#testplan)
    - [Testanalysebericht](#testanalysebericht)
    - [Projektentwicklungsbericht](#projektentwicklungsbericht)
    - [Bedienungsanleitung und Benutzerhandbuch](#bedienungsanleitung-und-benutzerhandbuch)

<!-- /TOC -->


-----------------------

### Einleitung

### Projektentwicklungsplan
Die Softwareentwicklung gliedert sich in folgende Teile:
    1. Verständnis der Anforderungen 
    2. Responsibility Driven Design
    3. Spezifikation des UML-Klassendiagramm und Use-Case Diagramm
    4. Spezifikation der UML-Squenz Diagramme und UML-Zustandsdiagramme
    5. Implementierung des Frameworks
   
Eine detaillierte Beschreibung der einzelnen Teile finden Sie in den folgenden Kapiteln.

----------------
### Spezifikation der Softwareanforderungen
Hauptverantwortlicher: Xiangyu Tong
In diesem Teil analysieren wir die Anforderungen und legen die Richtung der nächsten Softwareentwicklung fest.

--------------
### Detaillierte Designspezifikation
Dieser Teil ist in dem im "Projektentwicklungsplan" genannten 2 ~ 4-Teil enthalten.

#### Responsibility Driven Design
Hauptverantortlicher: Piljug Jeremias  

Im 2. Teil finden wir alle Klassen, Verantwortlichkeiten, Kollaborationen und Beziehungen.  

#### Spezifikation des UML-Klassendiagramm und Use-Case Diagramm
Hauptverantortlicher: Dongze Yang  

Im 3. Teil erstellen wir auf Grundlage des Softwareanforderungen einen geeigneten Entwurf der Klassenhierarchie als UML-Klassendiagramm, indem wir die genauen Interfaces eventueller Klassen an sowie die Attribute, welche die jeweiligen Klassen verwalten.

Außerdem führen wir eine Umfeldanalyse, in dieser haben wir wertvolle Informationen über verschiedene Nutzergruppen gesammelt, und dann fassen wir die beschriebenen Ergebnisse in einem UML Use-Case-Diagramm zusammen.

##### UML-Klassendiagramm
Das UML-Diagramm, das wir ursprünglich entworfen haben, sieht wie folgt aus:  
<div align="center">
<img src="https://raw.githubusercontent.com/XYTong/software-engineer/master/Ue3/3.png" >
</div>
Und wir versuchen, eine Verhaltenssimulation über diesen Graphen durchzuführen:  

(Use-case) Benutzer möchte das Bild drehen 
Von der Auswahl von „Drehen" durch den Benutzer bis zum Abschluss der Bildrotation sollten die folgenden Schritte ausgeführt werden:
1. Der Benutzer öffnet ein Bild
2. Der Benutzer klickt auf den Knopf „Drehen"
3. Das System erledigt den Dreh-Aufgabe
4. Das System zeigt das Resultat an

Dann ist der Prozess wie folgt:
<div align="center">
<img src="https://raw.githubusercontent.com/XYTong/software-engineer/master/Ue3/sc1.png" >
<img src="https://raw.githubusercontent.com/XYTong/software-engineer/master/Ue3/sc2.png" >
<img src="https://raw.githubusercontent.com/XYTong/software-engineer/master/Ue3/sc3.png" >
</div>

Zuerst dachten wir, dass dies in Ordnung ist, aber dann fanden wir beim Entwerfen des UML-Sequenzdiagramms einige Probleme mit den aktuellen UML-Diagrammen.

Beispielsweise können aus Sicht der Implementierung einige Funktionen kombiniert und einige Funktionen müssen getrennt werden. Zu diesem Zweck haben wir das UML-Diagramm neu gestaltet(Der größte Dank geht an Pascal für seinen Beitrag zum Team).

Das neue UML-Diagramm sieht folgendermaßen aus:
<div align="center"><object data="https://raw.githubusercontent.com/XYTong/software-engineer/master/Ue4/Klassendiagramm_v2.svg" type="image/svg+xml">
</object>
</div>

#### Spezifikation der UML-Squenz Diagramme und UML-Zustandsdiagramme
Hauptverantortlicher: Schröter Pascal  

Erstellen wir auf der Grundlage des Softwareanforderungen ein geeignetes Design eines Szenarios als UMLSequenzdiagramme, indem es Interaktionen zwischen einer Menge von Objekten in einer Zeitsequenz darstellt.  

Außerdem erstellen wir ein Zustandsdiagramm eines InterlliPhoto, dafür definieren wir geeignete Zustandsübergänge und evtl. Bedingungen. Und das beschreibt die zeitliche Evolution eines Objektes von einer gegebenen Klasse in Abhängigkeit von Interaktionen mit anderen Objekten innerhalb und außerhalb des Systems.

----------------
### Testplan

---------------
### Testanalysebericht

------------
### Projektentwicklungsbericht
Hauptverantortlicher: Xiangyu Tong

Im 5. Teil implementieren wir diese Software. 


--------------
### Bedienungsanleitung und Benutzerhandbuch