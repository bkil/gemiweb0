# JavaScript feature set overview

This is non normative work in progress. See the following document for a detailed reasoning about each choice of cutting features from the grammar:

* [js-choices.md](js-choices.md)

## Statements

* if-else
* while
* for-in
* comments
* function definition
* return
* optional compound block within if, while or for statements ({})
* ES3/NS5: try-catch, throw

convenience:

* function expression

missing:

* ES3/NS4: switch-case-default, do-while, label-goto
* for (the C-styled one), for-of, break, continue, with, varargs, arbitrary block scopes with {}
* NS2: arguments
* ES3/NS4: call, apply
* ES6: tail call optimization

## Operators

* !, ~, +, -, *, /, %, <, >, <=, >=, ^, |, &, <<, >>, >>>, ===, !==

convenience:

* parenthesis subexpressions, short-circuiting &&, ||, '+' also works for string concatenation
* ES1/NS3: typeof

missing:

* ==, !=, +=, ++, class, new (mocked for some built-in objects), precedence (have to fully parenthesize)
* ES3/NS5: instanceof
* ES1/NS2: ternary operator
* ES1/NS2: comma operator
* NS4: delete

## Values

* var
* undefined
* null
* decimal integers
* NaN
* string literals (without escaping)
* Object and Array square bracket member accessor ([])

convenience:

* var initializer, object dot member accessor, member access chaining
* ES3/NS4: anonymous function expression

missing:

* this, true, false, hexadecimal, float, string control character escapes
* NS3: void
* ES3: Object and Array literals
* ES5: const, let

## Functions

* eval
* eval2: not standard, a sandboxed variant not operating on the current environment, but on one passed in as an Object argument
* isNaN
* parseInt(s, 10)

missing:

* parseFloat, escape, unescape

## Language objects

missing:

* Boolean, Function, Math, Number, RegExp

### Array

* .length
* [i]

missing:

* ES2/NS3: join, reverse, sort
* ES3/NS4: concat, pop, push, shift, slice, splice, unshift

### Date

missing:

* everything except a few basic arithmetics with the current time in milliseconds (date + number, date / number, date % number, date - date)

### Object

* ES3: .hasOwnProperty

missing:

* NS3: valueOf

### String

* .length
* .charAt
* ES2/NS4: String.prototype.fromCharCode
* ES2/NS4: .charCodeAt

convenience:

* .indexOf
* ES3/NS4: .match

missing:

* .lastIndexOf, .substring, .toLowerCase, .toUpperCase
* ES2/NS3: .split
* ES3/NS4: .concat, .slice, .replace, .search, .substr

## Application server

```
TODO This section still needs more research, a proof of concept and then drafting.
```

* console.log()
* process.stdin.on('data', function(data) {})
* require('fs').readFileSync(file)
* require('fs').writeFileSync(file, data)
* require('node:net').createServer(function(socket) {}).listen(function(){}).close()
* require('node:net').createConnection({}, function() {}).on('data', function(data) {}).write('')
* require('node:net').connect({})

## Navigator objects

These are not provided by the interpreter, but by the runtime of the web browser user agent.

### Document

* document.close
* document.write
* document['FormName']['ElementName'].value

convenience:

* document.docType, document.documentElement.innerHTML

missing:

* document.open (implicit)

### Cookies

A hardened minimal subset required to interface with most common gratis web hosting, storage and authorization providers

* document.cookie (expires)
* public suffix list

### Window

* window.location.href
* NS2: window.setTimeout (function argument)

missing:

* window.location.replace, window.setTimeout (string variant), window.clearTimeout
* NS4: window.setInterval

### XMLHttpRequest

* new XMLHttpRequest
* .open
* .onload
* .onerror
* .ontimeout
* .status
* .timeout
* .send
* .responseText

## Implementation

Multiple proof of concept interpreter runtimes are in progress. If you would like to help with implementing this subset in a minimalistic way and provide feedback, let's get in touch to help shape the specification for the better.

* https://bkil.gitlab.io/static-wonders.js/browser-vm/fun-var-array-bf.html
* https://bkil.gitlab.io/static-wonders.js/browser-vm/fun-err-obj-js.html
* https://bkil.gitlab.io/static-wonders.js/browser-vm/parse-dispatch-js.html

A simple, text-entry & pre based browser written in the JavaScript subset interpreted by the interpreter in the browser:

* https://bkil.gitlab.io/static-wonders.js/browser-vm/lambda-dispatch-js.html

Work in progress C interpreter aiming for short source that is easy to review, small size of compressed binary code and low memory footprint:

* [../src/js2/test-vm.c](../src/js2/test-vm.c)
* [../src/js3/test-vm.c](../src/js3/test-vm.c)

Not published yet:

* Multiple C-based interpreters for various subsets

Planned on shortlist:

* A minimalistic real world web app running in the C browser and runtime

## Inspiration

* https://tinygo.org/docs/concepts/compiler-internals/
* https://docs.micropython.org/en/latest/develop/index.html
* https://bellard.org/tcc/tcc-doc.html#devel
* https://t3x.org/subc/
* https://github.com/DoctorWkt/acwj
* https://github.com/KolibriOS/kolibrios/tree/main/programs/develop/cmm

## Best practices

* https://biomejs.dev/linter/rules
* https://github.com/biomejs/biome/tree/main/website/src/content/docs/linter/rules
* https://eslint.org/docs/latest/rules/
* https://github.com/eslint/eslint/tree/main/docs/src/rules
* https://jshint.com/docs/options/
* https://github.com/jshint/jshint/blob/main/src/options.js
* https://github.com/jslint-org/jslint#user-content-directive-jslint
* https://github.com/semgrep/semgrep-rules/tree/develop/javascript/lang
* https://github.com/google/closure-compiler/wiki/Flags-and-Options#available-error-groups
* https://github.com/google/closure-compiler/wiki/Lint-checks
* https://github.com/google/closure-compiler/wiki/JS-Conformance-Framework
* https://github.com/google/closure-compiler/tree/master/src/com/google/javascript/jscomp

## References

### JavaScript 1.0

* https://web.archive.org/web/19970613234917/http://home.netscape.com/eng/mozilla/2.0/handbook/javascript/index.html

### JavaScript 1.1

* https://web.archive.org/web/19970614042441/http://home.netscape.com/eng/mozilla/3.0/handbook/javascript/index.html
* https://web.archive.org/web/19981205222505/http://home.netscape.com/eng/javascript/
* https://hepunx.rl.ac.uk/~adye/jsspec11/jsspec.ps.gz
* https://www.ecma-international.org/wp-content/uploads/ECMA-262_2nd_edition_august_1998.pdf

### JavaScript 1.2

* https://web.archive.org/web/19990127231137/http://developer.netscape.com/docs/manuals/communicator/jsguide4/contents.htm
* https://www.ecma-international.org/wp-content/uploads/ECMA-262_3rd_edition_december_1999.pdf

### EcmaScript

* https://www.ecma-international.org/publications-and-standards/standards/ecma-262/
