#include "ApplicationLoader.h"


#include <QLibrary>

#include <exception>
#include <regex>

namespace Magna{
  namespace Application{
    ApplicationLoader &ApplicationLoader::obtainLoader(){
      static ApplicationLoader _loader;
      return _loader;
    }

    ApplicationLoader::ApplicationLoader()
      :m_mutex(){

    }

    ApplicationLoader::~ApplicationLoader(){

    }

    ApplicationTaskBlock *ApplicationLoader::loadDesktopApplication( DesktopObject& _out_ ){
      typedef void(MAGNA_CDECL *app_entry)();
      typedef MagnaApplication*(MAGNA_CDECL *app_obtainer)();

      ApplicationTaskBlock * _ret_block = Nullptr;
      try{        
        QString _desktop_path( "sysdesktop" );
        QLibrary *_app = new QLibrary( _desktop_path );    
      
        app_entry _entry = reinterpret_cast<app_entry>(_app->resolve( "_magna_entry" ));

        if( _entry != Nullptr ){
          app_obtainer _obtainer = reinterpret_cast<app_obtainer>(_app->resolve( "_magna_obtain_app" ));
          if( _obtainer != Nullptr ){
            _ret_block = new ApplicationTaskBlock( _entry, _app  );
            _ret_block->run();

            MagnaApplication *_obtained_app = _obtainer();
            if( _obtainer != Nullptr  ){
              //assign the application
              _ret_block->assignRunningApplication( _obtained_app);

              //wrap desktop object
              DesktopObject::disp_new_wnd_run _disp_new_wnd_run 
                = reinterpret_cast<DesktopObject::disp_new_wnd_run>(
                _app->resolve( "_magna_desktop_disp_new_wnd_run" ));

              DesktopObject::disp_fin_wnd_run _disp_fin_wnd
                = reinterpret_cast<DesktopObject::disp_fin_wnd_run>(
                _app->resolve( "_magna_desktop_disp_finish_wnd" ));

              DesktopObject::disp_wnd_focus_changed _disp_focus_changed
                =  reinterpret_cast<DesktopObject::disp_wnd_focus_changed>(
                _app->resolve( "_magna_desktop_disp_wnd_focus_changed" ));


              if( _disp_new_wnd_run != Nullptr
                && _disp_fin_wnd != Nullptr){    
                _out_.init( _obtained_app, _disp_new_wnd_run
                  , _disp_fin_wnd, _disp_focus_changed );
              }
            }
            else{
              _app->unload();
              delete _ret_block;
              _ret_block = Nullptr;
              //throw
            }

          }

        }
      }

      catch( const std::exception& ex ){

      }    
      return _ret_block;
    }

    //  fun_seq
    //  check path
    //  resolve entry & obtainer
    //  generate block 
    //  
    ApplicationTaskBlock *ApplicationLoader::loads( const String& path ){
      typedef void(MAGNA_CDECL *app_entry)();
      typedef MagnaApplication*(MAGNA_CDECL *app_obtainer)();
      
      ApplicationTaskBlock * _ret_block = Nullptr;
      try{        
        if( [&]()->bool{
          std::wregex _app_regex ( L"(^//.|^/|^[a-zA-Z])?:?/.+(/$)*\.(dll|so)?" );
          std::wsregex_iterator _reg_iter ( path.begin(), path.end(), _app_regex );
#ifdef _MSC_VER
          return (_reg_iter != std::wsregex_iterator()) && QLibrary::isLibrary( QString::fromUtf16( reinterpret_cast<const ushort *>(path.c_str()), path.size() ) );    
#else
          return (_reg_iter != std::wsregex_iterator()) && QLibrary::isLibrary( QString::fromStdWString( path ) );      
#endif                  
        }() ){
        
#ifdef _MSC_VER
          QLibrary *_app = new QLibrary( QString::fromUtf16( reinterpret_cast<const ushort *>(path.c_str()), path.size() ) );    
#else
          QLibrary *_app = new QLibrary( QString::fromStdWString( path ) );          
#endif
          
          app_entry _entry = reinterpret_cast<app_entry>(_app->resolve( "_magna_entry" ));
          
          //  ###Unsolved Problem
          //  First I create a thread just within the main function scope
          //  and then run the app obtainer
          //  which throw a Nullptr pointer exception
          //  and i debug the created thread found that
          //  the thread data is corrupted
          //  idk why this happened so just recorded
          if( _entry != Nullptr ){
            app_obtainer _obtainer = reinterpret_cast<app_obtainer>(_app->resolve( "_magna_obtain_app" ));
            if( _obtainer != Nullptr ){
              _ret_block = new ApplicationTaskBlock( _entry, _app  );
              _ret_block->run();

              //Thread::sleep( 1000 );
              //obtain the application object from application instance
              MagnaApplication *_obtained_app = _obtainer();
              if( _obtainer != Nullptr  ){
                //assign the application
                _ret_block->assignRunningApplication( _obtained_app);
              }
              else{
                //
                //result fatal error
                //###
                //### 
                //when can get into the entry
                //but with no application instance
                //that would be caused by some fatal error
                //the details would be shown in Test case           
                //free the block
                _app->unload();
                delete _ret_block;
                _ret_block = Nullptr;
                //throw
              }

            }

          }
          
        }
      }
      catch( const std::exception& ex ){

      }    
      return _ret_block;
    }

    void ApplicationLoader::loadApplicationExpInfo( const String& _app_path, String &_out_ap_name, String &_out_icon_path ){
      typedef String (*_magna_obtain_app_name)();
      typedef String (*_magna_obtain_app_icon_path)();

      m_mutex.acquires();
      QLibrary _lib(QString::fromUtf16( reinterpret_cast<const ushort *>(_app_path.c_str()), _app_path.size() ) );  
      if( _lib.load() ){
        _magna_obtain_app_name _get_name = reinterpret_cast<_magna_obtain_app_name>(_lib.resolve( "_magna_obtain_app_name" ));
        if(_get_name != Nullptr ){
          _out_ap_name = _get_name();
        }
        _magna_obtain_app_icon_path _icon_path = reinterpret_cast<_magna_obtain_app_name>(_lib.resolve( "_magna_obtain_app_icon_path" ));
        if( _icon_path != Nullptr ){
          _out_icon_path = _icon_path();
        }
        _lib.unload();
      }
      m_mutex.releases();
    }

  }//namespace Application
}//namespace Magna
