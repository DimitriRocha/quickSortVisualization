#include "QuickSort.h"

QuickSort::QuickSort(float x, float y) {
	this->screenWidth  = x;
	this->screenHeight = y;
	this->fillArray();
}

void QuickSort::setViewSize(float x, float y) {
	this->screenWidth = x;
	this->screenHeight = y;
}

void QuickSort::generateVisualSort(sf::RenderWindow* window) {
	float recXsize = this->screenWidth/ this->arr.size();
	
	for(size_t i = 0 ; i < this->arr.size() ; i++){
		sf::RectangleShape shape(sf::Vector2f(recXsize, this->arr[i]));
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineThickness(1.f);
		shape.setOutlineColor(sf::Color(0, 0, 0));
		shape.setPosition(recXsize*i, (this->screenHeight - this->arr[i]));
		window->draw(shape);
	}

	for (size_t i = 0; i < this->partitionIndexes.size(); i++){
		if(this->partitionIndexes[i] == 1){
			sf::RectangleShape shape(sf::Vector2f(3, this->screenHeight));
			shape.setFillColor(sf::Color::Red);
			shape.setPosition(recXsize*i + recXsize, 0);
			window->draw(shape);
		}
	}
}

void QuickSort::fillArray() {
	//Generate increasing array
	for (size_t i = 0; i < this->arr.size(); i++) {
		this->arr[i] = (i+1) * (this->screenHeight/ this->arr.size());
	}

	//Shuffle array
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(this->arr.begin(), this->arr.end(), std::default_random_engine(seed));
}

void QuickSort::sortArray(std::array<int, ARR_MAX_VALUE>* arr, int low, int high) {
	if (low < high)
	{
		int pi = partition(arr, low, high);
		
		auto preIndexSort = std::async(&QuickSort::sortArray, this, arr, low, pi - 1);
		auto postIndexSort = std::async(&QuickSort::sortArray, this, arr, pi + 1, high);
		preIndexSort.get();
		postIndexSort.get();
	}

	return;
}

int QuickSort::partition(std::array<int, ARR_MAX_VALUE>* ptArr, int low, int high) {
	std::array<int, ARR_MAX_VALUE> arr = *ptArr;
	int pivot = arr[high];
	int i = (low - 1); 

	for (int j = low; j <= high - 1; j++)
	{
		this->partitionIndexes[j] = 1;
		if (arr[j] < pivot)
		{
			i++;
			this->swap(&(*ptArr)[i], &(*ptArr)[j]);
		}
		this->partitionIndexes[j] = 0;
	}
	this->swap(&(*ptArr)[i + 1], &(*ptArr)[high]);

	return (i + 1);
}

void QuickSort::swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
	sf::sleep(sf::milliseconds(30));
}
