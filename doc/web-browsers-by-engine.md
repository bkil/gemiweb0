# FOSS web browsers by engine

We've originally tried to enumerate lightweight web browsers for outdated computers. They are grouped by engine as resource consumption usually correlates well. One supporting multiple engines is listed under the lightest engine.

## Blink engine

### AgregoreWeb

* https://github.com/AgregoreWeb/agregore-browser
* interface: Electron BrowserWindow and BrowserView
* implemented in: interface in JavaScript, Electron and Blink in C++
* license: interface is AGPL-3.0, Electron is MIT, Blink is BSD-3
* protocols: HTTP, HTTPS, Hypercore, Dat, Gemini, IPFS, BitTorrent, magnet, SSB

### Chromium

* https://en.wikipedia.org/wiki/Chromium_(web_browser)

```
apt install chromium-browser
```

### Dooble

* https://en.wikipedia.org/wiki/Dooble
* QtWebEngine

### Falkon

* https://en.wikipedia.org/wiki/Falkon
* QtWebEngine

```
apt install falkon
```

### morph-browser

* https://gitlab.com/ubports/development/core/morph-browser
* interface: Qt, Lomiri (Ubuntu Touch)
* implemented in: QML, C++
* rendering engine: QtWebEngine
* license: GNU GPLv3

```
apt install morph-browser
```

### New Edge

* https://en.wikipedia.org/wiki/Microsoft_Edge#New_Edge_(2019%E2%80%93present)

### privacybrowser

* https://packages.debian.org/sid/privacybrowser
* https://gitweb.stoutner.com/?p=PrivacyBrowserPC.git;a=tree
* rendering engine: QtWebEngine
* implemented in: C++
* license: GPLv3+

```
apt install privacybrowser
```

### SRWare Iron

* https://en.wikipedia.org/wiki/SRWare_Iron

## WebKit engine

### GNOME Web

* https://en.wikipedia.org/wiki/GNOME_Web
* libwebkit2gtk

```
apt install epiphany-browser
```

### Konqueror

* https://en.wikipedia.org/wiki/Konqueror
* KDE
* Blink by default (QtWebEngine), but an extension for WebKit2 (QtWebKit) is available
* https://github.com/KDE/kwebkitpart

```
apt install konqueror
```

### Luakit

* https://github.com/luakit/luakit
* https://github.com/luakit/luakit-plugins
* rendering engine: libwebkit2gtk
* interface: GTK 3+
* implemented in: C
* plugins: Lua 5.1

```
apt install luakit
```

### Nyxt

* https://github.com/atlas-engineer/nyxt/blob/master/documents/README.org
* Emacs, vi, CUA
* libwebkit2gtk
* beta: Blink engine

### Oku

* https://github.com/OkuBrowser/oku
* rendering engine: webkit2gtk
* implemented in: Rust (and C++)
* platform: Linux
* license: AGPL v3

> Oku lets you create replicas, virtual drives that you can share online. A read-only ticket can be used to view, but not edit, your replica. Is this ready to be my default browser? No. Oku is still actively in development.

### Otter Browser

* https://en.wikipedia.org/wiki/Otter_Browser
* can choose between Blink (QtWebEngine) and WebKit (QtWebKit)

### Qutebrowser

* https://en.wikipedia.org/wiki/Qutebrowser
* radical, keyboard interface
* Blink by default (QtWebEngine), but a WebKit2 (libqt5webkit5) variant is also available (qutebrowser-qtwebkit)

```
apt install qutebrowser
```

### sugar-browse-activity

* https://github.com/sugarlabs/browse-activity
* https://github.com/godiard/help-activity/blob/master/source/browse.rst
* interface: GTK+ 3, GIR, Sugar Learning Platform
* rendering engine: libwebkit2gtk, gir1.2-webkit2, libsoup
* implemented in: Python3
* license: GNU GPL v2

```
apt install sugar-browse-activity
```

### Surf

* https://en.wikipedia.org/wiki/Surf_(web_browser)
* unusual, keyboard control
* libwebkit2gtk

```
apt install surf
```

### vimb

* https://github.com/fanglingsu/vimb
* rendering engine: webkit2gtk
* interface: GTK+ 3
* implemented in: C

## KHTML engine

* https://github.com/KDE/khtml/tree/0c0f313659504be0fcd2feec92fd7a7a425379fb
* Konqueror also used this up to Ubuntu Focal and Debian Buster, but then switched

## Gecko engine

### Firefox

* https://en.wikipedia.org/wiki/Firefox

```
apt install firefox
apt install firefox-esr
```

### GNU IceCat

* https://en.wikipedia.org/wiki/GNU_IceCat

### SeaMonkey

