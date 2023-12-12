#!/bin/sh

to() {
  local CASE GIVEIN EXPOUT GOTOUT GOTRET
  readonly CASE="$1"
  readonly GIVEIN="$2"
  readonly EXPOUT="$3"

  GOTOUT="`printf "$GIVEIN" | eval "$CASE"`"
  GOTRET="$?"
  [ "$GOTRET" -ge 128 ] && GOTRET=$((GOTRET - 256))

  if ! [ "$GOTRET" = 0 ]; then
    printf "failed status for \"%s\", expected 0, error %s\n" "$CASE" "$GOTRET" >&2
    FAILS=$((FAILS+1))
  elif ! [ "$GOTOUT" = "$EXPOUT" ]; then
    printf "failed output for \"%s\", expect: \"%s\", got: \"%s\"\n" "$CASE" "$EXPOUT" "$GOTOUT" >&2
    FAILS=$((FAILS+1))
  else
    SUCC=$((SUCC+1))
  fi
}

tk() {
  local TKF CASE EXPOUT EXPRET GOTOUT GOTRET
  readonly CASE="$1"
  readonly EXPRET="$2"
  readonly EXPOUT="`printf "$3"`"

  readonly TKF="tmp.js"
  echo "$CASE" > "$TKF"

  GOTOUT="`$B $TKF </dev/null`"
  GOTRET="$?"
  [ "$GOTRET" -ge 128 ] && GOTRET=$((GOTRET - 256))

  if ! [ "$GOTRET" = "$EXPRET" ]; then
    printf "failed status for \"%s\", expected %s, error %s\n" "$CASE" "$EXPRET" "$GOTRET" >&2
    FAILS=$((FAILS+1))
  elif ! [ "$GOTOUT" = "$EXPOUT" ]; then
    printf "failed output for \"%s\", expect: \"%s\", got: \"%s\"\n" "$CASE" "$EXPOUT" "$GOTOUT" >&2
    FAILS=$((FAILS+1))
  else
    SUCC=$((SUCC+1))
  fi
  rm "$TKF"
}

test_stdin() {
  local C
  readonly C="$B test-stdin.js"

  to "$C" '' 'EOF'
  to "$C" '42' '42.EOF'
  to "$C" '42\n' '42.EOF'
  to "$C" '42\n69\n' '42.69.EOF'

  tk "console.log('hi')" 0 'hi'
  tk "console.log('hel');console.log('lo')" 0 'hello'
  tk "console.log('hel'+String.fromCharCode(10)+'lo')" 0 'hel\nlo'

  tk "process.stdin.on('data', undefined)" 0 ''
  tk "process.stdin.on()" -2 ''
  tk "process.stdin.on(2)" -2 ''
  tk "process.stdin.on('bad')" -2 ''
  tk "process.stdin.on('data')" -2 ''
}

main() {
  local B FAILS SUCC
  FAILS=0
  SUCC=0
  [ $# -ge 1 ] || {
    echo "usage: $0 <jsrun_binary> [args]" >&2
    exit 1
  }
  readonly B="$*"

  test_stdin

  if [ "$FAILS" = 0 ]; then
    printf "All %d system tests successful\n" "$SUCC" >&2
  else
    printf "%s system tests failed\n" "$FAILS" >&2
    return 1
  fi
}

main "$@"
