#include "emsdbf.h"
#include "TrackDBFSatellites.h"


CTrackDBFSatellites::CTrackDBFSatellites(void)
{
}


CTrackDBFSatellites::~CTrackDBFSatellites(void)
{
}

// mytrackdbfsatellites_2021_03_14_for_Sunil.cpp


EMSCOMPLEX
CTrackDBFSatellites::_CAdd ( EMSCOMPLEX cData1, EMSCOMPLEX cData2 )
{
  EMSCOMPLEX cOutput;
  cOutput.re = cData1.re + cData2.re ;
  cOutput.im = cData1.im + cData2.im;
  return cOutput;
}

EMSCOMPLEX
CTrackDBFSatellites::_CMultiply ( EMSCOMPLEX cData1, EMSCOMPLEX cData2 )
{
  EMSCOMPLEX cOutput;
  cOutput.re = cData1.re * cData2.re - cData1.im * cData2.im;
  cOutput.im = cData1.re * cData2.im + cData1.im * cData2.re;;
  return cOutput;
}


EMSCOMPLEX
CTrackDBFSatellites::_CSub ( EMSCOMPLEX cData1, EMSCOMPLEX cData2 )
{
  EMSCOMPLEX cOutput;
  cOutput.re = cData1.re - cData2.re ;
  cOutput.im = cData1.im - cData2.im;
  return cOutput;
}

EMSCOMPLEX
CTrackDBFSatellites::_CDivide ( EMSCOMPLEX cData)
{
  EMSCOMPLEX cOutput;
  double dMagnitude = cData.re * cData.re + cData.im * cData.im;
  cOutput.re = cData.re/dMagnitude;
  cOutput.im = -cData.im/dMagnitude;
  return cOutput;
}


void CTrackDBFSatellites::_CVectorConj(const EMSCOMPLEX *X, EMSCOMPLEX *Y, int len)
{
	for (int k=0; k < len; k++)
	{
		Y[k].re =  X[k].re;
		Y[k].im = -X[k].im;
	}
}


float CTrackDBFSatellites::_CNorm (EMSCOMPLEX cData)
{
  return sqrt(cData.re*cData.re+cData.im*cData.im);   
}


float CTrackDBFSatellites::_CVectorNorm (EMSCOMPLEX *cData, int len)
{
   float sum=0.0;
   for(int k=0; k < len; k++)
   {
       sum += ( cData[k].re*cData[k].re + cData[k].im*cData[k].im);   
   }
   return sqrt(sum);
}

EMSCOMPLEX  CTrackDBFSatellites::_CDotProd( const EMSCOMPLEX *src1, const EMSCOMPLEX *src2, int len)
{
	int k;
	
	EMSCOMPLEX sum;
	
	sum.re=0; sum.im=0;
	
	for(k=0; k < len; k++)
	{
		sum = _CAdd(sum, _CMultiply(src1[k],src2[k]));
	}
	
	return sum;
}


void CTrackDBFSatellites::computedbfvcorrelation(EMSCOMPLEX *dbfv1, int n1, EMSCOMPLEX   *dbfv2, int n2, double *corr12)
{
    int v1, v2;
    EMSCOMPLEX  c;
    EMSCOMPLEX  conjugatedbfv[NUM_CHANNELS];
    
    for(v2=0; v2 < n2; v2++)
    {
        for(v1=0; v1 < n1; v1++)
        {
            _CVectorConj(dbfv1+NUM_CHANNELS*v1,conjugatedbfv,NUM_CHANNELS);
            
            c = _CDotProd(dbfv2+NUM_CHANNELS*v2, conjugatedbfv,NUM_CHANNELS);
            
            corr12[v2*n1+v1] = (double)(_CNorm(c)/_CVectorNorm(dbfv2+NUM_CHANNELS*v2,NUM_CHANNELS)/_CVectorNorm(dbfv1+NUM_CHANNELS*v1,NUM_CHANNELS));    
        }   
    }  
}


int CTrackDBFSatellites::find_max_integerval(int *int_vect, int len)
{
    int k;   
	
	int maxint = int_vect[0];
    
    for (k=1; k < len; k++)
    {
         if ( int_vect[k] > maxint )
         {
             maxint = int_vect[k];
         }
    }
    
    return maxint; 
}


void CTrackDBFSatellites::find_max_val(double *val_vect, int len, double *maxval, int *maxidx)
{
    int k;
    *maxval =val_vect[0];
    *maxidx=0;
    for (k=1; k < len; k++)
    {
         if ( val_vect[k] > (*maxval) )
         {
             *maxval=val_vect[k];
             *maxidx=k;
         }
    }
}


