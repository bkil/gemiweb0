# JavaScript alternative subset grammars

You should separate each implemented variant on a branch or file before moving on to the next level. Log time you spend on it so we can compare power to weight ratio. Feel free to propose new variants that could serve as good milestones for beginners.

Note that this is a work in progress file. The headings will be renamed. Some of the variants may be removed.

## Warm-up

### Level lisp expr

```
program: [ <fun> ]* <expr> [ ';' ]?
fun: 'function' <id> '(' [<id> [ ',' <id>]* ]? ')' '{' [ <expr> ';' ]* 'return' <expr> [ ';' ]? '}'
expr: <id> [ <iExpr> ]? | <int> [ <nExpr> ]?
iExpr: '(' [ <expr> [ ',' <expr>]* ]? ')' | <nExpr>
nExpr: <op> <term> | '?' <expr> ':' <expr>
term: <int> | <id>
op: + | - | '<'
int = [0-9]+
id = [a-zA-Z_.]+
```

### Level lisp anonymous function

```
program: <expr>
expr: <fun> | <id> [ <iExpr> ]? | <cTerm> [ <nExpr> ]?
fun: 'function' '(' [<id> [ ',' <id>]* ]? ')' '{' 'return' <expr> '}'
iExpr: '(' [ <expr> [ ',' <expr>]* ]? ')' | <nExpr>
nExpr: <op> <term> | '?' <expr> ':' <expr>
term: <id> | <cTerm>
cTerm: '(' <expr> ')' | <int>
op: + | - | '<'
int = [0-9]+
id = 'Array' | 'document.write' | 'console.log' | [a-zA-Z_.]+
```

### Level lisp if

```
program: <stms>
stmBody: { <stms> }
stms: <stm> [; <stm>]*
stm: if ( <expr> ) <stmBody> else <stmBody> | <expr>
expr: <funExpr> | <term> [<op> <term>]?
funExpr: ( function ( [<id> [, <id>]* ]? ) { <stms> ; return <expr> } ) ( [ <expr> [, <expr>]* ]? )
term: <int> | <id>
op: + | - | '<'
int = [0-9]+
id = [a-zA-Z_.]+
```

### Level bf

```
program: <statements>
statements: <statement> <moreStatements>
moreStatements: ';' <statements> | ''
statement: 'while(v[i]){' <statements> '}' | [ console.log | document.write ] '(String.fromCharCode(v[i]))' | var ' ' [ v | i | j ] | <assignment>
assignment: v [ '=new Array' | '[i]=' [ '(v[i]|0)' [ '+' | '-' ] 1 | 'form.text.value.charCodeAt(j)|0' ] ] | [ i | j ] [ '=0' | '++' | '--' ]
```

Not supported:

* whitespace
* optional semicolons
* arbitrary variables
* additional parenthesis

### Level 0

```
program: <stms>
stmBody: { <stms> }
stms: <stm> [; <stm>]*
stm: while ( <expr> ) <stmBody> | <funExpr> | <id> <iStm>
funExpr: function <id> ( ) <stmBody>
iStm: '=' <expr> | ( [ <expr> ]? )
expr: <term> [<op> <term>]?
term: <int> | <id>
op: + | - | '<'
int = [0-9]+
id = [a-zA-Z_.]+
```

### Level 0 array

```
program: <stms>
stmBody: { <stms> }
stms: <stm> [; <stm>]*
stm: while ( <expr> ) <stmBody> | <funExpr> | <id> <iStm>
funExpr: function <id> ( ) <stmBody>
iStm: [ '[' <expr> ']' ]? = <expr> | ( [ <expr> ]? )
expr: <term> [<op> <term>]?
term: <int> | new Array | <id> [ '[' <expr> ']' ]?
op: + | - | '<'
int = [0-9]+
id = [a-zA-Z_.]+
```

### Level 0 rec array

