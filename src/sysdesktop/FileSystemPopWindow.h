#ifndef FILESYSTEMPOPWINDOW_H
#define FILESYSTEMPOPWINDOW_H

#include <vector>

#include "system/FileSystemInfo.h"
#include "system/FileSystemUsageQueryResult.h"
using namespace Magna::System;

#include "basegui/PopOutWindow.h"
#include "basegui/Button.h"
#include "basegui/TableLayout.h"
using namespace Magna::GUI;

#include "FileSystemButton.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{
      
      class FileSystemPopWindow : public PopOutWindow{
        __Constructor_Destructor public:
          FileSystemPopWindow();
          virtual ~FileSystemPopWindow();

        public:
          void updateFileSystemUsage();

        __Data_Field private:
          SharedPtr<TableLayout> m_centerLayout; 

          std::vector<FileSystemInfo> m_fileSystemInfos;
          std::vector<FileSystemUsageQueryResult> m_usageResults;
          std::vector<SharedPtr<FileSystemButton> > m_fileSystemButtons;
      };

    }//namespace Desktop
  }//namespace SystemComponent
}//namespace Magna

#endif  /*  FILESYSTEMPOPWINDOW_H  */