void CTrackDBFSatellites::find_max_val2d(double* val_matrix, int rows, int cols, double *maxval_vect, int *maxidx_vect)
{
	int m=rows;
	
	int n=cols;
	
    for(int col=0; col< n; col++)
    {
        find_max_val(val_matrix+col*m, m, maxval_vect+col, maxidx_vect+col);		
    }
}


void CTrackDBFSatellites::find_larger_val(double *a,  int len, double threshold, int *I)
{
    memset(I, 0, sizeof(int)*MAX_BEAMS);
    for (int k=0; k< len; k++)
    {
        if ( a[k] > threshold)
        {
            I[k] =1;
        }else
        {
            I[k]=0;   
        }  
    }  
}


void CTrackDBFSatellites::find_smaller_val(double *a,  int len, double threshold, int *I)
{
     memset(I, 0, sizeof(int)*MAX_BEAMS);
     
    for (int k=0; k< len; k++)
    {
        if ( a[k] < threshold)
        {
            I[k] =1;
        }else
        {
            I[k]=0;   
        }  
    }  
}


void CTrackDBFSatellites::find_inbetween_val(double *a,  int len, double Tup, double Tlo, int *I)
{
     memset(I, 0, sizeof(int)*MAX_BEAMS);
     
    for (int k=0; k< len; k++)
    {
        if ( ( a[k] <= Tup) && ( a[k] >= Tlo) )
        {
            I[k] =1;
        }else
        {
            I[k]=0;   
        }  
    }  
}


int CTrackDBFSatellites::find_min_index(double *x, int len)
{
    int min_index;
    int i;  
    min_index=0;
    for(i=1; i< len; i++)
    {
        if (x[i]<x[min_index])
        {
             min_index=i;   
        }
    }
    return min_index;
}

void CTrackDBFSatellites::sort1d(double *a, int len, double *b, int *I)
{
    int p[5*MAX_BEAMS];
    int q[5*MAX_BEAMS];
    double d[5*MAX_BEAMS];
    
    int i;
	
    if (len == 1)
    {
        b[0]=a[0];
        I[0]=0;
    }else
    {
        for (int k=0; k< len-1; k++)
        {
           p[k] = k+1;
        } 
        
        i=find_min_index(a,len);
        if (i==0)
        {
            b[0]=a[0];
            I[0]=0;
             
        }else
        {
            b[0] = a[i];
            I[0] = i;
            a[i] = a[0];
            p[i-1]=0;       
        }
        
		sort1d(a+1,len - 1,d, q);
        
		for (int j=0; j< len-1; j++)
        {
             b[j+1] =d[j];   
             I[j+1]=p[q[j]];  
        }     
    } 
}


int  CTrackDBFSatellites::find_largest_correlation( double *corr12, const int num_beams1, const int num_beams2,
   const double Tup,  double  *maxval_vect,  int *new_beam_idx_vect, int *matching_beam_idx_vect,
   double  *maxval_subvect,  int *new_beam_idx_subvect, int *matching_beam_idx_subvect )
{    
    int maxval_subvect_len;     
	   
	int I[MAX_BEAMS];
	
	int incr;
	
    for(int idx = 0; idx < num_beams2; idx++)
	{
		new_beam_idx_vect[idx] = idx;  
	}
	
	find_max_val2d(corr12, num_beams1, num_beams2, maxval_vect, matching_beam_idx_vect);
	
	memset(I, 0, sizeof(int)*num_beams2);
    
	find_larger_val(maxval_vect,  num_beams2, Tup, I); //length(I) = num_beams2

	memset(maxval_subvect, 0, sizeof(double)*num_beams2); 
	memset(matching_beam_idx_subvect, 0, sizeof(int)*num_beams2);
	memset(new_beam_idx_subvect, 0, sizeof(int)*num_beams2);
	
	incr = 0;
	
	for (int idx = 0; idx < num_beams2; idx++)
	{
		if ( I[idx] == 1 )
		{	
			maxval_subvect[incr] = maxval_vect[idx];
			matching_beam_idx_subvect[incr] =  matching_beam_idx_vect[idx];
			new_beam_idx_subvect[incr] =  new_beam_idx_vect[idx];   
            incr++;
		}
       
	}  

    maxval_subvect_len = incr;
	
	return maxval_subvect_len;
}


