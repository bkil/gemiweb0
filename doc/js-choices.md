# JavaScript restrictions

A heavy set of restrictions are imposed on user code that can be executed by the interpreter. This allows to make the runtime as simple to implement and reason about as possible.

The following restrictions are non-normative and being worked on pending the result of proof of concepts implemented in various host programming languages.

## Mandatory

### Whitespace and comments

* Verdict: Recommended
* Reason: easy to implement, required for LibreJS-level distribution of code in preferred form of modification by each web site
* Standard: JS1

### if-else

* Verdict: Recommended
* Implementation complexity: low
* Incidence rate: very common
* Reason: Turing-completeness
* Standard: JS1

### while

* Verdict: Required
* Incidence rate: very common
* Reason: Turing-completeness
* Standard: JS1

### for-in

* Verdict: Required
* Incidence rate: rare
* Reason: single original way for dynamic iteration on Object keys
* Standard: JS1

### function definition and return

* Verdict: Required
* Incidence rate: very common
* Reason: basic modularization. A restriction of return at the very end of the body was considered, but then dismissed as easy to implement without this restriction while greatly improving clarity of user code.
* Standard: JS1

### read from standard input

* Verdict: Recommended
* Incidence rate: none in web code, high in command line and server CGI code
* Reason: Turing-completeness
* Solution: process.stdin.on
* Workaround: some other API that can open and read from a file descriptor
* Standard: Node.js

### reading contents of a file

* Verdict: Recommended
* Incidence rate: none in web code, high in command line and server CGI code
* Reason: native platform interface
* Solution: require('fs').readFile()
* Alternative: require('fs').readFileSync()
* Workaround: some other API that can open and read from a file descriptor
* Standard: Node.js

### writing contents to a file

* Verdict: Recommended
* Incidence rate: none in web code, high in command line and server CGI code
* Reason: native platform interface
* Solution: require('fs').writeFile()
* Workaround: some other API that can open and write to a file descriptor
* Standard: Node.js

### document.cookie

* Verdict: required
* Incidence rate: low, but non-negligible
* Reason: useful to interface with extant web hosting services
* Workaround: none for web, adding custom headers for HTTP/TCP connections on native platforms
* Standard: NS2

### Call stack quota

* Verdict: required
* Reason: the visitor must have control over untrusted code
* Implementation complexity: low

### Heap allocation quota

* Verdict: required
* Reason: the visitor must have control over untrusted code
* Implementation complexity: higher intermediate due to many corner cases
* Solution: account for each allocation including overheads of alignment and padding, accessing a large index in an array, allocate many small objects, concatenating large strings, setting many fields on a single object, manipulations on mmap'ped files

### CPU time quota

* Verdict: required
* Reason: the visitor must have control over untrusted code
* Implementation complexity: intermediate
* Solution: if the interactive user agent is single threaded without a means to abort the script from the interface, start a watchdog timer within the event loop and terminate the script if the single atomic dispatch takes more than the quota. If the user interface can remain responsive for aborting a running script, the total CPU time since the last user interaction with the script should be metered and the user warned if it had taken more than a threshold or if the average CPU utilization percentage caused by the script had exceeded a threshold after some time.

## Quality of life improvement

### Pause, resume and terminate script upon interactive command

* Verdict: recommended
* Implementation complexity: low if granularity provided by event loop conditioning is sufficient, intermediate if termination at reductions or via a separate process model would be warranted, very high if resumption without POSIX job control signals also required

### javascript: URI

* Verdict: recommended
* Reason: the simplest alternative for client side interaction
* Incidence rate: very high
* Use case: client side interactions, form processing, validation, bookmarklets
* Implementation complexity: trivial
* Workaround: implement event handlers such as onclick and onsubmit or navigate to a URI pointing to (or submit a form targeting) an HTML containing JavaScript that dispatches upon loading, encode the link identifier and serialize the whole application state to the URI query or anchor
* Standard: NS2

### Pure anonymous function expression

* Verdict: Recommended
* Reason: Potential for building a higher level library by the user
* Standard: ES1 (`Function`), ES3 (`function(){}`)

### Nested function definition

* Verdict: Recommended
* Reason: modularization, reducing global oversaturation and reduce visibility of unrelated functionality
* Standard: ES3

### short-circuiting operators &&, ||

* Verdict: recommended
* Incidence: high
* Workaround: if, &
* Standard: JS1

### eval

* Verdict: recommended
* Incidence: low
* Implementation complexity: low
* Workaround: interpreter
* Standard: JS1

### Strict equality === !==

