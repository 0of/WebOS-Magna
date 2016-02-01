#ifndef EVENTARGCONSTATNTS_H
#define EVENTARGCONSTATNTS_H

#include "GUIEventIndexer.h"

using namespace Magna;

#include "basedef/Trigger.h"

using namespace Magna::Core;

namespace Magna{  
   namespace GUI{

     struct GUIEventConstants{
       enum EventType{
         GUIEvent_WindowClose = EventIndexer<WindowClose>::Index,
         GUIEvent_Hidden = EventIndexer<Hidden>::Index,
         GUIEvent_Shown= EventIndexer<Shown>::Index,

         GUIEvent_Moved = EventIndexer<Moved>::Index,
         GUIEvent_Resized = EventIndexer<Resized>::Index,

         GUIEvent_MousePressed = EventIndexer<MousePressed>::Index,
         GUIEvent_MousePressingMoved = EventIndexer<MousePressingMoved>::Index,
         GUIEvent_MouseReleased = EventIndexer<MouseReleased>::Index,

         GUIEvent_MouseWheelUp = EventIndexer<MouseWheelUp>::Index,
         GUIEvent_MouseWheelDown = EventIndexer<MouseWheelDown>::Index,

         GUIEvent_MouseHoverIn = EventIndexer<MouseHoverIn>::Index,
         GUIEvent_MouseHovered = EventIndexer<MouseHovered>::Index,
         GUIEvent_MouseHoverOut = EventIndexer<MouseHoverOut>::Index,

         GUIEvent_KeyPressed = EventIndexer<KeyPressed>::Index,
         GUIEvent_KeyReleased = EventIndexer<KeyReleased>::Index,

         GUIEvent_MouseClicked = EventIndexer<MouseClicked>::Index,
         GUIEvent_MouseDoubleClicked = EventIndexer<MouseDoubleClicked>::Index,

         GUIEvent_Rendering = EventIndexer<Rendering>::Index,

         GUIEvent_FocusIn = EventIndexer<FocusIn>::Index,
         GUIEvent_FocusOut = EventIndexer<FocusOut>::Index,

         GUIEvent_Scrolled = EventIndexer<Scrolled>::Index
       };
     };


     struct MouseEventArgConstants{
       enum MouseButton{
         MouseButton_NoButton  =  0x00000000 ,
         MouseButton_LeftButton  = 0x00000001 ,
         MouseButton_RightButton = 0x00000002 ,
         MouseButton_MidButton = 0x00000004 ,
         MouseButton_Other  =  0xFFFF0000 
       };
     };

     //key mapper
     //17 controller
     //18 alt
     // 16 shift
     //20 CAP
     // enter 13
  //   KeyEventArgConstants::KeyCode keyMapper[] = {
  //     KeyCode_Escape
//     };
//

