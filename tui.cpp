#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border, hflow, paragraph
#include "ftxui/util/ref.hpp"  // for Ref

//int main() {
//    using namespace ftxui;
//    auto screen = ScreenInteractive::Fullscreen();
//
//
//    // The data:
//    std::string first_name;
//    std::string last_name;
//    std::string password;
//    std::string phoneNumber;
//
//    // The basic input components:
//    Component input_first_name = Input(&first_name, "first name");
//    Component input_last_name = Input(&last_name, "last name");
//
//    // The password input component:
//    InputOption password_option;
//    password_option.password = true;
//    Component input_password = Input(&password, "password", password_option);
//
//    // The phone number input component:
//    // We are using `CatchEvent` to filter out non-digit characters.
//    Component input_phone_number = Input(&phoneNumber, "phone number");
//    input_phone_number |= CatchEvent([&](Event event) {
//        return event.is_character() && !std::isdigit(event.character()[0]);
//    });
//    input_phone_number |= CatchEvent([&](Event event) {
//        return event.is_character() && phoneNumber.size() > 10;
//    });
//
//    // The component tree:
//    auto component = Container::Vertical({
//                                                 input_first_name,
//                                                 input_last_name,
//                                                 input_password,
//                                                 input_phone_number,
//                                         });
//
//    // Tweak how the component tree is rendered:
//    auto renderer = Renderer(component, [&] {
//        return vbox({
//                            // 使用 hflow 和 paragraph 来自动换行
//                            (paragraph("Hello " + first_name + " " + last_name)),
//
//                            (paragraph("Your password is " + password)),
//                            (paragraph("Your phone number is " + phoneNumber)),
//                            separator(),
//
//                            hbox(text(" First name : "), input_first_name->Render()),
//                            hbox(text(" Last name  : "), input_last_name->Render()),
//                            hbox(text(" Password   : "), input_password->Render()),
//                            hbox(text(" Phone num  : "), input_phone_number->Render()),
//                    }) | border;
//    });
//
////    auto screen = ScreenInteractive::TerminalOutput();
//    screen.Loop(renderer);
//}

//#include <memory>
//#include <string>
//#include <vector>
//#include <iomanip>
//
//#include "ftxui/component/screen_interactive.hpp"
//#include "ftxui/dom/elements.hpp"
//
//using namespace ftxui;
//
//int main() {
//    auto screen = ScreenInteractive::TerminalOutput();
//
//    // 源代码内容，每行为一个元素
//    std::vector<std::string> code_lines = {
//            "#include <iostream>",
//            "",
//            "int main() {",
//            "    std::cout << \"Hello, World!\" << std::endl;",
//            "    return 0;",
//            "}",
//            "#include <iostream>",
//            "",
//            "int main() {",
//            "    std::cout << \"Hello, World!\" << std::endl;",
//            "    return 0;",
//            "}",
//            "#include <iostream>",
//            "",
//            "int main() {",
//            "    std::cout << \"Hello, World!\" << std::endl;",
//            "    return 0;",
//            "}",
//            "#include <iostream>",
//            "",
//            "int main() {",
//            "    std::cout << \"Hello, World!\" << std::endl;",
//            "    return 0;",
//            "}"
//    };
//
//    // 存储带行号的代码元素
//    std::vector<Element> code_elements;
//    int line_number = 1;
//
//    // 遍历每行代码并添加行号
//    for (const auto& line : code_lines) {
//        std::string line_no = std::to_string(line_number++);  // 转换行号为字符串
//        // 为行号和代码添加不同的样式
//        code_elements.push_back(
//                hbox({
//                             text(line_no + "  ") | color(Color::BlueLight),   // 行号
//                             text(line),                                       // 代码
//                     })
//        );
//    }
//
//    // 将所有代码行垂直堆叠，并加上边框
//    auto code_block = vbox(code_elements) | border;
//
//    auto renderer = Renderer([&] {
//        return vbox({
//                            text("C++ Code Example:") | bold,
//                            separator(),
//                            code_block,  // 显示带行号的代码块
//                    }) | border;
//    });
//
//    screen.Loop(renderer);
//    return 0;
//}


//#include <memory>
//#include <string>
//#include <vector>
//
//#include "ftxui/component/component.hpp"
//#include "ftxui/component/screen_interactive.hpp"
//#include "ftxui/dom/elements.hpp"
//
//using namespace ftxui;
//
//int main() {
//    auto screen = ScreenInteractive::TerminalOutput();
//
//    // 源代码内容，每行为一个元素
//    std::vector<std::string> code_lines = {
//            "#include <iostream>",
//            "",
//            "int main() {",
//            "    std::cout << \"Hello, World!\" << std::endl;",
//            "    return 0;",
//            "}"
//    };
//
//    int current_line = 0;
//
//    // 创建按钮，点击时更新行号
//    auto next_button = Button("Next Line", [&] {
//        if (current_line < code_lines.size() - 1) {
//            ++current_line;
//        } else {
//            current_line = 0;  // 重置行号
//        }
//    });
//
//    // 创建 Renderer 函数来显示代码行
//    auto code_renderer = Renderer([&] {
//        std::vector<Element> code_elements;
//
//        // 遍历每行代码，显示行号并改变当前行的颜色
//        for (size_t i = 0; i < code_lines.size(); ++i) {
//            std::string line_no = std::to_string(i + 1); // 行号从1开始
//            auto line_color = (i == current_line) ? color(Color::Red) : color(Color::BlueLight);
//
//            code_elements.push_back(
//                    hbox({
//                                 text(line_no + "  ") | line_color,  // 行号颜色变化
//                                 text(code_lines[i])                  // 代码行
//                         })
//            );
//        }
//
//        // 将代码行垂直堆叠并加边框
//        return vbox({
//                            vbox(code_elements) | border,
//                            separator(),
//                            next_button->Render() | center,
//                    });
//    });
//
//    auto container = Container::Vertical({
//                                                 next_button,
//                                                 code_renderer,
//                                         });
//
//    // 通过 Renderer 来管理界面
//    auto renderer = Renderer(container, [&] {
//        return vbox({
//                            text("C++ Code Debugging Example:") | bold,
//                            separator(),
//                            code_renderer->Render(),
//                    });
//    });
//
//    screen.Loop(renderer);
//    return 0;
//}

