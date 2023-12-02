#include "Game.hpp"

Game::Game()
{
	m_reference["red"] = 12;
	m_reference["green"] = 13;
	m_reference["blue"] = 14;
	m_count = 0;
	return ;
}

Game::~Game()
{
	return ;
}

void	Game::storeFile(std::string &path)
{
	std::string	input;

	m_file.open(path);
	if (m_file.fail() == true)
		throw FileError();
	while (std::getline(m_file, input))
	{
		m_fileContent.push_back(input);
		input.clear();
	}
	m_file.close();
}

size_t	Game::getCount()
{
	size_t	number;

	for (auto &i : m_fileContent)
	{
		number = m_resultGame(i);
		m_count += number;
	}
	return (m_count);
}

size_t	Game::m_resultGame(std::string const &line)
{
	std::string	templ;
	std::string	number;
	std::string	game;
	size_t		index;
	size_t		pos;
	size_t		result;

	templ = line;
	index = templ.find(':');
	number = templ.substr(5, index);
	game = templ.substr(index + 2);
	pos = game.find(';');
	while (pos != std::string::npos)
	{
		game.replace(pos, 1, "");
		pos = game.find(';');
	}
	pos = game.find(',');
	while (pos != std::string::npos)
	{
		game.replace(pos, 1, "");
		pos = game.find(',');
	}
	if (m_isPossible(game) == true)
	{
		try
		{
			result = std::stoi(number);
		}
		catch (const std::exception &e)
		{
			result = 0;
		}
	}
	else
		result = 0;
	return (result);
}

bool	Game::m_isPossible(std::string const &input)
{
	size_t						i;
	size_t						extracted;
	std::istringstream			iss(input);
	std::string					temp;
	std::vector<std::string>	split;

	i = 0;
	split.clear();
	temp.clear();
	while (std::getline(iss, temp, ' '))
	{
		split.push_back(temp);
		temp.clear();
	}
	for (auto &string : split)
	{
		if (i % 2 == 0)
		{
			try
			{
				extracted = std::stoi(string);
			}
			catch (const std::exception &e)
			{
				extracted = 0;
			}
		}
		else
		{
			if (m_reference.find(string)->second < extracted)
				return (false);
		}
		i++;
	}
	return (true);
}

const char	*Game::FileError::what() const throw()
{
	return ("There was an issue with the file!!");
}