void  CTrackDBFSatellites::find_largest_correlation_in_order( double  *maxval_subvect,  int *new_beam_idx_subvect, 
    int *matching_beam_idx_subvect,  const int maxval_subvect_len, 
	double  *maxval_subvect_in_order, int *new_beam_idx_subvect_in_order, int *matching_beam_idx_subvect_in_order )
{
	int  J[MAX_BEAMS];
	
	int new_beam_idx_subvect_in_order0[MAX_BEAMS];
	int matching_beam_idx_subvect_in_order0[MAX_BEAMS];
	double maxval_subvect_in_order0[MAX_BEAMS];
    
	if (maxval_subvect_len > 0)
    {
        memset(J, 0, sizeof(int)*maxval_subvect_len);
        
        sort1d(maxval_subvect, maxval_subvect_len, maxval_subvect_in_order0, J);
        
        memset(matching_beam_idx_subvect_in_order0, 0, sizeof(int)*maxval_subvect_len);
        memset(new_beam_idx_subvect_in_order0, 0, sizeof(int)*maxval_subvect_len);
	
        for (int idx = 0; idx < maxval_subvect_len; idx++)
        {
            matching_beam_idx_subvect_in_order0[idx] = matching_beam_idx_subvect[J[idx]];
            new_beam_idx_subvect_in_order0[idx]      = new_beam_idx_subvect[J[idx]];
        }

        memset(maxval_subvect_in_order, 0, sizeof(float)*maxval_subvect_len);
        memset(matching_beam_idx_subvect_in_order, 0, sizeof(int)*maxval_subvect_len);
        memset(new_beam_idx_subvect_in_order, 0, sizeof(int)*maxval_subvect_len);
	
        for (int idx = 0; idx < maxval_subvect_len; idx++)
        {
            maxval_subvect_in_order[idx] = maxval_subvect_in_order0[maxval_subvect_len-1-idx];
            matching_beam_idx_subvect_in_order[idx]= matching_beam_idx_subvect_in_order0[maxval_subvect_len-1-idx];
            new_beam_idx_subvect_in_order[idx] =new_beam_idx_subvect_in_order0[maxval_subvect_len-1-idx];
        }
    }else if (maxval_subvect_len == 0)
    {
        memset( maxval_subvect_in_order, 0, sizeof(double)*MAX_BEAMS); 
        memset( matching_beam_idx_subvect_in_order, 0, sizeof(int)*MAX_BEAMS); 
        memset( new_beam_idx_subvect_in_order, 0, sizeof(int)*MAX_BEAMS);  
    }
}





