#include "stdafx.h"
#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct telephone_t {
	char *mark;
	char *firma;
	float weight;
	float price;
} telephone_t;

// получение массива телефонов из файла
telephone_t *read_telephones(const char *file_path, size_t &length) {
	length = 0;

	FILE *f = fopen(file_path, "r");

	if (!f) {
		cout << "Erorr during opening file " << file_path << endl;
		return NULL;
	}

	size_t capacity = 1;
	telephone_t *telephones = (telephone_t *)malloc(capacity * sizeof(telephone_t));
	telephones[0].mark = (char *)malloc(50 * sizeof(char));
	telephones[0].firma = (char *)malloc(50 * sizeof(char));

	while (!feof(f)) {
		fscanf(f, "%[^,], %[^,], %f, %f\n", telephones[length].mark, telephones[length].firma, &telephones[length].price, &telephones[length].weight);
		length++;

		if (length >= capacity)
			telephones = (telephone_t *) realloc(telephones, (capacity *= 2) * sizeof(telephone_t));

		telephones[length].mark = (char *)malloc(50 * sizeof(char));
		telephones[length].firma = (char *)malloc(50 * sizeof(char));
	}

	free(telephones[length].mark);
	free(telephones[length].firma);
	fclose(f);

	return telephones;
}

// вывод на печать содержимого массива телефонов
void print_telephones(telephone_t *telephones, size_t size) {
	cout << endl;

	for (size_t i = 0; i < size; i++)
		cout << telephones[i].mark << ", " << telephones[i].firma << ", " << telephones[i].price << "rub, " << telephones[i].weight << "g" << endl;
}

// поиск телефона с минимальным весом
void min_weight(telephone_t *telephones, size_t size) {
	int i_min = 0;

	for (size_t i = 1; i < size; i++)
		if (telephones[i].weight < telephones[i_min].weight)
			i_min = i;

	cout << endl << "The lightest phone is " << telephones[i_min].mark << ", " << telephones[i_min].firma << ", " << telephones[i_min].price << "rub, " << telephones[i_min].weight << "g" << endl;
}

int main() {
	char path[100]; // путь к файлу
	cout << "Enter path to file: ";
	cin >> path;

	size_t length;
	telephone_t *telephones = read_telephones(path, length);

	print_telephones(telephones, length);
	min_weight(telephones, length);

	system("pause");
    return 0;
}