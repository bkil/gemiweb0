#!/bin/sh
# Copyright (C) 2023 bkil.hu
# Refer to the GNU GPL v2 in LICENSE for terms

to() {
  local CASE GIVEIN EXPOUT GOTOUT GOTRET
  readonly CASE="$1"
  readonly GIVEIN="$2"
  readonly EXPOUT="`printf "$3"`"

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

  readonly TKF="tmp.systest.in.js"
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
  to "$C" '42' '42.\nEOF'
  to "$C" '42\n' '42.\nEOF'
  to "$C" '42\n69\n' '42.\n69.\nEOF'

  tk "console.log('hi')" 0 'hi'
  tk "console.log('hel');console.log('lo')" 0 'hel\nlo'
  tk "console.log('hel'+String.fromCharCode(10)+'lo')" 0 'hel\nlo'

  tk "process.stdin.on('data', undefined)" 0 ''
  tk "process.stdin.on()" -2 ''
  tk "process.stdin.on(2)" -2 ''
  tk "process.stdin.on('bad')" -2 ''
  tk "process.stdin.on('data')" -2 ''
  tk "process.stdin.removeAllListeners()" -2 ''
  tk "process.stdin.removeAllListeners(2)" -2 ''
}

tn() {
  local GIVEIN EXPNET EXPOUT C TNF GOTRET GOTOUT PID
  readonly GIVEIN="$1"
  readonly EXPNET="`printf "$2"`"
  readonly EXPOUT="`printf "$3"`"
  readonly TNF="tmp.sock.out.txt"

  if [ "$PORT" -ge 1024 ]; then
    {
      printf "$GIVEIN" |
      nc -l -q 1 "$PORT" > "$TNF"
    } &
    PID=$!
  fi

  GOTOUT="`eval "$C"`"
  GOTRET="$?"
  [ "$GOTRET" -ge 128 ] && GOTRET=$((GOTRET - 256))

  [ "$PORT" -ge 1024 ] &&
    wait "$PID"

  GOTNET="`cat "$TNF" 2>/dev/null`"

  if ! [ "$GOTRET" = 0 ]; then
    printf "failed status for network \"%s\", expected 0, error %s\n" "$C $GIVEIN" "$GOTRET" >&2
    FAILS=$((FAILS+1))
  elif ! [ "$GOTNET" = "$EXPNET" ]; then
    printf "failed data over network \"%s\", expect: \"%s\", got: \"%s\"\n" "$C $GIVEIN" "$EXPNET" "$GOTNET" >&2
    FAILS=$((FAILS+1))
  elif ! [ "$GOTOUT" = "$EXPOUT" ]; then
    printf "failed output for network \"%s\", expect: \"%s\", got: \"%s\"\n" "$C $GIVEIN" "$EXPOUT" "$GOTOUT" >&2
    FAILS=$((FAILS+1))
  else
    SUCC=$((SUCC+1))
  fi

  rm "$TNF" 2>/dev/null
}

test_network() {
  local PORT C
  PORT="21198"

  C="$B test-sock-end.js </dev/null"
  tn "" ":connected" "!connected\n!writebad,expecting String argument (;\n  } catch (e) {\n    console.lo...)\n!end"

  C="$B test-sock-conex.js </dev/null"
  tn "" "" "!throw\n!error"

  C="$B test-sock-coner.js </dev/null"
  tn "" "" "!fatal\n!error"

  C="$B test-sock.js </dev/null"

  #TODO: sleeps for 1 second, should kill nc instead
  tn "" ":connected" "!connected\n!eof,"

  tn "?bye" ":connected" "!connected\n!bye,?bye"
  tn "?ping?bye" ":connected:pong" "!connected\n!pong\n!bye,?ping?bye"

  PORT="1"
  tn "-" "" "!error"

  tk "var n=require('node:net'); var o=new Object; o.host='-'; o.port=1; var c=n.createConnection(o); c.on('error', function(e){console.log(e)}); c.on('connect',function(){})" 0 'failed to get address of host'
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
  test_network

  if [ "$FAILS" = 0 ]; then
    printf "All %d system tests successful\n" "$SUCC" >&2
  else
    printf "%s system tests failed\n" "$FAILS" >&2
    return 1
  fi
}

main "$@"
