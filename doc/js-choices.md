# JavaScript restrictions

A heavy set of restrictions are imposed on user code that can be executed by the interpreter. This allows to make the runtime as simple to implement and reason about as possible.

The following restrictions are non-normative and being worked on pending the result of proof of concepts implemented in various host programming languages.

## Mandatory

### Whitespace and comments

* Verdict: Recommended
* Reason: easy to implement, required for LibreJS-level distribution of code by each web site

### if-else

* Verdict: Recommenedd
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
* Reason: basic modularization. A restriction of return at the very end of the body was considered, but then dismissed as easy to implement and greatly improving clarity of user code.

## Quality of life improvement

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

## To research

### Floating point numbers

* Verdict: Desirable, but unsupported
* Restriction: only integers supported and the special value of `NaN`
* Reason: too complex to implement and potentially increases memory use and more difficult to optimize. NaN is desirable to detect error conditions of standard functions.

### Unicode

* Verdict: partially supported
* Restrictions: String indexing may iterate on UTF8 instead of UCS-2
* Use case: must be able to process input in extant human languages in a way that should work in an equivalent way to extant web browsers.

### Operator precedence in expressions

* Verdict: partial
* Restriction: only support unary and binary operators to not have to observe operator precedence rules. A few subexpressions may be supported without parenthesis that are very common: function invocation, array index, object member.
* Incidence rate: intermediate
* Implementation complexity: intermediate
* Workaround: parenthesis, temporary variables

### Booleans

* Verdict not supported
* Incidence rate: high
* Implementation complexity: low
* Workaround: can be substituted with `0===1` and `1===1`, but 0/1 can be used instead of false/true similar to C

### Date

* Verdict: partial
* Restriction: only getting the current time as a Unix epoch and converting it to a number is supported. Ensure storage on enough bits.
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
* Implementation complexity: easy with restriction
* Workaround: function, multiple if

### Immediately invoked anonymous function expression

* Verdict: Recommended
* Reason: Its desirable qualities useful for modules and userscript (userjs) within a web browser.
* Restrictions: not all syntax may be supported and in not every position within an expression. This should work: `(function(){})()`

### Environment capturing by a function definition

* Verdict: Desirable, but only partially supported
* Use case: state encapsulation for object oriented programming, Currying for functional programming
* Restrictions: to avoid reference cycles, a runtime may make a shallow copy of the environment from above the function definition, not including itself.
* Workaround: Use a C-like function definition order within the file. Recursion needs to be worked around by passing in a self-reference for the function. `Function` and `eval` can be fully mitigated, but may prove as an alternative.

### Variable initializer

* Verdict: Desirable, partially supported
* Reason: Occurs frequently, easy to implement.
* Restriction: single variable and single initializer supported as usually recommended by style guides to maintain one statement per line.

### Exceptions throw-catch, throw

* Verdict: desirable, limited support
* Restriction: no classes, catch may be implemented as a restricted kind of environment
* Reason: Useful for detecting error conditions of standard functions.

### Field accessor chaining

* Verdict: desirable, limited support
* Reason: very common in code, easy to implement
* Restriction: chaining starting from a variable should be supported, but may not support interspersing function calls

## Unsupported

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
* Workaround: return, if, altered loop condition

### varargs

* Verdict: not supported
* Implementation complexity: intermediate (function arguments object, call, apply)
* Incidence rate: rare
* Workaround: Array

### block scope environment const, let

* Verdict: not supported
* Implementation complexity: complicated
* Incidence rate: would be often useful
* Reason: would increase memory pressure, would be less error prone for newcomers than the function scope `var`
* Workaround: function

### switch-case-default

* Verdict: not supported
* Implementation complexity: intermediate
* Incidence rate: rare
* Workaround: if-else

### Literal object notation

* Verdict: not supported, desirable at times
* Implementation complexity: straight forward
* Incidence rate: intermediate
* Workaround: easy, create an intermediate object and add the value via an accessor

### Literal array notation

* Verdict: not supported, desirable at times
* Implementation complexity: straight forward
* Incidence rate: intermediate
* Workaround: easy, create an intermediate array and add the value via an index

### Reference cycles

* Verdict: Unsupported.
* Restriction: Avoid storing a reference within object `p` pointing to object `q` if there exists a directed path leading from `q` to `p`.
* Reason: Such a cycle would mandate a more complicated and less deterministic garbage collection scheme for collecting cycle specifically.
* Workaround: store the key of a given object within a common map instead of a direct reference. Inspect carefully which environment a given function definition captures and alter the ordering or use additional encapsulation to hide stray paths.

### Prototype

* Verdict: avoid in user code
* Restriction: the implementation may use it internally but may not expose it to user code
* Reason: implementation is difficult, slow and uses more memory. Also considered bad practice for most use cases.
* Workaround: emulate regular inheritance by function expressions or chain only pure functions where applicable
