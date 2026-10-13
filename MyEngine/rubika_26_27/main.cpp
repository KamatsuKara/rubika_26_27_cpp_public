#include <SFML/Graphics.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>

#include <Globals.h>
#include <Profiler.h>
#include <Logger.h>
#include <DebugMgr.h>

#include "SceneMgr.hpp"
#include "TextureMgr.h"

int main()
{
    gData.Init();

    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "Please work...", sf::State::Windowed);

    ImGui::SFML::Init(window);

    sf::Clock clock;
    clock.restart();

    gData.SceneMgr->AddScene("Scene0");
    gData.SceneMgr->AddScene("Scene1");
    gData.SceneMgr->AddScene("Scene2");

    gData.SceneMgr->GetScene("Scene0")->AddEntity("Entity0");
    gData.SceneMgr->GetScene("Scene0")->AddEntity("Entity1");

    gData.SceneMgr->GetScene("Scene1")->AddEntity("Entity0");

    std::string objUuid = gData.SceneMgr->GetScene("Scene2")->AddEntity("Entity0")->GetUuid();
    gData.SceneMgr->GetScene("Scene2")->RemoveEntity(objUuid);

    bool pls = gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/IsaacSprite.png");


    while (window.isOpen())
    {
        gData.IncrementFrameCount();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLACK, "Frame %llu", gData.FrameCount);

        int deltaTimeMicroS = clock.getElapsedTime().asMicroseconds();
        float fDeltaTimeMS = (float)deltaTimeMicroS / 1000.f;
        float fDeltaTimeS = fDeltaTimeMS / 1000.f;
        sf::Time imGuiTime = clock.restart();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_BLUE, "Event & Input");

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

#ifdef _USE_IMGUI
            ImGui::SFML::ProcessEvent(window, event.value());
#endif
        }

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_RED, "Update");
#ifdef _USE_IMGUI
        ImGui::SFML::Update(window, imGuiTime);
#endif

        // sample
        //ImGui::ShowDemoWindow();
        //Logger::DrawLogger();
        gData.DebugMgr->Draw();

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Draw");
        window.clear();

#ifdef _USE_IMGUI
        ImGui::SFML::Render(window);
#endif
        window.display();

        PROFILER_EVENT_END();

        PROFILER_EVENT_END();
    }

    ImGui::SFML::Shutdown();

    gData.Shut();
    gData.Destroy();

    return 0;
}