#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H

#include "render_lib.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"

namespace Magna{
  namespace Render{
    
    class RENDER_LIB_EXPORT TransformMatrix{
      __Constants public:
        //enum RotateX
      __Constructor_Destructor public:
        TransformMatrix();
        explicit TransformMatrix(float m11, float m12, float m13, float m21, float m22, float m23 );
        TransformMatrix( const TransformMatrix& mat );
        ~TransformMatrix();

      __Setter public:


      public:
        void rotate( float radian );
        void shear( float xShear, float yShear );
        void scale( float xScale, float yScale );
        void translate( float dx, float dy);

        TransformMatrix & det( const TransformMatrix& mat );

      __Overloaded_Methods public:
        TransformMatrix& operator = ( const TransformMatrix& mat ){ return *this; }

        bool operator == ( const TransformMatrix& mat );
        bool operator != ( const TransformMatrix& mat );

      __Data_Field private:
        float m_matrix[ 6 ];

    };
  }//namespace Render
}//namespace Magna

#endif  /*  TRANSFORMMATRIX_H  */


