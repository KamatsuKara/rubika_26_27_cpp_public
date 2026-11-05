#include <SFML/Graphics.hpp>
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>

#include <Globals.h>

#include <TextureMgr.h>
#include <SceneMgr.h>
#include <InputMgr.hpp>

#include <Scene.h>
#include <Profiler.h>
#include <Logger.h>

#include <Player.hpp>
#include <Obstacle.hpp>

#include <TransformComponent.h>

int main()
{
    gData.Init();

    sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "PLS work...", sf::State::Windowed);

    ImGui::SFML::Init(window);

    gData.TextureMgr->LoadTexture("../Ressources/IsaacSprite.png");
    gData.TextureMgr->LoadTexture("../Ressources/Basement.png");

    gData.InputMgr->LoadInput("../Ressources/Input.xml");

    Scene* scene = gData.SceneMgr->CreateScene("Main");
    {
        Player* player = scene->CreateEntity<Player>("Player");
        player->GetComponent<TransformComponent>()->SetWorldPosition(sf::Vector2f(50, 50));
        Obstacle* obstacle = scene->CreateEntity<Obstacle>("Obstacle");

        for(int i = 0; i < 100; ++i)
            scene->CreateEntity<Obstacle>(std::string("Obstacle"));
    }

    gData.SceneMgr->SetActiveScene("Main");
    gData.SceneMgr->Start();

    sf::Clock clock;
    clock.restart();

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
        
        gData.Update(fDeltaTimeS);

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