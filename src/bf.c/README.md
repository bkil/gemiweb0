# Brainfuck JavaScript subset

## Introduction

This is an absolute minimal JavaScript subset that corresponds to the capabilities of Brainfuck. The formal grammar definition for the language subset is available:

[../../doc/js-grammar.md](../../doc/js-grammar.md#Level-bf)

Scrolling through the test cases also illustrates the syntax:

[./test-vm.c](./test-vm.c)

## Implementation

Standard input is handled similarly as if you were handling a form submit button, while standard output can be done through `console.log` (as on a server) or `document.write` (like a browser). The API could be easily extended on demand, although further development of the proof of concept seems uncalled for.

This one takes only a few hundred lines of C code - originally 300 SLOC, resulting in ~1400 bytes of gzip'ped compiled object code. Its bulk stems from offering a dynamically growing array and extensive diagnostic warning message generation that's still not exhaustive, though. Assuming input resulting from flawless code generation, most of the safeties could even be removed. See the following example for web browsers:

[rot1.html](rot1.html)

Here is a syntax checker for its grammar implemented in HTML0/JS0:

[../check/bf.html](../check/bf.html)

## Motivation

Brainfuck is one of the smallest Turing-complete programming languages:

[https://en.wikipedia.org/wiki/Brainfuck](https://en.wikipedia.org/wiki/Brainfuck)

Many existing projects are available for compiling general programs originally written in any language to Brainfuck mechanically, for example:

[https://github.com/shinh/elvm](https://github.com/shinh/elvm)

## Outlook

We have thus shown in the mathematical sense that such a runtime is possible to implement within a few hours that can execute fully functional apps that also work the same in modern web browsers.

Any further levels of JavaScript subsets are looking for the answer to how we can extend such a subset up to a level where it is plausible to program in directly without using any transpilers, capping the total effort to the ball park of a few weekends.
