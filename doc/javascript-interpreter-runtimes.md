# FOSS JavaScript interpreters, runtimes

Implementing the relevant standards of JavaScript fully would be prohibitively expensive for a hobby project.
Feel free to review the complexity of existing small independent solutions that are work in progress.

## Production

### DukTape

* https://duktape.org/dukweb.html

> Embeddable, portable, compact: can run on platforms with 160kB flash and 64kB RAM
> ECMAScript E5/E5.1, with some semantics updated from ES2015+
> Partial support for ECMAScript 2015 (E6) and ECMAScript 2016 (E7)
> ES2015 TypedArray and Node.js Buffer bindings

Includes a web based example interpreter.

### ucode

* https://github.com/jow-/ucode

> JavaScript-like language with optional templating
> The ucode language is a small, general-purpose scripting language that resembles ECMAScript syntax. It can be used as a standalone interpreter or embedded into host applications. Ucode supports template mode with control flow and expression logic statements embedded in Jinja-like markup blocks.
> The development of ucode was motivated by the need to rewrite the OpenWrt firewall framework using nftables. Initially intended as a template processor, ucode evolved into a versatile scripting language for various system scripting tasks. Its design goals include easy integration with C applications, efficient handling of JSON data and complex data structures, support for OpenWrt's ubus message bus system, and a comprehensive set of built-in functions inspired by Perl 5.

### v7

* https://github.com/cesanta/v7

> V7 is the smallest JavaScript engine written in C.
> Cross-platform: works on anything, starting from Arduino to MS Windows
> Small size. Compiled static size is in 40k - 120k range, RAM footprint on initialization is about 800 bytes with freeze feature, 15k without freeze feature
> Standard: V7 implements JavaScript 5.1
> Usable out-of-the-box: V7 provides an auxiliary library with Hardware (SPI, UART, etc), File, Crypto, Network API
> part of the full stack Mongoose OS Platform

### mJS

* https://github.com/cesanta/mjs

> mJS is designed for microcontrollers with limited resources. Main design goals are: small footprint and simple C/C++ interoperability. mJS implements a strict subset of ES6 (JavaScript version 6).
> On 32-bit ARM mJS engine takes about 50k of flash memory, and less than 1k of RAM. mJS is part of MongooseOS

### Espruino

* https://github.com/espruino/Espruino

> Espruino is a JavaScript interpreter for microcontrollers. It is designed for devices with as little as 128kB Flash and 8kB RAM.

### jerryscript

* https://github.com/jerryscript-project/jerryscript

> JerryScript is a lightweight JavaScript engine for resource-constrained devices such as microcontrollers. It can run on devices with less than 64 KB of RAM and less than 200 KB of flash memory.
> Full ECMAScript 5.1 standard compliance
> Heavily optimized for low memory consumption
> Snapshot support for precompiling JavaScript source code to byte code

### mujs

* https://mujs.com/

> MuJS is a lightweight Javascript interpreter designed for embedding in other software to extend them with scripting capabilities.
> MuJS was designed with a focus on small size, correctness, and simplicity. It is written in portable C and implements ECMAScript as specified by ECMA-262. The interface for binding with native code is designed to be as simple as possible to use, and is very similar to Lua.
> It was originally developed for use with the MuPDF viewer

### quickjs

* https://github.com/bellard/quickjs

> QuickJS is a small and embeddable Javascript engine. It supports the ES2020 specification including modules, asynchronous generators, proxies and BigInt.
> It supports mathematical extensions such as big decimal float float numbers (BigDecimal), big binary floating point numbers (BigFloat), and operator overloading.
> Small and easily embeddable: just a few C files, no external dependency, 210 KiB of x86 code for a simple "hello world" program.
> Fast interpreter with very low startup time
> Garbage collection using reference counting (to reduce memory usage and have deterministic behavior) with cycle removal.
> Small built-in standard library with C library wrappers.

### tiny-js

* https://github.com/gfwilliams/tiny-js

> This project aims to be an extremely simple (~2000 line) JavaScript interpreter, meant for inclusion in applications that require a simple, familiar script language that can be included with no dependencies other than normal C++ libraries. It currently consists of two source files: one containing the interpreter, another containing built-in functions such as String.substring.
> TinyJS is not designed to be fast or full-featured. However it is great for scripting simple behaviour, or loading & saving settings.
> I make absolutely no guarantees that this is compliant to JavaScript/EcmaScript standard. In fact I am sure it isn't. However I welcome suggestions for changes that will bring it closer to compliance without overly complicating the code, or useful test cases to add to the test suite.
> TinyJS uses a Recursive Descent Parser, so there is no 'Parser Generator' required. It does not compile to an intermediate code, and instead executes directly from source code. This makes it quite fast for code that is executed infrequently, and slow for loops.
> Variables, Arrays and Objects are stored in a simple linked list tree structure (42tiny-js uses a C++ Map). This is simple, but relatively slow for large structures or arrays.

### JS-Interpreter

* https://github.com/NeilFraser/JS-Interpreter

> A sandboxed JavaScript interpreter in JavaScript. Execute arbitrary ES5 JavaScript code line by line in isolation and safety.

### narcissus

* https://github.com/mozilla/narcissus/

> Narcissus is a JavaScript interpreter written in pure JavaScript (i.e., a meta-circular evaluator), using the SpiderMonkey engine.
> Originally a proof-of-concept, a test-bed for rapidly prototyping new language features for the JavaScript language (as well as the ECMAScript standard).

### otto

* https://github.com/robertkrimen/otto
* https://github.com/robertkrimen/natto

> Package otto is a JavaScript parser and interpreter written natively in Go.
> Otto targets ES5
> Go translates JavaScript-style regular expressions into something that is "regexp" compatible via parser.TransformRegExp. Unfortunately, RegExp requires backtracking for some patterns, and backtracking is not supported by the standard Go engine. re2 (Go) has a different definition for \s: [\t\n\f\r ]
> Package natto is an example/offshoot of otto that implements an event loop (supporting setTimeout/setInterval).

## Planned

### this project

* As this project is not public yet, only an internal working name is available.
* The main scope is producing only documentation, specification and conformance tests. Developers are expected to implement it on their own.
* A proof of concept JavaScript0 interpreter plugin for gemini and web browsers and for CLI/CGI web server integration will be provided later in multiple languages, both low level and high level.
* Language: C, PHP, busybox ash & awk, JavaScript0

### ToyLang

* https://github.com/evomassiny/toylang
* Language: Rust

> This a toy programming language, utterly useless. I'm using it to experiment parser, compiler and interpreter designs
> keywords: function (only supports named function), while, for, if, else, return, let, null, undefined, continue, break
> operators: + - * / ** %, > < >= <= ==, ! && ||, ++foo foo++ --foo foo--
> separators: ; for expressions, ( ) for sub-expressions, { }
> literals: booleans, float/integers, strings

## Benchmarks

* https://kangax.github.io/compat-table/es6/

## References

* https://en.wikipedia.org/wiki/List_of_ECMAScript_engines

## Related

HTML rich text support by desktop widget toolkits

* https://github.com/bkil/wiki/blob/master/en/widget-toolkit-html-rich-text.md

FOSS web browsers by engine

[./web-browsers-by-engine.md](./web-browsers-by-engine.md)
