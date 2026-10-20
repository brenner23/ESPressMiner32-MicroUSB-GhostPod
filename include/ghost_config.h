#pragma once
// Ghost Pod: Hardware und Geister-Stufen (nur Bauvariante GHOST_POD=1, eingebunden aus config.h)

// ---------------------------------------------------------------------------
//  Ghost Pod: Hardware im Eisbecher
// ---------------------------------------------------------------------------
#define PIN_LED1                 25   //  9 Uhr, rot links  - Lebenszeichen (halbe Share-Diff)
#define PIN_LED2                 26   // 12 Uhr, rot oben   - Share gefunden (im 2.6-Code faelschlich "rechts")
#define PIN_LED3                 27   //  3 Uhr, rot rechts - Highscore geknackt (im 2.6-Code faelschlich "oben")
#define PIN_LED4                 14   //  6 Uhr, Herz       - BLOCK (zwischen den gruenen)
#define PIN_GREEN_STEADY         13   // gruen: an = es wird gemint
#define PIN_GREEN_BLINK          12   // gruen: Sekundentakt / schnell beim Riechen
#define PIN_BEEPER               23
#define PIN_TOUCH_A              32   // Kupferband um den Becher (Ground-Haelfte des Dipols)
#define PIN_TOUCH_B              33   // Teleskop-Stabantenne
#define PIN_NOISE_ADC            34   // offener ADC1-Pin = reines Rauschen
#define PIN_BRIDGE               21   // Drahtbruecke auf GND: Highscore dauerhaft, gezogen: nur seit Start

// ---------------------------------------------------------------------------
//  Ghost Pod: Geister-Stufen (echte Difficulty, vom Pool mitgeteilt)
//    LED1 ( 9 Uhr) = Pool-Difficulty x LED1_FACTOR  -> Lebenszeichen, "da ist Aktivitaet"
//    LED2 (12 Uhr) = Pool-Difficulty                -> echter Share, geht an den Pool
//    LED3 ( 3 Uhr) = Highscore geknackt             -> hoeher als der bisherige Bestwert
//    LED4 ( 6 Uhr) = Netz-Difficulty                -> echter BLOCK (Piepser + Poltergeist)
// ---------------------------------------------------------------------------
#define GHOST_LED1_FACTOR        0.5
// Highscore-Lampe: 0 = Bestwert ohne Zeitfenster, sonst = Bestwert der letzten N Stunden
// (1..48, z.B. 24 = "staerkster Geist des Tages").
// Bei 0 entscheidet die Drahtbruecke an PIN_BRIDGE (einmal beim Einschalten gelesen):
//   gesteckt (GND) = Allzeit-Bestwert, ueberlebt Neustarts
//   gezogen        = Bestwert seit dem letzten Start
#define GHOST_HIGHSCORE_HOURS    0
// Nach einem Block bleibt die Herz-LED so viele Stunden an
#define GHOST_BLOCK_LED_HOURS    24

// Takt einer kompletten Runde: Scan (Nase in die Luft) + Suche + Ergebnis zeigen.
// Die Suchzeit wird daraus berechnet:  60 s - 3 s Scan - 5 s Ergebnis = 52 s Suche
#define GHOST_CYCLE_S            60
#define GHOST_SHOW_S             5
#define GHOST_ROUND_S            (GHOST_CYCLE_S - GHOST_SHOW_S - GHOST_SCAN_MS / 1000)

// Piepser pro Stufe (1 = an)
#define GHOST_BEEP_LED1          0
#define GHOST_BEEP_LED2          0
#define GHOST_BEEP_LED3          0
#define GHOST_BEEP_LED4          1

// "In die Luft riechen": so lange wird bei jedem neuen Job die Antenne abgetastet
#define GHOST_SNIFF_MS           200
// ... und so lange zu Beginn jeder Runde (Scan-Phase wie bei Ghost Pod 2.6, Mining laeuft weiter)
#define GHOST_SCAN_MS            3000

// Stabantenne: gemessener Touch-Wert (PIN_TOUCH_B) je Stellung, eingefahren -> ganz ausgezogen.
// Gemessen am Schreibtisch 2026-10-08. Zugeordnet wird die naechstgelegene Stellung.
#define GHOST_ANT_CAL            { 64.0f, 59.4f, 55.0f, 52.0f, 48.7f, 45.0f }
#define GHOST_ANT_BASE_CM        19   // Laenge eingefahren
#define GHOST_ANT_SEG_CM         15   // je ausgezogenes Segment

// Historie hoechstens so oft in den Flash schreiben (Stufe 3/4 + Block sofort)
#define GHOST_SAVE_INTERVAL_S    600
