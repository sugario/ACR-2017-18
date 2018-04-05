#define _CRT_SECURE_NO_WARNINGS

#define HAVE_STRUCT_TIMESPEC    // timespec issues
#include <pthread.h>
#include <stdint.h>
#include <cstdio>
#include <cstdlib>
#include <array>

#include <Random.hpp>
#include <chrono>

#include <iostream>

#define ARR_LENGTH 8
#define NUM_OF_THREADS 2

typedef std::chrono::high_resolution_clock Clock;

void* PrintHello(void* threadId) noexcept
{
	const auto tId = (long)threadId;
	printf("Hello World! It's me, thread #%ld!\n", tId);

	/*pthread_exit(nullptr);*/
	return nullptr;
}

struct arg_struct {
	int32_t *arrStart;
	int32_t *arrEnd;
};

void *GetSum(void *arguments)
{
	struct arg_struct *args = (struct arg_struct *)arguments;

	int32_t result = 0;
	while (args->arrStart != args->arrEnd) {
		printf("%d\n", (int)*args->arrStart);
		args->arrStart++;
		break;
	}


	return nullptr;
}




int32_t main(void)
{
	Random random;
	int32_t arr[ARR_LENGTH];
	auto result = 0;

	for (auto i = 0; i < ARR_LENGTH; i++) {
		arr[i] = random.Next(-1000, 1000);
		printf("arr[%u] = %d\n", i, arr[i]);
	}

	pthread_t threads[NUM_OF_THREADS];

	printf("----------------------------------\n");

	auto timerStart = Clock::now();
	for (auto i = 0; i < NUM_OF_THREADS; i++) {
		struct arg_struct args;
		int32_t range = ARR_LENGTH / NUM_OF_THREADS - 1;
		args.arrStart = arr + i * range;
		args.arrEnd = arr + (i + 1) * range;

		printf("i = %d\n", i * range);
		printf("i = %d\n", (i + 1) * range);


		const auto rc = pthread_create(&threads[i], nullptr, GetSum, (void *)&args);
		if (rc)
		{
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			return EXIT_FAILURE;
		}
	}

	for (auto& t : threads) {
		pthread_join(t, nullptr);
	}
	
	auto timerEnd = Clock::now();

	printf("Result: %d\n", result);
	printf("Execution time: %u microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(timerEnd - timerStart).count());

	pthread_exit(nullptr);
	return EXIT_SUCCESS;
}

//int32_t main(void)
//{
//	Random random;
//	std::array<int32_t, ARR_LENGTH> arr;
//	auto result = 0;
//
//	for (auto i = 0; i < ARR_LENGTH; i++) {
//		arr[i] = random.Next(-1000, 1000);
//	}
//
//	auto timerStart = Clock::now();
//	for (auto i = 0; i < ARR_LENGTH; i++) {
//		result += arr[i];
//	}
//	auto timerEnd = Clock::now();
//
//	printf("Result: %d\n", result);
//	printf("Execution time: %u microseconds\n", std::chrono::duration_cast<std::chrono::microseconds>(timerEnd - timerStart).count());
//
//	return EXIT_SUCCESS;
//}