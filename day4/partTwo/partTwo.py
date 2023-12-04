import sys

class games:

	#Constructor of the class.
	def __init__(self, cards):
		self.__repetition = 1
		self.__temp = cards.split(' | ')
		self.__winner = self.__temp[0].split()
		self.__cardNumbers = self.__temp[1].split()
		self.__winner = self.__iterateList(self.__winner)
		self.__cardNumbers = self.__iterateList(self.__cardNumbers)
		self.__points = self.__findNumbers()
	
	#This private method iterates a list with strings and converts it in
	#a list of integers.
	def __iterateList(self, list):
		i = 0
		for toNumber in list:
			list[i] = int(toNumber)
			i += 1
		return list
	
	#This function find the ocurrences between winner and cardNumbers.
	def __findNumbers(self):
		points = 0
		for winnerIter in self.__winner:
			for numbersIter in self.__cardNumbers:
				if winnerIter == numbersIter:
					points += 1
		return points
	
	#This function returns the value of winning ocurrences.
	def getPoints(self):
		return self.__points

	def getRepetition(self):
		return self.__repetition

	def increaseRepetition(self):
		self.__repetition += 1

#This function interates the gameList to establish the ammount
#of duplication of every card.

def	iterateDuplicates(start, end, gameList, length, repetition):
	while start <= end and start < length:
		i = 0
		while i < repetition:
			gameList[start].increaseRepetition()
			i += 1
		start += 1

#This function return the total ammount of scratchCards
#considering the duplication of cards.
def getAmmountScrathCards(gameList):
	length = len(gameList)
	result = 0
	winAmmount = 0
	i = 0
	for points in gameList:
		winAmmount = points.getPoints()
		iterateDuplicates((i + 1), (winAmmount + i), gameList, length, points.getRepetition())
		result += points.getRepetition()
		i += 1
	return result

#This function return a list of games objects.
def getGameList(cards):
	gameList = []
	for card in cards:
		gameList.append(games(card))
	return gameList


#This function trimms the game number part to deal better with the inputs.
def	removeGameLayer(cards):
	i = 0
	colon = cards[0].find(':')
	colon += 2
	for game in cards:
		cards[i] = game[colon:]
		i += 1
	return (cards)

#This function checks if the file can be open and read and returns the
#document as a string.
def openFile(arguments):
	try:
		file = open(arguments[1], "r")
		document = file.read()
	except FileNotFoundError:
		print("File not found!!")
		exit(1)
	except FileExistsError:
		print("It was an issue reading the file!!")
		file.close()
		exit(1)
	file.close()
	return document

#This function check the arguments given to the program and creates the objects
#to solve the puzzle
if __name__ == "__main__":
	arguments = sys.argv
	if (len(arguments) != 2):
		print("Invalid ammount of arguments!!")
		exit(1)
	document = openFile(arguments)
	cards = document.split('\n')
	cards = removeGameLayer(cards)
	gameList = getGameList(cards)
	result = getAmmountScrathCards(gameList)
	print(f"The ammount of scrathcards is: {result}")