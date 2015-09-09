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
Skills investieren: AP, LP, Mana, Magieschaden, Waffenlevel und Magielevel. Die Skills 1 bis 4 erhöhen die
Obergrenze, die die jeweiligen Werte erreichen können. Das Waffenlevel legt fest, wie starke Waffen man verwenden kann,
das Magielevel gibt das selbe für Zauber an.

# Interagieren

Wenn man ein NPC anspricht, startet dieser ein Unterprogramm, mit dem Dialoge gezeigt, Quest vergeben, Handel abgeschlossen oder
Items übergeben werden. Auf die Dialoge gibt es immer mehrere Antworten, die der Spieler auswählen muss.

# Tränke

Trank-Items erhöhen die Werte des Spielers bis zum Maximum um einen festen Wert.