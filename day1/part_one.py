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
	return document

if __name__ == "__main__":
	document = getFile()
	lines = parseFile(document)
	numbers = getNumbers(lines)
	sum = getSum(numbers)
	print(sum)