* https://en.wikipedia.org/wiki/SeaMonkey

### Waterfox

* https://en.wikipedia.org/wiki/Waterfox

## Goanna engine

A fork of older Firefox/Gecko for security and to keep older extensions working.

### Basilisk

* https://en.wikipedia.org/wiki/Pale_Moon_(web_browser)#Basilisk_browser

### Conkeror

* https://en.wikipedia.org/wiki/Conkeror
* Radical, keyboard driven, not for the faint of heart. Needs to catch up with the code of Pale Moon updates.

### Pale Moon

* https://en.wikipedia.org/wiki/Pale_Moon_(web_browser)

## May become full featured

### gngr

More of a tech demo than a product for end users, but it is a unique independent engine with theoretically good coverage of standards.

* https://github.com/gngrOrg/gngr
* https://en.wikipedia.org/wiki/Rhino_(JavaScript_engine)

> Based on The Lobo Project. jStyleParser: for parsing and analysing CSS, okhttp: support for cookies, SPDY.

### Ladybird

### SerenityOS LibWeb

It first started as the document rendering component LibWeb built into SerenityOS in 2019:

* https://en.wikipedia.org/wiki/SerenityOS
* https://github.com/SerenityOS/serenity/tree/master/Userland/Applications/Browser
* https://github.com/SerenityOS/serenity/tree/master/Userland/Libraries/LibWeb
* https://github.com/SerenityOS/serenity/tree/master/Ladybird
* https://awesomekling.github.io/Ladybird-a-new-cross-platform-browser-project/
* https://awesomekling.github.io/Memory-safety-for-SerenityOS/
* language: C++
* JavaScript is supported by its own interpreter (LibJS)

It was then split to create a separate cross-platform browser:

* https://awesomekling.substack.com/p/forking-ladybird-and-stepping-down-serenityos
* https://github.com/LadybirdBrowser/ladybird

It received $1M funding on 2024-07-01 to help release a public beta by 2026.

* https://ladybird.org/announcement.html
* https://ladybird.org/why-ladybird.html

### LoboEvolution

* https://github.com/LoboEvolution/LoboEvolution
* https://github.com/LoboEvolution/CobraEvolution
* rendering engine: CobraEvolution
* fork of LoboBrowser
* features: CSS, Rhino JavaScript
* languages: English, French
* implemented in: Java
* license: MIT

### NetSurf

* https://en.wikipedia.org/wiki/NetSurf
* rendering engine: Hubbub (independent and are working to support common web pages in iterations)
* interface: support for GTK and Linux Framebuffer
* features: HTML5, simple CSS (LibCSS), JavaScript support was implemented with SpiderMonkey in the past, and recently with DukTape.
* platform: RISC OS, Linux, Haiku (BeOS), AmigaOS, Windows, Atari
* implemented in: C

### visurf

* https://git.sr.ht/~sircmpwn/visurf
* fork of NetSurf to add frontend user interface with vi key bindings

### Web-K

More of a tech demo than a product for end users, but it is a unique independent engine with theoretically good coverage of standards.

* https://github.com/Earnix/Web-K
* https://en.wikipedia.org/wiki/Flying_Saucer_(library)
* https://en.wikipedia.org/wiki/Nashorn_(JavaScript_engine)
* https://github.com/flyingsaucerproject/flyingsaucer/blob/828de14f7991350d069ed858ba4ed7bf63490313/www/feature-list.html

> Web-K is FlyingSaucer-based pure Java browser and Swing browser component. Nashorn JavaScript runtime, Canvas, es6-shim polyfill. Modified JSoup library provides support of HTML5 at parsing level.

## Graphical browsers with compromises

### Arachne

* https://en.wikipedia.org/wiki/Arachne_(web_browser)
* https://www.glennmcc.org/
* language: C
* features: tables, frames, animated GIF, subset of HTML 4.0, CSS 1.0 (color, background-color, font-size, font-style:italic, font-weight:bold, text-decoration:underline), supports an extensive plugin system
* supported HTML tags: a (href, name), area, b (=em, strong), base (href), basefont (size, color, 3d, outline), bgsound (src, filename), big, blocquote, body (background, bgcolor, text, link, vlink, marginwidth, marginheight, mail, noresize, bgproperties), br (clear), button (uri, usr, url, to, subject, value, size, type, checked, active, name), caption (align, valign, nowrap, colspan, rowspan, bgcolor, background, height, width), center, code (=kbd), dd, div (align), embed (src, filename), font (size, color, 3d, outline), form (method, action), frame (src, name, framespacing, frameborder, border, scrolling, marginwidth, marginheight), frameset (frameborder, border, rows, cols), h1, h2, h3, h4, h5, h6, head, hr (size, noshade, align, width), i (=cite, address), iframe (src, name, framespacing, frameborder, border, scrolling, marginwidth, marginheight), img (src, align, ismap, usemap, border, height, width, alt, name), input (uri, usr, url, to, subject, value, size, type, checked, active, name), li (=dt), link (rel, href), map (name), meta (http-equiv, content), nobr, noframes, noscript, ol (=menu, dl, dir), option (selected, value), p (align), pre, s (=strike, del), script (?), select (size, name, multiple), small, style, sub, sup, table (border, frame, cellspacing, cellpadding, width, align, bgcolor, background), td (align, valign, nowrap, colspan, rowspan, bgcolor, background, height, width), textarea (rows, cols, name, wrap, active), th (align, valign, nowrap, colspan, rowspan, bgcolor, background, height, width), title, tr, tt, u (=ins), ul
* contains a web browser, email client and modem dialer
* DOS, Linux & SVGAlib
* no JavaScript

