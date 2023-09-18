# JavaScript

## Statements

* if-else
* while
* try-catch
* double slash comments
* throw
* function definition with an optional return at the end

missing:

* switch-case-default, for, for-in, for-of, foreach, do-while, label-goto, break, continue, with, arbitrary return, varargs

## Operators

* !, ~, +, -, * , /, %, <, >, <=, >=, ==, !=, ===, !==, ^, <<, >>

convenience:
* parenthesis subexpressions, short-circuiting &&, ||, + also works for string concatenation

missing:

* delete, instanceof, typeof, +=, ++, class, new (mocked for some built-in objects), precedence (have to fully parenthesize)

## Values

* var
* undefined
* null
* decimal integers
* string literals with escaping
* object square bracket member accessor

convenience:

* initializer for Object and Array, anonymous function expression, string control characters

missing:

* const, this, void, true, false, hexadecimal, float, object dot member accessor

## Navigator objects

### Document

* document.close
* document.write
* document['FormName']['ElementName'].value
* document.cookie (expires)

convenience:

* document.docType, document.documentElement.innerHTML, public suffix list

missing:

* document.open (implicit)

### Window

window.location.href
window.setTimeout (function)

missing:

* window.location.replace, window.setTimeout (string variant), window.setInterval, window.clearTimeout

## Language objects

missing:

* Boolean, Function, Math, Number, RegExp

### Array

`.length`

missing:

* concat, join, pop, push, reverse, shift, slice, splice, sort, unshift

### Date

`+new Date`

missing:

* everything except getting the current time in seconds

### Object

* Object.keys
* .hasOwnProperty

### String

* String.fromCharCode
* .charCodeAt
* .length

convenience:

* .toLowerCase, .toUpperCase, .substr, .match, .indexOf

missing:

* .charAt, .lastIndexOf, .concat, .split, .slice, .substring, .replace, .search

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

## Functions

* eval
* isNaN
* parseInt(s, 10)

missing:

* parseFloat, escape, unescape

## Implementation

Multiple proof of concept interpreter runtimes are in progress. If you would like to help with implementing this subset in a minimalistic way and provide feedback, let's get in touch to help shape the specification for the better.

* https://bkil.gitlab.io/static-wonders.js/browser-vm/fun-var-array-bf.html
* https://bkil.gitlab.io/static-wonders.js/browser-vm/fun-err-obj-js.html
* https://bkil.gitlab.io/static-wonders.js/browser-vm/parse-dispatch-js.html

A simple, text-entry & pre based browser written in the JavaScript subset interpreted by the interpreter in the browser:

* https://bkil.gitlab.io/static-wonders.js/browser-vm/lambda-dispatch-js.html

Not published yet:

* Multiple C-based interpreters for various subsets

Planned on shortlist:

* A minimalistic real world web app running in the C browser and runtime

## References

* https://web.archive.org/web/19990127231137/http://developer.netscape.com/docs/manuals/communicator/jsguide4/contents.htm
