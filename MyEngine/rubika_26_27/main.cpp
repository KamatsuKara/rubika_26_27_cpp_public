#include <SFML/Graphics.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>

#include <Globals.h>
#include <Profiler.h>
#include <Logger.h>
#include <DebugMgr.h>

#include "SceneMgr.hpp"
#include "TextureMgr.h"

#include "TransformComponent.h"
#include "RenderComponent.hpp"

#include "RectangleShape.hpp"

int main()
{
    gData.Init();

    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "Please work...", sf::State::Windowed);

    ImGui::SFML::Init(window);

    sf::Clock clock;
    clock.restart();

    bool pls = gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/IsaacSprite.png");
    pls &= gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/Basement.png");
    pls &= gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/enemy_texture_1.png");
    pls &= gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/enemy_texture_2.png");
    pls &= gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/enemy_texture_3.png");
    pls &= gData.TextureMgr->LoadTexture("C:/Users/b.candela/Documents/Project/Cpp/VampireSurvivorEngine/rubika_26_27_cpp_public/MyEngine/Ressources/enemy_texture_4.png");

    gData.SceneMgr->AddScene("Scene1");

    Entity* currentEntity = gData.SceneMgr->GetScene("Scene1")->AddEntity("Entity0");
    RectangleShape* rect = currentEntity->AddComponent<RenderComponent>()->AddDrawable<RectangleShape>();
    rect->SetTextureAndStaticTile("Basement", "Corner_Top_Left");
    TransformComponent* currentEntityTransform = currentEntity->AddComponent<TransformComponent>();
    currentEntityTransform->SetWorldPosition(sf::Vector2f(50, 50));
    rect->SetWorldTransform(currentEntityTransform->GetMatrix());

    gData.SceneMgr->SetActiveScene("Scene1");

    gData.SceneMgr->Start();

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
                gData.SceneMgr->Destroy();
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
        gData.SceneMgr->Update(fDeltaTimeMS);

        // sample
        //ImGui::ShowDemoWindow();
        //Logger::DrawLogger();
        gData.DebugMgr->Draw();

        PROFILER_EVENT_END();

        PROFILER_EVENT_BEGIN(PROFILER_COLOR_GREEN, "Draw");
        window.clear();

        gData.SceneMgr->Draw(window);

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