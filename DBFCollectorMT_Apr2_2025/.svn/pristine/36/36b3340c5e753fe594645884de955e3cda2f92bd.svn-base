#pragma once
#include "SIGPROC.H"

class CTrackDBFSatellites
{
public:
	CTrackDBFSatellites(void);
	~CTrackDBFSatellites(void);
public:
	EMSCOMPLEX _CAdd ( EMSCOMPLEX cData1, EMSCOMPLEX cData2 );
	EMSCOMPLEX _CMultiply ( EMSCOMPLEX cData1, EMSCOMPLEX cData2 );
	EMSCOMPLEX _CSub ( EMSCOMPLEX cData1, EMSCOMPLEX cData2 );
	EMSCOMPLEX _CDivide ( EMSCOMPLEX cData);
	void _CVectorConj(const EMSCOMPLEX *X, EMSCOMPLEX *Y, int len);
	float _CNorm (EMSCOMPLEX cData);
	float _CVectorNorm (EMSCOMPLEX *cData, int len);
	EMSCOMPLEX  _CDotProd( const EMSCOMPLEX *src1, const EMSCOMPLEX *src2, int len);
	void computedbfvcorrelation(EMSCOMPLEX *dbfv1, int n1, EMSCOMPLEX   *dbfv2, int n2, double *corr12);
	int find_max_integerval(int *int_vect, int len);
	void find_max_val(double *val_vect, int len, double *maxval, int *maxidx);
	void find_max_val2d(double* val_matrix, int rows, int cols, double *maxval_vect, int *maxidx_vect);
	void find_larger_val(double *a,  int len, double threshold, int *I);
	void find_smaller_val(double *a,  int len, double threshold, int *I);
	void find_inbetween_val(double *a,  int len, double Tup, double Tlo, int *I);
	int find_min_index(double *x, int len);
	void sort1d(double *a, int len, double *b, int *I);
	int  find_largest_correlation( double *corr12, const int num_beams1, const int num_beams2,
	const double Tup,  double  *maxval_vect,  int *new_beam_idx_vect, int *matching_beam_idx_vect,
	double  *maxval_subvect,  int *new_beam_idx_subvect, int *matching_beam_idx_subvect );
	void  find_largest_correlation_in_order( double  *maxval_subvect,  int *new_beam_idx_subvect, 
    int *matching_beam_idx_subvect,  const int maxval_subvect_len, 
	double  *maxval_subvect_in_order, int *new_beam_idx_subvect_in_order, int *matching_beam_idx_subvect_in_order );
	int update_dbf_beam_id( double *corr12, const int num_beams1, const int num_beams2,
            int *beams1,  const double Tup,  const double Tlo, int *beams2, double  *pr);
	int track_dbf_beams( EMSCOMPLEX *dbfv1, const int num_beams1, EMSCOMPLEX   *dbfv2, const int num_beams2, 
		int *beams1, const double Tup,  const double Tlo, int *beams2, double  *pr);
	void find_common_dbf_beam_id( int *beams1, const int num_beams1,  int *beams2, const int num_beams2,
    int *id_set_common, int *I1, int *I2,
	int *index_set_extra1, int *index_set_extra2,
	int *id_set_common_size,  int *index_set_extra1_size, int *index_set_extra2_size);
	int track_dbf_satellites( int *beams1, const int num_beams1, int *beams2, const int num_beams2, 
		int *sats1, int *sats1_in_pass_schedule, int *sats2_in_pass_schedule, int *sats2);	
	int perform_dbf_beam_and_sat_tracking( EMSCOMPLEX   *dbfv1, const int num_beams1, 
          EMSCOMPLEX   *dbfv2, const int num_beams2, int *sats1_in_pass_schedule, int *sats2_in_pass_schedule, 
          int *beams1, int *sats1, const double Tup,  const double Tlo, int *beams2, int *sats2, double  *pr);
};