int CTrackDBFSatellites::update_dbf_beam_id( double *corr12, const int num_beams1, const int num_beams2,
            int *beams1,  const double Tup,  const double Tlo, int *beams2, double  *pr)
{
	int hr = -1;
	
	int incr, index_found, mysum;
	
	int last_idx1, last_idx2, v1, v2, v3;
	
	int new_beam_idx_vect[MAX_BEAMS];
	
	int new_beam_idx_subvect[MAX_BEAMS];
	
	int new_beam_idx_subvect_in_order[MAX_BEAMS];
	
	int matching_beam_idx_vect[MAX_BEAMS];
	
	int matching_beam_idx_subvect[MAX_BEAMS];
	
	int matching_beam_idx_subvect_in_order[MAX_BEAMS];
	
	double maxval_vect[MAX_BEAMS];
	
	double maxval_subvect[MAX_BEAMS];
	
	double maxval_subvect_in_order[MAX_BEAMS];
           
    int maxval_subvect_len;     
	   
	int I[MAX_BEAMS], J[MAX_BEAMS];
	
	if ( (num_beams1 < 1) || (num_beams1 > MAX_BEAMS) )
		return hr;
	
	if ( (num_beams2 < 1) || (num_beams2 > MAX_BEAMS) )
		return hr;
	
	if ( (Tup <= 0 ) || (Tup > 1) || (Tlo <= 0 ) || (Tlo > 1) || (Tup <= Tlo) )
		return hr;
	
	if ( (!corr12) || (!beams1) || (!beams2) || (!pr) )
		return hr;
	
	memset(maxval_vect, 0, sizeof(double)*num_beams2);
	memset(maxval_subvect, 0, sizeof(double)*num_beams2);
	memset(maxval_subvect_in_order, 0, sizeof(double)*num_beams2);
	
	memset(matching_beam_idx_vect, 0, sizeof(int)*num_beams2);
	memset(matching_beam_idx_subvect, 0, sizeof(int)*num_beams2);
	memset(matching_beam_idx_subvect_in_order,0, sizeof(int)*num_beams2);
	
	memset(new_beam_idx_vect, 0, sizeof(int)*num_beams2);
	memset(new_beam_idx_subvect, 0, sizeof(int)*num_beams2);
	memset(new_beam_idx_subvect_in_order, 0, sizeof(int)*num_beams2);
	
	int index_set_is_incremented = 0;
	
	int MAX = find_max_integerval(beams1, num_beams1);
	
	memset(beams2, -1, sizeof(int)*num_beams2);
	
    if (num_beams1 == num_beams2)
	{
		maxval_subvect_len =  find_largest_correlation( corr12,  num_beams1, num_beams2,
             Tup,  maxval_vect,     new_beam_idx_vect,    matching_beam_idx_vect,
                   maxval_subvect,  new_beam_idx_subvect, matching_beam_idx_subvect );
		
		if (maxval_subvect_len > 0)
		{
			find_largest_correlation_in_order( maxval_subvect, new_beam_idx_subvect, matching_beam_idx_subvect, 
			maxval_subvect_len, 
	        maxval_subvect_in_order, new_beam_idx_subvect_in_order,matching_beam_idx_subvect_in_order);
			
			index_set_is_incremented = 0;
			
			for ( int idx=0; idx <  maxval_subvect_len; idx++) 
			{	
		       if (idx == 0)
			   {
					beams2[new_beam_idx_subvect_in_order[idx]] =  beams1[matching_beam_idx_subvect_in_order[idx]];					
			   }else if (idx > 0)
			   {	
					for (int  idx2 = 0; idx2 < idx; idx2++)
					{
                        if (beams2[ new_beam_idx_subvect_in_order[idx2] ] == beams1[matching_beam_idx_subvect_in_order[idx]])
						{
							MAX = MAX+1;
							index_set_is_incremented = index_set_is_incremented +1;
							beams2[new_beam_idx_subvect_in_order[idx]] = MAX;
						}else
						{
							beams2[new_beam_idx_subvect_in_order[idx]] = beams1[matching_beam_idx_subvect_in_order[idx]];
						}	
					}
			    }
			}
        
        
            if ( (num_beams2 > 1 ) && (index_set_is_incremented ==0) && ( maxval_subvect_len == (num_beams2-1) ) )
            {
                index_found =0;
                for (int idx=0; idx < num_beams2; idx++)
                {
                    mysum=0;
                    
                    for (int idx2 = 0; idx2 < (num_beams2-1); idx2++)
                    {
                        if (new_beam_idx_subvect_in_order[idx2] != idx)
                            mysum++;
                    }
                    
                    if ( mysum == ( num_beams2-1) )
                    {
                        index_found = 1;
                        last_idx2 = idx;
                        continue;
                    }
                }
                
                index_found =0;
                for ( int idx=0; idx< num_beams1; idx++)
                {
                    mysum=0;
                    
                    for(int  idx2=0; idx2 < num_beams1-1; idx2++)
                    {
                        if ( matching_beam_idx_subvect_in_order[idx2] != idx)
                            mysum++;
                    }
                    
                    if ( mysum == (num_beams1-1) )
                    {
                        index_found=1;
                        last_idx1=idx;
                        continue;
                    }
                }
                //table{k+1}(last_idx2) =table{k}(last_idx1);
                beams2[last_idx2] = beams1[last_idx1];
            }else
            {
                //I=myfindinbetween(maxval_vect,Tup, Tlo);
                memset(I,0, sizeof(int)*num_beams2);
                find_inbetween_val(maxval_vect,  num_beams2, Tup, Tlo, I);
                
                for (int idx=0; idx< num_beams2;idx++)
                {
                    if ( I[idx] ==1 )
                    {
                        v2= idx;
                        for (v3=0; v3 < num_beams2; v3++)
                        {
                            if  ( beams2[v3] == beams1[v2] )
                            {
                                MAX = MAX+1;
                                beams2[v2] = MAX;
                            }
                        }
                        if ( beams2[v2] == -1 )
                        {
                            beams2[v2] = beams1[v2];
                        }
                    }
                }
                
                //I=myfindsmallerval(maxval_vect, Tlo);
                memset(I,0, sizeof(int)*num_beams2);
                find_smaller_val(maxval_vect,  num_beams2, Tlo, I);
                
                for(int idx=0;  idx< num_beams2; idx++)
                {
                    if ( I[idx] == 1)
                    {
                        v2 = idx;
                        MAX = MAX+1;
                        beams2[v2] = MAX;
                    }
                }
            }
        }else if (maxval_subvect_len == 0)
        {
            //I=myfindinbetween(maxval_vect,Tup, Tlo);
            memset(I,0, sizeof(int)*num_beams2);
            find_inbetween_val(maxval_vect,  num_beams2, Tup, Tlo, I);
            
            for (int idx=0; idx< num_beams2;idx++)
            {
                if ( I[idx] ==1 )
                {
                    v2= idx;
                    for (v3=0; v3 < num_beams2; v3++)
                    {
                        if  ( beams2[v3] == beams1[v2] )
                        {
                            MAX = MAX+1;
                            beams2[v2] = MAX;
                        }
                    }
                    if ( beams2[v2] == -1 )
                    {
                        beams2[v2] = beams1[v2];
                    }
                }
            }
            
            //I=myfindsmallerval(maxval_vect, Tlo);
            memset(I,0, sizeof(int)*num_beams2);
            find_smaller_val(maxval_vect,  num_beams2, Tlo, I);
            
            for(int idx=0;  idx< num_beams2; idx++)
            {
                if ( I[idx] == 1)
                {
                    v2 = idx;
                    MAX = MAX+1;
                    beams2[v2] = MAX;
                }
            }
        }
        
    } else if (num_beams1 < num_beams2)   
	{   	
		maxval_subvect_len =  find_largest_correlation( corr12,  num_beams1, num_beams2,
             Tup,  maxval_vect,     new_beam_idx_vect,    matching_beam_idx_vect,
                   maxval_subvect,  new_beam_idx_subvect, matching_beam_idx_subvect );
		
		if (maxval_subvect_len > 0)
		{
			find_largest_correlation_in_order( maxval_subvect, new_beam_idx_subvect, matching_beam_idx_subvect, maxval_subvect_len, 
	           maxval_subvect_in_order, new_beam_idx_subvect_in_order,matching_beam_idx_subvect_in_order);
			   
			index_set_is_incremented = 0;
			
            for ( int idx=0; idx <  maxval_subvect_len; idx++) 
			{	
		       if (idx == 0)
			   {
					beams2[new_beam_idx_subvect_in_order[idx]] =  beams1[matching_beam_idx_subvect_in_order[idx]];
			   }else if (idx > 0)
			   {	
					for (int  idx2 = 0; idx2 < idx; idx2++)
					{
                        if (beams2[ new_beam_idx_subvect_in_order[idx2] ] == beams1[matching_beam_idx_subvect_in_order[idx]])
						{
							MAX = MAX+1;
							index_set_is_incremented = index_set_is_incremented +1;
							beams2[new_beam_idx_subvect_in_order[idx]] = MAX;
						}else
						{
							beams2[new_beam_idx_subvect_in_order[idx]] = beams1[matching_beam_idx_subvect_in_order[idx]];
						}	
					}
				}
			}
        }	
        
        
        //I=myfindinbetween(maxval_vect,Tup, Tlo);
        memset(I,0, sizeof(int)*num_beams2);
        
        find_inbetween_val(maxval_vect,  num_beams2, Tup, Tlo, I);
			 
        for (int idx=0; idx< num_beams2;idx++)
        {
            if ( I[idx] ==1 )
            {
                v2= idx;
                if ( v2 < num_beams1)   //bug if ( v2 <= num_beams1)
                {
                    for (v3=0; v3 < num_beams2; v3++)
                    {
                        if  ( beams2[v3] == beams1[v2] )
                        {
                            MAX = MAX+1;
                            beams2[v2] = MAX;
                        }
                    }
                    
                    if ( beams2[v2] == -1 )
                    {
                        beams2[v2] = beams1[v2];
                    }
                }else
                {
                    MAX = MAX+1;
                    beams2[v2] = MAX;
                }
            }
        }

        //I=myfindsmallerval(maxval_vect, Tlo);
        memset(I,0, sizeof(int)*num_beams2);
        find_smaller_val(maxval_vect,  num_beams2, Tlo, I);
        
        for(int idx=0;  idx< num_beams2; idx++)
        {
            if ( I[idx] == 1)
            {
                v2 = idx;
                MAX = MAX+1;
                beams2[v2] = MAX;
            }
        }
        
	}else if  ( num_beams1 > num_beams2 )                 
	{	
        maxval_subvect_len =  find_largest_correlation( corr12,  num_beams1, num_beams2,
             Tup,  maxval_vect,     new_beam_idx_vect,    matching_beam_idx_vect,
                   maxval_subvect,  new_beam_idx_subvect, matching_beam_idx_subvect );
		
		if (maxval_subvect_len > 0)
		{
			find_largest_correlation_in_order( maxval_subvect, new_beam_idx_subvect, matching_beam_idx_subvect, 
			maxval_subvect_len, 
	        maxval_subvect_in_order, new_beam_idx_subvect_in_order, matching_beam_idx_subvect_in_order);
			   
			index_set_is_incremented = 0;
			
            for ( int idx=0; idx <  maxval_subvect_len; idx++) 
			{	
		       if (idx == 0)
			   {
					beams2[new_beam_idx_subvect_in_order[idx]] =  beams1[matching_beam_idx_subvect_in_order[idx]];
			   }else if (idx > 0)
			   {	
					for (int  idx2 = 0; idx2 < idx; idx2++)
					{
                        if (beams2[ new_beam_idx_subvect_in_order[idx2] ] == beams1[matching_beam_idx_subvect_in_order[idx]])
						{
							MAX = MAX+1;
							index_set_is_incremented = index_set_is_incremented +1;
							beams2[new_beam_idx_subvect_in_order[idx]] = MAX;
						}else
						{
							beams2[new_beam_idx_subvect_in_order[idx]] = beams1[matching_beam_idx_subvect_in_order[idx]];
						}	
					}
				}
			}		
        }
              
	    //I=myfindinbetween(maxval_vect,Tup, Tlo);
		memset(I,0, sizeof(int)*num_beams2); 
		find_inbetween_val(maxval_vect,  num_beams2, Tup, Tlo, I);
		 
		for (int idx=0; idx< num_beams2;idx++)  
		{	 
			if ( I[idx] == 1 )
			{
				 v2= idx;
				 for (v3=0; v3 < num_beams2; v3++)    
				 {
					 if  ( beams2[v3] == beams1[v2] )
					 {
						 MAX = MAX+1;
						 beams2[v2] = MAX;
					 }	 
				 }		 
				 if ( beams2[v2] == -1 )
				 {
					 beams2[v2] = beams1[v2];
				 }	 
			}
		}
		 
		 //I=myfindsmallerval(maxval_vect, Tlo);
		 memset(I,0, sizeof(int)*num_beams2); 
		 find_smaller_val(maxval_vect,  num_beams2, Tlo, I);
		 
		 for(int idx=0;  idx< num_beams2; idx++)  
		 {	 
			  if ( I[idx] == 1)
			  { 
				 v2 = idx;
				 MAX = MAX+1;
				 beams2[v2] = MAX;
			  }
		 }      	
    } 
	for (int idx=0; idx < num_beams2; idx++)
	{
		pr[idx]= maxval_vect[idx];
	}

    return 1;   
}


