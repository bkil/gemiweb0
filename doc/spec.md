# Specification of GemiWeb, the gemini-HTTP/HTML subset

## Components

* Specification
* gemiweb & gopher-HTML client support patches for maintained gemini & gopher browsers
* gemiweb & gopher-HTML serving support patches for maintained static gemini capsules (gewfile servers)
  * File converters between gewfile (gemiweb) & gopher-HTML menu vs. gemfile (gemini) & gopher menu
  * gemiweb & gopher-HTML serving support patches for maintained dynamic gemini application servers
* gemini & gopher proxy server for viewing gemiweb & gopher-HTML pages
  * E2EE gemiweb socket proxy server for viewing gemini pages with certificates
  * gemiweb & gopher-HTML proxy server for viewing gemini & gopher pages
* Ethically Reduced: A proof of concept unethical application server for gemiweb, gemini, gopher-HTML and gopher

## Content producers

* Should cooperate in producing content that corresponds with gemini to their best abilities.
* May generate a small amount of additional data that can improve the quality of life of web browser users, for example a style sheet or by aiding navigation or accessibility.
* Must not generate a file with too many additions that causes an excessive amount of data being transferred for those users who can not interpret it.

## Client

## Implementation

* Optional: sending over everything (including the path) via the HTTP POST preserves some privacy against default web server logging

### Client side TLS certificate

* Instead of client side TLS certificates, each request could be signed
* Including the POST body, any arguments, the host origin, timestamp and optionally the sender's public IP address
* Subject to calibration against the server's time from previous HTTP responses
* The server could also echo the public IP of the client in each response
* An HTTP HTTP-only session cookie based workaround would be possible where signing would initiate "signing in"
  * The session cookie could simulated via URI paths

### Unicode byte order mark

### File uploads

* Up to 1KB: base64 encoded into the URI query
* Via a separately installable uploader that splits the file to such pieces and submits it in individual requests
  * Possibly via a browser extension
* Embedded within the TLS handshake: not very good out of the box support in HTTP servers
* Via an email attachment
  * Less commonly with anonymous FTP
* "Cheat" by allowing gemiweb users to post files via an HTTP form

## Notes

* gemini https://en.wikipedia.org/wiki/Gemini_(protocol)

* https://github.com/LukeEmmet/html2gemini

> A Go library to converts HTML into Gemini text/gemini (gemtext)

* https://github.com/makeworld-the-better-one/md2gemini

> File converter from Markdown to Gemini.
> One of its key features is that it can convert inline links into footnotes. It also supports tables, and will convert them into Unicode (or ASCII) tables.

* https://linuxreviews.org/Gemini
* https://tildegit.org/solderpunk/agena _Gemini-to-Gopher proxy written in Python_
* https://github.com/LukeEmmet/duckling-proxy _Duckling proxy 🦆 is a Gemini proxy to access the Small Web_
* https://github.com/kr1sp1n/awesome-gemini
* https://gitlab.com/gemini-specification/protocol
* https://github.com/Aarontheissueguy/Html2GeminiPy _Convert html sites to fully functional gemini containers using python._
* https://git.rdelaage.ovh/Gemini/mastoGem _MastoGem: a Mastodon proxy for Gemini_