### Dillo

* https://en.wikipedia.org/wiki/Dillo#Forks
* https://github.com/crossbowerbt/dillo-plus
* https://github.com/dillo-browser/dillo
* https://github.com/dillo-browser/dillo-browser.github.io
* https://web.archive.org/web/20220518060405/https://www.dillo.org/
* no JavaScript
* their domain name was squatted by a Wordpress clone
* CSS support to be improved
* implemented in: C (parts in C++)

### HV3

* https://packages.debian.org/bullseye/hv3
* CSS (from around 2008)
* optionally JavaScript if compiled from source (ES3, from around 2009)
* interface: Tk
* rendering engine: Tkhtml
* implemented in: Tcl

### KolibriOS WebView

* https://github.com/KolibriOS/kolibrios/tree/main/programs/cmm/browser
* https://github.com/KolibriOS/kolibrios/tree/main/programs/develop/libraries/box_lib/trunk
* https://github.com/KolibriOS/kolibrios/blob/main/programs/develop/libraries/http/http.asm
* https://github.com/KolibriOS/kolibrios/tree/main/programs/develop/libraries/iconv
* https://github.com/KolibriOS/kolibrios/tree/main/programs/develop/libraries/proc_lib/trunk
* supported HTML tags: a (href), p, img (src, title, alt), div, ol, ul, dt, dl, dd, li, hr (color), code, meta (charset, content, encoding, http-equiv refresh, name application), body (bgcolor, link, alink, text), iframe (src - just as a link), table (width), tr, th (width), td (width), caption, b (=big, strong), u (=ins), s (=strike, del), q, h1, h2, h3, h4, font (color, bg), pre, blockquote, button, img, nav, br (=header, article, footer, figure), title
* supported attributes: name, id
* features: HTML 4.0, character sets, up to 255 byte long anchor, control via mouse, CDATA comment, ignore content within script, style, binary and select
* language: C--, assembly
* no JavaScript
* only supports HTTPS through a custom hosted HTTP downgrade proxy
* platform: KolibriOS

## Text-only

## Terminal

### edbrowse

* https://github.com/CMB/edbrowse
* https://github.com/CMB/edbrowse/blob/master/src/html-tags.c
* https://web.archive.org/web/20101027132444/http://eklhad.net/edbrowse/edbrowse-2.2.10.zip
* https://web.archive.org/web/20101027130615/http://eklhad.net/edbrowse/edbrowse.pl
* text-only
* features: tables, forms, some CSS, some JavaScript with a subset of DOM level 1
* v2 up to 2.2.10 used a custom JavaScript engine, 3.1.1 used SpiderMonkey, 3.7.0 used DukTape, 3.8.0 uses QuickJS up to now
* protocol: http, https, gopher, ftp, sftp, smtp, pop3, pop3s, imap, imaps
* implemented in: C

```
apt install edbrowse
```

### ELinks

* https://en.wikipedia.org/wiki/ELinks
* https://github.com/rkd77/elinks
* text-based
* interface can be scripted via guile, Lua, Perl, Python, Ruby or SpiderMonkey
* features: mouse, utf-8, idn, brotli, zstd, text color, tables, frames, inline images using Sixel, some CSS, some JS with a subset of DOM level 1
* content JavaScript engine can be configured at compilation: SpiderMonkey, QuickJS or MuJS (formerly: NJS)
* protocol: http, https, gopher, gemini, ftp, sftp, nntp, smb, bittorrent, fsp
* implemented in: C

### Emacs Eww

