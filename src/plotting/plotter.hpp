//
// Created by mbero-akoko on 9/9/25.
//

#ifndef DRAKETUTORIAL_PLOTTER_HPP
#define DRAKETUTORIAL_PLOTTER_HPP
#include <imgui.h>

#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"
#include "utills/plotter_primitives.hpp"

namespace plotting {
    constexpr std::uint32_t APP_WIDTH = 800;
    constexpr std::uint32_t APP_HEIGHT = 800;


    class Figure final : public primitives::AppBase {

        bool is_running { false };
        bool exit_status { false };

        std::unique_ptr<components::FigureWindow> window_ { nullptr };

    public:
        explicit Figure() {
            this->set_up();
        }
        ~Figure() override {
            ImGui_ImplSDLRenderer3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
            SDL_Quit();
        };

        auto set_up_imgui() -> void {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io{ImGui::GetIO()};

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGui_ImplSDL3_InitForSDLRenderer(window_->get_window(), window_->get_renderer());
            ImGui_ImplSDLRenderer3_Init(window_->get_renderer());
        }

        auto set_up() -> void override {
            if (bool init_results = SDL_Init({SDL_INIT_VIDEO | SDL_INIT_EVENTS}); !init_results) {
                std::cerr << "Init failed with flags "<<
                    "(SDL_INIT_VIDEO | SDL_INIT_EVENTS)" << std::endl;
                std::cerr << SDL_GetError() << std::endl;
                exit_status = true;
            };

            window_ = std::make_unique<components::FigureWindow>(components::FigureWindow::FigureParams{
                        .window_title = "Dashboard Application",
                        .width = APP_WIDTH,
                        .height = APP_HEIGHT
            });
        };

        auto run() -> int override {
            if ( exit_status ) {
                return exit_status;
            }
            is_running = true;

            set_up_imgui();

            while ( is_running ) {
                SDL_Event event;
                // frame_limiter_.limit();
                while ( SDL_PollEvent( &event ) ) { // Event handlers should be hooked here
                    ImGui_ImplSDL3_ProcessEvent(&event);
                    if (event.type == SDL_EVENT_QUIT) {
                        is_running = false;
                    }
                }

                ImGui_ImplSDLRenderer3_NewFrame();
                ImGui_ImplSDL3_NewFrame();
                ImGui::NewFrame();

                //Render things here


                ImGui::Render();
                SDL_SetRenderDrawColor(
                   window_->get_renderer(), 0, 0, 0, 0);
                SDL_RenderClear(window_->get_renderer());
                ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), window_->get_renderer());
                SDL_RenderPresent(window_->get_renderer());
            }
            return exit_status;
        };
    };
}

#endif //DRAKETUTORIAL_PLOTTER_HPP