#if 0
#include <memory>
#include <string>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

int main() {
    bool bkval=0;
    auto screen = ScreenInteractive::TerminalOutput();

    // 源代码内容，每行为一个元素
    std::vector<std::string> code_lines = {
            "#include <iostream>",
            "",
            "int main() {",
            "    std::cout << \"Hello, World!\" << std::endl;",
            "    return 0;",
            "}"
    };

    int current_line = 0;

    // 创建按钮，点击时更新行号
    auto next_button = Button("Next Line", [&] {
        if (current_line < code_lines.size() - 1) {
            ++current_line;
        } else {
            current_line = 0;  // 重置行号
        }
    });

    // 创建 Renderer 函数来显示代码行
    auto code_renderer = Renderer([&] {
        std::vector<Element> code_elements;

        // 遍历每行代码，显示行号并改变当前行的颜色
        for (size_t i = 0; i < code_lines.size(); ++i) {
            std::string line_no = std::to_string(i + 1); // 行号从1开始
            auto line_color = (i == current_line) ? color(Color::Red) : color(Color::BlueLight);

            // 在当前行的行号左边加一个红点
            Element red_dot = (i == current_line)
                              ? text("->") | color(Color::Red)
                              : text("  "); // 空格占位
            auto linebreakpoint =Button("",[&](){

            });


            code_elements.push_back(
                    hbox({
                                 red_dot,                        // 红点或空格占位
                                 text(line_no + "  ") | line_color,  // 行号颜色变化
                                 text(code_lines[i])                  // 代码行
                         })
            );
        }

        // 将代码行垂直堆叠并加边框
        return vbox({
                            vbox(code_elements) | border,
                            separator(),
                            next_button->Render() | center,
                    });
    });

    auto container = Container::Vertical({
                                                 next_button,
                                                 code_renderer,
                                         });

    // 通过 Renderer 来管理界面
    auto renderer = Renderer(container, [&] {
        return vbox({
                            text("C++ Code Debugging Example:") | bold,
                            separator(),
                            code_renderer->Render(),
                    });
    });

    screen.Loop(renderer);
    return 0;
}

#endif

#if 1
#include <cstdlib>   // for EXIT_SUCCESS
#include <iostream>  // for std::cout, std::endl
#include <memory>    // for std::shared_ptr
#include <string>    // for std::string
#include <vector>    // for std::vector

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Button, Renderer, Container, Input
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, vbox, paragraph, separator, border, Element, hflow

int main() {
    using namespace ftxui;

    auto screen = ScreenInteractive::Fullscreen();

    // Sample code lines
    std::vector<std::string> lines = {
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;",
            "int main() {",
            "    return 0;",
            "}",
            "// This is a comment",
            "int a = 5;",
            "int b = 10;"
    };

    // Breakpoints state (false means no breakpoint, true means breakpoint)
    std::vector<bool> breakpoints(lines.size(), false);

    // Function to render code with line numbers and breakpoints
    auto renderer = Renderer([&] {
        std::vector<Element> elements;
        for (size_t i = 0; i < lines.size(); ++i) {
            // Add red dot if breakpoint is set
            Element breakpoint_indicator = (breakpoints[i] ? text("●") : text(" ")) | color(Color::Red);
            Element line_number = text(std::to_string(i + 1)) | color(Color::White);

            // Create a horizontal box for each line: [line_number][dot][code]
            elements.push_back(
                    hbox(breakpoint_indicator, line_number, text(lines[i])) );
        }
        return vbox(elements) | border;
    });

    // Catch mouse events to toggle breakpoints
    renderer |= CatchEvent([&](Event event) {
        if (event.is_mouse() && event.mouse().button == Mouse::Left) { // Use ftxui::MouseButton
            int clicked_line = event.mouse().y; // Get the clicked line number

            // Check if clicked on the breakpoint area (first column)
//            && clicked_line >= 0 && clicked_line < lines.size()
            if (event.mouse().x < 4 ) {
                // Toggle breakpoint
                breakpoints[clicked_line] = !breakpoints[clicked_line];
                return true; // Event handled
            }
        }
        return false; // Event not handled
    });

    // Main loop
    screen.Loop(renderer);
    return EXIT_SUCCESS;
}

#endif