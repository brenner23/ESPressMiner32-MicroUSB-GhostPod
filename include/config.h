#pragma once
// ---------------------------------------------------------------------------
//  Allgemeine Einstellungen
// ---------------------------------------------------------------------------

// Bauvariante: GHOST_POD=1 = Ghost Pod (Geisterdetektor im Eisbecher, env:ghostpod), sonst normaler Miner
#ifndef GHOST_POD
#define GHOST_POD 0
#endif

#if GHOST_POD
#define MINER_NAME        "GhostPod"
#else
#define MINER_NAME        "ESPressMiner32"
#endif
#define MINER_BUILD       __DATE__ " " __TIME__
#if HW_LOOP_TEST
#define MINER_VERSION     "1.1.0.007-looptest"   // Messbetrieb Micro-USB: dfw (.004) gegen O-Varianten (.007)
#elif DIAG_NET
#define MINER_VERSION     "1.1.0.007-diag"   // Test-Build: Netz-Diagnose /api/diag (10-Minuten-Fehlerschub)
#elif GHOST_POD
#define MINER_VERSION     "3.1.0.003"   // Ghost Pod: .003 Wi-Fi 2, Schnell-Setup (nur WLAN), Klapp-Abschnitte. .002 Neustart-Uebergabe + Pool-Tausch. .001 Unterbau von 1.1.1 (Hash-Schleife Rev. 1 ~1006 kH/s, WLAN-Waechter), Geister-Funktionen wie 3.0.0
#else
#define MINER_VERSION     "1.1.1.003"   // .003: Wi-Fi 2 (wird mitgeprueft), Schnell-Setup ohne Pool, Settings-Abschnitte aufklappbar (Zustand im NVS). .002: Neustart-Uebergabe (Betriebszeit, Best Diff, Blocks; Shares ab 0), Knopf Primary<->Secondary tauschen. .001: Ghost Pod als Bauvariante (env:ghostpod) im selben Projekt; Miner-Code = 1.1.1
#endif
#define MINER_REPO_URL    "https://github.com/brenner23/ESPressMiner32-DevKitC-MicroUSB"

// ---- Anzeige: Fehler aus WLAN-Wellen (ab v1.1.1, wie USB-C v1.3.1) -----------------------------
// SHOW_WAVE_ERRORS 0 = Dashboard und Konsole zeigen nur die Fehler der Hash-Schleife: "4 discarded"
// SHOW_WAVE_ERRORS 1 = zusaetzlich die Fehler aus WLAN-Wellen:      "4 discarded (+8 from 1 Wi-Fi wave)"
// Wellen = periodische Stoerung durch den Router (z. B. FRITZ!Box Mesh/Schluesselwechsel, alle ~600 s).
// Gezaehlt wird immer: /api/stats liefert hwErrors (gesamt), waveErrors und loopErrors.
#ifndef SHOW_WAVE_ERRORS
#define SHOW_WAVE_ERRORS         0
#endif

// Difficulty, die beim Pool angefragt wird (mining.suggest_difficulty).
// Bei ~1 MH/s ergibt 0.0005 etwa alle 8-9 Sekunden einen Share.
#define POOL_SUGGEST_DIFFICULTY  0.0005

// Pool-Verbindung gilt als tot, wenn so lange nichts empfangen wurde
#define STRATUM_RX_TIMEOUT_MS    (5UL * 60UL * 1000UL)
#define STRATUM_RECONNECT_MS     5000UL

// Statusausgabe auf der seriellen Konsole
#define STATS_INTERVAL_MS        5000UL

// Core-Zuordnung: Hardware-SHA-Miner exklusiv auf Core 1,
// WLAN/Stratum + Software-Miner auf Core 0
#define HW_MINER_CORE            1
#define SW_MINER_CORE            0
// Master 002: aus, weil er den HW-Miner ueber den Bus um ~95 kH/s bremste.
// Master 003 (v1.2.1): an. Die v2-Schleife haelt >= 3 Takte zwischen SHA-Writes ein
// und verliert dadurch nur ~3 kH/s (gemessen: HW 959.6 + SW 30.4 = 990 kH/s).
#define ENABLE_SW_MINER          1

