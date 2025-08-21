# Targeted platform configurations

## Overview

A platform configuration would be compromised of the OS, the web browser, interface (resolution, DPI, touch, mouse, keyboard) and device limitations (CPU, RAM).

Configurations can be tested inside a virtual machine or using browser matrix services. We can assume a high network speed to investigate that question separately.

Each content developer can pick which ones they specifically want to support. We might suggest that they also publish their choice on their page.

### Common problems

If we don't want to go into all nuance details of responsive design, the main pain points I observe:
* viewing on too small screen
* viewing on too wide screen
* if the visitor has greatly increased their font size and thus the effective pixel size became a fraction of the original or if it stops aligning with raster images
* if it is taking too long to load a huge page (or complex generated code) even over wifi
* if there's input lag during interactions
* the implementation relies on the behavior of a single rendering engine with regard to an obscure quirk or an optional experimental feature

## Example platforms

Hardware is assumed to be purchased a few years ago usually from a low budget. Each software is assumed to be the latest version except when noted otherwise.

### Microcontroller

* ESP32 or RP2040 (32-bit ARM Cortex-M0+), 256-512kB RAM, 2-4MB flash
* browser: gemiweb0

### Nokia 110 4G (2021)

* https://www.gsmarena.com/nokia_110_4g-10965.php
* Symbian S30+, 120x160, keypad, 128MB RAM
* browser: Opera mini 4 only
* https://techcabal.com/2025/04/16/opera-mini-mobile-browser/

### Nokia 3210 (2024)

* https://en.wikipedia.org/wiki/Nokia_3210_%282024%29
* Symbian S30+, 240x320, keypad, 64MB RAM
* browser: Opera mini 4 only

### Nokia 8000 4G

* https://www.gsmarena.com/nokia_8000_4g-10575.php
* KaiOS 2.5, 240x320, keypad, 512MB RAM
* browser: Gecko 48 only

### Nokia 2780 Flip

* https://en.wikipedia.org/wiki/Nokia_2760#Nokia_2780_Flip
* KaiOS 3.1, 240x320, keypad, 512MB RAM
* browser: Gecko 84 only

### Legacy Android

* Android 5, quad core, 540x960 touchscreen, 1GB RAM
* browser: only Mozilla Fennec not vulnerable
* https://f-droid.org/en/packages/org.mozilla.fennec_fdroid/

### Supported Android

* https://www.gsmarena.com/xiaomi_redmi_a5_4g-13737.php
* Android, octa-core, 720x1640 touchscreen, 3GB RAM
* browser: Mobile Chrome, no use in testing others

### Supported iPhone

* https://en.wikipedia.org/wiki/IPhone_SE_%282nd_generation%29
* Apple iOS, hexa-core A13, 750x1334 touchscreen, 3GB RAM
* browser: Mobile Safari, no use in testing others

### Hand386

* https://liliputing.com/hand-386-is-a-different-kind-of-gaming-handheld-qwerty-keyboard-and-ms-dos-compatible/
* FreeDOS, keyboard, mouse, 720x480x8, 8MB RAM
* browser: Arachne

### Cheap SBC or TV box from a few years ago

* Armbian, keyboard, mouse, quad core, 512MB-1GB RAM
* browsers: NetSurf, Ladybird, edbrowse, Chawan, Ferus, ELinks, Dillo
* just for fun: visurf, HV3, KolibriOS (on old PC), Emacs Eww, links2, lynx, netrik, w3m

### Laptop

* Xubuntu, keyboard, touchpad, 1366x768, 4GB RAM
* browsers: Chromium, Firefox, Tor browser (Firefox ESR), Epiphany (Gnome Web), gngr, LoboEvolution, Flying Saucer, Servoshell, Opera 12.18 (same as used by the server of Opera mini if you don't want to fiddle with an emulator online)

### Desktop

* Windows, keyboard, mouse, 1920x1080, 8GB RAM
* browsers: Microsoft Edge, Google Chrome

### Supported iPad

* https://en.wikipedia.org/wiki/IPad_Mini_%285th_generation%29
* iPadOS, hexa-core A12, 2048x1536, touchscreen, 3GB RAM
* browser: Mobile Safari, no use in testing others

### Supported MacBook Air

* https://en.wikipedia.org/wiki/MacBook_Air_%28Apple_silicon%29#Technical_specifications
* MacOS, 8-core M1, keyboard, touchpad, 2560x1600, touchscreen, 8-16GB RAM
* browser: Safari, no use in testing others
