# Development

## Types of tests

### Unit

* language: native C
* purpose: fuzz semantic invariants, make contracts explicit, defensive error handling, improve white box coverage
* granularity: per private function of implementation detail
* status: none

### Basic assurance

* language: native C
* purpose: ensure a small subset of JavaScript0 works on happy path to enable bootstrap of the JavaScript0 module testing framework
* alternative: test source may be generated from test cases stored in an abstract data structure shared with the module tests
* granularity: using external API calls
* status: TODO separate from module tests

### Module

* language: native C (TODO: JavaScript0)
* purpose: pure functions with no side effect that are safe to restart and can execute in parallel, each construct within small, isolated program eval snippet
* granularity: using external API calls
* test-vm.c

### System

* language: shell
* purpose: assert on properties if mocking and abstraction dedicated for testing would weigh more than the implementation
* granularity: one or more instances of the main runtime interpreter binary
* focus areas: standard input, standard output, file, network
* systest.sh ./js0

### Smoke

* language: native C or JavaScript0
* purpose: exclude certain kinds of ill side effects without exhaustive assertions, improve coverage via white box
* test-smoke.c
