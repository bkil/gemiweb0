# FOSS JavaScript interpreters and runtimes

Implementing the relevant standards of JavaScript fully would be prohibitively expensive for a hobby project. Feel free to review the complexity of existing small independent solutions as an alternative.

## Production

### cesanta elk

* https://github.com/cesanta/elk
* supports a tiny subset of ES6 (numerous restrictions below ES1)
* implemented in: C

> Elk: a tiny JS engine for embedded systems. Does not use malloc. Operates with a given memory buffer only. Small footprint: about 20KB on flash/disk, about 100 bytes RAM for core VM. No bytecode. Interprets JS code directly.  Elk is completely bare, it does not even have a standard library.

### CL-JavaScript

* https://github.com/akapav/js
* https://marijnhaverbeke.nl/cl-javascript/
* license: MIT
* implemented in: Common Lisp

> CL-JavaScript allows you to add user scripting to your Common Lisp application without requiring your poor users to learn Common Lisp. It is a JavaScript to Common Lisp translator, runtime, and standard library. We are ECMAScript 3 compatible, with some of the ECMAScript 5 extensions.
> By using the Lisp compiler to compile JavaScript (and by using some clever tricks for the things that Lisp normally isn't good at), this implementation manages to be faster than most of the 2009 generation of JavaScript engines. The new generation (V8, Jägermonkey) beats it by, depending on the benchmark, a factor 4 or so.

### DukTape

* https://duktape.org/dukweb.html
* https://github.com/svaarala/duktape
* https://packages.ubuntu.com/plucky/duktape
* https://packages.debian.org/buster/libduktape203
* https://packages.debian.org/bullseye/libduktape205
* https://packages.ubuntu.com/plucky/libduktape207

> Embeddable, portable, compact: can run on platforms with 160kB flash and 64kB RAM
> ECMAScript E5/E5.1, with some semantics updated from ES2015+
> Partial support for ECMAScript 2015 (E6) and ECMAScript 2016 (E7)
> ES2015 TypedArray and Node.js Buffer bindings

Includes a web based example interpreter.

### Escargot

* https://github.com/Samsung/escargot
* features: "a significant portion" of ES2025, memory efficiency
* implemented in: C++
* architecture: x86, x64, arm, aarch64
* platforms: Linux, MacOS, Windows, Android
* license: LGPL-2.1

### Espruino

* https://github.com/espruino/Espruino
* implemented in: C

> Espruino is a JavaScript interpreter for microcontrollers. It is designed for devices with as little as 128kB Flash and 8kB RAM.

### goja

* https://github.com/dop251/goja
* https://packages.ubuntu.com/plucky/golang-github-dop251-goja-dev
* forked from Otto
* features: ES 5.1
* implemented in: Go

### GraalJS

* https://github.com/oracle/graaljs
* implemented in: Java
* features: ECMAScript 2023, Node.js

> includes all the benefits from the GraalVM stack including interoperability with Java.

### Hermes

* https://github.com/facebook/hermes
* implemented in: C++

> Hermes is a JavaScript engine optimized for fast start-up of React Native apps. It features ahead-of-time static optimization and compact bytecode.

### JavaScriptCore

* https://en.wikipedia.org/wiki/WebKit#JavaScriptCore
* https://github.com/WebKit/WebKit/tree/main/Source/JavaScriptCore
* https://packages.debian.org/buster/libqtwebkit4
* https://packages.ubuntu.com/oracular/libqt5webkit5
* https://web.archive.org/web/20210507015325/packages.ubuntu.com/bionic/libjavascriptcoregtk-1.0-0
* https://web.archive.org/web/20210507015325/http://packages.ubuntu.com/libjavascriptcoregtk-3.0-0
* https://packages.debian.org/bookworm-backports/libjavascriptcoregtk-4.0-18
* https://packages.ubuntu.com/oracular/libjavascriptcoregtk-4.1-0
* https://packages.ubuntu.com/oracular/libjavascriptcoregtk-6.0-1
* used by: Webkit (Safari)
* implemented in: C++
* platforms: Linux, Mac, iOS, Windows
* license: LGPLv2.1 and 2-BSD

### jerryscript

* https://github.com/jerryscript-project/jerryscript

> JerryScript is a lightweight JavaScript engine for resource-constrained devices such as microcontrollers. It can run on devices with less than 64 KB of RAM and less than 200 KB of flash memory.
> Full ECMAScript 5.1 standard compliance
> Heavily optimized for low memory consumption
> Snapshot support for precompiling JavaScript source code to byte code

### Jint

* https://github.com/sebastienros/jint
* https://github.com/sebastienros/jint/blob/main/Jint.Benchmark/README.md
* features: ES5 with many additions from later standards up to ES2025
* used by: RavenDB, EventStore, OrchardCore, ELSA Workflows, docfx, JavaScript Engine Switcher
* implemented in: C#
* platforms: .NET Standard 2.0 and .NET 4.6.2 (and later)
* license: 2-BSD

### Jurassic

* https://github.com/paulbartrum/jurassic
* features: ES5, some ES6 features, compiles JS to .NET bytecode
* implemented in: C#
* platforms: .NET 3.5, .NET 4 and Silverlight
* license: MIT

### Kinoma XS6

* https://github.com/Kinoma/kinomajs
* https://www.moddable.com/XS7-TC-39

> Kinoma's XS6 library implements a JavaScript virtual machine optimized for devices with limited resources. This virtual machine conforms to the 6th edition of the ECMAScript specification (ECMAScript 2015).
> The Kinoma Porting Layer (KPL) is the bottom of the KinomaJS stack. It is a very light portability layer, modeled, as much as practical, on POSIX. Because KinomaJS runs on a wide variety of operating systems, the goal is to isolate all direct calls to the host operating in KPL. Some RTOS hosts do not support the full ANSI C library, so it cannot even be safely assumed that functions like printf are available. To avoid surprises with the size of types, a portable-type system modeled on that used by QuickTime is used.

### Ladybird LibJS

* formerly for SerenityOS LibWeb
* https://github.com/LadybirdBrowser/ladybird/tree/master/Userland/Libraries/LibJS
* used by Ladybird

### Micro QuickJS

* https://github.com/bellard/mquickjs
* https://www.phoronix.com/news/Micro-QuickJS
* features: a small, but robust subset of ES5, tracing and compacting garbage collector
* implemented in: C
* license: MIT

> Compiles & Runs JavaScript With As Little As 10kB Of RAM. Requires just around 100 kB of ROM, including the C library

### microvium

* https://github.com/coder-mike/microvium/blob/main/doc/supported-language.md#not-supported
* https://coder-mike.com/behind-microvium/
* https://coder-mike.com/blog/2022/06/11/microvium-is-very-small/
* implemented in: C
* supports a small subset of ES3 with some ES6 features

> Microvium is a tiny JavaScript engine (less than 16kB compiled size) for microcontrollers for running a small but useful subset of the JavaScript language. The runtime engine is portable C code and easy to integrate. Microvium takes the unique approach partially running the JS code at build time and deploying a snapshot, which leads to a number of advantages over other embedded JavaScript engines.

### mujs

* https://mujs.com/
* https://github.com/ccxvii/mujs
* https://packages.ubuntu.com/plucky/mujs
* https://packages.ubuntu.com/jammy/libmujs1
* https://packages.ubuntu.com/plucky/libmujs3
* license: ISC

> MuJS is a lightweight Javascript interpreter designed for embedding in other software to extend them with scripting capabilities.
> MuJS was designed with a focus on small size, correctness, and simplicity. It is written in portable C and implements ECMAScript as specified by ECMA-262. The interface for binding with native code is designed to be as simple as possible to use, and is very similar to Lua.
> It was originally developed for use with the MuPDF viewer

### nginx njs

* https://github.com/nginx/njs
* https://nginx.org/en/docs/njs/
* https://packages.ubuntu.com/plucky/njs
* https://packages.debian.org/trixie/njs
* ES5.1 strict with some ES6 extensions

### NiL.JS

* https://github.com/nilproject/NiL.JS
* features: ES6
* platform: .NET Framework 4.6.1+, .NET Standard 1.3+, .NET Core 3.1, 5.0 and 6.0
* implemented in: C#
* license: 3-BSD

### otto

* https://github.com/robertkrimen/otto
* https://github.com/robertkrimen/natto
* https://packages.ubuntu.com/jammy/golang-github-robertkrimen-otto-dev

> Package otto is a JavaScript parser and interpreter written natively in Go.
> Otto targets ES5
> Go translates JavaScript-style regular expressions into something that is "regexp" compatible via parser.TransformRegExp. Unfortunately, RegExp requires backtracking for some patterns, and backtracking is not supported by the standard Go engine. re2 (Go) has a different definition for \s: [\t\n\f\r ]
> Package natto is an example/offshoot of otto that implements an event loop (supporting setTimeout/setInterval).

### Qt V4

* https://doc.qt.io/qt-6/qtqml-javascript-hostenvironment.html
* https://doc.qt.io/qt-6/qtjavascript.html
* https://wiki.qt.io/V4
* https://wiki.qt.io/Application_Scripting_with_QJSEngine
* https://wiki.qt.io/Qt-contributors-summit-2013-QML-engine
* https://packages.ubuntu.com/oracular/libqt5qml5
* https://packages.ubuntu.com/oracular/libqt6qml6
* implemented in: C++
* features: ES7, JIT
* Used for QML and QJSEngine

### quickjs

* https://github.com/bellard/quickjs
* https://packages.ubuntu.com/plucky/libjavascript-quickjs-perl
* https://packages.ubuntu.com/plucky/r-cran-quickjsr
* https://packages.ubuntu.com/plucky/node-quickjs-emscripten
* https://packages.ubuntu.com/plucky/libquickjs
* https://packages.ubuntu.com/plucky/quickjs

> QuickJS is a small and embeddable Javascript engine. It supports the ES2020 specification including modules, asynchronous generators, proxies and BigInt.
> It supports mathematical extensions such as big decimal float float numbers (BigDecimal), big binary floating point numbers (BigFloat), and operator overloading.
> Small and easily embeddable: just a few C files, no external dependency, 210 KiB of x86 code for a simple "hello world" program.
> Fast interpreter with very low startup time
> Garbage collection using reference counting (to reduce memory usage and have deterministic behavior) with cycle removal.
> Small built-in standard library with C library wrappers.

### quickjs-ng

* https://github.com/quickjs-ng/quickjs

> Friendly QuickJS fork focused on reigniting the project.

### SpiderMonkey

* https://en.wikipedia.org/wiki/SpiderMonkey
* https://github.com/mozilla-spidermonkey/spidermonkey.dev
* https://github.com/mozilla-firefox/firefox/tree/main/js/src
* https://packages.ubuntu.com/plucky/libmozjs-128-0
* used by: Gecko (Mozilla Firefox)
* implemented in: C, C++, Rust
* architectures: IA-32, x86-64, ARM, MIPS, SPARC, RISC-V
* license: MPL 2.0

### Rhino

* https://en.wikipedia.org/wiki/Rhino_(JavaScript_engine)
* https://github.com/mozilla/rhino
* https://packages.ubuntu.com/plucky/rhino
* https://packages.ubuntu.com/plucky/librhino-java
* https://mozilla.github.io/rhino/compat/engines.html
* status: bundled with JRE
* used by LibreOffice, gngr
* features: ES5 with additions from ES6 and ES2016+
* implemented in: Java
* license: MPL 2.0

### ucode

* https://github.com/jow-/ucode
* https://github.com/ynezz/openwrt-ucode
* https://github.com/openwrt/luci/tree/master/modules/luci-base/ucode
* https://github.com/openwrt/luci/tree/master/applications/luci-app-commands/ucode
* https://github.com/openwrt/luci/blob/master/modules/luci-base/root/usr/share/rpcd/ucode/luci

> JavaScript-like language with optional templating
> The ucode language is a small, general-purpose scripting language that resembles ECMAScript syntax. It can be used as a standalone interpreter or embedded into host applications. Ucode supports template mode with control flow and expression logic statements embedded in Jinja-like markup blocks.
> The development of ucode was motivated by the need to rewrite the OpenWrt firewall framework using nftables. Initially intended as a template processor, ucode evolved into a versatile scripting language for various system scripting tasks. Its design goals include easy integration with C applications, efficient handling of JSON data and complex data structures, support for OpenWrt's ubus message bus system, and a comprehensive set of built-in functions inspired by Perl 5.

### V8

* https://en.wikipedia.org/wiki/V8_(JavaScript_engine)
* https://chromium.googlesource.com/v8/v8
* https://packages.ubuntu.com/oracular/libqt5webenginecore5
* https://packages.ubuntu.com/oracular/libqt6webenginecore6
* used by: Blink (Chromium, Google Chrome)
* architectures: IA-32, x86-64, 32-bit ARM, AArch64, 32-bit MIPS, MIPS64, PowerPC, IBM ESA/390, z/Architecture
* implemented in: C++
* license: BSD

### YantraJS.Core

* https://github.com/yantrajs/yantra
* features: "many" ES5 and ES6 features
* implemented in: C#
* platform: .NET (Core and Standard 2)
* license: Apache 2.0

## Maintained metacircular

### engine262

* https://github.com/engine262/engine262
* implemented in: JavaScript

### JS-Interpreter

* https://github.com/NeilFraser/JS-Interpreter

> A sandboxed JavaScript interpreter in JavaScript. Execute arbitrary ES5 JavaScript code line by line in isolation and safety.

### Porffor

* https://github.com/CanadaHonk/porffor
* implemented in: JavaScript
* license: MIT

> A from-scratch experimental AOT optimizing JS/TS -> Wasm/C engine/compiler/runtime in JS. Research project, not yet intended for serious use. Expect nothing to work! Only very limited JS is currently supported.

### Siubaak sval

* https://github.com/Siubaak/sval
* implemented in: JavaScript ES5
* features: ES5
* license: MIT

> Both invasived and sandbox modes available. Based on parser Acorn.

## Planned

### gemiweb0

* The main scope is producing only documentation, specification and conformance tests. Developers are expected to implement it on their own.
* A proof of concept JavaScript0 interpreter plugin for gemini and web browsers and for CLI/CGI web server integration will be provided later in multiple languages, both low level and high level.
* Language: C, PHP, busybox ash & awk, JavaScript0

### Yavashark

* https://github.com/Sharktheone/yavashark
* features: JavaScript, TypeScript
* implemented in: Rust
* license: MIT

## Experimental

### bali

* https://github.com/ferus-web/bali
* implemented in: Nim with C++ dependencies
* used by: Ferus web engine, Basket Wayland launcher
* license: LGPLv3

> Bali is still not in a usable state yet and is probably unstable. It is not meant to be used in production for now. As of 9th of November, 2024, Bali can successfully run 1% of the entire Test262 suite
> With some recent codegen optimizations, Bali is already pretty fast on cherry-picked benchmarks. Bali can perform some optimizations when it is generating code for the provided JavaScript source, granted that it can prove that there is an opportunity to optimize away things. Bali has some loop elision optimizations in place which can fully eliminate an expensive loop when it sees the opportunity. It also has some rudimentary dead code elimination for some cases.

### boa

* https://github.com/boa-dev/boa
* implemented in Rust
* license: Unlicense or MIT

> Boa is an embeddable and experimental Javascript engine written in Rust. Currently, it has support for some of the language.

### brimstone

* https://github.com/Hans-Halverson/brimstone
* features: most of ES2024
* implemented in Rust
* license: MIT

> Heavy inspiration is taken from the design of V8 and SerenityOS's LibJS. Brimstone chooses to implement almost all components of the engine from scratch with minimal dependencies, with the notable exception of ICU4X. Bytecode VM, heavily inspired by the design of V8's Ignition, Compacting garbage collector, written in very unsafe Rust, Custom RegExp engine

### Esprima .NET

Only a parser

* last update: 2024
* https://github.com/sebastienros/esprima-dotnet
* features: ES2022 parser with some newer features, JSX
* implemented in: C#
* platform: .NET 6
* license: 3-BSD

### Guile ECMAScript

* implemented around 2009, but still maintained
* https://git.savannah.gnu.org/cgit/guile.git/tree/module/language/ecmascript/
* https://www.gnu.org/software/guile/manual/html_node/ECMAScript.html
* approximately ES3 (not finished)

> It's probably not as fast as compilers that produce native code, but because it hooks into Guile's compiler at a high level, as Guile's compiler improves and eventually gets native code compilation, it will be plenty fast.

### Kiesel

* https://codeberg.org/kiesel-js/kiesel
* implemented in: Zig

> The implementation style is similar to LibJS - the JS engine used in SerenityOS and the Ladybird browser which I worked on before - in various aspects, most notably the desire to stay very close to spec. Development is still at an early stage and the engine's usefulness thus limited. While there are various things that already work well, there's an equal amount of things that don't :^)

### Nova

* https://github.com/trynova/nova
* implemented in: Rust
* license: MPL-2.0

> The execution model is currently greatly inspired by Kiesel and SerenityOS's LibJS. See the code for more details. Passing about 70% of the test262 test suite

### Toshok EchoJS

* https://github.com/toshok/echojs

> An ahead of time compiler and runtime for ES6. Things only build reliably on OSX. You'll need a couple of external dependencies to get things running: node.js, llvm 3.6, coffeescript

## Unmaintained

### adaptive-enterprises SEE

* https://web.archive.org/web/20240505032022/https://www.adaptive-enterprises.com.au/~d/software/see/
* https://web.archive.org/web/*/http://adaptive-enterprises.com/viewvc/see/see/trunk/*
* 2009
* ES3, JavaScript 1.5
* BSD
* C
* used by the HV3 web browser

### AWeb

* last update: 2009
* https://github.com/mirq/aweb/tree/master/aweblibs/awebjs
* features: JavaScript ES3 (claimed 1.1)
* implemented in C
* platform: Amiga
* license: AWebPL

### BeRo1985 besen

* last update: 2020
* https://github.com/BeRo1985/besen
* licence: LGPL2

> Complete ECMAScript Fifth Edition Implemention in Object Pascal

### cesanta mJS

* https://github.com/cesanta/mjs
* 2021

> mJS is designed for microcontrollers with limited resources. Main design goals are: small footprint and simple C/C++ interoperability. mJS implements a strict subset of ES6 (JavaScript version 6).
> On 32-bit ARM mJS engine takes about 50k of flash memory, and less than 1k of RAM. mJS is part of MongooseOS

### cesanta v7

* https://github.com/cesanta/v7
* 2020

> V7 is the smallest JavaScript engine written in C.
> Cross-platform: works on anything, starting from Arduino to MS Windows
> Small size. Compiled static size is in 40k - 120k range, RAM footprint on initialization is about 800 bytes with freeze feature, 15k without freeze feature
> Standard: V7 implements JavaScript 5.1
> Usable out-of-the-box: V7 provides an auxiliary library with Hardware (SPI, UART, etc), File, Crypto, Network API
> part of the full stack Mongoose OS Platform

### ChakraCore

* last update: 2020
* https://en.wikipedia.org/wiki/Chakra_(JavaScript_engine)
* https://github.com/chakra-core/ChakraCore
* used in Microsoft Edge Legacy (EdgeHTML)
* features: ES5.1 with additions from ES6
* implemented in: C++
* license: MIT

### Charon

* last update: 2007
* https://bitbucket.org/inferno-os/inferno-os/src/master/appl/charon/
* https://bitbucket.org/inferno-os/inferno-os/src/master/appl/lib/ecmascript/
* JavaScript ES3
* implemented in Limbo

### Constellation iv lv5

* last update: 2015
* https://github.com/Constellation/iv/tree/master/iv/lv5
* ES 5.1
* implemented in C++
* license: 2-BSD

> ECMAScript Lexer / Parser / Interpreter / VM / method JIT written in C++

### DMDScript

* last update: mostly implemented until 2017, still accepting patches up to 2024
* https://github.com/DigitalMars/DMDScript
* https://digitalmars.com/dscript/
* features: ES3, lacking __proto__
* implemented in: D
* license: BSL-1.0

### edbrowse 2

* last update: 2006
* https://web.archive.org/web/20101027132444/http://eklhad.net/edbrowse/edbrowse-2.2.10.zip
* JavaScript ES3 with a subset of DOM level 1
* implemented in C
* used by edbrowse up to v2.2.10

### Ejacs

* last update: 2018, but most code is from 2008
* https://github.com/emacsattic/ejacs
* features: ES3 and some JavaScript 1.5
* implemented in Emacs LISP
* license: GPL v2

> Ejacs is basically a toy. It is regrettably insufficient in several important dimensions

### Epimetheus

* last update: 2002
* https://www-archive.mozilla.org/js/language/epimetheus
* https://github.com/jrmuizel/mozilla-cvs-history/tree/master/js2
* https://github.com/ehsan/mozilla-cvs-history/tree/master/js2
* https://github.com/rhencke/mozilla-cvs-history/tree/master/js2
* https://github.com/roytam1/mozilla-cvs-history/tree/master/mozilla/js2
* features: most of ES3, ES4 draft
* implemented in: C++
* license: MPL 1.1/GPL 2.0/LGPL 2.1

### HJS

* last update: 2008
* https://wiki.haskell.org/Libraries_and_tools/HJS
* https://hackage.haskell.org/package/hjs-0.2.1
* features: ES3 and some JavaScript 1.5
* implemented in: Haskell
* license: 3-BSD

### JE

* last update: 2014
* https://metacpan.org/dist/JE
* https://packages.ubuntu.com/plucky/libje-perl
* features: ES3 with some ES5 behavior
* implemented in: Perl 5.0.4
* license: perl

### Jsish

* last update: 2018
* https://sourceforge.net/projects/jsish/
* https://web.archive.org/web/20180315190341/http://jsish.org/jsi/www/home.wiki
* https://web.archive.org/web/20180315195803/http://jsish.org/jsi/doc/tip/jsi/www/language.wiki#syntax
* https://web.archive.org/web/20180316140742/http://jsish.org/jsi/doc/tip/jsi/www/background.wiki#ecma
* support aimed at ES5.1
* implemented in: C

> provides types to increase maintainability, has builtin support for web and database, A Jsi function may have parameters with types and default values

### KHTML KJS

* https://github.com/KDE/khtml/tree/0c0f313659504be0fcd2feec92fd7a7a425379fb/src/ecma
* https://en.wikipedia.org/wiki/KHTML
* https://packages.debian.org/buster/libkjsapi4
* Used by Konqueror (KHTML) in the past
* implemented in: C++
* license: LGPLv2.1

### Links 2.1pre28

* last update: 2007
* http://dezip.org/http://links.twibright.com/download/links-2.1pre28.tar.gz
* JavaScript 1.1
* implemented in C
* used by links2 up to 2.1.pre28
* http://links.twibright.com/user_en.html#ap-javascript
* http://links.twibright.com/project.html#subch-javascript
* http://links.twibright.com/doc/links_doc_en.html#javascript
* http://links.twibright.com/doc/links_doc_en.html#interpret_javascriptu
* http://links.twibright.com/doc/implementacni.html#javascript

### lugrin.ch FESI

* https://web.archive.org/web/20120906033028/http://www.lugrin.ch/fesi/
* https://web.archive.org/web/20030622113311/home.worldcom.ch/jmlugrin/fesi/
* 2003
* ES1
* Java

### mbedthis appWeb ejs

* https://mbedthis.com/products/appWeb/doc/ejs/overview.html
* https://github.com/doghell/appweb-3/tree/master/src/ejs
* https://github.com/ly-web/appweb2/tree/master/ejs
* https://github.com/embedthis/appweb-doc
* 2011
* subset of JavaScript 1.5
* C++
* GNU GPL

### Nashorn

* https://en.wikipedia.org/wiki/Nashorn_(JavaScript_engine)
* https://github.com/openjdk/nashorn
* status: only a few patches up to 2023, deprecated since 2017, removed from JRE
* used by: Web-K
* features: fully compliant with ES5.1, also has additions from ES6
* implemented in: Java
* license: GNU GPL v2 with Classpath exception

### NGS JavaScript interpreter

* last update: 2023 (development halted in 1999 and resumed in 2023)
* https://github.com/markkurossi/js
* https://docs.stendahls.net/js/ngs/
* features: ES3
* no regexp, no Unicode
* used by: BrowseX
* implemented in: C
* license: GNU LGPL

### NJS-JavaScript.org

* last update: 2013
* https://sourceforge.net/projects/njs/
* https://web.archive.org/web/20080509072332/http://www.njs-javascript.org/
* https://web.archive.org/web/20080517015930/www.bbassett.net/njs/
* forked from NGS when it was discontinued in 1999
* features: ES3
* no regexp, no Unicode
* implemented in: C
* license: GNU LGPL

### Qt Script for Applications

* last update: 2008
* https://doc.qt.io/archives/qsa-1.2.2/getting-started.html
* https://web.archive.org/web/20131202231949/http://blog.qt.digia.com/blog/2007/01/05/say-hello-to-qtscript/
* https://github.com/aschet/qsaqt5
* deprecated by QtScript (4.3, 4.4, 4.5)
* implemented in: C++

### QtScript 4.5

* last update: 2009
* https://wiki.qt.io/JavaScript
* https://wiki.qt.io/Category:Developing_Qt::Qt_Script#History
* https://download.qt.io/archive/qt/4.5/
* http://dezip.org/v1/9/https/download.qt.io/archive/qt/4.5/qt-all-opensource-src-4.5.3.zip/qt-all-opensource-src-4.5.3/src/script/
* https://packages.debian.org/buster/libqt4-script
* https://packages.ubuntu.com/plucky/libqt5script5
* implemented in: C++
* features: ES5
* used in QtScript in Qt 4.3, 4.4 and 4.5 (2009)

### Tamarin

* last update: 2016
* https://en.wikipedia.org/wiki/Tamarin_(software)
* https://github.com/adobe/avmplus
* features: ES3, ActionScript 3, ES4 draft
* license: Tri-licensed GPL, LGPL, and MPL
* used in: Adobe Flash Player 9
* implemented in: C++

### sparkle

* last update: 2022
* https://github.com/psilva261/sparkle
* forked from goja
* features: ES 5.1 with BigInt arrays
* implemented in: Go
* used by: Mycel browser

### tiny-js

* https://github.com/gfwilliams/tiny-js
* 2019

> This project aims to be an extremely simple (~2000 line) JavaScript interpreter, meant for inclusion in applications that require a simple, familiar script language that can be included with no dependencies other than normal C++ libraries. It currently consists of two source files: one containing the interpreter, another containing built-in functions such as String.substring.
> TinyJS is not designed to be fast or full-featured. However it is great for scripting simple behaviour, or loading & saving settings.
> I make absolutely no guarantees that this is compliant to JavaScript/EcmaScript standard. In fact I am sure it isn't. However I welcome suggestions for changes that will bring it closer to compliance without overly complicating the code, or useful test cases to add to the test suite.
> TinyJS uses a Recursive Descent Parser, so there is no 'Parser Generator' required. It does not compile to an intermediate code, and instead executes directly from source code. This makes it quite fast for code that is executed infrequently, and slow for loops.
> Variables, Arrays and Objects are stored in a simple linked list tree structure (42tiny-js uses a C++ Map). This is simple, but relatively slow for large structures or arrays.

### ToyLang

* https://github.com/evomassiny/toylang
* 2021
* Language: Rust

> This a toy programming language, utterly useless. I'm using it to experiment parser, compiler and interpreter designs
> keywords: function (only supports named function), while, for, if, else, return, let, null, undefined, continue, break
> operators: + - * / ** %, > < >= <= ==, ! && ||, ++foo foo++ --foo foo--
> separators: ; for expressions, ( ) for sub-expressions, { }
> literals: booleans, float/integers, strings

### neades yaji

* last update: 2012
* https://github.com/neades/yaji-ecmascript-interpreter/tree/master/yaji-ecmascript-interpreter
* fork of FESI
* at least ES3 (aiming for ES5)
* implemented in: Java

### UweSchmidt js0

* last update: 2017
* https://github.com/UweSchmidt/js0/blob/master/src/Lang/JS0/Parser.hs
* features: unfinished, but the parser and the types seem to have progressed well
* implemented in: Haskell
* license: 3-BSD

> A Simplified JavaScript Compiler and Virtual Machine

### Voyager

* last update: 2002
* https://en.wikipedia.org/wiki/Voyager_(web_browser)
* https://zapek.com/software/voyager/
* https://github.com/zapek/Voyager
* features: JavaScript 1.3, DOM level 1 (IE)
* implemented in C
* platform: Amiga
* license: GNU GPL v2

## Unmaintained metacircular

### bramblex jsjs

* last update: 2018
* https://github.com/bramblex/jsjs

### benvie continuum

* last update: 2012
* https://web.archive.org/web/20121203041426/http://benvie.github.com/continuum/
* https://web.archive.org/web/20150619174908/github.com/benvie/continuum
* https://github.com/srounce/continuum
* supports ES6 draft
* implemented in JavaScript ES3

### es-lab

* https://github.com/tvcutsem/es-lab/blob/master/src/parser/es5parser.ojs
* https://github.com/tvcutsem/es-lab/blob/master/src/eval/eval.js

> ES-lab: experiments with proposed extensions to JavaScript. A "reify eval, absorb apply" style meta-interpreter for ES5.

### Esprima

Only a parser

* last update: 2021
* https://github.com/jquery/esprima
* https://esprima.org/
* features: ES2019 parser, JSX
* implemented in: TypeScript
* license: 2-BSD

### MetaES

* last update: 2022
* https://github.com/metaes/metaes
* implemented in: JavaScript
* license: MIT

### narcissus

* https://github.com/mozilla/narcissus/
* 2012

> Narcissus is a JavaScript interpreter written in pure JavaScript (i.e., a meta-circular evaluator), using the SpiderMonkey engine.
> Originally a proof-of-concept, a test-bed for rapidly prototyping new language features for the JavaScript language (as well as the ECMAScript standard).

### ohmjs ecmascript

Only a parser:

* https://github.com/ohmjs/ohm/blob/main/examples/ecmascript/README.md
* https://github.com/ohmjs/ohm/blob/main/examples/ecmascript/src/es5.ohm

> Ohm grammars for various versions of the ECMAScript spec. Based on Tom Van Cutsem's ES5 parser from the es-lab project. Currently, only the ES5 grammar is reasonably complete, but we are working on ES6.

## Benchmarks

* https://github.com/chromium/octane
* https://github.com/mzp/sunspider-jsx
* https://github.com/nbp/lifetime-benchmark
* https://github.com/sebastienros/jint/blob/main/Jint.Benchmark/README.md
* https://github.com/tc39/test262
* https://github.com/v8/web-tooling-benchmark
* https://github.com/WebKit/WebKit/tree/main/Websites/webkit.org/perf/
* https://compat-table.github.io/compat-table/es6/
* http://www.webkit.org/perf/sunspider/sunspider.html

## References

* https://en.wikipedia.org/wiki/List_of_JavaScript_engines
* https://joehni.github.io/JsUnit/products.html
* https://github.com/ivankra/javascript-zoo#user-content-list-of-javascript-engines
* https://gist.github.com/guest271314/bd292fc33e1b30dede0643a283fadc6a

## Related

HTML rich text support by desktop widget toolkits

* https://github.com/bkil/wiki/blob/master/en/widget-toolkit-html-rich-text.md

FOSS web browsers by engine

[./web-browsers-by-engine.md](./web-browsers-by-engine.md)

Daily runner of test262 and comparison chart for many engines:

* https://test262.fyi/
