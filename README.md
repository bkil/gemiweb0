# gemiweb0, a gemini-HTTP/HTML subset

Don't install a special client or pay for a custom server: enables HTTP-based shared web hosting.

## Status

Status: not public yet, volunteer developers and user brainstorming welcome!

The internal names of the work in progress subsets used are HTTP0, HTML0, JS0 and CSS0 respectively.

## Documentation

See the doc folder for more information:

* [doc/project-community.md](doc/project-community.md)
* [doc/user-application.md](doc/user-application.md)
* [doc/http-choices.md](doc/http-choices.md)
* [doc/http-spec.md](doc/http-spec.md)
* [doc/html-choices.md](doc/html-choices.md)
* [doc/html-spec.md](doc/html-spec.md)
* [doc/js-choices.md](doc/js-choices.md)
* [doc/js-spec.md](doc/js-spec.md)
* [doc/js-grammar.md](doc/js-grammar.md)
* [doc/css-spec.md](doc/css-spec.md)
* [doc/web-browsers-by-engine.md](doc/web-browsers-by-engine.md)
* [doc/javascript-interpreter-runtimes.md](doc/javascript-interpreter-runtimes.md)
* [doc/test.md](doc/test.md)
* [src/bf.c/README.htm](src/bf.c/README.htm)

Older notes:

* [doc/spec.md](doc/spec.md)
* [doc/home.md](doc/home.md)

## Development snapshots

Note that we are still accepting developer feedback on the specification. You should not build anything serious on it until we have finalized it. The proof of concept implementation of the js0 runtime, http0 fetcher and html0 renderer (so called "picobrowser") is not intended for general audiences yet and serves more of a code sample to review and be inspired by. All example web content is tested for compatibility with this kit. For safety, do consider running with containerization during testing.

* https://bkil.gitlab.io/gemiweb0/js0br0.zip
* https://bkil.gitlab.io/gemiweb0/js0br0-dev.zip
* https://bkil.gitlab.io/gemiweb0/js0br0-doc.zip
* https://bkil.gitlab.io/gemiweb0/js0-dl
* https://bkil.gitlab.io/gemiweb0/js0-static
* https://bkil.gitlab.io/gemiweb0/js0-min-static

## Example web content

Play with an example game obeying this subset:

* https://bkil.gitlab.io/static-wonders.js/game/rgbname.htm
* https://bkil.gitlab.io/static-wonders.js/game/guard.htm
* https://bkil.gitlab.io/static-wonders.js/game/rockpaps.htm
* https://bkil.gitlab.io/static-wonders.js/game/wallrace.htm
* https://bkil.gitlab.io/static-wonders.js/game/holejump.htm
* https://bkil.gitlab.io/static-wonders.js/game/memopair.htm
* https://bkil.gitlab.io/static-wonders.js/game/memonums.htm
* https://bkil.gitlab.io/static-wonders.js/game/markov.htm
* https://bkil.gitlab.io/static-wonders.js/game/towhanoi.htm
* https://bkil.gitlab.io/static-wonders.js/game/permslid.htm
* https://bkil.gitlab.io/static-wonders.js/share/colword.htm
* https://bkil.gitlab.io/static-wonders.js/share/sumlist.htm
* https://bkil.gitlab.io/static-wonders.js/edu/knowende.htm
* https://bkil.gitlab.io/static-wonders.js/edu/knownone.htm
* https://bkil.gitlab.io/static-wonders.js/edu/goodshuf.htm#
* https://bkil.gitlab.io/static-wonders.js/edu/knowcard.htm#
* https://bkil.gitlab.io/static-wonders.js/edu/sortfun.htm
* https://bkil.gitlab.io/static-wonders.js/toy/busybvr.htm
* https://bkil.gitlab.io/static-wonders.js/toy/busybvr4.htm
* https://bkil.gitlab.io/static-wonders.js/toy/logismap.htm
* https://bkil.gitlab.io/static-wonders.js/toy/langtona.htm
* https://bkil.gitlab.io/static-wonders.js/toy/rule110.htm
* https://bkil.gitlab.io/static-wonders.js/toy/namegen.htm
* https://bkil.gitlab.io/static-wonders.js/toy/snowdown.htm
* https://bkil.gitlab.io/static-wonders.js/joke/dare.htm
* https://bkil.gitlab.io/static-wonders.js/joke/js-nojs.htm
* https://bkil.gitlab.io/static-wonders.js/joke/hole-dimension-dirt-volume.htm
* https://bkil.gitlab.io/static-wonders.js/crypto/randhash.htm
* https://bkil.gitlab.io/static-wonders.js/crypto/papotp.htm
* https://bkil.gitlab.io/static-wonders.js/draw/pixfont.htm
* [src/br/index.htm](src/br/index.htm)
* [src/check/bf.html](src/check/bf.html)
* [src/bf.c/rot1.html](src/bf.c/rot1.html)

