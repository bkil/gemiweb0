# HTTP subset specification

Cover as little of it as possible to correspond to gemini while remaining compatible with most free hosting providers and existing web browsers. Allow implementing all targeted user application.

The following restrictions are non-normative and being worked on pending the result of proof of concepts.

## HTTP common

PATH: "[^? ]*" [ "?" PARAMS ]?

PARAMS: [ KEY "=" VALUE [ "&" KEY "=" VALUE ]* ]?

KEY: "[A-Za-z_]+"

VALUE: [^& ]*

ORIGIN: HOSTNAME ":" PORT

PORT: "[0-9]+"

LENGTH: [0-9]+

DATA: .*?

## GET request

REQUEST: "GET " PATH "HTTP/1.1\r\nHost: " ORIGIN "\r\n" HEADER "\r\n"

HEADER: [ [ Accept | Cookie | Authorization ] ": " DATA "\r\n" ]*

## POST urlencoded request

REQUEST: "POST " PATH "HTTP/1.1\r\nHost: " ORIGIN "\r\nContent-Type: application/x-www-form-urlencoded "\r\n" HEADER "\r\n" PARAMS

HEADER: [ [ "Content-Length: " LENGTH | [ Cookie | Authorization ] ": " DATA ] "\r\n" ]*

## POST form request

REQUEST: "POST " PATH "HTTP/1.1\r\nHost: " ORIGIN "\r\nContent-Type: multipart/form-data;boundary=\"" BOUNDARY "\"\r\n" HEADER "\r\n" BODY

HEADER: [ [ Cookie | Authorization ] ": " DATA "\r\n" ]*

BODY: "--" BOUNDARY "\r\nContent-Disposition: form-data; name=\"" KEY "\"" [ "; filename=\"" KEY "\"" ]? "\r\nContent-Length: " LENGTH "\r\n\r\n" DATA "\r\n--" BOUNDARY "--\r\n"

BOUNDARY: "[^\"\r\n-]+"

## HTTP response

RESPONSE: [ 200 | 302 | 404 | 429 | 500 ] " .*?\r\n" HEADER "\r\n" BODY

HEADER: [ [ Transfer-Encoding: Chunked | Content-Type: text/html | [ Location | Set-Cookie ] ": " DATA ] "\r\n" ]*

BODY: CHUNKED | DATA

CHUNKED: [ "[0-9a-f]+\r\n" DATA ]* "0\r\n"

### HTML

See

* [html-choices.md](html-choices.md)
* [html-spec.md](html-spec.md)

## Related

### Simple implementation

* https://github.com/mvbasov/lWS/blob/master/app/src/main/java/net/basov/lws/ServerHandler.java

### Simple protocols

* [Titan extension](https://communitywiki.org/wiki/Titan)
* [iapetus extension](https://web.archive.org/web/20210925220953/codeberg.org/oppenlab/iapetus)
* [Mercury](https://portal.mozz.us/gemini/zaibatsu.circumlunar.space/~solderpunk/gemlog/the-mercury-protocol.gmi)
* [Spartan protocol](http://spartan.mozz.us/)
* [gemini+upload](https://alexschroeder.ch/wiki/Baschdels_spin_on_Gemini_uploading)
* [Guppy](https://github.com/dimkr/guppy-protocol/blob/main/guppy-spec.gmi)
* [Nex](https://nightfall.city/nex/info/specification.txt)
* http://portal.mozz.us/gemini/inimeg.space/specification.gmi
* http://scrollprotocol.us.to/
* http://www.and.org/texts/server-http