int CTrackDBFSatellites::track_dbf_beams( EMSCOMPLEX *dbfv1, const int num_beams1, EMSCOMPLEX   *dbfv2, const int num_beams2, 
int *beams1, const double Tup,  const double Tlo, int *beams2, double  *pr)
{
    int hr;
	
	double corr12[MAX_BEAMS*MAX_BEAMS];
	
    computedbfvcorrelation(dbfv1, num_beams1, dbfv2, num_beams2, corr12);
    
    hr = update_dbf_beam_id( corr12, num_beams1, num_beams2, beams1, Tup, Tlo, beams2, pr);
	
	return hr;
}


void CTrackDBFSatellites::find_common_dbf_beam_id( int *beams1, const int num_beams1,  int *beams2, const int num_beams2,
     int *id_set_common, int *I1, int *I2,
	 int *index_set_extra1, int *index_set_extra2,
	 int *id_set_common_size,  int *index_set_extra1_size, int *index_set_extra2_size)
{
	int incr;
    int mysum;
	memset(I1, 0, sizeof(int)*MAX_BEAMS);
	memset(I2, 0, sizeof(int)*MAX_BEAMS);
	incr = 0;
	for ( int idx1 = 0; idx1 < num_beams1; idx1++)     
	{    
		for (int idx2 = 0;  idx2 < num_beams2; idx2++) 
		{	
			if ( beams1[idx1] == beams2[idx2] ) 
			{
				if( incr >= MAX_BEAMS )
				{
					//shouldnt happen..
					continue;
				}
				id_set_common[incr] = beams1[idx1]; 
				I1[incr] = idx1;
				I2[incr] = idx2;
                incr++;
			}
		}
	}	
	*id_set_common_size = incr;
			
	incr=0;	
	memset(index_set_extra1, 0, sizeof(int)*MAX_BEAMS);
	for ( int idx1 = 0; idx1 < num_beams1; idx1++) 
	{ 
		mysum=0;
		for (int idx2=0;  idx2 < num_beams2;  idx2++)  
		{
			if (beams1[idx1] != beams2[idx2]) 
				mysum++;    
		}
		if (mysum == num_beams2 )  
			index_set_extra1[incr++]  = idx1;
	}
	*index_set_extra1_size = incr;
	
	incr=0;	
	memset(index_set_extra2, 0, sizeof(int)*MAX_BEAMS);
	for (int idx2 = 0; idx2 < num_beams2; idx2++) 
	{   
		mysum=0;
		for (int  idx1 = 0; idx1 < num_beams1; idx1++ )
		{   
			if ( beams2[idx2] !=  beams1[idx1] )
				mysum++;    
		}        
		if ( mysum == num_beams1 )
			index_set_extra2[incr++] = idx2;  
	}
	
	*index_set_extra2_size = incr;	
}


