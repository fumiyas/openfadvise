/*
   open(2) wrapper to call posix_fadvise(2) after opening a file
   Copyright (C) 2012-2014 SATOH Fumiyasu @ OSS Technology Corp., Japan
		 <https://github.com/fumiyas/openfadvise>
		 <http://fumiyas.github.io/>
                 <http://www.OSSTech.co.jp/>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>

#define real_open2(fname, flags) \
  (syscall(SYS_open, (fname), (flags)))
#define real_open3(fname, flags, mode) \
  (syscall(SYS_open, (fname), (flags), (mode)))

#define real_openat2(dirfd, fname, flags) \
  (syscall(SYS_openat, (dirfd), (fname), (flags)))
#define real_openat3(dirfd, fname, flags, mode) \
  (syscall(SYS_openat, (dirfd), (fname), (flags), (mode)))

#define strequal(s1, s2) (strcmp((s1), (s2)) == 0)

#define ADVISE_DEFAULT	POSIX_FADV_NORMAL

static int advise = -1;

static inline int advise_from_env(void)
{
  const char *advise_str = getenv("OPENFADVISE_ADVISE");

  if (advise_str == NULL) {
    return ADVISE_DEFAULT;
  }

  if (strequal(advise_str, "normal")) {
    return POSIX_FADV_NORMAL;
  }
  if (strequal(advise_str, "sequential")) {
    return POSIX_FADV_SEQUENTIAL;
  }
  if (strequal(advise_str, "random")) {
    return POSIX_FADV_RANDOM;
  }
  if (strequal(advise_str, "noreuse")) {
    return POSIX_FADV_NOREUSE;
  }
  if (strequal(advise_str, "willneed")) {
    return POSIX_FADV_WILLNEED;
  }
  if (strequal(advise_str, "dontneed")) {
    return POSIX_FADV_DONTNEED;
  }

  return ADVISE_DEFAULT;
}

int open(const char *fname, int flags, ...)
{
  va_list	arg_ptr;
  int		fd;
  int		advise_errno;

  if (flags & O_CREAT) {
    va_start(arg_ptr, flags);
    fd = real_open3(fname, flags, va_arg(arg_ptr, int));
    va_end(arg_ptr);
  }
  else {
    fd = real_open2(fname, flags);
  }

  if (fd == -1) {
    return -1;
  }

  if (advise == -1) {
    advise = advise_from_env();
  }

  advise_errno = posix_fadvise(fd, 0, 0, advise);
  if (advise_errno != 0) {
    /* FIXME: Warn */
  }

  return fd;
}

int openat(int dirfd, const char *fname, int flags, ...)
{
  va_list	arg_ptr;
  int		fd;
  int		advise_errno;

  if (flags & O_CREAT) {
    va_start(arg_ptr, flags);
    fd = real_openat3(dirfd, fname, flags, va_arg(arg_ptr, int));
    va_end(arg_ptr);
  }
  else {
    fd = real_openat2(dirfd, fname, flags);
  }

  if (fd == -1) {
    return -1;
  }

  if (advise == -1) {
    advise = advise_from_env();
  }

  advise_errno = posix_fadvise(fd, 0, 0, advise);
  if (advise_errno != 0) {
    /* FIXME: Warn */
  }

  return fd;
}