* Verdict: recommended
* Reason: suggested by style guides, avoids wide classes of errors, easy to understand by beginners
* Incidence: high to always
* Implementation complexity: low
* Workaround: error prone and too verbose, invoke abstract equality and `typeof` or `instanceof` in every expression it occurs
* Standard: ES3

### document.write

* Verdict: recommended
* Incidence rate: intermediate
* Implementation complexity: low
* Reason: the simplest alternative for interactive document modification
* Workaround: serialize state, generate a complete new document using the string return value of a `javascript:` link to navigate away to, deserialize state
* Standard: NS2

### reading the value of a form input element

* Verdict: required
* Incidence rate: high
* Implementation complexity: low
* Reason: allow for interacting with typed user input without server involvement
* Workaround: unsatisfactory due to lack of caching, allow to submit the form via GET and parse the values from the URI upon load, without forms, provide an on screen keyboard with individual links for each key
* Standard: NS2

### Consecutive terms of same operator in expressions

* Verdict: recommended
* Restriction: you can apply the same operator consecutively in an expression without using parenthesis
* Use cases: string concatenation, numerical sums, factors, short circuiting bool logic
* Incidence rate: high
* Implementation complexity: trivial (only a few lines of code)
* Drawback: it creates an irregular corner case of supported syntax that needs to be remembered
* Workaround: parenthesis
* Standard: JS1

### Automatic ToBoolean conversion

* Verdict: supported
* Reason: expected by users
* Drawbacks: restricting it could improve hardening, either remove it completely or only support integers 0 and 1
* Incidence rate: high, higher for an interpreter substituting integers for the Boolean type
* Implementation complexity: trivial
* Workaround: invoke the `Boolean()` function
* Standard: JS1

## To research

### Abstract equality == !=

* Verdict: not mandatory, avoid in user code if possible
* Reason: may lead to bugs, difficult to keep in mind all corner cases for beginners, may only be needed for compatibility with JavaScript 1.0
* Incidence: low
* Implementation complexity: low
* Workaround: usually unwanted, but may simulate by first converting a value to canonical form according to the standard and compare with a sequence of strict equality checks
* Standard: JS1

### Floating point numbers

* Verdict: Desirable, but unsupported
* Restriction: only integers supported and the special value of `NaN`
* Reason: too complex to implement and potentially increases memory use and more difficult to optimize. `NaN` is desirable to detect error conditions of standard functions.
* Standard: JS1

### Automatic ToString conversion

* Verdict: partial
* Restriction: only allowed for concatenation by `+`
* Reason: expected by users, but would be beneficial to forbid
* Drawbacks: can often cause bugs if working on values of unforeseen types
* Incidence rate: high
* Implementation complexity: trivial, assuming `String()` is already available, high if had to make standard library conforming
* Workaround: invoke the `String()` function
* Standard: JS1

### Unicode

* Verdict: partially supported
* Restrictions: String indexing may iterate on UTF8 instead of UCS-2. May assume that the HTML and JS source are all encoded as UTF8.
* Use cases: must be able to process input in extant human languages in a way that should work in a way equivalent to extant web browsers.
* Standard: JS1

### Operator precedence in expressions

* Verdict: partial
* Restriction: only support unary and binary operators to avoid having to observe operator precedence rules. A few subexpressions may be supported without parenthesis that are very common: function invocation, array index, object member. The special case of consecutive terms of same operator is detailed separately.
* Incidence rate: intermediate
* Implementation complexity: intermediate
* Workaround: parenthesis, temporary variables
* Standard: JS1

### Booleans

* Verdict: not supported
* Incidence rate: high
* Implementation complexity: low
* Workaround: can be substituted with `0===1` and `1===1`, but 0/1 can also be used instead of false/true similarly to C
* Standard: JS1

### Date

* Verdict: partial
* Restriction: You can only subtract two Date objects from each other to get the elapsed time in milliseconds, add a Date and a Number offset to result in a Date and divide or compute modulo of a Date by a Number (usually 1000) as taken in number of milliseconds since Unix epoch. This should allow for Number to be represented on 32 bits. Consider methods for returning the locale time offset.
* Implementation complexity: high if unrestricted
* Incidence rate: low
* Workaround: library
* Standard: JS1

### RegExp

* Verdict: partial, investigate
* Restrictions: no RegExp class, String match, search or replace
* Incidence rate: intermediate to high
* Implementation complexity: intermediate if platform has compatible built-ins, very high otherwise
* Runtime overhead: variable memory and CPU utilization, may be exploited with ReDoS unless additional sanitization is implemented
* Workaround: while, if, String charCodeAt
* Standard: ES3

## Partial

### semicolon

