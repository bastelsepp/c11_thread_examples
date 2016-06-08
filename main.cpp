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
#include <time.h>
#include <iomanip>
#include <chrono>


using namespace std;

mutex m1;
mutex m2;
mutex trigger;
mutex mutex_counter;



static unsigned long counter;


void show_current_time()
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC,&time);
	cout<<"timestamp sec:"<<time.tv_sec<<" nsec:";
	cout<<setw(9)<<setfill('0')<<time.tv_nsec<<endl;
}

/* generate numbers and send them to a second thread */
void generate()
{
	while(true)
	{
		counter++;
		mutex_counter.unlock();
		this_thread::sleep_for(chrono::milliseconds{100});
	}
}

void show_generated()
{
	while(true)
	{

		mutex_counter.lock();
	show_current_time();
	cout<<"counter"<<counter<<endl;

	}
}

void show_1()
{
	m1.unlock();
	show_current_time();
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

	m2.lock();
	m1.lock();
	trigger.lock();
	mutex_counter.lock();

	std::thread thread_3(show_3);
	std::thread thread_2(show_2);
	std::thread thread_1(show_1);

	std::thread thread_generate(generate);
	std::thread thread_show_generated(show_generated);




	thread_1.join();
	thread_2.join();
	thread_3.join();

	this_thread::sleep_for(chrono::seconds{10});


	thread_generate.join();
	thread_show_generated.join();
	return 0;
}




