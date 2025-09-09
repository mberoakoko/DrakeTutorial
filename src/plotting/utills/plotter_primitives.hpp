//
// Created by mbero-akoko on 9/9/25.
//

#ifndef DRAKETUTORIAL_PLOTTER_PRIMITIVES_HPP
#define DRAKETUTORIAL_PLOTTER_PRIMITIVES_HPP

#include<bits/stdc++.h>
#include<SDL3/SDL.h>

#include <utility>

namespace plotting::primitives {
    class AppBase {
    public:
        virtual ~AppBase() = default;
        virtual auto set_up() -> void = 0;
        virtual auto  run() -> void = 0;
    };
}

namespace plotting::components {

    class FigureWindow{
        SDL_Window *window_ = nullptr;
        SDL_Renderer *renderer_ = nullptr;

        std::string window_title_;
        std::uint32_t width_ , height_;

    public:
        struct FigureParams {
            std::string window_title;
            std::uint32_t width;
            std::uint32_t height;
        };
        explicit FigureWindow(std::string window_title, const std::uint32_t& width, const std::uint32_t& height)
            : window_title_(window_title), width_(width), height_(height) {
            this->init_window();
            this->init_renderer();
        };

        explicit FigureWindow(const FigureParams& params): FigureWindow(params.window_title, params.width, params.height) {};

        ~FigureWindow() {
            SDL_DestroyRenderer(renderer_);
            SDL_DestroyWindow(window_);
        }


        [[nodiscard]] auto get_window() const -> SDL_Window* {return window_;}
        [[nodiscard]] auto get_renderer() const -> SDL_Renderer* {return renderer_;}

    private:
        auto init_window() -> void {
            std::cout <<  "Initializing window " << std::endl;
            constexpr auto WINDOW_FLAGS {
                (SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY),
            };
            SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
            window_ = SDL_CreateWindow(window_title_.c_str(), width_, height_, WINDOW_FLAGS);
        };

        auto init_renderer() -> void {
            std::cout << "Initializing renderer " << std::endl;
            renderer_ = SDL_CreateRenderer(window_, nullptr);
            if (renderer_ == nullptr) {
                std::cerr << "Failed to create renderer" << std::endl;
                return;
            }
        }
    };

}

#endif //DRAKETUTORIAL_PLOTTER_PRIMITIVES_HPP