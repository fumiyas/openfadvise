#!/bin/sh

if [ $# -lt 2 ]; then
  echo "Usage: $0 ADVISE COMMAND [ARGUEMNT ...]" 1>&2
  exit 1
fi

LD_PRELOAD="${LD_PRELOAD:+$LD_PRELOAD:}@libdir@/openfadvise.so"
OPENFADVISE_ADVISE="$1"; shift
export LD_PRELOAD OPENFADVISE_ADVISE

exec "$@"

