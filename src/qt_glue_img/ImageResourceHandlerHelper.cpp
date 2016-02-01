#include "ImageResourceHandlerHelper.h"

#include "Image_p.h"
#include "ImageResourceHandler.h"

namespace Magna{
  namespace Glue{
    

    bool ImageResourceHandlerHelper::getImageResourceString( const Image& img, OutStringStream& outter ){
      bool _ret_can_get = false;
      if( ! img.m_data.isNull() && img.m_data->m_int_runtimeId != 0 ){
        outter << L"var image=document.createElement('img');"
          << ImageResourceHandler::shared_Image_Res_Handler_node_name
          << L".getImageResource("
          << img.m_data->m_int_runtimeId
          << L").assignToHTMLImageElement(image);";

        _ret_can_get = !false;
      }

      return _ret_can_get;
    }

  }//namespace Glue
}//namespace Magna
