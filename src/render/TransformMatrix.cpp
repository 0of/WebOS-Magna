#include "TransformMatrix.h"

#include <cstring>

namespace Magna{
  namespace Render{
    TransformMatrix::TransformMatrix(){
      ::memset( m_matrix, 0, sizeof( float ) * 6 );
      m_matrix[0] = 1.0;
      
    }

    TransformMatrix::TransformMatrix(float m11, float m12, float m13, float m21, float m22, float m23 ){
      ::memcpy( &m_matrix, &m11, sizeof( float ) * 6 );
    }

    TransformMatrix::TransformMatrix( const TransformMatrix& mat ){
      ::memcpy( &m_matrix, &(mat.m_matrix), sizeof( float ) * 6 );
    }

    TransformMatrix::~TransformMatrix(){

    }

    void TransformMatrix::rotate( float radian ){

    }
    void TransformMatrix::shear( float xShear, float yShear ){
      m_matrix[1] = xShear;
      //m_matrix[]
    }
  //  void scale( float xScale, float yScale );
  //  void translate( float dx, float dy);
  }//namespace Render
}//namespace Magna

