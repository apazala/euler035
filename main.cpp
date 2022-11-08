#include <iostream>
#include <cinttypes>
#include <cmath>

using namespace std;

#define LIMIT 1000000

int primesList[78500];
int numprimes;
void fillprimes(int upperBound);

uint64_t iscompound[1 + ((LIMIT+1)>>6)];



#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))


int main()
{
    int tenpowers[8]; 

    fillprimes(LIMIT);
    tenpowers[0] = 1;
    for(int i = 1; i < 8; i++){
        tenpowers[i] = 10*tenpowers[i-1];
    }

    int primesrotcount = 0;
    int ndig = 1;
    int p, div = tenpowers[ndig-1], nextdiv = tenpowers[ndig], prot, maxdig, isprime;
    for(int i = 0; i < numprimes; i++)
    {
        p = primesList[i];
        if(p >= nextdiv){
            ndig++;
            div = nextdiv;
            nextdiv = tenpowers[ndig];
        } 

        prot = p;
        isprime = 1;
        for(int j = 1; j < ndig && isprime; j++){
            maxdig = prot/div;
            prot = prot%div;
            prot = prot*10 + maxdig;
            isprime = baisclear(iscompound, prot);
        }

        if(isprime) //All rotations prime
            primesrotcount++;
    }

    cout << primesrotcount << endl;
}

//upperBound INCLUSIVE
void fillprimes(int upperBound) {
	int i, j;

	baset(iscompound, 0);
	baset(iscompound, 1);
	int sqrtUb = sqrt(upperBound);
	for (i = 2; i <= sqrtUb; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

	for (i = sqrtUb + 1; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
		}
	}
}