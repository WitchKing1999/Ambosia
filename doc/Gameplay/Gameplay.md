# Items

Items sind Gegenstände, die der Spieler in seinem Inventar platzieren kann. Sie haben einen Namen, eine Beschreibung
und ein Bild. Das Inventar beinhaltet alle Items. Es ist unendlich und kann über ein eigenes Menü bearbeitet werden.
In diesem Menü können Items angesehen verschoben, gelöscht und in Slots platziert werden. Damit Items die Statuswerte
des Spielers verändern können, müssen sie in Slots platziert werden. Ein Slot kann immer nur ein Item halten und ein
Item immer nur in einem Slot platziert werden.

# Statuswerte

Der Spieler hat mehrere Statuswerte:

* Angriffspunkte (AP)
* Magieangriffspunkte (MAP)
* Lebenspunkte (LP)
* Mana (Mana)
* Erfahrungspunkte (EP)

Items aber haben folgende Werte:

* Verteidigungsfaktor
* Angriffsfaktor

# Nahkampf

Der Angreifer hat Angriffspunkte (AP) und dessen Nahkampfwaffe einen Angriffsfaktor (AF).
Der Verteidiger hat Lebenspunkte (LP) und dessen Schild einen Verteidigungsfaktor (VF).
Greift der Angreifer an, wird der Bruttoschaden berechnet (AP*AF).
Aus diesem Bruttoschaden errechnet der Verteidiger den Nettoschaden (Bruttoschaden/VF),
dieser wird von den Lebenspunkten des Verteidigers abgezogen.
Sobald die LP kleiner oder gleich null sind, stirbt der Verteidiger.

# Fernkampf

Der Angreifer schießt einen Pfeil ab, der beim Verteidiger Schaden verursacht. Die Berechnung
funktioniert genauso wie beim Nahkampf.

# Zauber

Es gibt drei Arten von Zauber: Schüsse, Beschwörungen und Flächenzauber.
Schüsse funktionieren genauso wie der Fernkampf, ein Schuss kostet aber zusätzlich je nach Waffe Mana.
Beschwörungen kosten Mana und erstellen NPCs, die einem im Kampf unterstützen.
Flächenzauber kosten auch Mana und breiten sich über eine Fläche aus. Solange der Zauber besteht, wird allem
was in dem Zauber steht, Schaden zugefügt.

# Looten

Durch das Töten von NPCs erhält man Geld, Items und/oder Erfahrungspunkte (EP). Wieviel man wovon bekommt, ist bei jedem NPC
individuell festgelegt.

# Leveln

Hat man genug EP gesammelt, steigt man ein Level auf. Dadurch bekommt man Skillpunkte (SP). Diese SP kann man dann in verschiedene
Skills investieren: Zum einen kann man die Werte AP, LP, Mana und Magieschaden erhöhen, zum anderen gibt es Waffengruppen, die
mit SP freigeschaltet werden müssen: Nahkampfwaffen, Fernkampfwaffen, Magiewaffen und Schwere Waffen. Jede dieser Gruppen ist dazu noch
in 2 Stufen eingeteilt.

# Interagieren

Wenn man ein NPC anspricht, startet dieser ein Unterprogramm, mit dem Dialoge gezeigt, Quest vergeben, Handel abgeschlossen oder
Items übergeben werden. Auf die Dialoge gibt es immer mehrere Antworten, die der Spieler auswählen muss.

# Tränke

Trank-Items erhöhen die Werte des Spielers bis zum Maximum um einen festen Wert.
