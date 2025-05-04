#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0};
        int index = k.length()-1;
        int arrayIndex = 4;

       

        while(arrayIndex>=0&&index >=0){
          unsigned long long base = 1; //36^0 is 1
          unsigned long long value = 0;
          for(int i = 0; i<6 && index-i>=0;i++){
            char currentC = k[index-i];
            HASH_INDEX_T cValue = letterDigitToNumber(currentC);

            value += cValue * base;
            base*=36;
          }

          w[arrayIndex] = value;
          arrayIndex--;
          index -=6;

        }
        

        unsigned long long result =0;

        for(int i =0; i <5; i++){
          result += static_cast<unsigned long long>(rValues[i]*w[i]);

        }

        return static_cast<HASH_INDEX_T>(result);


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        //if uppercase
        if(letter >='A'&& letter <= 'Z'){
          letter = letter - 'A'+'a'; 
        }

        if(letter >='a'&& letter <= 'z'){
          letter -= 'a';
          return letter;
        }

        if(letter >= '0'&& letter <='9'){
          letter = letter -'0'+26;
          return letter;

        }

        return 0;

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
