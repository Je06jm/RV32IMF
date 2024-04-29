#include <GUIInfo.hpp>

#include <imgui.h>

#include <format>

void GUIInfo::Draw() {
    if (ImGui::Begin("Info")) {
        auto vm_kbs = memory.GetTotalMemory() / 1024.0f;
        auto vm_mbs = vm_kbs / 1024.0f;
        auto vm_gbs = vm_mbs / 1024.0f;

        if (vm_mbs < 1.0) {
            ImGui::Text("VM memory size: %.2f KiBs", vm_kbs);
        } else if (vm_gbs < 1.0) {
            ImGui::Text("VM memory size: %.2f MiBs", vm_mbs);
        } else {
            ImGui::Text("VM memory size: %.2f GiBs", vm_gbs);
        }

        auto hm_kbs = memory.GetUsedMemory() / 1024.0f;
        auto hm_mbs = hm_kbs / 1024.0f;
        auto hm_gbs = hm_mbs / 1024.0f;

        if (hm_mbs < 1.0) {
            ImGui::Text("Host memory size: %.2f KiBs", hm_kbs);
        } else if (hm_gbs < 1.0) {
            ImGui::Text("Host memory size: %.2f MiBs", hm_mbs);
        } else {
            ImGui::Text("Host memory size: %.2f GiBs", hm_gbs);
        }
        
        auto ips = vm->GetInstructionsPerSecond();
        auto k_ips = ips / 1000.0f;
        auto m_ips = k_ips / 1000.0f;

        if (k_ips < 1.0) {
            ImGui::Text("IPC: %llu", ips);
        } else if (m_ips < 1.0) {
            ImGui::Text("IPC: %.2fK", k_ips);
        } else {
            ImGui::Text("IPC: %.2fM", m_ips);
        }

        ImGui::BeginChild("Current Hart Child", ImVec2(150, 20));

        if (ImGui::BeginCombo("Hart", std::format("{}", harts[selected_hart]).c_str(), 0)) {
            for (size_t i = 0; i < harts.size(); i++) {
                bool is_selected = selected_hart == i;
                if (ImGui::Selectable(std::format("{}", harts[i]).c_str(), is_selected, 0)) {
                    selected_hart = i;
                    is_selected = true;
                }

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }

        ImGui::EndChild();
    }

    ImGui::End();
}