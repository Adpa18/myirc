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

//NICK
# define ERR_NONICKNAMEGIVEN    "431 ERR_NONICKNAMEGIVEN"
# define ERR_NICKNAMEINUSE      "433 ERR_NICKNAMEINUSE"

//PART
# define ERR_NOTONCHANNEL	    "442 ERR_NOTONCHANNEL"

//PRIVMSG
# define ERR_NOSUCHNICK         "401 ERR_NOSUCHNICK"
# define ERR_NORECIPIENT	    "411 ERR_NORECIPIENT"
# define ERR_NOTEXTTOSEND	    "412 ERR_NOTEXTTOSEND"

//USER
# define ERR_ALREADYREGISTERED  "462 ERR_ALREADYREGISTRED"

// JOIN
# define ERR_NOSUCHCHANNEL "403 ERR_NOSUCHCHANNEL"

//AWAY (si on le fait)
# define RPL_AWAY		"301 RPL_AWAY \"<pseudo> :<message d'absence>\""

//LIST
# define RPL_LISTSTART		"321 RPL_LISTSTART \"Channel :Users Name\""
# define RPL_LIST		"322 RPL_LIST \"<canal> <# visible> :<sujet>\""
# define RPL_LISTEND		"323 RPL_LISTEND \":End of /LIST\""

//NAMES pour /users
# define RPL_NAMREPLY		"353 RPL_NAMREPLY \"<canal> :[[@|+]<pseudo> [[@|+]<pseudo> [...]]]\""
# define RPL_ENDOFNAMES		"366 RPL_ENDOFNAMES \"<canal> :End of /NAMES list\""

//PRIVMSG
// LE DESTINATAIRE N'EXISTE PAS
//# define ERR_NOSUCHNICK		"401 ERR_NOSUCHNICK \"<pseudonyme> :No such nick/channel\""
// LE CLIENT N'EST PAS DANS LE CHANNEL
# define ERR_CANNOTSENDTOCHAN	"404 ERR_CANNOTSENDTOCHAN \"<nom de canal> :Cannot send to channel\""
/*
** Renvoyé à un client qui essaie d'envoyer un PRIVMSG/NOTICE utilisant
** le format de destination utilisateur@hôte pour lequel utilisateur@hôte
** a plusieurs occurrences.
*/
# define ERR_TOOMANYTARGETS	"407 ERR_TOOMANYTARGETS \"<destination> :Duplicate recipients. No message delivered\""
// PAS DE  DESTINATAIRE
//# define ERR_NORECIPIENT	"411 ERR_NORECIPIENT \":No recipient given (PRIVMSG)\""
// PAS DE TEXTE A ENVOYER
//# define ERR_NOTEXTTOSEND	"412 ERR_NOTEXTTOSEND \":No text to send\""
// PAS NECESSAIRE POUR LE MYIRC
# define ERR_NOTOPLEVEL		"413 ERR_NOTOPLEVEL \"<masque> :No toplevel domain specified\""
// PAS NECESSAIRE POUR LE MYIRC
# define ERR_WILDTOPLEVEL	"414 ERR_WILDTOPLEVEL \"<masque> :Wildcard in toplevel domain\""

//JOIN
# define RPL_TOPIC		"332 RPL_TOPIC \"<canal> :<sujet>\""
//# define ERR_NOSUCHCHANNEL	"403 ERR_NOSUCHCHANNEL \"<nom de canal> :No such channel\""
# define ERR_TOOMANYCHANNELS	"405 ERR_TOOMANYCHANNELS \"<nom de canal> :You have joined too many channels\""
# define ERR_NEEDMOREPARAMS	"461 ERR_NEEDMOREPARAMS \"<commande> :Not enough parameters\""
# define ERR_CHANNELISFULL	"471 ERR_CHANNELISFULL \"<canal> :Cannot join channel (+l)\""
# define ERR_INVITEONLYCHAN	"473 ERR_INVITEONLYCHAN \"<canal> :Cannot join channel (+i)\""
# define ERR_BANNEDFROMCHAN	"474 ERR_BANNEDFROMCHAN \"<canal> :Cannot join channel (+b)\""
# define ERR_BADCHANNELKEY	"475 ERR_BADCHANNELKEY \"<canal> :Cannot join channel (+k)\""

//PART
//# define ERR_NOSUCHCHANNEL
//# define ERR_NOTONCHANNEL	"442 ERR_NOTONCHANNEL \"<canal> :You're not on that channel\""
//# define ERR_NEEDMOREPARAMS

//NICK
//# define ERR_NONICKNAMEGIVEN	"431 ERR_NONICKNAMEGIVEN \":No nickname given\""
//# define ERR_NICKNAMEINUSE	"433 ERR_NICKNAMEINUSE \"<nick> :Nickname is already in use\""
# define ERR_ERRONEUSNICKNAME	"432 ERR_ERRONEUSNICKNAME \"<pseudo> :Erroneus nickname\""
# define ERR_NICKCOLLISION	"436 ERR_NICKCOLLISION \"<nick> :Nickname collision KILL\""

//USER
//# define ERR_NEEDMOREPARAMS
//# define ERR_ALREADYREGISTERED	"462 ERR_ALREADYREGISTRED \":You may not reregister\""

#endif /* !ERROR_H_ */