# JavaScript alternative subset grammars

Note that this is a work in progress file.
The headings will be renamed.
Some of the variants may be removed.
Feel free to propose new variants that could serve as good milestones for beginners.
If you implement a variant completely, please save it as a branch or a separate file before moving to the next level and log the additional time you spent on implementing it so we could better gauge the power to weight ratio.

## Warm-up

### Level lisp

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
term: <int> | { } | <id> [ '[' <expr> ']' ]?
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
term: <int> | { } | <id> [ '[' <expr> ']' ]?
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
iTerm: undefined | null | NaN | new Object | new Array | typeof <expr> | <id> <sTerm>
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
