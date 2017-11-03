# HeavyGuardian

## Introduction

Data stream processing is a fundamental issue in many fields, such as databases, data mining, network traffic analysis. There are five typical tasks in data stream processing: frequency estimation, heavy hitter detection, heavy change detection, frequency distribution estimation, and entropy estimation. Different algorithms are proposed for different tasks, but they seldom achieve high accuracy and high speed at the same time. To address this issue, we propose a novel data structure named HeavyGuarding. The key idea is to intelligently separate and guard the information of hot items while approximately record the frequencies of cold items. We deploy HeavyGuarding on the above five typical tasks. Extensive experimental results show that HeavyGuarding achieves both much higher accuracy and higher speed than the  state-of-the-art solutions for each of the five typical tasks.
	