// Nonce-Aufteilung zwischen Hardware- und Software-Miner
#define HW_NONCE_START           0x00000000UL
#define HW_NONCE_END             0xE0000000UL   // exklusiv
#define SW_NONCE_START           0xE0000000UL
#define SW_NONCE_END             0xFFFFFFFFUL

// Nonces pro Durchlauf, bevor auf einen neuen Job geprueft wird
#define HW_BATCH_SIZE            8192
#define SW_BATCH_SIZE            1024

// HW-Miner (Core 1): Zwangspause von 1 Tick alle HW_YIELD_MS. 0 = keine Pause (ab 1.3.0.006).
// Auf Core 1 laeuft sonst nichts (loopTask beendet, Watchdog prueft IDLE1 nicht), die Pause
// kostete ~0,2 % (1 ms je 500 ms). Zurueck: 500.
#ifndef HW_YIELD_MS
#define HW_YIELD_MS              0
#endif

// Pre 1 (aus USB-C Master 005): Interrupts auf Core 1 waehrend einer HW-Charge sperren.
// Tick-/IPC-Unterbrechungen kosten sonst ~0,5 %. Danach kurz frei, damit wartende Interrupts laufen.
// Rev. 1: die _df-Schleifen stellen den gesicherten PS selbst wieder her (bleibt gesperrt). 0 = aus (wie 1.1.0.007).
#ifndef HW_IRQ_LOCK
#define HW_IRQ_LOCK              1
#endif

// Sicherheitsabstand (CPU-Takte) auf die beim Start gemessenen Grenzwerte
// der Hardware-Pipeline. Kleiner = schneller, groesser = mehr Reserve.
#define HW_CAL_MARGIN_BLOCK      1
#define HW_CAL_MARGIN_LOAD       1

// Hash-Schleife in Assembler (src/hw_scan_asm.S) statt C. 0 = C-Version
// Gemessen: Assembler 255 Takte/Hash, C 249. Die dichter gepackten Writes stauen
// sich am Bus (jeder Takt Pause nach START kostet genau einen Takt) -> C bleibt aktiv.
// Hinweis Master 003: hw_scan_asm.S zaehlt die Nonce noch byte-getauscht und passt
// nicht mehr zur T[3]-Wort-Zaehlung -> nicht einschalten.
#define HW_USE_ASM               0
// Zusaetzliche Takte zwischen START von Block 1 und dem ersten Block-2-Write
// (die Engine liest T[0..7] erst nach START ein). Die Kalibrierung prueft das mit.
#define HW_ASM_LOOP_GUARD        0

// Master 004 Messbetrieb: >0 = Varianten der Hash-Schleife reihum je so viele Minuten
// minen und Hashrate / verworfene Kandidaten je Variante protokollieren (Konsole, /api/stats).
// 0 = Normalbetrieb.
#ifndef HW_LOOP_TEST
#define HW_LOOP_TEST             0
#endif

// Ueberhitzungsschutz (ab 1.3.0.004), Werte des internen Sensors (grob, +-10 Grad Versatz).
// Ab SW_PAUSE pausiert der Software-Miner, ab STOP das ganze Mining; unter RESUME laeuft
// alles wieder. Werte ausserhalb PLAUSIBLE gelten als Sensorfehler und werden ignoriert.
#ifndef TEMP_SW_PAUSE_C
#define TEMP_SW_PAUSE_C          90.0f
#endif
#ifndef TEMP_STOP_C
#define TEMP_STOP_C              100.0f
#endif
#ifndef TEMP_RESUME_C
#define TEMP_RESUME_C            80.0f
#endif
#define TEMP_PLAUSIBLE_MIN_C     (-20.0f)
#define TEMP_PLAUSIBLE_MAX_C     150.0f

