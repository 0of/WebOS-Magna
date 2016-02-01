#ifndef XMLNODE_P_H
#define XMLNODE_P_H

#include "libxml/tree.h"

#include "XMLNode.h"

namespace Magna{
  namespace Network{

    typedef std::vector< XMLNode > ChildNodes;

    class XMLNode::NodeData{
    public:
      NodeData();
      explicit NodeData( xmlNodePtr node_ptr );
      ~NodeData();

      NodeData *detachingClone();

    public:
      xmlNodePtr m_node;
      AtomicInt m_invRefCount;

      String m_name;
      String m_content;

      XMLAttributes m_attributes;
      ChildNodes m_childNodes;
    };

  }//namespace Network
}//namespace Magna

#endif  /*XMLNODE_P_H  */