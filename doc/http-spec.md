# HTTP subset specification

Cover as little of it as possible to correspond to gemini while remaining compatible with most free hosting providers and existing web browsers. Allow implementing all targeted user application.

The following restrictions are non-normative and being worked on pending the result of proof of concepts.

## HTTP common

PATH: "[^? ]*" [ "?" PARAMS ]?

PARAMS: [ KEY [ "=" VALUE ]? ]? [ "&" [ KEY [ "=" VALUE ]? ]? ]*

KEY: [A-Za-z_]+

VALUE: "[^& ]*"

ORIGIN: HOSTNAME ":" PORT

PORT: [0-9]+

LENGTH: [0-9]+

DATA: .*?

DATAL: [^\r\n]*

## GET request

REQUEST: "GET " PATH " HTTP/1.1\r\nHost: " ORIGIN "\r\n" HEADER "\r\n"

HEADER: [ [ "Accept" | "Cookie" | "Authorization" ] ": " DATAL "\r\n" ]*

## POST urlencoded request

REQUEST: "POST " PATH " HTTP/1.1\r\nHost: " ORIGIN "\r\nContent-Type: application/x-www-form-urlencoded "\r\n" HEADER "\r\n" PARAMS

HEADER: [ [ "Content-Length: " LENGTH | [ "Cookie" | "Authorization" ] ": " DATAL ] "\r\n" ]*

## POST form request

REQUEST: "POST " PATH " HTTP/1.1\r\nHost: " ORIGIN "\r\nContent-Type: multipart/form-data;boundary=\"" BOUNDARY "\"\r\n" HEADER "\r\n" BODY

HEADER: [ [ "Cookie" | "Authorization" ] ": " DATAL "\r\n" ]*

BODY: "--" BOUNDARY "\r\nContent-Disposition: form-data; name=\"" KEY "\"" [ "; filename=\"" KEY "\"" ]? "\r\nContent-Length: " LENGTH "\r\n\r\n" DATA "\r\n--" BOUNDARY "--\r\n"

BOUNDARY: "[^\"\r\n-]+"

## HTTP response

RESPONSE: [ 200 | 302 | 404 | 429 | 500 ] "\>.*?\r\n" HEADER "\r\n" BODY

HEADER: [ [ "Transfer-Encoding: Chunked" | "Content-Type: text/html" | [ "Location" | "Set-Cookie" ] ": " DATAL ] "\r\n" ]*

BODY: CHUNKED | DATA

CHUNKED: [ "[0-9a-fA-F]+\r\n" DATA ]* "0\r\n"

### HTML

See

* [html-choices.md](html-choices.md)
* [html-spec.md](html-spec.md)

## Related

### Simple implementation

* https://github.com/mvbasov/lWS/blob/master/app/src/main/java/net/basov/lws/ServerHandler.java

### Simple protocols

gemini-adjacent:

* https://en.wikipedia.org/wiki/Gopher_%28protocol%29
* https://en.wikipedia.org/wiki/Gemini_(protocol)
* [Mercury](https://portal.mozz.us/gemini/zaibatsu.circumlunar.space/~solderpunk/gemlog/the-mercury-protocol.gmi)
* [Spartan protocol](http://spartan.mozz.us/)
* [Guppy](https://github.com/dimkr/guppy-protocol/blob/main/guppy-spec.gmi)
* [Nex](https://nightfall.city/nex/info/specification.txt)
* [Scroll Protocol](https://web.archive.org/web/20241225235035/http://scrollprotocol.us.to/)
* [Text Protocol](https://textprotocol.org/)
* [SuperTXT](https://supertxt.net/00-intro.html)
* [Scorpion Protocol/File-Format](https://github.com/zzo38/scorpion)
* [molerat](https://molerat.trinket.icu/)
* [TerseNet](https://github.com/runvnc/tersenet)

Upload-only extensions:

* [Inimeg](https://web.archive.org/web/20241225235035/portal.mozz.us/gemini/inimeg.space/specification.gmi)
* [Titan](https://web.archive.org/web/20241225235037/communitywiki.org/wiki/Titan)
* [iapetus](https://web.archive.org/web/20210925220953/codeberg.org/oppenlab/iapetus)
* [gemini+upload](https://web.archive.org/web/20241004190129/https://alexschroeder.ch/view/Baschdels_spin_on_Gemini_uploading)

Communication:

* [misfin](http://portal.mozz.us/gemini/misfin.org/)
* [nanomail](http://portal.mozz.us/gemini/misfin.org/)
* [Nightfall's Postal Service](https://nightfall.city/nps/info/form.txt)

General:

* https://en.wikipedia.org/wiki/File_Transfer_Protocol#Simple_File_Transfer_Protocol
* https://en.wikipedia.org/wiki/Trivial_File_Transfer_Protocol
* http://www.and.org/texts/server-http

## References

* https://wiki.archiveteam.org/index.php/SmolNet
* https://dbohdan.com/archive/scorpion/zzo38computer.org/smallweb.txt/