// mDNS-Name (Standard fuer den Hostnamen)  ->  http://espressminer.local
#if GHOST_POD
#define WEB_MDNS_NAME            "ghostpod"
#else
#define WEB_MDNS_NAME            "espressminer"
#endif

// Einrichtungs-Portal: WLAN "ESPressMiner32-XXXX" (min. 8 Zeichen Passwort)
#if GHOST_POD
#define PORTAL_AP_PASSWORD       "ghostpod"
#else
#define PORTAL_AP_PASSWORD       "espressminer"
#endif
// So lange wird beim Start auf das gespeicherte WLAN gewartet, dann Portal zusaetzlich an
#define WIFI_CONNECT_TIMEOUT_MS  20000UL

// WLAN-Waechter (ab 1.3.0.008): Nach einem Kanalwechsel im Mesh blieb 1.3.0.007 dauerhaft
// offline. Ist das WLAN so lange weg, wird neu verbunden (Suche ueber alle Kanaele) ...
#define WIFI_RECONNECT_AFTER_MS  10000UL
#define WIFI_RECONNECT_EVERY_MS  20000UL
// ... und hilft das nicht, startet der Miner neu.
#define WIFI_REBOOT_AFTER_MS     (3UL * 60UL * 1000UL)
// ab .003: auf WLAN 2 so oft nachsehen, ob WLAN 1 wieder da ist (wie Pool: 10 min)
#define WIFI2_RETRY_PRIMARY_MS   (10UL * 60UL * 1000UL)

// Schutzfenster (ab 1.3.0.008): Ein Geraet im Netz (Mesh/Router) stoert den ESP alle
// ~600 s fuer einen Augenblick (4-8 HW-Fehler auf einen Schlag). Der Miner lernt diesen
// Takt und rechnet um den erwarteten Zeitpunkt herum mit einer vorsichtigeren Schleife.
#ifndef HW_GUARD_ENABLE
#define HW_GUARD_ENABLE          1
#endif
#define HW_GUARD_BURST_ERRORS    2        // so viele HW-Fehler ...
#define HW_GUARD_BURST_MS        2000UL   // ... innerhalb dieser Zeit = Schub
#define HW_GUARD_PERIOD_MIN_MS   60000UL  // erlaubter Takt 1 .. 30 min (hier gemessen: 600,47 s)
#define HW_GUARD_PERIOD_MAX_MS   1800000UL
#define HW_GUARD_BEFORE_MS       6000UL   // Fenster vor ...
#define HW_GUARD_AFTER_MS        6000UL   // ... und nach dem erwarteten Schub
#ifndef HW_GUARD_PROBE_EVERY
#if HW_LOOP_TEST
#define HW_GUARD_PROBE_EVERY     1000000  // Messbetrieb: keine Stichprobe (Welle soll nie ins Ergebnis)
#else
#define HW_GUARD_PROBE_EVERY     6        // jedes 6. Fenster ungeschuetzt (Stichprobe: Welle noch da?)
#endif
#endif

// Optionale externe LED an GPIO13 (ESP32-DevKitC 38-Pin Micro-USB, neben GND, mit Vorwiderstand gegen GND):
// leuchtet, solange gemint wird; kurz aus bei jedem Share. -1 = aus
// Ghost Pod: aus, die LEDs steuert ghost.cpp (GPIO13 = gruene LED im Deckel)
#if GHOST_POD
#define LED_PIN                  -1
#else
#define LED_PIN                  13
#endif

// BOOT-Taste 5 s halten = Einstellungen loeschen. Ghost Pod: AUS (Wattebausch auf BOOT beim Flashen)
#ifndef BOOT_RESET_ENABLE
#define BOOT_RESET_ENABLE        (GHOST_POD ? 0 : 1)
#endif

#if GHOST_POD
#include "ghost_config.h"
#endif
