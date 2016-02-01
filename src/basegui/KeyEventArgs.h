#ifndef KEYEVENTARGS_H
#define KEYEVENTARGS_H

#pragma once
#pragma warning(disable:4800)

#include "basegui_lib.h"

#include "EventArgConstants.h"
#include "basedef/AbstractedEventArgs.h"

using namespace Magna::Core;

namespace Magna{  
   namespace GUI{
     class BASEGUI_LIB_EXPORT KeyEventArgs : public __Generalizes AbstractedEventArgs{
      __Constructor_Destructor public: 
        typedef uint32 PressedKeys;
         typedef uint32 KeyModifiers;
      __Constructor_Destructor public:
         explicit KeyEventArgs( GUIEventConstants::EventType type, PressedKeys keys ) :AbstractedEventArgs( static_cast<uint16>(type) ), m_keys( keys ){}
         KeyEventArgs( GUIEventConstants::EventType type, const KeyEventArgs& args ) :AbstractedEventArgs( static_cast<uint16>(type) ),  m_keys( args.m_keys ){}
         ~KeyEventArgs(){}

       __Getter public:
         inline PressedKeys getKeys() const { return m_keys; }
         KeyEventArgConstants::KeyCode getKeyCode() const { return static_cast<KeyEventArgConstants::KeyCode>(m_keys & KeyEventArgConstants::KeyCode_Mask); }
         KeyModifiers getModifers() const { return m_keys & KeyEventArgConstants::KeyModifier_Mask; }

       __Checker public:
         inline bool isCausedWithAltModifier() const { return static_cast<bool>( m_keys & KeyEventArgConstants::KeyModifier_Alt) ;}
         inline bool isCausedWithCtrlModifier() const { return static_cast<bool>( m_keys & KeyEventArgConstants::KeyModifier_Control) ;}
         inline bool isCausedWithShiftModifier() const { return static_cast<bool>( m_keys & KeyEventArgConstants::KeyModifier_Shift) ;}

       __Overloaded_Methods public:
         KeyEventArgs & operator = ( const KeyEventArgs& args ){ m_keys = args.m_keys; return *this; }

         bool operator == ( const KeyEventArgs& args ){ return m_keys == args.m_keys; }
         bool operator != ( const KeyEventArgs& args ){ return m_keys != args.m_keys; }

      __Data_Field private:
        PressedKeys m_keys;

     };

   }//GUI
}//Magna
#endif  /*  KEYEVENTARGS_H  */