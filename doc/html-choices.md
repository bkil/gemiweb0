# HTML restrictions

Explain some of the restrictions we impose to balance minimal implementation and being able to implement all targeted user applications.

## Mandatory

### script

* Verdict: partial, also allow src attribute
* Implementation complexity: high, but manageable in terms of cost to benefit
* Restriction: only JavaScript0 is allowed
* Incidence rate: high
* Use case: backend-optional computation, privacy, improving latency, reducing server hosting cost, logic can be changed by visitor
* Workaround: server side rendering
* Standard: NS2 for `script`, NS3 for `src` attribute

See:

* [js-spec.md](js-spec.md)
* [js-choices.md](js-choices.md)
* [js-grammar.md](js-grammar.md)

## Quality of life improvement

### noscript

* Verdict: discouraged
* Reason: use progressive enhancement instead
* Implementation complexity: trivial
* Use case: fallback when JavaScript is not implemented or disabled
* Workaround: greet with a "noscript" message and only hide it after the full JavaScript code has loaded successfully
* Standard: NS2

### javascript: URI

* Verdict: recommended
* Reason: the simplest alternative for client side interaction
* Incidence rate: very high
* Use case: client side interactions, form processing, validation, bookmarklets
* Implementation complexity: trivial
* Workaround: implement event handlers such as onclick and onsubmit or navigate to a URI pointing to (or submit a form targeting) an HTML containing JavaScript that dispatches upon loading, encode the link identifier and serialize the whole application state to the URI query or anchor
* Standard: NS2

## To research

### audio playback

* Verdict: partial
* Implementation complexity: high, platform dependent sound libraries
* Restriction: only uncompressed PCM wav codec
* Incidence rate: low
* Use case: web radio, lecture, push-to-talk conference call
* Workaround: download or pass to protocol handler, although it can't solve programmatic use cases

### inline links

* Verdict: probably supported
* Implementation complexity: low with footnotes on their own lines, intermediate when inline
* Drawback: does not map to gemini
* Incidence rate: very high
* Use case: buttons on planar game board within a (preformatted) table
* Workaround: put links on their own line

### table

* Verdict: probably unsupported
* Implementation complexity: high, layout
* Incidence rate: intermediate
* Use case: tabular data chart, game board
* Workaround: list, preformatted text

### images

* Verdict: probably unsupported
* Implementation complexity: very high, codecs, layout, rendering
* Drawback: more round trips if external
* Incidence rate: high
* Use case: photos, diagrams
* Workaround: download or pass to protocol handler

### iframe

* Verdict: probably unsupported
* Implementation complexity: high, isolate more state, nesting depth, frame busting
* Drawbacks: more round trips if external
* Incidence rate: low
* Use cases: third party integration, the only standard way for native JavaScript eval sandboxing within a code snippet pad
* Workaround: XMLHttpRequest

## Partial

## Unsupported
