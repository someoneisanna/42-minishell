#include "../libft/libft.h"

int main(void)
{
	char *str = "hello $HOME";

}

void	ft_expand_command(t_token *token)
{
	char	*key
	char	*value;

	while (ft_strchr(token->content, '$') != NULL)
	{
		key = ft_get_key(token->content);
		if (ft_strncmp(var_to_expand, "$?", 2) == 0)
			value = ft_itoa("22"); //create a exit status variable
		else
			value = ft_get_env_value(key);
		token->content = ft_replace_content(token->content, key, value);
	}
}

char	*ft_get_key(char *cmd)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = ft_strnstr(cmd, "$", ft_strlen(cmd));
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	while (tmp[len + 1] == '_' || ft_isalnum(tmp[len + 1]) == YES)
		len++;
	return (ft_substr(tmp, 0, len + 1));
}
