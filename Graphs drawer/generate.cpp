#include<iostream>
#include<time.h>
#include <stdlib.h>

int main(){
   srand(time(NULL));

   int vertices, aristas;
   std::cin>>vertices>>aristas;
   std::cout<<vertices<<" "<<aristas<<"\n";

   for(int i = 0; i<aristas; ++i){
      // variable = limite_inferior + rand() % (limite_superior +1 - limite_inferior) ;
      int v1 = 0 + rand()%(vertices);
      int v2 = 0 + rand()%(vertices);
      std::cout<<v1<<" "<<v2<<"\n";
   }
}

/*
5 15
0 1
0 2
0 3
0 4
1 2
1 3
1 4
2 3
2 4
3 4
0 0
1 1
2 2
3 3
4 4
*/
