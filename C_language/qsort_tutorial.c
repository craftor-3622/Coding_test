/* qsort() 사용 테스트
 qsort()는 정렬에서 quick sort 기법을 최적화하여 나타낸 c언어 함수로,
 거의 모든 상황에서 최적의 시간 복잡도(n log n)의 결과를 나타낼 수 있도록
 stdlib 헤더 파일에서 제공하는 정렬 함수입니다.
 최악의 경우인 순열 및 역순열에 대한 피벗 선택 최적화,
 배열 크기에 따른 방법 전환(작은 경우 Insertion Sort, 큰 경우 Heap Sort),
 중복된 키에 대한 처리 등을 통해 최적화된 결과를 나타냅니다.
 
 void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *));
 함수 사용법 : qsort(대상 배열 포인터, 배열 크기, 자료형 크기, 기준 함수)
 1. 대상 배열 : 정렬할 대상 배열을 나타냅니다. 이 때 입력할 때는 배열의 시작 주소를 입력합니다.
 2. 배열 크기 : 배열 요소들의 개수를 입력합니다.
 3. 자료형 크기 : 요소에 들어간 자료형의 크기를 입력합니다. ex) sizeof(int)
 4. 기준 함수 : 비교 함수에 대한 포인터를 입력합니다. 양수, 음수, 0을 반환하는 함수를 만들어야 합니다.
 기준 함수를 통한 반환 값이 양수인 경우, 두 요소의 위치를 바꿉니다.

 GitHub Copilot을 통해 더 자세한 사용법을 알 수 있습니다.
*/

#define _CRT_SECURE_NO_WARNINGS

#define ARRAY_SIZE 15

#include <stdio.h>
#include <stdlib.h>

// 이 부분이 기준 함수가 될 것입니다. 이 때 qsort()는 매개 변수 타입을 알지 못하기에 void로 받아야 합니다.
int compare(const void* a, const void* b) {
	// void 포인터로 받은 값을 int 포인터로 변환하여 비교합니다.
	// return *(int*)a - *(int*)b;		// 오름차순 정렬
	// a가 b보다 크면 양수, 작으면 음수, 같으면 0을 반환합니다.
	return *(int*)b - *(int*)a;			// 내림차순 정렬
}

int main() {

	// 예시로 무작위 배열을 하나 생성합니다.
	int arr[ARRAY_SIZE] = { 3, 5, 1, 2, 4, 6, 8, 7, 9, 10, 15, 13, 12, 11, 14 };

	// void* base : 대상 배열의 시작 주소 (arr)
	// size_t num : 배열 요소의 개수 (10)
	// size_t size : 배열 요소의 크기 (sizeof(int))
	// int (*compar)(const void *, const void *) : 기준 함수 (compare)
	qsort(arr, ARRAY_SIZE, sizeof(int), compare);

	for (int i = 0; i < ARRAY_SIZE; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}