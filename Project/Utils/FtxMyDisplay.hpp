#pragma once
#include <array>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>

using namespace ftxui;
using namespace std;

class FtxMyDisplay {
   private:
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    const string credentials = "Wojciech Siwiec s197815";

    void myExit() { screen.Exit(); }

    void settings() {
        auto modal = Container::Vertical({});

        auto renderer = Renderer(modal, [&] {
            return vbox({
                hbox({
                    text(credentials) | bold,
                }) | center,
                separator() | size(WIDTH, EQUAL, 40),
                modal->Render() | border | size(WIDTH, EQUAL, 40) | center,
            });
        });

        screen.Loop(renderer);
    }

   public:
    FtxMyDisplay() { system("clear"); }
    ~FtxMyDisplay() {
        cout << "Goodbye!" << endl;
        cin.get();
        system("clear");
    }

    void menu() {
        uint8_t selected = 0;

        const auto style = ButtonOption::Animated(
            Color::Default, Color::GrayDark, Color::Default, Color::White);

        const auto buttons = Container::Vertical({});
        buttons->Add(Button(
            "⏭  Continue", [&] { selected = 0; }, style));
        buttons->Add(Button(
            "🌍 New World", [&] { selected = 1; }, style));
        buttons->Add(Button(
            "📂 Load World", [&] { selected = 2; }, style));
        buttons->Add(Button(
            "⚙️  Settings", [&] { settings(); }, style));
        buttons->Add(Button(
            "❌ Exit ❌", [&] { myExit(); }, style));

        const auto renderer = Renderer(buttons, [&] {
            return vbox({vbox({
                             hbox({
                                 text(credentials) | bold,
                             }) | center,
                             separator() | size(WIDTH, EQUAL, 40),
                             vbox({
                                 buttons->Render() | vscroll_indicator | frame,
                             }) | center,
                         }) |
                         center | border | size(WIDTH, EQUAL, 40)}) |
                   center;
        });

        screen.Loop(renderer);
    }
};