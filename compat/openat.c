/*******************************************************************************
  Copyright (c) 2014 Vladimir Kondratyev <vladimir@kondratyev.su>
  SPDX-License-Identifier: MIT

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*******************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>  /* mode_t */

#include <errno.h>  /* errno */
#include <fcntl.h>  /* open */
#include <stdarg.h> /* va_start */
#include <stdlib.h> /* free */

#include "compat.h"

int
openat (int fd, const char *path, int flags, ...)
{
    char *fullpath;
    int newfd, save_errno;
    mode_t mode;
    va_list ap;

    if (flags & O_CREAT) {
        va_start(ap, flags);
        mode = va_arg(ap, int);
        va_end(ap);
    } else {
        mode = 0;
    }

    fullpath = fd_concat (fd, path);
    if (fullpath == NULL) {
        return -1;
    }

    newfd = open (fullpath, flags, mode);

    save_errno = errno;
    free (fullpath);
    errno = save_errno;

    return newfd;
}
