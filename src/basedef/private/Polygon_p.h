#ifndef POLYGON_P_H
#define POLYGON_P_H

#include "BaseTypes.h"
#include "SystemDef.h"

#include "RectRegion.h"
#include "DyadCoordinate.h"

//STL
#include <cassert>

#include <vector>

namespace Magna{  
   namespace Core{
     
     template<
           typename _type
          ,   class _type_trait =  StaticTypeTrait<_type, sint32, StaticTypeTrait<_type, float, StaticTypeTrait<_type, double> > > 
          >
     class PolygonPolicy {
       __Constructor_Destructor protected:
        PolygonPolicy()
          :m_data( new std::vector<DyadCoordinate<_type> > ){
          COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
        }

        explicit PolygonPolicy( uint32 size )
          :m_data( new std::vector<DyadCoordinate<_type> >( size ) ){
          COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
        }

        explicit PolygonPolicy( const std::vector<DyadCoordinate<_type> >& coords )
          :m_data( new std::vector<DyadCoordinate<_type>>( coords ) ){
          COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
        }

        PolygonPolicy( const PolygonPolicy<_type>& polygon )
          :m_data( polygon.m_data ){
          COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
        }

        ~PolygonPolicy(){

        }

      __Highlight_Property protected:


      protected:
        PolygonPolicy<_type> & _translatedBy( const _type & dx, const _type& dy ){
          std::vector< DyadCoordinate<_type> >::iterator i = m_data->begin();
          for(; i != m_data->end(); ++i ){
            i->translatedByEach( dx, dy );
          }
          return *this;
        }


        bool _contains( const DyadCoordinate<_type>& coords_array) const{
          assert( !m_data.isNull() );
          bool ret = false;
          
          if( _isNormal() ){
            //check the first one
            DyadCoordinate<_type>::ImpreciseQuadrant quad_of_pre_one 
              = m_data->at( 0 ).translatesTo( coords_array ).getImpreciseQuadrant();
            uint8 quad_of_pre_int_value =  static_cast<uint8>( quad_of_pre_one & 0x03 );
            uint32 sum_shfit_radian = 0;

            if( quad_of_pre_one != DyadCoordinate<_type>::Origin ){
              std::vector<DyadCoordinate<_type> >::const_iterator pre_iter = m_data->begin() ;
              std::vector<DyadCoordinate<_type> >::const_iterator iter = m_data->begin() + 1 ;
              
              for(; iter != m_data->end(); ++iter, ++pre_iter ){
                DyadCoordinate<_type> & eachTranslatedCoord = iter->translatesTo( coords_array );
                DyadCoordinate<_type>::ImpreciseQuadrant quad_of_current = eachTranslatedCoord.getImpreciseQuadrant();        
                
                if(  quad_of_current == DyadCoordinate<_type>::Origin ){
                  ret = true;
                  break;
                }
                else{            
                  uint8 quad_of_int_value = static_cast<uint8>( quad_of_current & 0x03 );
                  if( quad_of_int_value == ((quad_of_pre_int_value + 1) & ( 0x03 )) ){
                    sum_shfit_radian += 1;
                  }
                  else if( quad_of_pre_int_value == ((quad_of_int_value + 1) & ( 0x03 ) )){
                    sum_shfit_radian -= 1;
                  }
                  else{
                    const double det_result = pre_iter->determinant( *iter );
                    if( Comparer<double>::isHigherThanZero( det_result ) ){
                      sum_shfit_radian += 2;
                    }
                    else if(Comparer<double>::isLowerThanZero( det_result ) ){
                      sum_shfit_radian -= 2;
                    }    
                    else{
                      ret = true;
                      break;
                    }
                  }
                  quad_of_pre_int_value = quad_of_int_value;
                }
              }//for
              
              if( sum_shfit_radian != 0 ){
                ret = true;
              }
            }//check first is origin
          }
          return ret;
        }

        void _puts( uint32 size, DyadCoordinate<_type> *coords_array ){
          assert( !m_data.isNull() );
          try{
            for( uint32 i = 0; i != size; ++i ){
              m_data->push_back( *(coords_array + i)  );
            }
          }
          catch( std::out_of_range exce ){
            abort();
          }
        }

        void _insertAt( uint32 index, const DyadCoordinate<_type>& coord ){
          assert( !m_data.isNull() );
          std::vector<DyadCoordinate<_type> >::iterator iter = m_data->begin() + index;
          if( iter < m_data->end() ){
            m_data->insert( iter, coord );
          }        
        }

        void _deleteAt( uint32 index ){
          assert( !m_data.isNull() );
          std::vector<DyadCoordinate<_type> >::iterator iter = m_data->begin() + index;
          if( iter < m_data->end() ){
            m_data->erase( iter );
          }    
        }

        bool _isNormal() const {
          assert( !m_data.isNull() );
          return (m_data->size() > 2);
        }

       RectRegion<_type> _getBoundingRectRegion() const{
         RectRegion<_type> rect;
         std::vector<DyadCoordinate<_type> >::const_iterator iter = m_data->begin();
         const DyadCoordinate<_type> & bottomRight= rect.getBottomRightCoord();
         const DyadCoordinate<_type> & topLeft = rect.getTopLeftCoord();
         for(; iter != m_data->end(); ++iter ){
           if( Comparer<_type>::isHigherThan( (*iter).getY(),  bottomRight.getY() ) ){
             rect.setBottomRightCoordY( (*iter).getY() );
            }
           if( Comparer<_type>::isHigherThan( (*iter).getX(),  bottomRight.getX() ) ){
             rect.setBottomRightCoordX( (*iter).getX() );
            }
           if( Comparer<_type>::isLowerThan( (*iter).getX(),  topLeft.getX() ) ){
             rect.setTopLeftCoordX( (*iter).getX() );
            }
           if( Comparer<_type>::isLowerThan( (*iter).getY(),  topLeft.getY() ) ){
             rect.setTopLeftCoordY( (*iter).getY() );
            }
          }    
         return rect;
       }
    
      __Data_Field private:
       SharedPtr <std::vector<DyadCoordinate<_type> > > m_data;
     };
     template class PolygonPolicy<float>;
     template class PolygonPolicy<double>;
     template class PolygonPolicy<sint32>;
   }//Core
}//Magna
#endif  /*  POLYGON_P_H  */