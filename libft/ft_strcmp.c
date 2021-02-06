/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strcmp.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: syudai <syudai@student.42tokyo.jp>		 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/01/27 23:09:55 by syudai			#+#	#+#			 */
/*   Updated: 2021/01/27 23:10:08 by syudai		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	return (s1[i] > s2[i] ? 1 : -1);
}
