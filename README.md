# gemiweb0, a gemini-HTTP/HTML subset

No need to install a special client or pay for a custom server: enables HTTP-based shared web hosting of the simplest artisan content possible.

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

https://bkil.gitlab.io/static-wonders.js/game/rockpaps.htm

https://bkil.gitlab.io/static-wonders.js/game/talkidea.htm

https://bkil.gitlab.io/static-wonders.js/game/memopair.htm

https://bkil.gitlab.io/static-wonders.js/game/memonums.htm

https://bkil.gitlab.io/static-wonders.js/game/towhanoi.htm

https://bkil.gitlab.io/static-wonders.js/game/permslid.htm

https://bkil.gitlab.io/static-wonders.js/share/rot13.htm

https://bkil.gitlab.io/static-wonders.js/share/sumlist.htm

https://bkil.gitlab.io/static-wonders.js/audio/evalmus.htm

https://bkil.gitlab.io/static-wonders.js/audio/ansimus.htm

https://bkil.gitlab.io/static-wonders.js/edu/knowende.htm

https://bkil.gitlab.io/static-wonders.js/edu/knownone.htm

https://bkil.gitlab.io/static-wonders.js/edu/goodshuf.htm#

https://bkil.gitlab.io/static-wonders.js/edu/knowcard.htm#

https://bkil.gitlab.io/static-wonders.js/edu/sortfun.htm

https://bkil.gitlab.io/static-wonders.js/game/markov.htm

https://bkil.gitlab.io/static-wonders.js/toy/randjs.htm

https://bkil.gitlab.io/static-wonders.js/toy/namegen.htm

https://bkil.gitlab.io/static-wonders.js/joke/dare.htm

https://bkil.gitlab.io/static-wonders.js/joke/js-nojs.htm

https://bkil.gitlab.io/static-wonders.js/joke/hole-dimension-dirt-volume.htm

https://bkil.gitlab.io/static-wonders.js/crypto/randhash.htm

### Example visual web content

The visual impaired may not find the following examples enjoyable:

https://bkil.gitlab.io/static-wonders.js/game/rgbname.htm

https://bkil.gitlab.io/static-wonders.js/game/guard.htm

https://bkil.gitlab.io/static-wonders.js/game/catmaze.htm

https://bkil.gitlab.io/static-wonders.js/game/wallrace.htm

https://bkil.gitlab.io/static-wonders.js/game/holejump.htm

https://bkil.gitlab.io/static-wonders.js/share/colword.htm

https://bkil.gitlab.io/static-wonders.js/toy/busybvr.htm

https://bkil.gitlab.io/static-wonders.js/toy/busybvr4.htm

https://bkil.gitlab.io/static-wonders.js/toy/ploteval.htm

https://bkil.gitlab.io/static-wonders.js/toy/mandbrot.htm

https://bkil.gitlab.io/static-wonders.js/toy/logismap.htm

https://bkil.gitlab.io/static-wonders.js/toy/langtona.htm

https://bkil.gitlab.io/static-wonders.js/toy/rule110.htm

https://bkil.gitlab.io/static-wonders.js/toy/snowdown.htm

https://bkil.gitlab.io/static-wonders.js/crypto/papotp.htm

https://bkil.gitlab.io/static-wonders.js/draw/pixfont.htm

* [src/br/index.htm](src/br/index.htm)
* [src/check/bf.html](src/check/bf.html)
* [src/bf.c/rot1.html](src/bf.c/rot1.html)

Bookmarklets:

* https://bkil.gitlab.io/static-wonders.js/userjs/gmaps-embed.js0.html
* https://bkil.gitlab.io/static-wonders.js/userjs/localStorage-stub.html
* https://bkil.gitlab.io/static-wonders.js/userjs/maltai-map.js0.html

## Contact

Join our free chat room on Matrix, also relayed over an XMPP MUC and the IRC channel #gemiweb0. You can participate in brainstorming and give a hand by implementing the standard from scratch in your favorite language:

* https://matrix.to/#/#gemiweb0:matrix.org
* [xmpp:gemiweb0@conference.movim.eu](xmpp:gemiweb0@conference.movim.eu?join)
* [irc.oftc.net/#gemiweb0](irc://irc.oftc.net/%23gemiweb0)
* [irc.libera.chat/#gemiweb0](irc://irc.libera.chat/%23gemiweb0)
* [chat.freenode.net/#gemiweb0](irc://chat.freenode.net/%23gemiweb0)

## Source code repository

Web viewing may be blocked from some ISP due to load.

* https://gitlab.com/bkil/gemiweb0
* https://github.com/bkil/gemiweb0

### Feeds

Subscribe to the feed of changes via Atom (RSS):

* https://gitlab.com/bkil/gemiweb0/-/commits/master?format=atom

### 88x31 badges

The rendered website should be faster and more accessible than the git repository.

```html
<a href="https://bkil.gitlab.io/gemiweb0" target="_blank" rel="noopener" referrerpolicy="unsafe-url"><img alt="with(js0){bkil.write('minimal','browser');for 80x25 bright" width="88" height="31" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFgAAAAfBAMAAACR5hfTAAAAElBMVEWSkpIAAP////+2trZJSUkAAAAizS8YAAABoklEQVR4AX2RUY7iMBBEG6/2P3guYBfjfyRn/leJD4CMfP+rbLvw9CRks9UtZKSnp6aQy4RtQv5P5D0BAeKCCFxAxGfhIgLxQ0R+t/Ywdgro01dhD+UKsCzwiDejDA7fsMiAC+F4vVFsecg9iOzMRffMfIdzEDfgiLLo2s1mZhQ+z9HM377o5wLgVc1oR35tzOIIK/kJLAY7a2dndmGYF4MDzYRploe62bTD3hx9EDk1I2xuLkv0cA6O8p25EYb8wXn2ZicK+4SWamqo+qipNqAiAZUwzcLoGRHKtIqKlqDTGlIyeB/CtRJuHe5kI9z/wTmX76z5rnCXcAjjdRWAF/wTheEJ281I4yvibWvWKHye28HcdX0TL0Hr0qavCPyYDUa1RU1sjW8fD22YubKUZGb4br5cr9MGBszceA3NgJo/DmaAWqUwKm6EI9v4YvIzP5+sbp+8jYhCmq+s0+HoAQRBcBCncMl5VW5ec1nNrF6aQRhwoS/mvM4sVx/5ePPV06zkMM/KrXOhGZtcpumfZh2VH+E44OAI8+ZhzvKesk/e5i/Q5MGg7MqgLQAAAABJRU5ErkJggg=="></a>
```

```html
<a href="https://bkil.gitlab.io/gemiweb0" target="_blank" rel="noopener" referrerpolicy="unsafe-url"><img alt="with(js0){bkil.write("minimal","browser");for 80x25 dark" width="88" height="31" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFgAAAAfBAMAAACR5hfTAAAAElBMVEWSkpIAAP////9JSUkAAAC2trYVGYSLAAABoUlEQVR4AX2SUW7bMBBENy4PYCM6gLHiAQoL/Sfl8b+Bkve/SodThZKqKsMFwQAPD5O17OPq29ynb2L/JiHBQjJDSMh4VQ1fyJ9mFoDU2SthHk6DB5CrQCl85menOpy+YLMFroLz7SlxT7J3MtuZK+fM/EYIsLDAGbVweuedGYTPczTrfy+8S6ul1SzbsR8bs10Ek3wBpcOhb2dnvtwXc+lwklmwzJaaOzXY9+Y8JLNTs983nWvJQ1tNkHxnhmC3nzjP3nwxwsMMn+PsiHzEOToQMfMSLLMprJFBxiMifAaPO+a5w/sIjlGwN7iRLrj9gr/r9JVf9U24SXQEQ60I4y+8hjAGwb0zYf1J+CnzGsLneR7MTddmVpPmdl5sDKzmFY59eGlreg/H77mbo5YydzOGZv643a4bGKvZ1UZmgObPgxmLlgWWFbvgrG0Upb7q66XV7TNtY0aIKZWnwXnQB4sUYIGwT9NI7jFOPq5mqmUWDITUBo9pfDwmho/p2Pk2yExyMRMex4fL7Jt8XK//NfNQfoSzYE4QrM6L+VDDpm/yBzUN+jDXn7S6AAAAAElFTkSuQmCC"></a>
```

```html
<a href="https://bkil.gitlab.io/gemiweb0" target="_blank" rel="noopener" referrerpolicy="unsafe-url"><img alt="# gemiweb0 &gt; tiny * browser ``` js0 ``` bright" width="88" height="31" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFgAAAAfAgAAAAAME02dAAABJUlEQVR4AXXSIWgDMRQG4LC4mng3OWbPBuI92+S816Njct4zKsoRVc/GHZw9iDxZrxp4tCf60rd3uRwJ4/ZDKz4ejyT/Cbsa0dBKbgsD/5A8CzWnzBTZGWK9Mn87kl7LDpH/Jz5db8wHieB0D9g7DT0zJ04jtJFbDS5xmkYEFA4zp92IGrxWvjwgUJHzE+eZGVXJF8vZM3NWeTuWvLP2Yy9+mP9OP/D0NrwM4fW4Xfi93kx85CVhzFzv7D3zGHnMXD/m6fOMitl+xt00hLcxzFwxf23iSWISa+byOgPFGHO5S1zGuHxLUzAsT+VKrmR6WGaBqgNoUbUkXGr+0BsNpKEyUzeoUvONpJk7r3jb0nxTRfYSgSKnLpEkUAdOoMr83zdoV/MLsU8sS9NgqKkAAAAASUVORK5CYII="></a>
```

```html
<a href="https://bkil.gitlab.io/gemiweb0" target="_blank" rel="noopener" referrerpolicy="unsafe-url"><img alt="# gemiweb0 &gt; tiny * browser ``` js0 ``` dark" width="88" height="31" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFgAAAAfAgAAAAAME02dAAABIklEQVR4AWzRIWgDMRgF4Nf7K9LyQ+pVZWXg7MGVzVMVSkWZ90yOHfNeT27znkBs7ZicdzF1Gd1/aW4Jo0+c+HgcSR7szWCLG5lNzAAIOsmqMBIbB9G58L1B1D52RPIdeTWfCe8isfEtU2s8t8KS1CbuE/eeTebcJmK6GCqc/03kWfug6wMyqiw/JO/CFGpeWMlBuE7Ng6r5aO3TAXfC/9tf0h6at03zuh4mft6fR15jUI0qvD/ab2GVWBXef5b2En9sH0cesGleVHNFI/xwTidJydwJ19fZIKXH4qdmZHbllq7iMD2VqbnNDzvyhULH3FPoAZeX37XOMzyf3HWbvPw24sqdDiPn5benxDoSI3HekhAZHZsLBfc7uDCONIgjxQIAqb51UnzN6yUAAAAASUVORK5CYII="></a>
```

### 80x15 badges

```html
<a href="https://bkil.gitlab.io/gemiweb0" target="_blank" rel="noopener" referrerpolicy="unsafe-url"><img alt="best viewed in 80x25 bright" width="80" height="15" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAAAPBAMAAACB51W8AAAAElBMVEWqqqoAAKr///9VVVUAAABV//98YHRCAAAA3UlEQVR4AX2RQWrDMBBFJyXd2zpB/UcHMCO6N0LZF2rf/yr5nyFgMPhlFgI93ijYHhPEj7V7zOw5jEyBO9zESWzwQEMLIMJ5CoTrZzbE2NYUdevQICRDItxVTNao/VOMFLMY6knMoMSat+p9xIDELD6psrhFRc+iq5h6o4N8Y5Jivf3XKm4pMpkExHzGvn//G/lbJXISbxKpLnTKMmNJ8Tgk1jqQhCta5qWUWSZ9M2UJxdH7WVSx0FmoFa4+Xi8Oi8Do1yIdVbl63/eDq6/fOt/IYtHJviAe09QuzGfeyXVS0QO6XxcAAAAASUVORK5CYII="></a>
```

```html
<a href="https://bkil.gitlab.io/gemiweb0" target="_blank" rel="noopener" referrerpolicy="unsafe-url"><img alt="best viewed in 80x25 dark" width="80" height="15" src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAFAAAAAPBAMAAACB51W8AAAAElBMVEWqqqoAAKr///9VVVUAAABV//98YHRCAAAA2ElEQVR4AX2RQWrEMAxF/xR1H/kEtckBApnuRftnX2hy/6tUn5jUJXSesjD48WQIblMTb1ifA8CIZLrzGZ8QgwiGEYSRZkHQaJGTIiliOUTdBhk6StYEI36Ly1C0FM+iqSiRIiTO/ZZxiiaxFy1VAHFn68VQ8dCRDvsbRRdn/ksvxiE2dozCR/D6/r0mX4vEMxmQ2NxrOqV6q4e47xLn07NQtHgtxWWmDyibpMiPP6KKKdaaWsnV++ORn4riWtS45+pt2/Zcff3X/Y21lpYnvDRxm6b1go/8AJx2aM7HqVTHAAAAAElFTkSuQmCC"></a>
```

### LICENSE

* [LICENSE.md](LICENSE.md)
