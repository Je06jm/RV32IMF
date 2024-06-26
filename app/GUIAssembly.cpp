#include "GUIAssembly.hpp"

#include "GUIConstants.hpp"

#include <imgui.h>

#include <stdexcept>
#include <format>

void GUIAssembly::Draw() {
    if (ImGui::Begin("Assembly")) {
        Address pc = vm->GetPC();

        bool needs_scroll = pc != last_pc;
        last_pc = pc;

        int64_t window_begin = (pc >> 2) - WINDOW / 2 + WINDOW_SLIDE;

        if (window_begin < 0) window_begin = 0;

        int64_t window_end = window_begin + WINDOW;
        int64_t window_end_pc = window_end << 2;

        if (static_cast<Address>(window_end_pc) >= memory.GetTotalMemory()) {
            window_end = memory.GetTotalMemory() >> 2;
            window_end_pc = window_end << 2;
            window_begin = window_end - WINDOW;
        }

        if (window_begin < 0) {
            throw std::runtime_error(std::format("Memory needs to be at least {} bytes in size", WINDOW << 2));
        }

        Address window_pc = static_cast<Address>(window_begin) << 2;

        auto instrs = memory.PeekWords(window_pc, WINDOW);

        for (Address addr = window_pc, i = 0; i < WINDOW; addr += 4, i++) {
            if (instrs[i].second) {
                RVInstruction instr = RVInstruction::FromUInt32(instrs[i].first);
                std::string s_addr;
                if (vm->Is32BitMode())
                    s_addr = std::format("0x{:0>8x}", addr);
                
                else
                    s_addr = std::format("0x{:0>16x}", addr);

                if (addr == pc) {
                    ImGui::TextColored(gui_pc_highlight_color, "-> %s %s", s_addr.c_str(), std::string(instr).c_str());
                    if (needs_scroll) ImGui::SetScrollHereY();
                } else if (vm->IsBreakPoint(addr)) {
                    ImGui::TextColored(gui_break_highlight_color, "   %s %s", s_addr.c_str(), std::string(instr).c_str());
                } else {
                    ImGui::Text("   %s %s", s_addr.c_str(), std::string(instr).c_str());
                }
            }
            else {
                if (addr == pc) {
                    ImGui::TextColored(gui_pc_highlight_color, "-> Unmapped Memory");
                    if (needs_scroll) ImGui::SetScrollHereY();
                }
                else if (vm->IsBreakPoint(addr))
                    ImGui::TextColored(gui_break_highlight_color, "   Unmapped Memory");
                
                else
                    ImGui::Text("   Unmapped Memory");
            }
        }
    }

    ImGui::End();
}