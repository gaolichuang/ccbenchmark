#!/bin/bash

# 计算pi，精度5000位
time echo "scale=5000;4*a(1)" | bc -l -q   
