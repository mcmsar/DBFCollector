#ifndef __BASE_2_H__	
#define __BASE_2_H__	

//! Performs operations on base 2 numbers.
class CEMSBase2
{
	public:
		~CEMSBase2();

	private:
		CEMSBase2();

	public:
		static short Log( const long clValue )
		{
		   short sCount = 0;
		   long  lTemp = 0;

		   lTemp = clValue;
		   do
		   {
			  sCount++;
			  lTemp /= 2;
		   }
		   while( lTemp > 1 );

		   return sCount;
		}
};

#endif