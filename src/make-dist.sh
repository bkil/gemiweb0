#!/bin/sh
# Copyright (C) 2023 bkil.hu
# Refer to the GNU GPL v2 in LICENSE for terms

make_head() {
  cd "$ROOT/src/js3" || return 1

  zip \
    -j \
    "$DEST/js0br0.zip" \
    vm.c \
    vm-free.c.inc \
    vm.h \
    vm-impl.h \
    include.h \
    run.c \
    ../br/br0.js \
    ../br/br-lib.js \
    ../br/lib.js \
    ../LICENSE \
    || return 1
}

make_dev() {
  cd "$ROOT/src/js3" || return 1

  git ls-files \
    '*.sh' \
    'test*' \
    '*.js' \
    '../br/*.js' \
    '../br/*.htm' \
    |
  grep -E -v "^\.\./br/(br0|br-lib|lib)\.js$" |
  xargs zip \
    -j \
    "$DEST/js0br0-dev.zip" \
    vm-smallbin.c.inc \
    mk-run \
    ../make-dist.sh \
    ../LICENSE \
    || return 1
}

make_doc() {
  local S TMP
  cd "$ROOT" || return 1

  readonly TMP="$DEST/bf-js.md"
  cp -dp "src/bf.c/README.md" "$TMP" || return 1

  git ls-files \
    'doc/*' \
    |
  xargs zip \
    -j \
    "$DEST/js0br0-doc.zip" \
    README.md \
    LICENSE.md \
    "$TMP"

  S=$?
  rm "$TMP"
  return $S
}

compile() {
  local BIN COMP
  readonly BIN="$1"
  readonly COMP="$2"
  shift 2

  "$COMP" \
    -march=nocona -mtune=broadwell \
    "$OPT" \
    -flto \
    -fconserve-stack \
    -fno-asynchronous-unwind-tables \
    -Wl,-z,norelro \
    -Wl,--build-id=none \
    -Wl,--gc-sections \
    -fno-ident \
    -DSMALLBIN \
    -DNDEBUG \
    -s \
    run.c vm.c \
    -o "$BIN" \
    "$@" \
    || return 1

  strip \
    --remove-section=.comment \
  "$BIN"
}

bins() {
  local COMP OPT
  cd "$ROOT/src/js3" || return 1

  COMP="gcc"

  which musl-gcc >/dev/null && COMP="musl-gcc"

  OPT="-Os"
  "$COMP" -c -Oz -o /dev/null run.c 2>/dev/null && OPT="-Oz"

  compile "$DEST/js0-dl" gcc || return 1

  compile "$DEST/js0-static" "$COMP" -static || return 1

  compile "$DEST/js0-min-static" "$COMP" -static \
    -DNOREGEXP || return 1
}

make_html() {
  local MD PAR BASE OH
  cd "$ROOT" || return 1

  git ls-files |
  grep -E '\.md$' |
  while read MD; do
    PAR="`dirname "$MD"`"
    BASE="`basename "$MD" .md`"
    OH="$DEST/$PAR/$BASE.htm"
    mkdir -p "$DEST/$PAR" || return 1
    printf '%s\n%s' "$IX" "$MD" | "$DEST/js0-min-static" "$ROOT/src/convert/gem2htm.js" |
    sed -r "s~\.md((#[^\"]*)?\")( target=_blank)?(>)~.htm\1\4~g" > "$OH" || return 1
    [ -s "$OH" ] || return 1
    touch -r "$MD" "$OH"
  done
  mv "$DEST/README.htm" "$DEST/index.html" || return 1
  cp -a "$ROOT/doc/gemiweb-icon.ico" "$DEST/favicon.ico" || return 1
  cp -at "$DEST" "$ROOT/doc/gemiweb0-avatar.png" || return 1
}

fetch_index() {
  local PRE
cat << EOF |
https://bkil.gitlab.io/static-wonders.js/
EOF
  while read PRE; do
    wget -U "gemiweb0-makedist.sh/0.1" -O - "$PRE/files.csv" |
    sed "s~^~${PRE}~; N; N"
  done > "$1"
}

main() {
  local DESTNAME DEST ROOT IX
  readonly DESTNAME="$1"
  readonly ROOT="$(readlink -f "`dirname "$0"`/..")"

  [ -n "$DESTNAME" ] || {
    echo "usage: $0 <destdir>" >&2
    return 1
  }

  mkdir -p "$DESTNAME" || return 1
  readonly DEST="`readlink -f "$DESTNAME"`"
  readonly IX="$DEST/static-wonders.js.files.csv"
  cd "$ROOT" || return 1

  git ls-files |
  grep -E '(\.(html?|js|css|sh)|/LICENSE|/(js[23]|bf\.c)/test-vm\.c)$' |
  xargs tar -c --dereference |
  tar -xC "$DEST"

  make_head || return 1
  make_dev || return 1
  make_doc || return 1
  bins || return 1
  fetch_index "$IX" || return 1
  make_html "$IX" || return 1
  rm "$IX" 2>/dev/null || true
}

main "$@"
