#include <iostream>

using namespace std;


double factorielle(double n)
{
     if(n == 0)
	  return 1;
     else
	  return factorielle(n-1)*n;
}

int main()
{
    cout << "Hello world!" << endl;
    cout << factorielle(50) << endl;
    return 0;
}

