/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("------------2018038051    정종현-------------");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/*selection Sort
index의 값이 min 값 보다 작으면 min값과 minindex를 해당 index로 교체한다.
최소값을 저장한뒤, 배열을 한 칸 이동하고, 최소값을 찾아 저장하는 과정을 반복한다.
*/
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])
			{
				min = a[j];		//최소값 교체
				minindex = j;	//최소값 자리 교체
			}
		}
		a[minindex] = a[i];		//찾은 min 과 i 의 swap
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}
/* insertionSort
삽입될 새로운 값을 따로 빼놓은 뒤, 정렬을 진행한다. 삽입될 값보다 값이 크다면 오른쪽으로 한 칸 이동하게 되고,
삽입될 값보다 같거나 작은 값이 나올 때 까지 혹은 맨 왼쪽에 다다를 때 까지 반복한다. 반복을 마치면 값을 삽입한다.
*/
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];	//삽입될 값
		j = i;		//이미 정렬된 부분 스킵
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1];	//한 칸 뒤로 이동
			j--;
		}
		a[j] = t;	//새로운 값을 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*bubble Sort
배열을 한 칸씩 이동하며 정렬을 진행한다. 배열의 왼쪽에 있는 값이 자신의 값보다 크다면 swap을 해 오름차순으로 정렬한다.
*/
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])	//큰 값이 오른쪽에 있다면 swap
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*shell Sort 
삽입정렬의 단점을 보완한 정렬이다. 삽입정렬은 한 칸씩 비교를 했다면 shell sort는 MAX_ARRY_SIZE/2 한 만큼의 값만큼 떨어진 곳과 비교를 한다.
수행될 때 마다 h값을 반으로 감소시키면서 1이 될 때 까지 반복을 한다.
*/
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //h 가 1이 될 때 까지 반복
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)	//h만큼의 간격을 가지는 삽입정렬 시행
			{
				v = a[j];	//삽입될 값
				k = j;
				while (k > h-1 && a[k-h] > v)	//정렬이 필요하다면
				{
					a[k] = a[k-h];	//값을 h만큼 떨어진 곳 까지 이동
					k -= h;
				}
				a[k] = v;	//삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}
/*quick Sort
기준값을 중심으로 왼쪽 부분집합과 오른쪽 부분집합으로 분할하여 정렬 다음 함수에선 마지막원소를 기준으로 퀵정렬을 실행한다.
왼쪽 부분은 기준값보다 큰 값을 찾을 때 까지, 오른쪽 부분은 기준값보다 작은 값을 찾을 때 까지 이동한 다음, 그 원소들이 왼쪽과 오른쪽 부분에 그대로 있다면
그 두 원소의 위치를 swap 한다. 왼쪽과 오른쪽 부분이 교차하지 않을 때 까지 반복을 해준 뒤, 기준값을 정렬된 위치로 이동시킨다.
recursive하게 왼쪽 부분집합과 오른쪽 부분집합에 대해서 각각의 quicksort 를 해주며, 각각의 기준은 각 부분집합의 마지막 원소가 된다.
*/
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];	//기준 v, 마지막 원소를 선택한다.
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;	//i 가 j 보다 클 때, break, //큰 값이 왼편에 있다면 swap 한다.
			t = a[i];		
			a[i] = a[j];
			a[j] = t;
		}
		//마지막 원소 즉 기준값을 정렬된 위치로 이동시킨다.
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);	//왼쪽 부분집합의 quicksort 진행
		quickSort(a+i+1, n-i-1);	//오른쪽 부분집합의 ,quicksort
	}


	return 0;
}

/*hastcode 를 반환해주는 함수
divisino 을 활용해 MAX_HASH_TABLE_SIZE로 나눈 나머지를 버킷으로 사용한다.
*/
int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}
/*
hashing function
오버플로 처리를 위해 Linear Probing 을 사용하여 순서에 따라 해시 테이블 버킷을 검사한다.
13개의 버킷에 하나의 슬롯이 hasing table의 상태이다.
*/
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)	//비어있는 hashtable 인 경우 -1 로 초기화 한다.
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];	//
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)	//hashtable 의 해당하는 인덱스 값이 비어있다면 값을 저장
		{
			hashtable[hashcode] = key;
		} else 	{	//충동이 있다면

			index = hashcode;	//기존의 hashcode 를 새로운 변수에 옮기고

			while(hashtable[index] != -1)	//비어있는 자리가 나올 때 까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;	//인덱스를 한 칸씩 옮긴다.
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;	//비어있는 자리에 key 값을 저장한다.
		}
	}

	return 0;
}
/*hashing table에 적재된 값의 주소를 반환해주는 함수*/
int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)	//해당 주소와 hashcode가 나타내는 값이 같다면 반환한다.
		return index;

	while(ht[++index] != key)	//찾으려는 값이 나올 때 까지 index 를 1 증가시킨다.
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



