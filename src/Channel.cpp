/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:34:24 by gacorrei          #+#    #+#             */
/*   Updated: 2023/12/06 19:43:02 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
	:_name(""), _password(""), _topic("No topic is set"), _topic_mode(false), 
	_channel_limit(0), _channel_invite_only(false)
{
	//std::cout << CYAN << "Channel: Default constructor called" << RESET
	//	<< std::endl;
	_vectors[0] = "clients";
	_vectors[1] = "operators";
	_vectors[2] = "banned";
	_vectors[3] = "invited";
}

/* Parameter constructor: only name as parameter*/
Channel::Channel(std::string name)
	:_name(name), _password(""), _topic("No topic is set"), _topic_mode(false), 
		_channel_limit(0), _channel_invite_only(false)
{
	//std::cout << CYAN << "Channel: Parameter constructor called" << RESET
	//	<< std::endl;
	_vectors[0] = "clients";
	_vectors[1] = "operators";
	_vectors[2] = "banned";
	_vectors[3] = "invited";
}

/* Parameter constructor: name and pass*/
Channel::Channel(std::string name, std::string password)
	:_name(name), _password(password), _topic("No topic is set"), _topic_mode(false),
	_channel_limit(0), _channel_invite_only(false)
{
	//std::cout << CYAN << "Channel: Parameter constructor called" << RESET
	//	<< std::endl;
	_vectors[0] = "clients";
	_vectors[1] = "operators";
	_vectors[2] = "banned";
	_vectors[3] = "invited";
}

/* Copy constructor */
Channel::Channel(const Channel &copy)
{
	//std::cout << CYAN << "Channel: Copy constructor called" << RESET
	//	<< std::endl;
	*this = copy;
}

/* Destructor */
Channel::~Channel(void)
{
	//std::cout << RED << "Channel: Destructor called" << RESET << std::endl;
}

/* Operator overload */
Channel	&Channel::operator=(const Channel &copy)
{
	if (this != &copy) // this prevents self-assignment. Ex: Channel c1; c1 = c1;
	{
		_name = copy._name;
		_password = copy._password;
		_topic = copy._topic;
		_topic_mode = copy._topic_mode;
		_channel_limit = copy._channel_limit;
		_channel_invite_only = copy._channel_invite_only;
		_clients_in_channel = copy._clients_in_channel;
		_clients_banned = copy._clients_banned;
		_clients_operator_channel = copy._clients_operator_channel;
		_clients_invited_to_channel = copy._clients_invited_to_channel;
		_vectors[0] = copy._vectors[0];
		_vectors[1] = copy._vectors[1];
		_vectors[2] = copy._vectors[2];
		_vectors[3] = copy._vectors[3];
	}
	return (*this);
}


bool	Channel::operator==(std::string copy)
{
	return (_name == copy);
}

/* Operator overload */
std::string	Channel::get_name(void) const
{
	return (_name);
}

/* set_name() sets the name of the channel. */
void	Channel::set_name(std::string name)
{
	_name = name;
}

/* get_password() returns the password of the channel. */
std::string	Channel::get_password(void) const
{
	return (_password);
}

/* set_password() sets the password of the channel. */
void	Channel::set_password(std::string password)
{
	_password = password;
}

/* get_topic() returns the topic of the channel. */
std::string	Channel::get_topic(void) const
{
	return (_topic);
}

/* set_topic() sets the topic of the channel. */
void	Channel::set_topic(std::string topic)
{
	_topic = topic;
}

/* get_topic_mode() returns true if the topic is settable. */
bool	Channel::get_topic_mode(void) const
{
	return (_topic_mode);
}

/* set_topic_mode() sets the topic to be settable. */
void	Channel::set_topic_mode(bool topic_mode)
{
	_topic_mode = topic_mode;
}

/* get_mode():
** 1. checks the modes of the channel by accessing the private variables
** 2. returns a string with the modes of the channel
*/
std::string	Channel::get_mode(void) const
{
	std::string	chanel_modes;

	// check if the channel is invite only
	if (_topic_mode == true)
		chanel_modes += "+t ";
	else
		chanel_modes += "-t ";
	// check if the channel has a password
	if (_password != "")
		chanel_modes += "+k ";
	else
		chanel_modes += "-k ";
	// check if the channel has a operator (need to looj in _clients_operator_channel)
	if (_clients_operator_channel.size() > 0)
		chanel_modes += "+o ";
	else
		chanel_modes += "-o ";
	// check if the channel is invite only
	if (_channel_invite_only)
		chanel_modes += "+i ";
	else
		chanel_modes += "-i ";
	// check if the channel has a limit
	if (_channel_limit > 0)
		chanel_modes += "+l";
	else
		chanel_modes += "-l";
	return (chanel_modes);
}


/* get_channel_limit() returns the maximum number of users allowed in the
 * channel. */
unsigned int	Channel::get_channel_limit(void) const
{
	return (_channel_limit);
}

/* set_channel_limit() sets the maximum number of users allowed in the channel.*/
void	Channel::set_channel_limit(unsigned int limit)
{
	_channel_limit = limit;
}

/* get_channel_invite_only() returns true if the channel is invite only. */
bool	Channel::get_channel_invite_only() const
{
	return (_channel_invite_only);
}

/* set_channel_invite_only() sets the channel to invite only. */
void	Channel::set_channel_invite_only(bool invite_only)
{
	_channel_invite_only = invite_only;
}

/* get_clients_in_channel() returns a vector of clients in the channel. */
std::vector<Client>	&Channel::get_clients_in_channel(void)
{
	return (_clients_in_channel);
}

/* add_client() adds a client to the channel. */
void	Channel::add_client(Client &client)
{
	_clients_in_channel.push_back(client);
}

