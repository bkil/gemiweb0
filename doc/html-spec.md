# HTML subset specification

Cover as little as possible to correspond to gemini (gemtex) while remaining compatible with existing web browsers. Allow implementing all targeted user application.

## Grammar

### HTML

`"<!DOCTYPE html><html" { " " lang ATTR }? "><head><meta charset='utf-8'><title>" CONTENT </title> HEAD </head><body> BODY { FORM }? BODY </body></html>`

### HEAD

`"<link rel='shortcut icon' type='image/x-icon' href='data:image/x-icon;,'><meta property='og:description' content='" CONTENT "' name='description'><meta name='viewport' content='width=device-width, initial-scale=1'>" { <link " " rel Q{ stylesheet } href URL > }*`

### FORM

`<form NAME { " " action URL }? { " " method Q{ post } { " " enctype Q{ multipart/form-data } }? }? > BODY { <input NAME " " type Q{ file } > | <input NAME { " " value ATTR }? > | <textarea NAME > TEXT </textarea> } BODY <input " " type Q{ submit } { " " value ATTR }? > BODY </form>`

### BODY

`{ <h1> TEXT </h1> | <h2> TEXT </h2> | <h3> TEXT </h3> | <pre> TEXT </pre> | <blockquote> TEXT </blockquote> | <ul> { <li> TEXT </li> }* </ul> | BREAK | DYNAMIC | CONTENT }*`

### BREAK

`<br> | <p> | </p> | <div> TEXT </div>`

### DYNAMIC

`<a NAME { " " href URL }? > TEXT </a> | <script src URL { " " onerror ATTR }? ></script> | <script> TEXT </script> | <style> TEXT </style>`

### CONTENT

`{ "<!--.*?-->" | TEXT }*`

### NAME

`{ " " name ATTR }?`

### ATTR

`{ } | "=" { "\"" { TEXT1 | "'" }* "\"" | "'" { TEXT1 | "\"" }* "'" | TEXT2 }`

### URL

`Q{ { file | http | https | javascript } ":" TEXT1 }`

### Q

`Q{V}: "=" { V | "'" V "'" | "\"" V "\"" }`

### TEXT

`{ TEXT1 | "'\"\n" }*`

### TEXT1

`{ TEXT2 | " " | "&" { lt | gt | amp | apos | quot | nbsp } ";" }*`

### TEXT2

`"[^<>&'\"\n ]+"`

## Escaping

https://html.spec.whatwg.org/multipage/syntax.html#elements-2

* Void elements: area, base, br, col, embed, hr, img, input, link, meta, source, track, wbr (deprecated: command, keygen, param)
* Raw text elements: script, style
* Escapable raw text elements: textarea, title

## Doctype

```
<!DOCTYPE html>
<html>
```

## SGML comments

`<\!-- Optionally, text, with the additional restriction that the text must not start with the string ">", nor start with the string "->", nor contain the strings "<!--", "-->", or "--!>", nor end with the string "<!-". -->`

## CDATA

`<![CDATA[...]]>` is not supported, because it is XML-specific.

https://en.wikipedia.org/wiki/CDATA

## Tags to assume

* meta (charset=utf-8)
* title

## Tags to interpret

* h1, h2, h3
* a (href, name)
* br (~p, ~div)
* pre
* blockquote
* ul, li
* form (name, action, enctype, method=get, method=post)
* input (type=text, name, value)
* input (type=file, name)
* input (type=submit, value)
* textarea (name)
* script (src, onerror)

With a limitation of supporting up to one of a form input or a textarea element along with a submit button and up to 1 form per web page.

## Attributes to interpret

id or name should be followed for fragment linking and may improve user experience by allowing to preserve scroll position, focus or form input

### Accessibility

role=img and aria-label="..." added to a pre, blockquote or textarea should improve accessibility of ASCII art

readonly, role=status (or alert, log) and aria-live=polite (or assertive) added to a textarea might allow for status updates

## Protocol schemes

* file:
* http:
* javascript:
* optional https:

## References

### Similar halted efforts

* https://en.wikipedia.org/wiki/Small-C
* https://gemini.circumlunar.space/
* https://codeberg.org/Weblite/HTMLite/src/branch/master/htmlite.md

### Smolweb

* https://smolweb.org/guidelines.html
* https://codeberg.org/smolweb/smolweb-spec
* https://smolweb.org/specs/index.html

### C-HTML

* https://www.w3.org/TR/1998/NOTE-compactHTML-19980209/#www3-1
* https://en.wikipedia.org/wiki/I-mode#Description

> As a simpler form of HTML, C-HTML does not support tables, image maps, multiple fonts and styling of fonts, background colors and images, frames, or style sheets, and is limited to a monochromatic display. Includes GIF image support.

### Similar ongoing efforts

* https://github.com/acidus99/stargate-proxy
* https://github.com/matthewp/quack-proxy

### Compatible best practices

* https://seirdy.one/posts/2020/11/23/website-best-practices/
* https://indieweb.org/progressive_enhancement
* http://eev.ee/blog/2016/03/06/maybe-we-could-tone-down-the-javascript/
* https://ar.al/2020/08/07/what-is-the-small-web/
* https://benhoyt.com/writings/the-small-web-is-beautiful/
* https://shkspr.mobi/blog/2021/01/the-unreasonable-effectiveness-of-simple-html/

### HTML standards

1991-10-29 HTML Tags (1.0):

* http://info.cern.ch/hypertext/WWW/MarkUp/Tags.html
* https://www.w3.org/History/19921103-hypertext/hypertext/WWW/MarkUp/Tags.html
* https://lists.w3.org/Archives/Public/www-talk/1991SepOct/0003.html

1993-06 HTML 1.2:

https://www.w3.org/MarkUp/draft-ietf-iiir-html-01.txt

1993-11-08 HTML+

* https://www.w3.org/MarkUp/HTMLPlus/htmlplus_1.html
* https://www.w3.org/MarkUp/htmlplus_paper/htmlplus.html

1995-11-24 HTML 2.0:

https://datatracker.ietf.org/doc/html/rfc1866

1997-01-14 HTML 3.2:

https://www.w3.org/TR/REC-html32

1997-12-18 HTML 4.0:

https://www.w3.org/TR/REC-html40-971218/
