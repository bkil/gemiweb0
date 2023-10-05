# HTML subset specification

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

`{ "<!--.*?-->" | "<![CDATA[.*?]]>" | TEXT }*`

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

`{ TEXT2 | " " | "&" { lt | gt | amp | apos | quot } ";" }*`

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

```
<![CDATA[
]]>
```

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

With a limitation of supporting up to one form input or textarea element along with a submit button and up to 1 form per web page.

## Attributes to interpret

id or name should be followed for fragment linking

## Protocol schemes

* file:
* http:
* javascript:
* optional: https:

## Prior art

* https://gemini.circumlunar.space/
* https://codeberg.org/Weblite/HTMLite/src/branch/master/htmlite.md

## Similar efforts

* https://codeberg.org/smolweb/smolweb-spec
