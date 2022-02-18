#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    int neededNums = 20, n = 20, index = 0, border;
    int x = 0, y = 0;
    bool flag = true;
    string* words = new string[n];
    int* frequency = new int[n];

    int wordsArrayLength = 0;
    string stopWords[5] = {"the", "for", "in", "on", "a"};

    string word;

    ifstream file("text.txt");
    reading:
        if (!(file >> word)) {
            goto endOfReading;
        }

        index = 0;
        toLowerCase:
            if (!word[index]){
                goto endLowerCase;
            }
            if (word[index]>='A' && word[index]<= 'Z'){
                word[index] += 32;
            }
            index ++;
            goto toLowerCase;
        endLowerCase:

        
        index = 4;
        checkForbidden:
            if (index<0){
                goto endCheckForbidden;
            }
            if (word==stopWords[index]){
                goto reading;
            }
            index--;
            goto checkForbidden;
        endCheckForbidden:

       
        if (wordsArrayLength >= n) {
            string* newWords = new string[wordsArrayLength*10];
            int* newfrequency = new int[wordsArrayLength*10];
            n--;
            whileNnotLessZero:
                if (n<0) {
                    goto lessThanZero;
                }
                newWords[n] = words[n];
                newfrequency[n] = frequency[n];
                n--;
            goto whileNnotLessZero;
            lessThanZero:
            words = newWords;
            frequency = newfrequency;
            n = wordsArrayLength*10;
        }


        
        index = wordsArrayLength-1;
        flag = true;
        if (wordsArrayLength==0){
            words[0] = word;
            frequency[0] = 1;
            wordsArrayLength++;
        } else {
            
            isExist:{
                if (index<0){
                    goto endExist;
                }
                if (words[index]==word){
                    frequency[index] += 1;
                    flag = false;
                    goto endExist;
                }
                index--;
                goto isExist;
            }
            endExist:
                if (flag) {
                    words[wordsArrayLength] = word;
                    frequency[wordsArrayLength] = 1;
                    wordsArrayLength++;
                }
        }

    goto reading;
    endOfReading:

   
    x = 0;
    sorting: {
        if (x>=wordsArrayLength) {
            goto endOfSorting;
        }
        y = 0;
        cyclX:
            if (y<wordsArrayLength){
                if (frequency[x]>frequency[y]){
                    int buf = frequency[x];
                    frequency[x] = frequency[y];
                    frequency[y] = buf;

                    string wordBuf = words[x];
                    words[x] = words[y];
                    words[y] = wordBuf;
                }
                y++;
                goto cyclX;
            }
        x++;
        goto sorting;
    }
    endOfSorting:

    index = 0;
    border = neededNums;
    if (wordsArrayLength<neededNums) {
        border = wordsArrayLength;
    }
    output:
        if (index<border){
            cout << words[index] <<" - " <<frequency[index] <<endl;
            index++;
            goto output;
        }
    file.close();
    return 0;
}
