# Targeted platform configurations

A platform configuration would be compromised of the OS, the web browser, interface (resolution, DPI, touch, mouse, keyboard) and device limitations (CPU, RAM). Each content producer can pick which ones they specifically want to support. We might suggest that they also publish their choices on their web site.

## Overview

Configurations can be tested inside a virtual machine or using online browser matrix services. We can assume a high network speed to investigate that question separately.

### Web developer mistakes

If we don't want to go into all nuance details of responsive design, the main pain points I observe:
* viewing on too small screen
* viewing on too wide screen
* if the visitor has greatly increased their font size and thus the effective pixel size became a fraction of the original or if it stops aligning with raster images
* not planning to break long words
* not planning to wrap preformatted blocks
* not allocating sufficient space for alt text
* forcing fixed padding
* nesting one or more scrollable panes inside the already scrollable viewport
* if it is taking too long to load a huge page (or complex generated code) even over wifi
* if there's input lag during interactions
* the implementation relies on the behavior of a single rendering engine with regard to an obscure quirk or an optional experimental feature

### Emulation

* A developer need not possess all pieces of hardware on this list to ensure their app is working smoothly on a configuration from the same ball park. Calibrating some constants based on benchmark results might be needed.
* Some web browsers have a single click toggle to check rendering on small screen mobiles.
* You can adjust the cycle speed in DosBox directly.
* You can test on x86 and without GPU acceleration on a virtual machine, reduce the CPU core count, RAM and resolutions available.
* You can run an Android emulator on a PC with the same adjustments.
* You can slow down the CPU by either disabling turbo boost and locking the multiplier to its lowest value via sysfs, or by keeping the virtual machine process paused on a schedule:

```
while true; do
 killall -STOP VirtualBox
 sleep 0.1
 killall -CONT VirtualBox
 sleep 0.02
done
```

## Example platform configurations

* Hardware is assumed to be purchased a few years ago usually from a low budget and most of these would still be expected to be on sale.
* Each software is assumed to be the latest version except where noted otherwise.
* Each screen is assumed to support at least 15-bit/pixel RGB high or true color unless otherwise noted.

See also FOSS web browsers by engine:

[./web-browsers-by-engine.md](./web-browsers-by-engine.md)

### Microcontroller

* https://github.com/Allegra42/ZEReader
* custom RTOS, ESP32 or RP2040 (32-bit ARM Cortex-M0+), 256-512kB RAM, at least 320x240x1, up to 4 bit/pixel, 2-4MB flash
* browser: gemiweb0

### Hand386

* https://liliputing.com/hand-386-is-a-different-kind-of-gaming-handheld-qwerty-keyboard-and-ms-dos-compatible/
* FreeDOS, keyboard, mouse, 720x480x8, 8MB RAM
* browser: Arachne/DOS

### Legacy router

* OpenWrt, MIPS AR9331, 32MB RAM, 8MB flash
* browser: gemiweb0 (scripted or for js0 CGI)

### Nokia 110 4G 2021

* https://www.gsmarena.com/nokia_110_4g-10965.php
* Symbian S30+, 120x160, keypad, 128MB RAM
* browser: Opera mini 4 only
* https://techcabal.com/2025/04/16/opera-mini-mobile-browser/

### Nokia 3210 2024

* https://en.wikipedia.org/wiki/Nokia_3210_%282024%29
* Symbian S30+, 240x320, keypad, 64MB RAM
* browser: Opera mini 4 only

### Nokia 6300 4G

* https://www.gsmarena.com/nokia_6300_4g-10576.php
* KaiOS 2.5, low power 4-core A7, 240x320, keypad, 512MB RAM
* browser: Gecko 48 only

### Nokia 2780 Flip

* https://www.gsmarena.com/nokia_2780_flip-11973.php
* KaiOS 3.1, low power 4-core A53, 240x320, keypad, 512MB RAM
* browser: Gecko 84 only

### Legacy Android

* Android 5.0, low power 4-core A53, 540x960 touchscreen, 1GB RAM
* browser: only Fennec F-droid not vulnerable

### Supported Android

* https://www.gsmarena.com/xiaomi_redmi_a5_4g-13737.php
* Android, 8-core A75 & A55, 720x1640 touchscreen, 3GB RAM
* browser: Mobile Chrome, no use in testing others

### Supported iPhone

* https://en.wikipedia.org/wiki/IPhone_SE_%282nd_generation%29
* Apple iOS, 6-core A13, 750x1334 touchscreen, 3GB RAM
* browser: Mobile Safari, no use in testing others

### Legacy SBC or TV box

* representative chipset: x86 (VIA Eden X4, Intel Atom CE5300) or A53 (Raspberry Pi Zero 2 W, S805X Xiaomi Mi TV Stick)
* antiX or Armbian, keyboard, mouse, 1366x768, 512MB-1GB RAM
* browsers: NetSurf, Ladybird, edbrowse, Chawan, Ferus, ELinks, Dillo
* just for fun: visurf, KolibriOS (on x86), Emacs Eww, links2, lynx, netrik, w3m
* retro: Amaya, Arena, BrowseX, Emacs w3, HV3+SEE, Konqueror 1, Mozilla 1.0, Mycel, NCSA-Mosaic, Netscape 2.0, Netscape 3.0, Netscape 4.5, Opera 4.0, Opera 8.5
* needs porting or a VM: Arachne/Linux (svgalib), AWeb, Charon, Voyager

### Laptop

* Xubuntu, 2(4)-core Intel i3-8145U, keyboard, touchpad, 1600x900, 4GB RAM
* browsers: Chromium, Firefox, Tor browser (Firefox ESR), Epiphany (Gnome Web), gngr, LoboEvolution, Flying Saucer, Servoshell, Pale Moon, Basilisk, Opera 12.18 (same as used by the server of Opera mini if you don't want to fiddle with an emulator online)
* retro: Konqueror 5 (KHTML), Web-K

### Desktop

* Windows, 4-core AMD Ryzen 3 2200G, keyboard, mouse, 1920x1080, 8GB RAM
* browsers: Microsoft Edge, Google Chrome, Opera

### Supported iPad

* https://en.wikipedia.org/wiki/IPad_Mini_%285th_generation%29
* iPadOS, 6-core A12, 2048x1536, touchscreen, 3GB RAM
* browser: Mobile Safari, no use in testing others

### Supported MacBook Air

* https://en.wikipedia.org/wiki/MacBook_Air_%28Apple_silicon%29#Technical_specifications
* MacOS, 8-core M1, keyboard, touchpad, 2560x1600, touchscreen, 8-16GB RAM
* browser: Safari, no use in testing others