```
program: <stms>
stmBody: { <stms> }
stms: <stm> [; <stm>]*
stm: while ( <expr> ) <stmBody> | <funExpr> | <id> <iStm>
funExpr: function <id> ( ) <stmBody>
iStm: <idx> <iRest>
idx: [ '[' <expr> ']' | . <id> ]*
iRest: = <expr> | ( [ <expr> ]? )
expr: <term> [<op> <term>]?
term: <int> | new Array | new Object | <id> [ '[' <expr> ']' ]?
op: + | - | '<'
int = [0-9]+
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 1

```
program: <stms>
stmBody: { <stms> }
stms: <stm> [; <stm>]*
stm: while ( <expr> ) <stmBody> | <funExpr> | <id> <iStm>
funExpr: function <id> ( ) <stmBody>
iStm: = <expr> | ( [ <expr> ]? )
expr: <term> [<op> <term>]?
term: <int> | <string> | <id>
op: + | - | & | '|' | '<'
int = [0-9]+
string = '([^'])*'
id = [a-zA-Z_.]+
```

### Level 2

```
program: <stms>
stmBody: { <stms> }
stms: <stm> [; <stm>]*
stm: while ( <expr> ) <stmBody> | <funExpr> | <expr>
funExpr: function <id> ( ) <stmBody>
expr: <lExpr> | <id> <iExpr>
lExpr: <lTerm> [<op> <term>]?
iExpr: [<op> <term>]? | = <expr> | ( [ <expr> ]? )
term: <lTerm> | <id>
lTerm: <int> | <string>
op: + | - | & | '|' | '<'
int = [0-9]+
string = '([^'])*'
id = [a-zA-Z_.]+
```

### Level 3

```
program: <stms>
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [else <stmBody>]? | while ( <expr> ) <stmBody> | <expr> | var <id>
stmBody: { <stms> }
expr: funExpr | term [<op> <term>]?
funExpr: function <id> ( <params> ) { <stms> [ ; return <expr> ]? }
params: [ <id> [, <id>]* ]?
term: <int> | <string> | ( <expr> ) | <id> = <expr> | <id> ( <args> ) | <id>
op: + | - | & | '|' | '<' | ==
args: [ <expr> [, <expr>]* ]?
int = [1-9][0-9]*
string = '([^'\\]|\\.)*'
id = ([a-zA-Z_][a-zA-Z_0-9]*\.)*[a-zA-Z_][a-zA-Z_0-9]*
```

### Level 4

```
program: <stms>
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [else <stmBody>]? | while ( <expr> ) <stmBody> | <expr>
stmBody: { <stms> } | <stm>
expr: <funExpr> | [ ! ]? term [<op> <term>]?
funExpr: function <id> ( <params> ) <funBody>
funBody: { <funStm> [; <funStm>]* [ ; return <expr> ]? }
funStm: var <id> | <stm>
params: [ <id> [, <id>]* ]?
term: <int> | <string> | ( <expr> ) | <id> = <expr> | <id> ( <args> ) | <id>
op: + | - | & | '|' | '<' | ==
args: [ <expr> [, <expr>]* ]?
int = [1-9][0-9]*
string = '([^'\\]|\\.)*'
id = ([a-zA-Z_][a-zA-Z_0-9]*\.)*[a-zA-Z_][a-zA-Z_0-9]*
```

## Useful

### Level 7 assembly 0

```
program: <arrId> '=' new Array ';' [ <tstm> ';' ]* <expr>
tstm: function <funcId> '(' ')' <body> | <mstm>
mstm: if '(' <expr> ')' <body> | while '(' <expr> ')' <body> | <cstm>
body: '{' <mstm> [ ';' <mstm> ]* '}'
cstm: <builtin> | <funcId> '(' ')' | <arrId> <idx> '=' <expr> | <intId> '=' <expr>
expr: <term> [ <op> <term> ]?
term: <int> | <intId> | '(' [ 'form.text.value.charCodeAt(' <expr> ')' | <arrId> <idx> | '(' <term> '/' <term> ')' ] '|' '0' ')'
idx: '[' <expr> ']'
op: '+' | '-' | '*' | '%' | '<' | '>' | '<=' | '>=' | '^' | '|' | '&' | '<<' | '>>' | '>>>' | '===' | '!=='
builtin: 'console.log(String.fromCharCode(' <expr> '))'
arrId = _
intId = [a-z]
funcId = [a-zA-Z_]{2,8}
int = [0-9]+
```

Notes:

* Whitespace (at least newlines between statements) and comments (/* ... */) must be supported
* Standard input must not be consumed multiple times or out of sequence
* Integer variables may already be initialized to zero, the array may already be allocated and zeroed
* You must not access a negative array index or read a value before initializing it, but both may return zero
* Each function must be defined above the point of invocation
* You may assume that the interpreter stores the first few variables in CPU registers, so utilize them in lexicographical order

### Level 7 assembly 1

```
program: [ '\'use strict\'' ; [ var [ <arrId> | <intId> ] ; ]* <arrId> '=' new Array ; [ <tstm> ; ]* ]? <expr> [;]?
tstm: function <funcId> ( [ A [ , B [ , C [ , D [ , E [ , F [ , G [ , H [ , I [ , J [ , K [ , L [ , M [ , N [ , O [ , P [ , Q [ , R [ , S [ , T [ , U [ , V [ , W [ , X [ , Y [ , Z  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]? ) <fBody> | <mstm>
mstm: if '(' <expr> ')' <mBody> [ else <mBody> ]? | while ( <expr> ) <mBody> | <expr>
fstm: if '(' <expr> ')' <fBody> [ else <fBody> ]? | while ( <expr> ) <fBody> | return <expr> | <expr>
mBody: { [ <mstm> [ ; <mstm> ]* ]? [;]? }
fBody: { [ <fstm> [ ; <fstm> ]* ; ]? return <expr> [;]? }
expr: <term> [ <op> <term> ]* | '(' <term> '/' <term> ')' '|' '0'
term: <int> | <builtin> | <funcId> '(' [ <expr> [, <expr>]* ]? ')' | [ <intId> | <parId> ] [ <rhs> ]? | <arrId> <idx> <rhs> | '(' [ 'form.text.value.charCodeAt(' <expr> ')|0' | <arrId> <idx> '|0' | <expr> ] ')'
rhs: '=' <expr>
idx: '[' <expr> ']'
op: '+' | '-' | '*' | '%' | '<' | '>' | '<=' | '>=' | '^' | '|' | '&' | '<<' | '>>' | '>>>' | '||' | '&&' | '===' | '!=='
builtin: 'console.log(String.fromCharCode(' <expr> '))'
arrId = _
intId = [a-z]
parId = [A-Z]
funcId = [a-zA-Z_][0-9a-zA-Z_]{1,9}[0-9]?
int = [0-9]+
```

Notes:

* In expr, only the same operator can be repeated within the same group (i.e., without using parenthesis)
* Whitespace and comments must be supported
* Standard input must not be consumed multiple times or out of sequence
* Variable declaration may not be enforced, but you must not access a variable before declaring and initializing it
* Integer variables may already be initialized to zero, the array may already be allocated and zeroed
* You must not assign any single `funcId` identifier multiple times
* You must not access a negative array index or read a value before initializing it, but both may return zero
* You must not access parameters outside a function or those which you have not declared or given as argument
* You must not invoke a function with a different number of arguments than the number of parameters in the function definition
* Each function must be defined above the point of invocation
* You may assume that the interpreter stores the first few variables and the first few function parameters in CPU registers, so utilize them in lexicographical order
* The function name may be capped to 10 letters and a digit (packed as base64 and BCD to fit 64 bits)

### Level 7 assembly 2

```
program: [ '\'use strict\'' ; [ var [ <arrId> | <intId> ] ; ]* <arrId> '=' new Array ; [ <tstm> ; ]* ]? <expr> [;]?
tstm: function <funcId> ( [ A [ , B [ , C [ , D [ , E [ , F [ , G [ , H [ , I [ , J [ , K [ , L [ , M [ , N [ , O [ , P [ , Q [ , R [ , S [ , T [ , U [ , V [ , W [ , X [ , Y [ , Z  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]? ) <fBody> | <mstm>
mstm: if '(' <expr> ')' <mBody> [ else <mBody> ]? | while ( <expr> ) <mBody> | do <mBody> while ( <expr> ) | for ( [ <expr> ]? ; [ <expr> ]? ; [ <expr> ]? ) <mBody> | switch ( <expr> ) { [ case <expr>: <mBody> ]* [ default: <mBody> ]? } | <cstm>
fstm: if '(' <expr> ')' <fBody> [ else <fBody> ]? | while ( <expr> ) <fBody> | do <fBody> while ( <expr> ) | for ( [ <expr> ]? ; [ <expr> ]? ; [ <expr> ]? ) <fBody> | switch ( <expr> ) { [ case <expr>: <fBody> ]* [ default: <fBody> ]? } | return <expr> | <cstm>
cstm: break | continue | <expr>
mBody: { [ <mstm> [ ; <mstm> ]* ]? [;]? }
fBody: { [ <fstm> [ ; <fstm> ]* ; ]? return <expr> [;]? }
expr: <qexpr> [ '?' <qexpr> ':' <qexpr> ]?
qexpr: <uterm> [ [ <opRel> <uterm> ]* ]? | '(' <uterm> '/' <uterm> ')' '|' '0'
uterm: [ '++' | '--' ] [ <intId> | <parId> | <arrId> <idx> ] | [ [ '!' | '~' | '-' ]? <term> ]
term: <int> | <builtin> | <funcId> '(' [ <expr> [, <expr>]* ]? ')' | [ <intId> | <parId> ] [ <rhs> ]? | <arrId> <idx> <rhs> | <bracketed>
bracketed: '(' [ 'form.text.value.charCodeAt(' <expr> ')|0' | <arrId> <idx> '|0' | <expr> [ ',' <expr> ]* ] ')'
rhs: '++' | '--' | [ <op> ]? '=' <expr>
idx: '[' <expr> ']'
op: '+' | '-' | '*' | % | ^ | '|' | '&' | '<<' | '>>' | '>>>' | '||' | '&&'
opRel: <op> | '<' | '>' | '<=' | '>=' | '===' | '!=='
builtin: 'console.log(String.fromCharCode(' <expr> '))'
arrId = _
intId = [a-z]
parId = [A-Z]
funcId = [a-zA-Z_][0-9a-zA-Z_]{1,9}[0-9]?
int = [0-9]+
```

Notes:

* In expr, only the same `opRel` operator can be repeated within the same group (i.e., without using parenthesis)
* Whitespace and comments must be supported
* Standard input must not be consumed multiple times or out of sequence
* Variable declaration may not be enforced, but you must not access a variable before declaring and initializing it
* Integer variables may already be initialized to zero, the array may already be allocated and zeroed
* You must not assign any single `funcId` identifier multiple times
* You must not access a negative array index or read a value before initializing it, but both may return zero
* You must not access parameters outside a function or those which you have not declared or given as argument
* You must not invoke a function with a different number of arguments than the number of parameters in the function definition
* Each function must be defined above the point of invocation
* `continue` must not be used outside a loop
* `break` must not be used outside a loop or a switch
* You may assume that the interpreter stores the first few variables and the first few function parameters in CPU registers, so utilize them in lexicographical order
* The function name may be capped to 10 letters and a digit (packed as base64 and BCD to fit 64 bits)

### Level 7 assembly 3

```
program: [ '\'use strict\'' ; [ var [ <arrId> | <intId> | <constInit> ] ; ]* <arrId> '=' new Array ; [ <tstm> ; ]* ]? <expr> [;]?
constInit: <constId> '=' <cexpr> | <strId> '=' <string> | <litArrId> '=' '[' [ <cexpr> [ ',' <cexpr> ]* ]? ']'
tstm: function <funcId> ( [ A [ , B [ , C [ , D [ , E [ , F [ , G [ , H [ , I [ , J [ , K [ , L [ , M [ , N [ , O [ , P [ , Q [ , R [ , S [ , T [ , U [ , V [ , W [ , X [ , Y [ , Z  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]?  ]? ) <fBody> | <mstm>
mstm: if '(' <expr> ')' <mBody> [ else <mBody> ]? | while ( <expr> ) <mBody> | do <mBody> while ( <expr> ) | for ( [ <expr> ]? ; [ <expr> ]? ; [ <expr> ]? ) <mBody> | switch ( <expr> ) { [ case <expr>: <mBody> ]* [ default: <mBody> ]? } | <cstm>
fstm: if '(' <expr> ')' <fBody> [ else <fBody> ]? | while ( <expr> ) <fBody> | do <fBody> while ( <expr> ) | for ( [ <expr> ]? ; [ <expr> ]? ; [ <expr> ]? ) <fBody> | switch ( <expr> ) { [ case <expr>: <fBody> ]* [ default: <fBody> ]? } | return <expr> | <cstm>
cstm: break | continue | <expr>
mBody: { [ <mstm> [ ; <mstm> ]* ]? [;]? }
fBody: { [ <fstm> [ ; <fstm> ]* ; ]? return <expr> [;]? }
expr: [ [ '!' | '~' | '-' ]? <term> ] [ '?' <expr> ':' <expr> | [ <opRel> <term> ]* ]? | '(' <term> '/' <term> ')' '|' '0'
term: <int> | <builtin> | [ <strId> | <litArrId> ] '.length' | <funcId> '(' [ <expr> [, <expr>]* ]? ')' | <constId> | [ <intId> | <parId> ] [ <rhs> ]? | <arrId> <idx> <rhs> | <bracketed>
bracketed: '(' [ [ 'form.text.value' | <strId> ] '.charCodeAt(' <expr> ')|0' | [ <arrId> | <litArrId> ] <idx> '|0' | <expr> [ ',' <expr> ]* ] ')'
cexpr: [ [ '!' | '~' | '-' ]? <cterm> ] [ '?' <cexpr> ':' <cexpr> | [ <opRel> <cterm> ]* ]? | '(' <cterm> '/' <cterm> ')' '|' '0'
cterm: <int> | [ <strId> | <litArrId> ] '.length' | <constId> | <cbracketed>
cbracketed: '(' [ <strId> '.charCodeAt(' <cexpr> ')|0' | <litArrId> <idx> '|0' | <cexpr> ] ')'
rhs: '++' | '--' | [ <op> ]? '=' <expr>
idx: '[' <expr> ']'
op: '+' | '-' | '*' | '%' | '^' | '|' | '&' | '<<' | '>>' | '>>>' | '||' | '&&'
opRel: <op> | '<' | '>' | '<=' | '>=' | '===' | '!=='
builtin: 'console.log(String.fromCharCode(' <expr> '))'
arrId = _
intId = [a-z]
parId = [A-Z]
constId = [A-Z][0-9a-zA-Z_]{1,9}[0-9]?
strId = _s[0-9a-zA-Z_]{1,10}[0-9]?
litArrId = _a[0-9a-zA-Z_]{1,10}[0-9]?
funcId = [a-z][0-9a-zA-Z_]{1,9}[0-9]?
string = '[^'\\]*'|"[^"\\]*"
int = [0-9]+
```

Notes:

* In `expr` and `cexpr`, only the same `opRel` operator can be repeated within the same group (i.e., without using parenthesis)
* Whitespace and comments must be supported
* Standard input must not be consumed multiple times or out of sequence
* Variable declaration may not be enforced, but you must not access a variable before declaring and initializing it
* Integer variables may already be initialized to zero, the array may already be allocated and zeroed
* You must not assign any single `constId`, `strId`, `litArrId` and `funcId` identifier multiple times
* You must not access a negative array index or read a value before initializing it, but both may return zero
* You must not access parameters outside a function or those which you have not declared or given as argument
* You must not invoke a function with a different number of arguments than the number of parameters in the function definition
* Each function must be defined above the point of invocation
* `continue` must not be used outside a loop
* `break` must not be used outside a loop or a switch
* You may assume that the interpreter stores the first few variables and the first few function parameters in CPU registers, so utilize them in lexicographical order
* The function name may be capped to 10 letters and a digit (packed as base64 and BCD to fit 64 bits)

## Metacircular

### Level 5 fun expr array

```
program: <stms>
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [else <stmBody>]? | while ( <expr> ) <stmBody> | <expr>
stmBody: { <stms> } | <stm>
expr: <funExpr> | [ ! ]? term [<op> <term>]?
funExpr: function <id> ( <params> ) <funBody>
funBody: { <funStm> [; <funStm>]* [ ; return <expr> ]? }
funStm: var <id> | <stm>
params: [ <id> [, <id>]* ]?
term: <int> | <string> | new <id> | ( <expr> ) | <id> <idx> [ <iTerm> ]?
iTerm: = <expr> | ( <args> )
idx: [ '[' <expr> ']' | . <id> ]*
op: + | - | & | '|' | '<' | ==
args: [ <expr> [, <expr>]* ]?
int = [1-9][0-9]*
string = '([^'\\]|\\.)*'
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 6

```
program: <stms> [;]?
stmBody: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [ else <stmBody> ]? | while ( <expr> ) <stmBody> | try <stmBody> catch ( <id> ) <stmBody> | var <id> | function <function> | <expr>
function: <id> ( [ <id> [, <id>]* ]? ) { <stms> [ ; return <expr> ]? [;]? }
expr: <term> [ <op> <term> ]?
term: undefined | null | <int> | <string> | new <id> | [ ! ]? <id> <idx> [ <iTerm> ]?
iTerm: '=' <expr> | ( [ <expr> [, <expr>]* ]? )
idx: [ '[' <expr> ']' | . <id> ]*
op: + | - | '|' | & | '>>' | '<' | === | ==
int = -?[1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 6 b

```
program: <stms> [;]?
stmBody: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: while ( <expr> ) <stmBody> | function <function> | <expr>
function: <id> ( ) <stmBody>
expr: <iTerm> <eExpr> | <lTerm> <eExpr>
eExpr: [ <op> <term> ]?
term: <iTerm> | <lTerm>
lTerm: <int> | <string> | ! <id> <sTerm>
iTerm: new <id> | <id> <sTerm>
sTerm: <idx> [ <rhs> ]?
rhs: '=' <expr> | ( [ <expr> ]? )
idx: [ '[' <expr> ']' | . <id> ]?
op: + | - | '<'
int = [1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 6 c

```
program: <stms> [;]?
stmBody: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: while ( <expr> ) <stmBody> | function <function> | return <expr> | <expr>
function: <id> ( ) <stmBody>
expr: <iTerm> <eExpr> | <lTerm> <eExpr>
eExpr: [ <op> <term> ]?
term: <iTerm> | <lTerm>
lTerm: <int> | <string> | ! <id> <sTerm>
iTerm: undefined | new <id> | <id> <sTerm>
sTerm: <idx> [ <rhs> ]?
rhs: '=' <expr> | ( [ <expr> ]? )
idx: [ '[' <expr> ']' | . <id> ]?
op: + | - | '<' | '==='
int = [1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 6 d

```
program: <stms> [;]?
stmBody: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: while ( <expr> ) <stmBody> | function <id> ( [ <id> ]? ) <stmBody> | return <expr> | <expr>
expr: <term> [ <op> <term> ]?
op: + | - | '<' | '==='
term: <int> | <string> | undefined | new <cls> | [ '!' ]? <id> <idx> <rhs>
cls: Object
idx: [ '[' <expr> ']' | . <id> ]?
rhs: [ '=' <expr> | ( [ <expr> ]? ) ]?
int = [1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 6 e

```
program: <stms> [;]?
stmBody: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: while ( <expr> ) <stmBody> | var <id> | function <id> ( [ <id> ]? ) <stmBody> | return <expr> | try <stmBody> catch ( <id> ) <stmBody> | throw <expr> | <expr>
expr: <term> [ <op> <term> ]?
op: + | - | '<' | '==='
term: <int> | <string> | undefined | new <cls> | [ '!' ]? <id> <idx> <rhs>
cls: Object
idx: [ '[' <expr> ']' | . <id> ]?
rhs: [ '=' <expr> | ( [ <expr> ]? ) ]?
int = [1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 6 f

```
program: <stms>
stmBody: { <stms> }
stms: [ [ <stmu> ; | <stmb> [;]? ]* [ <stmu> | <stmb> ] [;]? ]*
stmu: var <id> | return <expr> | throw <expr> | <expr>
stmb: if ( <expr> ) <stmBody> [ else <stmBody> ]? | while ( <expr> ) <stmBody> | function <id> ( [ <id> ]? ) <stmBody> | try <stmBody> catch ( <id> ) <stmBody>
expr: <term> [ <op> <term> ]?
op: + | - | '|' | & | '>>' | '<' | === | ==
term: <int> | <string> | undefined | null | new <cls> | [ '!' ]? <id> <idx> <rhs>
cls: Object | Array
idx: [ '[' <expr> ']' | . <id> ]?
rhs: [ '=' <expr> | ( [ <expr> ]? ) ]?
int = -?[1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 7

```
program: <stms> [;]?
stmBody: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [ else <stmBody> ]? | while ( <expr> ) <stmBody> | var <id> | function <function> | return <expr> | try <stmBody> catch ( <id> ) <stmBody> | throw <expr> | <expr>
function: <id> ( [ <id> [, <id>]* ]? ) <stmBody>
expr: <iTerm> <eExpr> | <lTerm> <eExpr>
eExpr: [ <op> <term> ]?
term: <iTerm> | <lTerm>
lTerm: <int> | <string> | ! <id> <sTerm>
iTerm: undefined | null | new <id> | <id> <sTerm>
sTerm: <idx> [ <rhs> ]?
rhs: '=' <expr> | ( [ <expr> [, <expr>]* ]? )
idx: [ '[' <expr> ']' | . <id> ]?
op: + | - | '|' | & | '>>' | '<' | === | ==
int = -?[1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 7 b

```
program: <stms> [;]?
stmBody: <stmBrace> | <stm>
stmBrace: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [ else <stmBody> ]? | while ( <expr> ) <stmBody> | var <id> [ '=' <expr> ]? | function <id> <function> | return <expr> | try <stmBrace> catch ( <id> ) <stmBrace> | throw <expr> | <expr>
expr: function <function> | <iTerm> <eExpr> | <lTerm> <eExpr>
function: ( [ <id> [, <id>]* ]? ) <stmBrace>
eExpr: [ <op> <term> ]?
term: <iTerm> | <lTerm>
lTerm: <int> | <string> | ! <term> | ~ <term> | '(' <expr> ')'
iTerm: undefined | null | new Object | new Array | <id> <sTerm>
sTerm: <idx> [ <rhs> ]?
rhs: '=' <expr> | ( [ <expr> [, <expr>]* ]? )
idx: [ '[' <expr> ']' | . <id> ]?
op: + | - | '*' | / | % | '<' | '>' | '<=' | '>=' | ^ | '|' | '&' | '<<' | '>>' | '||' | '&&' | === | !==
int = -?[1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 7 c

```
program: <stms> [;]?
stmBody: <stmBrace> | <stm>
stmBrace: { <stms> [;]? }
stms: [ <stm> [; <stm>]* ]?
stm: if ( <expr> ) <stmBody> [ else <stmBody> ]? | while ( <expr> ) <stmBody> | for ( <id> in <expr> ) <stmBody> | var <id> [ '=' <expr> ]? | function <id> <function> | return <expr> | try <stmBrace> catch ( <id> ) <stmBrace> | throw <expr> | <expr>
expr: function <function> | <iTerm> <eExpr> | <lTerm> <eExpr>
function: ( [ <id> [, <id>]* ]? ) <stmBrace>
eExpr: [ <op> <term> ]*
term: <iTerm> | <lTerm>
lTerm: <int> | <string> | [ ! | ~ | - ] <term> | '(' <expr> ')' [ <args> ]?
iTerm: undefined | null | NaN | new Object | new Array | new Date | typeof <expr> | <id> <sTerm>
sTerm: <idx> [ <rhs> ]?
rhs: '=' <expr> | <args>
args: '(' [ <expr> [, <expr>]* ]? ')'
idx: [ '[' <expr> ']' | . <id> ]*
op: + | - | '*' | / | % | '<' | '>' | '<=' | '>=' | ^ | '|' | '&' | '<<' | '>>' | '>>>' | '||' | '&&' | === | !==
int = -?[1-9][0-9]*
string = '[^'\\]*'|"[^"\\]*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

Notes:

* In eExpr, only the same operator can be repeated within the same group (i.e., without using parenthesis)

### Level 8

```
program: <stms>
stms: [ <stm> [; <stm>]* [;]? ]?
stmBody: <stmBrace> | <stm>
stmBrace: { <stms> }
stm: if ( <expr> ) <stmBody> [ else <stmBody> ]? | while ( <expr> ) <stmBody> | do <stmBody> while ( <expr> ) | delete <id> <idx> | <goto> | <expr>
goto: try <stmBrace> catch ( <id> ) <stmBrace> | throw <expr> | return <expr> | break | continue | switch ( <expr> ) { [ case <lit>: <stms> ]* [ default: <stms> ]? }
expr: <funExpr> | <uTerm> [ '?' <expr> : <expr> | <op> <uTerm> ]?
funExpr: function [ <id> ]? ( [ <id> [, <id>]* ]? ) { <funStm> [; <funStm>]* [;]? }
funStm: var <varInit> [, <varInit> ]* | <stm>
varInit: <id> [ '=' <expr> ]?
uTerm: [ ! | ~ | - ]? <term>
term: <lit> | new <id> [ <args> ]? | typeof <id> <idx> | ( <expr> ) [ <args> ]? | <id> <idx> [ <iTerm> ]?
lit: undefined | null | <num> | <string>
iTerm: '=' <expr> | <args> | instanceof <id>
idx: [ '[' <expr> ']' | . <id> ]*
op: + | - | '*' | / | % | '<' | '>' | '<=' | '>=' | ^ | '|' | '&' | '<<' | '>>' | '>>>' | '||' | '&&' | === | !== | == | !=
args: ( [ <expr> [, <expr>]* ]? )
num: <double> | <int>
double = -?[1-9][0-9]*\.[0-9]+ | NaN
int = (-?[1-9][0-9]*|0x[0-9a-fA-F]+)
string = '([^'\\]|\\n|\\t|\\.)*'|"([^"\\]|\\n|\\t|\\.)*"
id = [a-zA-Z_][a-zA-Z_0-9]*
```

### Level 9 a

* comments
* instance method: .length, charCodeAt
* static methods: String.fromCharCode
* new Array
* new Object

### Level 9 b

* []
* {}
* associative operators with precedence
* ?? null coalescing
* .?
* defining general properties, accessors
* .prototype inheritance
