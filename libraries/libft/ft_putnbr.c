#include "libft.h"

void	ft_putnbr(long n)
{
	char	digit;

	if (n == -2147483648)
	{
		digit = '8';
		write(1, "-", 1);
		ft_putnbr(214748364);
	}
	else
	{
		if (n < 0)
		{
			n = -n;
			write(1, "-", 1);
		}
		if (n < 10)
			digit = n + 48;
		else
			digit = (n % 10) + 48;
		if (n > 9)
			ft_putnbr(n / 10);
	}
	write(1, &digit, 1);
}
