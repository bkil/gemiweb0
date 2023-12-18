#!/bin/sh
# Copyright (C) 2023 bkil.hu
# Refer to the GNU GPL v2 in LICENSE for terms

make_head() {
  cd "$ROOT/src/js3" || return 1

  zip \
    -j \
    "$DEST/js0br0.zip" \
    vm.c \
    vm-free.c \
    vm.h \
    vm-impl.h \
    include.h \
    run.c \
    ../br/br0.js \
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
  xargs zip \
    -j \
    "$DEST/js0br0-dev.zip" \
    vm-smallbin.c \
    mk-run \
    ../LICENSE \
    || return 1
}

make_doc() {
  local S
  cd "$ROOT" || return 1

  TMP="$DEST/bf-js.md"
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
  local COMP BIN
  readonly BIN="$1"
  readonly COMP="$2"
  shift 2
  "$COMP" \
    -march=nocona -mtune=broadwell \
    -Os \
    -flto \
    -fno-asynchronous-unwind-tables \
    -Wl,-z,norelro \
    -Wl,--build-id=none \
    -Wl,--gc-sections \
    -DSMALLBIN \
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
  cd "$ROOT/src/js3" || return 1
  compile "$DEST/js0-dl" gcc || return 1

  if which musl-gcc; then
    compile "$DEST/js0-static" musl-gcc -static || return 1
  else
    compile "$DEST/js0-static" gcc -static || return 1
  fi
}

main() {
  local DESTNAME DEST ROOT TMP
  readonly DESTNAME="$1"
  readonly ROOT="$(readlink -f "`dirname "$0"`/..")"

  [ -n "$DESTNAME" ] || {
    echo "usage: $0 <destdir>" >&2
    return 1
  }

  mkdir -p "$DESTNAME" || return 1
  readonly DEST="`readlink -f "$DESTNAME"`"
  cd "$ROOT" || return 1

  git ls-files |
  grep -E '\.(html?|js|css|sh)$' |
  xargs tar -c |
  tar -xC "$DEST"

  make_head || return 1
  make_dev || return 1
  make_doc || return 1
  bins || return 1
}

main "$@"
