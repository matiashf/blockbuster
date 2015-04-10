# Prosjektarbeid i C++ 2015
* **Tittel**: Blockbuster
* **Gruppemedlemmer**: s193364

## Prosjektbeskrivelse

Et sanntids 2D-spill med fysikkmotor der spillerne styrer hver sin
kule og forsøker å ødelegge hverandres blokker.

## Hovedfunksjonalitet i korte trekk

1. Når spillet starter skal man kunne velge antall spillere.
2. Hver spiller velger én farge og fire taster for bevegelse i to dimensjoner.
3. Det velges blant flere ulike brett.
4. Brettet vises. Hver spiller har én kule og flere blokker i sin farge.
5. Når en spiller holder ned en tast, aksellererer kulen i tilhørende retning.
6. Når blokker utsettes for støt, tar de skade. Dette vises ved
   farge-/teksturendring, ikke deformering.
7. Når en blokk har tatt nok skade knuses den.
8. Store blokker som knuses blir til mindre blokker.
9. Små blokker som knuses blir til fragmenter eller forsvinner helt.
10. Når alle blokkene til en spiller er knust har spilleren tapt og
    kan ikke lenger bevege kulen sin.

## Designmål: 

Spillet skal implementeres med Qt sin QGrahipcsView og fysikkmotoren
box2d. Det skal ikke tas høyde for spilling over nettverk.

* Utvidbarhet. Det skal være mulig å...
  - lage varianter av spillet, f.eks. enspillermodus.
  - vilkårlige input-metoder som f.eks. touch, spillkontroller.
  - implementere AI.
  - Lage nye brett uten å rekompilere spillet
  - Kunne lage ulike type blokker (f.eks. is, isopor, stein) med
    forskjellig hardhet, massetetthet, restitusjon (sprett), og
    utseende.
* Modularitet:
  - Kunne rendre forhåndsvisning av et spillbrett uten interaktivitet
* Ytelse: 30-60 FPS

## Avgrensning:

Jeg kommer til å prioritere funksjonalitet fremfor utseende.

Minimumsmål: Ett enkelt brett med én enkelt spiller som kan bevege en
ball og flytte på uknuselige blokker.

Ambisiøse mål:
* Laste inn spill fra tekstfil
* Forhåndsvise spillbrett
* Blokker knuses til fragmenter
* Teksturer på spillobjekter.
* AI-spiller.
