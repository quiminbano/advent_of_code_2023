#include "ProcessData.hpp"

ProcessData::ProcessData() : m_fail(false)
{
	m_keys.push_back("seed-to-soil");
	m_keys.push_back("soil-to-fertilizer");
	m_keys.push_back("fertilizer-to-water");
	m_keys.push_back("water-to-light");
	m_keys.push_back("light-to-temperature");
	m_keys.push_back("temperature-to-humidity");
	m_keys.push_back("humidity-to-location");
}

ProcessData::~ProcessData()
{

}

const bool	&ProcessData::fail() const
{
	return (m_fail);
}

void	ProcessData::processData(std::string const &path)
{
	std::string							line;
	std::vector<std::string>			split;

	m_file.open(path);
	if (m_file.fail() == true)
	{
		m_fail = true;
		return ;
	}
	while (std::getline(m_file, line))
	{
		line.append("\n");
		m_document.append(line);
		line.clear();
	}
	split = m_split(m_document, '\n');
	if (m_fillContainers(split) == 1)
	{
		m_fail = true;
		return ;
	}
	m_findValues();
}

std::vector<std::string>	ProcessData::m_split(std::string const &haystack, char const &c)
{
	std::vector<std::string>	split;
	std::string					temp;
	std::istringstream			iss;

	iss.str(haystack);
	temp.clear();
	while (std::getline(iss, temp, c))
	{
		if (iss.fail() == true)
		{
			split.clear();
			break ;
		}
		if (!temp.size())
			continue ;
		split.push_back(temp);
	}
	if (!split.back().compare("\n"))
		split.pop_back();
	return(split);
}

int	ProcessData::m_fillContainers(std::vector<std::string> const &split)
{
	std::vector<std::string>	templ;
	int							flag;
	int							ret;

	flag = -1;
	for (auto &iter : split)
	{
		templ.clear();
		if (flag == -1 && iter.find("seeds:") != std::string::npos)
		{
			templ = m_split(iter, ' ');
			templ.erase(templ.begin());
			for (auto &seeds : templ)
			{
				try
				{
					m_seed.push_back(std::stoul(seeds));
				}
				catch(const std::exception& e)
				{
					return (1);
				}	
			}
			flag = 0;
		}
		else if (flag == 0 && iter.find(m_keys[0]) != std::string::npos)
			flag = 1;
		else if (flag == 1 && iter.find(m_keys[1]) != std::string::npos)
			flag = 2;
		else if (flag == 2 && iter.find(m_keys[2]) != std::string::npos)
			flag = 3;
		else if (flag == 3 && iter.find(m_keys[3]) != std::string::npos)
			flag = 4;
		else if (flag == 4 && iter.find(m_keys[4]) != std::string::npos)
			flag = 5;
		else if (flag == 5 && iter.find(m_keys[5]) != std::string::npos)
			flag = 6;
		else if (flag == 6 && iter.find(m_keys[6]) != std::string::npos)
			flag = 7;
		else
		{
			if (flag > -1)
			{
				ret = m_fillMaps(m_keys[flag - 1], iter);
				if (ret == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	ProcessData::m_fillMaps(std::string const &key, std::string const &iter)
{
 	std::vector<std::string>	templ;
	size_t						destination;
	size_t						source;
	size_t						length;

	templ = m_split(iter, ' ');
	if (templ.size() != 3)
		return (1);
	try
	{
		destination = std::stoul(templ[0]);
		source = std::stoul(templ[1]);
		length = std::stoul(templ[2]);
	}
	catch(const std::exception& e)
	{
		return (1);
	}
	m_seedToLocation[key].push_back(std::make_tuple(destination, source, length));
	return (0);
}

void	ProcessData::m_findValues()
{
	size_t	location;

	for (auto &iter : m_seed)
	{	
		location = iter;
		for (auto &keys : m_keys)
			location = m_toLocation(keys, location);
		m_locations.push_back(location);
	}
}

size_t	ProcessData::m_toLocation(std::string const &key, size_t location)
{
	size_t	i;
	size_t	dest;
	size_t	source;
	size_t	length;
	std::vector<std::tuple<size_t, size_t, size_t>>	temp;

	temp = m_seedToLocation.find(key)->second;
	for (auto &vec : temp)
	{
		i = 0;
		dest = std::get<0>(vec);
		source = std::get<1>(vec);
		length = std::get<2>(vec);
		if ((location < source) || (location > (source + (length - 1))))
			continue ;
		while (i < length)
		{
			if (location == (source + i))
				return (dest + i);
			i++;
		}
	}
	return (location);
}

size_t	ProcessData::getSmallestLocation()
{
	std::sort(m_locations.begin(), m_locations.end());
	return (*(m_locations.begin()));
}
