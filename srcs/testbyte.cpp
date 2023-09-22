#include <iostream>

size_t getPtrSize( std::string *ptr )
{
   return sizeof( ptr );
}

using namespace std;
int main()
{
   string szHello = "eé¿";

   cout  << "The size of a char is: "
         << sizeof( char )
         << "\nThe length of " << szHello << " is: "
         << szHello.length()
         << "\nThe size of the pointer is "
         << getPtrSize( &szHello ) << endl;
}