/*
 * main.cpp
 *
 *  Created on: Jun 7, 2016
 *      Author: x200
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

mutex m1;
mutex m2;
mutex m3;
mutex counter;

static unsigned long counter;

/* generate numbers and send them to a second thread */
void generate()
{

	counter.lock();
	counter++;
	counter.unlock();

}


void show_1()
{
	m1.unlock();
	std::cout<<"show_1"<<std::endl;
	return;
}

void show_2()
{
	m1.lock();
	std::cout<<"show_2"<<std::endl;
	m2.unlock();
	return;
}

void show_3()
{
	m2.lock();
	std::cout<<"show_3"<<std::endl;
	return;
}

int main()
{
	m3.lock();
	m2.lock();
	m1.lock();

	std::thread thread_3(show_3);
	std::thread thread_2(show_2);
	std::thread thread_1(show_1);

	thread_1.join();
	thread_2.join();
	thread_3.join();
	return 0;
}




