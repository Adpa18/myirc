/*
** error.h for include
**
** Made by	Axel Vencatareddy
** Login	vencat_a
**
** Started on	Wed May 18 11:31:05 2016 Axel Vencatareddy
** Last update	Wed May 18 12:07:34 2016 Axel Vencatareddy
*/

#ifndef ERROR_H_
# define ERROR_H_

# define ERR_UNKNOWCMD          "421"
# define ERR_NEEDMOREPARAMS     "461"

//NICK
# define ERR_NONICKNAMEGIVEN    "431"
# define ERR_ERRONEUSNICKNAME	"432"
# define ERR_NICKNAMEINUSE      "433"

//PART
# define ERR_NOTONCHANNEL	    "442"

//PRIVMSG
# define ERR_NOSUCHNICK         "401"
# define ERR_NORECIPIENT	    "411"
# define ERR_NOTEXTTOSEND	    "412"

//USER
# define ERR_NOTREGISTERED      "451"
# define ERR_ALREADYREGISTERED  "462"

// JOIN
# define ERR_NOSUCHCHANNEL      "403"

//LIST
# define RPL_LISTSTART          "321"
# define RPL_LIST		        "322"
# define RPL_LISTEND		    "323"

//USERS
# define RPL_USERSSTART         "392"
# define RPL_USERS              "393"
# define RPL_ENDOFUSERS         "394"
# define RPL_NOUSERS            "395"

//NAMES
# define RPL_NAMREPLY		    "353"
# define RPL_ENDOFNAMES		    "366"

#endif /* !ERROR_H_ */