# include "libft.h"

int	__sflush(FILE *fp)
{
	unsigned char	*p;
	int	n, t;
	t = fp->_flags;
	if ((t & __SWR) == 0)
		return (0);
	if ((p = fp->_bf._base) == NULL)
		return (0);
	n = fp->_p - p;		/* write this much */
	/*
	 * Set these immediately to avoid problems with longjmp and to allow
	 * exchange buffering (via setvbuf) in user write function.
	 */
	fp->_p = p;
	fp->_w = t & (__SLBF|__SNBF) ? 0 : fp->_bf._size;
	for (; n > 0; n -= t, p += t) {
		t = (*fp->_write)(fp->_cookie, (char *)p, n);
		if (t <= 0) {
			fp->_flags |= __SERR;
			return (EOF);
		}
	}
	return (0);
}

int	ft_fflush(FILE *fp)
{
	if (fp == NULL)
		return (0);
	if ((fp->_flags & (__SWR | __SRW)) == 0) {
		errno = EBADF;
		return (EOF);
	}
	return (__sflush(fp));
}