* https://en.wikipedia.org/wiki/Eww_(web_browser)
* https://www.gnu.org/software/emacs/manual/html_mono/eww.html
* https://www.emacswiki.org/emacs/eww
* https://git.savannah.gnu.org/cgit/emacs.git/tree/lisp/net/eww.el
* interface: text-based, embedded within Emacs
* features: cookies, utf-8, text color, bookmarks, TLS, can show images inline
* no CSS, no JS
* implemented in: Emacs LISP

### Links2

* CSS support to be improved
* version 2.1pre28 was the last version that could interpret Netscape JavaScript 1.1
* http://links.twibright.com/download/ChangeLog
* can run either a text-only version from the terminal or display images inline and antialiased fonts if running on X11 or DirectFB
* implemented in: C

```
apt install links2
links2 -g
```

### lynx

* https://en.wikipedia.org/wiki/Lynx_(web_browser)
* https://github.com/ThomasDickey/lynx-snapshots
* https://lynx.invisible-island.net/
* interface: text-only
* features: table without layout, cookies, forms, lists, quotes
* protocols: HTTP, HTTPS, FTP, NNTP, gopher, finger, wais, telnet, tn3270, rlogin, file
* implemented in: C
* license: GNU GPL v2

```
apt install lynx
```

### netrik

* https://salsa.debian.org/debian/netrik
* interface: text-only
* text color, bold, italic, forms, table placeholder markers without layout
* UTF-8 rendering glitches, no CSS, no JS, no TLS, no cookies
* implemented in: C
* license: GNU GPL v2 or later

```
apt install netrik
```

### w3m

* https://en.wikipedia.org/wiki/W3m
* https://salsa.debian.org/debian/w3m/-/tree/master
* interface: text-based
* features: mouse, cookies, forms, FTP, dl, dt, frameset, table, no CSS, no JS
* can show images inline with sixel (Bobcat, Contour, ctx terminal, Darktile, DomTerm, Eat, foot, iTerm2, konsole, LaTerminal, MacTerm, mintty, mlterm, Rlogin, sixel-tmux, SwiftTerm, SyncTERM, tmux, toyterm, U++, Visual Studio Code, wezterm, xfce-terminal, xterm, xterm.js, yaft, Yakuake, Zellij, Hyper, Theia), osc5379, iTerm2, kitty (WezTerm, Konsole, wayst)
* can open images with a viewer for X11, DirectFB and Windows
* implemented in: C
* license: MIT

```
apt install w3m
```

## Experimental

### Chawan

* https://sr.ht/~bptato/chawan/
* https://codeberg.org/bptato/chawan
* text-based
* features: CSS with layout (flow, table, flexbox, colors), UTF-8, forms, cookies, mouse, bookmarks, history, inline images (Sixel, Kitty)
* protocols: HTTP, HTTPS, FTP, SFTP, Gopher, Gemini, Finger, Spartan
* QuickJS-ng JavaScript for link navigation, basic DOM manipulation and network requests
* platforms: Unix-like (Linux, FreeBSD, OpenBSD, Haiku, Mac OS, WSL)
* implemented in: Nim
* license: public domain

### Cocktail

* https://github.com/silexlabs/Cocktail
* no JavaScript, basic CSS

> With Cocktail, write HTML/CSS applications in Haxe and build them for OpenFL and flash/Air. As Cocktail uses the standard DOM API
> NME (another Haxe library)

### Cog

* https://github.com/Igalia/cog
* https://packages.debian.org/trixie/cog
* rendering engine: WPE WebKit

> It provides no user interface and is suitable to be used as a web application container for embedded devices in kiosk mode.

### HighWire

* last update: mostly implemented in 2010, but many recent commits
* https://github.com/freemint/highwire
* uses: HTMLtidy
* features: HTML 3.2, images (gif, jpg, png), tables, hyperlinks, sound, file selector, Gemscript, HTTP, forms
* partially working: HTML 4.0, frameset, PDF, Unicode characters up to U+FFFD, no CSS, no JavaScript
* platform: Atari (MiNT, MagiC)
* implemented in: C
* license: Zlib

### kosmonaut

* https://github.com/twilco/kosmonaut

> Kosmonaut is built with Rust using OpenGL bindings via gl-rs, Glutin for window management and OpenGL context creation, Servo's html5ever and cssparser for HTML and CSS parsing, and various other auxiliary libraries.
> Only a very limited subset of CSS is currently supported, so most web pages will not work.

### kristall

* https://github.com/MasterQ32/kristall
* https://github.com/MasterQ32/kristall/blob/master/src/renderers/htmlrenderer.cpp
* implemented in: C++

> Graphical small-internet client for windows, linux, MacOS X and BSDs. Supports gemini, http, https, gopher, finger.
> text/gemini, text/html (reduced feature set), text/markdown
> Qt5

### mbrowser

