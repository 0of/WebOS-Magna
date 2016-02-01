#include "XMLNode.h"

#include <map>
#include <codecvt>

#include "libxml/parser.h"
#include "libxml/tree.h"

#include "basedef/AtomicInt.h"
using namespace Magna::Core;

#include "XMLNode_p.h"

namespace Magna{
  namespace Network{

    XMLNode::NodeData::NodeData()
      :m_node( Nullptr )
      ,m_invRefCount( 0 )
      ,m_name()
      ,m_content()
      ,m_attributes()
      ,m_childNodes(){

    }

    XMLNode::NodeData::NodeData( xmlNodePtr node_ptr )
      :m_node( node_ptr )
      ,m_invRefCount( 0 )
      ,m_name()
      ,m_content()
      ,m_attributes()
      ,m_childNodes(){
      if( Nullptr != node_ptr ){
        std::wstring_convert<std::codecvt_utf8<unicode_char> > _convertor;
        if( Nullptr != node_ptr->name ){
          m_name = _convertor.from_bytes( reinterpret_cast< const assic_char *>( node_ptr->name ) ) ;
        }
        if( Nullptr != node_ptr->content ){
          m_content = _convertor.from_bytes( reinterpret_cast< const assic_char *>( node_ptr->content ) );
        }
        
        //init attributes
        for( xmlAttrPtr _each_attr = node_ptr->properties; Nullptr != _each_attr ; _each_attr = _each_attr->next ){
          auto *_each_prop_val = xmlGetProp( node_ptr, _each_attr->name );

          if( Nullptr != _each_attr->name && Nullptr != _each_prop_val ){
            m_attributes.emplace( std::make_pair( _convertor.from_bytes( reinterpret_cast< const assic_char *>( _each_attr->name ) ) 
              ,  _convertor.from_bytes( reinterpret_cast< const assic_char *>( _each_prop_val ) ) ) );
          }
        }
        
        //init all the child nodes
        for( auto _each_child = node_ptr->children; Nullptr != _each_child; _each_child = _each_child->next  ){
          XMLNode _child_node;
          _child_node.m_data = new NodeData( _each_child );

          m_childNodes.push_back( _child_node );
        }
      }
    }

    XMLNode::NodeData::~NodeData(){

    }

    XMLNode::NodeData * XMLNode::NodeData::detachingClone(){
      --m_invRefCount;

      NodeData *_data = new NodeData;

      //copy
      _data->m_content = m_content;
      _data->m_name = m_name;
      _data->m_attributes = m_attributes;
      _data->m_childNodes = m_childNodes;

      _data->m_node = xmlCopyNode( m_node,  2 );  
  
      return _data;
    }


    XMLNode::XMLNode()
      :m_data( Nullptr ){

    }

    XMLNode::XMLNode( const String& name,const String& content )
      :m_data( new NodeData ){

      m_data->m_node = xmlNewNode( Nullptr, reinterpret_cast<const xmlChar *>(name.toString().c_str()) );
      if( Nullptr != m_data->m_node ){
        xmlNodeSetContent( m_data->m_node, reinterpret_cast<const xmlChar *>( content.toString().c_str() ) );
        m_data->m_name = name;
        m_data->m_content = content;
      }
    }

    XMLNode::XMLNode( const XMLNode& node)
      :m_data( node.m_data ){

      if( Nullptr != m_data ){
        ++m_data->m_invRefCount;
      }

    }

    XMLNode:: ~XMLNode(){
      if( Nullptr != m_data ){
        if( m_data->m_invRefCount.read() > 0 ){
          --m_data->m_invRefCount;
        } else{
          if( Nullptr != m_data->m_node ){
            xmlFreeNode( m_data->m_node );
          }        
          delete m_data;
        }
      }
    }

    void XMLNode::setTagName( const String& name){
      if( Nullptr != m_data ){
        //if( m_data->m_invRefCount.read() > 0 ){
        //  m_data = m_data->detachingClone();
        //}
        xmlNodeSetName( m_data->m_node, reinterpret_cast<const xmlChar *>(name.toString().c_str()) );  
      } else{
        m_data = new NodeData;
        m_data->m_node = xmlNewNode( Nullptr, reinterpret_cast<const xmlChar *>(name.toString().c_str()) );
      }
    }

    void XMLNode::setContent( const String& content){
      if( Nullptr != m_data  && Nullptr != m_data->m_node ){

        //if( m_data->m_invRefCount.read() > 0 ){
        //  m_data = m_data->detachingClone();
        //}
        
        xmlNodeSetContent( m_data->m_node, reinterpret_cast<const xmlChar *>( content.toString().c_str() ) );
        m_data->m_content = content;
      }
    }

    String XMLNode::getTagName() const{
      return Nullptr != m_data ? 
        m_data->m_content : String();
    }

    String XMLNode::getAttributeBy( const String& name) const{
      String _ret_value;
      if( Nullptr != m_data ){
        auto _found = m_data->m_attributes.find( name );
        if( m_data->m_attributes.end() != _found ){
          _ret_value = _found->second;
        }
      }
      return _ret_value;
    }

