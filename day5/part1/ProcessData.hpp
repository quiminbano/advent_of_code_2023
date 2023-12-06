#pragma once

//Strings
#include <string>

//Containers
#include <map>
#include <vector>

//Streams
#include <iostream>
#include <sstream>
#include <fstream>

//Algorhithm
#include <algorithm>

class ProcessData
{
private:
	bool																	m_fail;
	std::vector<size_t>														m_seed;
	std::vector<size_t>														m_locations;
	size_t																	m_smallestLength;
	std::vector<std::string>												m_keys;
	std::ifstream															m_file;
	std::string																m_document;
	std::map<std::string, std::vector<std::tuple<size_t, size_t, size_t>>>	m_seedToLocation;

	ProcessData(ProcessData const &rhs);

	ProcessData	&operator=(ProcessData const &rhs);

	std::vector<std::string>	m_split(std::string const &haystack, char const &c);
	int							m_fillContainers(std::vector<std::string> const &split);
	int							m_fillMaps(std::string const &key, std::string const &iter);
	void						m_findValues();
	size_t						m_toLocation(std::string const &key, size_t location);

public:
	ProcessData();
	~ProcessData();

	const bool	&fail() const;
	void		processData(std::string const &path);
	size_t		getSmallestLocation();
};
