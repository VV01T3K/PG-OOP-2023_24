#pragma once
#include <array>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "../Simulator/World.hpp"

using namespace std;

class FtxMyDisplay {
   private:
    ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    const string credentials = " Wojciech Siwiec s197815 ";
    const ftxui::ButtonOption buttonStyle = ftxui::ButtonOption::Animated(
        ftxui::Color::Default, ftxui::Color::GrayDark, ftxui::Color::Default,
        ftxui::Color::White);

    void myExit() { screen.Exit(); }

    void settings() {
        using namespace ftxui;
        bool AI_REPRODUCE = false;
        bool AI_MOVE = false;
        bool HUMAN_AI = false;

        auto checkboxes = Container::Vertical({
            Checkbox("AI_REPRODUCE", &AI_REPRODUCE),
            Checkbox("AI_MOVE", &AI_MOVE),
            Checkbox("HUMAN_AI", &HUMAN_AI),
            Button(
                "❌ Exit ❌", [&] { myExit(); }, buttonStyle),
        });
        auto layout = Container::Vertical({checkboxes});

        const auto renderer = Renderer(layout, [&] {
            return vbox({vbox({
                             hbox({
                                 text(credentials) | bold,
                             }) | center,
                             separator() | size(WIDTH, EQUAL, 40),
                             vbox({
                                 layout->Render() | frame,
                             }) | center,
                         }) |
                         center | border | size(WIDTH, EQUAL, 40)}) |
                   center;
        });

        screen.Loop(renderer);
    }

   public:
    FtxMyDisplay() { system("clear"); }
    ~FtxMyDisplay() {
        system("clear");
        cout << "Screen closed" << endl;
    }

    void menu() {
        using namespace ftxui;
        uint8_t selected = 0;

        const auto buttons = Container::Vertical({});
        buttons->Add(Button(
            "⏭  Continue", [&] { selected = 0; }, buttonStyle));
        buttons->Add(Button(
            "🌍 New World", [&] { selected = 1; }, buttonStyle));
        buttons->Add(Button(
            "📂 Load World", [&] { selected = 2; }, buttonStyle));
        buttons->Add(Button(
            "⚙️  Settings", [&] { settings(); }, buttonStyle));
        buttons->Add(Button(
            "❌ Exit ❌", [&] { myExit(); }, buttonStyle));

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

    void worldView(World &world) {
        using namespace ftxui;
        auto button = Button(
            "⚙️", [&] { settings(); }, buttonStyle);

        auto header = Renderer([&] {
            return hbox({
                text("Time: " + to_string(world.checkTime())) | border,
                text("Entities: " + to_string(world.getOrganimsCount())) |
                    border,
                text(credentials) | border,
                button->Render(),
            });
        });

        auto logs = Container::Vertical({});
        for (auto log : world.getLogs()) {
            auto component =
                ftxui::Renderer([log] { return ftxui::text(log); });
            logs->Add(component);
        }

        auto layout = Container::Vertical({
            button,
            header,
            logs,
        });

        // auto board = Container::Horizontal({});
        // for (size_t i = 0; i < world.getWidth(); i++) {
        //     auto column = Container::Vertical({});
        //     for (size_t j = 0; j < world.getHeight(); j++) {
        //         auto tile = world.getTile(i, j);
        //         auto organisms = tile->getOrganisms();
        //         auto organism = organisms.empty() ? " " : "🦌";
        //         auto component = Renderer([organism] {
        //             return text(organism) | size(WIDTH, EQUAL, 4);
        //         });
        //         column->Add(component);
        //     }
        //     board->Add(column);
        // }

        const auto renderer = Renderer(layout, [&] {
            return vbox({
                       hbox({
                           header->Render(),
                       }) | flex,
                       hbox({
                           logs->Render() | flex,
                       }) | flex,
                   }) |
                   center;
        });

        screen.Loop(renderer);
    }
};