    XMLAttributes XMLNode::getAttributes() const{
      return Nullptr != m_data ?
        m_data->m_attributes : XMLAttributes();
    }

    bool XMLNode::hasAttribute( const String& name) const{
      return Nullptr != m_data ? 
        m_data->m_attributes.end() != m_data->m_attributes.find( name ) : false;
    }

    XMLNode& XMLNode::addAttribute( const String& name, const String& val ){
      if( Nullptr != m_data && Nullptr != m_data->m_node ){
        //if( m_data->m_invRefCount.read() > 0 ){
        //  m_data = m_data->detachingClone();
        //}

        auto _found = m_data->m_attributes.find( name );
        if( m_data->m_attributes.end() != _found ){          
          xmlSetProp( m_data->m_node
            , reinterpret_cast<const xmlChar *>(name.toString().c_str())
            , reinterpret_cast<const xmlChar *>(val.toString().c_str()) );
          _found->second = val;

        } else{          
          xmlNewProp( m_data->m_node
            , reinterpret_cast<const xmlChar *>(name.toString().c_str())
            , reinterpret_cast<const xmlChar *>(val.toString().c_str()) );

          m_data->m_attributes.emplace( std::pair<String,String>( name, val ) );
        }
      }
      return *this;
    }

    XMLNode::XMLNodeIterator XMLNode::getChildBegin() {
      XMLNode::XMLNodeIterator _iter;
      if( Nullptr != m_data ){    
        _iter.m_nodepointer = m_data->m_childNodes.data();
      }
      return _iter;
    }

    XMLNode::XMLNodeIterator XMLNode::getChildEnd() {
      XMLNode::XMLNodeIterator _iter;
      if( Nullptr != m_data ){    
        auto &_child_nodes = m_data->m_childNodes;
        _iter.m_nodepointer = (_child_nodes.data() + _child_nodes.size());
      }
      return _iter;
    }

    XMLNode::Const_XMLNodeIterator XMLNode::getChildCBegin() const{
      XMLNode::Const_XMLNodeIterator _iter;
      if( Nullptr != m_data ){    
        _iter.m_nodepointer =  m_data->m_childNodes.data();
      }
      return _iter;
    }

    XMLNode::Const_XMLNodeIterator XMLNode::getChildCEnd() const{
      XMLNode::Const_XMLNodeIterator _iter;
      if( Nullptr != m_data ){    
        auto &_child_nodes = m_data->m_childNodes;
        _iter.m_nodepointer = (_child_nodes.data() + _child_nodes.size());
      }
      return _iter;
    }

    XMLNode &XMLNode::appendChild( XMLNode& node){
      if( Nullptr != m_data && Nullptr != node.m_data 
        && m_data != node.m_data  ){  //cannot be itself
        if( Nullptr != m_data->m_node && Nullptr != node.m_data->m_node ){
          auto _appended_child = xmlAddChild( m_data->m_node, node.m_data->m_node );
          if( _appended_child == node.m_data->m_node ){
            m_data->m_childNodes.push_back( node );
          }
        }
      }
      return *this;
    }

    void XMLNode::removeChild( XMLNodeIterator iter ){
      if( Nullptr != m_data && Nullptr != iter.m_nodepointer ){
        if( Nullptr != iter->m_data ){
          //check 
          auto *_begin_pointer = m_data->m_childNodes.data();
          auto _offset = iter.m_nodepointer - _begin_pointer;
          if( _offset >= 0 
            && _offset < m_data->m_childNodes.size() ){
            xmlUnlinkNode(  iter->m_data->m_node );

            auto _nodes_iter = m_data->m_childNodes.begin() + _offset ;
            m_data->m_childNodes.erase( _nodes_iter );
          }            
        }
      }
    }

    void XMLNode::insertChild( XMLNodeIterator iter, XMLNode& node){
      if( Nullptr != m_data && Nullptr != iter.m_nodepointer ){
        if( Nullptr != iter->m_data && Nullptr != iter->m_data->m_node
          && Nullptr != node.m_data && Nullptr != node.m_data->m_node ){
          //check 
          auto &_child_nodes = m_data->m_childNodes;
          auto *_begin_pointer = _child_nodes.data();
          auto _offset = iter.m_nodepointer - _begin_pointer;
          if( _offset >= 0 && _offset < _child_nodes.size() ){
            auto *_inserted_child = xmlAddNextSibling( iter->m_data->m_node, node.m_data->m_node );
            if( _inserted_child == node.m_data->m_node ){
              _child_nodes.insert( _child_nodes.begin() + _offset , node );
            }
          }            
        }
      }
    }

    XMLNode XMLNode::clone(){
      XMLNode _ret_node;
      if( Nullptr != m_data ){

        NodeData *_data = new NodeData;

        //copy
        _data->m_content = m_data->m_content;
        _data->m_name = m_data->m_name;
        _data->m_attributes = m_data->m_attributes;
        _data->m_childNodes = m_data->m_childNodes;

        _data->m_node = xmlCopyNode( m_data->m_node,  2 );  

        _ret_node.m_data = _data;
      }

      return _ret_node;
    }


  }//namespace Network
}//namespace Magna