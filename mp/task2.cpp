#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Word {
    string text;
    string pages;
    int frequency;
    int lastRepeatPage;
};

int main()
{
    int n = 20, index = 0, pageSymbols = 0, currentPage=1, x = 0, y = 0;
    int wordsArrayLength = 0;
    bool flag = true;
    string newWord = "", word;
    Word* words = new Word[n];
    ifstream file("text.txt");
    reading:
        if (!(file >> word)) {
            goto endOfReading;
        }

        if (word == "-"){
            pageSymbols+=2;
            goto reading;
        }

        index = 0;
        newWord = "";
        toLowerCase:
            if (!word[index]){
                goto endLowerCase;
            }
            if (word[index]>='A' && word[index]<= 'Z'){
                word[index] += 32;
            }

            if (word[index]>='a' && word[index] <= 'z') {
                newWord += word[index]; 
            }
            index ++;
            goto toLowerCase;
        endLowerCase:
            word = newWord;
            pageSymbols+= index + 1;

       
        if (wordsArrayLength >= n) {
            Word* newWords = new Word[wordsArrayLength*10];
            n--;
            whileNnotLessZero:
                if (n<0) {
                    goto lessThanZero;
                }
                newWords[n] = words[n];
                n--;
            goto whileNnotLessZero;
            lessThanZero:
            words = newWords;
            n = wordsArrayLength*10;
        }


        
        index = wordsArrayLength-1;
        flag = true;
        if (wordsArrayLength==0){
            words[0].text = word;
            words[0].frequency = 1;
            words[0].pages = to_string(currentPage);
            words[0].lastRepeatPage = currentPage;
            wordsArrayLength++;
        } else {
            
            isExist:{
                if (index<0){
                    goto endExist;
                }
                if (words[index].text==word){
                    words[index].frequency += 1;
                    if (words[index].lastRepeatPage != currentPage) {
                        words[index].pages+= ", " + to_string(currentPage);
                        words[index].lastRepeatPage = currentPage;
                    }
                    flag = false;
                    goto endExist;
                }
                index--;
                goto isExist;
            }
            endExist:
                if (flag) {
                    words[wordsArrayLength].text = word;
                    words[wordsArrayLength].frequency = 1;
                    words[wordsArrayLength].pages = to_string(currentPage);
                    words[wordsArrayLength].lastRepeatPage = currentPage;
                    wordsArrayLength++;
                }
        }
        if (pageSymbols >= 1800) {
            currentPage++;
            pageSymbols = pageSymbols-1800;
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
                if (words[x].text<words[y].text){
                    Word wordBuf = words[x];
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
    output:
        if (index<wordsArrayLength){
            if (words[index].frequency <= 100){
                cout << words[index].text <<" - " <<words[index].pages <<endl;
            }
            index++;
            goto output;
        }
    file.close();
    return 0;
}
