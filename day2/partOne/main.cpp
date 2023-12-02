#include "Game.hpp"

int	main(int argc, char **argv)
{
	Game		game;
	std::string	input;
	size_t		count;

	if (argc != 2)
	{
		std::cerr << "Wrong ammount of argument!!" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	input = argv[1];
	try
	{
		game.storeFile(input);
	}
	catch(const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}
	count = game.getCount();
	std::cout << "The sum of valid games is: " << count << std::endl;
	return (0);
}