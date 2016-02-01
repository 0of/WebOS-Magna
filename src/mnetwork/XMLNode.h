#ifndef XMLNODE_H
#define XMLNODE_H

#include <vector>
#include <map>

#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace Network{
    
    typedef std::map<String, String> XMLAttributes;

    class XMLNode{
      friend class XMLDocument;

      typedef XMLNode * XMLNodePointer;
      typedef const XMLNode * ConstXMLNodePointer;

      typedef XMLNode & XMLNodeRef;
      typedef const XMLNode & ConstXMLNodeRef;

      __Constructor_Destructor public:
        XMLNode();
        explicit XMLNode( const String& name,const String& content );
        XMLNode( const XMLNode& );
        virtual ~XMLNode();

      public:
        void setTagName( const String& );
        void setContent( const String& );

        String getTagName() const;
        String getAttributeBy( const String& ) const;

        XMLAttributes getAttributes() const;

        bool hasAttribute( const String& ) const;

        XMLNode& addAttribute( const String& , const String& val );

        class XMLNodeIterator{
          friend class XMLNode;

          XMLNodePointer m_nodepointer;

          public:
            XMLNodeIterator() 
              :m_nodepointer( Nullptr ){}
            XMLNodeIterator( const XMLNodeIterator& i)
              :m_nodepointer( i.m_nodepointer ){}
            ~XMLNodeIterator(){}

          public:
            inline XMLNodeRef operator *(){
              return *m_nodepointer;
            }

            inline ConstXMLNodeRef operator *() const{
              return *m_nodepointer;
            }

            inline XMLNodeIterator & operator ++(){
              ++m_nodepointer;
              return *this;
            }

            XMLNodeIterator & operator --(){
              --m_nodepointer;
              return *this;
            }

            XMLNodePointer operator ->(){
              return m_nodepointer;
            }
        };

        class Const_XMLNodeIterator{
          friend class XMLNode;

          ConstXMLNodePointer m_nodepointer;

        public:
          Const_XMLNodeIterator()
            :m_nodepointer( Nullptr ){}
          Const_XMLNodeIterator( const Const_XMLNodeIterator& i)
            :m_nodepointer( i.m_nodepointer ){}
          ~Const_XMLNodeIterator(){}

        public:
          ConstXMLNodeRef operator *() const{
            return *m_nodepointer;
          }

          Const_XMLNodeIterator & operator ++(){
            ++m_nodepointer;
            return *this;
          }

          Const_XMLNodeIterator & operator --(){
            ++m_nodepointer;
            return *this;
          }

          ConstXMLNodePointer operator ->() const{
            return m_nodepointer;
          }
        };

      public:
        XMLNodeIterator getChildBegin() ;
        XMLNodeIterator getChildEnd() ;

        Const_XMLNodeIterator getChildCBegin() const;
        Const_XMLNodeIterator getChildCEnd() const;

        XMLNode &appendChild( XMLNode& );

        void removeChild( XMLNodeIterator );
        void insertChild( XMLNodeIterator, XMLNode& );

        XMLNode clone();

      private:
        class NodeData;
        NodeData *m_data;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  XMLNODE_H  */