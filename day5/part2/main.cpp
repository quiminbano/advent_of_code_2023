#include "ProcessData.hpp"

int	main(int ac, char **av)
{
	ProcessData	data;
	std::string	path;
	size_t		smallestLocation;

	if (ac != 2)
	{
		std::cerr << "Invalid ammount of parameters!!" << std::endl;
		exit(EXIT_FAILURE);
	}
	path = av[1];
	data.processData(path);
	if (data.fail() == true)
	{
		std::cerr << "Error processing the file!!" << std::endl;
		exit(EXIT_FAILURE);		
	}
	smallestLocation = data.getSmallestLocation();
	std::cout << "The smallest location is: " << smallestLocation << std::endl;
	return (0);
}
