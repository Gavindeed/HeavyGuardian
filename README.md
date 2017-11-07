# HeavyGuardian

## Introduction

Data stream processing is a fundamental issue in many fields, such as databases, data mining, network traffic analysis. There are five typical tasks in data stream processing: frequency estimation, heavy hitter detection, heavy change detection, frequency distribution estimation, and entropy estimation. Different algorithms are proposed for different tasks, but they seldom achieve high accuracy and high speed at the same time. To address this issue, we propose a novel data structure named HeavyGuarding. The key idea is to intelligently separate and guard the information of hot items while approximately record the frequencies of cold items. We deploy HeavyGuarding on the above five typical tasks. Extensive experimental results show that HeavyGuarding achieves both much higher accuracy and higher speed than the  state-of-the-art solutions for each of the five typical tasks.

## About the source codes, dataset and parameters setting

There are several directories here, including data, distribution, entropy, flow_size, heavychange and heavyhitter, which represent data and all algorithms.

The source code in each directory contains the C++ implementation of the HeavyGuarding, SpaceSaving, k_ary, PCU Sketch, CM Sketch plus heap. We complete these codes on WINDOWS 10 and compile successfully using g++ 4.8.4.

The file u1 is comprised of IP packets captured from the network of our campus. And the hash functions are 64-bit Bob hash functions and 32-bit Bob hash functions, obtained from http://burtleburtle.net/bob/hash/evahash.html.

You can also use your own dataset and other hash functions.
	
## How to run

Suppose you've already cloned the repository and start from the Codes directory.

You just need to compile and run main.cpp.

## Input format

You need to input an integer MEM, which means the size of memory. 

If you want to change some parameters, please read the code.

## Output format

We set some variables for each code. They will give you some information you want. (like AAE, ARE, PRE, etc)