     struct KeyEventArgConstants{
       enum KeyCode{    
         KeyCode_Escape =  0x0001001B ,   
         KeyCode_Tab =  0x00010009 ,      
         KeyCode_Backspace =  0x00010008 ,   
         KeyCode_Enter =  0x0001000D ,  
         KeyCode_Insert =  0x0001002D ,   
         KeyCode_Delete =  0x0001002E ,   
         KeyCode_Pause =  0x00010013 ,   
         KeyCode_Home =  0x00010024 ,   
         KeyCode_End =  0x00010023,   
         KeyCode_Left =  0x00010025 ,   
         KeyCode_Up =  0x00010026 ,   
         KeyCode_Right =  0x00010027 ,   
         KeyCode_Down =  0x00010028 ,   
         KeyCode_PageUp =  0x00010021 ,   
         KeyCode_PageDown =  0x00010022 ,   
          KeyCode_F1 =  0x00010070 ,   
          KeyCode_F2 =  0x00010071 ,   
          KeyCode_F3 =  0x00010072 ,   
          KeyCode_F4 =  0x00010073 ,   
          KeyCode_F5 =  0x00010074 ,   
          KeyCode_F6 =  0x00010075 ,   
          KeyCode_F7 =  0x00010076 ,   
          KeyCode_F8 =  0x00010077 ,   
          KeyCode_F9 =  0x00010078 ,   
          KeyCode_F10 =  0x00010079 ,   
          KeyCode_F11 =  0x0001007A,   
          KeyCode_F12 =  0x0001007B,
          KeyCode_Space  = 0x20,    
          KeyCode_Exclamation  = 0x21,   
          KeyCode_DoubleQuotation  =  0x22,   
          KeyCode_NumberSign  = 0x23   ,
          KeyCode_Dollar =   0x24   ,
          KeyCode_Percent=  0x25  , 
          KeyCode_Ampersand =  0x26,   
          KeyCode_Apostrophe   = 0x27,   
          KeyCode_LeftParenthesis =  0x28  , 
          KeyCode_RightParenthesis = 0x29,   
          KeyCode_Asterisk =  0x2A,   
          KeyCode_Plus  = 0x2B,   
          KeyCode_Comma  =0x2C,   
          KeyCode_Minus   = 0x2D, 
          KeyCode_Period =0x2E,   
          KeyCode_Slash =  0x2F,   
          KeyCode_0 =  0x30,   
          KeyCode_1 =  0x31,   
          KeyCode_2  = 0x32,
          KeyCode_3 =  0x33,
          KeyCode_4 =  0x34,   
          KeyCode_5 =  0x35,   
          KeyCode_6 =  0x36,   
          KeyCode_7 =  0x37  , 
          KeyCode_8=  0x38,   
          KeyCode_9=  0x39  , 
          KeyCode_Colon=  0x3A,
          KeyCode_Semicolon =  0x3B,   
          KeyCode_Less =  0x3C  , 
          KeyCode_Equal  =0x3D,   
          KeyCode_Greater  =0x3E,
          KeyCode_Question   =0x3F,   
          KeyCode_At  =0x40,   
          KeyCode_A =  0x41,   
          KeyCode_B=  0x42,   
          KeyCode_C=  0x43,   
          KeyCode_D=  0x44,   
          KeyCode_E=  0x45,   
          KeyCode_F=  0x46,   
          KeyCode_G=  0x47  , 
          KeyCode_H=  0x48   ,
          KeyCode_I=  0x49   ,
          KeyCode_J=  0x4A   ,
          KeyCode_K=  0x4B,   
          KeyCode_L=  0x4C  , 
          KeyCode_M=  0x4D   ,
          KeyCode_N=  0x4E   ,
          KeyCode_O=  0x4F   ,
          KeyCode_P=  0x50   ,
          KeyCode_Q=  0x51   ,
          KeyCode_R=  0x52   ,
          KeyCode_S=  0x53   ,
          KeyCode_T=  0x54   ,
          KeyCode_U=  0x55   ,
          KeyCode_V=  0x56   ,
          KeyCode_W=  0x57,   
          KeyCode_X=  0x58   ,
          KeyCode_Y=  0x59   ,
          KeyCode_Z=  0x5A ,
          KeyCode_LeftBracket  = 0x5B  , 
          KeyCode_Backslash=  0x5C   ,
          KeyCode_RightBracket=  0x5D   ,
          KeyCode_Caret =  0x5E,  /*!< symbol ^ */     
          KeyCode_Underline  =0x5F,   
          KeyCode_Backquote =  0x60,/*!< symbol ` */    
          KeyCode_a =  0x61,   
          KeyCode_b=  0x62,   
          KeyCode_c=  0x63,   
          KeyCode_d=  0x64,   
          KeyCode_e=  0x65,   
          KeyCode_f=  0x66,   
          KeyCode_g=  0x67  , 
          KeyCode_h=  0x68   ,
          KeyCode_i=  0x69   ,
          KeyCode_j=  0x6A   ,
          KeyCode_k=  0x6B,   
          KeyCode_l=  0x6C  , 
          KeyCode_m=  0x6D   ,
          KeyCode_n=  0x6E   ,
          KeyCode_o=  0x6F   ,
          KeyCode_p=  0x70   ,
          KeyCode_q=  0x71   ,
          KeyCode_r=  0x72   ,
          KeyCode_s=  0x73   ,
          KeyCode_t=  0x74   ,
          KeyCode_u=  0x75   ,
          KeyCode_v=  0x76   ,
          KeyCode_w=  0x77,   
          KeyCode_x=  0x78   ,
          KeyCode_y=  0x79   ,
          KeyCode_z=  0x7A ,
          KeyCode_LeftBrace =  0x7B,   
          KeyCode_VerticalBar =  0x7C   ,
          KeyCode_RightBrace  = 0x7D,
          KeyCode_Tilde = 0x7E
       };

       enum KeyModifier{
         KeyModifier_NoModifier =0x00000000,
         KeyModifier_Shift =  0x00020000,
         KeyModifier_Control =  0x00040000  ,
         KeyModifier_Alt =  0x00080000  
       };

       enum KeyConstantMask{
        KeyCode_Mask = 0x0001FFFF, 
        KeyModifier_Mask = 0x000E0000
       };
     };

   }//GUI
}//Magna
#endif  /*  EVENTARGCONSTATNTS_H  */