* https://github.com/MQuy/mbrowser
* DOM, partial CSS
* Rust
* uses various external dependencies for its components: cssparser, html5ever

> mBrowser is a toy browser developed from scratch for learning purpose.

### moon

* https://github.com/ZeroX-DG/moon
* GTK GUI

> This is a web browser developed from scratch using Rust. To fit with the "make from scratch" spirit, the development of the browser avoids the use of external libraries as much as possible.

### naglfar

* https://github.com/maekawatoshiki/naglfar
* gtk-rs

> A toy web browser implemented in Rust from scratch

### Odyssey Web Browser

* former name: Origyn Web Browser
* https://en.wikipedia.org/wiki/Origyn_Web_Browser
* https://github.com/deadwood2/OdysseyWebBrowser
* rendering engine: WebKit (libwebkitgtk?), Cairo
* features: HTML5 video and audio, CSS 2.1, some CSS3, SVG, MathML, JavaScript, DOM
* implemented in C++
* platform: Amiga, GTK, Qt, SDL
* license: BSD3

### QEmacs html-mode

* https://bellard.org/qemacs/qe-doc.html#SEC32
* https://github.com/qemacs/qemacs/tree/master/libqhtml
* interface: text-only
* implemented in: C
* features: a WYSIWYG HTML editor, some CSS2 with layout, tables
* limitations: no JavaScript, no images, no external resources, no frames
* license: MIT

> WYSIWYG HTML/XML/CSS2 mode graphical editing. Also supports lynx like rendering on VT100 terminals. Quite complete CSS2 support (including generated content and counters). Full Bidirectionnal Unicode support. Table support with both 'fixed' and 'auto' layout algorithms.

### Satori

* https://github.com/vercel/satori/
* https://github.com/facebook/yoga
* rendering engine: Yoga
* implemented in: TypeScript
* platform: browser, Web Worker, Node.js
* not a web browser, only a rendering engine producing SVG
* dependencies: opentype.js, css-background-parser, css-box-shadow, css-gradient-parser, css-to-react-native, emoji-regex, escape-html, linebreak, parse-css-color, postcss-value-parser, yoga-wasm-web

### Servoshell

* https://github.com/servo/servo/tree/main/ports/servoshell
* https://servo.org/download/
* https://servo.org/blog/2024/09/11/building-browser/
* rendering engine: Servo
* interface: egui
* implemented in: Rust
* platform: Linux, MacOS, Windows, Android, OpenHarmony
* license: MPL-2.0

> Complex sites such as Gmail and Google Chat are now usable in Servo, with some caveats

### Simple-San-Simon-Functional-Web-Browser

* https://github.com/carliros/Simple-San-Simon-Functional-Web-Browser
* https://hsbrowser.wordpress.com/
* implemented in: Haskell
* uu-parsinglib, url, tagsoup, gd-haskell, curl-haskell, wxHaskell

> support for a small sub-set of HTML, XHTML and XML grammar
> small sub-set of CSS. We implemented 48 CSS properties that let us modify Box features, apply styles to texts, use list and generate content.

### thdwb

* https://github.com/danfragoso/thdwb
* DOM, CSS, OpenGL, cache

> This is the hotdog web browser project. It's a web browser with its own layout and rendering engine, parsers, and UI toolkit!
> It's made from scratch entirely in golang. External dependencies are only OpenGL and GLFW, even go dependencies are kept to a minimum.

### WebWhir

* https://github.com/reesmichael1/WebWhir
* implemented in: C++

> WebWhir uses Boost sparingly and SFML for graphics.
> designed to be very easy to link into any application
> HTML tokenizer only handles the few of these that were necessary to parse simple and well-formatted strings

### wowser

* https://github.com/quittle/wowser
* glfw

> An (un)impressive browser being written from scratch in Rust

## Planned

Projects listed here have not produced a browser a user could test yet or are only components that others may build a web browser from in the future.

### CSSBox

* https://github.com/philborlin/CSSBox
* Java

> The input of the rendering engine is the document DOM tree and a set of style sheets referenced from the document. The output is an object-oriented model of the page layout. This model can be directly displayed but mainly, it is suitable for further processing by the layout analysis algorithms as for example the page segmentation or information extraction algorithms.
> The core CSSBox library may be also used for obtaining a bitmap or vector (SVG) image of the rendered document. Using the SwingBox package, CSSBox may be used as an interactive web browser component in a Java Swing application.
> CSSBox relies on the jStyleParser open source CSS parser
> the NekoHTML parser is used for creating the DOM tree. As an alternative, the The Validator.nu HTML Parser has been tested with CSSBox too.
> The Xerces library may be replaced by any other DOM implementation.

### Ferus

