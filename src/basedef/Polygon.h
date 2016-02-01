/*
  * This file is part of core library of Magna framework
  * 
  * Copyright (c) 2013 by Magnus
  */
#ifndef POLYGON_H
#define POLYGON_H

#include "basedef_lib.h"

#include "Polygon_p.h"

namespace Magna{  
   namespace Core{
     /***
      *  Polygon will be improved later and will bring iterators
      *  which is similar to manipulate the container. 
      **/
    /*!  \brief
        A Polygon. 多边形
      */
    /*!  
      *    A polygon can contain a convex or concave polygon.
      *
      *    A polygon can be initialized by given the point size or a
      *    set of points. #Polygon( const std::vector<DyadCoordinate<T> >& )
      *
      *    Just like manipulating the container, can use insertAt(), deleteAt(), append()
      *    to add or remove a point.Or you can use operator<<() to append coordinates.
      *
      *    Besides, calling puts() can append a series of points. 
      *    Or setFrom() sets several points in a row.
      *
      *    What's more, you can get the bounding rectangle of the polygon by calling  getBoundingRectRegion()
      *  
      *    If you want to check whether a point stands inside the polygon
      *    call contains() .And the algorithm we used is kinda deem the check point as origin
      *    and shift the polygon to the check point. Traverse all the points of the polygon and  
      *    accumulate the quadrants. Then we would throw a result according to the final quadrant sum.  
      * 
      *    \tparam T  can be in float, double, sint32 for the x and y type
      *    \attention  the T must be in float, double or sint32
      *          otherwise the compiler will throw a error.
      *
      *   \author  Magnus
      *   \version   1.0.0.0
      *  \date    2013/1/14
      */
     template<typename T, typename Policy = PolygonPolicy>
     class BASEDEF_LIB_EXPORT Polygon : Policy{
      __Constructor_Destructor public:
        //!  Default constructor
        Polygon() : Policy(){}
        //!  Constructor with vertexes size 
        explicit Polygon( uint32 size )
          :Policy( size ){

        }
        //!  Constructor with a vector of coordinates
        explicit Polygon( const std::vector<DyadCoordinate<T> >& coords )
          :Policy( coords ){

        }
        //!  Copy constructor
        /*!  
          *    Implicit copy    
          */
        Polygon( const Polygon<T,Policy>& polygon )
          :Policy( polygon ){

        }
        //!  Destructor
        ~Polygon(){

        }

      public:
        //!  Insert a coordinate 
        /*!  
          *    \param index if index is out of the range this function will do nothing
          *    \param coord insert coordinate
          */
        void insertAt( uint32 index, const DyadCoordinate<T>& coord ){
          _insertAt( index , coord );
        }
        //!  Delete a coordinate
        /*!  
          *    \param index if index is out of the range this function will do nothing   
          */
        void deleteAt( uint32 index ){
          _deleteAt( index );
        }
        //!  append a series of coordinates
        /*!  
          *    \throw out_of_range exception
          *    \param size shall be equal to the array size
          *    \param coords_array a pointer to #DyadCoordinate<T> and its size shall be match to size
          *      otherwise it may throw a fatal exception.
          *    \attention  the size of coords_array must be the parameter size
          */
        void puts( uint32 size, DyadCoordinate<T> *coords_array ){
          _puts( size, coords_array );
        }
        //!  append a coordinate
        /*!  
          *    \sa #operator+= #operator<<    
          */
        void append( const DyadCoordinate<T>& coord ){
          m_data->push_back( coord );
        }

      __Getter public:
        //!  Get the bounding rectangle of the polygon
        MAGNA_NOINLINE RectRegion<T> getBoundingRectRegion() const{
          return _getBoundingRectRegion();
        }
        //!  Get the vertexes size of the polygon
        inline uint32 getSize() const{
          return m_data->size();
        }
        
        //!  Get the vertex with index
        /*!  
          *    \throw out_of_range exception   
          *    \param index shall be lower than getSize() and higher than zero
          *    \return a const reference to the coordinate 
          */
        const DyadCoordinate<T>& getAt( uint32 index ){
          return m_data->at( index );
        }

