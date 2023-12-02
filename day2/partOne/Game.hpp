#pragma once

//Streams
#include <fstream>
#include <iostream>
#include <sstream>

//Containers
#include <map>
#include <vector>

//Exception
#include <stdexcept>

//Other
#include <string>

class	Game
{
	private:
		std::ifstream					m_file;
		std::vector<std::string>		m_fileContent;
		std::map<std::string, size_t>	m_reference;
		size_t							m_count;

		Game(Game const &rhs);

		Game	&operator=(Game const &rhs);

		size_t	m_resultGame(std::string const &line);
		bool	m_isPossible(std::string const &input);

	public:

		class	FileError : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		Game();
		~Game();

		void	storeFile(std::string &path);
		size_t	getCount();
};
