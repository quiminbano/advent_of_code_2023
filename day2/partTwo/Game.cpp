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

size_t	Game::getPower()
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
	std::string	game;
	size_t		index;
	size_t		pos;
	size_t		result;

	templ = line;
	index = templ.find(':');
	game = templ.substr(index + 2);
	pos = game.find(',');
	while (pos != std::string::npos)
	{
		game.replace(pos, 1, "");
		pos = game.find(',');
	}
	result = m_getPower(game);
	return (result);
}

size_t	Game::m_getPower(std::string const &input)
{
	std::istringstream				iss(input);
	std::istringstream				iss2;
	std::string						set;
	std::string						diceValue;
	std::map<std::string, size_t>	mapColor;
	size_t							i;
	size_t							extracted;
	size_t							result;

	mapColor["red"] = 0;
	mapColor["green"] = 0;
	mapColor["blue"] = 0;
	result = 1;
	while (std::getline(iss, set, ';'))
	{
		i = 0;
		iss2.clear();
		if (set[0] == ' ')
			set = set.substr(1);
		iss2.str(set);
		while (std::getline(iss2, diceValue, ' '))
		{
			if (i % 2 == 0)
			{
				try
				{
					extracted = std::stoi(diceValue);
				}
				catch(const std::exception& e)
				{
					extracted = 0;
				}
			}
			else
			{
				if (mapColor.find(diceValue)->second < extracted)
					mapColor[diceValue] = extracted;
			}
			diceValue.clear();
			i++;
		}
	}
	for (auto &iter : mapColor)
		result *= iter.second;
	return (result);
}

const char	*Game::FileError::what() const throw()
{
	return ("There was an issue with the file!!");
}