Bookmarklets:

* https://bkil.gitlab.io/static-wonders.js/userjs/gmaps-embed.js0.html
* https://bkil.gitlab.io/static-wonders.js/userjs/localStorage-stub.html
* https://bkil.gitlab.io/static-wonders.js/userjs/maltai-map.js0.html

## Contact

Join our chat room on Matrix, also relayed over a XMPP MUC and the IRC channel #gemiweb0. You can participate in brainstorming and give a hand by implementing the standard from scratch:

* https://matrix.to/#/#gemiweb0:matrix.org
* [xmpp:gemiweb0@conference.movim.eu](xmpp:gemiweb0@conference.movim.eu?join)
* [irc.oftc.net/#gemiweb0](irc://irc.oftc.net/%23gemiweb0)
* [irc.libera.chat/#gemiweb0](irc://irc.libera.chat/%23gemiweb0)
* [chat.freenode.net/#gemiweb0](irc://chat.freenode.net/%23gemiweb0)

## Source code repository

May be blocked from some ISP due to load.

* https://gitlab.com/bkil/gemiweb0
* https://github.com/bkil/gemiweb0

### Feeds

Subscribe to the feed of changes via Atom (RSS):

* https://gitlab.com/bkil/gemiweb0/-/commits/master?format=atom

### 88x31 badges

The rendered website should be faster and more accessible than the git repository.

```html
<a href='https://bkil.gitlab.io/gemiweb0' target='_blank' rel=noopener referrerpolicy=unsafe-url><img alt="with(js0){bkil.write('minimal','browser');for 80x25" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFgAAAAfBAMAAACR5hfTAAAAElBMVEWSkpIAAP////+2trYAAABJSUnoleIEAAABnklEQVR4AY2TUc7bIBCEidUDOJzADPZ7FP6+R4QDVFS+/1U60xWBlibqsEIb+ePTCsfusmLMhg9xfyciIt1jSrhHBMSkUofg+fhbKY8Xu0ZosQR76CjbOzz5BnU4NphygxMEhysk7nm4mwYYzUn1xnzTg3Q3GIGtqs0scw/hD5nMx4kDlXsFsHG5hbU5x30wu0WwyAOoL3jRplpGs86bub7gTWaDIZl7yP0QjD/NwfP0WzO2YeazBo9lEWzybi6CAffjf29jWRxhv6PseS/IbPKeC5Cxa0MzG84xAsiUjMwj4CoF+97hMQbnLFgYQR2AYL3B7+ls+ZluhIFsS4yWpgJgcA9heMF9ZsL2EwGDWSH8IZNZOtVusxRJC7sAdHOH86u46das92G+jWYWkKk1s2CZL9frOsDo5qJpsplBs5/MMC0p2BWzBAdojK/fSc/0fKY03cY5xjlCzFfiEhw8gJgQ9fERJn6Qq/o3djPV7aXY56pCPY9aZWVzzjNfvcwkm7mSOypkdhhyWdd/mrkon+FgsGYWbDObeRrDfbqNX38Fwj0z4oOFAAAAAElFTkSuQmCC'></a>
```

### LICENSE

* [LICENSE.md](LICENSE.md)
