# HTTP restrictions

## Mandatory

## Quality of life improvement

## To research

### XMLHttpRequest CORS

* Verdict: partial
* Implementation complexity: intermediate
* Restriction: only for unauthenticated public access (`Access-Control-Allow-Origin: *`)
* Use cases: third party integration
* Workaround: JSONP, custom CSS content embedding

### Content Security Policy

* Verdict: probably unsupported
* Implementation complexity: high
* Incidence rate: low where it would matter
* Use case: iframe sandbox of an online code snippet pad

### X-Frame-Ancestors

* Verdict: support
* Implementation complexity: low
* Incidence rate: high
* Use case: if iframe is also supported
* Workaround: none

## Partial

### Referrer policy

* Verdict: partial
* Implementation complexity: low
* Restriction: implement as little as required to authenticate against storage API of our targeted existing services
* Workaround: none

## Unsupported
