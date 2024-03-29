#include <iostream>
using namespace std;

// Conversion constants
#define CtoFRatio 1.80
#define CtoFOffset 32.00
#define CtoKOffset 27.30

// Scale indentifiers
#define DegC 'C'
#define Degc 'c'
#define DegF 'F'
#define Degf 'f'
#define DegK 'K'
#define Degk 'k'

// Conversion function prototypes
// Should be in a ".h" file, but placed here for lab1
double toFahrenheit( double T, char scale );
double toCelsius( double T, char scale );
double toKelvin( double T, char scale );

int main(void)
{
   double inTemp;
   char scale;
   
   cout << "\nThis program converts a temperature between the scales\n"
        << "\t Fahrenheit, Celsius and Kelvin.\n";

   // Get a temperature and scale
   cout << "\nPlease enter the temperature you wish to convert,\n"
        << "\tfollowed by its scale (eg. 23 C): ";
   cin >> inTemp >> scale;

   // Check for validity of scale
   if( scale != DegF && scale != Degf &&
       scale != DegC && scale != Degc &&
       scale != DegK && scale != Degk ) { 

      cerr << "\nError in input: Invalid scale `" << scale << "'\n";
      return -1;
   }

   // Print the converted results
   cout << "\n" << inTemp << " " << scale << " is equivalent to:\n"
        << "\t" << toFahrenheit( inTemp, scale ) << " F, "
        << toCelsius( inTemp, scale ) << " C, and "
        << toKelvin( inTemp, scale ) << " K\n";
   
   return 0;

}
// Converts the temperate 'T' from scale 'scale' to Fahrenheit
double toFahrenheit( double T, char scale )
{
   double outT;
   
   switch( scale ) {

   case DegF:
      outT = T;
       break;

   case Degf:
      outT = T;
       break;
      
   case DegC:
      outT = ((CtoFRatio) * T) + 32;
      break;

   case Degc:
      //outT = T * CtoFRatio + CtoFOffset;
      outT = (T * (CtoFRatio));
      outT += 32;
      break;

   case DegK:
      outT = (( T - 273.00 ) * CtoFRatio) + 32;
      break;

   case Degk:
      //outT = (5/9)*( T - 32 ) + 273.15;
      outT = (( T - 273.00 ) * CtoFRatio) + 32;
      break;

   default:
      break; 
   }

   return outT;
}

// Converts the temperate 'T' from scale 'scale' to Celsius
double toCelsius( double T, char scale )
{
   double outT;
   
   switch( scale ) {
	
	   case DegF: 
         outT = (T-32)* (1/CtoFRatio);
         break;

	   case Degf:
	      //outT = ( T - CtoFOffset ) / CtoFRatio;
         outT = (T-32)* (1/CtoFRatio);
          break;
	      
	   case DegC:
         outT = T;
         break;

	   case Degc:
	      outT = T;
         break;
	
	   case DegK:
         outT = T - 273.0;
         break;

	   case Degk:
	      outT = T - 273.0;
         break;
	
	   default:
	      break; 
   }

   return outT;
}

// Converts the temperate 'T' from scale 'scale' to Kelvin
double toKelvin( double T, char scale )
{
   double outT;
   
   switch( scale ) {
	
	   case DegF:
         outT = (1/CtoFRatio)*( T - 32 ) + 273.00;
         break;
	   case Degf:
         outT = (1/CtoFRatio)*( T - 32 ) + 273.00;
         break;
	      
	   case DegC:
         outT = T + 273.0;
         break;
	   case Degc:
	      outT = T + 273.0;
         break;
	
	   case DegK:
         outT = T;
         break;
	   case Degk: 
	      outT = T;
         break;
	
	   default:
	      break; 
   }

   return outT;
}

