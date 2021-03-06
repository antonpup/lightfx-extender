#pragma once

// Standard includes
#include <chrono>
#include <mutex>
#include <string>
#include <queue>

// Project includes
#include "../Managers/DeviceManager.h"
#include "../Managers/ChildOfManager.h"
#include "../Timelines/LightColor.h"
#include "../Timelines/Timeline.h"

// API exports
#include "../Common/ApiExports.h"


#pragma warning(push)
#pragma warning(disable : 4251)

namespace lightfx {
    namespace managers {
        class DeviceManager;
    }

    namespace devices {

        enum LFXE_API DeviceType {
            DeviceUnknown = 0x00,
            DeviceNotebook,
            DeviceDesktop,
            DeviceServer,
            DeviceDisplay,
            DeviceMouse,
            DeviceKeyboard,
            DeviceGamepad,
            DeviceSpeaker,
            DeviceOther = 0xFF
        };

        struct LFXE_API DeviceLightPosition {
            unsigned int x;
            unsigned int y;
            unsigned int z;
        };

        struct LFXE_API LightData {
            std::wstring Name = L"";
            DeviceLightPosition Position = {};
        };

        class LFXE_API Device : public managers::ChildOfManager < managers::DeviceManager > {

        public:
            Device() {}
            virtual ~Device();

            bool IsEnabled();
            bool IsInitialized();

            virtual bool Enable();
            virtual bool Disable();

            virtual bool Initialize();
            virtual bool Release();
            virtual bool Update(const std::chrono::milliseconds& timeTick);
            virtual bool Reset();

            timelines::Timeline GetActiveTimeline();
            timelines::Timeline GetQueuedTimeline();
            timelines::Timeline GetRecentTimeline();
            void QueueTimeline(const timelines::Timeline& timeline);
            bool CommitQueuedTimeline(const bool flushQueue = true);

            virtual const std::wstring GetDeviceName() = 0;
            virtual const DeviceType GetDeviceType() = 0;

            const size_t GetNumberOfLights();
            timelines::LightColor GetLightColor(const size_t lightIndex);
            LightData GetLightData(const size_t lightIndex);
            void SetLightData(const size_t lightIndex, const LightData& lightData);

        protected:
            void SetNumberOfLights(const size_t numberOfLights);

            void SetEnabled(const bool enabled);
            void SetInitialized(const bool initialized);

            timelines::Timeline ActiveTimeline;
            timelines::Timeline QueuedTimeline;
            std::mutex QueuedTimelineMutex;
            std::queue<timelines::Timeline> TimelineQueue;
            std::mutex TimelineQueueMutex;

            virtual bool PushColorToDevice(const std::vector<timelines::LightColor>& colors) = 0;

        private:
            bool isEnabled = false;
            bool isInitialized = false;
            size_t numberOfLights = 0;
            std::vector<timelines::LightColor> lightColor = {};
            std::vector<LightData> lightData = {};

            bool timelineDone = true;
            std::chrono::milliseconds timelineStart;

        };

    }
}

#pragma warning(pop)
