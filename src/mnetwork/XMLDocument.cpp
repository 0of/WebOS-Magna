#include "XMLDocument.h"

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "basedef/AtomicInt.h"
using namespace Magna::Core;

#include "XMLNode_p.h"

namespace Magna{
  namespace Network{

    class XMLDocument::DocumentData{
      public:
        DocumentData();
        ~DocumentData();

      public:
        xmlDocPtr m_docPtr;
        XMLNode m_rootNode;
        AtomicInt m_invRefCount;
    };

    XMLDocument::DocumentData::DocumentData()
      :m_docPtr( Nullptr )
      ,m_invRefCount( 0 )
      ,m_rootNode() {

    }

    XMLDocument::DocumentData::~DocumentData(){

    }
    
    XMLDocument::XMLDocument()
      :m_data(){

    }

    XMLDocument::XMLDocument( const String& filename )
      :m_data( new DocumentData ){

      //read
      m_data->m_docPtr = xmlParseFile( filename.toString().c_str() );
      if( Nullptr != m_data->m_docPtr ){
        xmlNodePtr _root_node = xmlDocGetRootElement( m_data->m_docPtr );
        if( Nullptr != _root_node ){
          m_data->m_rootNode.m_data = new XMLNode::NodeData( _root_node );
        }
      }
    }

    XMLDocument::XMLDocument( const XMLDocument& doc)
      :m_data( doc.m_data ){
      if( m_data != Nullptr ){
        ++m_data->m_invRefCount;
      }
    }

    XMLDocument::~XMLDocument(){
      if( m_data != Nullptr ){
        if( m_data->m_invRefCount.read() > 0 ){
          --m_data->m_invRefCount;
        }
        else{
          xmlFreeDoc( m_data->m_docPtr );
        }
      }
    }

    XMLNode XMLDocument::getRootNode() const{
      return Nullptr != m_data ?
        m_data->m_rootNode : XMLNode();
    }

    void XMLDocument::readFromFile( const String& filename){
      if( !filename.empty() ){

        if( m_data != Nullptr ){
          if( m_data->m_invRefCount.read() > 0 ){
            --m_data->m_invRefCount ;

            m_data = new DocumentData;        
          } else{
            if( m_data->m_docPtr != Nullptr ){
              xmlFreeDoc( m_data->m_docPtr );

              m_data->m_docPtr = Nullptr;
            }        
          }
        } else{
          m_data = new DocumentData;
        }
        
        m_data->m_docPtr = xmlParseFile( filename.toString().c_str() );
        //init root node
        if( Nullptr != m_data->m_docPtr ){
          xmlNodePtr _root_node = xmlDocGetRootElement( m_data->m_docPtr );
          if( Nullptr != _root_node ){
            m_data->m_rootNode.m_data = new XMLNode::NodeData( _root_node );
          }
        }
      }
    }

    bool XMLDocument::isNull() const{
      bool _ret_is_null = !false;

      if( m_data != Nullptr ){

        if( m_data->m_docPtr != Nullptr ){
          _ret_is_null = false;
        }
      }

      return _ret_is_null;
    }


  }//namespace Network
}//namespace Magna