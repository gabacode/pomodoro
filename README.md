# 🍅 Pomodoro Timer

- [Introduzione](#introduzione)
- [Requisiti](#requisiti)
- [Ringraziamenti](#ringraziamenti)
- [Licenza](#licenza)

---

# Introduzione

La _tecnica del pomodoro_ è un metodo di gestione del tempo lavorativo, mirato all'ottimizzazione della produttività, sviluppato inizialmente da Francesco Cirillo.

La metodologia originale prevede 4 periodi da 25 minuti ciascuno, intervallati da breve pause da 5 minuti ciascuna, finendo con una pausa più lunga da circa 15 minuti.

Questa popolare tecnica mira all'ottimizazione dei tempi di attenzione durante una fase produttiva, evitando lunghi periodi di lavoro non supervisionati.

Il progetto qui illustrato è stato presentato come progetto personale durante il corso _Arduino per tutt*_, organizzato dal [Centro di Sviluppo Creativo Danilo Dolci](https://danilodolci.org/), in associazione con l'[Associazione Culturale Bocs di Bagheria](https://www.arcipalermo.it/index.php/i-circoli/bocs-bagheria).

---

# Requisiti

I componenti che erano stati forniti per il progetto personale, erano quelli contenuti all'interno dell'[Elegoo Arduino Starter Kit](https://www.elegoo.com/products/elegoo-uno-project-super-starter-kit).  
In particolare sono stati utilizzati i seguenti componenti:

- 1x Elegoo Arduino Uno R3 (ATMEGA328P)
- 1x Display a 7 segmenti
- 2x 74HC595 Shift Register
- 1x Passive Buzzer
- 1x Push Button
- 8x 220Ω Resistors
- 1x Breadboard e cavi jumper

Grazie alla libreria [SevSeg Shift](https://github.com/bridystone/SevSegShift) di [bridystone](https://github.com/bridystone) è possibile utilizzare solo 3 digital pins per pilotare il display a 7 segmenti, con l'utilizzo di 2 registri a scorrimento 74HC595.

# Ringraziamenti

[Bocs APS](https://www.facebook.com/BocsClub)  
[CSC Danilo Dolci](https://danilodolci.org/)  
[Giuseppe Reres](https://uk.linkedin.com/in/giuseppe-reres-506bb0100) e [Vidjaya Thelen](https://it.linkedin.com/in/vidjaya-thelen-180b31173)

# Licenza

Tutto il lavoro contenuto all'interno di questo repo è concesso in licenza GPLv3.