* https://github.com/ferus-web/ferus
* dependencies: HTML5/DOM parser of Chawan, Stylus CSS3 parser, Bali JavaScript engine, ferusgfx rendering pipeline, sanchar URL utilities, ferrite for decoding UTF-16 and UTF-8
* implemented in: Nim

### gemiweb0

* The main scope is producing only documentation, specification and conformance tests. Developers are expected to implement it on their own.
* A proof of concept web browser, web server and bot user agent will be provided later in multiple languages, both low level and high level.

### gosub-browser

* https://github.com/jaytaph/gosub-browser

> GoSub: Gateway to Optimized Searching and Unlimited Browsing
> A feeble attempt on writing a browser and learning rust.
> Note: code in the main branch is currently not stable and might not even compile.
> In the future, this component (html5 parser) will receive through an API a stream of bytes and will output a stream of events. The events will be consumed by the next component and so on, until we can display something in a window/user agent. This could very well be a text-mode browser, but the idea is to have a graphical browser.

### Haphaestus

* https://haphaestus.org/
* https://argonaut-constellation.org/
* implemented in: Haskell

### Lexbor

* https://github.com/lexbor/lexbor
* https://github.com/lexbor/docs/blob/main/site/src/articles/html.md
* https://github.com/lexborisov/Modest
* language: C
* finished: HTML parser, CSS parser, character encoding
* deprecated implementation: fonts

### LibreOffice Writer Web

* https://github.com/LibreOffice/core/tree/master/sw/source/filter/html
* https://books.libreoffice.org/en/GS248/GS24810-FileFormatsSecurityExporting.html#bkmRefHeadingToc55582630270332
* https://books.libreoffice.org/en/GS73/GS7312-CreatingHTMLFiles.html#toc20
* interface: not a browser
* features: layout and rendering present in another subsystem, only parser and formatter for HTML and CSS
* schemes: file
* license: GPLv3
* implemented in: C++

### litehtml

* https://github.com/litehtml/litehtml
* https://github.com/google/gumbo-parser

> litehtml is the lightweight HTML rendering engine with CSS2/CSS3 support. Note that litehtml itself does not draw any text, pictures
> litehtml just parses HTML/CSS and places the HTML elements into the correct positions (renders HTML). To draw the HTML elements you have to implement the simple callback interface document_container.
> litehtml uses the gumbo-parser to parse HTML

### LURE

* https://github.com/smizdev/LURE

> LURE does not intend to implement a fully standards compliant web browser.
> LURE is currently under development and cannot yet produce rendered content. Much of the DOM and associated subsystems are still under heavy design and development

### Robinson

* https://github.com/mbrubeck/robinson
* https://limpet.net/mbrubeck/2014/08/08/toy-layout-engine-1.html
* Rust
* small subset of HTML and CSS, basic block layout
* no GUI or interaction yet, can only render to PNG or PDF

### SumatraPDF Reader

* https://github.com/sumatrapdfreader/sumatrapdf/blob/master/src/HtmlFormatter.cpp
* https://github.com/sumatrapdfreader/sumatrapdf/blob/master/src/utils/HtmlPullParser.cpp
* https://github.com/sumatrapdfreader/sumatrapdf/blob/master/do/scripts/gen_htmlparserlookup.py
* interface: not a browser
* features: contains a parser and renderer for HTML
* implemented in: C, C++, Python
* schemes: file
* license: GPLv3
* platform: Windows

### Verso

* https://github.com/versotile-org/verso
* rendering engine: Servo
* interface: glutin, widgets rendered with Servo
* implemented in: Rust
* platform: Windows, Mac OS, Flatpak, NixOS
* license: Apache-2.0, MIT

### WeasyPrint

* https://github.com/Kozea/WeasyPrint

> visual rendering engine for HTML and CSS that can export to PDF.
> It is based on various libraries but not on a full rendering engine like WebKit or Gecko. The CSS layout engine is written in Python, designed for pagination, and meant to be easy to hack on.
> flit_core, pydyf, cffi, html5lib, tinycss2, cssselect2, Pyphen, Pillow, fonttools[woff]

## Unmaintained

### Abaco

https://en.wikipedia.org/wiki/Abaco_(web_browser)

* OS: Plan 9 and Linux
* HTML 4.01, frames, tables

### Amaya

* last update: 2013
* https://en.wikipedia.org/wiki/Amaya_(web_editor)
* https://github.com/w3c/Amaya-Editor
* features: CSS, MathML, images (png, SVG)
* implemented in: C

### Arena

* last update: 1998
* https://en.wikipedia.org/wiki/Arena_(web_browser)
* features: HTML 3.0, tables, math, links, images (jpg, png, gif, xpm, xbm), forms, CSS1, Java applets, no JavaScript
* protocol: HTTP 1.1, FTP, NNTP, gopher, WAIS, mailto
* parser and networking: libwww
* implemented in: C

