#include "HGTEigenVectors.h"
#include "DBFCollectorConfig.h"
#include <fstream>
#include <iomanip>
void CHGTEigenVectors::_Init( const MKL_Complex8 *acCovarianceMatrix  )
{
   // memcpy( m_inputMatrix,acCovarianceMatrix, EIGEN_ROWS* EIGEN_ROWS  * sizeof(MKL_Complex8) );
	m_inputMatrix = const_cast< MKL_Complex8 *> ( acCovarianceMatrix );

}

void CHGTEigenVectors::PerformEigenDecomposition(const MKL_Complex8 *acCovarianceMatrix, 
                              float *EigenValues, MKL_Complex8 *acEigenVectors)
{
	_Init( acCovarianceMatrix );
	_CreateEigenVectors(EigenValues, acEigenVectors );

}

	
void
CHGTEigenVectors::print_matrix( char* desc, MKL_INT m, MKL_INT n, MKL_Complex8* a, MKL_INT lda ) {
		const std::string& logPath = CDBFCollectorConfig::GetInstance().GetEigenOutputFile();
		std::fstream fhLog( logPath,  std::fstream::out );	
        MKL_INT i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ )
				{
                        //printf( " (%6.2f,%6.2f)", a[i+j*lda].real, a[i+j*lda].imag );
						fhLog << std::fixed << std::setprecision(16) << a[i+j*lda].real << " " << a[i+j*lda].imag <<  "i," 
						;
				}
                fhLog<< std::endl;
        }
}


//void 
//CHGTEigenVectors::_CreateTransposed2dMatrix()
//{
//
//	int size = EIGEN_ROWS * EIGEN_COLS;
//	int idx = 0;
//	for(int i=0; i<EIGEN_ROWS; i++)
//		for(int j=0; j<EIGEN_COLS /*&& idx<size*/; j++) 
//		{
//			
//			m_inputMatrix2D[i][j] = m_inputMatrix[idx++];
//			if( i && j )
//				m_inputMatrix2DSUBARRAY[i-1][j-1] = m_inputMatrix2D[i][j];
//		}
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void 
CHGTEigenVectors::_CreateEigenVectors( float* eigenValues, MKL_Complex8 *eigenVectors)
{
	//intel transpose
	MKL_Complex8 alpha ={1,0};	

	MKL_Cimatcopy( 'C','T',EIGEN_ROWS, EIGEN_COLS,alpha,m_inputMatrix,EIGEN_ROWS,EIGEN_COLS);

	//call zheevd for eigen vectors
	int   info = LAPACKE_cheevd( LAPACK_COL_MAJOR, 'V', 'L', EIGEN_ROWS, m_inputMatrix, EIGEN_ROWS, eigenValues );
	
	//********transpose **********/
    memcpy( eigenVectors,m_inputMatrix, EIGEN_ROWS* EIGEN_ROWS  * sizeof(MKL_Complex8) );

	//Log values
	//_LogOutputCSV("");
}