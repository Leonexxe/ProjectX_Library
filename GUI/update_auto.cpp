#include <projectX/tools/sleep.cpp>
#include "GUIEnv.cpp"

namespace PXG {
    namespace update_auto {
        int AUTO_UPDATE_FREQUENCY = -1;
        bool IS_AUTO_UPDATING = 0;

        void *AUTO_UPDATE()
        {
            while(IS_AUTO_UPDATING)
            {
                if(AUTO_UPDATE_FREQUENCY > -1) {
                    PXG::display();
                }
                px::sleep(PXG::update_auto::AUTO_UPDATE_FREQUENCY);
            }
        }
        void startAutoUpdater()
        {
            if(PXG::update_auto::AUTO_UPDATE_FREQUENCY <= -1) {
                return;
            }
            if(IS_AUTO_UPDATING == 1) {
                return;
            }

            IS_AUTO_UPDATING = 1;
        }
    }
}