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
* assuming that all mouse and touchpad are equipped with more than one button and a usable scroll wheel or strip
* assuming that a user has a pointing device at all or prefers to use it instead of the keyboard when interspersed with typing
* not realizing pointer acceleration: that a mouse or touchpad may not be able to cross a big enough screen with a single stroke or that holding the cursor still on top of a small target or through a narrow tunnel can be difficult
* test with and without loading multimedia, fonts, CSS
* test with and without loading JS (except for web apps)

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
* "sensibly purchased" is an estimate of the last date when it was still easy to acquire anew and no successor was available for a similar cost or less.

See also FOSS web browsers by engine:

[./web-browsers-by-engine.md](./web-browsers-by-engine.md)

### Microcontroller

* sensibly purchased: 2012-2025
* https://github.com/Allegra42/ZEReader
* custom RTOS, Arduino Due, ESP8266, ESP32 (32-bit LX7) or RP2040 (32-bit ARM Cortex-M0+), 256-512kB RAM, at least 320x240x1, up to 4 bit/pixel, 2-4MB flash, TLS may not be supported
* browser: gemiweb0

### Hand386

* sensibly purchased: 2023-2025
* https://news.ycombinator.com/item?id=36193196
* FreeDOS, keyboard, mouse, 720x480x8, 8MB RAM, TLS may not be supported
* browser: Arachne/DOS

### Legacy router

* sensibly purchased: 2004-2025
* OpenWrt, MIPS AR9331, 32MB RAM, 8MB flash, TLS may be optionally supported
* browser: gemiweb0 (scripted or for js0 CGI)

### Nokia 110 4G 2021

* sensibly purchased: 2021-2024
* https://www.gsmarena.com/nokia_110_4g-10965.php
* Symbian S30+, 120x160, keypad, 128MB RAM
* browser: Opera mini 4 only
* https://techcabal.com/2025/04/16/opera-mini-mobile-browser/

### Nokia 3210 2024

* sensibly purchased: 2024-2025
* https://en.wikipedia.org/wiki/Nokia_3210_%282024%29
* Symbian S30+, 240x320, keypad, 64MB RAM
* browser: Opera mini 4 only

### JioPhone

* sensibly purchased: 2017-2018
* https://phonedb.net/index.php?m=device&id=14880&c=reliance_jiophone_td-lte_in_f101k__f30c__f10q__f61f
* KaiOS 1.0, low power 2-core A7, 240x320, keypad, 512MB RAM, some of the TLS root CA may have expired
* browser: Gecko 37 only
* https://web.archive.org/web/20180507203733/http://www.bgr.in/news/jiophone-kaios-surpasses-ios-india-second-most-popular-mobile-operating-system-android-smartphones-feature-phones-jio-4g/

### Nokia 6300 4G

* sensibly purchased: 2021-2022
* https://www.gsmarena.com/nokia_6300_4g-10576.php
* KaiOS 2.5, low power 4-core A7, 240x320, keypad, 512MB RAM, some of the TLS root CA may have expired
* browser: Gecko 48 only

### Nokia 2780 Flip

* sensibly purchased: 2022-2023
* https://www.gsmarena.com/nokia_2780_flip-11973.php
* KaiOS 3.1, low power 4-core A53, 240x320, keypad, 512MB RAM
* browser: Gecko 84 only

### Legacy Android

* sensibly purchased: 2015-2017
* https://www.gsmarena.com/zte_maven-7355.php
* Android 5.0, low power 4-core A53, 480x854 touchscreen, 1GB RAM
* browser: only Fennec F-droid not vulnerable

### Earliest supported Android

* sensibly purchased: 2023-2024
* https://www.gsmarena.com/tcl_502-13943.php
* Android 13 Go, fast 4-core A53, 480x960 touchscreen, 2GB RAM
* browser: Mobile Chrome, no use in testing others

### Recent supported Android

* sensibly purchased: 2025
* https://www.gsmarena.com/xiaomi_redmi_a5_4g-13737.php
* Android 15 Go, 8-core A75 & A55, 720x1640 touchscreen, 3GB RAM
* browser: Mobile Chrome, no use in testing others

### Supported iPhone

* sensibly purchased: 2020-2022
* https://en.wikipedia.org/wiki/IPhone_SE_%282nd_generation%29
* Apple iOS, 6-core A13, 750x1334 touchscreen, 3GB RAM
* browser: Mobile Safari, no use in testing others

### Legacy SBC or TV box

* sensibly purchased: 2021-2025
* representative chipset: x86 (VIA Eden X4, Intel Atom CE5300) or A53 (Raspberry Pi Zero 2 W, S805X Xiaomi Mi TV Stick)
* antiX or Armbian, keyboard, mouse, 1366x768, 512MB-1GB RAM
* browsers: NetSurf, Ladybird, edbrowse, Chawan, Ferus, ELinks, Dillo
* just for fun: visurf, KolibriOS (on x86), Emacs Eww, links2, lynx, netrik, w3m
* retro: Amaya, Arena, BrowseX, Emacs w3, HV3+SEE, Konqueror (KDE 2.0), Mozilla 1.0, Mycel, NCSA-Mosaic, Netscape 2.0, Netscape 3.0, Netscape 4.5, Opera 4.0, Opera 8.5. TLS may not be supported or TLS root CA may have expired in case of firmware.
* needs porting or a VM: Arachne/Linux (svgalib), AWeb, Charon, Voyager

### Laptop

* sensibly purchased: 2018-2020
* Xubuntu, 2(4)-core AMD Ryzen 3 2200U or Intel i3-8145U, keyboard, touchpad, 1600x900, 4GB RAM
* browsers: Chromium, Firefox, Tor browser (Firefox ESR), Epiphany (Gnome Web), gngr, LoboEvolution, Flying Saucer, Servoshell, Pale Moon, Basilisk, Opera 12.18 (same as used by the server of Opera mini if you don't want to fiddle with an emulator online)
* retro: Konqueror v5 (KHTML), Web-K

### Desktop

* sensibly purchased: 2018-2020
* Windows, 4-core AMD Ryzen 3 2200G or Intel i3-8100, keyboard, mouse, 1920x1080, 8GB RAM
* browsers: Microsoft Edge, Google Chrome, Opera

### Supported iPad

* sensibly purchased: 2019-2021
* https://en.wikipedia.org/wiki/IPad_Mini_%285th_generation%29
* iPadOS, 6-core A12, 2048x1536, touchscreen, 3GB RAM
* browser: Mobile Safari, no use in testing others

### Supported MacBook Air

* sensibly purchased: 2020-2024
* https://en.wikipedia.org/wiki/MacBook_Air_%28Apple_silicon%29#Technical_specifications
* MacOS, 8-core M1, keyboard, touchpad, 2560x1600, touchscreen, 8-16GB RAM
* browser: Safari, no use in testing others
