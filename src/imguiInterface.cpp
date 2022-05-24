
#include "imguiInterface.h"

#include "settings.h"
#include "audio.h"
#include "game.h"

#include <SFML/Window/Event.hpp>

void ImguiInterface::initialize(sf::RenderWindow& window) {
	ImGui::SFML::Init(window);
}

void ImguiInterface::shutdown() {
	ImGui::SFML::Shutdown();
}

void ImguiInterface::pollEvent(sf::RenderWindow& window, sf::Event& theEvent) {
	ImGui::SFML::ProcessEvent(theEvent);

	if (theEvent.type == sf::Event::KeyPressed && theEvent.key.code == sf::Keyboard::M)
		Settings::General::showImgui = !Settings::General::showImgui;
}

void ImguiInterface::update(sf::RenderWindow& window, sf::Time dt) {
	ImGui::SFML::Update(window, dt);
}

void ImguiInterface::draw(sf::RenderWindow& window) {
	if (Settings::General::showImgui) {
		ImGui::Begin("Settings");

		if (ImGui::Button("Hide"))
			Settings::General::showImgui = false;

        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
            if (ImGui::BeginTabItem("General"))
            {
				ImGui::Checkbox("Autoplace", &Settings::General::autoplace);
				if (Settings::General::autoplace)
					ImGui::SliderFloat("Seconds delay", &Settings::General::autoplaceDelay, 0.25, 2);

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Aspect"))
            {
				ImGui::Checkbox("Animations", &Settings::Aspect::animations);

				if (ImGui::TreeNode("Colors"))
				{
					if (ImGui::Button("Reset")) {
						Settings::Aspect::defaultValues();

						Game::theTable->updateColors();
						Game::theScore->updateColors();
						Game::pickupBoard->updateColors();
					}

					if (ImGui::CollapsingHeader("General")) {
						ImGui::ColorEdit3("Background", Settings::Aspect::appBackground);
						ImGui::ColorEdit3("Pickup margins", Settings::Aspect::pickupMargins);
						ImGui::ColorEdit3("Text", Settings::Aspect::textColor);

						Game::theScore->updateColors();
						Game::pickupBoard->updateColors();
					}
					if (ImGui::CollapsingHeader("Cells")) {
						ImGui::ColorEdit3("Solid", Settings::Aspect::cellSolid);
						ImGui::ColorEdit3("Preview", Settings::Aspect::cellPreview);
						ImGui::ColorEdit3("Completion", Settings::Aspect::cellCompletion);
						ImGui::ColorEdit3("Margins", Settings::Aspect::cellMargins);

						Game::theTable->updateColors();
					}
					if (ImGui::CollapsingHeader("Table")) {
						ImGui::ColorEdit3("Odd", Settings::Aspect::tableOdd);
						ImGui::ColorEdit3("Even", Settings::Aspect::tableEven);
						ImGui::ColorEdit3("Minor lines", Settings::Aspect::tableMinor);
						ImGui::ColorEdit3("Major lines", Settings::Aspect::tableMajor);

						Game::theTable->updateColors();
					}

					ImGui::TreePop();
				}

                ImGui::EndTabItem();
            }
			if (ImGui::BeginTabItem("Audio"))
			{
				ImGui::Checkbox("Mute", &Settings::General::muted);
				if (!Settings::General::muted)
					ImGui::SliderInt("Volume", &Settings::General::volume, 0, 100);

				Audio::updateState();

				ImGui::EndTabItem();
			}
            ImGui::EndTabBar();
        }
		ImGui::End();
	}

	ImGui::SFML::Render(window);
}