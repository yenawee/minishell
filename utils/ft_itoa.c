#include "../include/minishell.h"

static void	ft_strrev(char *s)
{
	int		len;
	int		i;
	char	temp;

	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		temp = s[i];
		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
		i++;
	}
}

static int	count_check(long long num, int *minus_check)
{
	int	count;

	count = 0;
	*minus_check = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		*minus_check = 1;
		num = -num;
	}
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

void	*make_rst(char *rst, long long num, int count, int *minus_check)
{
	int	i;

	i = 0;
	if (*minus_check)
		num *= -1;
	while (count--)
	{
		rst[i] = num % 10 + '0';
		num /= 10;
		i++;
	}
	if (*minus_check)
		rst[i++] = '-';
	rst[i] = '\0';
	return (rst);
}

char	*ft_itoa(int n)
{
	long long	num;
	int			minus_check;
	int			count;
	char		*rst;

	minus_check = 0;
	num = (long long)n;
	count = count_check(num, &minus_check);
	rst = (char *)malloc(sizeof(char) * count + minus_check + 1);
	if (!rst)
		return (NULL);
	make_rst(rst, num, count, &minus_check);
	ft_strrev(rst);
	return (rst);
}