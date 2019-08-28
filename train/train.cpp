// train.cpp: определяет точку входа для консольного приложения.
//

// Задача
/* Вы находитесь в поезде, вагоны которого закольцованы: последний вагон прицеплен к первому (кабина машиниста отсутствует). Все вагоны идентичны. Каждый вагон может быть либо освещен, либо не освещен. 
Изначально свет в вагонах горит случайным образом. Вы можете свободно перемещаться между вагонами и включать-выключать свет в вагоне, в котором находитесь. 
Придумать алгоритм, который позволит определить количество вагонов в поезде.*/

//Описание решения
/* Выключаем свет в первом вагоне, в следующем вагоне с выключенным светом включаем свет и возвращаемся в первый вагон, при этом считая количество пройденных вагонов. 
Затем возвращаемся в вагон с которого пошли назад и переходим в следующий, продолжаем до тех пор, пока в первом вагоне не выключим свет.*/

//Описание структур
// Используем структуру - циклический линейный двунаправленный список (кольцо) 

typedef struct railway_carriage
{
	int bulb;
	long long number;
	struct railway_carriage *ptr_prev;
	struct railway_carriage *ptr_next;
} carriage;

//Объявлениение функций
//Создаем кольцо из нужного числа вагонов
carriage * form_ring(carriage *, long long);
//Выводим результат
void print_ring(const carriage *);
//Считаем вагоны
int shuttle(carriage *);

#include "stdafx.h"
#include <stdio.h> 
#include <conio.h> 
#include <string.h> 
#include <Windows.h> 
#include <cmath> 
#include <time.h>


int main()
{
	//Подключаем русский язык 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//Объявляем переменные 
	long long S;
	carriage *train = NULL;
	S = 100000 ;
	printf_s(" S = %d\n", S);
	train = form_ring(train, S);
	//print_ring(train);
	printf_s("\n S = %d\n", shuttle(train));
	//print_ring(train);
	_getch();
	return 0;
}

//Реализация функций
carriage * form_ring(carriage *head, long long S)
{
	carriage *temp = NULL, *p = NULL;
	long long i;
	head = (carriage*)malloc(sizeof(carriage));
	head->bulb = 0 + rand() % 2;
	head->number = S;
	head->ptr_next = head;
	head->ptr_prev = head;
	if (S != 1)
	{
		for (i = (S - 1); i != 0; i--)
		{

			temp = (carriage*)malloc(sizeof(carriage));
			p = head->ptr_next;
			head->ptr_next = temp;
			temp->bulb = 0 + rand() % 2;
			temp->number = i;
			temp->ptr_next = p;
			temp->ptr_prev = head;
			p->ptr_prev = temp;
		}
		return(temp);
	}
	else
		return(head);
}

void print_ring(const carriage *head)
{
	long long a;
	a = head->number;
	do
	{
		printf_s("%2d  %d\n", head->number, head->bulb);
		head = head->ptr_next;
	} while (a != head->number);
}

int shuttle(carriage *head)
{
	long long n = 0, k = 0;
	clock_t start, end;
	carriage *temp = head, *p = NULL;
	start = time(NULL);
	temp->bulb = 1;
	n++;
	while (n)
	{
		temp = temp->ptr_next;
		n++;
		if (temp->bulb == 1)
		{
			k = n;
			temp->bulb = 0;
			do
			{
				temp = temp->ptr_prev;
				k--;
			} while (k != 1);
			if (temp->bulb == 0)
			{
				end = time(NULL);
				printf("Время работы: %f\n", difftime(end, start));
				return(n - 1);
			}
			else
			{
				do
				{
					temp = temp->ptr_next;
					k++;
				} while (k != n);
			}
		}
	}
}

