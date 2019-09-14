#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>
#include <random>
#include <chrono>
#include <future>
#include <list>

#define ARR_MAX_VALUE 240

class QuickSort {
public:
	float screenWidth;
	float screenHeight;
	std::array<int, ARR_MAX_VALUE> arr;
private:
	std::array<int, ARR_MAX_VALUE> partitionIndexes;

public:
	QuickSort(float x, float y);
	void setViewSize(float x, float y);
	void generateVisualSort(sf::RenderWindow* window);
	void sortArray(std::array<int, ARR_MAX_VALUE>* arr, int low, int high);

private:
	void fillArray();
	int partition(std::array<int, ARR_MAX_VALUE>* arr, int low, int high);
	void swap(int* a, int* b);
};
