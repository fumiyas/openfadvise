openfadvise - Command wrapper to call posix_fadvise(2) after open(2)
======================================================================

  * Copyright (c) 2012-2014 SATOH Fumiyasu @ OSS Technology Corp., Japan
  * License: GNU General Public License version 3
  * URL: <https://github.com/fumiyas/openfadvise>
  * Blog: <http://fumiyas.github.io/>
  * Twitter: <https://twitter.com/satoh_fumiyasu>

Usage
----------------------------------------------------------------------

``` console
$ openfadvise noreuse grep foo /path/to/largefile
```

or:

``` console
$ LD_PRELOAD=`pwd`/openfadvise.so OPENFADVISE_ADVISE=noreuse \
  grep foo /path/to/largefile
```

Available values for `$OPENFADVISE_ADVISE` (see `posix_fadvise`(2)):

  * `normal`
    * `POSIX_FADV_NORMAL`: Indicates that the application has no
      advice to give about its access pattern for the specified
      data.
  * `sequential`
    * `POSIX_FADV_SEQUENTIAL`: The application expects to access
      the specified data sequentially (with lower offsets read
      before higher ones).
  * `random`
    * `POSIX_FADV_RANDOM`: The specified data will be accessed
      in random order.
  * `noreuse`
    * `POSIX_FADV_NOREUSE`: The specified data will be accessed
      only once.
  * `willneed`
    * `POSIX_FADV_WILLNEED`: The specified data will be accessed
      in the near future.
  * `dontneed`
    * `POSIX_FADV_DONTNEED`: The specified data will not be
      accessed in the near future.

Note
----------------------------------------------------------------------

I heard current Linux kernel does NOT support `POSIX_FADV_NOREUSE`.

  * https://twitter.com/kosaki55tea/status/459173892062720000

See also:

  * linux-ftools - Linux command line tools for fallocate, fincore, fadvise, etc
    * http://code.google.com/p/linux-ftools/

GNU `cat`(1) calls `fadvise64(fd, 0, 0, POSIX_FADV_SEQUENTIAL)`
after `open`(2) for all input files, thus `openfadvise` does not affect.

TODO
----------------------------------------------------------------------

```
$ openfadvise noreuse="*.log" rsyslog ...
```

```
$ openfadvise noreuse="/var/log/" rsyslog ...
```

