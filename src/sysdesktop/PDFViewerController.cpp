#include "PDFViewerController.h"

#include <string>
#include "windows.h"

#include "basegui/Controller_p.h"
#include "basegui/ControllerImplementor.h"
#include "basegui/ScrollableController_p.h"

#include "glue_img/Image.h"
using namespace Magna::Glue;

//poppler
#include "poppler-document.h"
#include "poppler-page.h"
#include "poppler-page-renderer.h"
#include "poppler-image.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class Com{
      public:
        static std::string WChar2Ansi(const String& str )  
        {  
          int nLen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);  
          if (nLen<= 0) return std::string("");  
          char* pszDst = new char[nLen];  
          if (NULL == pszDst) return std::string("");  
          WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pszDst, nLen, NULL, NULL);  
          pszDst[nLen -1] = 0;  
          std::string strTemp(pszDst);  
          delete [] pszDst;  
          return strTemp;  
        }  
      };
      

      class PDFViewerControllerImplementor : public ControllerImplementor{
        public:
          PDFViewerControllerImplementor(PDFViewerController &);
          virtual ~PDFViewerControllerImplementor();

          virtual void rendering( RenderingEventArgs& eventArgs );

        public:
          void _loadDocument( const std::string& path );
          void _clearDocument();

          poppler::document *m_document;
          std::vector<Image> m_imageSequence;
          std::vector<poppler::page *> m_pages;

          poppler::page_renderer m_render;
          uint32 m_pageNum;
          uint32 m_currentPageIndex;

          //offset
          IntegerDyadCoordinate m_offset;
          uint32 m_verticalSpacing;

          IntegerSize m_eachPageSize;

          PDFViewerController &m_binding;
      };

      void PDFViewerControllerImplementor::_clearDocument(){
        if( m_document != Nullptr ){
          delete m_document;      
        }
        for(auto _iter = m_pages.begin(); _iter != m_pages.end(); ++_iter ){
          if( (*_iter) != Nullptr ){
            delete (*_iter);
          }
        }
        m_pages.clear();
        m_imageSequence.clear();
      }

      void PDFViewerControllerImplementor::_loadDocument( const std::string& path ){

        if( !path.empty() ){

          m_document = poppler::document::load_from_file( path );
          
          if( m_document != Nullptr ){
            m_pageNum = m_document->pages();

            m_pages = std::vector<poppler::page *>( m_pageNum );
            m_imageSequence = std::vector<Image>( m_pageNum );

            uint32 _page_limits = m_pageNum ;
            
            for( auto i = 0; i != _page_limits; ++i ){
              auto *_each_page = m_document->create_page( i );          
              m_pages.at( i ) = _each_page;
              if( _each_page != Nullptr ){
                bool can_render_ = m_render.can_render();

                const auto&_rect = _each_page->page_rect(); 

                auto &_poppler_img = m_render.render_page( _each_page, 200, 180, 0, 0);

                Image each;
                if( _poppler_img.is_valid() ){
                  Image::ImageFormat format = Image::ImageFormat_RGB24Bits;

                  if( _poppler_img.format() == poppler::image::format_argb32 ){
                    format = Image::ImageFormat_ARGB32Bits;
                  }

                  each = Image( reinterpret_cast<const byte *>(_poppler_img.const_data())
                    , static_cast<uint32>(_poppler_img.width())
                    , static_cast<uint32>(_poppler_img.height())
                    , format );

                  each.save( L"./~tem.png");
                  each = Image( L"./~tem.png" );

                  each.scale( m_eachPageSize );
                  m_imageSequence.at( i ) = each;        
                }
              }//load each page
            }
            //calculate the scroll size
            IntegerSize _scroll_size ( m_eachPageSize.getWidth()
              , (m_eachPageSize.getHeight() + m_verticalSpacing) * m_pageNum + m_verticalSpacing );
            m_binding.setScrollSize( _scroll_size );  
          }

        }//path not empty
      }

      void PDFViewerControllerImplementor::rendering( RenderingEventArgs& eventArgs ){
        if( eventArgs.isAccepted() ){
          auto *_2d_manager = eventArgs.getRenderManager2D();
          if( _2d_manager != Nullptr ){
            Canvas2DDrawer _drawer;
            if( _2d_manager->retrieveDrawer( _drawer ) != false ){
              const auto & _rect = eventArgs.getRenderingRectRegion();

              for( auto i = 0; i != m_pageNum; ++i ){
                uint32 _top = i * (m_eachPageSize.getHeight() + m_verticalSpacing ) + m_offset.getY();
                _drawer.drawImage( IntegerDyadCoordinate(m_offset.getX(), _top) , m_imageSequence.at( i ) );
              }

            /*
              if( m_currentPageIndex == 0 && !m_imageSequence.empty() ){
                _drawer.drawImage( m_offset, m_imageSequence.at( 0 ) );
              }
              else{
                //calculate the top
                if( m_currentPageIndex < m_imageSequence.size() ){
                  uint32 _top = m_currentPageIndex * (m_eachPageSize.getHeight() + m_verticalSpacing ) + m_offset.getY();

                  _drawer.drawImage( IntegerDyadCoordinate(m_offset.getX(), _top) , m_imageSequence.at( m_currentPageIndex ) );
                }            
                //_rect.getTopLeftCoord().getY()

              }
              */
              _2d_manager->pullbackDrawer( _drawer );
            }
          }
        }
      }

      PDFViewerControllerImplementor::PDFViewerControllerImplementor( PDFViewerController & binding )
        :ControllerImplementor()
        ,m_document( Nullptr )
        ,m_imageSequence()
        ,m_pages()
        ,m_render()
        ,m_pageNum(0)
        ,m_currentPageIndex(0)
        ,m_offset( 10, 10 )
        ,m_verticalSpacing( 10 )
        ,m_eachPageSize( 1000, 800 )
        ,m_binding( binding ){

      }

      PDFViewerControllerImplementor::~PDFViewerControllerImplementor(){
        _clearDocument();
      }


      PDFViewerController::PDFViewerController()
        :ScrollableController(){

        if( !m_root.isNull() ){
          PDFViewerControllerImplementor *impl = new PDFViewerControllerImplementor( *this );
          m_root->_impl_init( impl );

          //default size
          //m_sroot->m_scrollSize = IntegerSize( 400, 320 ) ;
          m_root->_size_set( IntegerSize( 800, 570 ) );
        }

      }

      PDFViewerController:: PDFViewerController( const String& path)
        :ScrollableController(){

        if( !m_root.isNull() ){
          PDFViewerControllerImplementor *impl = new PDFViewerControllerImplementor( *this );
          impl->_loadDocument( Com::WChar2Ansi(path) );
          m_root->_impl_init( impl );

          //default size
          //m_sroot->m_scrollSize = IntegerSize( 400, 320 ) ;
          m_root->_size_set( IntegerSize( 800, 570 ) );
        }
      }

      PDFViewerController:: ~PDFViewerController(){

      }

      void PDFViewerController::loadPDFDocument( const String& str){
        auto & _path = Com::WChar2Ansi(str);

        //obtain impl
        if( !m_root.isNull() ){
          auto &_impl = m_root->_impl_get();
          auto *_impl_ = _impl.operator->();

          if( _impl_ != Nullptr ){
            PDFViewerControllerImplementor *_pdf_impl_ = 
              reinterpret_cast<PDFViewerControllerImplementor *>( _impl_ );

            _pdf_impl_->_clearDocument();
            _pdf_impl_->_loadDocument( _path );
          }
        }

      }

      void PDFViewerController::jumpToPageAt( uint32 page){

        if( !m_root.isNull() ){
          auto &_impl = m_root->_impl_get();
          auto *_impl_ = _impl.operator->();

          if( _impl_ != Nullptr ){
            PDFViewerControllerImplementor *_pdf_impl_ = 
              reinterpret_cast<PDFViewerControllerImplementor *>( _impl_ );

            if( _pdf_impl_->m_document != Nullptr && page < _pdf_impl_->m_pageNum ){
              _pdf_impl_->m_currentPageIndex = page;

              //page
              auto *_page = _pdf_impl_->m_pages.at( page );
              if( _page == Nullptr ){
                _page = _pdf_impl_->m_document->create_page( page );

                _pdf_impl_->m_pages.at( page) = _page;

                //render image
                if( _page != Nullptr ){
                  auto &_poppler_img = _pdf_impl_->m_render.render_page( _page );

                  Image each;
                  if( _poppler_img.is_valid() ){
                    Image::ImageFormat format = Image::ImageFormat_RGB24Bits;

                    if( _poppler_img.format() == poppler::image::format_argb32 ){
                      format = Image::ImageFormat_ARGB32Bits;
                    }

                    each = Image( reinterpret_cast<const byte *>(_poppler_img.const_data())
                      , static_cast<uint32>(_poppler_img.width())
                      , static_cast<uint32>(_poppler_img.height())
                      , format );
                  }
                }
              }

            }
          }
        }

      }

      uint32 PDFViewerController::getPageNumbers() const{
        uint32 _page_num = 0;
        if( !m_root.isNull() ){
          auto &_impl = m_root->_impl_get();
          auto *_impl_ = _impl.operator->();

          if( _impl_ != Nullptr ){
            PDFViewerControllerImplementor *_pdf_impl_ = 
              reinterpret_cast<PDFViewerControllerImplementor *>( _impl_ );

            _page_num = _pdf_impl_->m_pageNum;
          }
        }
        return _page_num;
      }

    }
  }
}