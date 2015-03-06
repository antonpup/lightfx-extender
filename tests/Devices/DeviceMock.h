#pragma once

// Standard includes
#include <string>

// Project includes
#include "../../src/Devices/Device.h"


namespace lightfx_tests {
    namespace devices {

        class DeviceMock : public lightfx::devices::Device {

        public:
            using Device::IsEnabled;
            using Device::IsInitialized;

            using Device::Enable;
            using Device::Disable;

            using Device::Initialize;
            using Device::Release;
            using Device::Update;
            using Device::Reset;

            using Device::GetActiveLightAction;
            using Device::GetQueuedLightAction;
            using Device::GetLastLightAction;
            using Device::QueueLightAction;

            virtual bool PushColorToDevice() override { return false; }

            virtual const std::wstring GetDeviceName() override { return L"DeviceMock"; }
            virtual const lightfx::devices::DeviceType GetDeviceType() override { return lightfx::devices::DeviceType::DeviceOther; }

            using Device::GetNumberOfLights;
            using Device::GetLightData;
            using Device::SetLightData;

        };

    }
}
