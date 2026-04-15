#include "EMSBCH.h"
#include "EMSTYPES.h"
#include "EMSBEACONDFNS.h"

static int
ECCheck( int field_id, 
         bool modify, 
         BYTE *Message )
{
   // Log tables:
   //  logt[k] (k = 0 to 127) is the polynomial representation of (alpha**k).
   //  logt[-1] defines the zero polynomial

   short log_table[ 129 ];
   short *logt;

   /* Power tables:
   powt[p] (p = 0 to 127) is the exponent of alpha which yields the
   polynomial p. (i.e., powt[logt[k]] = k).
   Note - powt[0] = -1  according to convention.   */

   short powt[ 128 ];

   short poly;       /* BCH polynomial */
   short order;      /* Mask for most significant bit of POLY */
   short t;          /* Number of errors corrected by BCH code */
   short n;          /* Number of bits in BCH code word (message) */
   short npred;      /* Largest distinct power of alpha */
   short bit_offset; /* Index to first valid message bits */
   short msg_size;   /* Number of bits in message */

   /* syn[i] (i = 1 to 6) is the vector of syndromes of the received message.
   All syndromes are represented as exponents of alpha.
   syn[0] is not used. */

   short syn[ 7 ];

   /* Table of delta[mu]'s in the modified Berlekamp algorithm.
   All dmu's are represented as exponents of alpha.
   dmu is indexed from -1 to 6. */

   short dmu_table[ 8 ];
   short *dmu;

   /* Table of orders of the sigma polynomials in the modified
   Berlekamp algorithm.
   lmu is indexed from -1 to 6.   */

   short lmu_table[ 8 ];
   short *lmu;

   /* Table of sigma polynomials.
   sigma(j,i) is the coefficient of x**(i-1) in the j'th polynomial.
   All coefficients are represented as exponents of alpha.
   sigma(j,i) is indexed from j = -1 to 6,
   and from i = 1 to 8 (i=0 is not used).   */

   typedef short shintarray[ 9 ];
   short sigma_table[ 8 ][ 9 ];
   shintarray *sigma;

   /* Local variables */

   //    float msg[ 82 ];          /* Temporary storage for message */
   BYTE msg[144];        /* Temporary storage for message */
   int count_inx;        /* The length of msg used */
   int correct;          /* Return value, TRUE if message correctable */
   //    short bit;            /* Message bit state (0 or 1) */
   short bit_inx;        /* Message bit index */
   short syn_inx;        /* Syndrome polynomial index */
   short sig_inx;        /* Sigma coefficient index */
   short all_syns_zero;  /* TRUE if all syndromes are 0; i.e. no errors */
   short next_log;       /* Next power of alpha value */
   short syn_val;        /* Calculated syndrome polynomial */
   short mu;             /* Index of rows in the Berlekamp plateau */
   short rho;            /* Index of rows in the Berlekamp plateau */
   short mp;             /* Index of polynomial equal to d[mu]/d[rho] */
   short lmp;            /* Degree of current polynomial (sigma[mu]) */
   short p;              /* General-purpose "GF-polynomial" variable used in
   tableau calculation */
   short s,u;            /* General purpose "exponent of alpha" variables
   used in tableau calculation */
   short i,j,l;          /* General purpose index/counters */
   short tmp;            /* Temporary variable */
   short num_err_input;  /* Number of bit corrections requested */
   int   NumErrs;

   /*------------------         EXECUTABLE CODE         -------------------*/

   //      num_err_input = NumErrs;   /* Number of bit corrections requested */
   if ( field_id == 2 )
   {
      /* Second protected field */
      num_err_input = 2;
      poly  = 0x43;   /* BCH(63,51) primitive generator polynomial: X^6 + X + 1 */
      order = 0x40;        /* Mask for MSB of primitive polynomial */
      t = 2;               /* Number of errors corrected by BCH code */
      bit_offset = 106;    /* Message block is bits 107 through 144 */
      msg_size   = 38;     /* Number of bits in message block */
   }
   else
   {
      /* First protected field */
      num_err_input = 3;
      poly = 0x89;/* BCH(127,106) primitive generator polynomial: X^7 + X^3 + 1 */
      order = 0x80;        /* Mask MSB of polynomial */
      t = 3;               /* Number of errors corrected by BCH code */
      bit_offset = 24;     /* Message block is bits 25 through 106 */
      msg_size   = 82;     /* Number of bits in message block */
   }

   n = order - 1;           /* Number of bits in message block */
   npred = n - 1;           /* Largest distinct power of alpha */

   /* If executing for the first time, set up the alpha log and
   power tables.  */

   /* Initialize log table so as to enable negative subscripting */

   logt = &(log_table[1]);

   /* Log and pow special case */

   logt[-1]  = 0;
   logt[0]   = 1;
   logt[127] = logt[0];
   powt[0]   = -1;
   powt[1]   =  0;

   /* Setup log and pow tables:
   alpha**0 = 1;  alpha**1 = x+0 (i.e., '10');
   alpha**i = 2*(alpha**(i-1)) modulo POLY  */

   for ( i = 1; i <= npred; i++ )
   {
      next_log = 2 * logt[i-1];
      if ( (next_log & order) != 0 )
      {
         next_log = (next_log ^ poly);
      }
      logt[i] = next_log;
      powt[next_log] = i;
   }

   /* Initialize tables so as to enable negative subscripting */
   dmu   = &(dmu_table[1]);
   lmu   = &(lmu_table[1]);
   sigma = (shintarray *) sigma_table[1];

   /* Make sure that syn, lmu, dmu and sigma tables are zeroed out */
   for ( i = -1; i <= 6; i++ )
   {
      if ( i > 0 )
      {
         syn[i] = 0;
      }
      lmu[i] = 0;
      dmu[i] = 0;
      for ( j = 0; j <= 8; j++ )
      {
         sigma[i][j] = 0;
      }
   }

   /* Initialize error count and return value to indicate no errors */
   correct   = true;
   NumErrs = 0;

   /* Copy message into temporary message */
   count_inx = 0;
   for ( i = 0; i < 18; i++ )
   {
      for ( int j = 0; j < 8; j++ )
      {
         msg[count_inx] = 0x01 & ( Message[i] >> ( 7 - j ) );
         count_inx++;
      }
   }


   for ( bit_inx = 0; bit_inx < msg_size; bit_inx++ )
   {
      msg[bit_inx] = msg[bit_offset + bit_inx];
   }

   /* Calculate 2*T syndromes: Sj for j=1 to T,
   Sj = SUM(i=0 to N-1) of  [Xi * (alpha**j)**i]
   where Xi is the ith bit in the codeword */
   all_syns_zero = true;
   for ( syn_inx = 1; syn_inx <= (2*t); syn_inx++ )
   {
      syn_val = 0;
      for ( bit_inx = 0; bit_inx < msg_size; bit_inx++ )
      {
         if ( msg[bit_inx] == 1 )
         {
            tmp = (syn_inx * (msg_size - bit_inx - 1)) % n;
            syn_val = syn_val ^ logt[tmp];
         }
      }

      syn[syn_inx] = powt[syn_val];
      if ( syn_val != 0 )
      {
         all_syns_zero = false;
      }
   }
   /* If all syndromes are zero then the codeword has no errors.
   Otherwise use Berlekamp algorithm to determine the
   error locator polynomial:
   sigma(x) = x**T + (sigma1 * x**(T-1)) + ... + (sigmaT-1 * x) + sigmaT */

   if ( !all_syns_zero )
   {
      dmu[0] = syn[1];
      mu     = 0;
      lmp    = 0;
      while ( mu < t )
      {
         if ( dmu[mu] < 0 )
         {
            /* d[mu] zero : copy sigma polynomial down */
            lmp       = lmu[mu];
            lmu[mu+1] = lmp;
            lmp       = lmp + 1;
            for ( i = 1; i <= lmp; i++ )
            {
               sigma[mu+1][i] = sigma[mu][i];
            }
         }
         else
         {
            /* d[mu] nonzero : choose rho */
            rho = mu - 1;
            while ( dmu[rho] < 0 )
            {
               rho--;
            }
            /* Perform polynomial arithmetic:
            p[mu+1](x) = p[mu](x) +
            d[mu]/d[rho] * x**(2*(mu-rho)) * p[rho](x)  */
            tmp = 2 * ( mu - rho );
            if ( rho == -1 )
            {
               tmp = 2 * mu + 1;
            }
            if ( lmu[mu] > ( lmu[rho] + tmp ) )
            {
               l = lmu[mu] + 1;
            }
            else
            {
               l = lmu[rho] + tmp + 1;
            }
            mp = ( dmu[mu] - dmu[rho] + n ) % n;

            for ( i=1; i <= l; i++ )
            {
               if ( i <= tmp )
               {
                  s = sigma[mu][i];
               }
               else
               {
                  p = 0;
                  s = sigma[rho][i - tmp];
                  if ( s >= 0 )
                  {
                     p = logt[(mp + s) % n];
                  }
                  if ( i <= ( lmu[mu] + 1 ) )
                  {
                     p = p ^ logt[sigma[mu][i]];
                  }
                  s = powt[p];
               }
               sigma[mu+1][i] = s;
               if ( s >= 0 )
               {
                  lmp = i;
               }
            }

            lmu[mu+1] = lmp - 1;
         }
         /* Algorithm ends when mu = T */
         mu = mu + 1;
         if ( mu < t )
         {
            /* Compute d[mu+1] for the next round */
            tmp = 2*mu + 2;
            p = logt[syn[tmp-1]];

            if ( lmp >= 2 )
            {
               for ( i = 2; i <= lmp; i++ )
               {
                  s = sigma[mu][i];
                  u = syn[tmp-i];
                  if ( (s | u) >= 0 )
                  {
                     p = (p ^ logt[(s+u) % n]);
                  }
               }
            }
            dmu[mu] = powt[p];
         }
      }
      /* Determine the roots of the error locator polynomial.
      these roots are found by substituting successive powers
      of alpha into the polynomial. each substitution that yields
      a zero result corresponds to an error bit.
      when an error bit is detected, it is complemented and the
      error count is incremented */
      lmp = lmu[t];
      if ( lmp > t )
      {
         correct = false;
         NumErrs = t+1;
      }
      else if ( lmp != 0 )
      {
         lmp = lmp + 1;
         for ( i = 1; i <= n; i++ )
         {
            tmp = n + 1 - i;
            p = logt[sigma[t][1]];
            for ( sig_inx = 2; sig_inx <= lmp; sig_inx++ )
            {
               if ( sigma[t][sig_inx] >= 0 )
               {
                  p = p ^ ( logt[((sig_inx-1)*tmp+sigma[t][sig_inx] ) % n]);
               }
            }
            if ( p == 0 )
            {
               bit_inx = msg_size - i;
               if ( bit_inx >= 0 )
               {
                  (NumErrs)++;
                  //                              msg[bit_inx] = -msg[bit_inx];
                  if ( msg[bit_inx] == 1 ) 
                  {
                     msg[bit_inx] = 0;
                  } 
                  else
                  {
                     msg[bit_inx] = 1;
                  }
               }
               else
               {
                  NumErrs = t+1;
                  correct = false;
               }
            }
         }
         if ( NumErrs != (lmp-1) )
         {
            correct = false;
            NumErrs = t+1;
         }
      }
   }
   correct = correct && ( NumErrs <= num_err_input );
   /* If correct, copy temporary message into message argument */
   if ( correct && modify )
   {
      //        for ( bit_inx = 0; bit_inx < msg_size; bit_inx++ )
      //        {
      //              Message[bit_offset + bit_inx] = msg[bit_inx];
      //        }

      BYTE tmpMsg;
      int words_offset = bit_offset / 8;
      int words_num = msg_size / 8;
      int idx;

      if ( field_id == 1 )
      {
         for ( bit_inx = 0; bit_inx < words_num ; bit_inx++ )
         {
            tmpMsg = 0x00;
            for ( idx = 0; idx < 8; idx++ )
            {
               tmpMsg |= ( ( msg[bit_inx * 8 + idx] & 0x01 ) << ( 7 - idx ) );
            }
            Message[bit_inx + words_offset] = tmpMsg;
         }
         Message[words_num + words_offset] &= 0x3F;
         Message[words_num + words_offset] |= ( ( msg[words_num * 8] & 0x01 ) << 7 );
         Message[words_num + words_offset] |= ( ( msg[words_num * 8 + 1] & 0x01 ) << 6);
      }
      else
      {
         Message[words_offset] &= 0xC0;
         tmpMsg = 0x00;
         for ( idx = 2; idx < 8; idx++ )
         {
            tmpMsg |= ( ( msg[idx-2] & 0x01 ) << ( 7 - idx ) );
         }
         Message[words_offset] |= tmpMsg;

         for ( bit_inx = 1; bit_inx < words_num + 1 ; bit_inx++ )
         {
            tmpMsg = 0x00;
            for ( idx = 0; idx < 8; idx++ )
            {
               tmpMsg |= ( ( msg[ ( bit_inx * 8 ) + idx - 2 ] & 0x01 ) << ( 7 - idx ) );
            }
            Message[bit_inx + words_offset] = tmpMsg;
         }
      }
   }
   return( NumErrs );
}

ULONG
CBCHCoder::CheckPDF1( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] )
{
    return ECCheck( 1, false, abyBcnMsg );
}

ULONG
CBCHCoder::CorrectPDF1( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] )
{
    return ECCheck( 1, true, abyBcnMsg );
}

ULONG
CBCHCoder::CheckPDF2( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] )
{
    return ECCheck( 2, false, abyBcnMsg );
}

ULONG
CBCHCoder::CorrectPDF2( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] )
{
    return ECCheck( 2, true, abyBcnMsg );
}
