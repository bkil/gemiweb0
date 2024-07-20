# CSS feature set overview

Rendering of styles on a terminal emulator or to text files, with an inefficient algorithm and without traversing a DOM tree must be feasible. No HTML body element should precede a CSS rule which influences it in the markup source of the document.

This can avoid flash of unstyled content and having to implement reflowing. We aim to cover a small subset of "CSS1 core" (see also: "CSS1 advanced").

## Presentational HTML

HTML markup should convey the semantic structure of the document. Certain legacy HTML tags and attributes also allow conveying slight visual information: b (strong), body (bgcolor, text, link), big, br, center, del, i (em), font (color, size, face), hr, small, strike, sub, sup, u and more.

Allowing to override as much of the appearance of a page with user CSS allows for accessibility and easy customization. If a user agent has no support for CSS or the stylesheet failed to load, information loss may occur. We need to strike a good balance between HTML vs. CSS.

Information content within a document should remain legible and an application accessible regardless of web browser support:

* no CSS at all
* CSS0
* CSS1 core
* Subsets of CSS level 1, 2, 2.1, 3, 4 supported by contemporary browsers
* Screen resolution of 320x240 on 3-inch to 1920x1080 on 24-inch diameter
* Lack of colours

## Mandatory for ANSI formatting

Features:

* Containment in HTML: class attribute, inline style element (in `<head>`), link rel href
* Grouping: ",", ";"
* Inheritance: assume that only `<body>` (and optionally `<html>`) can be inherited from as element nesting is discouraged
* Element type selector
* ".Class" as selector: `[A-Za-z][0-9A-Za-z-]*`
* Cascading order: specificity
* Length units: px, em
* Color units: #abc, #abcdef
* Forward-compatible parsing

Properties:

* background-color
* color
* font-size: medium, large (may render as double height and double width line)
* font-style: normal, italic (not supported by Opera Mini)
* font-weight: normal, bold
* font-weight: lighter (not supported by Opera Mini)
* text-decoration: none, underline, overline, line-through
* vertical-align: baseline, sub, super

## Recommended for user style extensions

Negative lengths are not supported and truncate to zero.

Features:

* Comments
* "!important"
* "#ID" as selector
* Anchor pseudo-classes: :link :visited :active
* The ":first-letter" pseudo-element [advanced]
* The ":first-line" pseudo-element [advanced]

Properties:

* border
* border-bottom
* border-color
* border-left
* border-right
* border-style: none, solid [core]
* border-top
* display [advanced]
* font-family: sans-serif, monospace (not efficient on Opera mini outside `<textarea>`)
* font-variant [advanced]
* letter-spacing [advanced]
* line-height
* list-style-position
* list-style-type: disc, circle, square, decimal, lower-alpha, upper-alpha, none
* margin
* margin-bottom
* margin-left
* margin-right
* margin-top
* padding
* padding-bottom
* padding-left
* padding-right
* padding-top
* text-indent
* text-transform [advanced]
* white-space [advanced]
* width: 100% for `<form>`, `<input>`, `<textarea>`
* word-spacing [advanced]

## Out of scope

### Redundant

Features:

* Containment in HTML: style attribute
* Contextual selectors (descendant combinator)
* @import directive
* Length units: pt, mm, cm, pc, in, ex
* Color units: 16 keywords, rgb(0,5,255), rgb(0%,2%,100%)

Properties:

* background
* border-bottom-width
* border-left-width
* border-right-width
* border-top-width
* border-width
* font
* list-style

### Requires viewport layout

Features:

* Percentage units: "%"

Properties:

* clear
* float
* height [advanced]
* text-align
* width

### Requires raster image rendering

Features:

* URL unit

Properties:

* background-attachment [advanced]
* background-image
* background-position
* background-repeat
* list-style-image

### More recent standards

Features:

* @supports directive: may think about evaluating as if nothing was supported

Combinators:

* Chain selectors to combine multiple selectors without space
* Next-sibling ("+")
* Subsequent sibling ("~")

Properties:

* all
* break
* content
* cursor
* opacity
* position
* visibility

Pseudo-classes:

* :is()
* :not()
* :nth-child()
* :nth-of-type()
* :target

Pseudo-elements:

* ::after
* ::before

## References

### CSS guide

* https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Cascade_and_inheritance

### CSS1 standard

* https://www.w3.org/TR/CSS1/
* https://www.w3.org/TR/CSS2/
