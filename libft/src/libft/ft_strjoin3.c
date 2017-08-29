#include "libft.h"

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*new;

	if (!s1 && !s2 && !s3)
		return (NULL);
	if (!s2 && !s3)
		return (ft_strdup(s1));
	if (!s1 && !s3)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (ft_strdup(s3));
	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s1, s2));
	if (!(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3))))
		return (NULL);
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	ft_strcat(new, s3);
	return (new);
}
