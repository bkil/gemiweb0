#!/bin/sh

main() {
  IN="${1-1.gemtext}"

  TITLE="`grep -o -m1 "[^#].*" "$IN"`"

  cat << EOF
<!DOCTYPE html>
<html>
<head>
  <meta charset=utf-8>
  <meta http-equiv=content-type content='text/html; charset=UTF-8'>
  <title>$TITLE</title>
  <link rel='shortcut icon' type=image/x-icon href=data:image/x-icon;,>
  <meta name=viewport content='width=device-width, initial-scale=1.0'>
</head>
<body>
EOF

  sed -nr '
    s~&~\&amp;~g
    s~<~\&lt;~g
    s~>~\&gt;~g
    t loop

    :loop
    s~^###(.*)~<h3>\1</h3>~
    t p
    s~^##(.*)~<h2>\1</h2>~
    t p
    s~^#(.*)~<h1>\1</h1>~
    t p
    s~^&gt;(.*)~<blockquote>\1</blockquote>~
    t p
    s~^=&gt;([^ ]*)$~<p><a href="\1">\1</a></p>~
    t p
    s~^=&gt;([^ ]*) (.*)~<p><a href="\1">\2</a></p>~
    t p

    s~^```~<pre>~
    T no_pre
    N
    s~\n```$~</pre>~
    t p
    s~\n~~
    t pre
    :pre
    N
    s~\n```$~</pre>~
    T pre
    b p
    
    :no_pre
    s~^[*](.*)~<ul>\n<li>\1</li>~
    T no_list
    :list
    p
    n
    s~(^)[*](.*)~\1<li>\2</li>~
    t list
    h
    s~.*~</ul>~
    p
    g
    t loop

    :no_list
    s~.*~<p>&</p>~
    t p
    :p
    p
    :e
  ' "$IN"

  cat << EOF
</body>
</html>
EOF
}

main "$@"