int CTrackDBFSatellites::track_dbf_satellites( int *beams1, const int num_beams1, int *beams2, const int num_beams2, 
 int *sats1, int *sats1_in_pass_schedule, int *sats2_in_pass_schedule, int *sats2)
{
    int hr, incr, mysum;
	
	int id_set_common[MAX_BEAMS];
	int index_set_extra1[MAX_BEAMS];
    int index_set_extra2[MAX_BEAMS];
	
	int id_set_common_size;
	int index_set_extra1_size = 0; 
    int index_set_extra2_size = 0;
	
	int I1[MAX_BEAMS];
	
    int I2[MAX_BEAMS];
	
	memset(I1, 0, sizeof(int)*MAX_BEAMS);
	
	memset(I2, 0, sizeof(int)*MAX_BEAMS);
	
	
	if ( (num_beams1 < 1) || (num_beams1 > MAX_BEAMS) )
		return hr;
	
	if ( (num_beams2 < 1) || (num_beams2 > MAX_BEAMS) )
		return hr;
	
	if ( (!beams1) || (!beams2) || (!sats1) || (!sats2) || (!sats1_in_pass_schedule) || (!sats2_in_pass_schedule) )
		return hr;
	
	if (num_beams1 == num_beams2)
	{
        //table1{k+1} = table1{k};
		for(int idx=0; idx< num_beams2; idx++)
		{
			//This needs more refinements
			sats2[idx]= sats1[idx];	
		}
		
		find_common_dbf_beam_id( beams1, num_beams1, beams2, num_beams2,
          id_set_common, I1, I2,
	      index_set_extra1, index_set_extra2,
	      &id_set_common_size,  &index_set_extra1_size, &index_set_extra2_size);
		
        if ( id_set_common_size == 0 )
		{
		   for (int idx = 0; idx < num_beams2; idx++)
		   {
			   sats2[idx] = sats2_in_pass_schedule[idx];   
		   }
		}else if ( id_set_common_size == num_beams2 ) 
		{ 
			for (int  idx = 0; idx < id_set_common_size; idx++ )
            { 				
                sats2[I2[idx]] = sats1[I1[idx]];  
            } 				
		}else if (  (num_beams2 > 1) &&  (id_set_common_size == (num_beams2 - 1)) )              
		{ 
			for (int idx= 0; idx < id_set_common_size; idx++)    
				sats2[I2[idx]] = sats1[I1[idx]];
			
			sats2[index_set_extra2[0]]= sats1[index_set_extra1[0]];
						
        }else
		{
            for (int idx= 0; idx < id_set_common_size; idx++)    
				sats2[I2[idx]] = sats1[I1[idx]]; 			  	   
        } 
			
	}else if (num_beams1 < num_beams2)
	{
        //table1{k+1} = zeros(1,m(k+1));
        //table1{k+1}(1:m(k)) = table1{k};
        //table1{k+1}(m(k)+1:m(k+1)) =SAT_ID{k+1}(m(k)+1: m(k+1));
		for(int idx = 0; idx < num_beams1; idx++)
		{
			sats2[idx]= sats1[idx];	
		}
		for (int idx = 0; idx < (num_beams2 - num_beams1); idx++)
		{
			//This needs more refinements
			sats2[num_beams1+idx] = sats2_in_pass_schedule[num_beams1+idx];	
		}
		
		find_common_dbf_beam_id( beams1, num_beams1, beams2, num_beams2,
          id_set_common, I1, I2,
	      index_set_extra1, index_set_extra2,
	      &id_set_common_size,  &index_set_extra1_size, &index_set_extra2_size);
		
        if ( id_set_common_size == 0 )
		{
		   for (int idx=0; idx < num_beams2; idx++)
		   {
			   sats2[idx] = sats2_in_pass_schedule[idx];   
		   }
		}else if ( id_set_common_size == num_beams1 ) 
		{	
            for (int  idx= 0; idx < id_set_common_size; idx++ )
            { 				
                sats2[I2[idx]] = sats1[I1[idx]];  
            } 
			
			for(int idx=0; idx < index_set_extra2_size; idx++)
               		sats2[index_set_extra2[idx]] = sats2_in_pass_schedule[num_beams1+idx];	
				
        }else  
		{  
            for (int  idx= 0; idx < id_set_common_size; idx++ )
            { 				
                sats2[I2[idx]] = sats1[I1[idx]];  
            }    
        }
		
    }else if (num_beams1 > num_beams2)
	{      
        //table1{k+1} = zeros(1,m(k+1));
        //table1{k+1}(1:m(k+1)) = table1{k}(1:m(k+1));
        for(int idx = 0; idx < num_beams2; idx++)
		{
			//This needs more refinements
			sats2[idx]= sats1[idx];	
		}
				
	    find_common_dbf_beam_id( beams1, num_beams1, beams2, num_beams2,
	      id_set_common, I1, I2,
	      index_set_extra1, index_set_extra2,
	      &id_set_common_size,  &index_set_extra1_size, &index_set_extra2_size);
             
        if ( id_set_common_size == 0 )
		{
		   for (int idx=0; idx < num_beams2; idx++)
		   {
			   sats2[idx] = sats2_in_pass_schedule[idx];   
		   }
		}else if ( id_set_common_size == num_beams2 )
		{        
            for (int  idx= 0; idx < id_set_common_size; idx++ )
            { 				
                sats2[I2[idx]] = sats1[I1[idx]];  
            }
		}else
		{
            for (int  idx= 0; idx < id_set_common_size; idx++ )
            { 				
                sats2[I2[idx]] = sats1[I1[idx]];  
            }  
        }  		
	}
    hr=1;
    return hr;
}