/* remove_client() removes a client from the channel. */
void	Channel::remove_client(Client &client)
{
	std::vector<Client>::iterator	it = find(_clients_in_channel.begin(), _clients_in_channel.end(), client);

	if (it != _clients_in_channel.end())
		_clients_in_channel.erase(it);
}

/* get_clients_banned() returns a vector of clients banned from the channel. */
std::vector<Client> &Channel::get_clients_banned(void)
{
	return (_clients_banned);
}

/* 	add_client_to_banned_vector(Client &client) adds a client to the list of
 * 	banned clients. */
void	Channel::add_client_to_banned_vector(Client &client)
{
	_clients_banned.push_back(client);
}

/* remove_client_from_banned_vector() removes a client from the list of banned
 * clients. */
void	Channel::remove_client_from_banned_vector(Client &client)
{
	std::vector<Client>::iterator	it = find(_clients_banned.begin(), _clients_banned.end(), client);

	if (it != _clients_banned.end())
		_clients_banned.erase(it);
}

/* get_clients_operator_channel() returns a vector of clients that are
 * operators in the channel. */
std::vector<Client> &Channel::get_clients_operator_channel(void)
{
	return (_clients_operator_channel);
}

/* add_client_to_clients_operator_vector adds a client to the list of operators
 * in the channel. */
void	Channel::add_client_to_clients_operator_vector(Client &client)
{
	_clients_operator_channel.push_back(client);
}

Client	&Channel::get_operator()
{
	return (_clients_operator_channel[0]);
}

void	Channel::check_operator()
{
	if (_clients_operator_channel.size() == 0 && _clients_in_channel.size() > 0)
	{
		_clients_operator_channel.push_back(_clients_in_channel[0]);
		_clients_in_channel[0].set_is_admin(true);		
	}
}

/* remove_client_from_clients_operator_vector() removes a client from the list
 * of operators in the channel. */
void	Channel::remove_client_from_clients_operator_vector(Client &client)
{
	std::vector<Client>::iterator	it = find(_clients_operator_channel.begin(), _clients_operator_channel.end(), client);

	if (it != _clients_operator_channel.end())
		_clients_operator_channel.erase(it);
}

/* get_clients_invited_to_channel() returns a vector of clients that have voice
 * in the channel. */
std::vector<Client> &Channel::get_clients_invited_to_channel(void)
{
	return (_clients_invited_to_channel);
}

/* add_client_invited_to_channel() adds a client to the list of clients that
 * have voice in the channel. */
void	Channel::add_client_to_clients_invited_vector(Client &client)
{
	_clients_invited_to_channel.push_back(client);
}

/* remove_client_invited_to_channel() removes a client from the list of clients
 * that have voice in the channel. */
void	Channel::remove_client_from_clients_invited_vector(Client &client)
{
	std::vector<Client>::iterator	it = find(_clients_invited_to_channel.begin(), _clients_invited_to_channel.end(), client);

	if (it != _clients_invited_to_channel.end())
		_clients_invited_to_channel.erase(it);
}

/* find_client() returns a pointer to the client if it is found in the channel.
 * Otherwise, it returns NULL. */
Client	*Channel::find_client(std::string nickname, std::string vector)
{
	unsigned int					i = 0;
	std::vector<Client>::iterator	it;
	std::vector<Client>::iterator	end;

	for (; i < vector.size(); i++)
	{
		if (_vectors[i] == vector)
			break;
	}
	switch (i)
	{
		case 0:
			end = _clients_in_channel.end();
			it = find(_clients_in_channel.begin(), end, nickname);
			break;
		case 1:
			end = _clients_operator_channel.end();
			it = find(_clients_operator_channel.begin(), end, nickname);
			break;
		case 2:
			end = _clients_banned.end();
			it = find(_clients_banned.begin(), end, nickname);
			break;
		case 3:
			end = _clients_invited_to_channel.end();
			it = find(_clients_invited_to_channel.begin(), end, nickname);
			break;
		default:
			return NULL;
	}
	if (it == end)
		return (NULL);
	return (it.base());
}

void	Channel::message(Client &client, std::string msg)
{
	std::vector<Client>::iterator		it = _clients_in_channel.begin();
	int									fd;
	std::string	final_msg = ":" + client.get_nickname() + "!"
	+ client.get_username() + "@" + "localhost" + " PRIVMSG "
	+ _name + " :" + msg + "\r\n";

	for (; it < _clients_in_channel.end(); it++)
	{
		if (*it == client)
			continue;
		fd = it->get_client_fd();
		send(fd, final_msg.c_str(), final_msg.length(), MSG_NOSIGNAL);
	}
}

void	Channel::message(Client &client, std::string msg, std::string code)
{
	std::vector<Client>::iterator		it = _clients_in_channel.begin();
	int									fd;
	std::string	final_msg = ":localhost! " + code + " " + client.get_nickname()
							+ " " + _name + " :" + msg + "\r\n";

	for (; it < _clients_in_channel.end(); it++)
	{
		if (*it == client)
			continue;
		fd = it->get_client_fd();
		send(fd, final_msg.c_str(), final_msg.length(), MSG_NOSIGNAL);
	}
}

void	Channel::info_message(std::string msg)
{
	std::vector<Client>::iterator	it = _clients_in_channel.begin();
	int								fd;

	for (; it < _clients_in_channel.end(); it++)
	{
		fd = it->get_client_fd();
		sendMessage(fd, msg);
	}
}

int Channel::sendMessage(int client_fd, const std::string &successMessage)
{
	if (send(client_fd, successMessage.c_str(), successMessage.size(), MSG_NOSIGNAL) == -1)
	{
		std::cerr << RED << "Error: " << RESET << "send() failed" << std::endl;
		return (-1);
	}
	return (0);
}
