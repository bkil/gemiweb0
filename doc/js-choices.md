# JavaScript restrictions

A heavy set of restrictions are imposed on user code that can be executed by the interpreter. This allows to make the runtime as simple to implement and reason about as possible.

The following restrictions are non-normative and being worked on pending the result of proof of concepts implemented in various host programming languages.

## Mandatory

### Whitespace and comments

* Verdict: Recommended
* Reason: easy to implement, required for LibreJS-level distribution of code in preferred form of modification by each web site

### if-else

* Verdict: Recommended
* Implementation complexity: low
* Incidence rate: very common
* Reason: Turing-completeness

### while

* Verdict: Required
* Incidence rate: very common
* Reason: Turing-completeness

### for-in

* Verdict: Required
* Incidence rate: rare
* Reason: single original way for dynamic iteration on Object keys

### function definition and return

* Verdict: Required
* Incidence rate: very common
* Reason: basic modularization. A restriction of return at the very end of the body was considered, but then dismissed as easy to implement without this restriction while greatly improving clarity of user code.

### read from standard input

* Verdict: Recommended
* Incidence rate: none in web code, high in command line and server CGI code
* Reason: Turing-completeness
* Solution: process.stdin.on
* Workaround: some other API that can open and read from a file descriptor

### write to standard output

* Verdict: Recommended
* Incidence rate: low in web code, high in command line and server CGI code
* Reason: Turing-completeness
* Solution: console.log
* Workaround: some other API that can open and write to a file descriptor

### reading contents of a file

* Verdict: Recommended
* Incidence rate: none in web code, high in command line and server CGI code
* Reason: native platform interface
* Solution: require('fs').readFile()
* Alternative: require('fs').readFileSync()
* Workaround: some other API that can open and read from a file descriptor

### writing contents to a file

* Verdict: Recommended
* Incidence rate: none in web code, high in command line and server CGI code
* Reason: native platform interface
* Solution: require('fs').writeFile()
* Workaround: some other API that can open and write to a file descriptor

### document.cookie

* Verdict: required
* Incidence rate: low, but non-negligible
* Reason: useful to interface with extant web hosting services
* Workaround: none for web, adding custom headers for HTTP/TCP connections on native platform

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

### Pure anonymous function expression

* Verdict: Recommended
* Reason: Potential for building a higher level library by the user

### Nested function definition

* Verdict: Recommended
* Reason: modularization, reducing global oversaturation and reduce visibility of unrelated functionality

### short-circuiting operators &&, ||

* Verdict: recommended
* Incidence: high
* Workaround: if, &

### eval

* Verdict: recommended
* Incidence: low
* Implementation complexity: low
* Workaround: interpreter

### Strict equality === !===

* Verdict: recommended
* Reason: suggested by style guides, avoids wide classes of errors, easy to understand by beginners
* Incidence: high to always
* Implementation complexity: low
* Workaround: error prone and too verbose, invoke abstract equality and `typeof` or `instanceof` in every expression it occurs

### document.write

* Verdict: recommended
* Incidence rate: intermediate
* Implementation complexity: low
* Reason: the simplest alternative for interactive document modification
* Workaround: serialize state, generate a complete new document using the string return value of a `javascript:` link to navigate away to, deserialize state

### reading the value of a form input element

* Verdict: required
* Incidence rate: high
* Implementation complexity: low
* Reason: allow for interacting with typed user input without server involvement
* Workaround: unsatisfactory due to lack of caching, allow to submit the form via GET and parse the values from the URI upon load

## To research

### Abstract equality == !==

* Verdict: not mandatory, avoid in user code if possible
* Reason: may lead to bugs, difficult to keep in mind all corner cases for beginners, may only be needed for compatibility with JavaScript 1.0
* Incidence: low
* Implementation complexity: low
* Workaround: usually unwanted, but may simulate by first converting a value to canonical form according to the standard and compare with a sequence of strict equality checks

### Floating point numbers

* Verdict: Desirable, but unsupported
* Restriction: only integers supported and the special value of `NaN`
* Reason: too complex to implement and potentially increases memory use and more difficult to optimize. `NaN` is desirable to detect error conditions of standard functions.

### Unicode

* Verdict: partially supported
* Restrictions: String indexing may iterate on UTF8 instead of UCS-2. May assume that the HTML and JS source are all encoded as UTF8.
* Use case: must be able to process input in extant human languages in a way that should work in an equivalent way to extant web browsers.

### Operator precedence in expressions

* Verdict: partial
* Restriction: only support unary and binary operators to not have to observe operator precedence rules. A few subexpressions may be supported without parenthesis that are very common: function invocation, array index, object member.
* Incidence rate: intermediate
* Implementation complexity: intermediate
* Workaround: parenthesis, temporary variables

### Booleans

* Verdict: not supported
* Incidence rate: high
* Implementation complexity: low
* Workaround: can be substituted with `0===1` and `1===1`, but 0/1 can also be used instead of false/true similarly to C

### Date

* Verdict: partial
* Restriction: only getting the current time as a Unix epoch and converting it to a number is supported. Ensure storage on enough bits. Consider returning the locale time offset.
* Implementation complexity: high if unrestricted
* Incidence rate: low
* Workaround: library

## Partial

### semicolon

* Verdict: partial
* Implementation complexity: high if done per standard
* Reason: automatic semicolon insertion as called for by the standard is very complicated to both implement and remember.
* Restriction: terminate or begin every statement with a `;`. You can leave out `;` either before the end of a block (end of program or before `}`) or after the start of a block (start of program or after `{`)

### block scope braces