int CTrackDBFSatellites::perform_dbf_beam_and_sat_tracking(
          EMSCOMPLEX   *dbfv1, const int num_beams1, 
          EMSCOMPLEX   *dbfv2, const int num_beams2, 
          int *sats1_in_pass_schedule, int *sats2_in_pass_schedule, 
          int *beams1, int *sats1, 
          const double Tup,  const double Tlo, 
          int *beams2, int *sats2, double  *pr)
{
	//dbfv1: array storing the old dbf beam vectors, each dbf beam vector containing NUM_CHANNELS=31 entries 
	//num_beams1: number of dbf beam vectors in the array dbfv1
	//
	//dbfv2: array storing the new dbf beam vectors, each dbf beam vector containing NUM_CHANNELS=31 entries 
	//num_beams2: number of dbf beam vectors in the array dbfv1
	//
	//sats1_in_pass_schedule: array storing the satellite IDs retrieved from the pass schedule associated
	//with the dbf beam vectors in dbfv1.
	// It is assumed that the number of dbf beam vectors in the array dbfv1, num_beams1, is the same as the
    // number of satellites retrieved from the pass schedule associated with the dbf beam vectors in dbfv1.	
	// Thus the number of satellite IDs in sats1_in_pass_schedule must be identical to num_beams1.
	//
	//sats2_in_pass_schedule: array storing the satellite IDs retrieved from the pass schedule associated
	//with the dbf beam vectors in dbfv2.
	// It is assumed that the number of dbf beam vectors in the array dbfv2, num_beams2, is the same as the
    // number of satellites retrieved from the pass schedule associated with the dbf beam vectors in dbfv2.	
	// Thus the number of satellite IDs in sats2_in_pass_schedule must be identical to num_beams2.
	//
	//beams1: array storing the dbf beam IDs for the dbf beam vectors stored in the array dbfv1.
	//There are num_beams1 dbf beam IDs in beams1.
	// beams1 is initialized from 1 to N at the start of this tracking algorithm, with N denoting the number of
	// dbf beam vectors (number of satellites) calculated at the start of this tracking algorithm.
	//For instance, if the number of dbf beam vectors at the start of this tracking algorithm is 5, N is set to 5.
	//The dbf beam vector IDs for each set of dbf beam vectors calculated from a 1 second data buffer will always be distinct.
	//
	//sats1: array storing the predicted satellite IDs for the dbf beam vectors stored in the array dbfv1.
	//There are num_beams1 satellite IDs in sats1.
	//sats1 is initialized, at the start of this tracking algorithm, as the satellite IDs given by the pass schedule
    //associated with the 1 second data buffer used to calculate the dbf beam vectors in dbfv1, in decreasing order of
	//the satellite elevation angles.
	//For instance, if the number of dbf beam vectors at the start of this tracking algorithm is N=5 and the satellite IDs
	//retrieved from the pass schedule associated with the 1 second data buffer used to calculate the dbf beam vectors
	//in dbfv1 are given, in the decreasing order of elevation angles, 401, 421, 403, 409, 419. Then the array sats1 will be 
	//initialized as {401, 421, 403, 409, 419}.
	//
	//beams2: array storing the updated dbf beam IDs for the dbf beam vectors stored in the array dbfv2 based on
	//the correlation between the dbf beam vectors in the array dbfv2 and those in the array.
	//There are num_beams2 dbf beam IDs in beams2.
    //Again note that the dbf beam vector IDs for each set of dbf beam vectors calculated from a 1 second data buffer will always be distinct
	//and thus the IDs in beams2 must be distinct.
	//
	//It must be noted that no specific meaning is attached each dbf beam ID!
	//
	//sats2: array storing the predicted satellite IDs for the dbf beam vectors stored in the array dbfv2 based on the dbf
	//beam vectors in beams2 and satellite IDs stored in the three arrays sats1, sats1_in_pass_schedule, and sats2_in_pass_schedule.
	//There are num_beams2 satellite IDs in sats2.
	//
	//pr: array storing the reliability level, a real number in between 0 and 1, of the predicted dbf beam vector IDs 
	//
	// March 14, 2021, SW

    int hr=-1;
	
    hr = track_dbf_beams(dbfv1, num_beams1, dbfv2, num_beams2, 
              beams1, Tup, Tlo, beams2, pr);
    
	if (hr == 1)
	{
		hr = track_dbf_satellites(beams1, num_beams1, beams2, num_beams2, 
           sats1, sats1_in_pass_schedule, sats2_in_pass_schedule, sats2);	
	}
	
	return hr;
}


