//
// Created by zhouxuguang on 2020/11/24.
//

#ifndef TACKINGDEMO_ANDROID_FOPEN_H
#define TACKINGDEMO_ANDROID_FOPEN_H

#include <stdio.h>
#include <vector>

FILE *android_fopen(const char *fileName, const char *mode);

void readBinary(FILE* file, std::vector<char>& bytes);
void getBinaryData(const char* fileName, std::vector<char>& bytes);

#endif //TACKINGDEMO_ANDROID_FOPEN_H
