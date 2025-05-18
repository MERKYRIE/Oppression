#pragma once

namespace NOppression::NClient
{
    inline struct SMouse
    {
        std::unordered_map<std::string , std::shared_ptr<NMouse::SButton>> FButtons;
        std::unordered_map<std::int64_t , std::string> FButtonsAdaptors;

        std::shared_ptr<NMouse::SCursor> FCursor;

        std::shared_ptr<NMouse::SWheel> FWheel;

        SMouse();
        void IUpdate();
    }
    GMouse;
}