* Verdict: supported
* Restrictions: only allowed (optional) for body of if-else and while
* Implementation complexity: easy if restricted
* Workaround: function, multiple if

### Immediately invoked anonymous function expression

* Verdict: Recommended
* Reason: desirable qualities of encapsulation useful for modules and userscript (userjs) within a web browser.
* Restrictions: not all syntax may be supported and in not every position within an expression. This should work: `(function(){})();`

### Environment capturing by a function definition

* Verdict: Desirable, but only partially supported
* Use case: state encapsulation for object oriented programming, Currying for functional programming
* Restrictions: to avoid reference cycles, a runtime may make a shallow copy of the environment from above the function definition, not including itself.
* Workaround: Use a C-like function definition order within the file. Recursion needs to be worked around by passing in a self-reference for the function. `Function` and `eval` could also be used as an alternative.

### Variable initializer

* Verdict: Desirable, partially supported
* Incidence rate: frequently
* Implementation complexity: easy
* Restriction: single variable and single initializer supported per `var` keyword as usually recommended by style guides to maintain one statement per line.

### Exceptions try-catch, throw

* Verdict: desirable, limited support
* Restriction: no classes, catch may be implemented as a restricted kind of environment
* Reason: Useful for detecting error conditions of standard functions.

### Field accessor chaining

* Verdict: desirable, limited support
* Incidence rate: very common
* Implementation complexity: easy
* Restriction: chaining starting from a variable should be supported, but may not support interspersing function calls or parenthesized expressions

### window.location.href

* Verdict: partial
* Use cases: process arguments in the URI query or hash anchor, possibly `GET` form submissions
* Restriction: can only get the full URL as a string
* Workaround: library

### window.setTimeout

* Verdict: partial
* Restriction: function argument, up to a single timeout active at a time
* Implementation complexity: higher intermediate, needs an event loop with termination and signal handling
* Use cases: retry with backoff, autosave, neighborly crawling, animation, debouncing
* Workaround: eval instead of string argument, none for setTimeout itself, implement a dispatcher that tracks upcoming events in ascending order to simulate multiple timers

### form post

* Verdict: partial
* Implementation complexity: high, encoding types, file attachments, hooks for both HTML and JavaScript
* Restriction: limited input types, limited attributes (action, method, enctype)

### XMLHttpRequest

* Verdict: partial
* Implementation complexity: high, header handling, timeout
* Restriction: can only return a string responseText without progress, CORS may not be complete
* Use cases: interfacing with API, third party integration, incremental update of local state
* Workaround: JSONP, form submit

## Unsupported

### window.setInterval

* Verdict: unsupported
* Implementation complexity: low
* Workaround: simulate using setTimeout and Date

### writing to the value of a form input element

* Verdict: not supported
* Incidence rate: low
* Implementation complexity: higher intermediate, depending on widget toolkit, may need to keep the whole HTML source or a representation in memory and reflow
* Workaround: generate a new document with the intended value set as default, possibly represent value within body outside form

### variable declaration hoisting

* Verdict: not supported
* Reason: considered bad practice, confusing for beginners
* Implementation complexity: low to intermediate depending on graph representation, may carry a runtime penalty when streaming
* Incidence rate: very low, usually not on purpose
* Use case: none
* Workaround: declare a variable before referencing it

### do-while

* Verdict: not supported
* Implementation complexity: easy
* Incidence rate: low
* Workaround: while, if, return

### for

* Verdict: not supported
* Implementation complexity: easy
* Incidence rate: intermediate
* Workaround: while

### break, continue

* Verdict: not supported
* Implementation complexity: intermediate
* Incidence rate: low
* Reason: goto also disfavored by style guides
* Workaround: return, if, altered loop condition

### varargs

* Verdict: not supported
* Implementation complexity: intermediate (function arguments object, call, apply)
* Incidence rate: rare
* Use cases: a few standard library functions in ES3 whose functionality could be restricted to only support the minimal amount of non-trivial arguments (1 for Array.prototype.concat, push, unshift, String.fromCharCode, String.prototype.concat, 2 for Array.prototype.splice, Math.min, max and the Function() constructor)
* Workaround: Array

### block scope environment const, let

* Verdict: not supported
* Implementation complexity: complicated
* Incidence rate: would be often useful
* Reason: would increase memory pressure, would be less error prone for newcomers than the function scope `var`
* Workaround: function, immediately invoked anonymous function expression

### switch-case-default

* Verdict: not supported
* Implementation complexity: intermediate
* Incidence rate: rare
* Workaround: if-else

### Literal object notation

* Verdict: not supported, desirable at times
* Implementation complexity: straightforward
* Incidence rate: intermediate
* Workaround: easy, create an intermediate object and add the value via an accessor

### Literal array notation

* Verdict: not supported, desirable at times
* Implementation complexity: straightforward
* Incidence rate: intermediate
* Workaround: easy, create an intermediate array and add the value via an index

### Reference cycles

* Verdict: Unsupported.
* Restriction: Avoid storing a reference within object `p` pointing to object `q` if there exists a directed path leading from `q` to `p`. Captured function environment scopes are also counted as a reference.
* Reason: Such a cycle would mandate a more complicated and less deterministic garbage collection scheme for collecting cycles specifically.
* Workaround: store the key of a given object within a common map instead of a direct reference. Inspect carefully which environment a given function definition captures and alter the ordering or use additional encapsulation to hide stray paths.

### Prototype

* Verdict: avoid in user code
* Restriction: runtime implementation may use it internally but may not expose it to user code
* Reason: uniform implementation is difficult, slow and uses more memory. Also considered bad practice for most use cases.
* Workaround: emulate regular inheritance by function expressions or chain only pure functions where applicable