### Arora

* last update: 2023, but engine stopped security patches earlier
* https://en.wikipedia.org/wiki/Arora_(web_browser)
* https://sourceforge.net/projects/zbrowser-linux/
* https://github.com/ZeromusSoftware/BlueLightCat
* https://github.com/EndorphinBrowser/browser
* rendering engine: QtWebkit
* implemented in: C++
* license: GPL v2 or later

### AWeb

* last update: 2009
* https://en.wikipedia.org/wiki/AWeb
* https://github.com/mirq/aweb
* https://github.com/matjam/aweb
* features: HTML 3.2, parts of HTML 4.01, forms, frames, animated GIF, JPEG, PNG, ILBM, WAV, AU, basic auth, utf-8, arexx, JavaScript ES3 (claimed 1.1), no CSS
* protocols: http, https, ftp, gopher, nntp, mailto (smtp)
* implemented in C
* platform: Amiga
* license: AWebPL

### BrowseX

* last update: 2001
* https://web.archive.org/web/20180515103826/http://jsish.org:80/browsex/Features.html
* https://web.archive.org/web/20020225144633/http://browsex.com/index.html
* https://web.archive.org/web/20180515103955/http://jsish.org:80/browsex/Javascript.html
* rendering engine: Tkhtml
* features: HTML 3.2, frames, form, cookies, basic auth, print to text and postscript, JavaScript (NGS javascript compiler), partial DOM, jpeg, png, animated gif, no CSS
* applications: web browser, web server with free dynamic DNS, password manager, mailbox, peer-to-peer Talk to chat based on hostname
* schemes: HTTP, HTTPS (SSL/TLS), FTP, POP3, file, proxy
* implemented in C, Tcl
* license: Artistic License

### Charon

* last update: 2007
* https://en.wikipedia.org/wiki/Charon_(web_browser)
* https://bitbucket.org/inferno-os/inferno-os/src/master/appl/charon/
* implemented in Limbo
* runs graphically under wm on Inferno
* schemes: HTTP 1.1, SSL v3, FTP, file
* features: start page, history, cookies, web proxy, utf-8
* aim for compatibility with Netscape 3.0: HTML 3.2 formatting, images (jpeg, xbitmap, Inferno BIT, animated gif), aimed for JavaScript 1.1 (ES2), but runtime has ES3 features

### contiki-os webbrowser

* last update: repository in 2018, browser mostly written in 2003
* https://github.com/contiki-os/contiki/blob/master/apps/webbrowser/
* interface: text-only
* features: a href links, img (only shows alt instead of the image), no layout (breaks flow on: p, h1, h2, h3, h4, newline on: br, tr, div), li, comments, form (action, input, submit), skips inline content of style, script and select
* protocols: HTTP 1.0 (with host header added, supporting 301/302 redirects)
* `User-Agent: Contiki/3.x (; http://www.contiki-os.org/)`
* no CSS, no JS
* implemented in C, up to 256 bytes of buffer lookahead
* platform: contiki-os
* license: BSD3

### Emacs w3

* last update: 2008
* https://www.emacswiki.org/emacs/w3
* https://elpa.gnu.org/packages/w3.html
* https://git.savannah.gnu.org/cgit/w3.git/tree/
* https://github.com/emacs-straight/w3
* https://www.xemacs.org/Documentation/21.5/html/xemacs-faq_5.html#Q6_002e4_002e1
* https://packages.ubuntu.com/plucky/xemacs21-basesupport
* interface: text-based, embedded within Emacs
* features: tables, utf-8, SOCKS v5, forms, images, mouse, no frames, some CSS1
* protocols: http 1.0, https, file, gopher, mailto, nntp
* no JS
* implemented in: Emacs LISP

### Erwise

* last update: 1992
* https://browsers.flanigan.us/browsers/erwise/index.html#run

### kweb

* last update: 2014
* https://github.com/ekapujiw2002/kweb
* rendering engine: WebKit

### Line Mode Browser

* last update: 2017
* https://en.wikipedia.org/wiki/Line_Mode_Browser
* https://github.com/w3c/libwww/blob/master/LineMode/Overview.html
* interface: text-only
* rendering engine: libwww
* features: HTML 4.0
* protocols: http 1.1 (pipelining, PUT, POST, digest authentication, deflate, IDN, SSL), ftp, nntp, wais, finger, rlogin, telnet, gopher
* no CSS, no JS
* implemented in: C

### Midori

* https://en.wikipedia.org/wiki/Midori_(web_browser)

```
apt install midori
```

### Mothra

