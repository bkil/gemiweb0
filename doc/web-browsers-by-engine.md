# FOSS web browsers by engine

The question that we wanted to research when assembling this list is to enumerate potentially lightweight web browsers for old computers.
However, as the resource consumption of most browsers should somewhat correlate with the engine used, they are grouped by engine.
If a browser supports multiple engines, it is present under the heading of the supposedly lighter engine.

## Blink engine

### Chromium

* https://en.wikipedia.org/wiki/Chromium_(web_browser)

`apt install chromium-browser`

### Dooble

* https://en.wikipedia.org/wiki/Dooble
* QtWebEngine

### New Edge

* https://en.wikipedia.org/wiki/Microsoft_Edge#New_Edge_(2019%E2%80%93present)

### Falkon

* KDE: https://en.wikipedia.org/wiki/Falkon

`apt install falkon`

### SRWare Iron

* https://en.wikipedia.org/wiki/SRWare_Iron

## WebKit engine

### Konqueror

* https://en.wikipedia.org/wiki/Konqueror
* KDE
* Blink by default (QtWebEngine), but an extension for WebKit2 (QtWebKit) is available
* https://github.com/KDE/kwebkitpart

`apt install konqueror`

### Otter Browser

* https://en.wikipedia.org/wiki/Otter_Browser
* can choose between Blink (QtWebEngine) and WebKit (QtWebKit)

### GNOME Web

* https://en.wikipedia.org/wiki/GNOME_Web
* libwebkit2gtk

`apt install epiphany-browser`

### Surf

* https://en.wikipedia.org/wiki/Surf_(web_browser)
* unusual, keyboard control
* libwebkit2gtk

`apt install surf`

### Qutebrowser

* https://en.wikipedia.org/wiki/Qutebrowser
* radical, keyboard interface
* Blink by default (QtWebEngine), but a WebKit2 (libqt5webkit5) variant is also available (qutebrowser-qtwebkit)

`apt install qutebrowser`

### Nyxt

* https://github.com/atlas-engineer/nyxt/blob/master/documents/README.org
* Emacs, vi, CUA
* libwebkit2gtk
* beta: Blink engine

## KHTML engine

* https://github.com/KDE/khtml
* Konqueror also used this up to Ubuntu Focal and Debian Buster, but then switched

## Gecko engine

### Firefox

* https://en.wikipedia.org/wiki/Firefox

`apt install firefox`

### GNU IceCat

* https://en.wikipedia.org/wiki/GNU_IceCat

### SeaMonkey

* https://en.wikipedia.org/wiki/SeaMonkey

### Waterfox

* https://en.wikipedia.org/wiki/Waterfox

## Goanna engine

A fork of older Firefox/Gecko for security and to keep older extensions working.

### Conkeror

* https://en.wikipedia.org/wiki/Conkeror
* Radical, keyboard driven, not for the faint of heart. Needs to catch up with the code of Pale Moon updates.

### Basilisk

* https://en.wikipedia.org/wiki/Pale_Moon_(web_browser)#Basilisk_browser

### Pale Moon

* https://en.wikipedia.org/wiki/Pale_Moon_(web_browser)

## May become full featured

### NetSurf

* https://en.wikipedia.org/wiki/NetSurf
* independent and are working to support common web pages in iterations
* support for GTK and Linux Framebuffer

JavaScript support was implemented with SpiderMonkey in the past, and recently with DukTape:

* https://duktape.org/
* https://kangax.github.io/compat-table/es6/

### SerenityOS LibWeb

* https://en.wikipedia.org/wiki/SerenityOS
* https://github.com/SerenityOS/serenity/tree/master/Userland/Applications/Browser
* https://github.com/SerenityOS/serenity/tree/master/Userland/Libraries/LibWeb
* https://github.com/SerenityOS/serenity/tree/master/Ladybird
* https://awesomekling.github.io/Ladybird-a-new-cross-platform-browser-project/

### gngr

More of a tech demo than a product for end users, but it is a unique independent engine with theoretically good coverage of standards.

* https://github.com/gngrOrg/gngr
* https://en.wikipedia.org/wiki/Rhino_(JavaScript_engine)

> Based on The Lobo Project. jStyleParser: for parsing and analysing CSS, okhttp: support for cookies, SPDY.

### Web-K

More of a tech demo than a product for end users, but it is a unique independent engine with theoretically good coverage of standards.

* https://github.com/Earnix/Web-K
* https://en.wikipedia.org/wiki/Flying_Saucer_(library)
* https://en.wikipedia.org/wiki/Nashorn_(JavaScript_engine)
* https://github.com/flyingsaucerproject/flyingsaucer/blob/828de14f7991350d069ed858ba4ed7bf63490313/www/feature-list.html

> Web-K is FlyingSaucer-based pure Java browser and Swing browser component. Nashorn JavaScript runtime, Canvas, es6-shim polyfill. Modified JSoup library provides support of HTML5 at parsing level.

## Graphical browsers with compromises

### Dillo

* https://en.wikipedia.org/wiki/Dillo#Forks
* https://github.com/crossbowerbt/dillo-plus
* no JavaScript
* their domain name was squatted by a Wordpress clone
* CSS support to be improved
* no JavaScript

### Links2

* CSS support to be improved
* version 2.1pre28 was the last version that could interpret Netscape JavaScript 1.1
* http://links.twibright.com/download/ChangeLog

`links2 -g`

### HV3

* https://packages.debian.org/bullseye/hv3
* CSS (from around 2008)
* optionally JavaScript if compiled from source (ES3, from around 2009)

### edbrowse

* https://github.com/CMB/edbrowse
* text-based
* it formerly used DukTape JavaScript but recently migrated to QuickJS

`apt install edbrowse`

### NCSA-mosaic

* https://github.com/alandipert/ncsa-mosaic

## Unmaintained

### kweb

* https://github.com/ekapujiw2002/kweb

Hasn't been updated for a long time.

### Midori

* https://en.wikipedia.org/wiki/Midori_(web_browser)

`apt install midori`

## Related

* https://github.com/bkil/wiki/blob/master/en/widget-toolkit-html-rich-text.md

> HTML rich text support by desktop widget toolkits
