#ifndef CATEGORYBAR_H
#define CATEGORYBAR_H

#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "glue_img/Image.h"
using namespace Magna::Glue;

#include "basegui/Controller.h"
#include "basegui/Button.h"
#include "basegui/LinearLayout.h"
#include "basegui/ButtonGroup.h"
using namespace Magna::GUI;

#include "FileSystemPopWindow.h"
#include "VideoPopWindow.h"
#include "BookPopWindow.h"
#include "WebsPopWindow.h"
#include "MusicPopWindow.h"
#include "FrequentUsedAppPopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{
      
      class CategoryBar : public Controller{
        __Constants public:
          static const uint32 shared_default_width = 64;
          enum Category{
            Category_FileSystem,
            Category_FrequencyUseApps,
            Category_News,
            Category_Documents,
            Category_Readings,
            Category_Music,
            Category_FilmVideo,
            Category_Games
          };

        __Constructor_Destructor public:
          explicit CategoryBar( uint32 _init_height );
          virtual ~CategoryBar();

        public:
          void toggleCategroyPanel(  const uint32& );
          void untoggleCategoryPanel( const uint32 & );
          

        __Data_Field private:
          SharedPtr<Button> m_fileSystemButton;
          SharedPtr<Button> m_frequencyUseAppsButton;
          SharedPtr<Button> m_newsButton;
          SharedPtr<Button> m_documentsButton;
          SharedPtr<Button> m_readingsButton;
          SharedPtr<Button> m_musicButton;
          SharedPtr<Button> m_filmVideoButton;
          SharedPtr<Button> m_gamesButton;
          ButtonGroup m_group;

          SharedPtr<LinearLayout> m_linearLayout;

          std::map<uint32, SharedPtr<PopOutWindow> > m_indexMapsPopOutWnd;
          SharedPtr<FileSystemPopWindow> m_fileSysPopOutWindow;
          SharedPtr<VideoPopWindow> m_videoPopOutWindow;
          SharedPtr<BookPopWindow> m_bookPopOutWindow;
          SharedPtr<WebsPopWindow> m_websPopOutWindow;
          SharedPtr<MusicPopWindow> m_musicPopOutWindow;
          SharedPtr<FrequentUsedAppPopWindow> m_frePopWindow;

          SharedPtr<PopOutWindow> m_currentPopOutWindow;
      };


    }//namespace Desktop
  }//namespace SystemComponent
}//namespace Magna

#endif  /*  CATEGORYBAR_H  */