/*
Benchmark
*/


#pragma once
#include <iostream>
#include <chrono>
#include <format>
#include <string>
#include "logger_file.h"

using namespace std::chrono;


class StopWatch
{
public:
	StopWatch() {
	}
	~StopWatch() {}

	int start();
	int end();
	int print(std::string func_name);

private:
	high_resolution_clock::time_point s, e;
};



int StopWatch::start()
{
	this->s = high_resolution_clock::now();
	return 0;
}


int StopWatch::end()
{
	this->e = high_resolution_clock::now();
	return 0;
}

int StopWatch::print(std::string func_name)
{
	SimpleLogger log("benchmark.log");
	auto sec = duration_cast<std::chrono::seconds>(this->e - this->s);
	auto m = duration_cast<std::chrono::milliseconds>(this->e - this->s);
	std::string s = std::format("{} {}.{}", func_name, sec, m);
	log.debug("Started.. " + s);
	return 0;
	
}