* Verdict: partial
* Implementation complexity: high if done per standard
* Reason: automatic semicolon insertion as called for by the standard is very complicated to both implement and remember.
* Restriction: terminate or begin every statement with a `;`. You can leave out `;` either before the end of a block (end of program or before `}`) or after the start of a block (start of program or after `{`)
* Standard: JS1

### write to standard output

* Verdict: Partial
* Restriction: only a single argument is allowed for console.log() without any formatting
* Incidence rate: low in web code, high in command line and server CGI code
* Reason: Turing-completeness
* Solution: console.log
* Workaround: some other API that can open and write to a file descriptor
* Standard: Node.js, IE8, Firefox 4, Chrome 4, Opera 11, Safari 3.1

### block scope braces

* Verdict: supported
* Restrictions: only allowed (optional) for body of if-else and while
* Implementation complexity: easy if restricted
* Workaround: function, multiple if
* Standard: JS1

### Immediately invoked anonymous function expression

* Verdict: Recommended
* Reason: desirable qualities of encapsulation useful for modules and userscript (userjs) within a web browser.
* Restrictions: not all syntax may be supported and in not every position within an expression. This should work: `(function(){})();`
* Workaround: `Function`
* Standard: ES1 (`Function`), ES3 (`function(){}`)

### Environment capturing by a function definition

* Verdict: Desirable, but only partially supported
* Use cases: state encapsulation for object oriented programming, Currying for functional programming
* Restrictions: to avoid reference cycles, a runtime may make a shallow copy of the environment from above the function definition, not including itself.
* Workaround: Use a C-like function definition order within the file. Recursion needs to be worked around by passing in a self-reference for the function. `Function` and `eval` could also be used as an alternative.
* Standard: ES3

### Variable initializer

* Verdict: Desirable, partially supported
* Incidence rate: frequently
* Implementation complexity: easy
* Restriction: single variable and single initializer supported per `var` keyword as usually recommended by style guides to maintain one statement per line.
* Standard: JS1

### Exceptions try-catch, throw

* Verdict: desirable, limited support
* Restriction: no classes, catch may be implemented as a restricted kind of environment
* Reason: Useful for detecting error conditions of standard functions.
* Standard: ES3, NS5

### Field accessor chaining

* Verdict: desirable, limited support
* Incidence rate: very common
* Implementation complexity: easy
* Restriction: chaining starting from a variable should be supported, but may not support interspersing function calls or parenthesized expressions
* Standard: JS1

### window.location.href

* Verdict: partial
* Use cases: process arguments in the URI query or hash anchor, possibly `GET` form submissions
* Restriction: can only get the full URL as a string
* Workaround: library
* Standard: NS2

### window.setTimeout

* Verdict: partial
* Restriction: function argument, up to a single timeout active at a time
* Implementation complexity: higher intermediate, needs an event loop with termination and signal handling
* Use cases: retry with backoff, autosave, neighborly crawling, animation, debouncing, initialization after onload (instead of noscript)
* Workaround: eval instead of string argument, none for setTimeout itself (except for immediately invoking the function if the timeout is 0), implement a dispatcher that tracks upcoming events in ascending order to simulate multiple timers
* Standard: NS2, JS1

### form post

* Verdict: partial
* Implementation complexity: high, encoding types, file attachments, hooks for both HTML and JavaScript
* Restriction: limited input types, limited attributes (action, method, enctype)
* Standard: NS2

### XMLHttpRequest

* Verdict: partial
* Implementation complexity: high, header handling, timeout, reference cycle
* Restriction: can only return a string responseText without progress, CORS may not be complete
* Use cases: interfacing with API, third party integration, incremental update of local state, bookmarklet that would parse the current document
* Workaround: JSONP, form submit, Fetch
* Standard: Internet Explorer 5, Gecko 1.0, Safari 1.2, Opera 8

### Automatic ToNumber conversion

* Verdict: partial
* Restriction: only allowed to get milliseconds from a Date for certain operators detailed in the Date section
* Reason: potential for bugs outweighs ergonomic benefits in most common code
* Drawbacks: can often cause bugs if working on values of unforeseen types
* Incidence rate: low
* Implementation complexity: low, assuming `parseInt()` is already available, high if had to make standard library conforming
* Workaround: `typeof`, `parseInt()`
* Standard: JS1

### Instantiate class with new keyword

* Verdict: partial
* Restriction: only for a few predetermined classes (Array, Object, XMLHttpRequest), see constructor arguments detailed separately.
* Incidence rate: low for custom classes, intermediate for built-in
* Implementation complexity: high if assuming full OOP, prototype and this support
* Drawbacks: prototype based inheritance is disfavored
* Workaround: can cleanly simulate OOP by capturing state within a Function that returns an Object of methods
* Standard: JS1

