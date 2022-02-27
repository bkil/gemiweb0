#!/bin/sh

main() {
  cat "${1-1.gewtext}" |
  sed -nr '1,/<(\/head|body)>/ ! p' |
  sed -r '
    :l
    s~<pre>[^<>]*$~&~
    t e
    N
    s~((>)\s*\n\s*|\s*\n\s*(<))~\2\3~
    t l
    s~\n~ ~
    t l
    :e
  ' |
  sed -nr '
    :loop
    s~^<h1>([^<]*)</h1>~#\1\n~
    t p
    s~^<h2>([^<]*)</h2>~##\1\n~
    t p
    s~^<h3>([^<]*)</h3>~###\1\n~
    t p
    s~^<blockquote>([^<]*)</blockquote>~>\1\n~
    t p
    s~^<li>([^<]*)</li>~*\1\n~
    t p
    s~^<a href="([^"]*)">([^<]*)</a>~=>\1\n~
    t p
    s~^</ul><ul>~\n~
    t p
    s~^<p>([^<]*)</p>~\1\n~
    t p

    s~^<pre>~```\n~
    T drop
    P
    s~.*\n~~
    t pre

    :pre
    s~</pre>~\n~
    T more_pre
    P
    s~.*(\n)~```\1~
    b p

    :more_pre
    p
    n
    b pre

    :drop
    s~^<[^>]*>~~
    t loop

    s~<~\n&~
    t p

    s~^$~~
    t e

    :p
    h
    s~\n.*~~
    s~&lt;~<~g
    s~&gt;~>~g
    s~&amp;~\&~g
    p
    g

    s~.*\n~~
    t loop
    :e
    '
}

main "$@"
