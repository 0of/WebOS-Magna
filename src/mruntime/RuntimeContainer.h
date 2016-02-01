#ifndef WEBKITVIEW_H
#define WEBKITVIEW_H

#include "mruntime_global.h"

#include <QWebView>
#include <QWebPage>
#include <QWebFrame>

#include "basedef/SpinMutex.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include "EventDispatcherNode.h"

namespace Magna{
  namespace Runtime{

    class MRUNTIME_EXPORT RuntimeContainer : public QObject{
      //Q_OBJECT    

    public:
      static RuntimeContainer & getRuntimeContainer() ;
    private:
      RuntimeContainer();

      static SpinMutex shared_Load_mutex;

    public:
      ~RuntimeContainer();


    public:
      void evalJavaScript( const QString& sc);
      void evalJavaScript( const String& sc);
      /*
      

      void evalJavaScriptRenderingWindow(  const assic_char* element_id, const std::string& content );

      void evalJavaScriptOpenNewWindow( const std::string& content );
      void evalJavaScriptSetWindowVisible( const std::string& id );
      void evalJavaScriptSetWindowHidden( const std::string& id );
      */
    public:
    
      void initContainer( );
      
      void loadDesktopPage();

      //nx the parameter would be a URL/URI
      void loadApplication( const String& path );
      
      inline QWebView *getWebView(){
        return m_webview;
      }

    private:
      void loadHTMLFrame();

    private:
      bool m_did_load;
      QWebView *m_webview;
      //main frame
      QWebFrame *m_mainFrame;
      EventDispatcherNode m_eventDispatcherNode;

    };

  }
}//namespace Magna

#endif  /*  WEBKITVIEW_H  */