* https://github.com/ocoufal/mothra
* https://en.everybodywiki.com/Mothra_(web_browser)
* http://man.9front.org/1/mothra
* platform: Plan 9
* interface: graphical
* features: forms, cache, proxy, utf-8, images (rendered using external programs: gif, jpeg, png, pic, tiff, xbm)
* tags: a, address, b, base, blockquote, body, br, center, cite, code, dd, dfn, dir, dl, dr, em, font, form, h1. h2, h3, h4, h5, h6, hr, i, input, img, isindex, kbd, key, li, link, listing, menu, meta, nextid, ol, option, p, plaintext, pre, samp, select, strong, table, td, textarea, title, tr, tt, u, ul, var, xmpp, frame
* protocols: http, gopher, ftp
* no CSS, no JS
* implemented in: C

### Mycel

* renamed from opossum in 2024, but no other change since 2022
* https://github.com/psilva261/mycel
* https://github.com/mjl-/duit
* https://github.com/andybalholm/cascadia
* https://github.com/psilva261/sparklefs
* https://github.com/psilva261/sparkle
* https://github.com/psilva261/6to5
* https://github.com/tdewolff/parse/tree/master/js
* interface: graphical (using duit)
* features: images, small subset of HTML5 and CSS (using cascadia)
* JavaScript: sparklefs (forked from goja and otto, uses sparkle and tdewolff/parse), basic DOM, AJAX, ES5 (ES6 with 6to5 translator)
* protocol: HTTP (TLS)
* platform: Plan 9 (9front, 9legacy, plan9port, 9pi), Mac OS, Linux
* implemented in: Go

> Still experimental and a lot of features are missing. Rudimentary HTML5 and CSS support, large parts like float/flex layout are just stub implementations. Since the implementation is very limited anyway, DOM changes are only computed initially and during click events. A handful of jQuery UI widgets work

### NCSA-mosaic

* https://github.com/alandipert/ncsa-mosaic

### Nexus WorldWideWeb

* last update: 1994
* https://en.wikipedia.org/wiki/WorldWideWeb
* https://www.w3.org/People/Berners-Lee/WorldWideWeb.html
* https://www.w3.org/History/1991-WWW-NeXT/Implementation/
* parser and networking: libwww

### Odysseus

* https://github.com/alcinnz/Odysseus

### retawq

* last update: 2006
* https://retawq.sourceforge.net/
* text-only
* features: mouse, incremental rendering, forms partially, tables partially, frames partially
* no CSS, no JS
* protocols: http, https, ftp, ftps, nntp, finger, file, local cgi

### tkWWW

* last update: 1995
* https://en.wikipedia.org/wiki/TkWWW
* http://web.mit.edu/course/other/cdsdev/html/tk-www/help/overview.html
* parser and networking: libwww
* implemented in: Tcl/Tk
* license: GPL v2

### Uzbl

https://en.wikipedia.org/wiki/Uzbl

* WebkitGtk+
* libsoup

### Voyager

* last update: 2002
* https://en.wikipedia.org/wiki/Voyager_(web_browser)
* https://zapek.com/software/voyager/
* features: HTML 3.2, frames, parts of HTML 4.01, table layout, basic auth, JavaScript 1.3, DOM level 1 (IE), CSS, pdf, animated gif, jpeg, alpha png, xbm
* protocols: http, https (TLS v1), ftp, mailto (smtp)
* implemented in C
* platform: Amiga
* license: GNU GPL v2

## Related

HTML rich text support by desktop widget toolkits

* https://github.com/bkil/wiki/blob/master/en/widget-toolkit-html-rich-text.md

FOSS JavaScript interpreters, runtimes

[./javascript-interpreter-runtimes.md](./javascript-interpreter-runtimes.md)

### References

* https://packages.debian.org/bookworm/www-browser
* https://en.wikipedia.org/wiki/List_of_web_browsers
* https://wiki.archlinux.org/title/List_of_applications/Internet#Web_browsers
* https://github.com/cliffordfajardo/awesome-web-browsers#user-content-desktop-web-browsers
* https://github.com/metov/awesome-browser#user-content-desktop-gui
* https://github.com/hs3180/awesome-browser#user-content-browser
* https://github.com/ZeroX-DG/awesome-browser#user-content-open-source-web-browsersbrowser-engines
* https://github.com/gaeulbyul/non-webkit#user-content-non-webkit
* https://github.com/nerdyslacker/desktop-web-browsers
* https://blogs.gnome.org/mcatanzaro/2022/11/04/stop-using-qtwebkit/
* https://en.wikipedia.org/wiki/Libwww#Applications_using_libwww
* https://eylenburg.github.io/browser_engines.htm
