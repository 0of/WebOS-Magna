#ifndef FILESYSTEMBUTTON_H
#define FILESYSTEMBUTTON_H

#include "basegui/Controller.h"
#include "basegui/Label.h"
#include "basegui/ProgressBar.h"
#include "basegui/LinearLayout.h"
#include "basegui/Button.h"
using namespace Magna::GUI;

#include "system/FileSystemInfo.h"
using namespace Magna::System;

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      class FileSystemButton : public Controller{
        __Constructor_Destructor public:
          FileSystemButton( const String& dir, FileSystemInfo::FileSystemType type
            , const String& label, float usage, const String& info);
          virtual ~FileSystemButton();

        public:
          void updateUsageBar( float val );
          void updateFileUsageInfo( const String& info );

        private:
          void accessFileSystem();

        __Data_Field private:
          class FileSysButtonIconManager{
            public:
              FileSysButtonIconManager();
              ~FileSysButtonIconManager();

              Image m_diskIcon;
              Image m_cdromIcon;
          };

          static FileSysButtonIconManager shared_file_sys_icon_manager;

          String m_fileSysDir;

          SharedPtr<Label> m_fileSystemNameLabel;
          SharedPtr<Button> m_dishButton;
          SharedPtr<ProgressBar> m_usageBar;
          SharedPtr<Label> m_fileUsageInfoLabel;

      };

    }
  }
}//namespace Magna
#endif  /*  FILESYSTEMBUTTON_H  */