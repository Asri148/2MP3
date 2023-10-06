#include <stdio.h>

int main() {
    // This code computes the average weight of people registered in the class.
    int Ross = 95;
    int Monica = 102;
    int Rachel = 65;
    int Chandler = 84;
    int totalWeight = Ross + Monica + Rachel + Chandler;
    int numberOfPeople = 4;
    int averageWeight = totalWeight / numberOfPeople;
    
    printf("Average weight: %d\n", averageWeight);
    return 0;
}
