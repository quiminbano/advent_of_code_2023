def	getSum(number):
	result = 0
	for num in number:
		result += num
	return result

def getNumbers(lines):
	list = []
	for member in lines:
		result = ""
		length = len(member)
		j = length
		i = 0
		for i in range(0, length, 1):
			if (member[i].isdigit()):
				break
		if (i == length):
			list.append(0)
			continue
		for j in range(length - 1, -1, -1):
			if (member[j].isdigit()):
				break
		result = member[i] + member[j]
		list.append(int(result))
	return list

def	findLast(temp, words, numbers):
	i = 0
	ocurrences = []
	reversed = temp[::-1]
	for i in range(0, 9):
		dict = {}
		index = reversed.find(words[i][::-1])
		if not index == -1:
			dict['index'] = index
			dict['value'] = i
			ocurrences.append(dict)
	length = len(ocurrences)
	if (length > 0):
		ocurrences.sort(key=lambda x : x['index'])
		part1 = reversed[0:ocurrences[0]['index']]
		part2 = reversed[ocurrences[0]['index'] + len(words[ocurrences[0]['value']]):]
		reversed = part1 + numbers[ocurrences[0]['value']] + part2
	return reversed[::-1]

def	processOverlapping(ocurrences, words, temp):
	index = ocurrences[0]['index']
	value = ocurrences[1]['value']
	length = len(words[value])
	size = len(ocurrences)
	i = 0
	while i < size:
		if i == 0:
			i += 1
			continue
		if (ocurrences[i]['index'] < (index + length)):
			break
		i += 1
	if i == size:
		return temp
	diff = ((index + length) - ocurrences[i]['index'])
	part1 = temp[0:(index + length)]
	part2 = temp[(index + length):]
	i = 0
	while i < diff:
		part1 += words[value][i]
		i += 1
	temp = part1 + part2
	return temp

def	findFirst(temp, words, numbers):
	i = 0
	ocurrences = []
	for i in range(0, 9):
		dict = {}
		index = temp.find(words[i])
		if not index == -1:
			dict['index'] = index
			dict['value'] = i
			ocurrences.append(dict)
	length = len(ocurrences)
	if (length > 0):
		ocurrences.sort(key=lambda x : x['index'])
		if (length > 1):
			temp = processOverlapping(ocurrences, words, temp)
		part1 = temp[0:ocurrences[0]['index']]
		part2 = temp[ocurrences[0]['index'] + len(words[ocurrences[0]['value']]):]
		temp = part1 + numbers[ocurrences[0]['value']] + part2
	return temp
	

def	reWriteNumbers(lines):
	list = []
	words = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]
	numbers = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
	for sentence in lines:
		temp = sentence
		temp = findFirst(temp, words, numbers)
		temp = findLast(temp, words, numbers)
		list.append(temp)
	return list

def	parseFile(document):
	list = []
	list = document.split("\n")
	return list

def	getFile():
	try:
		with open("input.txt", "r") as file:
			document = file.read()
	except FileNotFoundError:
		print("File not found!")
		exit(1)
	except FileExistsError:
		print("There was some issue opening the file!")
		exit(1)
	file.close()
	return document

if __name__ == "__main__":
	document = getFile()
	lines = parseFile(document)
	newLines = reWriteNumbers(lines)
	numbers = getNumbers(newLines)
	sum = getSum(numbers)
	print(sum)