      __Setter public:
        //!  Replace the coordinate with index
        inline void setAt( uint32 index, const DyadCoordinate<T>& coord ){
          if( index < m_data->size() ){
            m_data->at( index ) = coord;
          }      
        }
        //!  Set an array of coordinates.
        /*!  
          *     these coordinates will replace those ranging from [start_index,end_index)
          *     included the start index excluded the end index.
          *    \throw out_of_range exception   
          *    \param start_index the start index (included)
          *    \param end_index the end(excluded)
          *    \param coords_array the size of it shall be matched the end_index - start_index
          *    otherwise will throw an fatal exception.
          *    \sa setAt
          */
        void setFrom( uint32 start_index, uint32 end_index, DyadCoordinate<T> *coords_array ){
          try{
            if( start_index < end_index 
              && end_index < m_data->size() ){
              for( sint32 i = 0; i != (end_index - start_index); ++i ){
                m_data->at( start_index + i ) = *coord;
              }
            }
          }
          catch( const std::out_of_range& exce ){
            abort();
          }      
        }

      __By_Methods public:
        //!  The whole polygon is translated by dx & dy
        Polygon<T,Policy> & translatedBy( const T & dx, const T& dy ){
          Policy::_translatedBy( dx, dy );
          return *this;
        }

      __To_Methods public:
        //std::string toString();
        
        //!  Get a translated polygon with all the vertexes have been translated by dx & dy
        Polygon<T,Policy>  translatesTo( const T & dx, const T& dy ){
          Polygon<T,Policy> ret( *this );
          ret.translatedBy( dx, dy );
          return ret;
        }

      __Checker public:
        //!  Check whether a coordinate is inside the polygon
        /*!  
         *    The algorithm we used is kinda deem the check point as origin
         *    and shift the polygon to the check point. Traverse all the points of the polygon and  
         *    accumulate the quadrants. Then we would throw a result according to the final quadrant sum. 
         *
         *    \param coord check coordinate 
         *    \return true if contains otherwise false
         */
        MAGNA_NOINLINE bool contains( const DyadCoordinate<T>& coord ){
          return _contains( coord );
        }

      __Overloaded_Methods public:
        //!  Assign operator
        /*!  
          *    Implicit assign    
          */
        Polygon<T,Policy>& operator = ( const Polygon<T,Policy>& coords ){
          m_data = coord.m_data;
          return *this;
        }
        //!  append a coordinate
        /*!  
          *    \sa append    
          */
        Polygon<T,Policy>& operator += ( const DyadCoordinate<T>& coord ){
          append( coord );
          return *this;
        }
        //!  Append coordinates of another polygon
        Polygon<T,Policy>& operator += ( const Polygon<T,Policy>& coords ){
          *m_data += *coords.m_data;
        }
        //!  Get a new polygon with appended coordinates
        Polygon<T,Policy> operator + ( const Polygon<T,Policy>& coords ){
          Polygon<T,Policy> ret( *this );
          ret += coords;
          return ret;
        }
        //!  Get a new polygon with appended coordinate
        Polygon<T,Policy> operator + ( const DyadCoordinate<T>& coord ){
          Polygon<T,Policy> ret( *this );
          ret += coord;
          return ret;
        }
        //!  Element access 
        /*!  
          *    \throw out_of_range exception   
          *    \param index shall be lower than getSize() and higher than zero
          *    \return a const reference to the coordinate 
          *    \sa getAt
          */
        const DyadCoordinate<T>& operator [] ( uint32 index ){
          return m_data->at( index );
        }
        
        //!  Check two polygons are equal
        bool operator == ( const Polygon<T,Policy>& coords ){
          return *m_data == *(coords.m_data);
        }
        //!  Check two polygons are not equal
        bool operator != ( const Polygon<T,Policy>& coords ){
          return *m_data != *(coords.m_data);
        }
        
        //!  append a coordinate
        /*!  
          *    \sa append , #operator+=
          */
        Polygon<T,Policy>& operator << ( const DyadCoordinate<T>& coord ){
          append( coord );
          return *this;
        }
        //!  append a coordinates of another polygon
        /*!  
          *    \sa append , #operator+=
          */
        Polygon<T,Policy>& operator << ( const Polygon<T,Policy>& coords ){
          return operator +=( coords );  
        }
     };

  //   typedef Polygon<sint32> DigitPolygon ;
  //   typedef Polygon<float> FloatPolygon ;
  //   typedef Polygon<double> RealPolygon ;
   }//Core
}//Magna
#endif  /*  POLYGON_H  */