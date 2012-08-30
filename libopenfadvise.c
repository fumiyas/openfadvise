/*
   open(2) / openat(2) wrapper to call posix_fadvise(3) after open
   Copyright (C) 2012 SATOH Fumiyasu @ OSS Technology Corp, Japan

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

#include <stdarg.h>
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

static int advise = -1;

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
    /* FIXME: Read from env */
    advise = POSIX_FADV_NOREUSE;
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
    /* FIXME: Read from env */
    advise = POSIX_FADV_NOREUSE;
  }

  advise_errno = posix_fadvise(fd, 0, 0, advise);
  if (advise_errno != 0) {
    /* FIXME: Warn */
  }

  return fd;
}

