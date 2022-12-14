#include <stdio.h>
#include <stdbool.h>

typedef enum
{
	OK = 0,
	Numbers = -1,
	Margin = -2,
	Scanning = -3,
	FileIsEmpty = -4
} StatesOfStructureErrors;

// все что угодно | число (мб начинается с нуля) | число (мб начинается с нуля)

int main()
{
	FILE *file = fopen("order.txt", "r");
	if (file == NULL)
	{
		printf("File not found!\n");
		return -2;
	}

	int amountOfProduct = 0;
	int priceOfProduct = 0;
	char currentChar = 0;
	char resultOfScanning = -1;
	char stateOfStructure = OK; // проверка на правильную структуру файла
	int overallCost = 0;

	while (stateOfStructure == OK)
	{
		currentChar = getc(file);
		if (currentChar == '\n')
		{
			stateOfStructure = Margin;
			break;
		} // Название товара без \n
		if (currentChar == -1)
		{
			stateOfStructure = FileIsEmpty;
			break;
		}

		while (currentChar != '\t')
		{
			currentChar = getc(file);
			if (currentChar == '\n') // ждем \t для перехода к количеству, перебираем символы названия
			{						 // если \n - то оно в названии => неправильное название
				stateOfStructure = Margin;
				break;
			}
		}

		currentChar = getc(file); // перебирали до \t, значит если дальше цифры => это количество товара
		if (!(currentChar >= '0' && currentChar <= '9'))
		{
			stateOfStructure = Margin;
			break;
		}
		ungetc(currentChar, file);

		resultOfScanning = fscanf(file, "%d", &amountOfProduct);
		if (resultOfScanning == 0)
		{
			stateOfStructure = Scanning;
			break;
		}
		if (amountOfProduct <= 0)
		{
			stateOfStructure = Numbers;
			break;
		}

		currentChar = getc(file);
		if (currentChar != '\t')
		{
			stateOfStructure = Numbers;
			break;
		}

		currentChar = getc(file);
		if (currentChar <= '0' || currentChar >= '9')
		{
			stateOfStructure = Margin;
			break;
		}
		ungetc(currentChar, file);

		resultOfScanning = fscanf(file, "%d", &priceOfProduct);
		if (resultOfScanning == 0)
		{
			stateOfStructure = Scanning;
			break;
		}
		if (priceOfProduct <= 0)
		{
			stateOfStructure = Numbers;
			break;
		}

		overallCost += amountOfProduct * priceOfProduct;
		currentChar = getc(file); // проверки на EOF и \n в конце файла/строки
		if (currentChar == -1)
		{
			break;
		}
		if (currentChar != '\n')
		{
			stateOfStructure = Margin;
			break;
		}
	}
	fclose(file);
	switch (stateOfStructure)
	{
	case OK:
		printf("The overall cost of all products in your file is %d\n", overallCost);
		break;
	case Numbers:
		printf("Numbers aren't right (<=0 or not only with digits)!\n");
		break;
	case Margin:
		printf("The margins are violated!\n");
		break;
	case Scanning:
		printf("The information fields are filled incorrectly!\n");
		break;
	case FileIsEmpty:
		printf("Your file is empty!\n");
		break;
	}

	return 0;
}