## Unsupported

### Automatic ToPrimitive conversion

* Verdict: unsupported
* Reason: implementation cost and introduced irregularity outweighs ergonomic benefits in most common code
* Drawbacks: can often cause bugs if working on values of unforeseen types
* Incidence rate: low
* Implementation complexity: high
* Workaround: convert to appropriate type manually
* Standard: JS1

### Constructor arguments

* Verdict: unsupported
* Implementation complexity: intermediate
* Incidence rate: low
* Use cases: Array initializer (instead of ES3 Array literal), ES3 RegExp
* Reason: not crucial in practice
* Workaround: separately instantiate the class and then initialize it (Array), use function application based alternatives that work without the new keyword (Function, String), substitute RegExp with String match, search or replace
* Standard: JS1

### window.setInterval

* Verdict: unsupported
* Implementation complexity: low
* Workaround: simulate using setTimeout and Date
* Standard: NS4

### writing to the value of a form input element

* Verdict: not supported
* Incidence rate: low
* Implementation complexity: higher intermediate, depending on widget toolkit, may need to keep the whole HTML source or a representation in memory and reflow
* Workaround: generate a new document with the intended value set as default, possibly represent value within body outside form
* Standard: NS2

### variable declaration hoisting

* Verdict: not supported
* Reason: considered bad practice, confusing for beginners
* Implementation complexity: low to intermediate depending on graph representation, may carry a runtime penalty when streaming
* Incidence rate: very low, usually not on purpose
* Use cases: none
* Workaround: declare a variable before referencing it
* Standard: JS1

### do-while

* Verdict: not supported
* Reason: redundant, but would be beneficial at times
* Implementation complexity: easy
* Incidence rate: low
* Workaround: while, if, return
* Standard: ES3

### for

* Verdict: not supported
* Reason: redundant, but would be beneficial at times
* Implementation complexity: easy
* Incidence rate: intermediate
* Workaround: while
* Standard: JS1

### break, continue

* Verdict: not supported
* Implementation complexity: intermediate
* Incidence rate: low
* Reason: goto also disfavored by style guides
* Workaround: return, if, altered loop condition, function expression
* Standard: JS1

### varargs

* Verdict: not supported
* Implementation complexity: intermediate (function arguments object, call, apply)
* Incidence rate: rare
* Use cases: a few standard library functions in ES3 whose functionality could be restricted to only support the minimal amount of non-trivial arguments (1 for Array.prototype.concat, push, unshift, String.fromCharCode, String.prototype.concat, 2 for Array.prototype.splice, Math.min, max and the Function() constructor)
* Workaround: Array
* Standard: JS1

### block scope environment const, let

* Verdict: not supported
* Implementation complexity: complicated
* Incidence rate: would be often useful
* Reason: would increase memory pressure, would be less error prone for newcomers than the function scope `var`
* Workaround: function, immediately invoked anonymous function expression
* Standard: ES6

### switch-case-default

* Verdict: not supported
* Implementation complexity: intermediate
* Incidence rate: rare
* Workaround: if-else
* Standard: ES3

### Literal object notation

* Verdict: not supported, desirable at times
* Implementation complexity: straightforward
* Incidence rate: intermediate
* Workaround: easy, create an intermediate object and add the value via an accessor
* Standard: ES3

### Literal array notation

* Verdict: not supported, desirable at times
* Implementation complexity: straightforward
* Incidence rate: intermediate
* Workaround: easy, create an intermediate array and add the value via an index
* Standard: ES3

### Reference cycles

* Verdict: Unsupported.
* Restriction: Avoid storing a reference within object `p` pointing to object `q` if there exists a directed path leading from `q` to `p`. Captured function environment scopes are also counted as a reference.
* Reason: Such a cycle would mandate a more complicated and less deterministic garbage collection scheme for collecting cycles specifically.
* Workaround: store the key of a given object within a common map instead of a direct reference. Inspect carefully which environment a given function definition captures and alter the ordering or use additional encapsulation to hide stray paths.
* Standard: JS1

### Tail call optimization

* Verdict: unsupported
* Reason: still not supported by most major browsers as of 2023
* Implementation complexity: very high
* Incidence rate: low (none for common imperative code)
* Workaround: while
* Standard: optional since ES6

### Prototype

* Verdict: avoid in user code
* Restriction: runtime implementation may use it internally but may not expose it to user code
* Reason: uniform implementation is difficult, slow and uses more memory. Also considered bad practice for most use cases.
* Workaround: emulate regular inheritance by function expressions or chain only pure functions where applicable
* Standard: JS1
