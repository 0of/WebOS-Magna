/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */
#ifndef GRADIENT_H
#define GRADIENT_H

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#include "render_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

#include "basedef/Color.h"

#include "DyadCoordinateMapper.h"

#include <list>

using namespace Magna;
using namespace Magna::Core;

namespace Magna{
   namespace Render{
     class FillBrush;

     /*!  \brief
         Define the gradient fill style.
      */
     /*!  \details
      *  
      *    Gradient is a kind of content fill style. Comparing with solid 
      *    color as the fill style,  It has stronger visual effect. UI may looks
      *    good if apply some gradient fill styles.
      *    
      *    Magna currently supports two gradient: linear and radial. 
      * 
      *    \author 
      *    \version   
      *    \date      
      */
     __Abstracted class RENDER_LIB_EXPORT Gradient{
       friend class FillBrush;
       __Definitions public:
         typedef std::pair< Color, float > GradientStop;

       __Constants public:
        enum GradientType{
          GradientType_Unknow = 0x00,
          GradientType_Linear = 0x01,
          GradientType_Radial = 0x02
        };
      __Constructor_Destructor protected:
        explicit Gradient( GradientType childType );
      __Constructor_Destructor public:
        virtual ~Gradient() = 0 ;

        public:
          void setColorAt( const Color& color, float at );
          void addStop( const GradientStop& stop );
          void clearStop();

        __Getter public:
          inline std::list<GradientStop>& getStops() {return m_stops;}
          inline GradientType getType() const{ return m_type; }

        protected:
          virtual String _toString( const IntegerDyadCoordinate& ) const = 0;

        __Data_Field protected:
          GradientType m_type;
          std::list<GradientStop> m_stops;
     };
   }//Render
}//Magna

#endif  /*  GRADIENT_H  */
